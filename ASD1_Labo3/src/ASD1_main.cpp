/*
 -----------------------------------------------------------------------------------
 Laboratoire : Laboratoire 03
 Fichier     : ASD1_main.cpp
 Auteur(s)   : Antoine Russbach, Thomas Léchaire et Michaël Brouchoud
 Date        : 16.04.2016

 But         : Comparer l'efficaciter de trois algorithme de tri en utilisant
               comme critere comparatif le temps d'execution pour trier des tableaux
               de taille differentes.

 Compilateur : Cygwin 2.4.1-1
 gcc 5.3.0
 g++ 5.3.0
 make 4.1
 gbd 7.10.1-1

 Remarque(s) : -

 -----------------------------------------------------------------------------------
 */

#include <cstdlib>
#include <cmath>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "TimeCollection.h"
#include "F_general_vector.h"
#include "Quick_sort.h"

int main() {
	srand(0);


	const size_t NB_SIMULATION = 30;
	const size_t POWER_MAX = 7;
	const size_t TEN = 10;

	clock_t begin, end ;

	//Contient l'ensemble des temps pour chaque simulation de selectionSort
	//vector<TimeCollection> selectionSortCollection;

	//Contient l'ensemble des temps pour chaque simulation de quickSort
	vector<TimeCollection> quickSortCollection;

	//Contient l'ensemble des temps pour chaque simulation de countingSort
	//vector<TimeCollection> countingSortCollection;

	for(size_t i = 1; i <= POWER_MAX; i++) {

		//TimeCollection selectionSortTime(NB_SIMULATION);
		TimeCollection quickSortTime(NB_SIMULATION, i);
		//TimeCollection countingSortTime(NB_SIMULATION);

		const size_t SIZE = pow(TEN, i);
		for(size_t j = 0; j < NB_SIMULATION; j++) {
			cout.flush();
			cout << (j + 1) << " ";
			//Generation d'un tableau contenant des nombres aleatoires
			vector<int> randomNumbers;
			randomNumbers.clear();
			randomNumbers.reserve(SIZE);
			fillVector(randomNumbers, SIZE);
			//displayVector(randomNumbers);

			//Tests algorithme
			//TODO Algorithme de tri par selection

			begin = clock();
			quickSort(randomNumbers.begin(), randomNumbers.end());
			end = clock();

			//displayVector(randomNumbers);

			quickSortTime.push_back((double(end - begin) / CLOCKS_PER_SEC));

			//TODO Algorithme de tri comtpage
			begin = clock();
			(randomNumbers.begin(), randomNumbers.end());
			end = clock();

			//Sert a bloquer pour voir les tris
			//cin.get();
		}//for j

		quickSortCollection.push_back(quickSortTime);
		cout << endl << quickSortTime << endl << endl;
	}//for i

	return EXIT_SUCCESS;
}

