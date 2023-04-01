#include <iostream>
#include <chrono>
#include <list> // For comparison
#include "list.hpp"

int main(){
    LJLIST::list<int> l_list;
    std::list<int> s_list;

    // Append some numbers
    std::cout << "Appending numbers..." << std::endl;
    for(int i=0; i<1000; i++){
        l_list.append(i);
        s_list.push_back(i);
    }

    // Get numbers at random positions
    std::cout << "Getting numbers at random positions..." << std::endl;
    std::list<int>::iterator s_it;
    for(int i=0; i<1000; i++){
        int idx = rand()%l_list.len();
        int l_val = l_list.get(idx);
        s_it = s_list.begin();
        for(int j=0; j<idx; j++){
            s_it++;
        }
        int s_val = *s_it;
        if(l_val != s_val){
            std::cout << "ERROR: " << l_val << " != " << s_val << std::endl;
        }
    }

    // Remove a few numbers at random positions
    std::cout << "Removing numbers at random positions..." << std::endl;
    for(int i=0; i<100; i++){
        int idx = rand()%l_list.len();
        l_list.remove(idx);
        s_it = s_list.begin();
        for(int j=0; j<idx; j++){
            s_it++;
        }
        s_list.erase(s_it);
    }
    // Get numbers at random positions (again)
    std::cout << "Getting numbers at random positions..." << std::endl;
    for(int i=0; i<1000; i++){
        int idx = rand()%l_list.len();
        int l_val = l_list.get(idx);
        s_it = s_list.begin();
        for(int j=0; j<idx; j++){
            s_it++;
        }
        int s_val = *s_it;
        if(l_val != s_val){
            std::cout << "ERROR: " << l_val << " != " << s_val << std::endl;
        }
    }

    // Insert a few numbers at random positions
    std::cout << "Inserting numbers at random positions..." << std::endl;
    for(int i=0; i<100; i++){
        int idx = rand()%l_list.len();
        l_list.insert(i, idx);
        s_it = s_list.begin();
        for(int j=0; j<idx; j++){
            s_it++;
        }
        s_list.insert(s_it, i);
    }

    // Get numbers at random positions (again)
    std::cout << "Getting numbers at random positions..." << std::endl;
    for(int i=0; i<1000; i++){
        int idx = rand()%l_list.len();
        int l_val = l_list.get(idx);
        s_it = s_list.begin();
        for(int j=0; j<idx; j++){
            s_it++;
        }
        int s_val = *s_it;
        if(l_val != s_val){
            std::cout << "ERROR: " << l_val << " != " << s_val << std::endl;
        }
    }

    return 0;
}