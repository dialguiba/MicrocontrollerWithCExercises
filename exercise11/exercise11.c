/*
Ejercicio 11:
Conectar un LED a uno de los pines del microcontrolador. Luego, escribir un
programa que haga parpadear el LED con un periodo de 01 segundo. Emplear el
Timer/Counter 0 (en modo normal) y su respectiva bandera de desbordamiento
para determinar el tiempo transcurrido y generar los retardos. No est�
permitido el uso de retardos generados por software (funciones _delay_us()
y _delay_ms()).
 */

/* Inclusiones */
#include <avr/io.h>
#include <stdint.h>

#define DDR_LED		DDRF
#define PORT_LED 	PORTF
#define LED			0

/* Declaraci�n de funciones (prototipos) */
void Timer0_Inicializar(void);

/* Funci�n principal */
int main(void){
	/* Contador de periodos de tiempo */
	uint8_t contador_16ms = 0;
	/* Configurar el pin del LED como salida */
	DDR_LED |= (1 << LED);
	/* Configurar el Timer0 */
	Timer0_Inicializar();

	/* Repetir indefinidamente */
	while(1){
		/* Si la bandera de desbordamiento est� en ALTO */
		if(TIFR0 & (1 << TOV0)){
			/* Limpiar la bandera de desbordamiento */
			TIFR0 |= (1 << TOV0);
			/* Cargar el valor offset al Timer0 */
			TCNT0 = 5;
			/* Incrementar el contador de tiempo */
			contador_16ms++;
			/* Si ha transcurrido 496ms (aprox 0.5 segundos) ... */
			if(contador_16ms == 31){
				/* Limpiar el contador de tiempo */
				contador_16ms = 0;
				/* Conmutar el LED */
				PORT_LED ^= (1 << LED);
			}
		}
	}

	return 0;
}

/* Definici�n de funciones */

void Timer0_Inicializar(void){
	/* Configurar Pre-Scaler: 1024 */
	TCCR0B |= (1 << CS00) | (1 << CS02);
	/* Cargar el valor offset al Timer0 */
	TCNT0 = 5;
}
