/*****************************************************************************
**   CS284 Operating Systems
**   Programers: Robert Graham, Pat Keeven
**   Programming Assignment #8
**   Program name: tempserver.c (server side)
**
**   This program demonstrates how to use socket for network Tic-Tac-Toe.
**   Usage:
**     in linux: gcc tempserver.c -o server -lpthread -lnsl
**     then run server.
**   Version: 1.0
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>  /* define socket */
#include <netinet/in.h>  /* define internet socket */
#include <netdb.h>       /* define internet socket */
#include <string.h>

#define SERVER_PORT 9999        /* define a server port number */
#define MAX_CLIENT 2           /* maximum clients */
#define true 1
#define false 0


struct sockaddr_in server_addr = { AF_INET, SERVER_PORT };
struct sigaction act;

int client_fd[MAX_CLIENT] = {0}; /* store FD for clients */
pthread_mutex_t m; /* mutex for accessing client_fd[] */
pthread_mutex_t b; /* mutex for accessing the board*/
pthread_mutex_t np; /*mutex for accessing numplayers*/
pthread_mutex_t t;  /* mutex to access current turn*/
pthread_mutex_t w;  /* winner mutex */
pthread_mutex_t q; /* score mutex */
char board[32];   //char array representing tictactoe board
int turn=0;       //numturns progressed in game
int numplayers=0;  //num players in game
int wins1=0, wins2=0; //wins for player 1 and 2
int win;              //bool style value for if the game has been won



//Function description: checkwinner determines winner of game
//Pre: None
//Post: checks board to see if there is a winner, sets win flag, and returns
//player number of winner

int checkwinner();                 /* Winner */

//Function description: board initializer
//Pre: None
//post: empty board is initialized, all Xs and Os replaced with blank spaces
//turn set to 0, win set to false    
void resetboard();                 /* Board initializer */

//Function descriprion: client handler thread
//Pre: none
//POST: chat and tic tac toe play are handled here
void* client_handler( void* );     /* client handler thread */

//Function description: signal thread
//Pre: none
//POST: signals are handled for the threads here
void sigint_handler();            /* sigint handler */


pthread_t thread;

