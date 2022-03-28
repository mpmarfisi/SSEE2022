#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LETRAS_ABECEDARIO   26
#define CANTIDAD_CARACTERES 37
#define ESPANOL_MORSE       0
#define MORSE_ESPANOL       1

// Array de strings o vector de punteros
//							 Filas	        Columnas (en este caso largo máximo del string)
const char diccionario[CANTIDAD_CARACTERES][   10   ] = 
{
	".-",    "-...",  "-.-.",		 	// A - C
	"-..",   ".",     "..-.",  "--.", 	// D - G
	"....",  "..",    ".---",  "-.-", 	// H - K
	".-..",  "--",    "-.",    "--.--", // L - Ñ (Indice 14)
	"---",   ".--.",  "--.-",  ".-.", 	// O - R
	"...",   "-",     "..-",   "...-", 	// S - V
	".--",   "-..-",  "-.--",  "--..", 	// W - Z
	"-----", ".----", "..---", "...--", // 0 - 3
	"....-", ".....", "-....", "--...", // 4 - 7
	"---..", "----."                    // 8 - 9
};
/*
Cada posicion del vector sera un puntero al inicio de cada string
*diccionario[0] = '.', *diccionario[1] = '-'
diccionario[2][1] -> diccionario[2]:    "-.-."
					 diccionario[2][1]: '.'
*/

// Funcion para convertir indice obtenido en comparacion con strings de morse a español
unsigned char convertIndex(int index)
{
    if(index == 14) // En el indice 14 del diccionario está la letra Ñ
        return 165; // Letra Ñ

    else if(index > ('Z' - 'A' + 1)) // Si estoy en el rango de los numeros (+1 por la Ñ)
        // Sumo solo lo que me excedo del rango total de las letras para los números, +1 por la ñ
        index = '0' + (index - (LETRAS_ABECEDARIO + 1)); 
    else if(index > ('O' - 'A'))  // Corro 1 el indice si estoy por arriba de la O, porque está la ñ en el medio
        index += 'A' - 1;

    else
        index += 'A';

    return index;
}

int main(void) {
	unsigned char frase[100];
    unsigned int modo = 0;
    unsigned char* limitador;
    unsigned int offset = 0;

    // Pongo un do-while para tomar otro valor si ingresan valores erroneos
    do{
        printf("Ingrese modo de operacion (0 espanol-morse, 1 morse-espanol): ");
        scanf("%d",&modo);
    } while(modo > 1);

    fflush(stdin); // Limpio enter

    printf("\nIngrese frase a traducir: ");
    fgets(frase, 100, stdin);     // Obtengo string a utilizar
    frase[strlen(frase) - 1] = 0; // Limpio enter fgets
    
    if(modo == ESPANOL_MORSE)
    {
	    for(int i = 0; i < strlen(frase); i++)
	    {
            if(frase[i] == ' ')
                continue; // Salteo loop si tengo un espacio

            if(frase[i] == 164 || frase[i] == 165) // Si es ñ o Ñ
                printf("%s ",diccionario[14]);
            else{
		        frase[i] = frase[i] >= 'a' ? frase[i] - ('a' - 'A') : frase[i]; // Paso todo a mayuscula
                offset = frase[i] >= 'O' ? 1 : 0; // Corro 1 el indice si estoy por arriba de la O, porque está la ñ en el medio
                printf("%s ",diccionario[frase[i] - 'A' + offset]); // Adecuo la letra al indice correspondiente
            }
	    }
    }else if(modo == MORSE_ESPANOL)
    {  
        /*
        char * strtok ( char * str, const char * delimiters );
        strok buscará dentro del string indicado el delimitador indicado, y cortará o tokenizará el string en partes
        donde vaya encontrando este caracter separador. En nuestro caso, la utilizaremos para ir "cortando" el string
        en partes donde haya un espacio, y así poder ir comparando cada letra de morse individualmente. Retornará un 
        puntero a la posición donde encuentre el delimitador.
        */
	    limitador = strtok(frase, " "); // Busco primera aparición del espacio

        for(int i = 0; i < CANTIDAD_CARACTERES; i++)
	    {	
            // Comparo el string ingresado contra todo mi diccionario para obtener la letra correspondiente
		    if(!memcmp(diccionario[i], frase, strlen(frase)))
            {
                printf("%c", convertIndex(i));
                break;
            }
	    }

        while(limitador != NULL)
        {
            /*
            Busco apariciones consiguientes del espacio. Indicando NULL, la funcion seguira recorriendo el ultimo string
            que recortó.
            */
            limitador = strtok(NULL, " "); 
            for(int i = 0; i < CANTIDAD_CARACTERES; i++)
	        {	
		        if(strcmp(diccionario[i], limitador) == 0)
                    printf("%c", convertIndex(i));
	        }
            
        }
    }
    return 0;
}