//
// Created by Thomas on 06.04.2018.
//

#ifndef DLINKEDLIST_NODEIMPL_H
#define DLINKEDLIST_NODEIMPL_H


template <typename T>
Node<T>::Node(const T& data): data(data) {
    _next = nullptr;
    _prev = nullptr;
}

template <typename T>
Node<T>::Node(const T &data, Node <T> *prev, Node <T> *next) : data(data), _prev(prev), _next(next) {}

template <typename T>
T& Node<T>::operator*(){
    return data;
}

template<typename T>
Node<T>& Node<T>::operator++() {
    return *_next;
}

template<typename T>
Node<T>& Node<T>::operator--() {
    return *_prev;
}

template<typename T>
T& Node<T>::getData() {
    return data;
}

template<typename T>
Node<T>* Node<T>::ptrSurNext() {
    return _next;
}

template<typename T>
Node<T>& Node<T>::refSurNext() {
    return *_next;
}

template<typename T>
void Node<T>::setNext(Node<T> *ptr){
    _next = ptr;
}

template<typename T>
void Node<T>::setPrev(Node<T> *ptr){
    _prev = ptr;
}


template<typename T>
Node<T>& Node<T>::refSurPrev() {
    return *_prev;
}

template<typename T>
Node<T>* Node<T>::ptrSurPrev() {
    return _prev;
}

template<typename T>
Node<T>& Node<T>::operator = (const Node<T>* noeud) {
    if(this != noeud){
        _prev = noeud->_prev;
        _next = noeud->_prev;
        data = noeud->data;
    }
    return *this;
}

#endif //DLINKEDLIST_NODEIMPL_H
