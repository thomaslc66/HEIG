/*
 -----------------------------------------------------------------------------------
 Laboratoire : Laboratoire 14
 Fichier     : main.cpp
 Auteur(s)   : Thomas Lechaire et Michael Brouchoud
 Date        : 09.04.2017

 But         : Tester la class String

 Compilateur : Cygwin 2.4.1-1
 gcc 5.3.0
 g++ 5.3.0
 make 4.1
 gbd 7.10.1-1

 Remarque(s) : -

 -----------------------------------------------------------------------------------
 */

#include "DoublyLinkedList.h"

#include <iostream>
using namespace std;

int main() {
    DoublyLinkedList<string> l;
    l.append("un");
    l.append("deux");
    l.append("trois");
    l.insert("zero");
    l.remove("un");
    l.append("un");
    l.remove(3);

    DoublyLinkedList<string>::Iterator test = l.find("deux");
    cout << *test << endl;

    /*for (DoublyLinkedList<string>::Iterator it = l.end(); it != l.begin(); it--)
        cout << *it << " ";
    cout << endl;*/

    DoublyLinkedList<string> essai = l;
    for (DoublyLinkedList<string>::Iterator it = essai.begin(); it != essai.end(); it++)
        cout << *it << " ";
    cout << endl;

    for(int i = 0; i < essai.size(); i++)
        cout << essai[i] << " ";
    cout << endl;

    /*for(int i = essai.size()-1; i >= 0; i--) {
        essai[i] = "a";
        cout << essai[i] << " ";
    }
    cout << endl;*/

   /* for (DoublyLinkedList<string>::Iterator it = l.end(); it != l.begin(); it--)
        cout << *it << " ";
    cout << endl;*/

    return EXIT_SUCCESS;
}

