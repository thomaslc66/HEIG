/*
 -----------------------------------------------------------------------------------
 Laboratoire : Laboratoire 15
 Fichier     : Person.h
 Auteur(s)   : Thomas Lechaire et Michael Brouchoud
 Date        : 30.04.2017

 But         : Construction d'une class Person

 Compilateur : Cygwin 2.4.1-1
 gcc 5.3.0
 g++ 5.3.0
 make 4.1
 gbd 7.10.1-1

 Remarque(s) : -

 -----------------------------------------------------------------------------------
 */

#ifndef POO2_LABO_03_PERSONNE_H
#define POO2_LABO_03_PERSONNE_H

#include <iostream>

/*
 * @class Node
 */
class Person {

    /*
     * @fn friend std::ostream& operator << (std::ostream& stream, const Person& person)
     *
     * @brief Surchage de l'operateur de flux
     *
     * @author Thomas Léchaire et Michael Brouchoud
     *
     * @param ostream& stream Le flux
     *
     * @param const Person& personne La Person a afficher
     *
     * @return ostream& L'operateur de flux
     *
     */
    friend std::ostream& operator << (std::ostream& stream, const Person& person);

    /*
     * @fn friend std::ostream& operator << (std::ostream& stream, const Person* person)
     *
     * @brief Surchage de l'operateur de flux
     *
     * @author Thomas Léchaire et Michael Brouchoud
     *
     * @param ostream& stream Le flux
     *
     * @param const Person* personne La Person a afficher
     *
     * @return ostream& L'operateur de flux
     *
     */
    friend std::ostream& operator << (std::ostream& stream, const Person* person);

private:
    std::string lastname;
    std::string firstname;

public:

    Person();
    /*
     * @fn Person(const std::string& firstname,const std::string& lastname)
     *
     * @brief Constructeur a partir d'un firstname et d'un lastname
     *
     * @author Thomas Léchaire et Michael Brouchoud
     *
     * @param std::string& firstname Le firstname
     * @param std::string& lastname Le lastname
     *
     */
    Person(const std::string& firstname,const std::string& lastname);

    /*
     * Destructeur
     */
    virtual ~Person();

    /*
     * @fn virtual void description() const
     *
     * @brief Permet d'afficher une description de la Person
     *
     * @author Thomas Léchaire et Michael Brouchoud
     *
     */
    virtual void description() const;
};


#endif //POO2_LABO_03_PERSONNE_H
