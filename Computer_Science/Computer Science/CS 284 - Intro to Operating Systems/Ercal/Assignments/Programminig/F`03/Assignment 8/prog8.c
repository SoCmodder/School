/*********************************************************************
 * Programmers: Mark Schisler and Austin Hartman 
 * Assignment: 08
 * Class     : CS-284
 * Purpose   : To model some parts of a shell such as running commands
 *             and piping output between them
 *********************************************************************/

#define NO_SEP_COM 3
/* this is the total number of commands that can be put on each line */

#define bool unsigned char
#define true 1
#define false 0 
#define _GNU_SOURCE
#define SIZE_OF_PIPE 2

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<sys/wait.h>
#include<unistd.h>

int children[NO_SEP_COM]={0}; 
/* array that holds the PIDs for the children */
char partials[NO_SEP_COM][512] = {{'\0'}}; 
/* table that holds individual commands that haven't been separated into
   commands and arguments */
int ** pipe_array; 
/* a dynamically allocated array of pipes */

char *  Temp_Cmd_Name=NULL;
/* the command name for each child that is parsed from the partials table */
char ** Temp_Args=NULL;
/* the argument table for each child that is also parsed from the partials
   table */
int NoArgs=0; 
/* the number of arguments in the argument table */

/*****************************************************************************
 * Returns the string length from from ptr to the until ptr
 *****************************************************************************/
int strlento(const char * ptr, const char * until)
{
	int i = 0;
	while ( *(ptr + i) != '\0' && ((ptr + i) != until) )
	{
		i++;
	}
	return i;
}

/*****************************************************************************
 * This function modifies the global variables Temp_Cmd_Name and Temp_Args so 
 * they contain the command name and argument table that will be passed during
 * the execvp call.  It does this by parsing the strings contained in the 
 * partials table
 ** Pre: ChildNo must be a valid row in the partials table
 *  The partials table must be initialized so it only contains commands
 *  and arguments with one space in between them
 ** Post: Temp_Cmd_Name and Temp_Args have been modified so they contain the
 *  command name and arguments table
 *****************************************************************************/
void AllocExecvArgs(const int ChildNo)
{
	int len = 0, /* the length of the entry in the partials table */
	    no_args=1; /* the number of arguments currently parsed */
	char * last = &partials[ChildNo][0]; 
	/* points to the entry in the partials table we last looked at */
	char * SpaceLoc= NULL;
	/* the location of the next space after last */
	bool HitLast = false; 
	/* flag telling whether the last argument has been found */
	bool GrabbedCmd = false;
	/* flag telling whether we've parsed through the command name yet */

	while (!HitLast)
	{

		/* Grab Location of next space or NULL if not found */
		if ( (SpaceLoc=strpbrk(last," \n") ) == NULL)
			HitLast=true;

		/* Get Distance between last and SpaceLoc */
		len = strlento(last, SpaceLoc);

		/* Grab Command */
		if ( !GrabbedCmd )
		{
			GrabbedCmd = true;
			Temp_Cmd_Name = calloc(len+1,sizeof(char));
			strncpy(Temp_Cmd_Name, last, len);
			Temp_Cmd_Name[len] = '\0';
			printf("Command %d is \"%s",ChildNo+1,Temp_Cmd_Name);
		}

		no_args++;
		Temp_Args = realloc(Temp_Args, no_args * sizeof(char*)); 
		Temp_Args[no_args-2] = calloc(len+1,sizeof(char));
		strncpy(Temp_Args[no_args-2], last, len); 
		Temp_Args[no_args-2][len] = '\0';
		if(no_args != 2)
			printf(" %s",Temp_Args[no_args-2]);
		if(HitLast)
			printf("\"\n");
		Temp_Args[no_args-1] = NULL;

		/* If at the end of the array don't segfault */
		if (SpaceLoc != NULL)
			last=SpaceLoc + 1;

		/* If we have more than 2 spaces in a row, skip ahead */
		while (*last == ' ' && last != NULL)
		{
			last ++;
		}
	} 

	NoArgs=no_args-2; /*Account for Null and Command Name */
	return;
}

/*****************************************************************************
 * This function spawns the individual children and runs their commands.  It
 * also sets up the pipes that will be used to pass data between the children.
 ** Pre: NoChild is the number of children that will created.  partials must
 *  have this number of commands inside of it
 ** Post: The children have been created and their respective commands run
 *****************************************************************************/
void spawn_children(const int NoChild)
{
	bool bNotFail=true;
	/* flag telling whether a child failed forking */
	int i=0; /* loop iterators */
	int j;
	int oldstdin, oldstdout; 
	/* the original stdin and stdout file descriptors*/

	/* Create the pipe array */
	/* Need only NoChild - 1 pipes */
        if(NoChild > 1)
	{
		pipe_array = (int **)calloc(NoChild - 1, sizeof(int*));
		for(j = 0; j < NoChild - 1; j++)
		{
			pipe_array[j]=(int*) calloc(SIZE_OF_PIPE, sizeof(int));
			if(pipe(pipe_array[j]) != 0)
			{
				perror("Error creating pipe\n");
				exit(-1);
			}
		}
        }

	/* The ith child reads from pipe_array[i-1][0] and writes to
	   pipe_array[i][1] */
		
	/* Create copies of the stdin and stdout in case we need them later */
	oldstdin = dup(0);
	oldstdout = dup(1);

	do{
		children[i]=fork(); /*fork another child*/
		if (children[i] == 0)
		{
			/* Get the command name and argument variables array
			   this child will use */
			AllocExecvArgs(i);

			/* print a blank line between the commands and their
			   execution if this is the last child */
			if(i == NoChild - 1)
				printf("\n");

			/* if this is the first child */
			if (i == 0)
			{ 
				/* if there is more than one command, 
				   make stdout a copy of the write pipe */
				if ( NoChild > 1 )
				{ 					
					if (dup2(pipe_array[i][1], 1) == -1)
						perror("ERRORRRRR!!!!\n");
                                }
				/* otherwise, make stdout a copy of the old
				   stdout */
				else
				{
					if(dup2(oldstdout, 1) == -1)
						perror("ERRORRRRR!!!!\n");
				}
			}

			/* if this is one of children that will have input
			   piped to it */
			else
			{  
				/* make the child's stdin read from the pipe
				   written to by the previous child */
				if( dup2(pipe_array[i-1][0],0) == -1 )
					perror("ERRORRRRR!!!!\n");
                                               
                                /* if there is another command after this one,
				   make stdout a copy of the write pipe */
				if (i < NoChild - 1)
				{
					if (dup2(pipe_array[i][1], 1) == -1)
						perror("ERRORRRRR!!!!\n");
				}
				else
				{
					/* make stdout a copy of the old stdout 
					   if this is the last child */
					if(dup2(oldstdout, 1) == -1)
						perror("ERRORRRRR!!!!\n");
				}
			}

			/* Close all unneeded pipes and free them */
			for(j = 0; j < NoChild - 1; j++)
			{
				if(close(pipe_array[j][0]) == -1)
					perror("Error closing pipe\n");
				if(close(pipe_array[j][1])== -1)
					perror("Error closing pipe\n");
				free(pipe_array[j]);
			}
			free(pipe_array);
			if(close(oldstdout) == -1)
				perror("Error closing pipe\n");
			if(close(oldstdin) == -1)
                                perror("Error closing pipe\n");
                        
			/* run the actual command */
			execvp(Temp_Cmd_Name,Temp_Args);
			perror("Failure Executing Command\n");
			_exit(-1);
		}
		else if (children[i] < 0) /*Child did not fork properly */
		{
			bNotFail=false;
			perror("Fork Failure: Killing other processes forked.\n");
			for (i=0;i<NoChild;i++)
			{
				if (children[i]>0)
					kill(children[i],SIGKILL);
			}
			_exit(-1);
		}

		i++;
	}while (bNotFail && i<NoChild);


	/* Close all unneeded pipes for the parent */
	for(j = 0; j < NoChild - 1; j++)
	{
		if(close(pipe_array[j][0]) == -1)
			perror("Error closing pipe\n");
		if(close(pipe_array[j][1])== -1)
			perror("Error closing pipe\n");
	}

	/* restore the old stdin and stdout for the main program */
	dup2(oldstdin, 0);
	dup2(oldstdout, 1);
	close(oldstdin);
	close(oldstdout);

	return;
}


/*****************************************************************************
 * main() reads in the input from the user and executes the commands until
 * EOF (^D) is entered
 ** Pre: None
 ** Post: has run everything the user desires
 *****************************************************************************/
int main()
{
	char * command = NULL; /* the string entered in by the user */
	char * next_command = NULL; 
	/* points to a location inside command; used to parse the string */
	char * piped_cmd  = NULL;
	/* points to either a pipe or endline; tells where the current command
	   ends */
	size_t command_size;
	/* getline writes into this to tell how large the entered string was */
	int i = 0, j = 0, j2=0, k = 0; /* loop iterators */
	int ChildrenChk=0, /* number of children that have exited */
	    status=0, /* written into by waitpid */
	    NumChild = 0; 
	    /* the total number of children to create, i.e., the number 
	       of commands */
	    

	printf("<CHEAP-PROMPT (TM)>");
	getline(&command, &command_size, stdin); 
	while (!feof(stdin))
	{
		i=0;
		j=0;
		NumChild=0;
		next_command = command;

		/* Parse the commands for usage later */
		while ((piped_cmd=strpbrk(next_command,"|\n")) && i<NO_SEP_COM )
		{
			NumChild++;
			j=0;
			j2=0;

			/* Skip spaces before */
			while (next_command[j2] == ' ')
			{ 
				j2++;
			}

			/* Grep the command */ 
			while ( (size_t)j2 < strcspn(next_command, "|"))
			{
				partials[i][j] = next_command[j2];
				j++;
				j2++;
			}
			/* Destroy spaces after */
			while (partials[i][j-1] == ' ' || partials[i][j-1] == '\n')
			{ 
				j--;
			}

			partials[i][j] ='\0';

			/* In case input ended with a pipe (invalid) */
			if ( (piped_cmd=piped_cmd+1) != NULL)
			{
				next_command = piped_cmd;
				i++;
			}
		}

		/* create the children and run the individual commands */
		spawn_children(NumChild);

		/* wait for all the children to die */
		ChildrenChk=0;
		while (ChildrenChk<NumChild)
		{
			if(waitpid(-1,&status,0) == -1)
			{
				perror("Child exited improperly\n");
			}
			ChildrenChk++;
		}

		/* free the parent's copy of the pipes table */
		if(NumChild > 1)
		{
			for(k = 0; k < NumChild - 1; k++)
			{
				free(pipe_array[k]);
				pipe_array[k] = NULL;
			}
			free(pipe_array);
			pipe_array = NULL;
		}

		printf("\n<CHEAP-PROMPT (TM)>");
		getline(&command, &command_size, stdin); 
	}
	printf("\n");
	return 0; 
}



