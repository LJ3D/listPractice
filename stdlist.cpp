#include <list>
#include <vector>
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

    // Our list object.
    std::list<int> lst;

    // APPEND
    sc::time_point t1 = sc::now();
    for (int i=0; i<BENCHMARK_N; i++) {
        lst.push_back (i);
    }
    d = sc::now()-t1;
    std::cout << "Append loop took " << d.count() << " us to run\n";

    // PREPEND
    t1 = sc::now();
    for (int i=0; i<BENCHMARK_N; i++) {
        lst.push_front (i);
    }
    d = sc::now()-t1;
    std::cout << "Prepend loop took " << d.count() << " us to run\n";

    // INSERT (wherever)
    t1 = sc::now();
    std::list<int>::iterator li = lst.begin(); // You need to start with an iterator to insert
    for (int i=0; i<BENCHMARK_N; i++) {
        li = lst.insert (li, i);
    }
    d = sc::now()-t1;
    std::cout << "Insert loop took " << d.count() << " us to run\n";

    // SEQ GET
    t1 = sc::now();
    li = lst.begin();
    for (int i=0; i<BENCHMARK_N; i++) {
        arr[i] = *li++;
    }
    d = sc::now()-t1;
    std::cout << "Seq. get loop took " << d.count() << " us to run\n";

    // SEQ GET BACKWARDS
    t1 = sc::now();
    li = lst.end();
    for (int i=0; i<BENCHMARK_N; i++) {
        arr[i] = *--li;
    }
    d = sc::now()-t1;
    std::cout << "Backwards seq. get loop took " << d.count() << " us to run\n";

    // RAND GET
    t1 = sc::now();
    li = lst.begin();
    for (int i=0; i<BENCHMARK_N; i++) {
        int idx = rand()%lst.size();
        li = lst.begin();
        std::advance (li, idx);
        arr[i] = *li;
    }
    d = sc::now()-t1;
    std::cout << "Rand. get loop took " << d.count() << " us to run\n";

    delete arr; // done with arr.

    // REMOVE BACK
    t1 = sc::now();
    for (int i=0; i<BENCHMARK_N; i++) {
        lst.pop_back();
    }
    d = sc::now()-t1;
    std::cout << "Remove back (pop_back) loop took " << d.count() << " us to run\n";

    // Refill the list:
    for (int i=0; i<BENCHMARK_N; i++) { lst.push_back (i); }

    // REMOVE FRONT
    t1 = sc::now();
    for (int i=0; i<BENCHMARK_N; i++) {
        lst.pop_front();
    }
    d = sc::now()-t1;
    std::cout << "Remove front (pop_front) loop took " << d.count() << " us to run\n";

    // Refill the list:
    for (int i=0; i<BENCHMARK_N; i++) { lst.push_back (i); }

    // REMOVE RAND
    t1 = sc::now();
    for (int i=0; i<BENCHMARK_N; i++) {
        int idx = rand()%lst.size();
        li = lst.begin();
        std::advance (li, idx);
        lst.erase (li);
    }
    d = sc::now()-t1;
    std::cout << "Remove back loop took " << d.count() << " us to run\n";

    sc::time_point tf = sc::now();


    d = tf - t0; // by using a duration, you can decide the time unit
    std::cout << "Entire program took " << d.count() << " us to run\n";
    return 0;
}
