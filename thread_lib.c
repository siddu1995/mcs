#include "types.h"
#include "stat.h"
#include "user.h"
#include "x86.h"
#include "thread_lib.h"
struct lock_t *l=0;
void thread_create(void *(*start_routine)(void*), void *arg)
{
    int size = 4096; //since page size is 4096
    void *stack = malloc(size);
    if(clone(stack, size) == 0)
    {
        (*start_routine)(arg);
        exit();
    }
}

void thread_join()
{
    wait();
}
  		  
 struct lock_t* fetch_and_store(struct lock_t **i) {
 struct lock_t *temp = l;
     l = *i;
    *i = temp;
    return temp;
}

 int compare_and_swap(struct lock_t **i) {
      if(l!= (*i)) return 0;
      l = 0;
      return 1;
  }
  		  
 void lock_acquire(struct lock_t *i)
 {
 i->next = 0;
 struct lock_t *pred = fetch_and_store(&i);
   if(pred != 0) {
         i->locked = 1;
         pred->next = i;
         while(i->locked == 1);
    }
  }		
  		  
void lock_release(struct lock_t *i)
{
      if(i->next == 0) {
         if(compare_and_swap(&i) == 1) return;
         while(i->next == 0);
     }
     i->next->locked = 0;
  }
