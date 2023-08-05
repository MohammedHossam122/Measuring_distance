/*
 * Measuring_Distance.c
 *
 *  Created on: Jul 1, 2023
 *      Author: mhoss
 *      Description: Measuring Distance using ultra-sonic sensor (HC-SR04) and display it on LCD (4x16)
 * 	with ATmega32 F_CPU = 8MHz
 */

#include "HAL/ultrasonic.h"
#include "HAL/lcd.h"
#include "std_types.h"
#include <avr/interrupt.h>



int main()
{
	SREG |= (1<<7);					/* Enable global interrupt*/
	LCD_init();						/* Initialize LCD and pins used*/
	Ultrasonic_init();				/* Initialize Ultrasonic Sensor*/
	uint16 distance = 0;			/* Variable to store distance from ultrasonic sensor to display*/

	while (1)
	{
		LCD_moveCursor(0, 0);
		LCD_displayString("distance= ");
		distance = Ultrasonic_readDistance();		/*Read distance from sensor*/

		/*Adjusting distance for accurate measurements due to rounding from float conversion*/
		if (distance < 59)
			++distance;
		else if (distance >=59 && distance < 133)
		{
			distance +=2;
		}
		else if (distance >= 133 && distance < 207)
		{
			distance +=3;
		}
		else if (distance >= 207)
		{
			distance +=4;
		}

		/* Displaying Distance */
		if (distance<100)
		{
			LCD_intgerToString(distance);
			LCD_displayString("  ");					/*delete last digit if number is less than 3 digits*/
		}
		else if (distance<10)
		{
			LCD_intgerToString(distance);
			LCD_displayString("  ");					/*delete last digit if number is less than 2 digits*/
		}
		else
		{
			LCD_intgerToString(distance);
		}
		LCD_displayStringRowColumn(0, 13, "cm");
	}
}
