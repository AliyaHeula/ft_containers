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
    std::cout << "size " << ft.size() << "\n\n";
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
    ft.reserve(9);
    st.reserve(9);
    print_vector(ft);
    print_capacity_size(ft);
    print_vector(st);
    print_capacity_size(st);

    ft.reserve(2);
    st.reserve(2);
    print_vector(ft);
    print_capacity_size(ft);
    print_vector(st);
    print_capacity_size(st);

//assign()
    std::cout << "\n\nassign()\n";
    ft.assign(10, 8);
    st.assign(10, 8);
    print_vector(ft);
    print_capacity_size(ft);
    print_vector(st);
    print_capacity_size(st);

    ft.assign(2, 1);
    st.assign(2, 7);
    print_vector(ft);
    print_capacity_size(ft);
    print_vector(st);
    print_capacity_size(st);

    ft::vector<int> ft1;
    std::vector<int> st1;

    for (int k = 0; k < 3; k++) {
        ft1.push_back(k);
        st1.push_back(k);
    }
    print_vector(ft1);
    print_capacity_size(ft1);
    print_vector(st1);
    print_capacity_size(st1);
    std::cout << "\n\nresize():\n";
    ft1.resize(1,7);
    st1.resize(1,7);
    print_vector(ft1);
    print_capacity_size(ft1);
    print_vector(st1);
    print_capacity_size(st1);

    ft1.resize(5,5);
    st1.resize(5,5);
    print_vector(ft1);
    print_capacity_size(ft1);
    print_vector(st1);
    print_capacity_size(st1);

    ft1.resize(11,11);
    st1.resize(11,11);
    print_vector(ft1);
    print_capacity_size(ft1);
    print_vector(st1);
    print_capacity_size(st1);
}