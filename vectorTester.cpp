#include <iostream>
#include "Vector.h"
#include <vector>

template<typename T>
void printVector(const T& v);

template<typename T>
void print2DVector(const T& v);

template <typename T>
void printVectorAttributes(const T& v);

template<typename T>
void fillVector(T& v, int seed);

void testDefaultVector();
void testSingleParamVector();

int main()
{
    testDefaultVector();
    testSingleParamVector();
    std::cout << "\nTesting 2D Vector...\n=========================\n";
    Vector<Vector<std::string>> TWO_D;
    TWO_D.push_back(Vector<std::string>(5, "00"));
    TWO_D.push_back(Vector<std::string>(5, "11"));
    TWO_D.push_back(Vector<std::string>(5, "22"));
    TWO_D.push_back(Vector<std::string>(5, "33"));
    TWO_D.push_back(Vector<std::string>(5, "44"));
    print2DVector(TWO_D);
    std::cout << "\nTesting bootleg Vector against a real vector\n=================================\n";
    Vector<int> bootLegVector = Vector<int>(10,10);
    bootLegVector = {10,9,8};
    std::vector<int> realVector = {10,9,8,7,6,5,4,3,2,1};
    bootLegVector.reserve(100);
    realVector.reserve(100);
    bootLegVector.shrink_to_fit();
    realVector.shrink_to_fit();
    printVectorAttributes(bootLegVector);
    std::cout << bootLegVector << "\n";
    printVectorAttributes(realVector);
    Vector<int> bootLegSum = bootLegVector + Vector<int>({1,2,3,4,5,6,7,8});
    std::cout << bootLegSum << "\n";
    printVectorAttributes(bootLegSum);
    printVector(realVector);
    std::cout << "\n";
    return 0;
}

template<typename T>
void printVector(const T& v)
{
    std::cout << "Vector Contents\n============================\n";
    std::cout << "[";
    for(int i = 0; i < v.size(); ++i)
    {
        std::cout << v.at(i);
        if (i != v.size() - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << "]";
}

template<typename T>
void print2DVector(const T& v)
{
    std::cout << "Vector Contents\n=============================\n";
    for (int i = 0; i < v.size(); ++i)
    {
        std::cout << v.at(i) << "\n";
    }
}

template<typename T>
void printVectorAttributes(const T& v)
{
    std::cout << "Vector Attributes\n==============================\n";
    std::cout << "Vector Size: " << v.size() << "\n";
    std::cout << "Vector Capacity: " << v.capacity() << "\n";
    if (v.empty())
    {
        std::cout << "Vector is empty!\n";
    }
    else
    {
        std::cout << "Front: " << v.front() << "\n";
        std::cout << "Back: " << v.back() << "\n";
    }
}

template<typename T>
void fillVector(T& v, int seed)
{
    for (int i = 0; i < v.size(); ++i)
    {
        v[i] = seed + i;
    }
}

void testDefaultVector()
{
    std::cout << "Testing Default Constructed Vector...\n";
    Vector<int> v1;
    printVectorAttributes(v1);
    std::cout << "\n";
    printVector(v1);
    std::cout << "\nAfter reserving a capacity of 10 elements...\n";
    v1.reserve(10);
    printVectorAttributes(v1);
    std::cout << "\n";
    printVector(v1);
    std::cout << "\n\nAfter pushing 3 elements into the Vector...\n";
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    printVectorAttributes(v1);
    std::cout << "\n";
    printVector(v1);
    std::cout << "\n\nAfter shrinking the capacity to fit the size...\n";
    v1.shrink_to_fit();
    printVectorAttributes(v1);
    std::cout << "\n";
    printVector(v1);
    std::cout << "\n";
}

void testSingleParamVector()
{
    std::cout << "\nTesting Single Parameter Constructed Vector (Size = 10)...\n";
    Vector<int> v1(10);
    printVectorAttributes(v1);
    std::cout << "\n";
    printVector(v1);
    std::cout << "\n\nAfter reserving a capacity of 20 elements...\n";
    v1.reserve(20);
    printVectorAttributes(v1);
    std::cout << "\n";
    printVector(v1);
    std::cout << "\n\nAfter pushing 3 elements into the Vector...\n";
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    printVectorAttributes(v1);
    std::cout << "\n";
    printVector(v1);
    std::cout << "\nA\nfter shrinking the capacity to fit the size...\n";
    v1.shrink_to_fit();
    printVectorAttributes(v1);
    std::cout << "\n";
    printVector(v1);
    std::cout << "\n";
}