/*
 * Program 7: Banker's Algorithm
 * Author: Brian Sea
 * Date: 10/26/03
 *
 * Descripton:
 *
 * This program is meant to demonstrate the Banker's Algorithm.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Define our types for the types of instructions
 */
#define INSTRUCT_TYPE_REQUEST 1
#define INSTRUCT_TYPE_RELEASE 2
#define INSTRUCT_TYPE_END     3

/*
 * Struct for each instuction
 *
 * Type         - One of request, release or end
 * Resource     - the resource used
 * ResourceAmt  - the amount of the resource used
 */
typedef struct Instruction
{
    int Type;
    int Resource;
    int ResourceAmt;
} Instruct_t;

/*
 * Our process
 *
 * ProcessID    - the ID of the process
 * Allocated    - the resources used by this process
 * Instructs    - the instructions this process uses
 * numInstructs - the number of instructions for this process
 * curInsturct  - the current instruction that the process is on
 */
typedef struct Process
{
    int ProcessID;
    int *Allocated;
    Instruct_t *Instructs;
    int numInstructs;
    int curInstruct;
} process_t;

/*
 * Our Queue
 *
 * Processess - Pointers to the processes in the Queue
 * numProcess - the number of processes in this Queue
 */
typedef struct SimpleQueue
{
    process_t **Processes;
    int numProcess;
} Q_t;

/* Prototype our functions */

/*
 * Queue Functions
 * PopFront - Pop the first node off Q's front
 * PushBack - Push Process onto Q's back
 */
process_t *PopFront( Q_t *Q);
void PushBack( Q_t *Q, process_t *Process );

/*
 * Functions for dynamic allocation and freeing of file-scope variables
 */
void InitFileScopes( int numProcess, int numResource );
void FreeFileScopes( int numProcess, int numResource );

/*
 * Grab the instructions from the File input for the number of processes
 * indicated by numProcess
 */
void GrabInstructions( FILE *input, int numProcess );

/*
 * For the Start of the Banker's Algorithm
 *
 * isSafe() - decides if is safe to execute instruction Instruct
 */
void BankersAlgorithm();
int isSafe( Instruct_t *Instruct );


/* Define Matrices and Vectors */
int **ClaimMatrix;
int *ResourceVector;
int numProcesses;
int numResources;

/*  Our actual processes - we point to these. */
process_t *Processes;

/* Define Queues */
Q_t BlockedQ, ReadyQ;

/* Only one process can run at a time */
process_t *Running;

#define FILENAME "Input.dat"

int main()
{
    int i,j;
    int numProcess;
    int numResources;
    FILE *input;

    /* Try to open our file */
    input = fopen( FILENAME, "r" );

    if( !input )
    {
        fprintf( stderr, "Could not open file \"%s\"\n", FILENAME );
        exit( -1 );
    }

    /* Get the number of Processes and Resources */
    fscanf( input, " %d %d ", &numProcess, &numResources );

    /* Allocate our File-scopes now that we have some information */
    InitFileScopes( numProcess, numResources );
    
    /* Populate the Resource Vector */
    for( i = 0; i < numResources; i++ )
    {
        fscanf( input, "  %d ", &ResourceVector[i] );
    }

    /* Populate the Claim Matrix */
    for( i = 0; i < numProcess; i++ )
    {
        for( j = 0; j < numResources; j++ )
        {
            fscanf( input, " %d ", &ClaimMatrix[i][j] );
        }
    }

    /* Grab Instructions */
    GrabInstructions( input, numProcess );

    /* 
     * Done with the File 
     * All processes should be ready and in the Ready Q
     */
    fclose( input );

    /* Go Banker Go!!!! */
    BankersAlgorithm();
    
    /* Clean up after ourselves! */
    FreeFileScopes( numProcess, numResources );
}

/*
 * Get the front of the Q.  This also removes it from the Q */
process_t* PopFront( Q_t *Q )
{
    int i;

    /* Remeber the first Node in the Q */
    process_t *Rtn = Q->Processes[0];

    /* Move everything forward */
    for( i = 1; i < Q->numProcess; i++ )
    {
        Q->Processes[i-1] = Q->Processes[i];
    }

    Q->numProcess--;

    return Rtn;
}

