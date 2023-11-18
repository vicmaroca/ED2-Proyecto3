//*********************
//                        LIBRERIAS
//*********************
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/adc.h"
#include "utils/ustdlib.h"

//*********************
//                    VARIABLES GLOBALES
//*********************
int ir1;
int ir2;
int ir3;
int ir4;

//*********************
//                 PROTOTIPOS DE FUNCIONES
//*********************
void setup(void);
void delay_ms(uint32_t ms);
void setupUART1(void);

//*********************
//                   FUNCION PRINCIPAL
//*********************
int main(void){
    //*********************
    //                        SETUP
    //*********************
    setup();
    setupUART1();

    //*********************
    //                    LOOP INFINITO
    //*********************
    while(1){
        ir1 = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_4);     //Leer IR1
        ir2 = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_5);     //Leer IR2
        ir3 = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_6);     //Leer IR3
        ir4 = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_7);     //Leer IR4

        //PRIMER ESPACIO DE PARQUEO
        if (ir1 == 0){//OCUPADO
            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0);                                             //LED verde apagado
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 255);                                           //LED rojo encendido
            while(UARTBusy(UART1_BASE)){}                                                             // Wait for the UART to be ready
            SendString("a");
            delay_ms(250);
        }else{//LIBRE
            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 255);                                           //LED verde encendido
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0);                                             //LED rojo apagado
            while(UARTBusy(UART1_BASE)){}                                                             // Wait for the UART to be ready
            SendString("A");
            delay_ms(250);
        }
        //SEGUNDO ESPACIO DE PARQUEO
        if (ir2 == 0){//OCUPADO
            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0);                                             //LED verde apagado
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 255);                                           //LED rojo encendido
            while(UARTBusy(UART1_BASE)){}
            SendString("b");
            delay_ms(250);
        }else{//LIBRE
            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 255);                                           //LED verde encendido
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0);                                             //LED rojo apagado
            while(UARTBusy(UART1_BASE)){}
            SendString("B");
            delay_ms(250);
        }
        //TERCER ESPACIO DE PARQUEO
        if (ir3 == 0){//OCUPADO
            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0);                                             //LED verde apagado
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, 255);                                           //LED rojo encendido
            while(UARTBusy(UART1_BASE)){}
            SendString("c");
            delay_ms(250);
        }else{//LIBRE
            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 255);                                           //LED verde encendido
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, 0);                                             //LED rojo apagado
            while(UARTBusy(UART1_BASE)){}
            SendString("C");
            delay_ms(250);
        }
        //CUARTO ESPACIO DE PARQUEO
        if (ir4 == 0){//OCUPADO
            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0);                                             //LED verde apagado
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 255);                                           //LED rojo encendido
            while(UARTBusy(UART1_BASE)){}
            SendString("d\n");
            delay_ms(250);
        }else{//LIBRE
            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 255);                                           //LED verde encendido
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0);                                             //LED rojo apagado
            while(UARTBusy(UART1_BASE)){}
            SendString("D\n");
            delay_ms(250);
        }

    }
}

//*********************
//                   FUNCION DE SETUP
//*********************
void setup(void){
    // CLOCK
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);             //Reloj a 40MHz
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);                                                //Habilitar el puerto F
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 255);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); //Habilitando el puerto B
        while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)); //Esperar la inicialización del puerto
        IntMasterEnable(); //Habilitando interrupciones globales

    //SETUP PORTA (IR SENSORS)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);                                                        //Habilitar el puerto A
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);           //Configurar PA# como entrada

    //SETUP PORTD (LEDS VERDES)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);                                                        //Habilitar el puerto D
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);          //Configurar LEDS como salidas
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 255);              //Iniciar con LEDS verdes encendidos

    //SETUP PORTE (LEDS ROJOS)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);                                                        //Habilitar el puerto E
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4);          //Configurar LEDS como salidas
}

//*********************
//                FUNCION UARTconfig
//*********************
void setupUART1(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1); //Habilitando el módulo UART1
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1); //Definiendo los pines para el UART
    GPIOPinConfigure(GPIO_PB0_U1RX); //Definiendo pinB0 como RX
    GPIOPinConfigure(GPIO_PB1_U1TX); //Definiendo pinB1 como TX

    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE)); //Configurando el UART1 con 115200 de baudrate, 8 bits, un dato y sin paridad
    UARTEnable(UART1_BASE); //Iniciando el UART1
}

//*********************
//              FUNCION PARA DELAY EN MS
//*********************
void delay_ms(uint32_t ms) {
    // Using 40MHz clock
    SysCtlDelay((SysCtlClockGet() / 3000) * ms);
}

//*********************
//             FUNCION PARA ENVIAR STRINGS
//*********************
void SendString(char* frase){
    //Funcion para poder enviar string mediante UART
    while (*frase){
        UARTCharPut(UART1_BASE, *frase++);
    }
}
