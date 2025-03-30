// ----- Alchemy game internal structure -----

#include<iostream>
#include<string>
#include<vector>
using namespace std;

// the obvious "Element" class

class Element{
    string name;
    bool endElement;
    public:
        Element(string name){
            endElement = true;
            this->name = name;
        }

        bool operator==(Element &other){
            return name==other.name;
        }

        string getName() const{
            return name;
        }

        void setName(string newName){
            name = newName;
        }

        bool getType() const{
            return endElement;
        }

        void setType(bool newType){
            endElement = newType;
        }

};

class Recipe{
    Element* ing1;
    Element* ing2;
    Element* res;
    public:
        Recipe(Element* ing1, Element* ing2, Element* res){
            this->ing1 = ing1;
            this->ing2 = ing2;
            this->res = res;
            ing1->setType(false); 
            ing2->setType(false);
        }

        Element Result(Element* ing1, Element* ing2){
            return *res;
        }

};

class AlchemyTable{
    vector<Recipe*> alchemyTable;
    public:
        AlchemyTable(vector<Recipe*>& alchemyTable) : alchemyTable(alchemyTable){
        }

};

int main()
{
    Element* water = new Element("water");
    Element* fire = new Element("fire");
    Element* earth = new Element("earth");
    Element* alcohol = new Element("alcohol");
    Recipe* r1 = new Recipe(water, fire, alcohol);
    vector<Recipe*> table = {r1};
    AlchemyTable table(table);
}