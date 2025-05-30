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
- display-able element -> elem is poz lui pe tabla
- set cu ce elem am gas pana acum
- fiecare window are clasa lui: start menu window, game window, show elements window (singletoane)
- clasa game - initializez jocul -> mosteneste alchemytable + retin instanta in care ma aflu (gameState), handle events *

- clasa abstracta pt windows *
- uniqueptr pentru switch intre windows *
- clasa noua: GameData (fiecare window retine referinta catre datele acquired in joc pana la mom respectiv) *
-> asa nu pierdem nimic cand dam switch intre windows 

- do not forget to do:
   dark and light theme *
   main menu button functionality (the little alchemy bottle)*
- buttons on main game screen:
   "?" = game info, how elements are combined, game logic *
   "+" = add element, takes you to Add Element Window
   "<-" = deletes last element

- Texture Manager: singleton care se ocupa cu incarcarea icon-urilor elementelor
                  pentru ca este singleton, singurul ob. de acest tip este creat in Screen
                  si evident ramane valabil fiecarui window al jocului * 

- teorie de adaugat:
   - foloseste operatorii overloaded: debug print (elements) *
   - template (metoda template, functie externa template) *
   - destructori (avem 2 :(( ) *


*/

// #define SFML_STATIC_
#include "game.h"
#include "alchemyTable.h"
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<map>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
using namespace std;


int main()  
{
   Game game;
   game.run();
   return 0;
}