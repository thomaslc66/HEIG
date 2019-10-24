//
// Created by Whiterussian on 23.04.2017.
//

#ifndef POO2_LABO_03_LISTIMPL_H
#define POO2_LABO_03_LISTIMPL_H

template <typename T>
void DoublyLinkedList<T>::iniList() {
    _size = 0;
    _begin = nullptr;
    _end = nullptr;
}

template <typename T>
void DoublyLinkedList<T>::copyList(const DoublyLinkedList<T>& list) {
    Iterator curr = list.begin();
    while (curr != list.end()) {
        append(**curr);
        ++curr;
    }
}

template <typename T>
void DoublyLinkedList<T>::deleteList() {
    if(!isEmpty()) {
        Node<T> *curr = _begin;
        while (curr != _end) {
            Node<T> *tmp = curr;
            ++curr;
            delete tmp;
        }
        delete curr;

        iniList();
    }
}

template <typename T>
void DoublyLinkedList<T>::remove(const Node<T>* node) {
    if(!isEmpty() && node != nullptr) {
        if(node == _end) {
            node->prev->next = nullptr;
            _end = node->prev;
        }
        else if(node == _begin) {
            node->next->prev = nullptr;
            _begin = node->next;
        }
        else {
            node->next->prev = node->prev;
            node->prev->next = node->next;
        }

        delete node;

        --_size;
    }
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
    iniList();
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& o) : DoublyLinkedList() {
    *this = o;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    deleteList();
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& o) {
    if(this != &o) {
        deleteList();
        copyList(o);
    }
    return *this;
}

template <typename T>
T& DoublyLinkedList<T>::operator[](const unsigned short index) {
    return (**find(index));
}

template <typename T>
const short int DoublyLinkedList<T>::size() const {
    return _size;
}

template <typename T>
void DoublyLinkedList<T>::insert(const T& o) {
    Node<T>* tmp = new Node<T>(o);

    if(isEmpty()) {
        _begin = tmp;
        _end = tmp;
    }
    else {
        _begin->prev = tmp;
        tmp->next = _begin;
        _begin = tmp;
    }

    _size++;
}

template <typename T>
void DoublyLinkedList<T>::append(const T& o) {
    Node<T>* tmp = new Node<T>(o);

    if(isEmpty()) {
        _begin = tmp;
        _end = tmp;
    }
    else {
        _end->next = tmp;
        tmp->prev = _end;
        _end = tmp;
    }

    _size++;
}

template <typename T>
void DoublyLinkedList<T>::remove(const unsigned short index) {
    remove(&*find(index));
}

template <typename T>
void DoublyLinkedList<T>::remove(const T& o) {
    remove(&*find(o));
}

template <typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::begin() const {
    return Iterator(_begin);
}

template <typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::end() const {
    return nullptr;
}

template <typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::find(const unsigned short index) {
    if(index < _size) {
        Iterator curr = begin();
        for (unsigned short i = 0; i < index; i++) {
            ++curr;
        }
        return curr;
    }
}


template <typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::find(const T& o) {
    Iterator curr = begin();
    while (curr != end()) {
        if(**curr == o) {
            return curr;
        }
        ++curr;
    }
    return curr;
}

template <typename T>
bool DoublyLinkedList<T>::isEmpty() const {
    return _size < 1;
}

#endif //POO2_LABO_03_LISTIMPL_H
