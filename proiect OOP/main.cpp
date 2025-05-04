// ----- Alchemy game internal structure -----

//Adaugari:
/* 
destructori, fct virtuale, clasa abstracta, casting (cast la elementul nested pt displayable elem), template :( <_> ;_; (paleta de culori, theme-uri(const) -> light/dark mode) 
design patern
- class Element se afla in AlchemyTable *
- adaug in Element static vector<*Element> *
- clasa Recipe nu mai exista *
- adaug map care link-uieste un pair de elemente la rezultatul celor doua *
- adaug header unde descriu functiile *
- fisier de configurare *
- override operator + intre 2 elemente * (add "throw error") *
- functie de initializare a jocului (procesez datele din fisierul de configurare) -> functie statica *
- static!! bool ca sa verif daca AlchemyTable a fost init. -> if not => eroare *
- supraincarcare operator citire elemente *
- fisier config elemente *
- functie in care decid daca elementul este endElement sau nu *
- clasa window (mosteneste alchemytable)?? care are vectorul currentElem -> pair<Element, int> -> retine ce elemente si ce grad de multiplicare au la mom respectiv
- ar fi nevoie si de o alta pagina in joc, unde sa fie display-uite toate elementele gasite
- pe pagina de display a elementelor, pot fi selectate si adaugate la current gameplay
- clasa de elemente -> mostenire (clasa de baza (abstracta) - functii virtuale)
- display-able element -> elem is poz lui pe tabla
- set cu ce elem am gas pana acum
- fiecare window are clasa lui: start menu window, game window, show elements window (singletoane)
- clasa game - initializez jocul -> mosteneste alchemytable + retin instanta in care ma aflu (gameState), handle events

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

// --- initializarea elementelor statice ---
std::map<std::string, AlchemyTable::Element> AlchemyTable::elements;
std::map<std::pair<AlchemyTable::Element, AlchemyTable::Element>, AlchemyTable::Element> AlchemyTable::recipes;
bool AlchemyTable::initTable = false;

// -----------------------------------------------

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

AlchemyTable::Element AlchemyTable::Element::verifEndElem(){
    map<pair<Element, Element>, Element>::iterator it;
    bool foundRecipe = false;
    for(it = recipes.begin(); it != recipes.end(); it++){
        if(it->first.first.getName() == this->getName())
            foundRecipe = true;
    }

    if(!foundRecipe)
        this->endElement = true;
    
    return *this;
}

AlchemyTable::Element AlchemyTable::Element::operator+(const Element &other)const{
    if(recipes.contains({*this, other})){
        return recipes[{*this, other}];
    }

    else{
        throw invalid_argument("These elements have no recipe asociated!!");
    }
}

// --- sfarsit functii membre Element ---


// ---functii membre AlchemyTable ---

AlchemyTable::AlchemyTable(vector<Element> elements, map<pair<Element, Element>, Element> recipes, bool initTable){

}

AlchemyTable& AlchemyTable::getInstance(){
    static AlchemyTable instance;
    return instance;
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

bool AlchemyTable::verifInitGame(){
    if(initTable)
        return true;
    else
        throw runtime_error("When an AlchemyTable object is declared it should also be initiated!!");
}

// --- sfarsit functii membre AlchemyTable ---


int main()
{
   return 0;
}