#include "ParallelScheduler.hpp"
//"../lib/ParallelScheduler.hpp"
//"../lib/ParallelScheduler.cpp"
//
//solved race condition problem with mutex
//

//make mutex variable
pthread_mutex_t mutex;

//1000 times ++arg with treads
void* inc(void* arg) {
    //while loop 1000 times
    int cntr = 1000;
    while(cntr--) {
        //convert an argument from void*) to int*
        int* a = (int*)arg;
        //lock and test mutex variable
        int err = pthread_mutex_lock(&mutex);
        if(err != 0) {
            std::cout << "error " << err << " while locking mutex" << std::endl;
        }
        //increment argument
        ++(*a);
        //unlock mutex variable and test
        int error = pthread_mutex_unlock(&mutex);
        if(error != 0) {
            std::cout << "error " << error << " while unlocking mutex" << std::endl;
        }
    }
    return NULL;
}

void threadCreatingTest(int arg) {
    if(arg != 0) {
        std::cout << "error " << arg << " while creating a thread" << std::endl;
        exit(arg);
    }
}

int main() {
    int res = pthread_mutex_init(&mutex, NULL);
    if(res != 0) {
        std::cout << "error " << res << " while using a mutex" << std::endl;
        exit(res);
    }
    //pointer to int, and value is 0
    int* a = new int(0);
    std::cout << *a << std::endl;
    int threadsCount = 44;
    pthread_t* threads = new pthread_t[threadsCount];
    //create mutexes
    for(int i = 0; i < threadsCount; ++i) {
        int res = pthread_create(&threads[i], NULL, &inc, a);
        threadCreatingTest(res);
    }
    //join mutex
    for(int i = 0; i < threadsCount; ++i) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    std::cout << *a << std::endl;
    
    delete[] a;
    delete[] threads; 
}

/*
int main() {
    int res = pthread_mutex_init(&mutex, NULL);
    if(res != 0) {
        std::cout << "error " << res << " while using a pthread_mutex_init" << std::endl;
        exit(res);
    }   

    //pointer to int, and value is 0
    int* a = new int(0);
    std::cout << *a << std::endl;
    int threadsCount = 44;
    pthread_t* threads = new pthread_t[threadsCount];
    //create mutexes
    for(int i = 0; i < threadsCount; ++i) {
        int res = pthread_create(&threads[i], NULL, &inc, a);
        threadCreatingTest(res);
    }
    //join mutex
    for(int i = 0; i < threadsCount; ++i) {
        pthread_join(threads[i], NULL);
    }

    std::cout << *a << std::endl;

    pthread_mutex_destroy(&mutex);
    delete[] a;
    delete[] threads;
}
*/
