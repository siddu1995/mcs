struct lock_t
 {
int locked;
struct lock_t * next;
 };



/*
 struct lock_t {
int locked;
struct lock_t *next;
};

 typedef struct mcs_node{
       mcs_node next;
       int is_locked;
};
 
typedef struct mcs_lock{
        mcs_node queue;
};

*/

