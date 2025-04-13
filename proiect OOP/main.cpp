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
- fisier config elemente *
- functie in care decid daca elementul este endElement sau nu

*/

#include "main.h"
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<map>
using namespace std;

ifstream recipeFile("recipes.txt");
ifstream elemFile("elements.txt");

// --- functii non-membre ---

std::istream& operator>>(std::istream& in, AlchemyTable::Element& other){
    in >> other.name;
    return in;
}

void findRecipe(const string givenString, string &res, string &elem1, string &elem2){
    // aici parsam o reteta si "returnam" numele celor 3 elemente 
    int i = 0;
    while(givenString[i] != ':'){
        res = res + givenString[i];
        i++;
    }
    i++;

    while(givenString[i] != '+'){
        elem1 = elem1 + givenString[i];
        i++;
    }
    i++;

    while(givenString[i] != '\0'){
        elem2 = elem2 + givenString[i];
        i++;
    }
}

// --- sfarsit functii non-membre ---


// --- functii membre Element ---

AlchemyTable::Element::Element(string name) {
    endElement = true;
    this->name = name;
}

AlchemyTable::Element::Element() {
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

// --- sfarsit functii membre Element ---


// ---functii membre AlchemyTable ---

AlchemyTable::AlchemyTable(vector<Element> elements, map<pair<Element, Element>, Element> recipes, bool initTable = false){

}

void AlchemyTable::initGame(const char* fileName){
    AlchemyTable::Element elemName;
    while(elemFile >> elemName){
        elements.insert({elemName.getName(), elemName});
    }

    string readRecipe;
    while(recipeFile >> readRecipe){
        string res, elem1, elem2;
        res = elem1 = elem2 = "";
        findRecipe(readRecipe, res, elem1, elem2);

        AlchemyTable::Element result, el1, el2;
        result.setName(res);
        el1.setName(elem1);
        el2.setName(elem2);

        recipes.insert({{el1, el2}, res});
    }

    initTable = true;
}

// --- sfarsit functii membre AlchemyTable ---


int main()
{
   return 0;
}