/*
 *	Delay functions
 *	See delay.h for details
 *
 *	Make sure this code is compiled with full optimization!!!
 */

#include	"delay.h"
#include "LPC17xx.h"

static volatile unsigned long  fac_us=0;//us��ʱ������
static volatile unsigned long fac_ms=0;//ms��ʱ������
void delay_init(unsigned char SystemOsc)
{
        SysTick->CTRL&=0xfffffffD;//
        fac_us=SystemOsc;                    
        fac_ms=fac_us*1000;
       
}
void delay_us(unsigned long nus)
{               
        static volatile unsigned long temp;                     
        SysTick->LOAD=nus*fac_us; //ʱ�����                           
        SysTick->VAL=0x00;        //��ռ�����
        SysTick->CTRL|=0x05 ;      //��ʼ����          

        do
        {
                temp=SysTick->CTRL;
        }
        while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
        SysTick->CTRL=0x00;       //�رռ�����
        SysTick->VAL =0X00;       //��ռ�����         
}
void delay_ms(unsigned long nms)
{                                     
        static volatile unsigned long temp;                  
        SysTick->LOAD=nms*fac_ms;//ʱ�����(SysTick->LOADΪ24bit)
        SysTick->VAL =0x00;           //��ռ�����
        SysTick->CTRL|=0x05 ;          //��ʼ����  

        do
        {
                temp=SysTick->CTRL;
        }
        while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
        SysTick->CTRL=0x00;       //�رռ�����
        SysTick->VAL =0X00;       //��ռ�����                      
}