int main( int argc, char* argv[] )
{
    int sd, ns, i;
    struct sockaddr_in client_addr = { AF_INET };
    int client_len = sizeof( client_addr );
    char buf[512], *host;

     
    resetboard();     //initial set up of the tic tac toe board
    
    /* set SIGINT handler  */
    act.sa_handler = sigint_handler; //specify signal handler
    sigemptyset( &(act.sa_mask) ); //dump signals present at beginning
    sigaction( SIGINT, &act, NULL );   //tell program to use our handler
    host = (char*)getenv( "HOSTNAME" ); //get host name

    /* create a socket */
    if( ( sd = socket( AF_INET, SOCK_STREAM, 0 ) ) == -1 )
    {
      perror( "server: socket failed" );
      exit( 1 );
    }
    
    /* bind a socket */
    if( bind(sd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1 )
    {
      perror( "server: bind failed" );
      exit( 1 );
    }

    /* listen for clients */
    if( listen( sd, MAX_CLIENT ) == -1 )
    {
      perror( "server: listen failed" );
      exit( 1 );
    }

    printf("Server is listening for at most %d clients\n", MAX_CLIENT);

    /* create a thread for each new client */
    while( 1 )
    {
        /* accept a new client */
      if( ( ns = accept( sd, (struct sockaddr*)&client_addr,
        &client_len ) ) == -1 )
        {
          perror( "server: accept failed" );
          exit( 1 );
        }

        /* find next available in client_fd[] to store FD */
        pthread_mutex_lock( &m );       //critical section
        for( i = 0; i < MAX_CLIENT; ++i ) //client_fd
          {
            if( client_fd[i] == 0 )
              {
                client_fd[i] = ns;
                break;
              }
          }
        pthread_mutex_unlock( &m );

        /* create a thread to handle the new client */
        pthread_create( &thread, NULL, client_handler, &ns);
        pthread_mutex_lock(&np);
        ++numplayers;
        pthread_mutex_unlock(&np);

    }

    return 0;
}

/*
 * SIGINT handler
 */
void sigint_handler()
{
    int i;
    char buf[512], *host;
  

    /*
     * send shutdown message to clients
     */
    host = (char*)getenv( "HOSTNAME" );
    strcpy( buf, "SERVER on " );
    strcat( buf, host );
    strcat( buf, ": Server is going down in 10 seconds.\n" );
    printf( "%s\n", buf );
    

    pthread_mutex_lock( &m );
    for( i = 0; i < MAX_CLIENT; ++i )
    {
      if( client_fd[i] != 0 )
        {
          if( write( client_fd[i], buf, sizeof( buf ) ) == -1 )
            {
              perror( "server: write failed" );
              exit( 1 );
            }
        }
    }
    pthread_mutex_unlock( &m );
    
    sleep(10);

    /*
     * sent ~quit to all clients
     */
    strcpy( buf, "~quit" );
    pthread_mutex_lock( &m );
    for( i = 0; i < MAX_CLIENT; ++i )
    {
      if( client_fd[i] != 0 )
        {
          if( write( client_fd[i], buf, sizeof( buf ) ) == -1 )
            {
              perror( "server: write failed" );
              exit( 1 );
            }
        }
    }
    pthread_mutex_unlock( &m );

    unlink( server_addr.sin_addr );
    exit( 1 );
}

/*
 * client handler thread
 */
void* client_handler( void* arg )
{
    int i=0, nread;       //nread, size of read buffer -1 if bad read
    int ns = *(int*)arg;  //ns: current thread socket num
    char  read_buf[512], write_buf[512], client_name[512]; 
    char *host, temp;     //host: name of host
    int goneyet=0;        //bool representing if a player has moved yet
    int playernum, place=0; //playernum: number of player for thread
                            //place: holder for winner of game
    char c;                 //letter representing 'X' or 'O', depending on player
    char buf [512];         //temp buffer for storing data


    pthread_mutex_lock(&np);
    playernum=numplayers;        //set playernum to current numplayers
    pthread_mutex_unlock(&np);

    if(playernum==1)  //set c for this player
    {
      c='X';
    }
    else c='O';

    /* get the host name */
    host = (char*)getenv( "HOSTNAME" );

    /*
     * read in client name
     */
    nread = read( ns, client_name, sizeof( client_name ) );
    if( nread == -1 )
      {
        perror( "server: read failed" );
        exit( 1 );
      }
    printf( "SERVER on %s: %s connected\n", host, client_name );

    
 
/*
* send "welcome" and instructions to new client
*/
   
    strncpy( write_buf, "SERVER on ", 512 );
    strncat( write_buf, host , 512);
    strncat( write_buf, ": Welcome ", 512 );
    strncat( write_buf, client_name, 512 );
    strncat( write_buf, "! type exit to leave.", 512 );
    strncat( write_buf, "\n1 | 2 | 3\n  |   |\n---------\n4 | 5 | 6\n  |   |\n---------\n7 | 8 | 9\n  |   |\n", 512);
    strncat( write_buf, "\n\nWelcome to Keeven and Graham's Tic-Tac Toe game.\n", 512);
    strncat( write_buf, "You are player number: ", 512);

    sprintf(buf, "%d\n", playernum+1);
    strncat( write_buf, buf, 512);
    strncat( write_buf, "Enter the number corresponding to the space you wish to place a piece.\n", 512);
    strncat( write_buf, "Enter 0 to display the scoreboard", 512);

    if( write( ns, write_buf, sizeof( write_buf ) ) == -1 )
    {
      perror( "server: write failed" );
      exit( 1 );
    }
      

    /*                                   
     * send new client name to other clients
     */
    strcpy( write_buf, "SERVER on " );
    strcat( write_buf, host );
    strcat( write_buf, ": " );
    strcat( write_buf, client_name );
    strcat( write_buf, " enters" );                                 

    while( 1 )
    {

      nread = read( ns, read_buf, sizeof( read_buf ) );

      if( nread == -1 )
      {
        perror( "server: read failed" );
        exit( 1 );
      }



 /*
  * Tic-Tac-Toe code begins
  */ 
    
    
    printf("%d \n", i);
    pthread_mutex_lock(&t);
    if((isdigit(read_buf[0])) && (strlen(read_buf)==1))  //input is a signal digit
      {
        temp=atoi(read_buf);  //cahnge value to int
        if(temp==0)  //display scores
          {

            pthread_mutex_lock(&q);
            sprintf(buf, "System: Player 1: %d  ::  Player 2: %d", wins1, wins2);
            pthread_mutex_unlock(&q);
            strncpy(write_buf, buf, 512);
          }
        else if(turn%2!=playernum)  //not this players turn to move
        strncpy(write_buf, "System: Not your turn", 512);
        else
        {
          printf(" %s %d ", read_buf, temp);
          pthread_mutex_lock(&b);
          strncpy(write_buf, " ", 512);

          if(temp==1)   //place piece in spot indicated by temp
            {
              if(board[1]!=' ')   //space full
              {
                strncpy(write_buf, "System: That space is occupied", 512);
              }
              else
              {
                board[1]=c;
                turn++;
              }
          }
          if(temp==2)
          {
            if(board[3]!=' ')
            {
              strncpy(write_buf, "System: That space is occupied", 512);
            }
            else
            {
              board[3]=c;
              turn = turn+1;
              goneyet=true;
            }
          }

          if(temp==3)
          {
            if(board[5]!=' ')
            {
              strncpy(write_buf, "System: That space is occupied", 512);
            }
            else
            {
              board[5]=c;
              turn = turn+1;
              goneyet=true;
            }
          }

          if(temp==4)
           {
              if(board[13]!=' ')
              {
                strncpy(write_buf, "System: That space is occupied", 512);
              }
              else
              {
                board[13]=c;
                turn = turn+1;
                goneyet=true;

              }
            }

          if(temp==5)
          {
            if(board[15]!=' ')
            {
              strncpy(write_buf, "System: That space is occupied", 512);
            }
            else
            {
              board[15]=c;
              turn = turn+1;
              goneyet=true;

            }
          }

          if(temp==6)
          {
            if(board[17]!=' ')
            {
              strncpy(write_buf, "System: That space is occupied", 512);
            }
            else
            {
              board[17]=c;
              turn = turn+1;
              goneyet=true;

            }
          }

          if(temp==7)
          {
            if(board[25]!=' ')
            {
              strncpy(write_buf, "System: That space is occupied", 512);
            }
            else
            {
              board[25]=c;
              turn = turn+1;
              goneyet=true;
            }
          }

          if(temp==8)
          {
            if(board[27]!=' ')
            {
              strncpy(write_buf, "System: That space is occupied", 512);
            }
            else
            {
              board[27]=c;
              turn = turn+1;
              goneyet=true;

            }
          }
          if(temp==9)
          {
            if(board[29]!=' ')
            {
              strncpy(write_buf, "System: That space is occupied", 512);
            }
            else
            {
              board[29]=c;
              turn = turn+1;
             goneyet=true; 
            }
            
          }    //end if (temp==9)
        }      //end else  

        if( write( ns, write_buf, sizeof( write_buf ) ) == -1 )
        {
            perror( "server: write failed" );
            exit( 1 );
        }
      }      // end if input a single digit
      

      pthread_mutex_unlock(&b);
      place=checkwinner();  //check to see if there's a winner
    if(place!=1 && turn==9) //a tie has happened  send messages to clients
    {
       pthread_mutex_lock( &m);
       strncpy(write_buf, "TIE! \n ", 512);

       for( i = 0; i < MAX_CLIENT; ++i )
       {
          if( client_fd[i] != 0 )
          {
            if( write( client_fd[i], write_buf, sizeof( write_buf ) ) == -1 )
              {
                perror( "server: write failed" );
                exit( 1 );
              }
          }
        }
        pthread_mutex_unlock( &m );
        resetboard();

    }                                        
    pthread_mutex_unlock( &t );
    
    /*
     * someone has won the game
     */  
    if(place==1)
     {
       place=0;
       
       /*
        * declare winner to clients
        */
       strncpy(write_buf, "WINNER: PLAYER: ", 512);
       pthread_mutex_lock( & w);
       sprintf(buf, "%d\n", win);
       pthread_mutex_unlock( & w);
       pthread_mutex_lock( &m );
       strcat(write_buf, buf);
       printf("buffer %s\n", buf);
       for( i = 0; i < MAX_CLIENT; ++i )
        {
          if( client_fd[i] != 0 )
          {
            if( write( client_fd[i], write_buf, sizeof( write_buf ) ) == -1 )
              {
                perror( "server: write failed" );
                exit( 1 );
              }
          }
        }
        pthread_mutex_unlock( &m );
        
        /*
         * reset board for new game
         */
        resetboard();
     }

      // End tic-tac-toe code
      
      /*
       * Keep track of chatter on server
       */
      printf( "%s: %s\n", client_name, read_buf );
  

      /*
       * distribute chat to other client
       */
      if( strlen( read_buf ) == 0 ) break;
      else if( strcmp( read_buf, "exit" ) != 0 ) //if exit not recieved
        {
          pthread_mutex_lock( &m );
          for( i = 0; i < MAX_CLIENT; ++i )
            {
              if( client_fd[i] != 0 && client_fd[i] != ns )
                {
                  strcpy( write_buf, client_name );
                  strcat( write_buf, ": " );
                  strcat( write_buf, read_buf );
                  strcat(write_buf, board);
                

             if( write(client_fd[i], write_buf,
                sizeof( write_buf ))== -1 )
                {
                  perror( "server: write failed" );
                  exit( 1 );
                }
                }

            }
          
            pthread_mutex_unlock( &m );
            strcpy(write_buf, "");
        } 
        else
          {
            write( ns, read_buf, sizeof( read_buf ) );
            pthread_mutex_lock( &m );
            for( i = 0; i < MAX_CLIENT; ++i )
              {
                if( client_fd[i] == ns )
                {
                  client_fd[i] = 0;
                  break;
                }
              }
              pthread_mutex_unlock( &m );
              break;
           }       
 }         
 

    /*
     * send the client name who leaves
     */
    printf( "SERVER on %s: %s disconnected\n", host, client_name );
    strcpy( write_buf, "SERVER on " );
    strcat( write_buf, host );
    strcat( write_buf, ": " );
    strcat( write_buf, client_name );
    strcat( write_buf, " leaves" );
    pthread_mutex_lock( &m );

    for( i = 0; i < MAX_CLIENT; ++i )
    {
      if( client_fd[i] != 0 && client_fd[i] != ns )
       {
        if( write( client_fd[i], write_buf, sizeof( write_buf ) ) == -1 )
          {
            perror( "server: write failed" );
            exit( 1 );
          }
        }
    }
    pthread_mutex_unlock( &m );

    close( ns );
   
    pthread_mutex_lock(&np);
    numplayers--;    //decrement numplayers on exit
    pthread_mutex_unlock(&np);
    pthread_exit( 0 );

} // main end

 
int checkwinner ()  
{
  char winner='L';
  pthread_mutex_lock(&b);
 
  if (board[1]==board[3] && board[3]==board[5])     //row win
  {
    if(board[1]!=' ')
      winner=board[1];
  }

  else if (board[13]==board[15] && board[13]==board[17])
  {
    if(board[1]!=' ')
      winner=board[13];
  }
  else if (board[25]==board[27] && board[27]==board[29])
  {
    if(board[25]!=' ')
      winner=board[25];
  }
  else if (board[1]==board[13] && board[13]==board[25])  //column win
  {
    if(board[1]!=' ')
      winner=board[25];
  }
  else if (board[3]==board[15] && board[15]==board[27])
  {
    if(board[3]!=' ')
      winner=board[27];
  }
  else if (board[5]==board[17] && board[17]==board[29])
  {
    if(board[5]!=' ')
      winner=board[29];           
  }
  else if (board[1]==board[15] && board[17] == board[29])  //diagonal win
  {
    if(board[1]!=' ')
      winner=board[1];
  }

  else if (board[5]==board[15] && board[15]==board[25])
  {
    if(board[5]!=' ')
      winner=board[5];
  }
  
  pthread_mutex_unlock (&b);
  pthread_mutex_lock(&w);
  pthread_mutex_lock (&q);
  if (winner =='X')
  {
    wins2++;
    win=2;
    pthread_mutex_unlock(&q);
    pthread_mutex_unlock (&w);
    return 1;
  }
  if(winner=='O')
  {
    wins1++;
    win=1;
    pthread_mutex_unlock(&q);
    pthread_mutex_unlock (&w);
    return 1;
  }
  
  else win=-1;
  pthread_mutex_unlock(&q);
  pthread_mutex_unlock (&w);
  return 0;
}

void resetboard()    // Inializing the board to all blank spaces
{
    int i=0;
    pthread_mutex_lock(&b);
    board[0]='\n';    board[1]=' ';    board[2]='|';    board[3]=' ';    board[4]='|';    board[5]=' ';
    board[6]='\n';

    for(i=7; i<12; i++)
      {
	      board[i]='-';
      }
    board[12]='\n';     board[13]=' ';    board[14]='|';    board[15]=' ';    board[16]='|';   board[17]=' ';
    board[18]='\n';

    for(i=19; i<24; i++)
      {
      	board[i]='-';
      }

    board[24]='\n';    board[25]=' ';   board[26]='|';   board[27]=' ';   board[28]='|';   board[29]=' ';
    board[30]='\n'; board[31]='\0';

    pthread_mutex_unlock(&b);

    pthread_mutex_lock(&t);
    turn=0;
    pthread_mutex_unlock(&t);

    pthread_mutex_lock(&w);
    win=0;
    pthread_mutex_unlock(&w);
 }




 
    
  

 