#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>



// Both linked list structures use the same structs
// How the stuff provided works is a bit beyond me. It just do, Idk.
// The only real difference I'm picking up on is the second locks less.
//Figure29.7:ConcurrentLinkedList

//basicnodestructure
typedef struct __node_t {
    int key;
    struct __node_t *next;
} node_t;

//basicliststructure(oneusedperlist)
typedef struct __list_t {
    node_t *head;
    pthread_mutex_t lock;
} list_t;


void List_Init(list_t *L){
L->head=NULL;
pthread_mutex_init(&L->lock,NULL);
}


int List_Insert(list_t *L,int key){
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
return 0;// success
}


int List_Lookup(list_t *L,int key){
pthread_mutex_lock(&L->lock);
node_t *curr=L->head;
while(curr){
if(curr->key== key){
pthread_mutex_unlock(&L->lock);
return 0;// success
}
curr=curr->next;

}
pthread_mutex_unlock(&L->lock);
return-1;//failure
}


//Figure 29.8: Concurrent Linked List: Rewritten

void List_Init2(list_t *L) {
L->head = NULL;
pthread_mutex_init(&L->lock, NULL);
}

int List_Insert2(list_t *L, int key) {
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

int List_Lookup2(list_t *L, int key) {
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


//list methods
//These methods are shared between the two different structures.
/*

thread functions that will
sum up (add) data in a list

*/

// Finds a value in the list and axes the thing.
int List_Remove(list_t *L,int key){
pthread_mutex_lock(&L->lock);

node_t *previous = NULL;
node_t *current=L->head;

while(current){

if(current->key== key){
    if (previous != NULL){
        previous->next =current->next;
    } 
    else {
        L->head = current->next;
    }
    free(current);
    pthread_mutex_unlock(&L->lock);
    return 0;// success
}
previous = current;
current=current->next;
}
pthread_mutex_unlock(&L->lock);
return-1;//failure
}

// Prints all the values in the structur in the format 1 -> 2 -> 3.
void List_Print(list_t *L){
    pthread_mutex_lock(&L->lock);
    node_t *current=L->head;
    while(current != NULL){
        printf("%d", current->key);

            if(current->next != NULL){
                printf(" -> ");
            }
        current=current->next;
    }
    printf("\n");
pthread_mutex_unlock(&L->lock);
}


// Give list to copy from and copy to. They must be initialized by hand with the method.
void List_Copy(list_t *from, list_t *to){
    pthread_mutex_lock(&L->lock);

    node_t *current = to->head;
    node_t *tail = NULL;

    while(current != NULL){
        node_t *new = malloc(sizeof(node_t));
        if(new == NULL){
         break;
        }
        new->key = current->key;
        new->next = NULL;

        if(tail == NULL){
            to->head = new;
            tail = new;
        } else {
            tail->next = new;
            tail = new;
        }
        current = current->next;
    }
pthread_mutex_unlock(&L->lock);
}


// main section methods
// Calls insert the number of times requested putting random ints in. Also give it the list to insert to. 
// For the test we are timing how long it takes to sum the values. This makes no sense. The structure is only different with reguards to lookup and insertion. 
// There will be no difference unless I delibratly have them use different suming methods. Because suming involves no insertion and lookup. The lists are identical
// and I'm not gonna sum differently. This question is pointless?

int insertmany (list_t *L ,int many){
    for (int i = 0; i < many - 1; i++){
        int code = List_Insert(list_t *L, (rand() % 100));
            if(code != 0){
                printf("Many insert Fail")
            }
    }
}




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

int main(void){
node_t* test = NULL;   
List_Init1(&test);
List_Insert(&test, 5)
List_Insert(&test, 50)
List_Insert(&test, 500)
List_Print(&test)

node_t* list = NULL;    
node_t* copy = NULL;

List_Init1(&list);
List_Init2(&copy);

insertmany(&list, 10)
List_Print(&list)
List_Copy(&list, &copy)
List_Print(&copy)

}