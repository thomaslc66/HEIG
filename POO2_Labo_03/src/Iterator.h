//
// Created by Michael on 07.04.2017.
//

#ifndef POO2_LABO_03_ITERATOR_H
#define POO2_LABO_03_ITERATOR_H

template <typename TypeNode>
class Iterator {
private:
    TypeNode* ptr;

public:
    Iterator(TypeNode* ptr);
    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);
    bool operator==(const Iterator& o) const;
    bool operator!=(const Iterator& o) const;
    TypeNode& operator*();
};

#include "IteratorImp.h"

#endif //POO2_LABO_03_ITERATOR_H
