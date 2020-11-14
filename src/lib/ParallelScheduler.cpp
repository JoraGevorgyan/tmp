#include "ParallelScheduler.hpp"

//"../program/main.cpp"

//extern pthread_mutex_t mutex;

void printTest() {
    std::cout << "test workes\n";
}
/*
void threadCreatingTest(int arg) {
    if(arg != 0) {
        std::cout << "error " << arg << " while creating a thread" << std::endl;
        exit(arg);
    }
}

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
*/
