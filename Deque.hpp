#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <iostream>
#include <typeinfo>

// Need to figure out how to solve the iterator mutation problem.
// Also need to insert checks to see if the iterator has been incremented outside the bounds of the array.
// Still dont know what to do with the ##Class_less_by_id

#define Deque_DEFINE(Class) 															\
																						\
typedef struct Deque_##Class Deque_##Class; 											\
typedef struct Deque_##Class##_Iterator Deque_##Class##_Iterator; 						\
					 																	\
/* First things first, create a dynamically resizing array.  The Deque will have to use \
   dynamically resizing array within it. */												\
struct Deque_##Class																	\
{																						\
	Class *buffer; 																		\
	int isize; 																			\
	int capacity; 																		\
	int head; 																			\
	int tail; 																			\
	char type_name[sizeof("Deque_") + sizeof(#Class)];									\
																						\
	/* Functions */ 																	\
	size_t (* size)( Deque_##Class *);													\
	bool (* empty)( Deque_##Class *);													\
	void (* clear)(Deque_##Class *);													\
	void (* push_back)( Deque_##Class *, const Class &);								\
	void (* push_front)( Deque_##Class *, const Class &);								\
    void (* pop_back)(Deque_##Class *); 												\
	void (* pop_front)(Deque_##Class *); 												\
	bool (* cmp)(const Class &, const Class &);											\
	const Class &(* front)(const Deque_##Class *);										\
	const Class &(* back)(const Deque_##Class *);										\
	const Class &(*at)(const Deque_##Class *, size_t i);								\
	Deque_##Class##_Iterator (* begin)(const Deque_##Class *); 							\
	Deque_##Class##_Iterator (* end)(const Deque_##Class *); 							\
	void (*dtor)(Deque_##Class *);														\
};																						\
 																						\
struct Deque_##Class##_Iterator 														\
{ 																						\
	int current; 																		\
	const Deque_##Class *deq;		 													\
																						\
	/* Functions */ 																	\
	void (* inc)(Deque_##Class##_Iterator *);											\
    void (* dec)(Deque_##Class##_Iterator *);											\
    const Class &(*deref)(const Deque_##Class##_Iterator *); 							\
};							 															\
																						\
 /****** AUXILIARY FUNCTIONS ******/													\
																						\
int 																					\
front_index(const Deque_##Class *deq) 													\
{ 																						\
	if(deq->head == deq->capacity - 1) return 0;			 							\
	else return deq->head + 1;				 											\
}																						\
																						\
int 																					\
back_index(const Deque_##Class *deq) 													\
{ 																						\
	if(deq->tail == 0) return deq->capacity - 1; 										\
	else return deq->tail - 1; 															\
}																						\
																						\
/*																						\
void print_elements(Deque_##Class *deq)													\
{																						\
	int i = front_index(deq);															\
	while(i!= deq->tail)																\
	{																					\
		std::cout << deq->buffer[i] << ", "; 											\
		if(i == deq->capacity - 1) i = 0;												\
		else i++;																		\
	}																					\
	std::cout << std::endl;																\
} */																					\
																						\
/* Need to redo this with the iterator later. <-- CHANGE NEEDED	*/						\
void																					\
Deque_realloc(Deque_##Class *deq)														\
{																						\
	Class *new_buffer = (Class *)malloc(2 * deq->capacity * sizeof(Class));				\
																						\
	int old_index = front_index(deq);													\
	int new_index = 1;																	\
	while(old_index != deq->tail)														\
	{																					\
		new_buffer[new_index] = deq->buffer[old_index];									\
		new_index++;																	\
		if(old_index == deq->capacity - 1) old_index = 0;								\
		else old_index++;																\
	}																					\
																						\
	deq->capacity = deq->capacity * 2;													\
	deq->head = 0;																		\
	deq->tail = deq->isize + 1;															\
	free(deq->buffer);																	\
	deq->buffer = new_buffer;															\
}																						\
																						\
/***** MAIN FUNCTIONS *****/ 															\
																						\
bool 																					\
Deque_##Class##_Iterator_equal(const Deque_##Class##_Iterator &it1,						\
							   const Deque_##Class##_Iterator &it2)						\
{																						\
																						\
	if( !(it1.deq->cmp(it1.deref(&it1), it2.deref(&it2))) &&							\
		!(it1.deq->cmp(it2.deref(&it2), it1.deref(&it1))) ) return true;				\
	else return false;																	\
}																						\
 																						\
bool 																					\
Deque_##Class##_equal(const Deque_##Class &d1, const Deque_##Class &d2)					\
{																						\
	int index_one = front_index(&d1);													\
	int index_two = front_index(&d2);													\
	while(index_one != d1.tail)		 													\
	{																					\
		if( !d1.cmp(d1.buffer[index_one],d2.buffer[index_two]) && 						\
			!d1.cmp(d2.buffer[index_two],d1.buffer[index_one]) ) 						\
		{																				\
			if(index_one == d1.capacity - 1) index_one = 0;								\
			else index_one++;															\
			if(index_two == d2.capacity - 1) index_two = 0;								\
			else index_two++;															\
		}																				\
		else return false;																\
	}																					\
	if(index_two != d2.tail) return false;												\
	return true;																		\
}																						\
																						\
size_t 																					\
size(Deque_##Class *deq) 																\
{ 																						\
	return deq->isize; 																	\
} 																						\
																						\
bool 																					\
empty(Deque_##Class *deq) 																\
{ 																						\
	return !deq->isize; 																\
} 																						\
																						\
void 																					\
clear(Deque_##Class *deq) 																\
{ 																						\
	deq->head = 0;																		\
	deq->tail = 1;																		\
	deq->isize = 0;																		\
} 																						\
 																						\
/* Implies that we add something at the end of the the array. Involves manipulating 	\
	the tail pointer. */																\
void 																					\
push_back(Deque_##Class *deq, const Class &elem)										\
{ 																						\
	/* Check if array is full. Keep the size 2 less than the capacity at all times so 	\
	   that the head/tail pointers never overlap. */ 									\
	if(deq->isize == deq->capacity - 2) Deque_realloc(deq); 							\
 																						\
	/* add element to tail. */															\
	deq->buffer[deq->tail] = elem; 														\
	deq->isize++; 																		\
 																						\
	/* First, do the pointer arithemetic on the tail index. */							\
	if(deq->tail >= deq->capacity - 1) deq->tail = 0; 									\
	else deq->tail++; 																	\
}																						\
																						\
/* Add to beginning of array. Involves manipulating the head pointer. */				\
void																					\
push_front(Deque_##Class *deq, const Class &elem)										\
{																						\
	/* Check if array is full. Keep the size 2 less than the capacity at all times so 	\ 
	   that the head/tail pointers never overlap. */									\
	if(deq->isize == deq->capacity - 2) Deque_realloc(deq);								\
																						\
	/* add element to head.	*/															\
	deq->buffer[deq->head] = elem;														\
	deq->isize++;																		\
																						\
	/* First, do the pointer arithemetic on the head index.	*/							\
	if(deq->head <= 0) deq->head = deq->capacity - 1;									\
	else deq->head--;																	\
} 																						\
 																						\
/* Pops the last element from the array, and decrements the tail pointer */				\
void																					\
pop_back(Deque_##Class *deq)															\
{ 																						\
	if(deq->isize == 0)  assert(false); 												\
	deq->isize--; 																		\
	if(deq->tail == 0) deq->tail = deq->capacity - 1;									\
	else deq->tail--; 																	\
} 																						\
 																						\
/* Pops the first element from the array, and increments the head pointer */			\
void																					\
pop_front(Deque_##Class *deq)															\
{ 																						\
	if(deq->isize == 0)  assert(false); 												\
	deq->isize--; 																		\
	if(deq->head == deq->capacity - 1) deq->head = 0;									\
	else deq->head++; 																	\
} 																						\
 																						\
const Class & 																			\
front(const Deque_##Class *deq) 														\
{ 																						\
	return deq->buffer[front_index(deq)];												\
} 																						\
 																						\
const Class & 																			\
back(const Deque_##Class *deq) 															\
{ 																						\
	return deq->buffer[back_index(deq)];												\
} 																						\
																						\
const Class &																			\
at(const Deque_##Class *deq, size_t i)													\
{																						\
	return deq->buffer[(front_index(deq) + i) % deq->capacity];							\
}																						\
																						\
/***** ITERATOR FUNCTIONS *****/ 														\
																						\
/* Increments the iterator pointer to the next value. If the iterator is already		\
   at the end of the array, then it keeps it there. */									\
void 																					\
inc(Deque_##Class##_Iterator *it)														\
{																						\
	if(Deque_##Class##_Iterator_equal(*it, it->deq->end(it->deq))) return;	 			\
	it->current++;																		\
}																						\
																						\
/* Decrements the iterator pointer to the next value. If the iterator is already		\
   at the beginning of the array, then it keeps it at there.*/							\
void 																					\
dec(Deque_##Class##_Iterator *it)														\
{																						\
	if(Deque_##Class##_Iterator_equal(*it, it->deq->begin(it->deq))) return; 			\
	it->current--;		 																\
}																						\
																						\
/* Leverages the "at()" function to dereference the iterator. */						\
const Class & 																			\
deref (const Deque_##Class##_Iterator *it)												\
{																						\
	return it->deq->at(it->deq, it->current);											\
}																						\
																						\
/***** ITERATOR RELATED DEQUE FUNCTIONS *****/ 											\
																						\
Deque_##Class##_Iterator 																\
begin(const Deque_##Class *deq) 														\
{																						\
	Deque_##Class##_Iterator it;														\
	it.current = 0;																		\
	it.deq = deq; 																		\
	it.inc = &inc;		 																\
	it.dec = &dec; 																		\
	it.deref = &deref;																	\
	return it;			 																\
} 																						\
																						\
Deque_##Class##_Iterator 																\
end(const Deque_##Class *deq) 															\
{																						\
	Deque_##Class##_Iterator it;														\
	it.current = deq->isize;															\
	it.deq = deq; 																		\
	it.inc = &inc;		 																\
	it.dec = &dec;	 																	\
	it.deref = &deref;																	\
	return it;			 																\
} 																						\
																						\
/***** CONSTRUCTOR AND DESTRUCTOR *****/ 												\
																						\
void																					\
dtor(Deque_##Class *deq)																\
{																						\
	free(deq->buffer);																	\
}																						\
 																						\
void																					\
Deque_##Class##_ctor(Deque_##Class *deq, bool (*less)(const Class &, const Class &))	\
{ 																						\
	/* Allocate enough space for two integers so we can set head and tail to indices. */\
	deq->buffer = (Class *)malloc(2 * sizeof(Class)); 									\
	deq->isize = 0; 																	\
	deq->head = 0; 																		\
	deq->tail = 1; 																		\
	deq->capacity = 2; 																	\
	strcpy(deq->type_name, "Deque_");													\
	strcat(deq->type_name, #Class); 													\
																						\
	deq->size = &size; 																	\
	deq->empty = &empty; 																\
	deq->clear = &clear;																\
	deq->push_front = &push_front; 														\
	deq->push_back = &push_back; 														\
	deq->front = &front;																\
	deq->back = &back; 																	\
	deq->pop_back = &pop_back; 															\
	deq->pop_front = &pop_front; 														\
	deq->cmp = less; 																	\
	deq->at = &at;																		\
	deq->begin = &begin; 																\
	deq->end = &end; 																	\
	deq->dtor = &dtor;																	\
}
#endif /* DEQUE_HPP */