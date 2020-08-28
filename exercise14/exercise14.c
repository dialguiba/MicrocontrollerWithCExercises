/*
Ejercicio 14:
Conectar un pulsador y 02 LEDs al microcontrolador. Luego, escribir un
programa que haga que el pulsador se comporte como un bot�n ON/OFF para
uno de los LEDs, mientras que el otro LED parpadea cada segundo. El segundo
LED debe mantenerse parpadeando, sin importar que el pulsador se encuentre
presionado o no. No olvide habilitar la resistencia pull-up interna para el
pulsador. No se permite el uso de retardos generados por software.
 */

/* Inclusiones */
#include <avr/io.h>
#include <stdint.h>

/*Definici�n de pines */

#define PORT_BOTON	PORTK
#define PIN_BOTON	PINK
#define BOTON		0

#define DDR_LEDS	DDRF
#define PORT_LEDS	PORTF
#define LED_01		1
#define LED_02		2

/* Macros */
#define LED_01_TOGGLE()	PORT_LEDS ^= (1 << LED_01)
#define LED_02_TOGGLE()	PORT_LEDS ^= (1 << LED_02)

/* Declaraci�n de funciones (prototipos) */
void Timer0_Inicializar(void);
uint8_t Evento_Boton_Pulsado(void);

/* Funci�n principal */
int main(void){

	uint8_t contador_2ms = 0;
	uint8_t contador_10ms = 0;

	/* Configurar los pines de los LEDs como salida */
	DDR_LEDS |= (1 << LED_01) | (1 << LED_02);
	/* Habilitar la resistencia pull-up del pin del bot�n */
	PORT_BOTON |= (1 << BOTON);
	/* Configurar el Timer 0 */
	Timer0_Inicializar();

	while(1){
		/* Si la bandera de comparaci�n est� en ALTO */
		if(TIFR0 & (1 << OCF0A)){
			/* Limpiar la bandera de comparaci�n */
			TIFR0 |= (1 << OCF0A);
			/* Incrementar el contador de 2ms */
			contador_2ms++;
			/* Si han transcurrido 10ms (para reducir efectos de rebote)*/
			if(contador_2ms == 5){
				/* Limpiar el contador de 2ms */
				contador_2ms = 0;
				/* Leer si el bot�n ha sido pulsado y conmutar LED_01, de ser el caso */
				if(Evento_Boton_Pulsado()){
					LED_01_TOGGLE();
				}
                                /* Incrementar el contador de 10ms */
				contador_10ms++;
				/* Si ha transcurrido medio segundo */
				if(contador_10ms == 50){
					/* Limpia el contador de 10ms */
					contador_10ms = 0;
					/* Conmutar el LED_02 */
					LED_02_TOGGLE();
				}
			}
		}
	}

	return 0;
}

void Timer0_Inicializar(void){
	/* Configurar el Timer0 para que la bandera de comparaci�n se
	 * active cada 2ms */

	/* Configurar pre-scaler: 256 */
	TCCR0B |= (1 << CS02);
	/* Configurar el Timer0 para trabajar en modo CTC */
	TCCR0A |= (1 << WGM01);
	/* Cargar el valor TOP en el registro OCRA */
	OCR0A = 124;
}



uint8_t Evento_Boton_Pulsado(void){

	// Estado del boton: 0-> boton presionado, 1-> boton liberado
	static uint8_t boton_estado_anterior = 1;
	uint8_t  boton_estado_actual;
	uint8_t evento_boton_pulsado;

	// Leer el estado actual del bot�n (presionado o liberado)
	boton_estado_actual = (PIN_BOTON & (1 << BOTON));
	// Detectar si ha ocurrido un flanco de bajada en el pin del bot�n
	evento_boton_pulsado = boton_estado_anterior && (!boton_estado_actual);
	// Actualizar el estado anterior del bot�n
	boton_estado_anterior = boton_estado_actual;
	// Retorna '1' si el bot�n ha sido pulsado; de lo contrario, retorna '0'
	return evento_boton_pulsado;
}



