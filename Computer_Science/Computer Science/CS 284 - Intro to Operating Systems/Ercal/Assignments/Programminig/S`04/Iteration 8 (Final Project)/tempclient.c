/*****************************************************************************
**   CS284 Operating Systems
**   Programming Assignment #8
**   Programers: Robert Graham, Pat Keeven
**   Program name: tempclient.c (client side)
**
**   This program demonstrates how to use socket for network Tic-Tac-Toe.
**   Usage:
**     in linux: gcc tempclient.c -o client -lpthread -lnsl
**     then run: client <hostname> <nickname>
**   Version: 1.0
*****************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>  /* define socket */
#include <netinet/in.h>  /* define internet socket */
#include <netdb.h>       /* define internet socket */
#include <string.h>

#define SERVER_PORT 9999     /* define a server port number */


struct sockaddr_in server_addr = { AF_INET, SERVER_PORT };


// Function Description: client handler thread
// Pre-condition: None
// Post-condition:  Echo the message from server
void* echo_handler( void* ); /* client handler thread */



int main( int argc, char* argv[] )
{
    int sd, nread;
    char buf[512];
    struct hostent *hp;
    pthread_t thread;

    /* check if the command line argument number is valid */
    if( argc != 3 )
    {
      printf( "Usage: %s hostname nickname\n", argv[0] );
      exit( 1 );
    }

    /* get the host */
    if( ( hp = gethostbyname( argv[1] ) ) == NULL )
    {
      printf( "%s: %s unknown host\n", argv[0], argv[1] );
      exit( 1 );
    }
    bcopy( hp->h_addr_list[0], (char*)&server_addr.sin_addr, hp->h_length );

    /* create a socket */
    if( ( sd = socket( AF_INET, SOCK_STREAM, 0 ) ) == -1 )
    {
      perror( "client: socket failed" );
      exit( 1 );
    }

    /* connect a socket */
    if( connect( sd, (struct sockaddr*)&server_addr,
    sizeof(server_addr) ) == -1 )
    {
      perror( "client: connect failed" );
      exit( 1 );
    }

    /* write the nickname */
    write( sd, argv[2], 30 );

    /* read welcome message */
    nread = read( sd, buf, sizeof( buf ) );
    if( nread == -1 )
    {
      perror( "client: read failed" );
      exit ( 1 );
    }
    printf( "%s\n", buf );

    /* create a client handler thread */
    pthread_create( &thread, NULL, &echo_handler, &sd );

    /* read the client input and write it to server */
    while( 1 )
    {

      gets( buf );
      if( write( sd, buf, sizeof( buf ) ) == -1 )
      {
        perror( "client: write failed" );
        exit( 1 );
      }
      if( strcmp( buf, "exit" ) == 0 ) break;
    }

    close( sd );

 /* join the client thread */
    pthread_join( thread, NULL );

   
    return( 0 );
}  // End main



/*
 * client thread to echo the message from server
 */
void* echo_handler( void* arg )
{
    int nread;
    int sd = *(int*)arg;
    char buf[512];

    /* read the message from the server */
    while( 1 )
    {
      nread = read( sd, buf, sizeof( buf ) );
      if( nread == -1 )
      {
        perror( "client: read failed" );
        break;
      }

      if( strcmp( buf, "exit" ) == 0 )
      {
        break;
      }
      else if( strcmp( buf, "~quit" ) == 0 )
      {
        printf( "exit: server down\n" );
        exit( 1 );
      }
      else
      {
        printf( "%s\n", buf );
      }
    }

    pthread_exit( 0 );
}
