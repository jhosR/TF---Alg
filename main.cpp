#include <iostream>

#include "CMenu.hpp"

int main(){ //15 clases (5 entidades por estudiante)
    srand(time(0));
    setlocale(LC_ALL, "es_ES");
    CMenu* objMenu = new CMenu();
	objMenu->empezarMenu();
	delete objMenu;

    return 0;
}