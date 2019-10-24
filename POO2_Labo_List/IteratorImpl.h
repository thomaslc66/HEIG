//
// Created by Thomas on 06.04.2018.
//

#ifndef DLINKEDLIST_ITERATORIMPL_H
#define DLINKEDLIST_ITERATORIMPL_H


template<typename N>
Iterator<N>& Iterator<N>::operator++() {
    ptr = ptr->_next;
    return *this;
}

template<typename N>
Iterator<N> Iterator<N>::operator++(int i){
    Iterator<N> iter(ptr);
    operator++();
    return iter;
}

template<typename N>
Iterator<N>& Iterator<N>::operator--() {
    ptr = ptr->_prev;
    return *this;
}

template <typename N>
Iterator<N> Iterator<N>::operator--(int i){
    Iterator<N> iter(ptr);
    operator--();
    return iter;
}

template<typename N>
N& Iterator<N>::operator*() {
    return *ptr;
}

template<typename N>
N* Iterator<N>::operator->() {
    return ptr;
}

template<typename N>
bool Iterator<N>::operator ==(const Iterator<N>& o) const{
    return ptr == o.ptr;
}

template<typename N>
bool Iterator<N>::operator!=(const Iterator<N>& o) const {
    return  !(*this == o); //appel l'operateur ==
}

template<typename N>
Iterator<N>::Iterator(N *_ptr) : ptr(_ptr){}


#endif //DLINKEDLIST_ITERATORIMPL_H

