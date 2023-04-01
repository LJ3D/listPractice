#include <iostream>
#include <chrono>
#include "list.hpp"

#define BENCHMARK_N 50000

int main(){
    namespace cr = std::chrono;

    srand(time(NULL));
    LJLIST::list<int> lst;



    // ====== APPEND
    auto allStart = cr::high_resolution_clock::now();
    auto appendStart = cr::high_resolution_clock::now();
    std::cout << "Appending " << BENCHMARK_N << " elements..." << std::endl;
    for(int i=0; i<BENCHMARK_N; i++){
        lst.append(i);
    }
    auto appendEnd = cr::high_resolution_clock::now();
    // ====== GET RANDOM
    auto getRandomStart = cr::high_resolution_clock::now();
    std::cout << "Getting " << BENCHMARK_N << " elements at random positions and placing them in an array..." << std::endl;
    int* arr = new int[BENCHMARK_N];
    for(int i=0; i<BENCHMARK_N; i++){
        int idx = rand()%lst.len();
        arr[i] = lst.get(idx);
    }
    delete arr;
    auto getRandomEnd = cr::high_resolution_clock::now();
    // ====== GET SEQUENTIAL
    auto getSequentialStart = cr::high_resolution_clock::now();
    std::cout << "Getting " << BENCHMARK_N << " elements at sequential positions and placing them in an array..." << std::endl;
    arr = new int[BENCHMARK_N];
    for(int i=0; i<BENCHMARK_N; i++){
        arr[i] = lst.get(i);
    }
    delete arr;
    auto getSequentialEnd = cr::high_resolution_clock::now();
    // GET SEQUENTIAL BACKWARDS
    auto getSequentialBackwardsStart = cr::high_resolution_clock::now();
    std::cout << "Getting " << BENCHMARK_N << " elements at sequential positions backwards and placing them in an array..." << std::endl;
    arr = new int[BENCHMARK_N];
    for(int i=0; i<BENCHMARK_N; i++){
        arr[i] = lst.get(BENCHMARK_N-i-1);
    }
    delete arr;
    auto getSequentialBackwardsEnd = cr::high_resolution_clock::now();
    // ====== REMOVE RANDOM
    auto removeStart = cr::high_resolution_clock::now();
    std::cout << "Removing " << BENCHMARK_N << " elements at random positions..." << std::endl;
    while(lst.len()){
        lst.remove(rand()%lst.len());
    }
    auto removeEnd = cr::high_resolution_clock::now();
    // ====== REMOVE FRONT
    for(int i=0; i<BENCHMARK_N; i++){
        lst.append(i);
    }
    auto removeFrontStart = cr::high_resolution_clock::now();
    std::cout << "Removing " << BENCHMARK_N << " elements at the front..." << std::endl;
    while(lst.len()){
        lst.remove(0);
    }
    auto removeFrontEnd = cr::high_resolution_clock::now();
    // ====== PREPEND
    auto prependStart = cr::high_resolution_clock::now();
    std::cout << "Prepending " << BENCHMARK_N << " elements..." << std::endl;
    for(int i=0; i<BENCHMARK_N; i++){
        lst.prepend(i);
    }
    auto prependEnd = cr::high_resolution_clock::now();
    // ====== REMOVE BACK
    auto removeBackStart = cr::high_resolution_clock::now();
    std::cout << "Removing " << BENCHMARK_N << " elements at the back..." << std::endl;
    while(lst.len()){
        lst.remove(lst.len()-1);
    }
    auto removeBackEnd = cr::high_resolution_clock::now();
    // ====== INSERT
    auto insertStart = cr::high_resolution_clock::now();
    std::cout << "Inserting " << BENCHMARK_N << " elements at random positions..." << std::endl;
    for(int i=0; i<BENCHMARK_N; i++){
        lst.insert(lst.len() ? rand()%lst.len() : 0, i);
    }
    auto insertEnd = cr::high_resolution_clock::now();
    auto allEnd = cr::high_resolution_clock::now();

    std::cout << "======================" << std::endl;
    std::cout << "Benchmark results with a list of " << BENCHMARK_N << " elements:" << std::endl;
    std::cout << "Append: " << cr::duration_cast<cr::microseconds>(appendEnd-appendStart).count() << " microseconds" << std::endl;
    std::cout << "Prepend: " << cr::duration_cast<cr::microseconds>(prependEnd-prependStart).count() << " microseconds" << std::endl;
    std::cout << "Insert: " << cr::duration_cast<cr::microseconds>(insertEnd-insertStart).count() << " microseconds" << std::endl;
    std::cout << "Get (sequential): " << cr::duration_cast<cr::microseconds>(getSequentialEnd-getSequentialStart).count() << " microseconds" << std::endl;
    std::cout << "Get (sequential backwards): " << cr::duration_cast<cr::microseconds>(getSequentialBackwardsEnd-getSequentialBackwardsStart).count() << " microseconds" << std::endl;
    std::cout << "Get (random positions): " << cr::duration_cast<cr::microseconds>(getRandomEnd-getRandomStart).count() << " microseconds" << std::endl;
    std::cout << "Remove (random positions): " << cr::duration_cast<cr::microseconds>(removeEnd-removeStart).count() << " microseconds" << std::endl;
    std::cout << "Remove (front): " << cr::duration_cast<cr::microseconds>(removeFrontEnd-removeFrontStart).count() << " microseconds" << std::endl;
    std::cout << "Remove (back): " << cr::duration_cast<cr::microseconds>(removeBackEnd-removeBackStart).count() << " microseconds" << std::endl;
    std::cout << "Total: " << cr::duration_cast<cr::microseconds>(allEnd-allStart).count() << " microseconds" << std::endl;
    
    return 0;
}