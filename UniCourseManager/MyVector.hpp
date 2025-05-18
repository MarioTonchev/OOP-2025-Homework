//Mario Tonchev Tonchev 0MI0600460
#pragma once

#include <stdexcept>

template <typename T>

class MyVector {
private:
	T* items;
	int size;
	int capacity;
		
	void resize() {
		capacity *= 2;
		T* newItems = new T[capacity];

		for (size_t i = 0; i < size; i++)
		{
			newItems[i] = items[i];
		}

		delete[] items;
		items = newItems;
	}
public:
	MyVector() : size(0), capacity(4) {
		items = new T[capacity];
	};

	~MyVector() {
		delete[] items;
		items = nullptr;
		size = 0;
		capacity = 0;
	}

	MyVector(const MyVector& other) {
		size = other.size;
		capacity = other.capacity;
		items = new T[capacity];

		for (int i = 0; i < size; ++i) 
		{
			items[i] = other.items[i]; 
		}
	}

	MyVector& operator=(const MyVector& other) {
		if (this != &other) 
		{
			delete[] items;
			size = other.size;
			capacity = other.capacity;
			items = new T[capacity];

			for (int i = 0; i < size; ++i) 
			{
				items[i] = other.items[i];
			}
		}

		return *this;
	}

	T& operator[](int index) {
		if (index < 0 || index >= size)
		{
			throw std::out_of_range("Index is out of bounds!");
		}

		return items[index];
	}
	
	const T& operator[](int index) const {
		if (index < 0 || index >= size)
		{
			throw std::out_of_range("Index is out of bounds!");
		}

		return items[index];
	}

	void push_back(const T& element) {
		if (size >= capacity)
		{
			resize();
		}

		items[size++] = element;
	}
	void pop_back() {
		if (size == 0)
		{
			return;
		}

		size--;
	}
	void remove_at(int index) {
		size--;
		for (size_t i = index; i < size; i++)
		{
			items[i] = items[i + 1];
		}
	}

	int getSize() const {
		return size;
	}
	int getCapacity() const {
		return capacity;
	}
};
