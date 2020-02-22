/*
 * File:   ADC.c
 * Author: jxica
 *
 * Created on 6 de febrero de 2020, 07:52 PM
 */

#include <pic16f887.h>
#include <xc.h>
#include "ADC.h"
#include <stdint.h>


void ADC_conf(uint8_t ADCNum) {
    switch(ADCNum){
        case 0:
        //AN5
        //Selecion del canal analogico
        ADCON0bits.CHS3=0;
        ADCON0bits.CHS2=1;
        ADCON0bits.CHS1=0;
        ADCON0bits.CHS0=1;
        break;
        
        case 1:
        //AN6
        //Selecion del canal analogico
        ADCON0bits.CHS3=0;
        ADCON0bits.CHS2=1;
        ADCON0bits.CHS1=1;
        ADCON0bits.CHS0=0;            
        break;      
    }
    ADCON0bits.GO_DONE=1;
    
}

void ADC_init(void){
    
    ANSEL = 0;
    ANSELbits.ANS5 =1;//Entrada analogica RE5
    ANSELbits.ANS6 =1;//Entrada analogica RE6    
    //Encender interrupcion ADC
    PIE1bits.ADIE=1;
    PIR1bits.ADIF=1;
    //Configuracion ADC
    ADCON0bits.ADCS=01;    
    ADCON0bits.GO_nDONE=0;
    //Activacion del ADC
    ADCON0bits.ADON=1;
    //Tipo de justificado
    ADCON1bits.ADFM=0;
    //Refencia VSS y VDD
    ADCON1bits.VCFG0=0;
    ADCON1bits.VCFG1=0;    
}
