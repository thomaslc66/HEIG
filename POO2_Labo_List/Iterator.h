//
// Created by Thomas on 06.04.2018.
//

#ifndef DLINKEDLIST_ITERATOR_H
#define DLINKEDLIST_ITERATOR_H

#include "Deplacements.h"

template<typename N>
class Iterator: public Deplacements{


private:
    N* ptr;

public:

    /**
     *
     * @param o
     * @return
     */
    Iterator& operator ++ ();

    /**
     *
     * @param o
     * @param i
     * @return
     */
    Iterator operator ++ (int i);

    /**
     *
     * @param o
     * @return
     */
    Iterator& operator -- ();

    /**
     *
     * @param o
     * @param i
     * @return
     */
    Iterator operator -- (int i);

    /**
     *
     * @return
     */
    N& operator*();

    /**
     *
     * @return
     */
    N* operator ->();

    /**
     *
     * @param o
     * @return
     */
    bool operator ==(const Iterator& o) const;

    /**
     *
     * @param o
     * @return
     */
    bool operator !=(const Iterator& o) const;

    /**
     *
     * @param ptr
     */
    Iterator(N* _ptr);

};


#include "IteratorImpl.h"


#endif //DLINKEDLIST_ITERATOR_H
