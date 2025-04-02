// ----- Alchemy game internal structure -----

//Adaugari:
/* 
- class Element se afla in AlchemyTable *
- adaug in Element static vector<*Element> *
- clasa Recipe nu mai exista *
- adaug map care link-uieste un pair de elemente la rezultatul celor doua *
- adaug header unde descriu functiile *
- fisier de configurare
- override operator + intre 2 elemente
- functie de initializare a jocului (procesez datele din fisierul de configurare)

*/

#include "main.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;


AlchemyTable::Element::Element(string name) {
    endElement = true;
    this->name = name;
}

bool AlchemyTable::Element::operator==(Element &other) {
    return name==other.name;
}

string AlchemyTable::Element::getName() const{
    return name;
}

void AlchemyTable::Element::setName(string newName){
    name = newName;
}

bool AlchemyTable::Element::getType() const{
    return endElement;
}

void AlchemyTable::Element::setType(bool newType){
    endElement = newType;
}

AlchemyTable::AlchemyTable(vector<Element*> elements, map<pair<Element*, Element*>, Element*> recipes){

}


int main()
{
   return 0;
}