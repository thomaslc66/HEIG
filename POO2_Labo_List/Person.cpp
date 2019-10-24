/*
 -----------------------------------------------------------------------------------
 Laboratoire : Laboratoire 15
 Fichier     : Personne.cpp
 Auteur(s)   : Thomas Lechaire et Michael Brouchoud
 Date        : 30.04.2017

 But         : Implementation d'une class Person

 Compilateur : Cygwin 2.4.1-1
 gcc 5.3.0
 g++ 5.3.0
 make 4.1
 gbd 7.10.1-1

 Remarque(s) : -

 -----------------------------------------------------------------------------------
 */

#include "Person.h"

std::ostream& operator << (std::ostream& stream, const Person& person) {
    stream << person.firstname << " " << person.lastname;
    return stream;
}

std::ostream& operator << (std::ostream& stream, const Person* person) {
    stream << *person;
    return stream;
}

Person::Person(const std::string& firstname = " ", const std::string& lastname = " ") : firstname(firstname), lastname(lastname) { }
Person::Person(): Person("",""){}


Person::~Person() {}

void Person::description() const {
    std::cout << "Ce message provient de la class Person";
}