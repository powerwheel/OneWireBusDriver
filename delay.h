

#ifndef DELAY_H
#define DELAY_H
extern void delay_init(unsigned char SystemOsc);
extern void delay_us(unsigned long nus);
extern void delay_ms(unsigned long nms);
#endif
