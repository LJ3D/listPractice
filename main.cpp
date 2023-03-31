#include <iostream>
#include <chrono>
#include "list.hpp"

#define BENCHMARK_N 50000

int main(){
    list<int> lst;

    // ====== APPEND ======
    auto allStart = std::chrono::high_resolution_clock::now();
    auto appendStart = std::chrono::high_resolution_clock::now();
    std::cout << "Appending " << BENCHMARK_N << " elements..." << std::endl;
    for(int i=0; i<BENCHMARK_N; i++){
        lst.append(i);
    }
    auto appendEnd = std::chrono::high_resolution_clock::now();
    // ====== GET ======
    auto getStart = std::chrono::high_resolution_clock::now();
    std::cout << "Getting " << BENCHMARK_N << " elements and placing them into an array..." << std::endl;
    int* arr = new int[BENCHMARK_N];
    for(int i=0; i<BENCHMARK_N; i++){
        arr[i] = lst.get(i);
    }
    delete arr;
    auto getEnd = std::chrono::high_resolution_clock::now();
    // ====== REMOVE ======
    auto removeStart = std::chrono::high_resolution_clock::now();
    std::cout << "Removing " << BENCHMARK_N << " elements (with worst case scenario (removing last element))..." << std::endl;
    while(lst.len()){
        lst.remove(lst.len()-1);
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
