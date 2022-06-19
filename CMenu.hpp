#include "CControl.hpp"

class CMenu
{
private:
    CControl*objC;
    //App* objApp;
	//CHistorias* objHistorias;
	//Valoracion* objV = new Valoracion();
	int op;
    int numData;
    int auxL;

	uint32_t userCode;
    string name;
	string auxN;
    string language; //desired language

	bool found;

	void registerUser() {
        system("cls");
	    cout << "Ingrese su nombre: ";
	    cin.ignore(); getline(cin, name);
		auxN = Utils::generateUserName(toupper(name[0]),toupper(name[1]));
		cout << "\nHola " << name << "! Se te registrara como: " << auxN;
	    cout << "\n¿Que lenguaje deseas aprender? (1: Ingles 2:Frances)";
	    cin >> auxL; language = languages[auxL-1];
		userCode = Utils::generateRandNumber(1000,9999);
	    objC->insertDataMenu(userCode,Person(userCode, auxN,languages[rand()%2],0,0,0));
	    cout << "\n¡Usuario Registrado!";
	    cout << "Su código es:" << userCode;
	    _getch();
    }

	void programa() {

	    if (found) {
            //Comienza aplicación

	    }
	    else {
		cout << "Por favor, registrese para comenzar.";
	    }
	    _getch();
    }

	void creditos(){
        system("cls");
		cout << "======================Créditos======================\n";
		cout << "•	Jhosaim Ricardo Pocohuanca Pineda - u202115595\n";
		cout << "•	Alejandro Alberto Pachas Chavez  - u201917598\n";
		cout << "•	Jak Cristian Campos Espinoza  - u20211a184\n";
		cout << "====================================================\n";
		_getch();
    }

    void opciones(){
        system("cls");
        cout << "APRENDIZAJE BÁSICO DE INGLES Y FRANCES\n";
        cout << "1- Generar datos aleatorios\n";
        cout << "2- Registrar usuario\n";
		cout << "3- Ingresar al programa\n";
        cout << "4- Mostrar lista de usuarios (Arbol Binario) \n";
		cout << "5- Mostrar Hash Table\n";
        cout << "6- Ordenar ()\n";
        cout << "7- Creditos\n";
        cout << "8- Salir\n";
    }

public:

    void empezarMenu() {

        while (op!=8) {
            opciones();
            cin >> op;
            switch (op) {
            case 1: {
                objC->generateAndSaveData(numData);
            } break;
            case 2: {
                registerUser();
            } break;
            case 3: {
				programa();
            } break;
            case 4: {
                objC->displayData();
            } break;
            case 5: {
				objC->generateHT();
            }
            default: break;
            case 6: {
                objC->sortByID();
            } break;
            case 7: {
				creditos();
            }
            }
        }

    }

	CMenu() {
        objC = new CControl();
	    //objApp = new App();
	    //objHistorias = new CHistorias();
        op = 0;
        numData = 10;
        auxL = 0;
		userCode = 0;
    	name = "";
    	language = "";
		auxN = "";
	    found = false;
    }

	~CMenu() {
        delete objC;
	    //delete objApp;
	    //delete objHistorias;
	    //delete objV;
    }
};