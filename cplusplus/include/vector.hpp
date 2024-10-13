#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory.h>

template <typename T>
class vector {
private:
    T *array_ptr;
    T *cpy_ptr;
    char cpy_updated = 0;
    size_t vec_length;
    size_t size;

public:
    /*
     *
     */
    vector() 
    {
        vec_length = 0;
        size = 0;
    }

    /* 
     * Creates a dynamic array with all elements at the default value.
     * Do not create any pointer to an element from this vector.
     */
    vector(size_t initial_length)
    {
        try {
            vec_length = initial_length;
            size = initial_length * sizeof(T);
            array_ptr = (T*) calloc(initial_length, sizeof(T));

            if (array_ptr == NULL) 
                throw size;
        }

        catch (size_t &bytes) {
            std::cout << "Error: memory allocation was not possible." << std::endl;
            std::cout << "Bytes to allocate: " << bytes << std::endl;
            vec_length = 0;
            size = 0;
            free(array_ptr);
            free(cpy_ptr);
        }
    }

    /*
     *
     */
    ~vector()
    {
        vec_length = 0;
        size = 0;
        free(array_ptr);
        free(cpy_ptr);
    }

    /* 
     * Replaces the old pointer with a new, bigger one.
     * Returns 1 if successful, 0 if not.
     */
    int grow(size_t size_to_add)
    {
        size_t dest_size = size + size_to_add * sizeof(T);

        // memcpy_s error conditions test #1
        if (dest_size <= size || array_ptr == NULL)
            return 0;

        T *new_ptr = (T*) calloc(vec_length + size_to_add, sizeof(T));
        
        // memcpy_s error conditions test #2
        if (new_ptr == NULL)
            return 0;
        
        // Copying the array from the old pointer to the new one
        if (memcpy_s(
                new_ptr,
                dest_size,
                array_ptr,
                size
            ) != 0)
            return 0;

        // Replacing the old array pointer with the new one, deleting the old array
        free(array_ptr);
        array_ptr = new_ptr;

        cpy_updated = 0;
        vec_length += size_to_add;
        size = dest_size;

        return 1;
    }

    /* 
     * Replaces the old pointer with a new, smaller one.
     * Returns 1 if successful, 0 if not.
     */
    int shrink(size_t size_to_remove)
    {
        // Test if the size to remove is greater or equal to the current size (length)
        if (size_to_remove >= vec_length)
            return 0;
        
        size_t dest_size = size - size_to_remove * sizeof(T);

        // memcpy_s error conditions test #1
        if (dest_size >= size || array_ptr == NULL)
            return 0;

        T *new_ptr = (T*) calloc(vec_length - size_to_remove, sizeof(T));
        
        // memcpy_s error conditions test #2
        if (new_ptr == NULL)
            return 0;
        
        // Copying the array from the old pointer to the new one
        if (memcpy_s(
                new_ptr,
                dest_size,
                array_ptr,
                dest_size
            ) != 0)
            return 0;
        
        // Replacing the old array pointer with the new one, deleting the old array
        free(array_ptr);
        array_ptr = new_ptr;

        cpy_updated = 0;
        vec_length -= size_to_remove;
        size = dest_size;

        return 1;
    }

    /* 
     * Set the element at the select index to the selected value.
     * If the element is not-null or equal to 0, the elements in its place and
     * in front of him will be moved foward until the last element takes the
     * index of a null element.
     * Returns 1 if was successful, 0 if was not.
     */
    int add(size_t index, T value)
    {
        // Checking if the index is in the vector range
        if (index >= vec_length || 0 > index)
            return 0;
        
        // Path #1, null
        if (array_ptr[index] == 0) {
            array_ptr[index] = value;
            cpy_updated = 0;
            return 1;
        }
        
        // Path #2, not null, last index
        if (!(array_ptr[index] == 0) && index == vec_length - 1) {
            if (grow(1)) {
                array_ptr[index + 1] = value;
                cpy_updated = 0;
                return 1;
            }
            else return 0;
        }
        
        // Todo: Path #3, not null, not last index
        if (!(array_ptr[index] == 0) && index != vec_length - 1)
            return 0;

        return 0;
    }

    /* 
     * Set the null element in front of the not-null element closest 
     * to the end to the selected value.
     * If the array has not a null element at the end, it will grow the array 
     * by 1 and put the element at the end of the array.
     * Returns 1 if was successful, 0 if was not.
     */
    int append(T value)
    {
        for (size_t i = vec_length - 1; i >= 0; i--) {
            if (array_ptr[i] != 0 && i < vec_length - 1) {
                array_ptr[i+1] = value;
                return 1;
            }
            
            else if (array_ptr[i] != 0 && i == vec_length - 1) {
                if(grow(1)) {
                    array_ptr[i+1] = value;
                    cpy_updated = 0;
                    return 1;
                }
                else return 0;
            }
        }
        return 0;
    }

    /* 
     * Set the element at the selected index to 0.
     * Returns 1 if the element was setted, 0 if was not.
     */
    int remove(size_t index)
    {
        cpy_updated = 0;
        return set(index, 0);
    }

