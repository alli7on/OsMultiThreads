/*
Part 3
Compare the time performance of the C-based linked list data structures shown in Figures 29.7 and 29.8 in the OSTEP textbook:

For each list, write:
missing list functions like

List_Remove to look for a particular item and remove it
List_Copy to make a copy of a list
thread functions that will
insert a number into a list
sum up (add) data in a list
make a copy of an existing list
remove specified items from a list
print out the contents of a list
a C main function that is capable of creating threads that can insert, copy, remove, and print lists
the main function should be able to:
insert a large number (e.g. a million to a billion) random integer values into a list
make a second copy of the finished list
sum up all the items in the list - use the gettimeofday() Linux system function to measure time needed to compute the sum - with
a single thread to add all the items in a list
2 threads working concurrently and cooperatively - each thread can work on a certain range of numbers - to add all the items in a list and return the sum
4 threads working concurrently to add all the items in a list and return the sum
use the copy of the original list to find and remove items from the first list


Use the valgrind program with helgrind as in Chapter 27 to test your multithreaded code for concurrency errors.
Show the timing data for computing the sums as a graph for 1, 2, and 4 threads for each list. The sums in each case should match!
Attach all the necessary C code so that your group members and the instructor can compile and run the programs to recreate the timing data.


In 250 words or more, explain:
how accurate the timing is: what is the smallest interval it can measure?
what valgrind/helgrind tells us about the correctness and performance of the multithreaded code
how you tested whether the two linked lists actually worked and what the timing data tells us about these two linked lists.
*/

//Figure29.7:ConcurrentLinkedList

//basicnodestructure
typedefstruct__node_t{
int key;
struct__node_t *next;
}node_t;

//basicliststructure(oneusedperlist)
typedefstruct__list_t{
node_t *head;
pthread_mutex_t lock;
}list_t;

voidList_Init(list_t *L){
L->head=NULL;
pthread_mutex_init(&L->lock,NULL);
}

intList_Insert(list_t *L,intkey){
pthread_mutex_lock(&L->lock);
node_t *new=malloc(sizeof(node_t));
if(new==NULL){
perror("malloc");
pthread_mutex_unlock(&L->lock);
return-1;//fail
}

new->key = key;
new->next= L->head;
L->head = new;
pthread_mutex_unlock(&L->lock);
return0;// success
}

intList_Lookup(list_t *L,intkey){
pthread_mutex_lock(&L->lock);
node_t *curr=L->head;
while(curr){
if(curr->key== key){
pthread_mutex_unlock(&L->lock);
return0;// success
}

curr=curr->next;
}

pthread_mutex_unlock(&L->lock);
return-1;//failure
}

//29.7's methods






//Figure 29.8: Concurrent Linked List: Rewritten

void List_Init(list_t *L) {
L->head = NULL;
pthread_mutex_init(&L->lock, NULL);
}

int List_Insert(list_t *L, int key) {
// synchronization not needed
node_t *new = malloc(sizeof(node_t));
if (new == NULL) {
perror("malloc");
return-1;
}

new->key = key;
// just lock critical section
pthread_mutex_lock(&L->lock);
new->next = L->head;
L->head = new;
pthread_mutex_unlock(&L->lock);
return 0; // success
}

int List_Lookup(list_t *L, int key) {
int rv =-1;
pthread_mutex_lock(&L->lock);
node_t *curr = L->head;
while (curr) {
if (curr->key == key) {
rv = 0;
break;
}

curr = curr->next;
}

pthread_mutex_unlock(&L->lock);
return rv; // now both success and failure
}

//29.8's methods

