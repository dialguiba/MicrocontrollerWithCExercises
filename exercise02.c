/*
Ejercicio 02:
Conectar cuatro LEDs (con sus respectivas resistencias) a los pines del
puerto F. Luego,implementar un pograma que cuente segundos desde 0 hasta 15.
El valor del contador debe mostrarse en los LEDs en formato binario.
Una vez que el programa funcione correctamente, implementar una funci�n que
convierta un n�mero de formato binario a formato Gray (de 4 bits). Finalmente,
el valor del contador en formato Gray debe ser mostrado en los LEDs.
Utilizar la funci�n _delay_ms() para la generaci�n de los retardos.
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

/* Constantes y macros */

// Definicion de pines
#define DDR_LEDS	DDRF
#define PORT_LEDS	PORTF

/* Declaracion de funciones (prototipo) */
void Cuenta_15(void);
uint8_t Binario_A_Gray_04_Bits(uint8_t num_bin);

/* Funcion principal */
int main(void){

	/* Configurar los 4 LSB del Puerto F como salida */
	DDR_LEDS = 0x0F;

	/* Repetir indefinidamente */
	while(1){
		Cuenta_15();
	}

	return 0;
}

/* Definicion de funciones */

void Cuenta_15(void){

	uint8_t contador;

	/* Incrementar un contador cada medio segundo */
	for(contador = 0; contador < 16; contador++){
		/* Convertir el valor binario del contador a Gray de 04 bits
		 * y mostrar el valor obtenido*/
		PORT_LEDS = Binario_A_Gray_04_Bits(contador);
		/* Espera medio segundo */
		_delay_ms(500);
	}
}


uint8_t Binario_A_Gray_04_Bits(uint8_t num_bin){

	uint8_t num_bin_desplazado;
	uint8_t num_gray;

	/* Desplazar el nomero binario */
	num_bin_desplazado = num_bin >> 1;
	/* Calcular el nuevo valor de los bits */
	num_gray = num_bin_desplazado ^ num_bin;
	/* Retornar el valor en codigo Gray de 4 bits */
	return num_gray;
}
