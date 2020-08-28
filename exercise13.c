/*
Ejercicio 13:
Modificar el programa del ejercicio anterior para que el Timer/Counter 0
funcione como contador: que incremente la cuenta cada vez que reciba un
flanco de subida en el pin T0. Adem�s, modificar el programa para generar
una se�al cuadrada con un periodo de 01 segundo a trav�s de uno de sus pines.
Verificar que el valor binario mostrado en los LEDs se incrementa mientras
el pin que genera la se�al se encuentra conectado al pin T0.
 */

/* Inclusiones */
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#define DDR_LEDS	DDRF
#define PORT_LEDS 	PORTF

#define DDR_SIGNAL	DDRK
#define PORT_SIGNAL	PORTK
#define SIGNAL 0

#define PORT_EXT_CLOCK	PORTD
#define EXT_CLOCK		7

/* Declaraci�n de funciones (prototipos) */
void Timer0_Inicializar(void);

/* Funci�n principal */
int main(void){
	/* Configurar los pines de los LEDs como salidas */
	DDR_LEDS = 0xFF;
	/* Configurar el pin de la se�al como salida */
	DDR_SIGNAL |= (1 << SIGNAL);
	/* Activar la resistencia pull-up del pin del clock externo (para reducir
	 * los efectos del ruido al desconectar la se�al de clock) */
	PORT_EXT_CLOCK |= (1 << EXT_CLOCK);
	/* Configurar el Timer0 */
	Timer0_Inicializar();

	/* Repetir indefinidamente */
	while(1){
		/* Generar una se�al cuadrada con 1 segundo de periodo */
		PORT_SIGNAL |= (1 << SIGNAL);
		_delay_ms(500);
		PORT_SIGNAL &= ~(1 << SIGNAL);
		_delay_ms(500);
		/* Mostrar el valor del contador del Timer0 en los LEDs */
		PORT_LEDS = TCNT0;
	}

	return 0;
}

/* Definici�n de funciones */

void Timer0_Inicializar(void){
	/* Configurar fuente de reloj externa (flanco de subida) */
	TCCR0B |= (1 << CS00) | (1 << CS01) | (1 << CS02);
}
