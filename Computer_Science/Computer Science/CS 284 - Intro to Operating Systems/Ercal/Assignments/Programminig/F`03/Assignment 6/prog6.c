/* 
 * Assignment 6 
 * Author: Brian Sea 
 * Date: 10/14/03 
 * 
 * Purpose: 
 * 
 * This program is meant to demostrate the classical Producer/Consumer 
 * problem.  However, this program is coded to work with any number of: 
 * 
 * Producers - NUM_PROD 
 * Consumers - NUM_CONS 
 * Buffers - NUM_BUF 
 * Widgets - NUM_OBJS 
 * Buffer Size - BUFFER_SIZE 
 * 
 * Also this program has a set way that producers place objects into buffers 
 * and consumers remove them. 
 * 
 * Policy for Producers:  A Producer will place a widget in the buffer with 
 * the LEAST number of widgets in it at the time of checking. 
 * 
 * Policy for Consumers: A Consumer will start removing a widget from a buffer 
 * at random.  If there are no widget in that buffer, then the Consumer will 
 * begin a round-robin approach of picking a buffer, beginning with the one the 
 * Consumer started with. 
 * 
 * To compile:  gcc -o prog6 prog6.c -lpthread 
 */ 
 
 
#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>    /* POSIX threads */ 
#include <signal.h>     /* signals */ 
#include <sys/wait.h>   /* wait() */ 
#include <sys/types.h>  /* errno values */ 
#include <errno.h>      /* errno values */ 
#include <time.h>       /* time() */ 
 
/*  
 * FILE scope defines 
 * 
 * NUM_PROD - number of producers 
 * NUM_CONS - number of consumers 
 * NUM_BUF  - number of buffers 
 * NUM_OBJS - number of objects to create 
 * BUFFER_SIZE - the size of each buffer 
 */ 
#define NUM_PROD    7 
#define NUM_CONS    3 
#define NUM_BUF     2 
#define NUM_OBJS    100 
#define BUFFER_SIZE 8 
 
 
/* 
 * Structure to hold the ID of each thread and the number of widgets 
 * manipulated. 
 */ 
typedef struct id 
{ 
    pthread_t ID; 
    unsigned int num; 
} ID_t; 
 
/* 
 * Structure representing one widget in the Buffer. 
 * 
 * Creator - the pthread that filled in the widget.  This is for accounting 
 *           purposes and is currently not used (though it is filled). 
 * 
 * ID - the ID of the widget.  Once again for accounting and is currently not 
 *      used (though it is filled correctly). 
 * 
 * empty - boolean value of whether the widget is empty. 1 means empty, 0 
 *         means full. 
 */ 
typedef struct widget 
{ 
    pthread_t Creator; 
    unsigned int ID; 
    int empty; 
} widget_t; 
 
/* 
 * Structure that represents the Buffer.   
 * 
 * Widgets - the actual widgets in the buffer. 
 * num - the number of widgets in the Buffer that are full. 
 * Mutex - the mutex associated with the buffer.  Used to provide thread 
 *         safety to the structure. 
 */ 
typedef struct Buffer 
{ 
    widget_t Widgets[ BUFFER_SIZE ]; 
    int num; 
    pthread_mutex_t Mutex; 
} Buffer_t; 
 
/* Current counts of units produced and consumed */ 
int prod_count =    0; 
int cons_count =    0; 
 
/* The actual Buffers used to store the Widgets */ 
Buffer_t Buffers[ NUM_BUF ]; 
 
pthread_mutex_t mutex_prod;  /* Protect prod_count */ 
pthread_mutex_t mutex_cons;  /* Protect cons_count */ 
 
/* 
 * rand() is supposedly not MT-safe.  I am not sure if Linux has made rand() 
 * MT-safe or not (no rand_r function exists).   
 * 
 * Therefore, this mutex is used to make sure that only one thread calls the 
 * rand() function at any one time. 
 */ 
pthread_mutex_t mutex_rand;   
 
/* 
 * Condition variables used in the program: 
 * 
 * cond_need_objs - signaled when more objects need to be created. Used to wake 
 *                  up idle Producers so they can make more objects. 
 *  
 * cond_need_space - signaled when more space is needed.  Used to wake up idle 
 *                   Consumers so they can buy more objects. 
 */ 
pthread_cond_t cond_need_objs; 
pthread_cond_t cond_need_space; 
 
/*  
 * initialize all of our FileScope variables */ 
void Init_FileScopes() 
{ 
    int i, j; 
 
    for( i = 0; i < NUM_BUF; i++ ) 
    { 
        for( j = 0; j < BUFFER_SIZE; j++ ) 
        { 
            Buffers[i].Widgets[j].Creator = 0; 
            Buffers[i].Widgets[j].ID = 0; 
            Buffers[i].Widgets[j].empty = 1; 
        } 
 
        pthread_mutex_init( &Buffers[i].Mutex, NULL); 
    } 
 
    pthread_mutex_init( &mutex_prod, NULL ); 
    pthread_mutex_init( &mutex_cons, NULL ); 
    pthread_mutex_init( &mutex_rand, NULL ); 
 
    pthread_cond_init( &cond_need_space, NULL); 
    pthread_cond_init( &cond_need_objs, NULL ); 
} 
 
/* The Producer */ 
int Producer( int arg ) 
{ 
 
    const int MAXTIME = 5; 
    int i, j; 
    int sleep_time; 
    int minBuf; 
    int Placed = 0; 
    int local_prod_count; 
 
    int Widget_Placed; 
 
    /* Setup our ID structure */ 
    ID_t ID; 
     
    ID.ID = pthread_self(); 
    ID.num = 0; 
 
    while( 1 ) 
    { 
        Placed = 0; 
 
        /* Generate our sleep time.  Since we use rand(), protect it */ 
        pthread_mutex_lock( &mutex_rand ); 
            sleep_time = rand() % MAXTIME + 1; /* 1 - MAXTIME */ 
        pthread_mutex_unlock( &mutex_rand ); 
 
        sleep( sleep_time ); 
 
        /*   
         *  Check prod_count.  If it's not at our NUM_OBJS then we will "make" 
         *  one.  We do not actually place the widget in the Buffer yet.  We 
         *  simply increment to tell other producers that another widget has 
         *  been created.  This is called "forward counting" 
         * 
         *  If we hit our production count, then return the number of objects 
         *  we have created. 
         * 
         *  Protect prod_count only, since that's the only variable that needs 
         *  protection! 
         */ 
        pthread_mutex_lock( &mutex_prod ); 
            if( prod_count == NUM_OBJS ) 
            { 
                pthread_mutex_unlock( &mutex_prod ); 
                return ID.num; 
            } 
     
            prod_count++; 
            local_prod_count = prod_count; 
        pthread_mutex_unlock( &mutex_prod ); 
 
        ID.num++;  /* We made a widget */ 
 
        /* We've made a widget and accounted for it.  We must place it in a 
         * Buffer.  Therefore, we run this loop until we've placed it. 
         */ 
        while( !Placed ) 
        { 
            /* 
             * Here we try to find the Buffer with the LEAST number of widgets 
             * in it.  We do this by checking each *unlocked* buffer.  We do 
             * it this way so that other producers can place widgets at the 
             * same time as this Producer. 
             */ 
            minBuf = -1; 
            for( i = 0; i < NUM_BUF; i++ ) 
            { 
                /*  
                 * Try to grab the lock on a Buffer.  If it doesn't work, then 
                 * we move on to the next one. 
                 */ 
                if( pthread_mutex_trylock( &Buffers[i].Mutex ) != EBUSY ) 
                { 
                    /*  
                     * Got the lock!  Now check if the number of widgets in 
                     * the newly locked buffer is lower than our current 
                     * minimum 
                     * 
                     * If minBuf is -1, then it's our first time though.  Set 
                     * as minimum immediately. 
                     */ 
 
                    if( minBuf == -1 ) 
                    { 
                        minBuf = i; 
                        pthread_mutex_unlock( &Buffers[i].Mutex ); 
                        continue; 
                    } 
                         
                    if( Buffers[i].num < Buffers[minBuf].num ) 
                    { 
                        /*  
                         * New Minimum!  We can now unlock our old minimum 
                         * buffer (so others can use it) and move our minimum 
                         * to the newly found buffer (which we keep the lock 
                         * on so that others stay out) 
                         */ 
                        pthread_mutex_unlock( &Buffers[minBuf].Mutex ); 
                        minBuf = i; 
                    } 
                    else 
                    { 
                        /*  
                         * Not lower.  Unlock the buffer since we don't want 
                         * it 
                         */ 
                        pthread_mutex_unlock( &Buffers[i].Mutex ); 
                    } 
                } 
            } 
 
            /* We didn't get ANY lock.. try again */ 
            if( minBuf == -1 ) 
            { 
                continue; 
            } 
 
            /*  
             * We've got a lock... Now we have make to sure that we have a  
             * place to put it. 
             */ 
            for( i = 0; i < BUFFER_SIZE; i++ ) 
            { 
                /* Empty!  Fill in the appropriate data */ 
                if( Buffers[minBuf].Widgets[i].empty ) 
                { 
                    Buffers[minBuf].Widgets[i].empty = 0; 
                    Buffers[minBuf].Widgets[i].Creator = pthread_self(); 
                    Buffers[minBuf].num++; 
                    Buffers[minBuf].Widgets[i].ID = local_prod_count; 
  
                    /* 
                     * We save the ID localy, so we can increase 
                     * speed by a factor of ... alot 
                     */ 
                    Widget_Placed = Buffers[minBuf].Widgets[i].ID; 
                    Placed = 1;  /* We Placed out widget */ 
 
                    /* Tell the consumers we placed a widget */ 
                    pthread_cond_signal( &cond_need_objs ); 
                    break; 
                } 
            } 
         
            /*  
             * Our Buffer was full.  If this buffer was full then there's a 
             * good chance all the others were too.  So we'll just sit here 
             * until a consumer has freed some space for us 
             */ 
            if( i == BUFFER_SIZE && !Placed ) 
            { 
                pthread_cond_signal( &cond_need_objs ); 
                pthread_cond_wait( &cond_need_space, &Buffers[minBuf].Mutex ); 
            } 
 
            /* free our Buffer.  We do like to share! */ 
            pthread_mutex_unlock( &Buffers[minBuf].Mutex ); 
 
            /* 
             * System calls are slow.  Since we want to minimize the amount of 
             * time in a lock we move this statement to a plae where no locks 
             * are held.  Now the OS can take all the time it wants. 
             */ 
            printf("Producer %d - Created widget %d.\n",  
                pthread_self(), Widget_Placed ); 
        } 
    } 
} 
 
/* The Consumer  
 * This function runs very similiar to the Producer function.  Difference will 
 * be highlighted. 
 */ 
int Consumer( int arg ) 
{ 
    int i,j; 
    int sleep_time; 
    int Buf; 
    int Bought; 
    int Entered; 
 
    int Widget_Bought; 
    
    ID_t ID; 
 
    ID.ID = pthread_self(); 
    ID.num = 0; 
     
    while( 1 ) 
    { 
        Bought = 0; 
 
        /*  
         * Here we're using the rand() call for two things.  One is to pick 
         * the buffer and the other is our sleep time  
         */ 
        pthread_mutex_lock( &mutex_rand ); 
            sleep_time = (rand() % 1000) + 500; /* 500 - 1500 */ 
            Buf = rand() % NUM_BUF; 
        pthread_mutex_unlock( &mutex_rand ); 
 
        /* Sleep is used in microseconds */ 
        usleep( sleep_time ); 
 
        /* 
         * "Forward count" our buying 
         */ 
        pthread_mutex_lock( &mutex_cons ); 
            if( cons_count == NUM_OBJS ) 
            { 
                pthread_mutex_unlock( &mutex_cons ); 
                return ID.num; 
            } 
     
            cons_count++; 
        pthread_mutex_unlock( &mutex_cons ); 
 
        ID.num++; 
 
        /* While we haven't bought a widget */ 
        while( !Bought ) 
        { 
            Entered = 0; 
 
            /* 
             * Try to buy a widget.  We start at our random value and move 
             * through the buffers in a round-robin approach 
             * 
             * We use the Entered flag to determine if we've been through this 
             * loop before, so we don't keep looping! 
             */ 
            for( i = Buf; i != Buf || !Entered; i %= NUM_BUF ) 
            { 
                if( Bought ) 
                { 
                    break; 
                } 
 
                Entered = 1; 
 
                if( pthread_mutex_trylock( &Buffers[i].Mutex ) != EBUSY ) 
                { 
                    /* There's a widget in this buffer. Get it! */ 
                    if( Buffers[i].num > 0 ) 
                    { 
                        for( j = 0; j < BUFFER_SIZE; j++ ) 
                        { 
                            if( !Buffers[i].Widgets[j].empty ) 
                            { 
                                Buffers[i].Widgets[j].empty = 1; 
                                Buffers[i].Widgets[j].Creator = 0; 
                                Buffers[i].num--; 
 
                                /*  
                                 * We save the ID localy, so we can increase 
                                 * speed by a factor of ... alot 
                                 */ 
                                Widget_Bought = Buffers[i].Widgets[j].ID; 
                                Bought = 1; 
 
                                /* Tell the Producers they have room */ 
                                pthread_cond_signal( &cond_need_space ); 
                                break; 
                            } 
                        } 
                    } 
 
                    pthread_mutex_unlock( &Buffers[i].Mutex ); 
                } 
 
                i++; 
            } 
 
            /*  
             * There's nothing for me to buy.  So I'll just wait for the 
             * Producers to get working! 
             */ 
            if( i == Buf && !Bought ) 
            { 
                pthread_mutex_lock( &Buffers[i].Mutex ); 
                pthread_cond_signal( &cond_need_space ); 
                pthread_cond_wait( &cond_need_objs, &Buffers[i].Mutex ); 
                pthread_mutex_unlock( &Buffers[i].Mutex ); 
            } 
        } 
 
        /* System call.  Outside locks */ 
        printf("Consumer %d - Bought Widget %d.\n", pthread_self(), 
                            Widget_Bought ); 
    } 
} 
 
/* Ahh.. the main() */ 
int main( int argc, char *argv[], char *env[] ) 
{ 
    int i, j, Ptotals = 0, Ctotals = 0; 
    pthread_t ThreadPool[ NUM_PROD + NUM_CONS ]; 
    int ThreadRtns[ NUM_PROD + NUM_CONS ]; 
 
    /* Seed the random generator */ 
    srand( time(NULL) ); 
 
    /*  
     * Pull off the first 12 numbers to increase inpredicability.  Notice we 
     * do not protect rand() here.  This is because no other threads are 
     * running right now. 
     */ 
    for( i = 0; i < 12; i++ ) 
    { 
        rand(); 
    } 
 
    printf("%s: Starting Execution.\n", argv[0] ); 
 
    Init_FileScopes(); 
 
    /* Make our producers */ 
    for( i = 0; i < NUM_PROD; i++ ) 
    { 
        pthread_create( ThreadPool + i, NULL,  
                    (void *(*)(void *))Producer, (void *) i ); 
    } 
 
    /* Make our consumers */ 
    for( i = 0; i < NUM_CONS; i++ ) 
    { 
        pthread_create( ThreadPool + NUM_PROD + i, NULL, 
                    (void *(*)(void *))Consumer, (void *) (i + NUM_PROD) ); 
    } 
 
    /* Now we join them one by one */ 
    for( i = 0; i < NUM_PROD + NUM_CONS; i++ ) 
    { 
        pthread_join( ThreadPool[i], (void**)&ThreadRtns[i] ); 
    } 
 
    /* Our Summary at the end */ 
    printf("===============\n"); 
    printf("SUMMARY\n"); 
    printf("===============\n\n"); 
    for( i = 0; i < NUM_PROD; i++ ) 
    { 
        printf( "%s: Joined Producer %d - Created %d widgets.\n", 
                argv[0], ThreadPool[i], ThreadRtns[i] ); 
 
        Ptotals += ThreadRtns[i]; 
    } 
 
    printf("\n"); 
    for( i = 0; i < NUM_CONS; i++ ) 
    { 
        printf( "%s: Joined Consumer %d - Bought %d widgets.\n", 
                argv[0], ThreadPool[ i + NUM_PROD],  
                ThreadRtns[i+NUM_PROD] ); 
 
        Ctotals += ThreadRtns[ i + NUM_PROD ]; 
    } 
 
    printf("\nTotals:  Producers - %d   Consumers - %d\n",  
            Ptotals, Ctotals ); 
 
    return 0; 
} 
