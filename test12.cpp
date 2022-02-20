// MultiIndiex.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

struct Key {
    int x;
    int y;

    bool operator<(const Key& param) const
    {
        bool result = false;

        if (this->x != param.x) {
            result = (this->x < param.x);
        }
        else {
            result = (this->y < param.y);
        }
        return result;
    }

    bool operator==(const Key& param) const {
        return (this->x == param.x && this->y == param.y);
    }

};

struct hashFnKey
{
    size_t operator() (const Key& param) const
    {
        return hash<int>()(param.x)^hash<int>()(param.y);
    }  
};

void exercise1(const vector<Key>& arrKeys);
void exercise2(const vector<Key>& arrKeys);

int main()
{
    vector<Key> arrKeys = {
        { 110,220 },
        { 102,230 },
        { 101,340 },
        { 101,339 },
        { 115,220 },
        { 101,341 },
        { 115,219 }
    };
    exercise1(arrKeys);
    exercise2(arrKeys);

    return 0;
}

void exercise1(const vector<Key> & arrKeys) {

    map<Key, size_t> mp; 
    size_t i,l; 

    for (i = 0, l=arrKeys.size(); i < l; i++) {
        mp[arrKeys[i]] = i;
    }

    //print data
    cout << endl << "===== Exercise 1: map =====";
    for (auto x : mp) {
        cout << x.first.x << " " << x.first.y << " " << x.second << endl;
    }
    cout << endl; 

};

void exercise2(const vector<Key>& arrKeys) {
    unordered_map<Key, size_t, hashFnKey> ump;
    size_t i,l; 

    //load data
    for (i = 0, l=arrKeys.size(); i < l; i++) {
        ump[arrKeys[i]] = i;
    }

    //print data
    cout << endl << "===== Exercise 2: unordered_map ====="; 
    for (auto x : ump) {
        cout << x.first.x << " " << x.first.y << " " << x.second << endl;
    }
    cout << endl;

}



// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
