#ifndef NEDUCK_LINKARRAY_CPP
#define NEDUCK_LINKARRAY_CPP

#include "linkarray.h"

namespace neduck {

#pragma region "Constructor"

    template<typename T>
    void LinkArray<T>::init(std::vector<T> &arr) {
            size_t arrSize = arr.size();
            head = new LinkNode;
            LinkNode* last = head;

#ifdef DEBUG
            std::cout << "[DEBUG] Initialize: Link Array Addr: {" << head;
#endif
            for (int i = 0; i < arrSize; i++) {
                LinkNode* node = new LinkNode(arr[i]);
#ifdef DEBUG
                std::cout << ", " << node;
#endif
                node->prev = last;
                last->next = node;
                last = node;
            }
            tail = new LinkNode;
            last->next = tail;
            tail->prev = last;
#ifdef DEBUG
            std::cout << ", " << tail << "}";
            std::cout << std::endl;
#endif
        }

    template<typename T>
    LinkArray<T>::LinkArray(std::vector<T> &arr) {
        init(arr);
    }
    
    template<typename T>
    template<size_t SIZE>
    LinkArray<T>::LinkArray(const T (&arr)[SIZE]) {
        std::vector<T> vec;
        vec.assign(arr, arr+SIZE);
        init(vec);
    }
#pragma endregion

#pragma region "Deconstructor"
    template<typename T>
    LinkArray<T>::~LinkArray() {
        LinkNode* nodeptr = this->head;
        LinkNode* _nodeptr;
#ifdef DEBUG
        std::cout << "[DEBUG] Deconstruct: Link Node Addr: {";
#endif
        while (nodeptr) {
            _nodeptr = nodeptr->next;
#ifdef DEBUG
            std::cout << nodeptr;
            if (_nodeptr) std::cout << ", ";
#endif
            delete nodeptr;
            nodeptr = _nodeptr;
        }
#ifdef DEBUG
        std::cout << "}" << std::endl;
#endif
    }

#pragma endregion

#pragma region "Iterater Function"
    template<typename T>
    typename LinkArray<T>::iterator LinkArray<T>::begin() const {
        return iterator(head->next);
    }
    
    template<typename T>
    typename LinkArray<T>::iterator LinkArray<T>::end() const {
        return iterator(tail);
    }
    
    template<typename T>
    typename LinkArray<T>::reverse_iterator LinkArray<T>::rbegin() const {
        return reverse_iterator(tail->prev);
    }

    template<typename T>
    typename LinkArray<T>::reverse_iterator LinkArray<T>::rend() const {
        return reverse_iterator(head);
    }
#pragma endregion

#pragma region "Basic Function"
    template<typename T>
    typename LinkArray<T>::LinkNode* LinkArray<T>::getNode(int index, bool canReverse) const {
        LinkNode* nodeptr;
        int sign = (index > 0) - (index < 0);

        if (sign == -1) index = -index;

        if (canReverse && sign == -1) {
            index--;
            nodeptr = tail->prev;
        }
        else {
            nodeptr = head->next;
        }

        while (index > 0 && nodeptr != head && nodeptr != tail) {
            index--;
            nodeptr = (sign == 1)?nodeptr->next:nodeptr->prev;
        }

        
#ifdef DEBUG
        std::cout << "[DEBUG] Get: Link Array Addr:" << nodeptr << std::endl;
#endif

        return nodeptr;
    }

    template<typename T>
    bool LinkArray<T>::isInbound(size_t index) const {
        return (index >= 0 && index < size());
    };

    template<typename T>
    void LinkArray<T>::print() const {
        LinkNode* nodeptr = head->next;
        LinkNode* _nodeptr;
        
        std::cout << "{";
        std::cout << nodeptr->data;
        while ((nodeptr = nodeptr->next) != tail) {
            std::cout << ", " << nodeptr->data;
        }
        std::cout << "}" << std::endl;
    }
    
    template<typename T>
    int LinkArray<T>::size() const {
        LinkNode* node = head->next;
        int size = 0;
        while (node != tail) {
            size++;
            node = node->next;
        }
        return size;
    }

