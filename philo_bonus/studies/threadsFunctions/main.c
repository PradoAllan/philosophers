#include <pthread.h>
#include <stdio.h>
#include <unistd.h> // for sleep

// This function will be executed by the detached thread
void* print_in_background(void* arg)
{
	(void)arg;
	printf("This is printed from the thread.\n");
	sleep(5);
	return NULL;
}

int main() {
	pthread_t thread_id;

    // Create a new thread
	if (pthread_create(&thread_id, NULL, print_in_background, NULL) != 0)
	{
		perror("Failed to create thread");
        	return 1;
	}

    // 🚨 toggle these 2 🚨
    	pthread_detach(thread_id);
	//pthread_join(thread_id, NULL);

    // Continue with the main thread's work
	printf("This is printed from the main thread.\n");
	usleep(100000);

	return 0;
}
