/*
 -----------------------------------------------------------------------------------
 Laboratoire : Laboratoire 03
 Fichier     : Quick_sortCodeCheck.cpp
 Auteur(s)   : Antoine Russbach, Thomas L�chaire et Micha�l Brouchoud
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

//
//  qsort.cpp
//
//  Created by Olivier Cuisenaire on 10.04.15.
//  Copyright (c) 2015 Olivier Cuisenaire. All rights reserved.
//

#include <iostream>
#include <utility>
#include <climits>
#include <vector>
#include <string>

using namespace std;

// selectPivot(begin,end)
//
// choisit un pivot pour le tri rapide parmi le tableau
// entre begin et end (non inclus). Calcule la m�diane
// entre le premier, le dernier et l'�l�ment central.
// retourne un iterateur du m�me type que begin et end
// pointant sur la valeur choisie.
//
// NE RIEN MODIFIER DANS CETTE FONCTION

template < typename RandomAccessIterator >
RandomAccessIterator selectPivot( const RandomAccessIterator begin,
                                 const RandomAccessIterator end )
{
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

// display
//
// Affiche les valeur entre begin et end (non inclus)
// en entourant de [] la valeur du pivot situ�e entre
// begin et end.
//
// NE RIEN MODIFIER DANS CETTE FONCTION

template < typename RandomAccessIterator >
void display( const RandomAccessIterator begin,
             const RandomAccessIterator pivot,
             const RandomAccessIterator end )
{
    for(auto it = begin; it<pivot; ++it) cout << *it << " ";
    cout << "[" << *pivot << "] ";
    for(auto it = pivot+1; it<end; ++it) cout << *it << " ";
    cout << endl;
}


/**
 *  @fn RandomAccessIterator partition(RandomAccessIterator begin, RandomAccessIterator end)
 *
 *  @brief Partitionne le tableau de l�indice begin � l�indice
 *         end en utilisant *end comme pivot.
 *
 *  @author Antoine Russbach, Thomas L�chaire
 *          et Micha�l Brouchoud
 *
 *  @param[in] RandomAccessIterator begin Le debut du tableau partitionne
 *  @param[in] RandomAccessIterator end La fin du tableau partitionne
 *
 *  @return RandomAccessIterator i Le pivot du tableau partitionne
 *
 */
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

// quickSort
//
// Effectue le tri rapide des �l�ments entre begin
// et end (non inclus). Doit appeler selectPivot(...)
// pour le choix du pivot, et display() apr�s chaque
// partition
//
// A COMPLETER

template < typename RandomAccessIterator >
void quickSort( RandomAccessIterator begin, RandomAccessIterator end )
{
	if(end <= begin + 1) {
		return;
	}//if

	RandomAccessIterator pivot = selectPivot(begin, end);

	swap(*(end - 1), *pivot);

	RandomAccessIterator i = partition(begin, end);
	display(begin, i, end);

	quickSort(begin, i);
	quickSort(i + 1, end);
}


/*// main
//
// Programme testant la mise en oeuvre de quickSort
// appelle cette fonction avec une string, un tableau
// C d'entiers et un std::vector<double>
//
//
// NE RIEN MODIFIER DANS CETTE FONCTION

int main(int argc, const char * argv[]) {

    // std::string

    string s("EXEMPLE_DE_TRI_RAPIDE");
    cout << s << endl;

    quickSort(s.begin(),s.end());

    cout << s << endl;

    // C array

    int array[] = { 7, 3, 6, 1, 9, 2, 0, 10, 12, -3 };
    cout << endl;
    for(int i : array)
        cout << i << " ";
    cout << endl;

    quickSort(array,array+10);

    for(int i : array)
        cout << i << " ";
    cout << endl;

    // std::vector

    vector<double> vd { 0.1, 1.2, 3.5, 1.8, 0.4, 10.2, -0.4, 5.8, 6.9, 12.5, 24.3, 0.6, 12.2, 4.5, 3.1415 };
    cout << endl;
    for(double d : vd)
        cout << d << " ";
    cout << endl;

    quickSort(vd.begin(),vd.end());

    for(double d : vd)
        cout << d << " ";
    cout << endl;

    return 0;
}*/