    template<typename T>
    int LinkArray<T>::find(T content) const {
        int i = 0;
        for (LinkArray<T>::iterator iter = begin(); iter != end(); iter++) {
            if (*iter == content) {
                break;
            }
            i++;
        }
        if (i == size()) i = -1;
        return i;
    }
#pragma endregion

#pragma region "Insert"
    template<typename T>
    LinkArray<T>& LinkArray<T>::insertVector(const size_t index, std::vector<T> &arr) {
        size_t arrSize = arr.size();

        if (index < 0 || index > size()) {      
#ifdef WARNING
            std::cout << "[Warning] Insert: Out of bound: LinkArray[" << index << "]" << std::endl;
#endif
            return *this;
        }
        
        LinkNode* prevNode = getNode(index-1, false);
        LinkNode* first;
        LinkNode* last;
#ifdef DEBUG
        std::cout << "[DEBUG] Insert: Link Array Addr: {";
#endif

        for (int i = 0; i < arrSize; i++) {
            LinkNode* node = new LinkNode(arr[i]);
            if (i == 0) {
                first = node;
                last = node;
            }
#ifdef DEBUG
            std::cout << node;
            if (i+1 < arrSize) std::cout << ", ";
#endif

            node->prev = last;
            last->next = node;
            last = node;
        }
#ifdef DEBUG
        std::cout << "}" << std::endl;
#endif
        first->prev = prevNode;
        prevNode->next->prev = last;
        last->next = prevNode->next;
        prevNode->next = first;
        
        return *this;
    }

    template<typename T>
    LinkArray<T>& LinkArray<T>::insertAt(const size_t index, T data) {

        if (index < 0 || index > size()) {     
#ifdef WARNING
            std::cout << "[Warning] Insert: Out of bound: LinkArray[" << index << "]" << std::endl;
#endif
            return *this;
        }

        LinkNode* node = new LinkNode(data);
        LinkNode* prevNode = getNode(index-1, false);

        node->prev = prevNode;
        prevNode->next->prev = node;
        node->next = prevNode->next;
        prevNode->next = node;

        return *this;
    }
    
    template<typename T>
    LinkArray<T>& LinkArray<T>::insertAt(const size_t index, std::vector<T> arr) {
        return insertVector(index, arr);
    }

    template<typename T>
    template<size_t SIZE>
    LinkArray<T>& LinkArray<T>::insertAt(const size_t index, const T (&arr)[SIZE]) {
        std::vector<T> vec;
        vec.assign(arr, arr+SIZE);
        return insertVector(index, vec);
    }
#pragma endregion

#pragma region "Destroy"
    template<typename T>
    LinkArray<T>& LinkArray<T>::destroyAt(const size_t index, const size_t amount) {
        
        if (!isInbound(index)) {      
#ifdef WARNING
            std::cout << "[Warning] Destroy: Out of bound: LinkArray[" << index << "]" << std::endl;
#endif
            return *this;
        }
        
        LinkNode* prevNode = getNode(index-1, false);
        LinkNode* node = prevNode->next;
        LinkNode* nextNode = node;
        if (node->hasData) {
#ifdef DEBUG
            std::cout << "[DEBUG] Destroy: Link Array Addr: {";
#endif
            for (int i = 0; i < amount; i++) {
                if (!node->hasData) break;

                nextNode = node->next;
#ifdef DEBUG
                std::cout << node;
                if (nextNode->hasData && i+1 < amount) std::cout << ", ";
#endif

                delete node;

                node = nextNode;
            }
#ifdef DEBUG
            std::cout << "}" << std::endl;
#endif

            prevNode->next = nextNode;
            nextNode->prev = prevNode;
        }

        return *this;
    }

    template<typename T>
    LinkArray<T>& LinkArray<T>::destroy(T content) {
        int index;
        if ((index = find(content)) != -1) {
            LinkNode* node = getNode(index);
            node->prev->next = node->next;
            node->next->prev = node->prev;

#ifdef DEBUG
            std::cout << "[DEBUG] Destroy: Link Array Addr: {" << node << "}" << std::endl;
#endif
            delete node;
        }

        return *this;
    }
#pragma endregion

#pragma region "Operator"
    template<typename T>
    T LinkArray<T>::valueOf(size_t i) const { return getNode(i)->data; }

    // getter
    template<typename T>
    T LinkArray<T>::operator[] (size_t i) const { return getNode(i)->data; }
    // setter
    template<typename T>
    T& LinkArray<T>::operator[] (size_t i) { return getNode(i)->data; }
#pragma endregion
}
#endif //NEDUCK_LINKARRAY_CPP