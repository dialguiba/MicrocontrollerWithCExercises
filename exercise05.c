/*
Ejercicio 04:
Conectar un LED a cada uno de los pines del puerto F. Luego, seguir las
indicaciones del profesor para la implementaci�n de 03 secuencias de
encendido de los LEDs. Despu�s, escribir 03 funciones para implementar
las secuencias (una funci�n por cada secuencia).
 */

/* Inclusiones */
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

/* Constantes y macros */

// Definici�n de pines
#define	DDR_LEDS	DDRF
#define PORT_LEDS	PORTF

/* Declaraci�n de funciones (prototipos) */
void Secuencia_LEDs_01(void);
void Secuencia_LEDs_02(void);
void Secuencia_LEDs_03(void);

/* Funci�n principal */
int main(void){

	/* Configurar todos los pines conectados a los LEDs como salida */
	DDR_LEDS = 0xFF;

	/* Repetir indefinidamente */
	while(1){
		Secuencia_LEDs_01();
		Secuencia_LEDs_01();
		Secuencia_LEDs_02();
		Secuencia_LEDs_03();
	}

	return 0;
}


/* Definici�n de funciones */

void Secuencia_LEDs_01(void){

	uint8_t posicion;

	for(posicion = 0; posicion <= 7; posicion++){
		PORT_LEDS = (1 << posicion);
		_delay_ms(500);
	}
}

void Secuencia_LEDs_02(void){

	int8_t posicion;

	/* Encendido de ida de los LEDs */
	for(posicion = 0; posicion <= 7; posicion++){
		PORT_LEDS = (1 << posicion);
		_delay_ms(500);
	}

	/* Encendido de regreso de los LEDs */
	for(posicion = 6; posicion >= 0; posicion--){
		PORT_LEDS = (1 << posicion);
		_delay_ms(500);
	}
}

void Secuencia_LEDs_03(void){

	int8_t posicion;

	/* Apaga todos los LEDs antes de iniciar la secuencia */
	PORT_LEDS = 0;

	/* Secuencia de encendido de los LEDs */
	for(posicion = 0; posicion <= 7; posicion++){
		PORT_LEDS |= (1 << posicion);
		_delay_ms(500);
	}

	/* Secuencia de apagado de los LEDs */
	for(posicion = 7; posicion >= 0; posicion--){
		PORT_LEDS &= ~(1 << posicion);
		_delay_ms(500);
	}
}
