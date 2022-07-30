#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <vector>

namespace ft {
	template <class T, class Container = std::vector<T> >
	class stack {
		public:
			typedef Container                                container_type;
			typedef typename container_type::value_type      value_type;
			typedef typename container_type::size_type       size_type;

		protected:
			container_type c;

		public:
			stack() {}
			~stack() {}
			stack(const stack &q) {
				this = q;
			}
			stack& operator=(const stack &q) {
				this->c = q->c;
				return this;				
			}

			bool empty() const { return c.empty(); }
			size_type size() const { return c.size(); }
			value_type &top() { return c.back(); }
			const value_type& top() const { return c.back(); }
			void push(const value_type& x) { c.push_back(x); }
			void pop() { c.pop_back(); }
			bool eq(const stack<T, Container>& y) const { return c == y.c; }
			bool lft(const stack<T, Container>& y) const { return c < y.c; }
	};

	template <class T, class Container>
	bool operator==(const stack<T, Container>& x, const stack<T, Container>& y) {
		return x.eq(y);
	}
	template <class T, class Container>
	bool operator< (const stack<T, Container>& x, const stack<T, Container>& y) {
		return x.lft(y);
	}
	template <class T, class Container>
	bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y) {
		return !x.eq(y);
	}
	template <class T, class Container>
	bool operator> (const stack<T, Container>& x, const stack<T, Container>& y) {
		return !x.lft(y);
	}
	template <class T, class Container>
	bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y) {
		return (!x.lft(y) || x.eq(y));
	}
	template <class T, class Container>
	bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y) {
		return (x.lft(y) || x.eq(y));
	}
}

#endif