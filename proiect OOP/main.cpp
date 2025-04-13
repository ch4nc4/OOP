// ----- Alchemy game internal structure -----

//Adaugari:
/* 
- class Element se afla in AlchemyTable *
- adaug in Element static vector<*Element> *
- clasa Recipe nu mai exista *
- adaug map care link-uieste un pair de elemente la rezultatul celor doua *
- adaug header unde descriu functiile *
- fisier de configurare *
- override operator + intre 2 elemente * (add "throw error")
- functie de initializare a jocului (procesez datele din fisierul de configurare) -> functie statica
- static!! bool ca sa verif daca AlchemyTable a fost init. -> if not => eroare
- supraincarcare operator citire elemente
- fisier config elemente

*/

#include "main.h"
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<map>
using namespace std;

ifstream recipeFile("recipes.txt");

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

AlchemyTable::Element AlchemyTable::Element::operator+(const Element &other)const{
    if(recipes.contains({*this, other})){
        return recipes[{*this, other}];
    }

    else{
        //throw error;
    }
   
}

AlchemyTable::AlchemyTable(vector<Element> elements, map<pair<Element, Element>, Element> recipes){

}

void AlchemyTable::initGame(const char* fileName){
    
}

int main()
{
   return 0;
}