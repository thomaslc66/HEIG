#include <iostream>
#include "List.h"
#include <string>
#include "Person.h"
#include "Child.h"

using namespace std;

int main()
{

    //List string vide
    List<string> emptyList;

    //List de string
    List<string> stringList;
    stringList.append("un");
    stringList.append("deux");
    stringList.append("trois");

    //List string copie
    List<string> cpStringList(stringList);

    //Liste de Person
    List<Person> personList;
    personList.append(Person("Matthieu", "Girard"));
    personList.append(Child("Thomas", "Lechaire"));
    personList.append(Child("Francis", "Cabrel"));
    personList.append(Person("Michel", "Sardou"));

    //Liste de pointeurs de Person
    List<Person*> ptrPersonList;
    ptrPersonList.append(new Person("Matthieu", "brouchoud"));
    ptrPersonList.append(new Child("Thomas", "Lechaire"));
    ptrPersonList.append(new Child("Francis", "Cabrel"));
    ptrPersonList.append(new Person("Michel", "Sardou"));

    //Liste constante de int
    const List<int> cListe = { 42, 3, 14 };

    //Affichage
    cout << "---------------------------------- Tests de la class List -----------------------------------" << endl;
    cout << "------------------------------- Test de creation d'instances --------------------------------" << endl;
    cout << "Constructeur vide, List<string> emptyList : " << emptyList << endl;
    cout << "Constructeur de copie, List<string> cpStringList : " << cpStringList << endl;
    cout << endl;

    cout << "------------------------------ Affichage des Listes de départ -------------------------------" << endl;
    cout << "List<string> emptyList : " << emptyList << endl;
    cout << "List<string> stringList : " << stringList << endl;
    cout << "List<string> cpStringList : " << stringList << endl;
    cout << "Liste<Person> personList: " << personList << endl;
    cout << "Liste<Person*> ptrPersonList: " << ptrPersonList << endl;
    cout << endl;

    cout << "------------------------------------ Test d'operateurs --------------------------------------" << endl;
    cout << "--------------------------------------- operateur = -----------------------------------------" << endl;
    cout << "List<string> emptyList : " << emptyList << endl;
    cout << "List<string> stringList : " << stringList << endl;
    cout << "Utilisation de l'operateur = entre emptyList et stringList" << endl;
    emptyList = stringList;
    cout << "List<string> emptyList : " << emptyList << endl;
    cout << "List<string> stringList : " << stringList << endl;
    cout << endl;

    cout << "List<string> stringList : " << stringList << endl;
    cout << "Utilisation de l'operateur = entre stringList et stringList" << endl;
    stringList = stringList;
    cout << "List<string> stringList : " << stringList << endl;
    cout << endl;

    cout << "--------------------------------------- operateur [] -----------------------------------------" << endl;
    cout << "L'element se trouvant a la position stringList[1] est : " << stringList[1] << endl;
    cout << endl;

    cout << "L'element se trouvant a la position stringList[6] est : ";
    try {
        cout << stringList[6] << endl;
    }
    catch (out_of_range e) {
        cout << e.what() << endl;
    }
    cout << endl;

    cout << "-------------------------------- Test de la taille d'une liste -------------------------------" << endl;
    cout << "La List stringList contient " << stringList.size() << " elements" << endl;

    cout << "---------------------------- Test d'insertion en debut/fin de liste --------------------------" << endl;
    cout << "Ajout de l'element \"zero\" en debut de la liste stringList" << endl;
    stringList.insert("zero");
    cout << "List<string> stringList : " << stringList << endl;
    cout << endl;

    cout << "Ajout de l'element \"quatre\" en fin de la liste stringList" << endl;
    stringList.append("quatre");
    cout << "List<string> stringList : " << stringList << endl;
    cout << endl;
    cout << "La List stringList contient " << stringList.size() << " elements" << endl;

    cout << "------------------------------ Test de suppression d'un element ------------------------------" << endl;
    cout << "List<string> stringList : " << stringList << endl;
    cout << "Suppression de l'element \"zero\" de la liste stringList via sont index (methode remove(int index))" << endl;
    stringList.removeAt(0);
    cout << "List<string> stringList : " << stringList << endl;
    cout << endl;

    cout << "Suppression de l'element \"quatre\" de la liste stringList via sont element (methode remove(T o))" << endl;
    cout << "List<string> stringList : " << stringList << endl;
    stringList.remove("quatre");
    cout << "List<string> stringList : " << stringList << endl;
    cout << endl;

    cout << "------------------------------------- Test iterator ------------------------------------------" << endl;
    cout << "List<string> stringList : " << stringList << endl;
    cout << "L'iterator begin() de la liste stringList vaut : " << *stringList.begin() << endl;
    cout << "L'iterator end() de la liste stringList vaut : " << *stringList.end() << endl;
    cout << endl;

    cout << "--------------------------------------- Test find --------------------------------------------" << endl;
    cout << "List<string> stringList : " << stringList << endl;
    cout << "Recherche de l'element \"deux\" de la liste stringList : " << stringList.find("deux") << endl;
    cout << "Recherche de l'element \"quatre\" de la liste stringList : ";
    int retour = stringList.find("quatre");
    if(retour != -1) {
        cout << "l'element \"quatre\" de la liste stringList se trouve à l'index " << retour << endl;
    }
    else {
        cout << "L'element ne se trouve pas dans la liste" << endl;
    }
    cout << endl;

    cout << "----------------------------- Fin des Tests de la class List ---------------------------------" << endl;
    cout << endl;
    cout << "------------------------------- Tests de la class Iterator -----------------------------------" << endl;
    cout << "-------------------------------- operator ++, --, != et * ------------------------------------" << endl;
    cout << "Affichage de stringList via une boucle for dans le sens normal" << endl;
    for (List<string>::Iterator it = stringList.begin(); it != stringList.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Affichage de stringList via une boucle for dans le sens inverse" << endl;
    for (List<string>::Iterator it = --stringList.end(); it != --stringList.begin(); it--) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "--------------------------------------- operator == ------------------------------------------" << endl;
    cout << "Comparaison de l'Iterator pointant sur \"deux\" avec la list stringList" << endl;
    for (List<string>::Iterator it = stringList.begin(); it != stringList.end(); ++it) {
        cout << *it << " et " << stringList[stringList.find("deux")];
        ;
        if(*it == stringList[stringList.find("deux")]) {
            cout << " sont";
        }
        else {
            cout << " ne sont pas";
        }
        cout << " egaux" << endl;
    }
    cout << endl;

    cout << "----------------------------- Test sur les Listes Constantes ---------------------------------" << endl;
    cout << "Affichage de cListe via une boucle for dans le sens inverse" << endl;
    List<int >::ConstIterator it = --cListe.end();
    for (; it != --cListe.begin(); --it)
        std::cout << *it << " ";

    std::cout << std::endl;


    cout << "----------------------------- Fin des Tests de la class List ---------------------------------" << endl;
    cout << endl;
    cout << "-------------------------- Tests du mécanisme de liaison dynamique ----------------------------" << endl;
    cout << "Affichage d'une liste de pointeur sur des Person contenant des Child" << endl;
    for (List<Person*>::Iterator it = ptrPersonList.begin(); it != ptrPersonList.end(); ++it) {
        cout << *it << " : ";
        (*it)->description();
        cout << endl;
    }
    cout << endl;

    cout << "----------------------- Fin des Tests du mécanisme de liaison dynamique -----------------------" << endl;
    cout << endl;

}