#ifndef CLASSES_VECTOR_CPP
#define CLASSES_VECTOR_CPP
#include "Vector.h"

template<typename T>
Vector<T>::Vector()
{
    this->_size = 0;
    this->_capacity = 0;
    this->arrPtr = nullptr;
}

template<typename T>
Vector<T>::Vector(int size)
{
    if (!isPositive(size))
    {
        throw std::invalid_argument("Error. Negative allocation. Enter positive sizes only.");
    }
    this->_size = size;
    this->_capacity = size;
    this->arrPtr = new T[this->_capacity]{T()};
}

template<typename T>
Vector<T>::Vector(int size, const T& defaultValue)
{
    if (!isPositive(size))
    {
        throw std::invalid_argument("Error. Negative allocation. Enter positive sizes only.");
    }
    this->_size = size;
    this->_capacity = size;
    this->arrPtr = new T[this->_capacity];
    for (int i = 0; i < this->_size; ++i)
    {
        *(this->arrPtr + i) = defaultValue;
    }
}

template<typename T>
Vector<T>::Vector(const Vector& otherVector)
{
    this->_size = otherVector._size;
    this->_capacity = otherVector._capacity;
    this->arrPtr = new T[this->_capacity];
    copyArr(otherVector.arrPtr);
}

template<typename T>
Vector<T>::Vector(const std::initializer_list<T>& list)
{
    this->_size = list.size();
    this->_capacity = this->_size;
    this->arrPtr = new T[this->_capacity];
    copyArr(list.begin());
}

template<typename T>
Vector<T>::~Vector()
{
    delete [] this->arrPtr;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& rightVector)
{
    if (&rightVector != this)
    {
        this->~Vector();
        this->_size = rightVector._size;
        this->_capacity = rightVector._capacity;
        this->arrPtr = new T[this->_capacity];
        copyArr(rightVector.arrPtr);
    }
    return *this;
}

template<typename T>
T& Vector<T>::operator[](int index)
{
    if (!inRange(index))
    {
        throw std::length_error("Error. Index out-of-bounds.");
    }
    return *(this->arrPtr + index);
}

template<typename T>
const T& Vector<T>::operator[](int index) const
{
    if (!inRange(index))
    {
        throw std::length_error("Error. Index out-of-bounds.");
    }
    return *(this->arrPtr + index);
}

template<typename T>
Vector<T>& Vector<T>::operator+=(const Vector& rightVector)
{
    int minSize = std::min(this->_size, rightVector._size);
    for (int i = 0; i < minSize; ++i)
    {
        *(this->arrPtr + i) += *(rightVector.arrPtr + i);
    }
    return *this;
}

