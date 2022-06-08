#include <iostream>
#include <string>
using namespace std;

int main(){
    string s = "202115595";
    int a=0;
    for (auto e:s) a+=(e-'0');
    cout << a;
    cout << endl;
    a %= 21;
    cout << a;
    cout << "\nEjercicios: ";
    for (int i = 0; i < 5; i++) {
        cout << a + (i*2) << " ";
    }
    
}