#pragma once

#include<string>
#include<map>
#include<vector>
using namespace std;

void findRecipe(const string givenString, string &res, string &elem1, string &elem2);

class AlchemyTable{
    public:
        class Element{
            string name;
            bool endElement;
            public:
                Element(string name);

                Element();
        
                bool operator==(Element &other);
        
                string getName() const;
        
                void setName(string newName);
        
                bool getType() const;
        
                void setType(bool newType);

                Element verifEndElem();

                Element operator+(const Element &other)const;

                friend std::istream& operator>>(std::istream& in, Element &other);
        
        };
    private:
        static map<string,Element> elements;
        static map<pair<Element, Element>, Element> recipes;
        static bool initTable;
    public:
        AlchemyTable(vector<Element> elements, map<pair<Element, Element>, Element> recipes, bool initTable = false);

        static void initGame(const char* fileName);

        static bool verifInitGame();
    
};

