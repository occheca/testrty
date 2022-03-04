
#include <iostream>; 

void exercise1();
void exercise2(); 
void exercise3(); 

using namespace std; 

int main()
{
    int opc = 0; 

    do {
        cout << endl;
        cout << "1) Test 1 " << endl;
        cout << "2) Test 2 " << endl;
        cout << "3) Test 3 " << endl;
        cout << "4) Exit " << endl;
        cin >> opc; 
        switch (opc) {
            case 1:
                exercise1();
                break;
            case 2:
                exercise2();
                break;
            case 3:
                exercise3(); 
                break;
            }

    } while (opc != 4); 

    return 0;
}