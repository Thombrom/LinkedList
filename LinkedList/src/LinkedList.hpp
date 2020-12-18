#pragma once

#include <initializer_list>
#include <exception>

/* Forward declarations */
template <class T>
class LinkedList;

/* Exceptions */
struct OutOfBoundsException : public std::exception
{
	const char* what() const throw()
	{
		return "LinkedList out of bounds";
	}
};

/* LinkedListItterator Declarations */
template <class T>
class LinkedListIterator
{
public:
	using ValueType = typename LinkedList<T>::ValueType;
	using ValuePointer = ValueType*;
	using ValueReference = ValueType&;

	using NodeType = typename LinkedList<T>::list_node;
	using NodePointer = NodeType*;
	using NodeReference = NodeType&;

public:
	LinkedListIterator(NodePointer _ptr);

	LinkedListIterator& operator++();
	LinkedListIterator operator++(int);
	bool operator!= (const LinkedListIterator& _itt);

	ValuePointer operator->();
	ValueReference operator*();

private:
	NodePointer m_ptr;
};

/* LinkedListItterator Implementation */
template <class T>
LinkedListIterator<T>::LinkedListIterator(NodePointer ptr)
{
	m_ptr = ptr;
}

template <class T>
bool LinkedListIterator<T>::operator!=(const LinkedListIterator& _itt)
{
	return m_ptr != _itt.m_ptr;
}

template <class T>
LinkedListIterator<T>& LinkedListIterator<T>::operator++()
{
	m_ptr = m_ptr->m_next;
	return *this;
}

template <class T>
LinkedListIterator<T> LinkedListIterator<T>::operator++(int)
{
	LinkedListIterator iterator = *this;
	++(*this);
	return iterator;
}

template <class T>
typename LinkedListIterator<T>::ValuePointer LinkedListIterator<T>::operator->()
{
	return *(m_ptr->m_value);
}

template <class T>
typename LinkedListIterator<T>::ValueReference LinkedListIterator<T>::operator*()
{
	return m_ptr->m_value;
}

/* Linkedlist Declarations */
template <class T>
class LinkedList
{
	friend class LinkedListIterator<T>;

	public:
		using ValueType		 = T;
		using ValuePointer	 = ValueType*;
		using ValueReference = ValueType&;

		using Iterator = LinkedListIterator<ValueType>;

	private:

		/* Node Implementation */
		struct list_node {
			T m_value;

			list_node* m_next;
		};

		using NodeType       = list_node;
		using NodePointer    = list_node*;
		using NodeReference  = list_node&;

	public:
		LinkedList();
		LinkedList(std::initializer_list<ValueType> _initlist);
		~LinkedList();

	public:
		ValueReference pop();
		ValueReference push(ValueType _value);

		Iterator begin();
		Iterator end();

		ValueReference operator[](const int& _index);

	private:
		NodePointer end_ptr();
		NodePointer m_root;
};

/* LinkedList Implementation */

template <class T>
LinkedList<T>::LinkedList()
{
	m_root = new NodeType();
}

template <class T>
LinkedList<T>::LinkedList(std::initializer_list<T> _initlist)
{
	m_root = new NodeType();

	NodePointer cond = m_root;
	for (ValueType val : _initlist)
	{
		cond->m_next = new NodeType();
		cond = cond->m_next;
		
		cond->m_value = val;
	}
}

template <class T>
LinkedList<T>::~LinkedList()
{
	NodePointer cond = m_root;

	while (cond != nullptr)
	{
		NodePointer buff = cond->m_next;
		delete cond;

		cond = buff;
	}
}

template <class T>
typename LinkedList<T>::NodePointer LinkedList<T>::end_ptr()
{
	NodePointer cond = m_root;

	while (cond->m_next != nullptr)
	{
		cond = cond->m_next;
	}

	return cond;
}

template <class T>
T& LinkedList<T>::push(ValueType _value)
{
	NodePointer end = end_ptr();

	end->m_next = new list_node();
	end->m_next->m_value = _value;

	return _value;
}

template <class T>
T& LinkedList<T>::pop()
{
	NodePointer cond = m_root;

	if (cond->m_next == nullptr)
		throw new OutOfBoundsException;

	while (cond->m_next->m_next != nullptr)
	{
		cond = cond->m_next;
	}

	ValueType val = cond->m_next->m_value;
	delete cond->m_next;
	cond->m_next = nullptr;

	return val;
}

template <class T>
T& LinkedList<T>::operator[](const int& _index)
{
	NodePointer cond = m_root;

	//One added to accomodate for m_root being 0
	for (uint32_t index = _index + 1; index != 0; index--)
	{
		if (cond->m_next == nullptr)
			throw new OutOfBoundsException;
		
		cond = cond->m_next;
	}

	return cond->m_value;
}

template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::begin()
{
	NodePointer ptr = m_root->m_next;
	return Iterator(ptr);
}

template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::end()
{
	return Iterator(nullptr);
}


