#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define THREAD_NUM 2

pthread_mutex_t mutexBuffer;
sem_t semEmpty;
sem_t semFull;

int buffer[1];
int count=0;

void* producer(void* args){
    for(int i=0;i<10;i++){
        //Produce step
        int x = rand() % 100;
        sleep(0.5);
        
        //Add to buffer
        sem_wait(&semEmpty);
        pthread_mutex_lock(&mutexBuffer);
        if(count < 10){
        buffer[count] = x;
        count++;
        }else{
            printf("Skipped %d\n", x);
        }
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semFull);
    }
}

void* consumer(void* args){
    while(1){
        int y = -1;
        //Remove from buffer

        sem_wait(&semFull);
        pthread_mutex_lock(&mutexBuffer);
        //Don't need the if statement
        if(count > 0){
            y = buffer[count - 1];
            count--;
        }
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semEmpty);

        //Consuming
        printf("Got %d\n", y);
        sleep(0.5);
    }
}


int main(int argc, char* argv[]){

    srand(time(NULL));
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutexBuffer, NULL);
    sem_init(&semEmpty, 0, 10);
    sem_init(&semFull, 0, 0);    
    int i;

    for (i=0; i<THREAD_NUM; i++){
        if (i % 2==0){
            if(pthread_create(&th[i], NULL, &producer, NULL) != 0){
                perror("Failed to create thread");
            }
        }else {
             if(pthread_create(&th[i], NULL, &consumer, NULL) != 0){
                perror("Failed to create thread");
            }
        }

    }
    for(i=0; i<THREAD_NUM; i++) {
        if(pthread_join(th[i], NULL)!=0){
            perror("Failed to join thread");
        }
    }
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    pthread_mutex_destroy(&mutexBuffer);
    return 0;
}
