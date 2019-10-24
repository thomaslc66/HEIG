/*
 -----------------------------------------------------------------------------------
 Laboratoire : Laboratoire 03
 Fichier     : F_general_vectorImpl.h
 Auteur(s)   : Antoine Russbach, Thomas Léchaire et Michaël Brouchoud
 Date        : 16.04.2016

 But         : Implementation de diverses fonctions utiles pour l'interaction avec un vector

 Compilateur : Cygwin 2.4.1-1
 gcc 5.3.0
 g++ 5.3.0
 make 4.1
 gbd 7.10.1-1

 Remarque(s) : -

 -----------------------------------------------------------------------------------
 */

#ifndef F_GENERAL_VECTORIMPL_H_
#define F_GENERAL_VECTORIMPL_H_

template <typename T>
void fillVector(vector<T>& vectorToFill, size_t size, size_t max) {

	for(size_t i = 0; i < size; i++) {

		T random = (rand() % max) + 1;
		vectorToFill.push_back(random);

	}//for
}

template <typename T>
void displayVector(vector<T>& vectorToDisplay){

	//Affichage du vector
	cout << "[";

	for(T& element : vectorToDisplay){

		cout << element;

		if(&element != &vectorToDisplay.back()) {
			cout << ", ";
		}//if

	}//foreach

	cout << "]" << endl;

}


#endif /* F_GENERAL_VECTORIMPL_H_ */