/* Add Process to the back of the Q */
void PushBack( Q_t *Q, process_t *Process )
{
    Q->Processes[ Q->numProcess ] = Process;
    Q->numProcess++;
}

/*
 * Is is safe to execute instruction instruct?
 * The allocation requested MUST be done prior to this function being called.
 * 
 * Returns 0 - Not safe - You MUST reverse the requested allocation!
 * Returns >0 - safe - no need to reverse allocation.
 */
int isSafe( Instruct_t *instruct )
{
    int i,j, k,l;
    int checkPIDs[ numProcesses ];
    int Resource = 0;
    int ResAmt = instruct->ResourceAmt;
    int CurAvail[numResources];
    int Flag;
    int found;
   
    /* Move to the new state */
    Running->Allocated[ instruct->Resource ] += 
                    instruct->ResourceAmt;

    ResourceVector[instruct->Resource] -=
                    instruct->ResourceAmt;

    /* Check all processes */
    for( i = 0; i < numProcesses; i++ )
    {
        checkPIDs[i] = Processes[i].ProcessID;
    }

    /* Initialize Available Vector */
    for( k = 0; k < numResources;k++ )
    {
        CurAvail[k] = ResourceVector[k];
    }

    Flag = 0;
    /*
     * For each Process we check to see if that Process can run to completion.
     * If it can we then add its Allocated Resources to the Available amount,
     * and check the remainging processes.
     *
     * We continue to do this until we find out that there isn't a safe path
     * through ALL the processes.
     */
    for( i = 0; i < numProcesses; i++ )
    {
        if( checkPIDs[i] != -1 )
        {
       
            /* Can we run to completion? */
            for( j = 0; j < numResources; j++ )
            {
                if( ClaimMatrix[i][j] - 
                    Processes[i].Allocated[j]
                        > CurAvail[j] )
                {
                    break;
                }
            }

            if( j == numResources )
            {
                /*  
                 *  Well, since we got here we know that the resource can be
                 *  allocated successfully.  Add those resources to the
                 *  available amount, so that the next process can use them.
                 */


                for(  l = 0;  l < numResources; l++ )
                {
                    CurAvail[l] += Processes[i].Allocated[l];
                }

                
                /* 
                 * We completed the loop successfully. We now know that the
                 * process can run to completion.  Mark it as such.  We then
                 * restart our counter, so we run through all the unchecked
                 * processes again to see if they can complete now that we
                 * have resources.
                 *
                 * We increment Flag to show that one more process can
                 * complete its processing in the current state.
                 */
            
                checkPIDs[i] = -1;
                i = -1;
                Flag++;
                                
            }
        }
    }

    /*  
     *  If Flag doesn't equal the number of Processes then there was at least
     *  one process that couldn't complete in our state - it's unsafe to be
     *  here.  We take back our resources allocated for the new state.
     */
    if( Flag != numProcesses )
    {
        Running->Allocated[ instruct->Resource ] -= 
                    instruct->ResourceAmt;
        ResourceVector[instruct->Resource] +=
                    instruct->ResourceAmt;
    }
    
    printf("START:\n" );
    for( i = 0; i < numProcesses; i++ )
    {
    for ( l = 0; l < numResources; l++ )
    {
        printf("%d ", Processes[i].Allocated[l] );
    }
    printf("\n");
    }
    printf("\n");

    /* If Flag equals the number of processes than we're in a safe state */
    return (Flag==numProcesses);
}

