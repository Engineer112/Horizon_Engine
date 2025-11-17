//
// Created by Hosea on 11/16/2025.
//

#pragma once
#include <cstdlib>

template<typename T>
struct Vector {
    size_t size;
    size_t capacity;
    T* data = nullptr;
};

// -- lifetime --
template<typename T>
bool Vector_Init(Vector<T> &vector, size_t capacity) {
    if (vector.data)
        free(vector.data);
    vector.data = static_cast<T *>(malloc(capacity * sizeof(T)));
    if (!vector.data)
        return false;
    vector.capacity = capacity;
    vector.size = 0;
    return true;
}

template<typename T>
void Vector_Free(Vector<T> &vector) {
    free(vector.data);
}

// -- Memory Ops --
template<typename T>
bool Vector_Reserve(Vector<T> &vector, const size_t newMinCapacity) {
    if (newMinCapacity <= vector.capacity)
        return true;
    void* newData = realloc(vector.data, newMinCapacity * sizeof(T));
    if (!newData) return false;
    vector.data = static_cast<T *>(newData);
    vector.capacity = newMinCapacity;
    return true;
}

template<typename T>
void Vector_Clear(Vector<T> &vector) {
    vector.size = 0;
}

// -- vector ops --
template<typename T>
bool Vector_PushBack(Vector<T> &vector, const T &value) {
    if (!vector.data)
        return false;
    if (vector.size >= vector.capacity) {
        if (!Vector_Reserve(vector, vector.capacity * 2))
            return false;
    }
    vector.data[vector.size++] = value;
    return true;
}

template<typename T>
inline bool Vector_PopBack(Vector<T>& vector) {
    if (!vector.data && vector.size > 0) {
        return false;
    }
    --vector.size;
    return true;
}

template<typename T>
bool Vector_PopBack(Vector<T> &vector, T &out) {
    const bool result = Vector_PopBack(vector);
    out = vector.data[vector.size];
    return result;
}

template<typename T>
bool Vector_At(Vector<T> &vector, size_t index, T &value) {
    if (index >= vector.size && !vector.data)
        return false;
    value = vector.data[index];
    return true;
}

template<typename T>
bool Vector_Front(Vector<T> &vector, T*& out) {
    if (vector.size == 0) {
        out = nullptr;
        return false;
    }
    out = &vector.data[0];
    return true;
}

template<typename T>
bool Vector_Back(Vector<T>& vector, T*& value) {
    if (vector.size == 0) {
        value = nullptr;
        return false;
    }
    value = &vector.data[vector.size - 1];
    return true;
}
