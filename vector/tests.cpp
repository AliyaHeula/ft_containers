#include "vector.hpp"
#include <iostream>
#include <vector>

void print_vector(ft::vector<int> &ft) {
    for (size_t i = 0; i < ft.size(); i++) {
        std::cout << ft[i] << " ";
    }
    std::cout << "\t<- ft" << "\n";
}

void print_vector(std::vector<int> &ft) {
    for (size_t i = 0; i < ft.size(); i++) {
        std::cout << ft[i] << " ";
    }
    std::cout << "\t<- std" << "\n";
}

void print_capacity_size(ft::vector<int> &ft) {
    std::cout << "capacity " << ft.capacity() << std::endl;
    std::cout << "size " << ft.size() << std::endl;
}

void print_capacity_size(std::vector<int> &ft) {
    std::cout << "capacity " << ft.capacity() << std::endl;
    std::cout << "size " << ft.size() << std::endl;
}

int main() {
//push_back()
    std::cout << "\n\npush_back()\n";
    ft::vector<int> ft;
    std::vector<int> st;
    for (int k = 0; k < 5; k++) {
        ft.push_back(k);
        st.push_back(k);
        print_capacity_size(ft);
        print_vector(ft);
        std::cout << std::endl;
    }

//reserve()
    std::cout << "\n\nreserve()\n";
    ft.reserve(4);
    print_capacity_size(ft);
    ft.reserve(2);
    print_capacity_size(ft);

//assign()
    std::cout << "\n\nassign()\n";
    ft.assign(8, 8);
    st.assign(8, 9);
    print_vector(ft);
    print_vector(st);

    ft.assign(2, 1);
    st.assign(2, 7);
    print_vector(ft);
    print_vector(st);
}