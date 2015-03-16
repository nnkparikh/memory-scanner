
#ifndef _MEMCHUNKH_
#define _MEMCHUNKH_
/* chunk information */
struct memchunk {
    void *start;
    unsigned long length;
    int RW;
};

/* handle segmentation fault */
void signal_handler(int signo);

/* returns number of chunks in process memory */
int get_mem_layout(struct memchunk *chunk_list, int size);

/* given an addresss, checks its accesibility*/
int checkRW(char *ptr);



#endif
