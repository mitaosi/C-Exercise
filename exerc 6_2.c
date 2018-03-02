/* ====================================

File name: Exerc_6_2.c 

Date: 2018-03-01

Group Number:  #7

Members of students contributed:

Qing Lin

Qiu Shengzhi

Demonstration code: 
====================================== */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define num_elems 200
int array[200];
int max_value;

void *runner(void *param) {
	printf("Enter max value\n");
	scanf("%d", &max_value);

	int c = 0, n=0;

	for (c = 0; c < num_elems; c++) {
		for(n=0; n<1000; n++); // To delay a bit 
		array[c] = rand() % max_value;
	}
	printf("This is the thread for filling the array.\n");
	pthread_exit(NULL);
}

void *thread1(){
	int c, d, swap;

	for (c = 0; c < num_elems; c++) {
		for (d = 0; d < num_elems - c - 1; d++) {
			if (array[d] > array[d + 1]) {
				swap = array[d];
				array[d] = array[d + 1];
				array[d + 1] = swap;
			}
		}
	}
	//the function that prints the array is in the search function, so this line will print first.
	printf("This is the thread for sorting array.\n");  
	pthread_exit(NULL);
}

void *thread2(){
	int search;
	printf("Enter value to find\n");
	scanf("%d", &search);

	int first = 0;
	int last = num_elems - 1;
	int middle = (first + last) / 2;
	int n;
	for(n=0; n<num_elems; n++){
	    printf("\n %d", array[n]);
	}

	while (first <= last) {
		if (array[middle] < search)
			first = middle + 1;
		else if (array[middle] == search) {
			printf("\n%d found at location %d.\n", search, middle + 1);
			break;
		} else
			last = middle - 1;

		middle = (first + last) / 2;
	}
	if (first > last)
		printf("\nNot found! %d is not present in the list.\n", search);

	printf("This is the thread for finding the wanted value.\n");

	pthread_exit(NULL);
}

int main() {
	time_t t;
	pthread_t tid, tic, tie;
	pthread_attr_t attr;
	
	srand((unsigned) time(&t));
	pthread_attr_init(&attr);

	// create each thread and pause them
	pthread_create(&tid, &attr, runner, NULL);
	pthread_join(tid, NULL);
	
	pthread_create(&tic, &attr, thread1, NULL);
	pthread_join(tic, NULL);

	pthread_create(&tie, &attr, thread2, NULL);
	pthread_join(tie, NULL);
}