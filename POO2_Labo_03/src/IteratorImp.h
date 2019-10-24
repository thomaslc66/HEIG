//
// Created by Michael on 07.04.2017.
//

#ifndef POO2_LABO_03_ITERATORIMPL_H
#define POO2_LABO_03_ITERATORIMPL_H

template <typename TypeNode>
Iterator<TypeNode>::Iterator(TypeNode* ptr) : ptr(ptr) {}

template <typename TypeNode>
Iterator<TypeNode>& Iterator<TypeNode>::operator++() {
    ptr = &ptr->operator++();
    return *this;
}

template <typename TypeNode>
Iterator<TypeNode> Iterator<TypeNode>::operator++(int) {
    Iterator<TypeNode> tmp(ptr);
    operator++();
    return tmp;
}

template <typename TypeNode>
Iterator<TypeNode>& Iterator<TypeNode>::operator--() {
    ptr = &ptr->operator--();
    return *this;
}

template <typename TypeNode>
Iterator<TypeNode> Iterator<TypeNode>::operator--(int) {
    Iterator<TypeNode> tmp(ptr);
    operator--();
    return tmp;
}

template <typename TypeNode>
bool Iterator<TypeNode>::operator==(const Iterator<TypeNode>& o) const {
    return *ptr == *o.ptr;
}

template <typename TypeNode>
bool Iterator<TypeNode>::operator!=(const Iterator<TypeNode>& o) const {
    return !(*this == o);
}

template <typename TypeNode>
TypeNode& Iterator<TypeNode>::operator*() {
    return *ptr;
}

#endif //POO2_LABO_03_ITERATORIMPL_H