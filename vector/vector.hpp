#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include <stdexcept>

//to delete:
#include <vector>
#include <algorithm>


namespace ft
{
template <class T, class Allocator = std::allocator<T> >
class vector
{
public:
    typedef T											value_type;
    typedef Allocator									allocator_type;
    typedef typename allocator_type::reference			reference;
    typedef typename allocator_type::const_reference	const_reference;
    typedef typename allocator_type::difference_type	difference_type;
    typedef typename allocator_type::pointer			pointer;
    typedef typename allocator_type::const_pointer		const_pointer;
    typedef typename allocator_type::size_type			size_type;

     typedef std::__wrap_iter<pointer>   					iterator; //ft
     typedef std::__wrap_iter<const_pointer>				const_iterator; //ft
//     typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;
//     typedef std::reverse_iterator<iterator>				reverse_iterator;

private:
    size_type											_size, _capacity;
	pointer										    	_value_first;
    allocator_type                                      _alloc;

    void exception_handler () {
        clear();
        _alloc.deallocate(_value_first, _size);
        _size = 0;
        _capacity = 0;
        throw;
    }

public:

//    default (1)
    explicit vector (const allocator_type& alloc = allocator_type())
            : _size(0) , _capacity(0), _value_first(0), _alloc(alloc) {}

//    fill (2)
    explicit vector (size_type n, const value_type& val = value_type(),
            const allocator_type& alloc = allocator_type())
            :_size(n), _capacity(n), _alloc(alloc) {
        _value_first = _alloc.allocate(_capacity);
        try {
            for (size_type i = 0; i < _size; i++) {
                _alloc.construct(_value_first + i, val);
            }
        } catch (std::exception &e) { // _alloc.construct
            exception_handler();
        }

    }

//    range (3)
    template <class InputIterator>
    vector (InputIterator first, InputIterator last,
            const allocator_type& alloc = allocator_type()): _alloc(alloc) {
    if (last < first) {
        throw std::length_error("vector");
    }
    _size = _capacity = last - first;
//    _capacity = _size;
    try {
        _value_first = _alloc.allocate(_capacity);
        for (size_type i = 0; first < last; first++, i++) {
            _alloc.construct(_value_first + i, *first);
        }
    } catch (std::exception &e) { // _alloc.construct
        exception_handler();
    }
}

//    copy (4)
    vector (const vector& x) {
        *this = x;
    }

    ~vector() {
        clear();
        _alloc.deallocate(_value_first, _size);
        _size = 0;
        _capacity = 0;
    }

    vector& operator=(const vector& x) {
        if (this != &x) {
            clear();
            _alloc.deallocate(_value_first, _size);
            _alloc = x._alloc;
            _size = _capacity = x._size;
//            _capacity = x._size;
            _value_first = _alloc.allocate(_capacity);
            try {
                for (size_type i = 0; i < _size; i++) {
                    _alloc.construct(_value_first + i, x._value_first[i]);
                }
            } catch (std::exception &e) { // _alloc.construct
                exception_handler();
            }
        }
        return *this;
	}

//Iterators:

    iterator               begin() { return iterator(_value_first); }
    const_iterator         begin()   const { return const_iterator(_value_first); }
    iterator               end() { return iterator(_value_first + _size); }
    const_iterator         end()     const { return const_iterator(_value_first + _size); }

//     reverse_iterator       rbegin();
    // const_reverse_iterator rbegin()  const;
    // reverse_iterator       rend();
    // const_reverse_iterator rend()    const;


public:
//Capacity:

    size_type size() const { return _size; }
    size_type max_size() const { return max_size(); }

    void resize(size_type sz, const value_type& c) {
        size_type i = 0;
		if (sz > _capacity) {
            try {
                pointer new_value = _alloc.allocate(sz);
                for (; i < _size; i++) {
                    _alloc.construct(new_value + i, _value_first[i]);
//                    new_value[i] = _value_first[i];
                }
                clear();
                _alloc.deallocate(_value_first, _size);
                _value_first = new_value;
                for (; i < sz; i++) {
                    _value_first[i] = c;
                }
            } catch (std::bad_alloc &ba) {
                throw &ba;
            }
            _size = sz;
        } else if (sz < _capacity) {
            for (size_type k = sz; k < _size; k++) {
                _alloc.destroy(_value_first + k);
            }
            for (size_type k = _size; k < sz; k++) {
                _value_first[k] = c;
            }
            _size = sz;
        }
	}

    size_type capacity() const { return _capacity; }
    bool empty() const { return _size == 0; }

    void reserve(size_type n);

//Element access:

    reference       operator[](size_type n) { return *(_value_first + n); }
    const_reference operator[](size_type n) const { return *(_value_first + n); }
    reference       at(size_type n) {
        if (n >= _size) {
            throw std::out_of_range("vector");
        }
        return _value_first[n];
    }
    const_reference at(size_type n) const {
        if (n >= _size) {
            throw std::out_of_range("vector");
        }
        return _value_first[n];
    }

    reference       front() { return _value_first; }
    const_reference front() const { return _value_first; }
    reference       back() { return _value_first + _size; }
    const_reference back() const { return _value_first + _size; }

//Modifiers:

    template <class InputIterator>
        void assign(InputIterator first, InputIterator last);
    void assign(size_type n, const value_type& u);
    // void assign(initializer_list<value_type> il);

    void push_back(const value_type& x) {
        pointer new_value;
        if (_capacity == _size) {
            new_value = _alloc.allocate(_capacity * 2);
            try {
                _capacity *= 2;
                size_type i = 0;
                for (; i < _size; i++) {
                    _alloc.construct(new_value + i, _value_first[i]);
                }
                _alloc.construct(new_value + i, x);
                for (size_type i = 0; i < _size; i++) {
                    _alloc.destroy(_value_first + i);
                }
                _alloc.deallocate(_value_first, _size);
                _value_first = new_value;
                _size += 1;
            } catch (std::exception& e) { // _alloc.construct

                throw;
            }
		}
	}

    void pop_back() {
        _alloc.destroy(_value_first + _size - 1);
        _size -= 1;
    }

    // iterator insert(const_iterator position, const value_type& x);
    // iterator insert(const_iterator position, value_type&& x);
    // iterator insert(const_iterator position, size_type n, const value_type& x);
    // template <class InputIterator>
    //     iterator insert(const_iterator position, InputIterator first, InputIterator last);
    // iterator insert(const_iterator position, initializer_list<value_type> il);

    // iterator erase(const_iterator position);
    // iterator erase(const_iterator first, const_iterator last);

    // void swap(vector&)
    //    (allocator_traits<allocator_type>::propagate_on_container_swap::value ||
    //              allocator_traits<allocator_type>::is_always_equal::value);  // C++17

    void clear() {
        for (size_type i = 0; i < _size; i++) {
            _alloc.destroy(_value_first + i);
        }
        _size = 0;
    }

//Allocator:

    allocator_type get_allocator() const { return _alloc; }


//    bool __invariants() const;

//    bool eq (const vector<T,Allocator>& y) const {
//        return (_size == y._size && std::equal(begin(), end(), y.begin()))
//    }
};

//Non-member function overloads:

//template <class T, class Allocator> bool operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
//    return x.eq(y);
//}
template <class T, class Allocator> bool operator< (const vector<T,Allocator>& x, const vector<T,Allocator>& y);
//template <class T, class Allocator> bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
//    return !(x == y);
//}
template <class T, class Allocator> bool operator> (const vector<T,Allocator>& x, const vector<T,Allocator>& y);
template <class T, class Allocator> bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
template <class T, class Allocator> bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);


}

#endif
