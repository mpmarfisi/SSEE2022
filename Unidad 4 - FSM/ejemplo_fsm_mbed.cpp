#include "mbed.h"

// Definicion de estados
enum{
    ESTADO_OFF = 0, // 0
    ESTADO_ON // 1
};
#define BASE_TIEMPO 0.001 // 1ms

// Salidas
DigitalOut led(LED_RED);

// Varios
Ticker tick;
int tiempo = 500; // 500ms, tiempo de titileo

// Debug para imprimir por el USB
Serial pc(USBTX, USBRX); // Pin TX, pin RX

// Funcion del ticker
void Interrupcion(void)
{
    if(tiempo > 0)
        tiempo--;
}

// Protocolo funcion maquina de estados, respetar nomenclatura
void LED_Step(void);

int main() {
    // Inicializaciones
    tick.attach(&Interrupcion, BASE_TIEMPO);
    while(1) {
        LED_Step();
    }
}

void LED_Step(void)
{
    static int estado = ESTADO_OFF;
    switch(estado)
    {
        // Cada estado de la maquina sera representado con un case
        case ESTADO_OFF:
            led = 0; // Maquina de Moore, defino el estado de la salida en el estado actual
            if(tiempo == 0) // Las transiciones a los estados mediante if
            {
                pc.printf("ON\n");
                tiempo = 500;
                estado = ESTADO_ON;
            } 
            break;
        case ESTADO_ON:
            led = 1;
            if(tiempo == 0)
            {
                pc.printf("OFF\n");
                tiempo = 500;
                estado = ESTADO_OFF;
            } 
            break;
        default:
            estado = ESTADO_OFF;
            break;
    }
}