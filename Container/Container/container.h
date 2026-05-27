#ifndef __CONTAINER_H
#define __CONTAINER_H

#include <iostream>
#include <stdexcept>
#include <algorithm>

template<typename T>
class container {
private:
    size_t size, capacity, step;
    T* elem;
    void reallocate();
public:
    container(size_t cp = 10, size_t st = 5);
    container(size_t cp, size_t st, const T& el);
    container(const container<T>& other);
    container(container<T>&& other) noexcept;
    ~container();
    

    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    const container<T>& operator=(const container<T>& other);
    container<T>& operator=(container<T>&& other) noexcept;
    
 
    int find(const T& el) const;
    void push(const T& el);
    void push(T&& el);
    void remove(const T& el);
    void remove(T&& el);
    

    size_t getSize() const { return size; }
    size_t getCapacity() const { return capacity; }
    bool isEmpty() const { return size == 0; }
    
    friend std::ostream& operator<<(std::ostream& out, const container<T>& b) {
      out << "size = " << b.size << " | capacity = " << b.capacity << " | step = " << b.step << "\n[";
      for (size_t i = 0; i < b.size; i++) {
        out << b.elem[i];
        if (i + 1 < b.size) out << ", ";
      }
      out << "]";
      return out;
    };
};



template<typename T>
container<T>::container(size_t cp, size_t st) 
    : size(0), capacity(cp), step(st) {
    elem = new T[capacity]();
}

template<typename T>
container<T>::container(size_t cp, size_t st, const T& el) 
    : capacity(cp), size(cp), step(st) {
    elem = new T[capacity]();
    for (size_t i = 0; i < size; i++) {
        elem[i] = el;
    }
}

template<typename T>
container<T>::container(const container<T>& other) 
    : size(other.size), capacity(other.capacity), step(other.step) {
    elem = new T[capacity]();
    for (size_t i = 0; i < size; i++) {
        elem[i] = other.elem[i];
    }
}

template<typename T>
container<T>::container(container<T>&& other) noexcept
    : size(other.size), capacity(other.capacity), step(other.step), elem(other.elem) {
    other.elem = nullptr;
    other.size = 0;
    other.capacity = 0;
}

template<typename T>
container<T>::~container() {
    delete[] elem;
}

template<typename T>
T& container<T>::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return elem[index];
}

template<typename T>
const T& container<T>::operator[](size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return elem[index];
}

template<typename T>
const container<T>& container<T>::operator=(const container<T>& other) {
    if (this == &other) return *this;
    
    if (this->capacity != other.capacity) {
      delete[] elem;

      size = other.size;
      capacity = other.capacity;
      step = other.step;
      elem = new T[capacity]();

      for (size_t i = 0; i < size; i++) {
        elem[i] = other.elem[i];
      }
      return *this;
    }
}

template<typename T>
container<T>& container<T>::operator=(container<T>&& other) noexcept {
    if (this == &other) return *this;
    
    delete[] elem;
    
    size = other.size;
    capacity = other.capacity;
    step = other.step;
    elem = other.elem;
    
    other.elem = nullptr;
    other.size = 0;
    other.capacity = 0;
    
    return *this;
}

template<typename T>
void container<T>::reallocate() {
    size_t new_capacity = capacity + step;
    T* buff = new T[new_capacity]();
    for (size_t i = 0; i < size; i++) {
        buff[i] = elem[i];
    }
    delete[] elem;
    elem = buff;
    capacity = new_capacity;
}

template<typename T>
int container<T>::find(const T& el) const {
    for (size_t i = 0; i < size; i++) {
        if (elem[i] == el) return static_cast<int>(i);
    }
    return -1;
}

template<typename T>
void container<T>::push(const T& el) {
    if (size == capacity) reallocate();
    elem[size++] = el;
}

//template<typename T>
//void container<T>::push(T&& el) { //?
//    if (size == capacity) reallocate();
//    elem[size++] = std::move(el);
//}

template<typename T>
void container<T>::remove(const T& el) {
    int pos = find(el);
    if (pos == -1) throw std::runtime_error("Element not found");
    elem[pos] = elem[--size];
}

template<typename T>
void container<T>::remove(T&& el) { //?
    int pos = find(el);
    if (pos == -1) throw std::runtime_error("Element not found");
    elem[pos] = std::move(elem[--size]);
}



