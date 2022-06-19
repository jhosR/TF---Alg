#include "CDataGenerator.hpp"
#include <conio.h>
using DataStructures::BinarySearchTree;
using namespace std;

class CControl
{
private:
    bool userFirst;
    PersonRepository* repo;
    BinarySearchTree<int, Person>* bst;

    void loadData(){

        for (int i = 0; i < repo->getVec().size(); i++) {
            bst->insert(repo->getVec().at(i).getuserCode(),repo->getVec().at(i));
        }
    };

    void chargeData(){
        repo->readData();
        loadData();
    }

public:
    CControl(){
        repo = new PersonRepository("output.txt");
        bst = new BinarySearchTree<int, Person>(
                [](int a, int b) -> bool { return a < b;},
                [](Person p) -> void { std::cout << p << " "; },
                [](int a, int b) -> bool { return a == b; }
        );
        userFirst = false;
    }
    ~CControl(){
        delete repo;
    }

    void generateAndSaveData(int num){
        repo->generateData(num);
        loadData();
    }

    void insertDataMenu(uint32_t code, Person person){
        bst->insert(code,person);
        if (repo->getVec().empty()) {
            userFirst=true;
            repo->readData();
        }

        repo->savePerson(person);
        repo->saveData();
    }

    void displayData(){
        if (repo->getVec().empty()) { loadData(); }
        if (userFirst) {
            userFirst=false;
            loadData();
        } 
        bst->display();
        _getch();
    }

    void generateHT(){
        
    }

    void sortByID(){

    }
    
};