/*
 -----------------------------------------------------------------------------------
 Laboratoire : Laboratoire 03
 Fichier     : Quick_sortImpl.h
 Auteur(s)   : Antoine Russbach, Thomas Léchaire et Michaël Brouchoud
 Date        : 16.04.2016

 But         : Implementation de la fonction de tri quicksort et de ses differentes
               fonctions utiles a son bon fonctionnement

 Compilateur : Cygwin 2.4.1-1
 gcc 5.3.0
 g++ 5.3.0
 make 4.1
 gbd 7.10.1-1

 Remarque(s) : -

 -----------------------------------------------------------------------------------
 */

#ifndef QUICK_SORTIMPL_H_
#define QUICK_SORTIMPL_H_

template < typename RandomAccessIterator >
RandomAccessIterator selectPivot(const RandomAccessIterator begin, const RandomAccessIterator end) {
    RandomAccessIterator p1 = begin;
    RandomAccessIterator p2 = begin + ( end-begin ) / 2;
    RandomAccessIterator p3 = end-1;

    if(*p1 < *p2) {
        if( *p2 < *p3 ) return p2;
        else if(*p1 < *p3) return p3;
        return p1;
    } else {
        if( *p1 < *p3 ) return p1;
        else if(*p2 < *p3) return p3;
        return p2;
    }
}

template < typename RandomAccessIterator >
RandomAccessIterator partition(RandomAccessIterator begin, RandomAccessIterator end) {

	RandomAccessIterator i = begin - 1;
	RandomAccessIterator j = end - 1;

	while(true) {

		do {
			i++;
		} while(*i < *(end - 1));

		do {
			j--;
		} while(j > begin && *(end - 1) < *j);

		if(i >= j) {
			break;
		}//if

		swap(*i, *j);

	}//while

	swap(*i, *(end - 1));

	return i;
}

template < typename RandomAccessIterator >
void quickSort( RandomAccessIterator begin, RandomAccessIterator end )
{
	if(end <= begin + 1) {
		return;
	}//if

	RandomAccessIterator pivot = selectPivot(begin, end);

	swap(*(end - 1), *pivot);

	RandomAccessIterator i = partition(begin, end);

	quickSort(begin, i);
	quickSort(i + 1, end);
}

#endif /* QUICK_SORTIMPL_H_ */
