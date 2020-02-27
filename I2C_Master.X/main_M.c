/*
 * File:   main.c
 * Author: Pablo
 * Ejemplo de uso de I2C Master
 * Created on 17 de febrero de 2020, 10:32 AM
 */
//*****************************************************************************
// Palabra de configuraci�n
//*****************************************************************************
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//*****************************************************************************
// Definici�n e importaci�n de librer�as
//*****************************************************************************
#include <stdint.h>
#include <pic16f887.h>
#include "I2C.h"
#include "LCD.h"
#include <xc.h>
 #include <stdio.h>
//*****************************************************************************
// Definici�n de variables
//*****************************************************************************
#define _XTAL_FREQ 4000000

//*****************************************************************************
// Definici�n de funciones para que se puedan colocar despu�s del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
void setup(void);
float d1 = 0;
uint8_t d2; 
float d3 = 0;
uint8_t od3;
uint8_t dd3;
uint8_t d3_1;
uint8_t od1;
uint8_t dd1;
uint8_t d1_1;
uint8_t v1;
uint8_t dent1;
uint8_t int1;



//*****************************************************************************
// Main
//*****************************************************************************
void main(void) {
    setup();
    //Lcd_Clear();
    Lcd_Set_Cursor(1,1);                //SE DEFINEN LOS VALORES ESTATICOS DE LA LCD
    Lcd_Write_String ("S1");
    Lcd_Set_Cursor(7,1);
    Lcd_Write_String ("S2");
    Lcd_Set_Cursor(13,1);
    Lcd_Write_String ("S3");
    while(1){
        
        I2C_Master_Start();
        I2C_Master_Write(0x51);
        d3 = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(10);
          
        
        I2C_Master_Start();
        I2C_Master_Write(0x41);
        d2 = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(10);
        
        I2C_Master_Start();
        I2C_Master_Write(0x31);
        d1 = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(10);
        
        
        d3 = d3 * 5/255;
        od3 = d3;
        dd3 = (d3 - od3)*100;
        d3_1 = dd3;
        
        Lcd_Set_Cursor(1,2);            //MUESTRA EL VALOR DEL POTENCIOMETRO EN LA LCD
        Lcd_Write_Int(od3);
        Lcd_Write_Char('.');
        if (d3_1 >= 10){
            Lcd_Write_Int(d3_1);
        }else{
            Lcd_Write_Char('0');
            Lcd_Write_Int(d3_1);
        }
        
        d1 = d1 * 5/255;
        od1 = d1;
        dd1 = (d1 - od1)*100;
        d1_1 = dd1;
        
        Lcd_Set_Cursor(13,2);            //MUESTRA EL VALOR DEL POTENCIOMETRO EN LA LCD
        Lcd_Write_Int(od1);
        Lcd_Write_Char('.');
        if (d3_1 >= 10){
            Lcd_Write_Int(d1_1);
        }else{
            Lcd_Write_Char('0');
            Lcd_Write_Int(d1_1);
        }
        
        if(d2 < 10){                 //MUESTRA EL VALOR DEL CONTADOR EN LA LCD
            Lcd_Set_Cursor(7,2);
            Lcd_Write_String("0");
            Lcd_Write_Int(d2);
        }else{
            Lcd_Set_Cursor(7,2);
            Lcd_Write_Int(d2);
        }

        
        
    }
    return;
}
//*****************************************************************************
// Funci�n de Inicializaci�n
//*****************************************************************************
void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    
    TRISA = 0;
    TRISB = 0;
    TRISD = 0;
    
    PORTB = 0;
    PORTA = 0;
    PORTD = 0;
    initLCD();  
    Lcd_Clear();
 //   OSCCONbits.IRCF = 111;
    I2C_Master_Init(100000);        // Inicializar Comuncaci�n I2C
}