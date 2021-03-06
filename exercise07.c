/*
Ejercicio 07:
Del ejercicio anterior, escribir una funci�n para gestionar el orden de
activaci�n de los displays. Al ser llamada, la funci�n debe deshabilitar
todos los displays, cargar el d�gito correspondiente al puerto F, activar
el habilitador correspondiente (conectado al puerto K) y dejar indicado el
display que deber� ser activado la pr�xima vez que se invoque a la funci�n.
Se recomienda emplear variables locales est�ticas.
 */

/* Inclusiones */
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

/* Constantes y macros */

// Definici�n de pines
#define DDR_DISPLAY		DDRF
#define	PORT_DISPLAY	PORTF
#define DDR_ENABLES		DDRK
#define PORT_ENABLES	PORTK

// Constantes del programa
#define N_DISPLAYS		4
#define MASCARA_ENABLES	(0x0F)

/* Variables globales */
uint8_t display_buffer[N_DISPLAYS];

/* Declaraci�n de funciones */
uint8_t Display_Decodificar_Digito(uint8_t num_binario);
void Display_Decodificar_Entero_Decimal(uint16_t num_binario);
void Display_Gestionar_Habilitadores(void);

/* Funci�n principal */
int main(void){

	uint16_t numero = 1234;

	/* Configurar los pines de los segmentos como salida */
	DDR_DISPLAY = 0xFF;

	/* Configurar los pines de los habilitadores como salida */
	DDR_ENABLES |= MASCARA_ENABLES;

	/* Extraer, decodificar y almacenar los d�gitos de n�mero (base decimal)*/
	Display_Decodificar_Entero_Decimal(numero);

	/* Repetir indefinidamente */
	while(1){
		/* Cargar el d�gito y activar el display correspondiente */
		Display_Gestionar_Habilitadores();
		// Esperar un momento
		_delay_ms(2);
	}

	return 0;
}

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

void Display_Decodificar_Entero_Decimal(uint16_t num_binario){

	uint8_t pos_digito;

	/* Extraer los d�gitos (en base decimal)del n�mero deseado*/
	for(pos_digito = 0; pos_digito < N_DISPLAYS; pos_digito++){
		/* Extraer el d�gito de las unidades, decodificarlo y almacenarlo */
		display_buffer[pos_digito] = Display_Decodificar_Digito(num_binario % 10);
		/* Desplazar el n�mero un d�gito decimal hacia la derecha */
		num_binario /= 10;
	}
}

void Display_Gestionar_Habilitadores(void){

	static uint8_t pos_digito = 0;

	// Apagar todos los displays
	PORT_ENABLES &= ~MASCARA_ENABLES;
	// Cargar el digito correspondiente a los segmentos
	PORT_DISPLAY = display_buffer[pos_digito];
	// Habilitar el display correspondiente
	PORT_ENABLES |= (1 << pos_digito);
	// Actualizar el valor de la posici�n
	pos_digito++;
	if(pos_digito >= N_DISPLAYS){
		pos_digito = 0;
	}
}

