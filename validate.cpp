

/*
    ========================================
    This is weird and messy, but it works :)
    ========================================
*/


#include <iostream>
#include <chrono>
#include <list> // For comparison
#include "list.hpp"

#define VALIDATE_N 1000

template<typename T>
bool arrCmp(T* arr1, T* arr2, int len){
    for(int i=0; i<len; i++){
        if(arr1[i] != arr2[i]){
            return false;
        }
    }
    return true;
}

bool validateLists(LJLIST::list<int>& lst, std::list<int>& s_lst){
    std::list<int>::iterator s_it = s_lst.begin();
    int* lst_arr = new int[lst.len()];
    int* s_lst_arr = new int[s_lst.size()];
    for(int i=0; i<lst.len(); i++){
        lst_arr[i] = lst.get(i);
        s_lst_arr[i] = *s_it;
        s_it++;
    }
    return arrCmp(lst_arr, s_lst_arr, lst.len());
}

void deleteRandomTest(LJLIST::list<int>& lst, std::list<int>& s_lst){
    std::list<int>::iterator s_it = s_lst.begin();
    for(int i=0; i<VALIDATE_N; i++){
        int idx = rand()%lst.len();
        lst.remove(idx);
        s_it = s_lst.begin();
        std::advance(s_it, idx);
        s_lst.erase(s_it);
    }
}

void popFrontTest(LJLIST::list<int>& lst, std::list<int>& s_lst){
    for(int i=0; i<VALIDATE_N; i++){
        lst.pop_front();
        s_lst.pop_front();
    }
}

void popBackTest(LJLIST::list<int>& lst, std::list<int>& s_lst){
    for(int i=0; i<VALIDATE_N; i++){
        lst.pop_back();
        s_lst.pop_back();
    }
}

void insertRandomTest(LJLIST::list<int>& lst, std::list<int>& s_lst){
    std::list<int>::iterator s_it = s_lst.begin();
    for(int i=0; i<VALIDATE_N; i++){
        int idx = lst.len() ? rand()%lst.len() : 0;
        lst.insert(i, idx);
        s_it = s_lst.begin();
        std::advance(s_it, idx);
        s_lst.insert(s_it, i);
    }
}

void prependTest(LJLIST::list<int>& lst, std::list<int>& s_lst){
    for(int i=0; i<VALIDATE_N; i++){
        lst.push_front(i);
        s_lst.push_front(i);
    }
}

void appendTest(LJLIST::list<int>& lst, std::list<int>& s_lst){
    for(int i=0; i<VALIDATE_N; i++){
        lst.append(i);
        s_lst.push_back(i);
    }
}

void sortTest(LJLIST::list<int>& lst, std::list<int>& s_lst){
    lst.sort();
    s_lst.sort();
}


int main(){
    LJLIST::list<int> lst;
    std::list<int> s_lst;

    // First run the append test to fill the list with VALIDATE_N elements
    appendTest(lst, s_lst);
    if(!validateLists(lst, s_lst)){
        std::cout << "ERR: Append test failed" << std::endl;
        return 1;
    }else{
        std::cout << "PASS: Append test passed" << std::endl;
    }

    // Then run the delete random test to delete VALIDATE_N elements from the list
    deleteRandomTest(lst, s_lst);
    if(!validateLists(lst, s_lst)){
        std::cout << "ERR: Delete random test failed" << std::endl;
        return 1;
    }else{
        std::cout << "PASS: Delete random test passed" << std::endl;
    }

    // Then run the insert random test to insert VALIDATE_N elements into the list
    insertRandomTest(lst, s_lst);
    if(!validateLists(lst, s_lst)){
        std::cout << "ERR: Insert random test failed" << std::endl;
        return 1;
    }else{
        std::cout << "PASS: Insert random test passed" << std::endl;
    }

    // Then run the sort test to sort the list
    sortTest(lst, s_lst);
    if(!validateLists(lst, s_lst)){
        std::cout << "ERR: Sort test failed" << std::endl;
        return 1;
    }else{
        std::cout << "PASS: Sort test passed" << std::endl;
    }

    // Then run the pop front test to pop VALIDATE_N elements from the front of the list
    popFrontTest(lst, s_lst);
    if(!validateLists(lst, s_lst)){
        std::cout << "ERR: Pop front test failed" << std::endl;
        return 1;
    }else{
        std::cout << "PASS: Pop front test passed" << std::endl;
    }

    // Then run the prepend test to prepend VALIDATE_N elements to the front of the list
    prependTest(lst, s_lst);
    if(!validateLists(lst, s_lst)){
        std::cout << "ERR: Prepend test failed" << std::endl;
        return 1;
    }else{
        std::cout << "PASS: Prepend test passed" << std::endl;
    }

    // Then run the pop back test to pop VALIDATE_N elements from the back of the list
    popBackTest(lst, s_lst);
    if(!validateLists(lst, s_lst)){
        std::cout << "ERR: Pop back test failed" << std::endl;
        return 1;
    }else{
        std::cout << "PASS: Pop back test passed" << std::endl;
    }

    return 0;
}