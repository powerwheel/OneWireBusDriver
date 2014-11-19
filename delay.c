/*
 *	Delay functions
 *	See delay.h for details
 *
 *	Make sure this code is compiled with full optimization!!!
 */

#include	"delay.h"
#include "LPC17xx.h"

static volatile unsigned long  fac_us=0;//us延时倍乘数
static volatile unsigned long fac_ms=0;//ms延时倍乘数
void delay_init(unsigned char SystemOsc)
{
        SysTick->CTRL&=0xfffffffD;//
        fac_us=SystemOsc;                    
        fac_ms=fac_us*1000;
       
}
void delay_us(unsigned long nus)
{               
        static volatile unsigned long temp;                     
        SysTick->LOAD=nus*fac_us; //时间加载                           
        SysTick->VAL=0x00;        //清空计数器
        SysTick->CTRL|=0x05 ;      //开始倒数          

        do
        {
                temp=SysTick->CTRL;
        }
        while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
        SysTick->CTRL=0x00;       //关闭计数器
        SysTick->VAL =0X00;       //清空计数器         
}
void delay_ms(unsigned long nms)
{                                     
        static volatile unsigned long temp;                  
        SysTick->LOAD=nms*fac_ms;//时间加载(SysTick->LOAD为24bit)
        SysTick->VAL =0x00;           //清空计数器
        SysTick->CTRL|=0x05 ;          //开始倒数  

        do
        {
                temp=SysTick->CTRL;
        }
        while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
        SysTick->CTRL=0x00;       //关闭计数器
        SysTick->VAL =0X00;       //清空计数器                      
}
