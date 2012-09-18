/****************************************************************************
** CS284 Operating Systems
** Programming Assignment #7
** Program Name: prog7a.c
** Author: Chang Qian, Joe Wingbermuehle, Matt Walters
** Date: october 28, 2002
**
** This program is to create child processes and pipes between 
** children and parent to transfer information
** compilation: cc -o prog7a.out prog7a.c 
** execute prog7a.out
*****************************************************************************/
#include <stdio.h>       /* for fdopen() */
#include <stdlib.h>
#include <unistd.h>      /* for pipe() */
#include <sys/types.h>
#include <sys/wait.h>    /* for waitpid() */

int main(int argc, char *argv[])
{
  FILE *fin, *fout;
  char token[512];
  pid_t child[3]; /* child process ids */
  int p1[2], p2[2], p3[2], p4[2]; /* pipe descriptors */
  /* p1 for parent and child1 */
  /* p2 for child1 and child2 */
  /* p3 for child2 and child3 */
  /* p4 for child3 and parent */
  
  /* create pipes used by child1 */
  if (pipe(p1) == -1)
  { perror("pipe1 creation failed");
    exit(1);
  }
  if (pipe(p2) == -1)
  { perror("pipe2 creation failed");
    exit(1);
  }
  
  /* create the child1 process below */
  if ( (child[0]=fork()) == 0 )
  {  /* in the child1 process */
    if ( dup2(p1[0],0)==-1 )
    { perror("dup2 failed");
      exit(1);
    } /* make child1's stdin a duplicate of p1 read end */
    
    if ( dup2(p2[1],1)==-1)
    { perror("dup2 failed");
      exit(1);
    } /* make child1's stdout a dup of p2 write end */
    
    close(p1[0]);
    close(p1[1]);
    close(p2[0]);
    close(p2[1]); 
    /* close all the pipes in child1 expect for std ones */
    
    /* jump to prog7b.out with argument of "CHILD1" */
    execl("./prog7b.out", "prog7b.out", "CHILD1",0);
    perror("child1 executes prog7b.out fails\n");
    exit(1);
  }
  else if(child[0] < 0)
  { perror("child1 creation failed");
    _exit(1);
  }
  
  /* back to parent, now parent has p1 and p2 */
  /* now set up p3 for child2's use */
  if( pipe(p3)== -1)
  { perror("p3 creation failed");
    exit(1);
  }
  /* creat the child2 below */
  if( (child[1]=fork())==0 )
  {  /* inside the child2 */
    if( dup2(p2[0],0) == -1 )
    { perror("dup2 failed");
      exit(1);
    }/* make child2's stdin dup of p2's read end */
    if( dup2(p3[1],1)== -1)
    { perror("dup2 failed");
      exit(1);
    }/* make child2's stdout dup of p3 write end */
    
    close(p1[0]);
    close(p1[1]);
    close(p2[0]);
    close(p2[1]); 
    close(p3[0]);
    close(p3[1]); /* close all pipes in child2 except 
                   for its mapped std ones */
    execl("./prog7b.out","prog7b.out","CHILD2",0);
    perror("child2 execl prog7b.out failed");
    _exit(1);
  }
  else if (child[1]<0)
  { perror("child2 creation failed");
    _exit(1);
  }
  
  /* back to parent, now it has p1, p2, p3 */
  if( pipe(p4)==-1)
  { perror(" p4 creation failed ");
    exit(1);
  } /* create p4 for the use of child3 */
  
  /* create child3 below */
  if ( (child[2]=fork()) == 0 )
  {  
    if ( dup2(p3[0],0) == -1 )
    { perror("dup2 failed");
      exit(1);
    } /* makes child3's stdin dup of p3's read end */
    if ( dup2(p4[1],1) == -1 )
    { perror("dup2 failed");
      exit(1);
    } /* makes child3's stdout dup of p4's write end */
    
    /* close all pipes except for child3's std ones */
    close(p1[0]);
    close(p1[1]);
    close(p2[0]);
    close(p2[1]); 
    close(p3[0]);
    close(p3[1]);
    close(p4[0]);
    close(p4[1]);
    
    /*execute the prog7b.out */
    execl("./prog7b.out","prog7b.out","CHILD3",0);
    perror("child3 executes prog7b.out failed");
    exit(1);
  }  
  else if( child[2]<0 )
      { perror("child3 creation failed");
        _exit(1);
      }
      
  /* back to parent */
    close(p1[0]);
  /* close(p1[1]); leave p1 write end */
    close(p2[0]);
    close(p2[1]); 
    close(p3[0]);
    close(p3[1]);
  /* close(p4[0]); leave p4 read end */
    close(p4[1]);
    
  /* use fdopen to associate a write stream to
    the write end of p1 */
  if ( (fout = fdopen(p1[1],"w"))==0 )
  {  perror("fdopen failed");
     exit(1);
  }
  /* use fdopen to associate a read stream to 
     the read end of p4 */
  if ( (fin = fdopen(p4[0],"r"))==0 )
  {   perror( "fdopen failed ");
      exit(1);
  } 
  
  printf("input a string: ");
  while( scanf("%s",token) != EOF )
  { fprintf(fout,"%s-PARENT\n",token); /* write into p1 */
    fflush( fout );
    fscanf(fin,"%s",token); /* read from p4 */
    printf("%s\n",token);
  }
  close(p1[1]);
  close(p4[0]);
  
  waitpid(child[0],0,0);
  waitpid(child[1],0,0);
  waitpid(child[2],0,0);
  
  return(0);
  
}
  
    
    
  
    
     
