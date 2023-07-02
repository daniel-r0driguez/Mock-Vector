// Daniel Rodriguez - CS003A
// In-Class Labs
#ifndef CLASSES_VECTOR_H
#define CLASSES_VECTOR_H
#include <iostream>
#include <stdexcept>
#include <initializer_list>

template<typename T>
class Vector;

template<typename T>
bool operator==(const Vector<T>& leftVector, const Vector<T>& rightVector);

template<typename T>
std::ostream& operator<<(std::ostream& out, const Vector<T>& Vector);

template<typename T>
Vector<T> operator+(const Vector<T>& leftVector, const Vector<T>& rightVector);

template<typename T>
class Vector{
private:
    int _size = 0;
    int _capacity = 0;
    T* arrPtr = nullptr;

public:
    // Default constructor
    Vector();
    // Constructs a Vector object with an initial size and sets elements to 0 of the appropriate value type.
    explicit Vector(int size);
    // Constructs a Vector object with an initial size and sets elements to a passed in default value.
    Vector(int size, const T& defaultValue);
    // Copy Constructor which creates a new Vector object whose elements are equal to the passed in Vector object.
    Vector(const Vector& otherVector);
    // Constructor which copies the data from an initializer list.
    Vector(const std::initializer_list<T>& list);
    // Destructor. Frees any allocated memory.
    ~Vector();

    // Operators
    // Assignment operator. Causes the invoked Vector's values to be equal to that of the Vector object on the right.
    Vector& operator=(const Vector& rightVector);
    // Array-Notation operator. Returns a reference of the nth element in the Vector.
    T& operator[](int index);
    // Returns a constant reference of the nth element in the Vector.
    const T& operator[](int index) const;
    // Plus-Equals operator. The Vector on the left has its values incremented by the Vector's values on the right.
    Vector& operator+=(const Vector& rightVector);
    // Equality operator. Checks if two Vectors of the same base type are the same (Same size and values).
    friend bool operator==<T>(const Vector& leftVector, const Vector& rightVector);
    // Insertion operator. Prints the entire Vector object out to a stream.
    friend std::ostream& operator<< <T>(std::ostream& out, const Vector& rightVector);
    // Addition operator. Returns a new Vector object whose elements are the sum of the left and right Vector.
    friend Vector<T> operator+<T>(const Vector<T>& leftVector, const Vector<T>& rightVector);

    // Modifiers
    // Appends a new item at the end of the Vector.
    void push_back(const T& item);
    // Clears all the contents of the Vector. The capacity of the Vector remains unchanged.
    void clear();
    // Inserts a new item into the Vector. This causes any elements on the right of the index to be moved to the right.
    // Automatic reallocation will take place if the size == capacity.
    void insert(int index, const T& item);
    // Removes an element from the Vector. This causes any elements on the right of index to be moved to the left.
    void remove(int index);


    // Element accessors
    // Returns a reference to the first element in the Vector.
    T& front();
    // Returns a constant reference to the  first element in the Vector.
    const T& front() const;
    // Returns a reference to the last element in the Vector.
    T& back();
    // Returns a constant reference to the last element in the Vector.
    const T& back() const;
    // Returns a reference of nth element of the Vector.
    T& at(int index);
    // Returns a constant reference of the nth element of the Vector.
    const T& at(int index) const;

    // Vector capacity
    // Returns the current size of the Vector (The number of elements used).
    [[nodiscard]] int size() const;
    // Returns true if the size of the Vector is 0, false otherwise.
    [[nodiscard]] bool empty() const;
    // Returns the current capacity of the Vector (How many elements it can hold).
    [[nodiscard]] int capacity() const;
    // Allocates more capacity (memory) for the Vector.
    // If the desired capacity is less than the current capacity, no operations are done.
    void reserve(int capacitySize);
    // Shrinks the capacity of the Vector to fit the size, essentially freeing unused slots of the Vector.
    void shrink_to_fit();
    // insertion operator, optional( += ) operator

private:
    // Doubles the Vector's capacity if the size has reached the capacity.
    void resize();
    // Fills the Vector's current dynamic array's values with that of another dynamic array's values.
    void copyArr(const T* otherArr);
    // Helper function which checks if an index is range of the Vector's size (0 to this->_size - 1).
    [[nodiscard]] bool inRange(int index) const;
    // Helper function which checks if a desired size is of positive value.
    [[nodiscard]] bool isPositive(int size) const;
    void shiftRight(int index);
    void shiftLeft(int index);
};

#include "Vector.cpp"
#endif //CLASSES_VECTOR_H