    /*
     * Set the not-zero element closest to the end to 0.
     * Returns 1 if successful, 0 if not.
     */
    int pop()
    {
        for (size_t i = vec_length - 1; i >= 0; i--)
            if (array_ptr[i] != 0) {
                array_ptr[i] = 0;
                cpy_updated = 0;
                return 1;
            }
        
        return 0;
    }

    /* 
     * Returns a pointer that contains a copy of the array.
     * Returns NULL if the execution fails.
     * The pointer will be automatically freed when the vector is destroyed.
     */
    T* items()
    {
        // If the copy pointer is already updated, just return it
        if (cpy_updated)
            return cpy_ptr;

        // memcpy_s error conditions test #1
        if (array_ptr == NULL)
            return NULL;

        if (cpy_ptr != NULL)
            free(cpy_ptr);
        
        cpy_ptr = (T*) calloc(vec_length, sizeof(T));
        
        // memcpy_s error conditions test #2
        if (cpy_ptr == NULL)
            return NULL;
        
        // Copying the array from original pointer to the copy
        if (memcpy_s(
                cpy_ptr,
                size,
                array_ptr,
                size
            ) != 0)
            return NULL;

        cpy_updated = 1;
        return cpy_ptr;
    }

    /*
     *
     */
    int copy(const T * other_pointer, size_t pointer_size)
    {
        // memcpy_s error conditions test #1
        if (array_ptr == NULL || other_pointer == NULL)
            return 0;

        // memcpy_s error conditions test #2
        if (pointer_size > size)
            pointer_size = size;
        
        // Copying the array from original pointer to the copy
        if (memcpy_s(
                array_ptr,
                size,
                other_pointer,
                pointer_size
            ) != 0)
            return 0;
        
        return 1;
    }

    /* 
     * Set all values to 0.
     * Returns 1 if successful, 0 if not.
     */
    int empty()
    {
        // Setting all values to 0
        for (size_t i = 0; i < vec_length; i++) {
            array_ptr[i] = 0;

            // Testing if the element was properly setted to 0, returns 0 if the value is not 0
            if (array_ptr[i] != 0)
                return 0;
        }
        
        cpy_updated = 0;
        return 1;
    }

    /* 
     * Set all elements to the selected value.
     * Returns 1 if successful, 0 if not.
     */
    int fill(T value)
    {
        // Setting all values
        for (size_t i = 0; i < vec_length; i++) {
            array_ptr[i] = value;

            // Testing if the element was properly setted, returns 0 if was not
            if (array_ptr[i] != value)
                return 0;
        }
        
        cpy_updated = 0;
        return 1;
    }

    /* 
     * Returns the index closest to the start of a value.
     * Returns 0 if the value is not in the array.
     */
    size_t findex(T value)
    {
        for (size_t i = 0; i < vec_length; i++)
            if (array_ptr[i] == value)
                return i;
        return 0;
    }

    /* 
     * Returns the index closest to the end of a value.
     * Returns 0 if the value is not in the array.
     */
    size_t lindex(T value)
    {
        for (size_t i = vec_length - 1; i >= 0; i--)
            if (array_ptr[i] == value)
                return i;
        return 0;
    }

    /* 
     * Returns the nth index of a value.
     * Returns 0 if the value is not in the array.
     */
    size_t nindex(T value, size_t n)
    {
        size_t found = 0;
        
        for (size_t i = 0; i < vec_length; i++)
            if (array_ptr[i] == value) {
                found++;
                if (found == n)
                    return i;
            }
        
        return 0;
    }

    /* 
     * Returns how many times a value appears in the array.
     */
    size_t count(T value)
    {
        size_t c = 0;

        for (size_t i = 0; i < vec_length; i++)
            if (array_ptr[i] == value)
                c++;

        return c;
    }

    /*
     * Set the element at the selected index to the selected value.
     * Returns 1 if the element was setted, 0 if was not.
     */
    int set(size_t index, T value)
    {
        if (index < vec_length && index >= 0) {
            array_ptr[index] = value;
            cpy_updated = 0;
            return 1;
        }
        else return 0;
    }

    /*
     * Get the element at the selected index.
     * Returns the value of the element if the index was in 
     * the range of the array, 0 if was not.
     */
    T get(size_t index)
    {
        if (index < vec_length && index >= 0)
            return array_ptr[index];
        else return (T) 0;
    }

    /*
     *
     */
    int add_by_1(size_t index)
    {
        if (index < vec_length && index >= 0) {
            array_ptr[index]++;
            cpy_updated = 0;
            return 1;
        }
        else return 0;
    }

    /*
     *
     */
    int sub_by_1(size_t index)
    {
        if (index < vec_length && index >= 0) {
            array_ptr[index]--;
            cpy_updated = 0;
            return 1;
        }
        else return 0;
    }
    
    /*
     *
     */
    size_t length() {
        return vec_length;
    }

    /*
     *
     */
    size_t size_kB() {
        return size / 1024;
    }

    /*
     *
     */
    size_t size_B() {
        return size;
    }

    /*
     *
     */
    size_t size_b() {
        return size * 8;
    }
};

#endif // VECTOR_HPP
