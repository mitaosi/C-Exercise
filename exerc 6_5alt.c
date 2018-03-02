// Skeleton for exercise nr 6 in WP 6 course DIT165.
// File skeleton_wp6_6.c  
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  not_empty   = PTHREAD_COND_INITIALIZER;
pthread_cond_t  not_full   = PTHREAD_COND_INITIALIZER;

// Global buffer and corresponding counters.
char  letter = 'a'; //the starting letter
#define MAX 10//buffer size
#define THREADS 2//threads count
#define STIME (1000 * 10)
unsigned short count = 0;
char buffer[MAX]; // circular buffer
int write_pos = 0; // index for next character to be put in buffer (put)
int read_pos = 0; // index for next character to be read ( fetch )

void *put();
void *fetch();

int main(){

    int i;
    pthread_t threads[THREADS];
    //create thread for producer
    pthread_create(&threads[0], NULL, put, NULL);
    //create thread for consumer
    pthread_create(&threads[1], NULL, fetch, NULL);

    //for main function to loop prints out the textstring 
    while(1){
        //main loop textstring prints out
        printf("Main is executing\n");
        //sleep 1 ms for a clear view about output
        usleep(STIME);
    }
    //wait threads to exit while it is meanless due to this function will always in loop
    for (i = 0; i < THREADS; i++){
        //join the thread to release the source
        pthread_join(threads[i], NULL);
    }
    return 0;
}


void *put(){
    //initial the input character
    char c = 'a';
    while(1){
        pthread_mutex_lock(&count_mutex);
        //If buffer full (MAX number of characters in buffer) the thread should wait for a
        //cond_signal ¡®not full¡¯ from the other consuming thread telling that buffer is not full.
        while (count == MAX){
            pthread_cond_wait(&not_full, &count_mutex);
        }
        //if buffer not full, write the character
        buffer[write_pos] = c;
        //prints out infomation for producer
        printf("Buffer store\n");

        //increase wirte pos
        write_pos++;
        //for the  circular buffer 
        write_pos %= MAX;
        //increase the buffer used size
        count++;

        //create next input character in a infinitive loop
        c++;
        if (c > 'z'){
            c = 'a';
        }
        //sleep 1 ms for a clear view about output
        usleep(STIME);
        pthread_mutex_unlock(&count_mutex);
        //For every character stored it should call a cond_signal telling other threads that
        //buffer not empty.
        pthread_cond_signal(&not_empty);
    }
   
}


void *fetch(){
    while(1){
        pthread_mutex_lock(&count_mutex);
        //If no character in buffer it should wait for a cond_signal ¡®not_empty'
        // from the producer thread that signal every time it stores a new character in buffer
        while (count == 0){
            pthread_cond_wait(&not_empty, &count_mutex);
        }

        //prints out infomation for comsumer
        printf("Buffer output : %c\n", buffer[read_pos]);
        //increase wirte pos for the  circular buffer 
        read_pos++;
        read_pos %= MAX;
        //descrease the buffer used size
        count--;

        //sleep 1 ms for a clear view about output
        usleep(STIME);
        pthread_mutex_unlock(&count_mutex);
        //For every character fetch from buffer, it should call a cond_signal telling other threads that
        //buffer not full.
        pthread_cond_signal(&not_full);
    }

}
