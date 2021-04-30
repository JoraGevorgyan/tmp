#include "ParallelScheduler.hpp"

void foo(void* arg) {
    std::cout << "\nfoo called\n";
    int* a = (int*)arg;
    std::cout << *a << ' ';
}

template<typename T>
void print(const T& x){
     std::cout << x << std::endl;

}

int main() {
    print("begin");
    ParallelScheduler scheduler(14);
    print("end");
    for(int i = 1; i < 21; ++i) {
        print("\nin for loop, from main");
        scheduler.run(foo, &i);
    }
    std::cout << std::endl;
}
