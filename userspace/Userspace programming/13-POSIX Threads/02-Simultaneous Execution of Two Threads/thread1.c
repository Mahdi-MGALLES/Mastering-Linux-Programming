#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void *thread_function(void *arg);
char message[] = "Hello World";
int run_now = 1;
int main() {
	int res;
	pthread_t a_thread;
	void *thread_result;
	int print_count1 = 0;

	res = pthread_create(&a_thread, NULL, thread_function, NULL);
	if (res != 0) {
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}
	while(print_count1++ < 20) {
		if (run_now == 1) {
			printf("1");
			run_now = 2;
		}
		else {
			sleep(1);
		}
	}
	res = pthread_join(a_thread, &thread_result);
	if (res != 0) {
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}
	printf("Thread joined, it returned %s\n", (char *)thread_result);
	exit(EXIT_SUCCESS);
}
void *thread_function(void *arg) {
	int print_count2 = 0;
	while(print_count2++ < 20) {
		if (run_now == 2) {
			printf("2");
			run_now = 1;
		}
		else {
			sleep(1);
		}
	}
	pthread_exit("Thank you for the CPU time");
}
