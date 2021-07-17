#ifndef NEDUCK_LINKARRAY_H
#define NEDUCK_LINKARRAY_H

#include <iostream>
#include <vector>

namespace neduck {
    template<typename T>
    class LinkArray {
    private:
        class LinkNode;
        
        LinkNode* head;
        LinkNode* tail;
        
        void init(std::vector<T>&);
        LinkNode* getNode(int, bool = true) const;
        LinkArray<T>& insertVector(const size_t, std::vector<T>&);

    public:
        class iterator;
        class reverse_iterator;

        //Constructor
        LinkArray(std::vector<T>&);
        template<size_t SIZE> LinkArray(const T(&)[SIZE]);
        
        //Deconstructor
        ~LinkArray();

        //Iterater Function
        iterator begin() const;
        iterator end() const;
        reverse_iterator rbegin() const;
        reverse_iterator rend() const;

        //Basic function
        bool isInbound(size_t) const;
        void print() const;
        int size() const;
        int find(T content) const;

        //Insert
        LinkArray<T>& insertAt(const size_t, T);
        LinkArray<T>& insertAt(const size_t, std::vector<T>);
        template<size_t SIZE> LinkArray<T>& insertAt(const size_t, const T(&)[SIZE]);

        //Destroy
        LinkArray<T>& destroyAt(const size_t, const size_t = 1) ;
        LinkArray<T>& destroy(T);


        //Operator
        T valueOf(size_t i) const;
        T operator[] (size_t i) const;
        T& operator[] (size_t i);
    };

    template<typename T>
    class LinkArray<T>::LinkNode {
    public:
        bool hasData = false;
        T data;
        LinkNode* prev = nullptr;
        LinkNode* next = nullptr;

        LinkNode() {};
        LinkNode(T d) :data(d) {
            hasData = true;
        };
    };

    template<typename T>
    class LinkArray<T>::iterator {
    private:
        LinkNode* _Ptr;
    public:
        iterator() {
            _Ptr = nullptr;
        }

        iterator(LinkNode* ptr) {
            _Ptr = ptr;
        }

        T& operator*() const {
            return _Ptr->data;
        }

        iterator operator++() {
            _Ptr = _Ptr->next;
            return *this;
        }

        iterator operator++(int) {
            iterator _Tmp = *this;
            _Ptr = _Ptr->next;
            return _Tmp;
        }

        iterator operator--() {
            _Ptr = _Ptr->prev;
            return *this;
        }

        iterator operator--(int) {
            iterator _Tmp = *this;
            _Ptr = _Ptr->prev;
            return _Tmp;
        }

        iterator& operator+=(size_t n) {
            for (size_t i = 0; i < n; i++) {
                _Ptr = _Ptr->next;
                if (!_Ptr->hasData) break;
            }
            return *this;
        }

        iterator operator+(size_t n) const {
            iterator _Tmp = *this;
            _Tmp += n;
            return _Tmp;
        }

        iterator& operator-=(size_t n) {
            for (size_t i = 0; i < n; i++) {
                _Ptr = _Ptr->prev;
                if (!_Ptr->hasData) break;
            }
            return *this;
        }

        iterator operator-(size_t n) const {
            iterator _Tmp = *this;
            _Tmp -= n;
            return _Tmp;
        }

        T operator[](const size_t n) const {
            return *(*this + n);
        }

        bool operator==(const iterator& _Right) const {
            return _Ptr == _Right._Ptr;
        }

        bool operator!=(const iterator& _Right) const {
            return !(_Ptr == _Right._Ptr);
        }
    };

    template<typename T>
    class LinkArray<T>::reverse_iterator {
    private:
        LinkNode* _Ptr;
    public:
        reverse_iterator() {
            _Ptr = nullptr;
        }

        reverse_iterator(LinkNode* ptr) {
            _Ptr = ptr;
        }

        T& operator*() const {
            return _Ptr->data;
        }

        reverse_iterator operator++() {
            _Ptr = _Ptr->prev;
            return *this;
        }

        reverse_iterator operator++(int) {
            reverse_iterator _Tmp = *this;
            _Ptr = _Ptr->prev;
            return _Tmp;
        }

        reverse_iterator operator--() {
            _Ptr = _Ptr->next;
            return *this;
        }

        reverse_iterator operator--(int) {
            reverse_iterator _Tmp = *this;
            _Ptr = _Ptr->next;
            return _Tmp;
        }

        reverse_iterator& operator+=(size_t n) {
            for (size_t i = 0; i < n; i++) {
                _Ptr = _Ptr->prev;
                if (!_Ptr->hasData) break;
            }
            return *this;
        }

        reverse_iterator operator+(size_t n) const {
            reverse_iterator _Tmp = *this;
            _Tmp += n;
            return _Tmp;
        }

        reverse_iterator& operator-=(size_t n) {
            for (size_t i = 0; i < n; i++) {
                _Ptr = _Ptr->next;
                if (!_Ptr->hasData) break;
            }
            return *this;
        }

        reverse_iterator operator-(size_t n) const {
            reverse_iterator _Tmp = *this;
            _Tmp -= n;
            return _Tmp;
        }

        T operator[](const size_t n) const {
            return *(*this + n);
        }

        bool operator==(const reverse_iterator& _Right) const {
            return _Ptr == _Right._Ptr;
        }

        bool operator!=(const reverse_iterator& _Right) const {
            return !(_Ptr == _Right._Ptr);
        }
    };
}
#include "linkarray.cpp.h"
#endif //NEDUCK_LINKARRAY_H