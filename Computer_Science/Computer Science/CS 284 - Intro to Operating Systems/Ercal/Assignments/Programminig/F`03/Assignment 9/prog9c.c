/*****************************************************************************
**   CS284 Operating Systems
**   Programming Assignment #9
**   Program name: prog9c.c (client side)
**
**   This program demonstrates how to use socket for network programming.
**   Usage:
**     in solaris: cc prog9c.c -o prog9c -mt -lsocket -lnsl
**     then run: prog9c hostname nickname
*****************************************************************************/

#include <stdio.h>
#include <thread.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>  /* define socket */
#include <netinet/in.h>  /* define internet socket */
#include <netdb.h>       /* define internet socket */
#include <string.h>

#define SERVER_PORT 9999     /* define a server port number */

struct sockaddr_in server_addr = { AF_INET, htons( SERVER_PORT ) };

void* echo_handler( void* ); /* client handler thread */

int main( int argc, char* argv[] )
{
    int sd, nread, i;
    char buf[512], temp[512];
    struct hostent *hp;

    /* chech if the command line argument number is valid */
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
    thr_create( NULL, NULL, echo_handler, &sd, 0, NULL );

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

    /* join the client thread */
    thr_join( NULL, NULL, NULL );

    close( sd );
    return( 0 );
}

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

    thr_exit( 0 );
}
