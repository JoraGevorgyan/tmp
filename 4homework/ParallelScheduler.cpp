#include "ParallelScheduler.hpp"

ParallelScheduler::ParallelScheduler(size_t threadsCount = 4)
    :queueLock(PTHREAD_MUTEX_INITIALIZER)
     ,condvar(PTHREAD_COND_INITIALIZER)
     ,threads(threadsCount)
{
    std::cout << "from constructor \n";
    createJoinThreads();
    std::cout << "from c-r after f-n\n";
}

ParallelScheduler::~ParallelScheduler() {
    for(pthread_t& thread : threads) {
        pthread_cancel(thread);
    }
}

void ParallelScheduler::run(void(*start_rouTine)(void*), void* arg) {
    pthread_mutex_lock(&queueLock);
    functions.push(std::pair< void(*)(void*), void* >(start_rouTine, arg));
    pthread_mutex_unlock(&queueLock);
    pthread_cond_signal(&condvar);
}

void* ParallelScheduler::executeFunctions(void* arg) {
    std::cout << "from exec... \n";
    pthread_mutex_lock(&queueLock);
    while(true) {
        std::cout << "while ... \n";
        pthread_cond_wait(&condvar, &queueLock);
        std::cout << "while ... \n";
        void(*start_rouTine)(void*) = functions.front().first;
        void* arg = functions.front().second;
        functions.pop();
        start_rouTine(arg);
    }
    pthread_mutex_unlock(&queueLock);
    return NULL;
}

void* ParallelScheduler::executeFunctionsWrapper(void* arg) {
    reinterpret_cast<ParallelScheduler*>(arg)->executeFunctions(NULL);
    return NULL;
}

void ParallelScheduler::createJoinThreads() {
    for(pthread_t& thread : threads) {
        int err = pthread_create(&thread, NULL,  &executeFunctionsWrapper, this);
        if(err != 0) {
            std::cout << "pthread_create returns an error "
                << err
                << " number!" << std::endl;
            exit(err);
        }
        err = pthread_join(thread, NULL);
        if(err != 0) {
            std::cout << "pthread_join retunrs an error "
                << err
                << " number!" << std::endl;
            exit(err);
        }
    }
}






















