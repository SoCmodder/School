/*****************************************************************************
**   CS284 Operating Systems
**   Programming Assignment #9
**   Program name: prog9s.c (server side)
**
**   This program demonstrates how to use socket for network programming.
**   Usage:
**     in solaris: cc prog9s.c -o prog9s -mt -lsocket -lnsl
**     then run prog9s.
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <thread.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>  /* define socket */
#include <netinet/in.h>  /* define internet socket */
#include <netdb.h>       /* define internet socket */
#include <string.h>

#define SERVER_PORT 9999        /* define a server port number */
#define MAX_CLIENT 10           /* maximum clients */

struct sockaddr_in server_addr = { AF_INET, htons( SERVER_PORT ) };
struct sigaction act;

int client_fd[MAX_CLIENT] = {0}; /* store FD for clients */
mutex_t m; /* mutex for accessing client_fd[] */

void* client_handler( void* ); /* client handler thread */
void sigint_handler();        /* sigint handler */

int main( int argc, char* argv[] )
{
    int sd, ns, i;
    struct sockaddr_in client_addr = { AF_INET };
    int client_len = sizeof( client_addr );
    char buf[512], *host;

    /* set SIGINT handler  */
    act.sa_handler = sigint_handler;
    sigemptyset( &(act.sa_mask) );
    sigaction( SIGINT, &act, NULL );
    host = (char*)getenv( "HOSTNAME=" );

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
	mutex_lock( &m );
	for( i = 0; i < MAX_CLIENT; ++i )
	{
	    if( client_fd[i] == 0 )
	    {
		client_fd[i] = ns;
		break;
	    }
	}
	mutex_unlock( &m );

        /* create a thread to handle the new client */
	thr_create( NULL, NULL, client_handler, &ns, THR_DETACHED, NULL );
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
    host = (char*)getenv( "HOSTNAME=" );
    strcpy( buf, "SERVER on " );
    strcat( buf, host );
    strcat( buf, ": Server is going to down in 10 seconds.\n" );
    printf( "%s\n", buf );

    mutex_lock( &m );
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
    mutex_unlock( &m );
    
    sleep(10);

    /*
     * sent ~quit to all clients
     */
    strcpy( buf, "~quit" );
    mutex_lock( &m );
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
    mutex_unlock( &m );

    unlink( server_addr.sin_addr );
    exit( 1 );
}

/*
 * client handler thread
 */
void* client_handler( void* arg )
{
    int i, nread;
    int ns = *(int*)arg;
    char read_buf[512], write_buf[512], client_name[30], *host;

    /* get the host name */
    host = (char*)getenv( "HOSTNAME=" );

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
     * send "welcome" to new client
     */
    strcpy( write_buf, "SERVER on " );
    strcat( write_buf, host );
    strcat( write_buf, ": Welcome " );
    strcat( write_buf, client_name );
    strcat( write_buf, "! type exit to leave." );
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
    mutex_lock( &m );
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
    mutex_unlock( &m );

    /*
     * read and write clients' chat
     */
    while( 1 )
    {
	nread = read( ns, read_buf, sizeof( read_buf ) );
	if( nread == -1 )
	{
	    perror( "server: read failed" );
	    exit( 1 );
	}
	printf( "%s: %s\n", client_name, read_buf );

/*	if( strlen( read_buf ) == 0 ) continue; */
	if( strlen( read_buf ) == 0 ) break;
	else if( strcmp( read_buf, "exit" ) != 0 )
	{
	    mutex_lock( &m );
	    for( i = 0; i < MAX_CLIENT; ++i )
	    {
		if( client_fd[i] != 0 && client_fd[i] != ns )
		{
		    strcpy( write_buf, client_name );
		    strcat( write_buf, ": " );
		    strcat( write_buf, read_buf );
		    if( write(client_fd[i], write_buf,
			      sizeof( write_buf ))== -1 )
		    {
			perror( "server: write failed" );
			exit( 1 );
		    }
		}
	    }
	    mutex_unlock( &m );
	}
	else
	{
	    write( ns, read_buf, sizeof( read_buf ) );
	    
	    mutex_lock( &m );
	    for( i = 0; i < MAX_CLIENT; ++i )
	    {
		if( client_fd[i] == ns )
		{
		    client_fd[i] = 0;
		    break;
		}
	    }
	    mutex_unlock( &m );
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
    mutex_lock( &m );
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
    mutex_unlock( &m );

    close( ns );
    thr_exit( 0 );
}
