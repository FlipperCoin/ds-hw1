//
// Created by Itai on 17/01/2021.
//

#ifndef _SHAREDPOINTER_H
#define _SHAREDPOINTER_H

template<typename T>
class SharedPointer
{
private:
    void dispose() {
        // if already disposed of
        if (ref_count == nullptr) return;

        if ((*ref_count)-- <= 1) {
            if (pointer != nullptr) {
                delete pointer;
            }
            delete ref_count;
        }
    }
public:
    explicit SharedPointer(T* pointer) : pointer(pointer), ref_count(new int(1)) {};

    SharedPointer() : pointer(nullptr), ref_count(new int(1)) {};

    ~SharedPointer() {
        dispose();
    }

    SharedPointer(const SharedPointer& other) {
        ref_count = other.ref_count;
        pointer = other.pointer;

        (*ref_count)++;
    }

    SharedPointer& operator=(const SharedPointer& other) {
        if (&other == this) {
            return *this;
        }

        dispose();

        ref_count = other.ref_count;
        pointer = other.pointer;

        (*ref_count)++;

        return *this;
    }

    bool operator==(const T* other) {
        return this->pointer == other;
    }

    bool operator==(const SharedPointer<T>& other) {
        return this->pointer == other.pointer;
    }

    T& operator*() {
        return *pointer;
    }
    const T& operator*() const{
        return *pointer;
    }
    T* operator->() {
        return pointer;
    }
    T* rawPointer() {
        return pointer;
    }
    const T* operator->() const {
        return pointer;
    }

    bool isEmpty() const {
        return pointer == nullptr;
    }


private:
    T* pointer;
    int* ref_count;
};

#endif
