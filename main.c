#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Figure29.7:ConcurrentLinkedList

//basicnodestructure
typedef struct__node_t{
int key;
struct__node_t *next;
}node_t;

//basicliststructure(oneusedperlist)
typedef struct__list_t{
node_t *head;
pthread_mutex_t lock;
}list_t;


void List_Init7(list_t *L){
L->head=NULL;
pthread_mutex_init(&L->lock,NULL);
}


int List_Insert7(list_t *L,intkey){
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


int List_Lookup7(list_t *L,intkey){
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
/*
List_Copy to make a copy of a list
thread functions that will
insert a number into a list
sum up (add) data in a list
make a copy of an existing list
remove specified items from a list
print out the contents of a list
*/

int List_Remove7(list_t *List,intkey){
pthread_mutex_lock(&L->lock);

node_t *previous = NULL;
node_t *current=L->head;

while(current){

if(current->key== key){
    if (previous != NULL){
        previous->next =current->next;
    } 
    else {
        List->head = current->next;
    }
    pthread_mutex_unlock(&L->lock);
    free(current);
    return0;// success
}
previous = current
current=current->next;
}
pthread_mutex_unlock(&L->lock);
return-1;//failure
}








//Figure 29.8: Concurrent Linked List: Rewritten

void List_Init8(list_t *L) {
L->head = NULL;
pthread_mutex_init(&L->lock, NULL);
}

int List_Insert8(list_t *L, int key) {
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

int List_Lookup8(list_t *L, int key) {
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
/*
List_Remove to look for a particular item and remove it
List_Copy to make a copy of a list
thread functions that will

insert a number into a list
sum up (add) data in a list
make a copy of an existing list
remove specified items from a list
print out the contents of a list
*/






// main section methods

/*
a C main function that is capable of creating threads that can insert, copy, remove, and print lists
the main function should be able to:
insert a large number (e.g. a million to a billion) random integer values into a list
make a second copy of the finished list
sum up all the items in the list - use the gettimeofday() Linux system function to measure time needed to compute the sum - with
a single thread to add all the items in a list
2 threads working concurrently and cooperatively - each thread can work on a certain range of numbers - to add all the items in a list and return the sum
4 threads working concurrently to add all the items in a list and return the sum
use the copy of the original list to find and remove items from the first list
*/
Node* list7 = NULL
List_Init7(&list7);
List_Insert7(&list7, 5);

List_Insert7(&list7, 9);
List_Insert7(&list7, 1);

print(List_Lookup7(&list7, 5));

List_Remove7(&list7, 5);
print(List_Lookup7(&list7, 5));