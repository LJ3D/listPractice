#include <iostream>
#include <chrono>
#include "list.hpp"


#define BENCHMARK_N 50000

int main(){
    list<int> lst;

    // ====== APPEND
    auto allStart = std::chrono::high_resolution_clock::now();
    auto appendStart = std::chrono::high_resolution_clock::now();
    std::cout << "Appending " << BENCHMARK_N << " elements..." << std::endl;
    for(int i=0; i<BENCHMARK_N; i++){
        lst.append(i);
    }
    auto appendEnd = std::chrono::high_resolution_clock::now();
    // ====== GET RANDOM
    auto getRandomStart = std::chrono::high_resolution_clock::now();
    std::cout << "Getting " << BENCHMARK_N << " elements at random positions and placing them in an array..." << std::endl;
    int* arr = new int[BENCHMARK_N];
    for(int i=0; i<BENCHMARK_N; i++){
        arr[i] = lst.get(rand()%lst.len());
    }
    delete arr;
    auto getRandomEnd = std::chrono::high_resolution_clock::now();
    // ====== GET SEQUENTIAL
    auto getSequentialStart = std::chrono::high_resolution_clock::now();
    std::cout << "Getting " << BENCHMARK_N << " elements at sequential positions and placing them in an array..." << std::endl;
    arr = new int[BENCHMARK_N];
    for(int i=0; i<BENCHMARK_N; i++){
        arr[i] = lst.get(i);
    }
    delete arr;
    auto getSequentialEnd = std::chrono::high_resolution_clock::now();
    // GET SEQUENTIAL BACKWARDS
    auto getSequentialBackwardsStart = std::chrono::high_resolution_clock::now();
    std::cout << "Getting " << BENCHMARK_N << " elements at sequential positions and placing them in an array..." << std::endl;
    arr = new int[BENCHMARK_N];
    for(int i=0; i<BENCHMARK_N; i++){
        arr[i] = lst.get(BENCHMARK_N-i-1);
    }
    delete arr;
    auto getSequentialBackwardsEnd = std::chrono::high_resolution_clock::now();
    // ====== REMOVE RANDOM
    auto removeStart = std::chrono::high_resolution_clock::now();
    std::cout << "Removing " << BENCHMARK_N << " elements at random positions..." << std::endl;
    while(lst.len()){
        int idx = rand()%lst.len();
        lst.remove(idx);
    }
    auto removeEnd = std::chrono::high_resolution_clock::now();
    // == Append but untimed, just for the next remove benchmark
    std::cout << "Appending " << BENCHMARK_N << " elements (but not timing, this is just for the next benchmark)..." << std::endl;
    for(int i=0; i<BENCHMARK_N; i++){
        lst.append(i);
    }
    // ====== REMOVE FRONT
    auto removeFrontStart = std::chrono::high_resolution_clock::now();
    std::cout << "Removing " << BENCHMARK_N << " elements at the front..." << std::endl;
    while(lst.len()){
        lst.remove(0);
    }
    auto removeFrontEnd = std::chrono::high_resolution_clock::now();
    // == Another append just for the next benchmark
    std::cout << "Appending " << BENCHMARK_N << " elements (but not timing, this is just for the next benchmark)..." << std::endl;
    for(int i=0; i<BENCHMARK_N; i++){
        lst.append(i);
    }
    // ====== REMOVE BACK
    auto removeBackStart = std::chrono::high_resolution_clock::now();
    std::cout << "Removing " << BENCHMARK_N << " elements at the back..." << std::endl;
    while(lst.len()){
        lst.remove(lst.len()-1);
    }
    auto removeBackEnd = std::chrono::high_resolution_clock::now();
    auto allEnd = std::chrono::high_resolution_clock::now();



    std::cout << "Benchmark results with a list of " << BENCHMARK_N << " elements:" << std::endl;
    std::cout << "Append: " << std::chrono::duration_cast<std::chrono::milliseconds>(appendEnd-appendStart).count() << "ms" << std::endl;
    std::cout << "Insert: " << "N/A" << std::endl;
    std::cout << "Get (sequential): " << std::chrono::duration_cast<std::chrono::milliseconds>(getSequentialEnd-getSequentialStart).count() << "ms" << std::endl;
    std::cout << "Get (sequential backwards): " << std::chrono::duration_cast<std::chrono::milliseconds>(getSequentialBackwardsEnd-getSequentialBackwardsStart).count() << "ms" << std::endl;
    std::cout << "Get (random positions): " << std::chrono::duration_cast<std::chrono::milliseconds>(getRandomEnd-getRandomStart).count() << "ms" << std::endl;
    std::cout << "Remove (random positions): " << std::chrono::duration_cast<std::chrono::milliseconds>(removeEnd-removeStart).count() << "ms" << std::endl;
    std::cout << "Remove (front): " << std::chrono::duration_cast<std::chrono::milliseconds>(removeFrontEnd-removeFrontStart).count() << "ms" << std::endl;
    std::cout << "Remove (back): " << std::chrono::duration_cast<std::chrono::milliseconds>(removeBackEnd-removeBackStart).count() << "ms" << std::endl;
    std::cout << "Total: " << std::chrono::duration_cast<std::chrono::milliseconds>(allEnd-allStart).count() << "ms" << std::endl;
    
    return 0;
}
