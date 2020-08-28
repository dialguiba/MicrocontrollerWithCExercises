/*
Ejercicio 12:
Conectar 08 LEDs a uno de los puertos del microcontrolador. Luego, escribir
un programa que incremente un contador de 8 bits cada segundo y que muestre
el valor del contador, en formato binario, en los LEDS. Emplear el
Timer/Counter 0 (en Modo Normal) y su respectiva bandera de desbordamiento
para determinar el tiempo transcurrido. No est� permitido el uso de retardos
generados por software (funciones _delay_us() y _delay_ms()).
 */

/* Inclusiones */
#include <avr/io.h>
#include <stdint.h>

#define DDR_LEDS		DDRF
#define PORT_LEDS 	PORTF
#define LED			0

/* Declaraci�n de funciones (prototipos) */
void Timer0_Inicializar(void);

/* Funci�n principal */
int main(void){
	/* Contador de periodos de tiempo */
	uint8_t contador_16ms = 0;
        uint8_t contador_leds = 0;
	/* Configurar el pin del LED como salida */
	DDR_LEDS |= 0xFF;
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
			/* Si ha transcurrido 992ms (aprox 1.0 segundo) ... */
			if(contador_16ms == 62){
				/* Limpiar el contador de tiempo */
				contador_16ms = 0;
                                /* Incrementar el contador que se visualizar� */
                                contador_leds++; 
				/* Mostrar el valor del contador en los LEDs */
				PORT_LEDS = contador_leds;
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
