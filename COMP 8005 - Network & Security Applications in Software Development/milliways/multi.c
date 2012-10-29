/*--------- Multi-threaded "Hello World"-------*/

#include <pthread.h>
#include <stdio.h>
/*#include <pthread/mit/pthread.h>*/

#define _REENTRANT
#define DCE_COMPAT

/*----------- Function Prototypes ------------------*/
void* outputMsg (void*);

/*------------ Mutex Variables ---------------------*/
pthread_mutex_t printfLock = PTHREAD_MUTEX_INITIALIZER;


int main (void)
{
  pthread_t thread1, thread2;
  const char* msg1 = "Hello ";
  const char* msg2 = "World ";

  pthread_create (&thread1, NULL, outputMsg, (void*)msg1);
  pthread_create (&thread2, NULL, outputMsg, (void*)msg2);

  pthread_join (thread1, NULL);
  pthread_join (thread2, NULL);

  printf ("\n");
  return 0;
}

/*----------  Output Message Function -------------*/
void* outputMsg (void* msg)
{
  int i;

  for (i = 0; i < 10; ++i)
  {
    pthread_mutex_lock (&printfLock);
    printf ((char*)msg);
    pthread_mutex_unlock (&printfLock);
  }
  return NULL;
}


