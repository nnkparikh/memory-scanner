/*
 * Student: Neel Parikh
 * Id: 1358644
 * Cmput 379 Assignment 1
 */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include "memchunk.h"
#include <setjmp.h>

static jmp_buf jmpbuffer;
struct memchunk info;   /*to store info of every chunk*/
int get_mem_layout(struct memchunk *chunk_list, int size)
{
    unsigned long maxAddress = 0xFFFFFFFF; /* 4GB memory addresss space */ 
    const int pagesize = getpagesize();
    
   
    int numOfChunk = 1;
    char *ptr_currentAddress = 0;
    unsigned int currentAddress = 0;
    int count = 0;      /*current position to update in chunk_list*/
    
    /* scan through the entire 4GB memory area */
    for(;;){
        
        /*declare custom signal handler*/
        if(signal(SIGSEGV, signal_handler) == SIG_ERR)
            perror("can't catch SIGSEGV\n");

        /* check accessibility of the pointer*/
        int RW = checkRW(ptr_currentAddress);
        if(currentAddress == 0){
            /*initalize the RW value of the first byte in mem */
            info.start = 0;
            info.RW = RW;
            info.length = pagesize;
        }
        else{
            /*accesiblity of this address same as previous adr*/
            if(info.RW == RW)
                info.length += pagesize;

            /* end of the chunk, start of new chunk */
            else{
                /*write to list*/
                if(count < size)
                    chunk_list[count] = info;
                numOfChunk++;   /* increment number of chunks */
                info.start = ptr_currentAddress; /* new starting address */
                info.length = pagesize;    /* reset counter */
                info.RW = RW;   /* set RW value of new chunk */
                count++;
      
            }
        }
        /* stop scanning when you reach the last page in memory */
        if(currentAddress == (maxAddress - (pagesize -1)))
            break;
        /*increment address pointer and its integer value by pagesize*/
        ptr_currentAddress += pagesize;
        currentAddress += pagesize;
      
    }
    /* write the last chunk to chunk list*/
    if(count < size)
        chunk_list[count] = info;
    
    return numOfChunk;
}

/* handle the the signal*/
void signal_handler(int signo){   
    siglongjmp(jmpbuffer,1);
}

int checkRW(char *ptr){
    int access = -1; /* assume not readable*/   
    if(!sigsetjmp(jmpbuffer,1)){
        /* read from memory */
        char r =   *ptr;
        access = 0; /* if read, set access to 0 */
        /* now try to write */
        *ptr = r; 
        access = 1; /* if write and read succesful, set access to 1*/
    }
   
    return access;
}


