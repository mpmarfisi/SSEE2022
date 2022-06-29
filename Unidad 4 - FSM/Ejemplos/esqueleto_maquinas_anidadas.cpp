#include "mbed.h"

/*
Consigna:
El sistema en reposo comienza con el led RGB encendido en todos sus colores.
- Si se presiona P0 el led pasa a hacer una secuencia G - B - R en intervalos de 200ms. Para volver al reposo se debe presionar P2 durante 3s.
- Si se presiona P1 se prende el G y R, y se espera la presión de P0 o P2.
	. Si se presiona P0 el sistema alterna entre R y B en intervalos de 500ms. Para volver al reposo se debe presionar 2 veces P1 y luego 2 veces P2.
	. Si se presiona P2 el sistema alterna entre G y B. Para volver al reposo se debe presionar 2 veces P1
*/

#define ON 0
#define OFF 1

// Definicion de estados maquina principal
enum{
    REPOSO = 0, // 0
    MODO1, // 1
	ESPERA,
	MODO2,
	MODO3
};

// Definicion de estados secuencia 1
enum{
	GREEN_1,
	BLUE_1,
	RED_1
};

// Definicion de estados secuencia 2
enum{
	RED_2,
	BLUE_2
};

// Definicion de estados secuencia 3
enum{
	GREEN_3,
	BLUE_3
};

// Definicion de estados presiones
enum{
	P1,
	P2
};

void maquina_principal(void);
void secuencia1(void);
void secuencia2(void);
void secuencia3(void);
void presiones(void);
int Debounce(int index);

int main() {
    while(1) {
		// En el lazo infinito solo estarán presentes mis máquinas de estado hechas en FUNCIONES
		for(int i = 0; i < CANT_PULSADORES; i++)
            pulsadores[i] = Debounce(i);
        maquina_principal();
    }
}

void maquina_principal(void)
{
    static int estado = REPOSO;
    switch(estado)
    {
        case REPOSO:
			R = ON;
			G = ON;
			B = ON;
            // Completar transiciones
            break;
        case MODO1:
			// Ejecuto la maquina de la secuencia del modo 1
            secuencia1();
			// Completar transiciones
            break;
		case ESPERA:
			R = ON;
			G = ON;
			B = OFF;
			// Completar transiciones
			break;
		case MODO2:
			// Ejecuto la maquina de la secuencia del modo 2 y otra maquina para detectar la secuencia de presiones
			secuencia2();
			variable = presiones();
			// Completar transiciones
			break;
		case MODO3:
			// Ejecuto la maquina de la secuencia del modo 3
			secuencia3();
			// Completar transiciones
			break;
		// Importante siempre poner el estado default que será el estado de RESET
        default:
            estado = REPOSO;
            break;
    }
}

void secuencia1(void)
{
	static int estado = GREEN_1;
    switch(estado)
    {
		case GREEN_1:
			G = ON;
			B = OFF;
			R = OFF;
			// Completar transiciones de tiempo
			break;
		case BLUE_1:
			G = ON;
			B = OFF;
			R = OFF;
			// Completar transiciones de tiempo
			break;
		case RED_1:
			G = ON;
			B = OFF;
			R = OFF;
			// Completar transiciones de tiempo
			break;
		default:
			estado = GREEN_1;
	}
}

/*
Secuencia2 y secuencia3 serán muy similares en estructura a secuencia1 solo que con dos estados,
completen los esqueletos de las misma.
*/

void presiones(void)
{
	static int estado = P1;
    int salida = 0; // En esta variable almaceno el valor de salida que se genera luego de la secuencia ingresada
	switch(estado)
    {
		case P1;
			// Completar transiciones
			break;
		case P2:
			// Completar transiciones
			// Una vez que vuelvo a P1 después de las dos pulsaciones de P2 pongo salida en 1 y en P1 la vuelvo a poner en
			// 0 para generar un solo pulso
			break;
	}
	// Devuelvo el valor para utilizarlo en mi maquina principal
	return salida;
}