void BankersAlgorithm()
{
    Instruct_t *curInstruct;
    int i, j;
    int Flag;

    /* Get the first process to run */
    Running = PopFront( &ReadyQ );
    while(1)
    {
        /* Get the current instruction from the running process */
        curInstruct = &Running->Instructs[ Running->curInstruct ];
        switch( curInstruct->Type )
        {
            /* It's a REQUEST */
            case INSTRUCT_TYPE_REQUEST:
                printf("Job %d: REQUEST %d %d ----> ", Running->ProcessID,
                        curInstruct->Resource+1, curInstruct->ResourceAmt );
                
                /* If there aren't enough resources available - block */
                if( ResourceVector[curInstruct->Resource] <
                        curInstruct->ResourceAmt )
                {
                    printf("Not Granted; Blocked\n");
                    PushBack( &BlockedQ, Running );
                    Running = PopFront( &ReadyQ );
                    break;
                }
                
                /* 
                 * If we enter a safe state due to the request, then we
                 * increment the current instruction counter and send the
                 * process to the back of the Ready Q.
                 */
                if( isSafe( curInstruct ) )
                {
                    printf( "Granted\n" );
                    Running->curInstruct++;
                    PushBack( &ReadyQ, Running );
                }
                else
                {
                   
                    /* 
                     * It got Blocked - process to the back of the Blocked Q
                     */
                    printf("Not Granted; Blocked\n" );
                    PushBack( &BlockedQ, Running );
                }
                    
                /* Get the the next process */
                Running = PopFront( &ReadyQ );
                break;

                /* It's a Realease */
            case INSTRUCT_TYPE_RELEASE:

                /* 
                 * This check is here because we simulate a RELEASE of 0 when
                 * one of the processes ends
                 */
                if( curInstruct->ResourceAmt != 0 )
                {
                    printf("Job %d: RELEASE %d %d ----> ", Running->ProcessID,
                        curInstruct->Resource+1, curInstruct->ResourceAmt );
                }
                
                /* State is always safe.. give the resource back */
                Running->Allocated[ curInstruct->Resource ] -=
                    curInstruct->ResourceAmt;

                ResourceVector[curInstruct->Resource] +=
                    curInstruct->ResourceAmt;

                /*  Instruction counter increments */
                Running->curInstruct++;

                /* 
                 * This check is to verify that we aren't simulating an ENDJOB
                 * instruction.
                 */
                if( Running->curInstruct < Running->numInstructs )
                {
                    PushBack( &ReadyQ, Running );
                }
                
                if( BlockedQ.numProcess > 0 )
                {
                    /* 
                     * Go through the Blocked Q.  If there is one or more
                     * processes that can be unblocked - then do it!
                     */
                    Flag = 0;
                    for( i = 0; i < BlockedQ.numProcess; i++ )
                    {
                        Running = BlockedQ.Processes[i];
                        curInstruct = &Running->Instructs[Running->curInstruct];

                        if( ResourceVector[curInstruct->Resource] <
                                            curInstruct->ResourceAmt )
                        {
                            printf("\n\tUNBLOCK: Cannot unblock Process"
                                   " %d.", BlockedQ.Processes[i]->ProcessID );

                            continue;
                        }


                        if( isSafe( curInstruct ) )
                        {
                            
                            BlockedQ.Processes[i]->curInstruct++;

                            printf("\n\tUNBLOCK: Process %d given %d units "
                                    "of %d", BlockedQ.Processes[i]->ProcessID,
                                    curInstruct->ResourceAmt, 
                                    curInstruct->Resource+1 );
                       
                            /* 
                             * Cycle through the BlockedQueue and move the
                             * process we wish to unblock to the Ready Q
                             */
                            for( j = 0; j < i; j++ )
                            {
                                PushBack( &BlockedQ, PopFront(&BlockedQ) );
                            }
                            
                            /* 
                             * Flag equals 1 so we know we unblocked someone
                             * i equals -1, so that we restart through the
                             * Queue
                             */
                            PushBack( &ReadyQ, PopFront(&BlockedQ) );
                            Flag = 1;
                            i--;
                        }
                        else
                        {
                            printf("\n\tUNBLOCK: Cannot unblock Process"
                                    " %d.", BlockedQ.Processes[i]->ProcessID );
                        }
                    }

                    if( !Flag )
                    {
                        printf("\n\tUNBLOCK: Can't unblock a process\n");
                    }
                    else
                    {
                        printf("\n");
                    }
                }
                else
                {
                    printf("Nothing in Blocked Queue\n" );
                }

                Running = PopFront( &ReadyQ );

                break;

                /* It's an ENDJOB */
            case INSTRUCT_TYPE_END:

                /* Free all resources in this process */
                printf("Job %d: End ---> ", Running->ProcessID );
                for( i = 0; i < numResources; i++ )
                {
                    ResourceVector[i] += Running->Allocated[i];
                    Running->Allocated[i] = 0;
                }

                /* Simulate a RELEASE with an amount of 0 */

                curInstruct->Type = INSTRUCT_TYPE_RELEASE;
                curInstruct->Resource = 0;
                curInstruct->ResourceAmt = 0;
                Running->ProcessID = 0;

                break;

            default:

                if( ReadyQ.numProcess <= 0 )
                {
                    printf( "No more processes.  Exiting\n" );
                    return;
                }

                fprintf(stderr, "Invalid Instruction Type: %d\n",
                        curInstruct->Type );
        }
    }
}

