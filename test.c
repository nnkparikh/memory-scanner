#include "memchunk.h"
#include <stdio.h>

/*
 * Student: Neel Parikh
 * Id: 1358644
 * Cmput 379 Assignment 1
 */


/* test get_mem_layout function */
int main(){
    struct memchunk chunkList[20];
    int chunkCount = get_mem_layout(chunkList,20);
    printf("\n\nNumber of chunks: %d\n\n", chunkCount);
    int i;
    unsigned long long totalsum = 0;
    for(i = 0; i<chunkCount; i++)
    {   printf("Chunk number %d\n",i+1);
        printf("The start address of chunk: %p\n",chunkList[i].start);
        printf("The length of this chunk is: %lu\n", chunkList[i].length);
        totalsum += chunkList[i].length;
        printf("accesibility: %d\n", chunkList[i].RW);
        printf("\n");   
    }
    printf("Total length: %llu bytes \n", totalsum);
    return 0; 
}
