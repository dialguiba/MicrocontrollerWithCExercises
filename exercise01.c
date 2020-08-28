/*
Ejercicio 01:
Conectar un pulsador a uno de los pines del microcontrolador, y conectar un
LED a otro pin. Luego, escribir un programa que haga que el pulsador se
comporte como un botón ON/OFF: Si el LED se encuentra apagado, al presionar
el pulsador el LED debe encenderse; si el LED se encuentra encendido, al
presionar el pulsador el LED debe apagarse (ver el diagrama de flujo
proporcionado por el profesor como referencia).
 */

/* Definición de la frecuencia del procesador */
#define F_CPU	16000000

/* Inclusiones */
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

/* Constantes y macros */
#define DDR_DISPLAY1		DDRF
#define	PORT_DISPLAY1	PORTF
#define DDR_DISPLAY2		DDRK
#define	PORT_DISPLAY2	PORTK
#define DDR_LED  DDRB
#define PORT_LED  PORTB


/* Variables globales */


/* Declaración de funciones (prototipos) */
uint8_t Display_Decodificar_DigitoCATODO(uint8_t num_binario);
uint8_t Display_Decodificar_DigitoANODO(uint8_t num_binario);

/* Función principal */
int main(void){
	uint8_t contador1;
	uint8_t contador2;
	DDRK=0x7F;
	DDR_DISPLAY1 = 0xFF;
	PORTK = 0x80;
	PORT_DISPLAY1 = 0x00;
	// Habilitar la resistencia pull-up internas para el pulsador
	PORTK |= (1 << 7);
	uint8_t estado=0;
	// Configurar el pin del LED (PB7) como salida
	DDRB |= (1 << 7);

	// Repetir indefinidamente

while(1){
		// ----- Hacer esto si el pulsador es presionado ----
		if(!(PINK & (1 << 7))){

			// Conmutar el LED
			//PORTB |= (1 << 7);
			estado=1;
			PORTB &= ~(1 << 7);
		}
		else
		{
			PORT_DISPLAY1 = Display_Decodificar_DigitoCATODO(0);
			PORT_DISPLAY2 = Display_Decodificar_DigitoANODO(0);
		//PORTB &= ~(1 << 7);
		
		}

		if(estado==1)
		{
			
			for(contador1 = 0; contador1 <= 6; contador1++)
			{

				/* Decodificar el dígito y mostrarlo en el display */
				PORT_DISPLAY2 = Display_Decodificar_DigitoANODO(contador1);
				/* Incrementar el contador cada medio segundo */
				_delay_ms(300);
				if(contador1<6)
				{
					for(contador2 = 0; contador2 <= 9; contador2++)
					{/* Decodificar el dígito y mostrarlo en el display */
						PORT_DISPLAY1 = Display_Decodificar_DigitoCATODO(contador2);
						/* Incrementar el contador cada medio segundo */
					_delay_ms(300);}
				}
				
				PORT_DISPLAY1 = Display_Decodificar_DigitoCATODO(0);
				
				}
			
			estado=0;
			PORTB |= (1 << 7);
		}
		// ---------------------------------------------------

		// Incluir este retardo para evitar problemas de rebotes
		_delay_ms(20);
	
			}
	// Fin de la función principal
	return 0;
}
		

/* Definición de funciones */

uint8_t Display_Decodificar_DigitoCATODO(uint8_t num_binario){

	/* Tabla de búsqueda para decodificar los dígitos */
	uint8_t tabla_display1[11] = {
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
		0x3F, // 10
	};

	/* Retorna el valor del dígito decodificado */
	return tabla_display1[num_binario];
}

uint8_t Display_Decodificar_DigitoANODO(uint8_t num_binario){

	/* Tabla de búsqueda para decodificar los dígitos */
	uint8_t tabla_display2[10] = {
		~0x3F, // 0
		~0x06, // 1
		~0x5B, // 2
		~0x4F, // 3
		~0x66, // 4
		~0x6D, // 5
		~0x7D, // 6
		~0x07, // 7
		~0x7F, // 8
		~0x6F, // 9
	};

	/* Retorna el valor del dígito decodificado */
	return tabla_display2[num_binario];
}
