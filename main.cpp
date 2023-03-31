#include <iostream>
#include <chrono>
#include "list.hpp"


/*
int main(){
    srand(time(NULL));
    list<int> lst;

    // Some basic tests of the list
    for(int i=0; i<10; i++){
        lst.append(i);
    }

    std::cout << "List length: " << lst.len() << std::endl;
    std::cout << "List contents: ";
    for(int i=0; i<lst.len(); i++){
        std::cout << lst.get(i) << " ";
    }
    std::cout << std::endl;

    std::cout << "Removing element at index 5" << std::endl;
    lst.remove(5);

    std::cout << "Removing element at index 0" << std::endl;
    lst.remove(0);

    std::cout << "List length: " << lst.len() << std::endl;
    std::cout << "List contents: ";
    for(int i=0; i<lst.len(); i++){
        std::cout << lst.get(i) << " ";
    }
    std::cout << std::endl;

    lst.printDebugInfo();

    std::cout << "Removing all elements" << std::endl;
    while(lst.len()){
        lst.remove(0);
    }

    std::cout << "List length: " << lst.len() << std::endl;

    std::cout << "Appending 100 random elements" << std::endl;
    for(int i=0; i<100; i++){
        lst.append(rand()%100);
    }

    std::cout << "Removing all elements which are divisible by 2" << std::endl;
    for(int i=0; i<lst.len(); i++){
        if(lst.get(i)%2==0){
            std::cout << "Removing element at index " << i << std::endl;
            lst.remove(i);
            i--;
            std::cout << "New list contents: ";
            for(int i=0; i<lst.len(); i++){
                std::cout << lst.get(i) << " ";
            }
            std::cout << std::endl;
        }
    }

    std::cout << "List length: " << lst.len() << std::endl;
    std::cout << "List contents: ";
    for(int i=0; i<lst.len(); i++){
        std::cout << lst.get(i) << " ";
    }
    std::cout << std::endl;
}
*/





#define BENCHMARK_N 50000

int main(){
    srand(time(NULL));
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
        int idx = rand()%lst.len();
        arr[i] = lst.get(idx);
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
    std::cout << "Getting " << BENCHMARK_N << " elements at sequential positions backwards and placing them in an array..." << std::endl;
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
        lst.remove(rand()%lst.len());
    }
    auto removeEnd = std::chrono::high_resolution_clock::now();
    // ====== REMOVE FRONT
    for(int i=0; i<BENCHMARK_N; i++){
        lst.append(i);
    }
    auto removeFrontStart = std::chrono::high_resolution_clock::now();
    std::cout << "Removing " << BENCHMARK_N << " elements at the front..." << std::endl;
    while(lst.len()){
        lst.remove(0);
    }
    auto removeFrontEnd = std::chrono::high_resolution_clock::now();
    // ====== PREPEND
    auto prependStart = std::chrono::high_resolution_clock::now();
    std::cout << "Prepending " << BENCHMARK_N << " elements..." << std::endl;
    for(int i=0; i<BENCHMARK_N; i++){
        lst.prepend(i);
    }
    auto prependEnd = std::chrono::high_resolution_clock::now();
    // ====== REMOVE BACK
    auto removeBackStart = std::chrono::high_resolution_clock::now();
    std::cout << "Removing " << BENCHMARK_N << " elements at the back..." << std::endl;
    while(lst.len()){
        lst.remove(lst.len()-1);
    }
    auto removeBackEnd = std::chrono::high_resolution_clock::now();
    // ====== INSERT
    auto insertStart = std::chrono::high_resolution_clock::now();
    std::cout << "Inserting " << BENCHMARK_N << " elements at random positions..." << std::endl;
    for(int i=0; i<BENCHMARK_N; i++){
        lst.insert(lst.len() ? rand()%lst.len() : 0, i);
    }
    auto insertEnd = std::chrono::high_resolution_clock::now();
    auto allEnd = std::chrono::high_resolution_clock::now();

    std::cout << "\n\n\n====================\n";
    std::cout << "Benchmark results with a list of " << BENCHMARK_N << " elements:" << std::endl;
    std::cout << "Append: " << std::chrono::duration_cast<std::chrono::milliseconds>(appendEnd-appendStart).count() << "ms" << std::endl;
    std::cout << "Prepend: " << std::chrono::duration_cast<std::chrono::milliseconds>(prependEnd-prependStart).count() << "ms" << std::endl;
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
