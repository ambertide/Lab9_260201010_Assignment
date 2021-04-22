#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_STRING_SIZE 100


typedef struct string {
	char original[MAX_STRING_SIZE];
	char reverse[MAX_STRING_SIZE];
} structure;


void reverse_str(structure *str) {
	int size_ = strlen(str->original);
	for (int i = 0; i < size_; i++) {
		str->reverse[i] = str->original[size_ - i - 1];
	}
	str->reverse[size_] = '\0';
}

void *reverse(void *string_struct) {
	structure *str = (structure*) string_struct;
	reverse_str(str);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	pthread_t thread_ids[argc - 1];
	structure *structs[argc - 1];
	for (int i = 0; i < argc - 1; i++) {
		structs[i] = (structure *) malloc(sizeof(structure)); 
		strcpy(structs[i]->original, argv[i + 1]);
		pthread_create(&thread_ids[i], NULL, reverse, structs[i]);
		printf("Created new thread with ID: %ld\n", thread_ids[i]);
	}
	for (int i = 0; i< argc - 1; i++) {
		pthread_join(thread_ids[i], NULL); // Wait for thread termination.
		printf("\nThread ID: %ld\nOriginal String: %s\nReversed String: %s\n",
				thread_ids[i], structs[i]->original, structs[i]->reverse);
		free(structs[i]);
	}
	printf("\nFinish!\n");
}


