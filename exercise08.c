/*
Ejercicio 08:
Conectar una resistencia pull-down y un pulsador a uno de los pines del
microcontrolador, y un LED a otro. Luego, escribir un programa que encienda
el LED mientas el pulsador se encuentre presionado. Una vez que el programa
funcione correctamente, cambiar la resistencia pull-down por una resistencia
pull-up y modificar el c�digo para que el comportamiento del sistema se
mantenga (el LED debe encender mientras el pulsador se encuentre presionado).
 */

/* Inclusiones */
#include <avr/io.h>
#include <stdint.h>

/* Constantes y macros */

// Definici�n de pines
#define DDR_BOTON	DDRK
#define	PORT_BOTON	PORTK
#define	PIN_BOTON	PINK
#define BOTON		0

#define DDR_LED		DDRF
#define PORT_LED	PORTF
#define LED			3

//  Macros del programa
#define LED_ON()		PORT_LED |= (1 << LED)
#define LED_OFF()		PORT_LED &= ~(1 << LED)

// Si la resistencia es pull-up usar este
#define BOTON_PULSADO	(!(PIN_BOTON & (1 << BOTON)))
/*// Si la resistencia es pull-down usar este
#define BOTON_PULSADO	(PIN_BOTON & (1 << BOTON))
*/


/* Funci�n principal */
int main(void){

	/* Configurar el pin del LED como salida */
	DDR_LED |= (1 << LED);

	/* Repetir indefinidamente */
	while(1){
		if(BOTON_PULSADO){
			LED_ON();
		}else{
			LED_OFF();
		}
	}
	return 0;
}