template<typename T>
bool operator==(const Vector<T>& leftVector, const Vector<T>& rightVector)
{
    if (leftVector._size == rightVector._size)
    {
        for (int i = 0; i < leftVector._size; ++i)
        {
            if (leftVector.at(i) != rightVector.at(i))
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const Vector<T>& rightVector)
{
    out << "[";
    for (int i = 0; i < rightVector._size; ++i)
    {
        out << *(rightVector.arrPtr + i);
        if (i != rightVector._size - 1)
        {
            out << ", ";
        }
    }
    out << "]";
    return out;
}

template<typename T>
Vector<T> operator+(const Vector<T>& leftVector, const Vector<T>& rightVector)
{
    int minSize = std::min(leftVector._size, rightVector._size);
    int maxSize = std::max(leftVector._size, rightVector._size);
    Vector<T> newVector(maxSize);

    for (int i = 0; i < minSize; ++i)
    {
        *(newVector.arrPtr + i) = *(leftVector.arrPtr + i) + *(rightVector.arrPtr + i);
    }
    return newVector;
}

template<typename T>
void Vector<T>::push_back(const T& item)
{
    if(this->_size < this->_capacity)
    {
        *(this->arrPtr + this->_size) = item;
        ++this->_size;
    }
    else
    {
       resize();
       *(this->arrPtr + this->_size) = item;
       ++this->_size;
    }
}

template<typename T>
void Vector<T>::clear()
{
    delete [] this->arrPtr;
    this->_size = 0;
    this->arrPtr = new T[this->_capacity];
}

template<typename T>
void Vector<T>::insert(int index, const T& item)
{
    if (!inRange(index))
    {
        throw std::length_error("Error. Index out-of-bounds.");
    }
    if (this->_size < this->_capacity)
    {
        ++this->_size;
        shiftRight(index);
        *(this->arrPtr + index) = item;
    }
    else
    {
        resize();
        ++this->_size;
        shiftRight(index);
        *(this->arrPtr + index) = item;
    }

}

template<typename T>
void Vector<T>::remove(int index)
{
    if(!inRange(index))
    {
        throw std::length_error("Error. Index out-of-bounds.");
    }
    shiftLeft(index);
    --this->_size;
}

template<typename T>
T& Vector<T>::front()
{
    return *(this->arrPtr + 0);
}

template<typename T>
const T& Vector<T>::front() const
{
    return *(this->arrPtr + 0);
}

template<typename T>
T& Vector<T>::back()
{
    return *(this->arrPtr + this->_size - 1);
}

template<typename T>
const T& Vector<T>::back() const
{
    return *(this->arrPtr + this->_size - 1);
}

template<typename T>
T& Vector<T>::at(int index)
{
    if (!inRange(index))
    {
        throw std::length_error("Error. Index out-of-bounds.");
    }
    return *(this->arrPtr + index);
}

template<typename T>
const T& Vector<T>::at(int index) const
{
    if (!inRange(index))
    {
        throw std::length_error("Error. Index out-of-bounds.");
    }
    return *(this->arrPtr + index);
}

template<typename T>
int Vector<T>::size() const
{
    return this->_size;
}

template<typename T>
int Vector<T>::capacity() const
{
    return this->_capacity;
}

template<typename T>
bool Vector<T>::empty() const
{
    return this->_size == 0;
}

template<typename T>
void Vector<T>::resize()
{
    if (this->_capacity == 0)
    {
        this->_capacity = 1;
        this->arrPtr = new T[this->_capacity];
        return;
    }
    this->_capacity *= 2;
    T* oldArr = this->arrPtr;
    this->arrPtr = new T[this->_capacity]{T()};
    copyArr(oldArr);
    delete [] oldArr;
}

template<typename T>
void Vector<T>::shrink_to_fit()
{
    this->_capacity = this->_size;
    T* oldArr = this->arrPtr;
    this->arrPtr = new T[this->_capacity];
    copyArr(oldArr);
    delete [] oldArr;
}

template<typename T>
void Vector<T>::copyArr(const T* otherArr)
{
    for (int i = 0; i < this->_size; ++i)
    {
        *(this->arrPtr + i) = *(otherArr + i);
    }
}

template<typename T>
void Vector<T>::reserve(int capacitySize)
{
    if (!isPositive(capacitySize))
    {
        throw std::invalid_argument("Error. Negative allocation. Enter positive capacities only.");
    }
    if (capacitySize < this->_capacity)
    {
        return;
    }
    this->_capacity = capacitySize;
    T* temp = this->arrPtr;
    this->arrPtr = new T[this->_capacity];
    copyArr(temp);
    delete [] temp;
}

template<typename T>
bool Vector<T>::inRange(int index) const
{
    if (index >= 0 && index < this->_size)
    {
        return true;
    }
    return false;
}

template<typename T>
bool Vector<T>::isPositive(int size) const
{
    if (size < 0)
    {
        return false;
    }
    return true;
}

template<typename T>
void Vector<T>::shiftRight(int index)
{
    for (int i = this->_size - 1; i > index; --i)
    {
        *(this->arrPtr + i) = *(this->arrPtr + i - 1);
    }
}

template <typename T>
void Vector<T>::shiftLeft(int index)
{
    for (int i = index + 1; i < this->_size; ++i)
    {
        *(this->arrPtr + i - 1) = *(this->arrPtr + i);
    }
}

#endif //CLASSES_VECTOR_CPP