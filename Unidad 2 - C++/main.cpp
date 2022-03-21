#include <iostream>
#include "auto.h"
using namespace std;

int main()
{
    Auto auto1;
    Auto auto2(115503.58);
    Auto auto3(true, true);

    auto1.Prender();
    auto2.Acelerar(2.35);
    int temperatura3 = auto3.ObtenerTemperatura();

    return 0;
}

/*
    int valor1;
    char string1[50];
    float valor2;

    cout -> printf sin necesidad de especificar formato
    cin -> scanf sin necesidad de especificar formato

    cout << "Ingrese un valor entero: ";
    cin >> valor1 >> valor2;
    cin.get(); // Atrapo el enter que queda en el flujo de entrada
    cout << valor1 << endl; // endl es el equivalente al \n

    cout << "Ingrese un string: ";
    cin.getline(string1, sizeof(string1));
    cout << string1 << endl;

    cout << "Ingrese un valor decimal: ";
    cin >> valor2;
    cout << valor2 << endl;
*/
