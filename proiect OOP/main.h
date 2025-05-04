#pragma once

#include<string>
#include<map>
#include<vector>
using namespace std;

void findRecipe(const string givenString, string &res, string &elem1, string &elem2);

class AlchemyTable{ // singleton //
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

        // facem constructorul privat pt ca vrem ca un singur obiect de tip AlchemyTable sa fie creat
        AlchemyTable(vector<Element> elements = {},
             map<pair<Element, Element>, Element> recipes = {},
              bool initTable = false);

        // nu trebuie sa avem constructor de copiere sau posibilitatea de assign la AlchemyTable
        AlchemyTable(const AlchemyTable&) = delete;
        AlchemyTable& operator=(const AlchemyTable&) = delete;

    public:
        static AlchemyTable& getInstance();

        static void initGame(const char* fileName);

        static bool verifInitGame();
    
};

