// Albert Chang
// Csc 33200 - S

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t key =	PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t smoker =	PTHREAD_MUTEX_INITIALIZER;

//Initiate conditions
pthread_cond_t agent_process =	PTHREAD_COND_INITIALIZER;
pthread_cond_t smoker_and_tobacco =	PTHREAD_COND_INITIALIZER;
pthread_cond_t smoker_and_match =	PTHREAD_COND_INITIALIZER;
pthread_cond_t smoker_and_paper =	PTHREAD_COND_INITIALIZER;

//Ingredient conditions
pthread_cond_t tobacco =	PTHREAD_COND_INITIALIZER;
pthread_cond_t match =	PTHREAD_COND_INITIALIZER;
pthread_cond_t paper =	PTHREAD_COND_INITIALIZER;

// Initiate processes
int tobacco_held = 0, match_held = 0, paper_held = 0;
int smoker_and_tobacco_job = 0, smoker_and_match_job = 0,
    smoker_and_paper_job = 0;

int agent_job = 1;

// Generates a random integer within a given range
int getRand(int range){
    int randNum = rand() % range;
    return randNum;
}

void *agent(void * arg){

    while(1){
        sleep(1);
        pthread_mutex_lock(&key);

        //The agent stays waiting if agent_job is equal 0
        while(agent_job == 0)
            pthread_cond_wait(&agent_process, &key);

        printf("________________________________________________________\n");

        // Generates a random integer between [0-2] inclusive
        int randNum = getRand(3);

        // Paper and Match (Random int returned is 0)
        if ( randNum == 0 ){
            agent_job = 0;
            match_held = 1;
            paper_held = 1;
            puts("\nPut paper and match:");
            pthread_cond_signal(&paper);
            pthread_cond_signal(&match);
        }

        // Tobacco and Match (Random int returned is 1)
        else if ( randNum == 1 ) {
            agent_job = 0;
            match_held = 1;
            tobacco_held = 1;
            puts("\nPut tobacco and match:");
            pthread_cond_signal(&paper);
            pthread_cond_signal(&match);
        }

        // Tobacco and Paper (Random int returned is 2)
        else if ( randNum == 2 ) {
            agent_job = 0;
            tobacco_held = 1;
            paper_held = 1;
            puts("\nPut paper and tobacco:");
            pthread_cond_signal(&paper);
            pthread_cond_signal(&tobacco);
        }

        pthread_mutex_unlock(&key);
    }
    
    return 0;
}

void *pusher_paper(void * arg){

    while(1){
        pthread_mutex_lock(&key);
        while(paper_held == 0)
            pthread_cond_wait(&paper, &key);

        if(match_held == 1) {
            match_held = 0;
            agent_job = 0;
            smoker_and_tobacco_job = 1;
            puts("Call: Tobacco Smoker");
            pthread_cond_signal(&smoker_and_tobacco);
        }

        if(tobacco_held == 1) {
            tobacco_held = 0;
            agent_job = 0;
            smoker_and_match_job = 1;
            puts("Call: Match Smoker");
            pthread_cond_signal(&smoker_and_match);
        }

        pthread_mutex_unlock(&key);
    }

    return 0 ;
}

void *pusher_match(void * arg){

    while(1) {
        pthread_mutex_lock(&key);
        while(match_held == 0)
            pthread_cond_wait(&match, &key);

        if(paper_held == 1) {
            paper_held = 0;
            agent_job = 0;
            smoker_and_tobacco_job = 1;
            puts("Call: Tobacco Smoker");
            pthread_cond_signal(&smoker_and_tobacco);
        }

        if(tobacco_held == 1) {
            tobacco_held = 0;
            agent_job = 0;
            smoker_and_paper_job = 1;
            puts("Call: Paper Smoker");
            pthread_cond_signal(&smoker_and_paper);
        }

        pthread_mutex_unlock(&key);
    }

    return 0 ;
}

void *pusher_tobacco(void * arg){

    while(1){
        pthread_mutex_lock(&key);
        while(tobacco_held == 0)
            pthread_cond_wait(&tobacco, &key);

        if(match_held == 1) {
            match_held = 0;
            agent_job = 0;
            smoker_and_paper_job = 1;
            puts("Call: Paper Smoker");
            pthread_cond_signal(&smoker_and_paper);
        }

        if(paper_held == 1) {
            tobacco_held = 0;
            agent_job = 0;
            smoker_and_match_job = 1;
            puts("Call: Match Smoker");
            pthread_cond_signal(&smoker_and_match);
        }

        pthread_mutex_unlock(&key);
    }

    return 0 ;
}

void *smoker_tobacco(void * arg){

    while(1){
        pthread_mutex_lock(&smoker);
        while(smoker_and_tobacco_job == 0)
            pthread_cond_wait(&smoker_and_tobacco, &smoker);

        paper_held = 0;
        match_held = 0;
        smoker_and_tobacco_job = 0;
        agent_job = 1;
        puts("Tobacco Smoker -> make cigarette...");
        pthread_mutex_unlock(&smoker);
        puts("Tobacco Smoker -> Smoking...");
    }

    return 0;
}

void *smoker_paper(void * arg){

    while(1){
        pthread_mutex_lock(&smoker);
        while(smoker_and_paper_job == 0)
            pthread_cond_wait(&smoker_and_paper, &smoker);

        tobacco_held = 0;
        match_held = 0;
        smoker_and_paper_job = 0;
        agent_job = 1;
        puts("Paper Smoker -> make cigarette...");
        pthread_mutex_unlock(&smoker);
        puts("Paper Smoker -> Smoking...");
    }

    return 0;
}

void *smoker_match(void * arg){

    while(1){
        pthread_mutex_lock(&smoker);
        while(smoker_and_match_job == 0)
            pthread_cond_wait(&smoker_and_match, &smoker);

        paper_held = 0;
        tobacco_held = 0;
        smoker_and_match_job = 0;
        agent_job = 1;
        puts("Match Smoker -> make cigarette...");
        pthread_mutex_unlock(&smoker);
        puts("Match Smoker -> Smoking...");
    }

    return 0;
}

int main(int argc, char *argv[]){

    pthread_t agent_t, smoker_tobacco_t, smoker_paper_t, smoker_match_t,
              pusher_tobacco_t, pusher_paper_t, pusher_match_t;

    time_t t;
    srand((unsigned) time(&t));

    if ((pthread_create(&agent_t,NULL,agent,NULL) != 0) ||
        (pthread_create(&pusher_tobacco_t,NULL,pusher_tobacco,NULL) != 0)
        || (pthread_create(&pusher_paper_t,NULL,pusher_paper,NULL) != 0)
        || (pthread_create(&pusher_match_t,NULL,pusher_match,NULL) != 0)
        || (pthread_create(&smoker_tobacco_t,NULL,smoker_tobacco,NULL) != 0)
        || (pthread_create(&smoker_paper_t,NULL,smoker_paper,NULL) != 0)
        || (pthread_create(&smoker_match_t,NULL,smoker_match,NULL) != 0)){

          fprintf (stderr, "Impossible to create thread\n");
          exit (1);
    }

    pthread_join(agent_t, NULL);
    pthread_join(pusher_tobacco_t, NULL);
    pthread_join(pusher_paper_t, NULL);
    pthread_join(pusher_match_t, NULL);
    pthread_join(smoker_tobacco_t, NULL);
    pthread_join(smoker_paper_t, NULL);
    pthread_join(smoker_match_t, NULL);
}