/* Initialize the File-SCOPE variables */
void InitFileScopes( int numProcess, int numResource )
{
    int i, j;
    
    /* Allocation and Claim Matrix */
    ClaimMatrix = (int **)calloc( numProcess, sizeof(int*) );
    ResourceVector = (int *)calloc( numResource, sizeof( int ) );
    Processes = (process_t *)calloc( numProcess, sizeof(process_t) );
    numProcesses = numProcess;
    numResources = numResource;

    for( i = 0; i < numProcess; i++ )
    {
        ClaimMatrix[i] = (int *)calloc( numResource, sizeof(int) );
        Processes[i].Allocated = (int*)calloc( numResource, sizeof(int) );
        Processes[i].Instructs = (Instruct_t *)malloc( sizeof(Instruct_t) );
        Processes[i].curInstruct = 0;
        Processes[i].numInstructs = 0;
        for( j = 0; j < numResource; j++ )
        {
            Processes[i].Allocated[j] = 0;
        }
    }

    /* Init Queues */
    BlockedQ.numProcess = 0;
    ReadyQ.numProcess = 0;

    BlockedQ.Processes = 
        (process_t **)calloc( numProcess, sizeof(process_t*) );
    ReadyQ.Processes = 
        (process_t **)calloc( numProcess, sizeof(process_t*) );
    Running = NULL;
}

/* Free them up... someone has to do it */
void FreeFileScopes( int numProcess, int numResource )
{
    int i;
    free( ClaimMatrix );
    
    for( i = 0; i < numProcess; i++ )
    {
        free( Processes[i].Allocated );
    }
    
    free( Processes );
    free( BlockedQ.Processes );
    free( ReadyQ.Processes );
}

/* This grabs the instructions and populates the process table */
void GrabInstructions( FILE *input, int numProcess )
{
    int i, j;
    char Buffer[256];

    for( i = 0; i < numProcess; i++ )
    {
        /* Header */
        fscanf( input, " %256s ", Buffer );
        fscanf( input, " %d ", &Processes[i].ProcessID );

        j = 1;
        while(1)
        {
            /* resize the instruction queue */
            Processes[i].Instructs = 
                (Instruct_t *)realloc( Processes[i].Instructs, 
                                       sizeof( Instruct_t ) * j ); 
            fscanf( input, " %256s ", Buffer);

            /* It's a request */
            if( !strcmp( Buffer, "REQUEST" ) )
            {
                Processes[i].Instructs[j-1].Type = INSTRUCT_TYPE_REQUEST;
            }
            else
            {
                /* It's a release */
                if( !strcmp( Buffer, "RELEASE" ) )
                {
                    Processes[i].Instructs[j-1].Type = INSTRUCT_TYPE_RELEASE;
                }
                else
                {
                    /* No more instructions */
                    if( !strcmp( Buffer, "ENDJOB" ) )
                    {
                        Processes[i].numInstructs = j;
                        Processes[i].Instructs[j-1].Type = INSTRUCT_TYPE_END;

                        /* Add the process to the Ready Q */
                        PushBack( &ReadyQ, &Processes[i] );
                        break;
                    }
                }
            }

            /* Grab the Resource type and Resource Amount */
            fscanf( input, " %d ", &Processes[i].Instructs[j-1].Resource );
            Processes[i].Instructs[j-1].Resource--;
            fscanf( input, " %d ", &Processes[i].Instructs[j-1].ResourceAmt );

            j++;
        }
    }
}
