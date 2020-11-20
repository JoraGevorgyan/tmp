#include "ParallelScheduler.hpp"

void foo(void* arg) {
    std::cout << "\nfoo called\n";
    int* a = (int*)arg;
    std::cout << *a << ' ';
}

int main() {
    std::cout << "begin\n";
    ParallelScheduler scheduler(14);
    std::cout << "end\n";
    for(int i = 1; i < 21; ++i) {
        std::cout << "\nin for loop, from main\n";
        scheduler.run(foo, &i);
    }
    std::cout << std::endl;
}
