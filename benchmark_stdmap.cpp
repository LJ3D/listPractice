#include <map>
#include <chrono>
#include <iostream>

int main()
{
    using namespace std::chrono;
    using sc = std::chrono::steady_clock;

    sc::time_point t0 = sc::now();  // ns is default for time_point, it seems

    static constexpr int BENCHMARK_N = 50000;

    srand(time(NULL));

    std::cout << "Benchmarking with " << BENCHMARK_N << " loops...\n";

    // Used for get benchmarking
    int* arr = new int[BENCHMARK_N];

    // Here's how to construct a 0 microsecond duration
    duration<double, std::micro> d{};

    // Our map object (and an iterator) (pretending to be a list)
    std::map<int, int> lst;
    std::map<int, int>::iterator li = lst.begin();

    // APPEND
    sc::time_point t1 = sc::now();
    for (int i=0; i<BENCHMARK_N; i++) {
        lst[i] = i;
    }
    d = sc::now()-t1;
    std::cout << "Append loop took " << d.count() << " us to run\n";

    // RAND GET
    t1 = sc::now();
    li = lst.begin();
    for (int i=0; i<BENCHMARK_N; i++) {
        int idx = rand()%lst.size();
        arr[i] = lst[idx];
    }
    d = sc::now()-t1;
    std::cout << "Rand. get loop took " << d.count() << " us to run\n";

    // SEQ GET
    t1 = sc::now();
    li = lst.begin();
    for (int i=0; i<BENCHMARK_N; i++) {
        arr[i] = lst[i];
    }
    d = sc::now()-t1;
    std::cout << "Seq. get loop took " << d.count() << " us to run\n";

    // SEQ GET BACKWARDS
    t1 = sc::now();
    for (int i=0; i<BENCHMARK_N; i++) {
        arr[i] = lst[BENCHMARK_N-1-i];
    }
    d = sc::now()-t1;
    std::cout << "Backwards seq. get loop took " << d.count() << " us to run\n";

    // REMOVE RAND
    t1 = sc::now();
    for (int i=0; i<BENCHMARK_N; i++) {
        int idx = rand()%lst.size();
        lst.erase (idx);
    }
    d = sc::now()-t1;
    std::cout << "Remove random loop took " << d.count() << " us to run\n";

    // Refill the list:
    for (int i=0; i<BENCHMARK_N; i++) { lst[i] = i; }

    // REMOVE FRONT
    t1 = sc::now();
    for (int i=0; i<BENCHMARK_N; i++) {
        lst.erase (i);
    }
    d = sc::now()-t1;
    std::cout << "Remove front (pop_front) loop took " << d.count() << " us to run\n";

    // PREPEND
    t1 = sc::now();
    for (int i=0; i<BENCHMARK_N; i++) {
        // add in reverse order, there's no obvious prepend for a map
        lst[BENCHMARK_N-1-i] = i;
    }
    d = sc::now()-t1;
    std::cout << "Prepend loop took " << d.count() << " us to run\n";

    // REMOVE BACK
    t1 = sc::now();
    for (int i=0; i<BENCHMARK_N; i++) {
        lst.erase(BENCHMARK_N-1-i);
    }
    d = sc::now()-t1;
    std::cout << "Remove back (pop_back) loop took " << d.count() << " us to run\n";

    // INSERT (wherever)
    t1 = sc::now();
    li = lst.begin(); // You need to start with an iterator to insert
    for (int i=0; i<BENCHMARK_N; i++) {
        int idx =  rand()%BENCHMARK_N;
        lst[idx] = i;
    }
    d = sc::now()-t1;
    std::cout << "Insert random loop took " << d.count() << " us to run\n";

    delete arr; // done with arr.

    sc::time_point tf = sc::now();

    d = tf - t0; // by using a duration, you can decide the time unit
    std::cout << "Entire program took " << d.count() << " us to run\n";
    return 0;
}
