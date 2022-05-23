#include <mbed.h>
#include "TM1637.h"

// Vector de digitos que prende segmentos correspondientes para cada numero
char digits[] = {63,6,91,79,102,109,125,7,127,111};

// El modulo con 4 displays y 7 segmentos se llama CATALEX
// https://www.todomicro.com.ar/arduino/862-modulo-display-4-digitos-controlador-tm1637.html
TM1637_CATALEX CATALEX(PTD2, PTD1);

int main()
{
    // Limpio displays y seteo brillo (TM1637_BRT0 minimo - TM1637_BRT7 maximo)
    CATALEX.cls(); 
    CATALEX.setBrightness(TM1637_BRT3);

    int cnt=0;
    int num;
    char numdigits[4];
    while(1){
        num=cnt;
        int i=0;
        // Voy aumentando el numero a mostrar y lo parto en unidad, decena, centena, miles
        while(num != 0)
        {
            int digit = num % 10;
            num = num / 10;
            numdigits[i]=digit;
            i++;
        }
    
        // Guardo en la variable de datos del display el número a mostrar y lo convierto con el vector digits
        //                                Digito 3              Digito 2            Digito 1            Digito 0
        TM1637::DisplayData_t dat = {digits[numdigits[3]],digits[numdigits[2]],digits[numdigits[1]],digits[numdigits[0]]};
        // Mando la información al display con la variable del display
        CATALEX.writeData(dat);

        cnt++;
    }
}
