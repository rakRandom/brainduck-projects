#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory.h>

template <typename T>
class vector {
public:
    /*
     *
     */
    vector();

    /* 
     * Creates a dynamic array with all elements at the default value.
     * Do not create any pointer to an element from this vector.
     */
    vector(size_t initial_length);

    /*
     *
     */
    ~vector();

    /* 
     * Replaces the old pointer with a new, bigger one.
     * Returns 1 if successful, 0 if not.
     */
    int grow(size_t size_to_add);

    /* 
     * Replaces the old pointer with a new, smaller one.
     * Returns 1 if successful, 0 if not.
     */
    int shrink(size_t size_to_remove);

    /* 
     * Set the element at the select index to the selected value.
     * If the element is not-null or equal to 0, the elements in its place and
     * in front of him will be moved foward until the last element takes the
     * index of a null element.
     * Returns 1 if was successful, 0 if was not.
     */
    int add(size_t index, T value);

    /* 
     * Set the null element in front of the not-null element closest 
     * to the end to the selected value.
     * If the array has not a null element at the end, it will grow the array 
     * by 1 and put the element at the end of the array.
     * Returns 1 if was successful, 0 if was not.
     */
    int append(T value);

    /* 
     * Set the element at the selected index to 0.
     * Returns 1 if the element was setted, 0 if was not.
     */
    int remove(size_t index);

    /*
     * Set the not-zero element closest to the end to 0.
     * Returns 1 if successful, 0 if not.
     */
    int pop();

    /* 
     * Returns a pointer that contains a copy of the array.
     * Returns NULL if the execution fails.
     * The pointer will be automatically freed when the vector is destroyed.
     */
    T* items();

    /*
     *
     */
    int copy(const T * other_pointer, size_t pointer_size);

    /* 
     * Set all values to 0.
     * Returns 1 if successful, 0 if not.
     */
    int empty();

    /* 
     * Set all elements to the selected value.
     * Returns 1 if successful, 0 if not.
     */
    int fill(T value);

    /* 
     * Returns the index closest to the start of a value.
     * Returns 0 if the value is not in the array.
     */
    size_t findex(T value);

    /* 
     * Returns the index closest to the end of a value.
     * Returns 0 if the value is not in the array.
     */
    size_t lindex(T value);

    /* 
     * Returns the nth index of a value.
     * Returns 0 if the value is not in the array.
     */
    size_t nindex(T value, size_t n);

    /* 
     * Returns how many times a value appears in the array.
     */
    size_t count(T value);

    /*
     * Set the element at the selected index to the selected value.
     * Returns 1 if the element was setted, 0 if was not.
     */
    int set(size_t index, T value);

    /*
     * Get the element at the selected index.
     * Returns the value of the element if the index was in 
     * the range of the array, 0 if was not.
     */
    T get(size_t index);

    /*
     *
     */
    int add_by_1(size_t index);

    /*
     *
     */
    int sub_by_1(size_t index);
    
    /*
     *
     */
    size_t length();

    /*
     *
     */
    size_t size_kB();

    /*
     *
     */
    size_t size_B();

    /*
     *
     */
    size_t size_b();
};

#endif // VECTOR_HPP
