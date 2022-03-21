#include <stdio.h>
#include <stdlib.h>

// Comento el define para elegir que fragmento quiero que corra

//#define EJ_PUNTEROS_1
#define EJ_PUNTEROS_2

int main()
{
/*
#ifdef: verifica si está definido
#if: evalua una condición, EJ_PUNTEROS_1 == 4
#ifndef: verifica si no está definido

Controlo que fragmentos de código quiero que
se compilen y corran. Es muy útil para usar en los programas
cuando quiero ejecutar algo de vez en cuando sin necesidad
de utilizar otro programa, por ejemplo, para hacer una prueba
o probar casos particulares de funcionamiento.
*/

// Si está definido EJ_PUNTEROS_1 se ejecutará este código
#ifdef EJ_PUNTEROS_1
    int* puntero;
    int numero = 123;
    // Utilizo el operador & para obtener la dirección de memoria de numero
    puntero = &numero;

    printf("direcci\242n: %x\n", puntero);
    printf("contenido de %x --> %d\n", puntero, numero);
#endif // EJ_PUNTEROS_1

// Si está definido EJ_PUNTEROS_1 se ejecutará este código
#ifdef EJ_PUNTEROS_2
    char vector[5] = {0,1,2,3,4};
    // vector es un puntero a la posicion inicial del vector
    // vector es un char* a la pos inicial.
    for(int i = 0; i < 5; i++)
        printf("%d %d\n", vector + i, *(vector + i)); // *(vector + i) = vector[i]
    /*
    Gracias a la aritmética de punteros, al sumar un valor a un puntero
    este sabe automáticamente cuánto tiene que sumar para llegar a la siguiente
    posición de memoria donde hay un valor.
    Por ejemplo en el caso del int:
    Si vector = 0x00F0 -> vector+1 = 0x00F4
    *(vector) = 0
    *(vector + 1) = 1
    */
#endif // EJ_PUNTEROS_2
    return 0;
}