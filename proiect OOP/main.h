#pragma once

#include<string>
#include<map>
#include<vector>
using namespace std;

class AlchemyTable{
    class Element{
        string name;
        bool endElement;
        public:
            Element(string name);
    
            bool operator==(Element &other);
    
            string getName() const;
    
            void setName(string newName);
    
            bool getType() const;
    
            void setType(bool newType);
    
    };
    vector<Element*> elements;
    static const map<pair<Element*, Element*>, Element*> recipes;
    public:
        AlchemyTable(vector<Element*> elements, map<pair<Element*, Element*>, Element*> recipes){

        }
    
};

