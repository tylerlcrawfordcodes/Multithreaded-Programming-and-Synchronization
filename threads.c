#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_THREADS 500
#define PTHREAD_SYNC

#ifdef PTHREAD_SYNC
pthread_mutex_t mutex;
pthread_barrier_t mybarrier;
#endif

int SharedVariable = 0;//variable to be modified by all threads


/* Method that forks a few threads each executing the loop. After all the threads modified the shared variable SharedVariable, Thread number along with SharedVariable will be displayed for each forked thread as well as the final value seen.
 */
void *SimpleThread(void *which)
{
	int num, val, tid, *p;
	p = which;

    for(num = 0; num < 20; num++)
	{
		if (random() > RAND_MAX / 2)
		usleep(500);

		#ifdef PTHREAD_SYNC
		pthread_mutex_lock(&mutex); //lock mutex to ensure only one thread can modify sharedVariable at a time
		#endif

		val = SharedVariable;
		printf("*** thread %d sees value %d\n", *p, val);
		SharedVariable = val + 1;

		#ifdef PTHREAD_SYNC
		pthread_mutex_unlock(&mutex); //unlock mutex to when finished modifying
		#endif
	}


	#ifdef PTHREAD_SYNC
	pthread_barrier_wait(&mybarrier); //wait for all threads to finish modifying sharedVariable
	#endif

	val = SharedVariable;
	printf("Thread %d sees final value %d\n", *p, val);
	pthread_exit(0);
}



void main(int argc, char* argv[])
{
	int numThreads = atoi(argv[1]); //Command line argument taken in
	pthread_t *tids;

	#ifdef PTHREAD_SYNC
	pthread_mutex_init(&mutex, NULL); // initialise a pthread mutex
	pthread_barrier_init(&mybarrier, NULL, numThreads); // allocates resources required to use barrier
	#endif

    //Validates command line parameter making sure that only numbers can be accepted.
	if(numThreads > 0 && numThreads <= MAX_THREADS)
	{
		tids = (pthread_t*)malloc(sizeof(pthread_t)*atoi(argv[1])); //Dynamically allocate integer array with thread number (command-line argument)
		int *j = (int*)malloc(sizeof(int)*numThreads);

		//Gives threads ID and creates threads
		for(int i = 0; i < numThreads; i++)
		{
			j[i] = i;
			pthread_create(&tids[i], NULL, SimpleThread, &j[i]);
		}

		//Waits for all threads to finish
		for(int i = 0; i < numThreads; i++)
		{
			pthread_join(tids[i], NULL);
		}
	}
	else
	{
		perror("Please input a reasonable number of threads in the command line");
		exit(1);
	}

	#ifdef PTHREAD_SYNC
	int pthread_mutex_destroy (pthread_mutex_t* mutex); //destroys a mutex
	pthread_barrier_destroy(&mybarrier); // destroys barrier referenced
	#endif

}
