/*
Ejercicio 03:
Empleando la funci�n _delay_us(), escribir una funci�n que permita generar
una se�al PWM de, aproximadamente, 10KHz. La funci�n debe recibir el duty
cycle como par�metro. Verificar el correcto funcionamiento de la funci�n,
midiendo el pin de salida con un osciloscopio.
De no contar con un osciloscopio, conectar el pin a un LED (con su respectiva
resistencia) y verificar que la intensidad de la luz emitida por el LED cambia
al modificar el duty cycle.
 */

/* Inclusiones */
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

/* Constantes y macros */

// Definici�n de pines
#define DDR_PWM		DDRF
#define PORT_PWM	PORTF
// Macros del programa
#define PWM_ALTO()	PORT_PWM = 0x01;
#define PWM_BAJO()	PORT_PWM = 0x00;


/* Declaraci�n de funciones (prototipos) */
void Genera_PWM(uint8_t duty_cycle);

/* Funci�n principal */
int main(void){

	/* Configurar PF0 como salida */
	DDR_PWM = 0x01;

	/* Repetir indefinidamente */
	while(1){
		Genera_PWM(2);
	}

	return 0;
}

/* Definici�n de funciones */
void Genera_PWM(uint8_t duty_cycle){

	uint8_t contador;

	/* Restringir el valor del duty cycle */
	if(duty_cycle >= 100){
		duty_cycle = 100;
	}

	/* Generar la se�al */
	for(contador = 0; contador <= 100; contador++){
		if(contador < duty_cycle){
			PWM_ALTO();
		}else{
			PWM_BAJO();
		}
		_delay_us(1);
	}
}
