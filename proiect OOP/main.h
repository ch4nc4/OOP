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

            Element operator+(const Element &other)const;
    
    };
    static map<string,Element> elements;
    static map<pair<Element, Element>, Element> recipes;
    public:
        AlchemyTable(vector<Element> elements, map<pair<Element, Element>, Element> recipes);

        static void initGame(const char* fileName);
    
};

