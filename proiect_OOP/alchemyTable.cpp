#include "alchemyTable.h"
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<map>
#include<filesystem>

ifstream recipeFile("assets/recipes.txt");
ifstream elemFile("assets/elements.txt");

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
    if(recipes.count({*this, other}) > 0){
        return recipes[{*this, other}];
    }

    else{
        throw invalid_argument("These elements have no recipe asociated!!");
    }
}

bool AlchemyTable::Element::operator<(const Element &other)const{
    return name < other.name; 
}
// --- sfarsit functii membre Element ---


// ---functii membre AlchemyTable ---

AlchemyTable::AlchemyTable(vector<Element> elements, map<pair<Element, Element>, Element> recipes, bool initTable){

}

AlchemyTable& AlchemyTable::getInstance(){
    static AlchemyTable instance;
    return instance;
}

void AlchemyTable::initGame(const string& elemFileName, const string& recipeFileName){
    std::ifstream file1(elemFileName);
    if (!file1.is_open()) {
        std::cerr << "Error: Could not open element file: " << elemFileName << '\n';
        throw std::runtime_error("Element file could not be opened.");
    }

    std::ifstream file2(recipeFileName);
    if (!file2.is_open()) {
        std::cerr << "Error: Could not open recipe file: " << recipeFileName << '\n';
        throw std::runtime_error("Recipe file could not be opened.");
    }

    std::cout << "Files opened successfully\n";

    string elem = "";
    while(std::getline(file1, elem)){
        AlchemyTable::Element elemName;
        elem.erase(0, elem.find_first_not_of(" \t\r"));
        elem.erase(elem.find_last_not_of(" \t\r") + 1);
        elemName.setName(elem);
        elements.insert({elemName.getName(), elemName});
        elem="";
    }

    string recipe;
    while(std::getline(file2, recipe)){
        string res, elem1, elem2;
        res = elem1 = elem2 = "";
        findRecipe(recipe, res, elem1, elem2);

        AlchemyTable::Element result, el1, el2;
        result.setName(res);
        el1.setName(elem1);
        el2.setName(elem2);

        recipes.insert({{el1, el2}, result});
    }

    // std::cout << "[Game] elements.size() = " << elements.size()
    //       << ", recipes.size() = " << recipes.size() << "\n";
    initTable = true;
}

void AlchemyTable::verifInitGame(){
    if(initTable)
        throw runtime_error("When an AlchemyTable object is declared it should also be initiated!!");
}

// --- sfarsit functii membre AlchemyTable ---