#include "Deque.hpp"

Deque_DEFINE(int)

bool hi(const int &o1, const int &o2)
{ return o1 < o2; }

int
main(void)
{
	Deque_int deq;
	Deque_int_ctor(&deq, hi);
	deq.push_front(&deq, 1);
	deq.push_front(&deq, 2);
	deq.push_front(&deq, 3);
	deq.push_front(&deq, 4);
	deq.push_front(&deq, 5);
	push_back(&deq, 6);
	push_back(&deq, 7);
	push_back(&deq, 8);
	push_back(&deq, 9);

	print_elements(&deq);
	std::cout << deq.at(&deq, 0) << ", ";
	std::cout << deq.at(&deq, 1) << ", ";
	std::cout << deq.at(&deq, 2) << ", ";
	std::cout << deq.at(&deq, 3) << ", ";
	std::cout << deq.at(&deq, 4) << ", ";
	std::cout << deq.at(&deq, 5) << ", ";
	std::cout << deq.at(&deq, 6) << ", ";
	std::cout << deq.at(&deq, 7) << ", ";
	std::cout << deq.at(&deq, 8) << ", ";
	std::cout << std::endl;
	

	return 0;
}