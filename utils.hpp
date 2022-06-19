#include <string>
#include <ctime>
#include <functional>
#include <cmath>

std::string languages[2] = {"Ingles","Frances"};

namespace Utils {
    uint32_t generateRandNumber(uint32_t from, uint32_t to) { //generar numero aleatorio
        return from + rand()% (to - from + 1);
    }
    std::string generateName(){//generar el nombre de usuario
        std::string res;
        int firstL = 'A';
        int firstN = '0';
        res.push_back((char)(firstL + rand()% (90 - firstL + 1)));
        res.push_back((char)(firstL + rand()% (90 - firstL + 1)));
        for(size_t i = 0; i < 3; ++i) {res.push_back((char)(firstN + rand()% (57 - firstN + 1)));}
        return res;
    }
    std::string generateUserName(char c1, char c2){//generar el nombre de usuario
        std::string res;
        res.push_back(c1);
        res.push_back(c2);
        int firstN = '0';
        for(size_t i = 0; i < 3; ++i) {res.push_back((char)(firstN + rand()% (57 - firstN + 1)));}
        return res;
    }
}

namespace DataStructures {
//

template<class T>
class List {
public:
    class Node {
    public:
        T value; // Valor del nodo
        Node* next; //  Puntero al siguiente nodo
        Node(T value, Node* next = nullptr) : value(value), next(next) {}
    };
private:
    Node* inicio;
    Node* fin;
    unsigned long size;
    std::function<void(T)> mostrar;
public:
    List(std::function<void(T)> mostrar) : mostrar(mostrar) {
        inicio = fin = nullptr;
        size = 0;
    }
    ~List() {
        while (size > 0) {
            popFront();
        }
        inicio = fin = nullptr;
    }
    void print() {
        std::cout << "\n";
        if (size == 0) {
            std::cout << "\nnullptr";
            return;
        }
        _print(inicio);
    }
private:
    void _print(Node* n) {
        if (n == nullptr) return;
        mostrar(n->value);
        _print(n->next);
    }
public:
    void pushBack(T value) {
        if (size == 0) {
            Node* n = new Node(value);
            inicio = n;
            fin = n;
            ++size;
        }
        else {
            Node* n = new Node(value);
            fin->next = n;
            fin = n;
            ++size;
        }
    }
    void popFront() {
        if (size == 0) return;
        Node* aux = inicio;
        if (size == 1) inicio = fin = nullptr;
        else inicio = inicio->next;
        delete aux;
        --size;
    }
    unsigned long Size() {
        return size;
    }
    Node* insertInRange(std::function<void(T)> insert, int i, int f, Node* n) {
        size_t init = i;
        Node* aux = (!n) ? this->inicio : n;
        for (init; init <= f; ++init) {
            insert(aux->value);
            aux = aux->next;
        }
        return aux;
    }
};

//


template<class T>
class HashTable {
    struct Entity {
        std::string key;
        T value;
        Entity(std::string key, T value): key(key), value(value) {}
    };
    List<Entity>** ht;
    size_t bucketSize;
    std::function<void(Entity)> show;
public:
    HashTable(std::function<void(T)> show, size_t capacity): bucketSize(capacity){
        ht = new List<Entity>*[capacity];
        for(size_t i = 0; i < bucketSize; ++i)
            ht[i] = nullptr;
        this->show = [&show](Entity e) -> void {
            show(e.value);
        };
    }

    void insert(std::string key, T value) {
        size_t index = HashFunction(key);
        if(!ht[index])
            ht[index] = new List<Entity>(this->show);
        ht[index]->pushBack(Entity(key,value));
    }
    void print(){
        for(size_t i = 0; i < bucketSize; ++i){
            std::cout << "\nIndex " << i << "\n";
            if(ht[i])
                ht[i]->print();
        }
    }
private:
    size_t HashFunction(std::string key) {
        size_t p = 0;
        for(size_t i = 0; i < key.length(); ++i) {
            int asciiValue = key[i];
            p += pow(asciiValue,i + 1);
        }
        return p % bucketSize;
    }
    // En hash tables sin listas
    size_t cuadraticProbing(size_t index) {
        size_t p = 1;
        size_t currentIndex = index;
        while(ht[index] != nullptr){
            currentIndex = index;
            currentIndex += pow(p,2);
            if(currentIndex >= bucketSize)
                currentIndex %= bucketSize;
        }
        return currentIndex;
    }
};

    template<class K, class T>
    class BinarySearchTree {
        struct Entity {
            K key;
            T value;
            Entity(K key, T value): key(key), value(value) {}
        };
        class Node {
        public:
            Entity value;
            Node* left;
            Node* right;
            Node(Entity value): value(value), left(nullptr), right(nullptr) {}
        };
        Node* root;
        size_t size;
        std::function<bool(K,K)> compare;
        std::function<bool(K,K)> equals;
        std::function<void(T)> show;
    public:
        BinarySearchTree(std::function<bool(K,K)> compare, std::function<void(T)> show, std::function<bool(K,K)> equals): compare(compare), show(show), equals(equals) {
            root = nullptr;
            size = 0;
        }
        void insert(K key, T value) {
            Node* aux = root;
            if(!root) {
                root = new Node(Entity(key,value));
                ++size;
                return;
            }
            while (true) {
                if(compare(key, aux->value.key)){
                    if(!aux->left){
                        aux->left = new Node(Entity(key,value));
                        ++size;
                        return;
                    }
                    aux = aux->left;
                } else {
                    if(!aux->right){
                        aux->right = new Node(Entity(key,value));
                        ++size;
                        return;
                    }
                    aux = aux->right;
                }
            }
        }
        void display() {
            this->_display(this->root);
        }
        T getByKey(K key) {
            Node* aux = root;
            if(aux->value.key == key)
                return aux->value.value;
            while(true) {
                if(!aux) return T();
                if(equals(key, aux->value.key))
                    return aux->value.value;
                if(compare(key, aux->value.key))
                    aux = aux->left;
                else
                    aux = aux->right;
            }
        }
    private:
        void _display(Node* n) {
            if(!n) return;
            show(n->value.value);
            std::cout << "\n";
            _display(n->left);
            _display(n->right);
        }
    };
}