/*
Ejercicio 09:
Conectar dos pulsadores y un LED al microcontrolador. Luego, escribir un
programa que habilite las resistencias pul-up internas de los pines
conectados a los pulsadores, y que encienda el LED solo si los dos pulsadores
se encuentran presionados.
 */

/* Inclusiones */
#include <avr/io.h>
#include <stdint.h>

/* Constantes y macros */

// Definici�n de pines
#define DDR_BOTONES		DDRK
#define	PORT_BOTONES	PORTK
#define	PIN_BOTONES		PINK
#define BOTON_01		0
#define BOTON_02		3

#define DDR_LED		DDRF
#define PORT_LED	PORTF
#define LED			3

//  Macros del programa
#define LED_ON()		PORT_LED |= (1 << LED)
#define LED_OFF()		PORT_LED &= ~(1 << LED)

#define BOTON_01_PULSADO	(!(PIN_BOTONES & (1 << BOTON_01)))
#define BOTON_02_PULSADO	(!(PIN_BOTONES & (1 << BOTON_02)))


/* Funci�n principal */
int main(void){

	/* Habilitar las resistencias pull-up internas de los pines
	 * conectados a los pulsadores */
	PORT_BOTONES |= (1 << BOTON_01) | (1 << BOTON_02);

	/* Configurar el pin del LED como salida */
	DDR_LED |= (1 << LED);

	/* Repetir indefinidamente */
	while(1){
		if(BOTON_01_PULSADO && BOTON_02_PULSADO){
			LED_ON();
		}else{
			LED_OFF();
		}
	}
	return 0;
}
