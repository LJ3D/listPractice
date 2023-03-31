#include <iostream>
#include <chrono>
#include "list.hpp"

#define BENCHMARK_N 50000

int main(){
    list<int> lst;

    auto allStart = std::chrono::high_resolution_clock::now();

    auto appendStart = std::chrono::high_resolution_clock::now();
    for(int i=0; i<BENCHMARK_N; i++){
        lst.append(i);
    }
    auto appendEnd = std::chrono::high_resolution_clock::now();

    auto getStart = std::chrono::high_resolution_clock::now();
    int* arr = new int[BENCHMARK_N];
    for(int i=0; i<BENCHMARK_N; i++){
        arr[i] = lst.get(i);
    }
    delete arr;
    auto getEnd = std::chrono::high_resolution_clock::now();

    auto removeStart = std::chrono::high_resolution_clock::now();
    for(int i=0; i<BENCHMARK_N; i++){
        lst.remove(0);
    }
    auto removeEnd = std::chrono::high_resolution_clock::now();


    auto allEnd = std::chrono::high_resolution_clock::now();

    std::cout << "Benchmark results with a list of " << BENCHMARK_N << " elements:" << std::endl;
    std::cout << "Append: " << std::chrono::duration_cast<std::chrono::milliseconds>(appendEnd-appendStart).count() << "ms" << std::endl;
    std::cout << "Get: " << std::chrono::duration_cast<std::chrono::milliseconds>(getEnd-getStart).count() << "ms" << std::endl;
    std::cout << "Remove: " << std::chrono::duration_cast<std::chrono::milliseconds>(removeEnd-removeStart).count() << "ms" << std::endl;
    std::cout << "Total: " << std::chrono::duration_cast<std::chrono::milliseconds>(allEnd-allStart).count() << "ms" << std::endl;
    
    return 0;
}