template<typename T>
class container<T*> {
private:
    size_t size, capacity, step;
    T** elem;
    void reallocate();

public:
    container(size_t cp = 10, size_t st = 5);
    container(size_t cp, size_t st, T*& el);
    container(const container<T*>& other);
    container(container<T*>&& other) noexcept;
    ~container();
    
    T*& operator[](size_t index);
    const T*& operator[](size_t index) const;
    const container<T*>& operator=(const container<T*>& other);
    container<T*>& operator=(container<T*>&& other) noexcept;
    
    int find(const T* el) const; 
    void push(T* el);              
    void remove(const T* el);      
    
    size_t getSize() const { return size; }
    size_t getCapacity() const { return capacity; }
    bool isEmpty() const { return size == 0; }
    friend std::ostream& operator<<(std::ostream& out, const container<T*>& b) {
        out << "size = " << b.size << " | capacity = " << b.capacity << " | step = " << b.step << "\n____________\n";
        for (size_t i = 0; i < b.size; i++) {
            if (b.elem[i]) out << *b.elem[i];
            else out << "nullptr";
            out << '\n';
        }
        out << "____________";
        return out;
    }
};



template<typename T>
container<T*>::container(size_t cp, size_t st) 
    : size(0), capacity(cp), step(st) {
    elem = new T*[capacity]();
}

template<typename T>
container<T*>::container(size_t cp, size_t st, T*& el) 
    : capacity(cp), step(st), size(cp) {
    elem = new T*[capacity]();
    for (size_t i = 0; i < size; i++) {
        elem[i] = new T(*el);
    }
}

template<typename T>
container<T*>::container(const container<T*>& other) 
    : size(other.size), capacity(other.capacity), step(other.step) {
    elem = new T*[capacity]();
    for (size_t i = 0; i < size; i++) {
        if (other.elem[i]) elem[i] = new T(*other.elem[i]);
        else elem[i] = nullptr;
    }
}

template<typename T>
container<T*>::container(container<T*>&& other) noexcept
    : size(other.size), capacity(other.capacity), step(other.step), elem(other.elem) {
    other.elem = nullptr;
    other.size = 0;
    other.capacity = 0;
}

template<typename T>
container<T*>::~container() {
    for (size_t i = 0; i < size; i++) {
        delete elem[i];
    }
    delete[] elem;
}

template<typename T>
T*& container<T*>::operator[](size_t index) {
    if (index >= size) throw std::out_of_range("Index out of range");
    return elem[index];
}

template<typename T>
const T*& container<T*>::operator[](size_t index) const {
    if (index >= size) throw std::out_of_range("Index out of range");
    return elem[index];
}

template<typename T>
const container<T*>& container<T*>::operator=(const container<T*>& other) {
    if (this == &other) return *this;
    
    for (size_t i = 0; i < size; i++) delete elem[i];
    delete[] elem;
    
    size = other.size;
    capacity = other.capacity;
    step = other.step;
    elem = new T*[capacity]();
    
    for (size_t i = 0; i < size; i++) {
        if (other.elem[i]) elem[i] = new T(*other.elem[i]);
        else elem[i] = nullptr;
    }
    return *this;
}

template<typename T>
container<T*>& container<T*>::operator=(container<T*>&& other) noexcept {
    if (this == &other) return *this;
    
    for (size_t i = 0; i < size; i++) delete elem[i];
    delete[] elem;
    
    size = other.size;
    capacity = other.capacity;
    step = other.step;
    elem = other.elem;
    
    other.elem = nullptr;
    other.size = 0;
    other.capacity = 0;
    
    return *this;
}

template<typename T>
int container<T*>::find(const T* el) const {
    if (el == nullptr) return -1;
    for (size_t i = 0; i < size; i++) {
        if (elem[i] && *elem[i] == *el) return static_cast<int>(i);
    }
    return -1;
}

template<typename T>
void container<T*>::reallocate() {
    size_t new_capacity = capacity + step;
    T** buff = new T*[new_capacity]();
    for (size_t i = 0; i < size; i++) {
        buff[i] = elem[i];
    }
    delete[] elem;
    elem = buff;
    capacity = new_capacity;
}

template<typename T>
void container<T*>::push(T* el) {
    if (size == capacity) reallocate();
    elem[size++] = new T(*el);
}

template<typename T>
void container<T*>::remove(const T* el) {
    if (el == nullptr) throw std::runtime_error("Cannot remove nullptr");
    
    int pos = find(el);
    if (pos == -1) throw std::runtime_error("Element not found");
    
    delete elem[pos];
    elem[pos] = elem[--size];
    elem[size] = nullptr;
}

#endif