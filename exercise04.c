/*
Ejercicio 04:
Conectar un display de 7 segmentos (c�todo com�n) al puerto F. Luego,
escribir un programa que cuente segundos desde 0 hasta 9, y que muestre
el valor del contador en el display de 7 segmentos. Utilizar la funci�n
_delay_ms() para la generaci�n de los retardos.
 */

/* Inclusiones */
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

/* Constantes y macros */

// Definici�n de pines
#define DDR_DISPLAY		DDRF
#define	PORT_DISPLAY	PORTF

/* Declaraci�n de funciones (prototipos) */
uint8_t Display_Decodificar_Digito(uint8_t num_binario);

/* Funci�n principal */
int main(void){

	uint8_t contador;

	/* Configurar todos los pines conectados a los segmentos como salida */
	DDR_DISPLAY = 0xFF;
	/* Inicializar valor de salida */
	PORT_DISPLAY = 0x00;

	/* Repetir indefinidamente */
	while(1){

		/* Cuenta desde 0 hasta 9 */
		for(contador = 0; contador <= 9; contador++){
			/* Decodificar el d�gito y mostrarlo en el display */
			PORT_DISPLAY = Display_Decodificar_Digito(contador);
			/* Incrementar el contador cada medio segundo */
			_delay_ms(500);
		}
	}

	return 0;
}

/* Definici�n de funciones */

uint8_t Display_Decodificar_Digito(uint8_t num_binario){

	/* Tabla de b�squeda para decodificar los d�gitos */
	uint8_t tabla_display[10] = {
									0x3F, // 0
									0x06, // 1
									0x5B, // 2
									0x4F, // 3
									0x66, // 4
									0x6D, // 5
									0x7D, // 6
									0x07, // 7
									0x7F, // 8
									0x6F, // 9
								};

	/* Retorna el valor del d�gito decodificado */
	return tabla_display[num_binario];
}
