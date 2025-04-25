#pragma once
#include<iostream>

using namespace std;

template<typename T>
class Unit
{
public:
	T value;
	Unit<T>* next;

	Unit(T val = {}, Unit<T>* nxt = nullptr) : value(val), next(nxt) { }
	
	Unit* get_next()
	{
		return next;
	}
};


template<typename T>
class List
{
protected:
	Unit<T>* first;
	size_t sz;

public:
	class Iterator
	{
	public:
		Unit<T>* current;

		Iterator() : current(nullptr) {}

		Iterator(Unit<T>* unit) : current(unit) {}
		
		Iterator(const Unit<T>* unit) : current(const_cast<Unit<T>*>(unit)) {}
		
		Iterator(const Iterator& it)
		{
			current = it.current;
		}

		Unit<T>* get_current() const noexcept { return current; }

		Iterator& operator++()
		{
			current = current->next;
			return *this;
		}

		Iterator operator++(int)
		{
			Iterator tmp = *this;
			++(*this);
			return tmp;
		}

		T& operator*() 
		{
			return current->value;
		}

		const T& operator*() const
		{
			if (current != nullptr) return current->value;
			throw logic_error("is nullptr");
		}

		const bool operator==(const Iterator& it) const
		{
			return current == it.current;
		}

		const bool operator!=(const Iterator& it) const
		{
			return !(*this == it);
		}
	};

	List()
	{
		first = nullptr;
		sz = 0;
	}
	List(Unit<T>* first_, size_t sz_=1): first(first_), sz(sz_) {}
	
	List(const List<T>& list)
	{
		first = nullptr;
		sz = 0;
		if (this != &list) 
		{
			for (Iterator i = list.begin(); i != list.end(); ++i) 
			{
				push_back(*i);
			}
		}
	}

	~List()
	{
		this->clear();
	}

	void clear() 
	{
		while (first != nullptr)
		{
			Unit<T>* tmp = first;
			first = first->next;
			delete tmp;
		}
		sz = 0;
	}

	Unit<T>* get_first() const noexcept
	{
		return first;
	}

	size_t get_size() const noexcept
	{
		return sz;
	}

	typename List<T>::Iterator begin() noexcept
	{
		return Iterator(first);
	}
	typename List<T>::Iterator begin() const noexcept
	{
		return Iterator(first);
	}
	typename List<T>::Iterator end() noexcept
	{
		return Iterator();
	}
	typename List<T>::Iterator end() const noexcept
	{
		return Iterator();
	}

	void push_front(T val)
	{
		first = new Unit<T>(val, first);
	    ++sz;
	}

	void pop_front()
	{
		if (first == nullptr)
		{
			throw logic_error("List is empty");
		}
		Unit<T>* tmp = first;
		first = tmp->next;
		delete tmp;
		--sz;
	}

	void insert(T val, Unit<T>* unit)
	{
		if (unit == nullptr)
		{
			push_front(val);
		}
		else
		{
			unit->next = new Unit<T>(val, unit->next);
			++sz;
		}
	}

	void erase(Unit<T>* unit)
	{
		if (unit == nullptr)
		{
			pop_front();
		}
		else
		{
			Unit<T>* tmp = unit->get_next();
			if (tmp != nullptr)
			{
				unit->next = tmp->get_next();
				delete tmp;
				--sz;
			}
		}
	}

	Unit<T>* get_last() const
	{
		if (first == nullptr)
		{
			return nullptr;
		}
		Unit<T>* tmp = first;
		while (tmp->next != nullptr)
		{
			tmp = tmp->get_next();
		}
		return tmp;
	}

	void push_back(T val)
	{
		insert(val, this->get_last());
	}
};
