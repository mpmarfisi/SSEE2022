#include "mbed.h"

#define BAUD_RATE   9600
#define INICIO      '$'
#define FIN         '#'
#define LARGO_DATOS 10

// Comandos
#define COMANDO_LEDS 'L'

#define VERIFICACION_RECEPCION

enum{
    REPOSO = 0,
    COMANDO,
    DATOS,
    VERIFICACION
};
/*
Baud rate: velocidad de transferencia de datos, por defecto 9600, máximo 115200
Debo tener el mismo baudrate en el transmisor y el receptor
Debemos seleccionar una de las 3 uarts del KL25:
UART0: TX PTA2,  RX PTA1, es la UART del USB
UART1: TX PTE0,  RX PTE1
UART2: TX PTE22, RX PTE23
*/
//En mbed, disponemos de la clase Serial para implementar la UART
//       PIN TX  PIN RX   
Serial pc(USBTX, USBRX, BAUD_RATE);
// BAUD_RATE: 4800, 9600, 14400, ..., 115200

/* Funciones que utlizaremos de la clase Serial:
pc.putc(char caracter) -> Enviar un caracter
pc.getc() -> Retornar un caracter
pc.readable() -> Avisa cuando hay algo disponible para leer
*/

char comando = 0; // Comando recibido por serie
char datos[LARGO_DATOS]; // Vector donde recibo los datos del serie
char estado = REPOSO; // Estado maquina de estados

DigitalOut led_red(LED_RED);
DigitalOut led_green(LED_GREEN);
DigitalOut led_blue(LED_BLUE);

void maquina_recepcion(void);
void envio_trama(char comando, char * datos);
void funcion_comandos(char comando, char * datos);

int main() {
    while(1) {
         maquina_recepcion();
    }
}

// Funcion de verificacion mediante XOR de todos los datos ingresados
char checksum_verif(char * data, int largo) // Paso el vector de datos
{
    char chksum = 0;
    // Hago el XOR de cada uno de los bytes de la trama
    for(int i = 0; i < largo; i++)
        chksum = chksum ^ data[i]; // XOR Byte a byte
    
    return chksum; // Devuelvo el byte de verificacion hecho localmente
}

/*
Defino un protocolo arbitrario
$ab...bc#
$: caracter de inicio
a: comando (1 byte), vale cualquier caracter
b...b: datos (largo indefinido)
c: verificacion
#: caracter de fin
*/
void maquina_recepcion(void)
{
    static int indice = 0; // Indice para vector de datos de comando
    
    char caracter_recibido = 0; // Caracter donde guardamos el dato recibido
    char verificacion = 0; // Verificacion local de los datos
    char verificacion_recibida = 0; // Verificacion recibida por serial
    
    // Me fijo si hay algo disponible para recibir
    if(pc.readable()){
        caracter_recibido = pc.getc(); // Leo un caracter
    }
    else
      return; // Si no hay caracter disponible me voy de la funcion, no evaluo el switch
    
    switch(estado)
    {
        case REPOSO:
            // Espero a que llegue un caracter de inicio
            if(caracter_recibido == INICIO)
                estado = COMANDO;
            break;
        case COMANDO: // El proximo byte que llegue despues del inicio es el comando
            // Recibo el comando e inmediatamente paso a recibir los datos,
            // luego se evaluará si el comando es válido
            comando = caracter_recibido;
            estado = DATOS;
            break;
        case DATOS:
            // Espero a que llegue el caracter de fin para dejar de recibir datos
            if(caracter_recibido == FIN)
            {
                indice--; // Por el ultimo aumento al igualar en el vector
                // Evaluo si mi trama llego ok, hago la verificacion
                // Utilizo un define para definir si controlo o no los datos
                #ifdef VERIFICACION_RECEPCION
                    verificacion = checksum_verif(datos, indice - 2);
                #else
                    verificacion = datos[indice]; // No controlo verificacion
                #endif
                // datos[indice] sera el byte de verificacion recibido
                verificacion_recibida = datos[indice];
                if(verificacion != verificacion_recibida)
                {
                    // Si falla la verificacion no guardo los datos
                    comando = 0;
                    // Limpio el vector
                    //    Vector    Valor   Largo
                    memset(datos,     0,    indice);
                }else{
                    // Si la verificacion es correcta ejecuto el comando
                    funcion_comandos(comando, datos);
                }
                indice = 0; // Reseteo el indice cuando termino de recibir
                estado = REPOSO;
                break;
            }
            // Recibo datos y aumento el indice
            datos[indice++] = caracter_recibido;
            //indice++; // Igual a linea anterior
            break;
    }   
}

void funcion_leds(char * datos)
{
    // Utilizo los datos que recibo para definir el estado de los leds
    // Resto '0' ya que recibo en ASCII
    led_red   = datos[0] - '0';
    led_green = datos[1] - '0';
    led_blue  = datos[2] - '0';
}

void funcion_comandos(char comando, char * datos)
{
    // En funcion de la letra que recibo ejecuto distintas funciones
    switch(comando)
    {
        case COMANDO_LEDS:
            funcion_leds(datos);
			envio_trama('L',"LEDOK"); // Envio devolución de comando recibido
            break;
    }
}
// $ab...bc#
void envio_trama(char comando, char * datos)
{
	char buffer[50];
	char verificacion = 0;
	char index = 0;
	/*			  
	sprintf nos "imprime" al buffer como si fuera un printf,
	solo que en vez de imprimir a la pantalla, escribe el string
	que le indiquemos. El valor que retorna será la cantidad de caracteres
	que logro escribir.		   $ a Datos*/
	index += sprintf(buffer, "%c%c%s", INICIO, 
									   comando, 
									   datos);
	// Hago la verificacion para agregarla a la trama
	verificacion = checksum_verif(buffer, strlen(buffer));
	/* Sumo index para no pisar lo ya escrito sobre buffer y comenzar a
	escribir después de la ultima posición escrita anteriormente */
	sprintf(buffer + index, "%c%c", verificacion, 
									FIN);
	// Envio trama con la funcion putc y el largo del buffer formado
	for(int i = 0; i < strlen(buffer); i++)
		pc.putc(buffer[i]);
}