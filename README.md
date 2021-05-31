# Multithreaded-Programming-and-Synchronization
Description
This assignment utilizes the thread subsystem of Linux to use the Pthreads library that forks a few threads, printing out the modified shared variable within and after the loop, Called "Simple Multi-Thread Programming without Synchronization". Secondly, this assignment synchronizes the multi-threaded program using Pthreads mutex variables.
Usage
Makefile does not need to be altered. Program name is threads.c
After compiling to run the code: command line includes *name of file* and *Number of Threads*. For Step 1 of the assignment, COMMENT OUT "#define PTHREAD_SYNC" and for step 2, COMMENT IN "#define PTHREAD_SYNC" as this will allow for the synchronization.
