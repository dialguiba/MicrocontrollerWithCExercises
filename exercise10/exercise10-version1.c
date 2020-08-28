/*
Ejercicio 10:
Conectar un pulsador a uno de los pines del microcontrolador, y conectar
un LED a otro pin. Luego, escribir un programa que haga que el pulsador se
comporte como un bot�n ON/OFF: Si el LED se encuentra apagado, al presionar
el pulsador el LED debe encenderse; si el LED se encuentra encendido, al
presionar el pulsador el LED debe apagarse.
 */

/* Inclusiones */
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

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
#define LED_TOGGLE()	PORT_LED ^= (1 << LED)

#define BOTON_PULSADO	(!(PIN_BOTON & (1 << BOTON)))


/* Funci�n principal */
int main(void){

	/* Habilita la resistencia pull-up interna del pin conectado al pulsador */
	PORT_BOTON |= (1 << BOTON);

	/* Configurar el pin del LED como salida */
	DDR_LED |= (1 << LED);

	/* Repetir indefinidamente */
	while(1){
		/* Si el bot�n est� pulsado ... */
		if(BOTON_PULSADO){
			/* Conmutar el estado del LED */
			if(PORT_LED & (1 << LED)){
				LED_OFF();
			}else{
				LED_ON();
			}

			while(BOTON_PULSADO){
				// Esperar hasta que el bot�n se haya liberado
			}
		}

		/* Esperar un momento (para evitar los efectos de los rebotes)*/
		_delay_ms(5);
	}

	return 0;
}

