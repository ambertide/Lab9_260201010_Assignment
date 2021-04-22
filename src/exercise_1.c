#include <pthread.h>
#include <stdio.h> // For printf.


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex variable for accessing balance.
int balance = 1000;


void *deposit_money(void *balance_ptr) {
	int *balance = (int*) balance_ptr;
	for (int i = 0; i < 500; i++) {
		pthread_mutex_lock(&mutex);
		*balance += 10;
		pthread_mutex_unlock(&mutex);
	}
	printf("Deposited money. Balance: %d\n", *balance);
	pthread_exit(NULL);
}

void *withdraw_money(void *balance_ptr) {
	int *balance = (int*) balance_ptr;
	for (int i = 0; i < 200; i++) {
		pthread_mutex_lock(&mutex);
		*balance -= 5;
		pthread_mutex_unlock(&mutex);
	}
	printf("Withdrawn money. Balance: %d\n", *balance);
	pthread_exit(NULL);
}

int main() {
	pthread_t deposit_thread_id, withdraw_thread_id;
	pthread_create(&deposit_thread_id, NULL, deposit_money, &balance);
	pthread_create(&withdraw_thread_id, NULL, withdraw_money, &balance);
	pthread_join(deposit_thread_id, NULL) && pthread_join(withdraw_thread_id, NULL); // Wait for threads to complete execution.
	printf("Threads executed. Balance: %d\n", balance);
	return 0;
}
