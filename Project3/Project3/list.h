#ifndef CS20A_LIST_H
#define CS20A_LIST_H

#include<iostream>
#include<assert.h>
// Linked List object that maintains both m_head and m_tail pointers
// and the m_size of the list.  Note that you have to keep the m_head,
// m_tail and m_size consistent with the intended state of the List 
// otherwise very bad things happen. 
template<typename Item>
class List {
public:

	List();

	List(const List<Item>& other);

	List<Item>& operator=(const List<Item>& other);

	~List();

	void	print() const;
	bool	empty() const;

	void	push_front(const Item& item);
	void	push_rear(const Item& item);
	void	insert(int index, const Item& item);

	// Note that the user must first ensure the list is not empty
	// prior to calling these functions. */
	Item	front() const;
	Item	rear() const;
	Item	get(int index) const;

	int		size() const;
	
	int		find(const Item& item) const;

	bool	pop_front();
	bool	pop_rear();
	bool	remove(int index);

#ifndef MAKE_MEMBERS_PUBLIC
private:
#endif
	// Forward declare the nodes for our List.
	// Will be implemented along with list's
	// member functions
	class Node;

	// We'll have both m_head and m_tail points for 
	// Fast insertion/deletion from both ends.
	Node* m_head;
	Node* m_tail;

	// Keep track of number of nodes in the list
	int		m_size;
};


/* List Implementation
//
//  Since List is a template class (which is not an actual
//  class yet, not until we actually instantiate the list)
//  we need to keep the implementation together with
//  the definition.  There are ways to simulate having
//  separate "implementation/definition" with templates,
//  but they aren't necessary and can be confusing.
*/

/* Node definition
//		Already implemented, nothing to do here but to use it.
*/
template<typename Item>
class List<Item>::Node {
public:
	Node() :next(nullptr), prev(nullptr) {}
	Node(Item it, Node* p, Node* n) : item(it), next(n), prev(p) {}

	Item  item;
	Node* next;
	Node* prev;
};



/* List default constructor
//		Set m_head and m_tail pointer to point to nothing, m_size is zero
//		Already implemented, nothing to do.
*/
template<typename Item>
List<Item>::List() :m_head(nullptr), m_tail(nullptr), m_size(0) {
}


/* 
Copy constructor
*/
template<typename Item>
List<Item>::List(const List<Item>& other) {

	Node* p = other.m_head;
	while (p != nullptr) {
		push_rear(p->item);
		p = p->next;
	}
}

/* Overloaded assignment operator*/

template<typename Item>
List<Item>& List<Item>::operator=(const List<Item>& other) {
	Node* p = other.m_head;
	while (p != nullptr) {
		push_rear(p->item);
		p = p->next;
	}
	return *this;
}


/* List destructor
*/
template<typename Item>
List<Item>::~List() {
	for (int i = 0; i < m_size; i++) {
		pop_front();
	}
}

/* List push_front
*/
template<typename Item>
void List<Item>::push_front(const Item& item)
{
	// Create the new node
	Node* p = new Node;
	p->item = item;
	p->next = nullptr;
	p->prev = nullptr;
	if (m_head == nullptr)
	{
		m_head = p;
		m_tail = p;
	} else { // Other case
		p->next = m_head;
		m_head->prev = p;
		m_head = p;
	}
	m_size++;

}

/* List print */

template<typename Item>
void List<Item>::print() const {

	Node* p;
	p = m_head;
	while (p != nullptr)
	{
		std::cout << p->item << " ";
		p = p->next;
	}
	std::cout << std::endl;
}


/* List push_rear */
template<typename Item>
void List<Item>::push_rear(const Item& item)
{
	Node* p = new Node;
	p->item = item;
	p->next = nullptr;
	p->prev = nullptr;

	if (m_head == nullptr)
	{
		push_front(item);
	}
	else
	{
		p->prev = m_tail;
		m_tail->next = p;
		m_tail = p;
		m_size++;
	}
}

/* List empty */

template<typename Item>
bool List<Item>::empty() const {
	return m_head == nullptr;

}

/*List front*/

template<typename Item>
Item List<Item>::front() const {
	// Force check that the m_head is pointing to a Node
	// Typical solution for deployement code is to throw
	// exceptions, but since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(m_head != nullptr);
	return m_head->item;
}

/* List rear */

template<typename Item>
Item List<Item>::rear() const {

	// Force check that the m_tail is pointing to a Node
	// Typical solution for deployement code is to throw
	// exceptions, since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(m_tail != nullptr);
	return m_tail->item;

}

/* List get */
//		returns the item at index

template<typename Item>
Item List<Item>::get(int index) const {

	// Force index to be correct before getting the Item
	// Typical solution for deployement code is to throw
	// exceptions, since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(index >= 0 && index < m_size);
	Node* p = m_head;
	for (int i = 0; i < index; i++) {
		p = p->next;
	}
	return p->item;
	
}

/* List size */
template<typename Item>
int List<Item>::size() const {
	return m_size;
}

/* List find  */

template<typename Item>
int List<Item>::find(const Item& item) const {
	int index = 0;
	Node* p = m_head;
	while (p != nullptr) {
		if (p->item == item) {
			return index;
		}
		p = p->next;
		index++;
	}

	return -1;
}

/* List pop_front */

template<typename Item>
bool List<Item>::pop_front() {

	if (m_head == nullptr)
	{
		// Case: list is empty
		return false;
	}
	if (m_size == 1) {
		Node* tmp = m_head;
		m_head = nullptr;
		m_tail = nullptr;
		delete tmp;
	} else {
		Node* tmp = m_head;
		m_head = m_head->next;
		tmp->next = nullptr;
		m_head->prev = nullptr;
		delete tmp;
	}

	m_size--;
	return true;
}

/* List pop_rear*/

template<typename Item>
bool List<Item>::pop_rear() {
	if (m_head == nullptr)
	{
		// Case: list is empty
		return false;
	}
	if (m_size == 1) {
		Node* tmp = m_head;
		m_head = nullptr;
		m_tail = nullptr;
		delete tmp;
	}
	else {
		Node* tmp = m_tail;
		m_tail = m_tail->prev;
		m_tail->next = nullptr;
		tmp->prev = nullptr;
		delete tmp;
		
	}

	m_size--;
	return true;
}


/* List remove */

template<typename Item>
bool List<Item>::remove(int index) {
	assert(index >= 0 && index < m_size);
	if (index == 0) {
		return pop_front();
	}
	if (index == m_size - 1) {
		return pop_rear();
	}

	// Other cases
	Node* p = m_head;
	for (int i = 0; i < index - 1; i++) {
		p = p->next;
	}
	Node* tmp = p->next;
	p->next = p->next->next;
	tmp->next->prev = p;
	tmp->next = nullptr;
	tmp->prev = nullptr;
	delete tmp;

	m_size--;
	return true;

}

/* List insert */
template<typename Item>
void List<Item>::insert(int index, const Item& item) {
	assert(index >= 0 && index < m_size);
	if (index == 0) {
		push_front(item);
	}
	else if (index == m_size - 1) {
		push_rear(item);
	}
	else {
		Node* p = m_head;
		Node* newNode= new Node;
		newNode->item = item;
		newNode->next = nullptr;
		newNode->prev = nullptr;
		for (int i = 0; i < index - 1; i++) {
			p = p->next;
		}
		newNode->next = p->next;
		p->next->prev = newNode;
		p->next = newNode;
		newNode->prev = p;
		m_size++;
	}

}

#endif
