#include "mbed.h"

#define CANT_PULSADORES 3
#define BASE_TIEMPO     0.001

// Estados antirrebote
enum {
    SUELTO, QUIZA_PRESIONADO, PRESIONADO, QUIZA_SUELTO
};

// BusIn me permite hacer un "vector" de entradas y accederlo con [] para cada
// posicion individual
BusIn pulsadores(PTD1, PTD2, PTD3);
int salidas[CANT_PULSADORES];

// BusOut me permite hacer un "vector" de entradas y accederlo con [] para cada
// posicion individual
BusOut LEDs(LED_RED, LED_GREEN, LED_BLUE);

// Ticker
Ticker tim;
int time_puls[CANT_PULSADORES] = {0};

// Antirrebote para N pulsadores
int Debounce(int index);


// Decremento cada 1ms //
void TimerDecremento(void)
{
    // Decremento variables establecidas en las maquinas cada 1ms
    // obteniendo asi los tiempos deseados
    for(int i = 0; i < CANT_PULSADORES; i++)
        if (time_puls[i] > 0)
            time_puls[i]--;
}

int main() {
    tim.attach(&TimerDecremento, BASE_TIEMPO);
    
    while(1) {
        for(int i = 0; i < CANT_PULSADORES; i++)
        {
            salidas[i] = Debounce(i);
            LEDs[i] = salidas[i]; // Utilizo vector de salidas de los pulsadores para lo que necesite
            // y seteo cada LED individualmente
        } 
    }
}

// ANTIRREBOTE //
int Debounce(int index)
{
    int Estado = 0; 
    static int DEBOUNCE_estado[CANT_PULSADORES] = {SUELTO};
    switch (DEBOUNCE_estado[index]) {
        case SUELTO:
            Estado = 0;
            // Accedo a cada entrada individualmente mediante el BusIn
            if (pulsadores[index] == 1) {
                DEBOUNCE_estado[index] = QUIZA_PRESIONADO;
                time_puls[index] = 30;
            }
            break;
        case QUIZA_PRESIONADO:
            if (time_puls[index] == 0) {
                if (pulsadores[index] == 1) {
                    DEBOUNCE_estado[index] = PRESIONADO;
                }
                if (pulsadores[index] == 0) {
                    DEBOUNCE_estado[index] = SUELTO;
                }
            }
            break;
        case PRESIONADO:
            Estado = 1;
            if (pulsadores[index] == 0) {
                DEBOUNCE_estado[index] = QUIZA_SUELTO;
                time_puls[index] = 30;
            }
            break;
        case QUIZA_SUELTO:
            if (time_puls[index] == 0) {
                if (pulsadores[index] == 0) {
                    DEBOUNCE_estado[index] = SUELTO;
                }
                if (pulsadores[index] == 1) {
                    DEBOUNCE_estado[index] = PRESIONADO;
                }
            }
            break;
    }
    return Estado;
}
