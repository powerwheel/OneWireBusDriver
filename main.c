    
#include "GLCD.h" 
#include "LPC17xx.h"
#include "ds1820.h"
#include "types.h"
#include "delay.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>







/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
int main(void)
{
  sint16 temperature_raw;     /* temperature raw value (resolution 1/256) */
  float temperature_float;
  char temperature[8];        /* temperature as string */
  char buf[32];
  uint8 sensor_count;         /* sensor counter */
  delay_init(96);

  delay_ms(10);
  LCD_Initializtion();
  LCD_Clear(Red);

  while (1)
  {
	  
	  delay_ms(10);
	   sensor_count = 0;
	   if ( DS1820_FindFirstDevice() ){
	   	  do
            {
                /* get temperature raw value (resolution 1/256) */
                temperature_raw = DS1820_GetTempRaw();

                /* convert raw temperature to string for output */
                DS1820_GetTempString(temperature_raw, temperature);
                
                /* get temperature value as float */
                temperature_float = DS1820_GetTempFloat();
               
		sprintf(buf,"Sensor:%d %s",sensor_count,temperature);

		GUI_Text(0,sensor_count*24,buf,White,Red);
              
                sensor_count ++;
            }
            while ( DS1820_FindNextDevice() );

            sensor_count = 0;
	   }
	  
	  
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

