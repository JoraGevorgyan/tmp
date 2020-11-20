//use this file only once when linking
#pragma once

#include <iostream>
#include <queue>
#include <vector>
#include <pthread.h>

class ParallelScheduler {
    private:
        pthread_mutex_t queueLock;
        pthread_cond_t condvar;
        std::vector< pthread_t > threads;
        std::queue< std::pair< void(*)(void*), void*> > functions;
    public:
        ParallelScheduler(size_t threadsCount);
        ~ParallelScheduler();
        void run(void(*start_rouTine)(void*), void* arg);
    private:
        void createJoinThreads();
        void* executeFunctions(void* arg);
        static void* executeFunctionsWrapper(void* arg);
};
