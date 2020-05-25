#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

void *thread_function(void *arg);
void *thread_function1(void *arg);

pthread_mutex_t work_mutex; /* protects both work_area and time_to_exit */
#define WORK_SIZE 1024
char work_area[WORK_SIZE];
int time_to_exit = 0;
int main() {
	int res;
	int res1;
	pthread_t a_thread;
	pthread_t a_thread1;

	void *thread_result;
	res = pthread_mutex_init(&work_mutex, NULL);
	if (res != 0) {
		perror("Mutex initialization failed");
		exit(EXIT_FAILURE);
	}
	res = pthread_create(&a_thread, NULL, thread_function, NULL);
	if (res != 0) {
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}
	res1 = pthread_create(&a_thread1, NULL, thread_function1, NULL);
	if (res1 != 0) {
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}

	printf("\nWaiting for thread to finish...\n");
	res = pthread_join(a_thread, &thread_result);
	if (res != 0) {
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}
	printf("Thread joined\n");
	pthread_mutex_destroy(&work_mutex);
	exit(EXIT_SUCCESS);
}
void *thread_function(void *arg) {
	sleep(1);
	pthread_mutex_lock(&work_mutex);
	printf("here here\n");
	while(strncmp("end", work_area, 3) != 0) {
			printf("here here*****\n");
		printf("You input %ld characters\n", strlen(work_area) -1);
		work_area[0] = '\0';
		pthread_mutex_unlock(&work_mutex);
		sleep(1);
		pthread_mutex_lock(&work_mutex);
		while (work_area[0] == '\0' ) {
			pthread_mutex_unlock(&work_mutex);
			sleep(1);
			pthread_mutex_lock(&work_mutex);
		}
	}
	printf("here here before exit\n");
	time_to_exit = 1;
	work_area[0] = '\0';
	pthread_mutex_unlock(&work_mutex);
	pthread_exit(0);
}
void *thread_function1(void *arg) {
	pthread_mutex_lock(&work_mutex);
	while(!time_to_exit) {
		printf("Input some text. Enter ‘end’ to finish\n");
		fgets(work_area, WORK_SIZE, stdin);
		pthread_mutex_unlock(&work_mutex);
		while(1) {
			printf("in while condition\n");
			pthread_mutex_lock(&work_mutex);
			if (work_area[0] != '\0') {
				printf("in if condition\n");
				pthread_mutex_unlock(&work_mutex);
				sleep(1);
				printf("After sleep\n");
			}
			else {
				break;
			}
		}
	}
	pthread_mutex_unlock(&work_mutex);
}
