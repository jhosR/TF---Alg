#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#include "utils.hpp"

class Person {
    uint32_t userCode;
    std::string name;
    std::string language;
    uint32_t score;
    uint32_t totQ;
    uint32_t corrQ;
public:
    Person(uint32_t userCode, std::string name, std::string language, uint32_t score,uint32_t totQ, uint32_t corrQ):
    userCode(userCode), name(name), language(language),score(score),totQ(totQ),corrQ(corrQ) {}

    friend std::ostream& operator<<(std::ostream& os, Person p) {
        os << p.userCode << "|" << p.name << "|" << p.language << "|" << p.score << "|" << p.totQ << "|" << p.corrQ;
        return os;
    }

    uint32_t getuserCode(){
        return userCode;
    }

    static Person createPerson() {
        return Person(Utils::generateRandNumber(1000,9999), Utils::generateName(),languages[rand()%2],0,0,0);
    }
};

class PersonRepository {
    std::string path;
    std::ofstream file;
    std::vector<Person> vecP;
private:
    void read() {
        std::string line = "";
        std::ifstream arch("output.txt");
        while (getline(arch, line)) {
            std::stringstream s(line);
            std::string aux;

            uint32_t userCode;
            std::string name;
            std::string language;
            uint32_t score;
            uint32_t totQ;
            uint32_t corrQ;

            getline(s, aux, '|');
            userCode = std::stoi(aux);
            getline(s, aux, '|');
            name=aux;
            getline(s, aux, '|');
            language=aux;
            getline(s, aux, '|');
            score = std::stoi(aux);
            getline(s, aux, '|');
            totQ = std::stoi(aux);
            getline(s, aux, '|');
            corrQ = std::stoi(aux);

            Person t(userCode, name, language, score, totQ, corrQ);
            vecP.push_back(t);
        }
        arch.close();
    }
public:
    PersonRepository(std::string path): path(path) {
        //this->file.open(path);
    }
    ~PersonRepository() {
        vecP.clear();
    }
    void generateData(size_t quantity) { //genera y guarda datos en un archivo txt
        if (!file.is_open()) this->file.open(path);
        for(size_t i = 0; i < quantity; ++i) file << Person::createPerson() << "\n";
        this->file.close();
    }

    void saveData() {
        if (!file.is_open()) this->file.open(path);
        for(size_t i = 0; i < vecP.size(); ++i) file << vecP.at(i) << "\n";
        this->file.close();
    }

    std::vector<Person> getVec(){
        return vecP;
    }

    void savePerson(Person person){
        vecP.push_back(person);
    }

    void readData(){
        read();
    }
};