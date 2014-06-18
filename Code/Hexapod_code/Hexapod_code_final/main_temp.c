//ICC-AVR application builder : 11/4/2009 1:05:10 PM
// Target : M2560
// Crystal: 11.059Mhz



/*
Pin name	Port		Anding (make 0)		Oring (make 1)
SP LEFT	PL1		1111 1101	0xFD		0000 0010	0x02

1A		PD5		1101 1111	0xDF		0010 0000	0x20
1B		PL2		1111 1011	0xFB		0000 0100	0x04
1C		PG1		1111 1101	0xFD		0000 0010	0x02
2A		PL6		1011 1111	0xBF		0100 0000	0x40
2B		PD4		1110 1111	0xEF		0001 0000	0x10
2C		PL7		0111 1111	0x7F		1000 0000	0x80
3A		PH6		1011 1111	0xBF		0100 0000	0x40
3B		PH4		1110 1111	0xEF		0001 0000	0x10
3C		PH5		1101 1111	0xDF		0010 0000	0x20
SP RIGHT	PJ7		0111 1111	0x7F		1000 0000	0x80
4A		PG0		1111 1110	0xFE		0000 0001	0x01
4B		PD7		0111 1111	0x7F		1000 0000	0x80
4C		PD6		1011 1111	0xBF		0100 0000	0x40
5A		PJ5		1101 1111	0xDF		0010 0000	0x20
5B		PJ6		1011 1111	0xBF		0100 0000	0x40
5C		PJ4		1110 1111	0xEF		0001 0000	0x10
6A		PJ3		1111 0111	0XF7		0000 1000	0x08
6B		PJ1		1111 1101	0xFD		0000 0010	0x02
6C		PJ2		1111 1011	0xFB		0000 0100	0x04

Remote control communication protocoal
transmitted command		received data
1						right joystick x axis 8 bit analog position;	center:0x24; left: 0x3B; right: 0x04
2						right joystick y axis 8 bit analog position;	center:0x24; up: 0x3B; down: 0x04
3						left joystick x axis 8 bit analog position;		center:0x3A; left: 0x23; right: 0x04
4						left joystick y axis 8 bit analog position;		center:0x1F; up: 0x34; down: 0x04
5						right joystick button
6						left joystick button
7						digital switches left 1,2 and right 1,2
						bit7: Right 2; bit6: right 1; bit4: left 1; bit3: left 2

Received data will be stored in the array unsigned char remote_data [8]; from the location 1 to 7 in the same order as the command.
*/

#include <iom2560v.h>
#include <macros.h>

//#include "globals.h"
#include "helpers.h"
#include "init.h"
#include "hexapod_motion.h"

unsigned int i=0;

void servo_on (void)
{ PORTB = PORTB | 0x01; }

void servo_off (void)
{ PORTB = PORTB & 0xFE; }

unsigned char leg_up = 0;
void step(void)
{
	motion_busy = 1; 
	
	if (leg_up == 0)
	{
		angle_1B(0);
		leg_up = 1;
	}
	else
	{
		angle_1B(40);
		leg_up = 0;
	}
	
	motion_busy = 0;
}

void step2(void)
{
	motion_busy = 1; 
	angle_1B(0);
	delay_1s();
	delay_1s();
	delay_1s();
	angle_1B(40);
	angle_2B(0);
	delay_1s();
	delay_1s();
	delay_1s();
	motion_busy = 0;
}

void step3(void)
{
	motion_busy = 1; 
	
	if (leg_up == 0)
	{
		leg_up = 1;
		angle_1B(0);
		angle_6B(0);
		
		angle_1C(40);
		angle_6C(40);
		
		angle_2B(70);
		angle_3B(70);
		angle_4B(70);
		angle_5B(70);
	}
	else
	{
		leg_up = 0;
		angle_1B(40);
		angle_6B(40);
		
		angle_1C(0);
		angle_6C(0);
		
		angle_2B(90);
		angle_3B(90);
		angle_4B(90);
		angle_5B(90);
	}
	
	motion_busy = 0;
}

void basic_move(void)
 {

 motion_busy = 1; 

 //servo_calibration();
 delay_1s();
 //lift 1
 angle_1B(40); angle_1C(90);
 delay_1s();
 //lift 2
 angle_2B(40); angle_2C(90);
 delay_1s();
 //rest 1
 angle_1B(70); angle_1C(20);
 delay_1s();
 //lift3
 angle_3B(40); angle_3C(90);
 delay_1s();
 //rest2
 angle_2B(70); angle_2C(20);
 delay_1s();
 //lift6
 angle_6B(40); angle_6C(90);
 delay_1s();
 //rest3
 angle_3B(70); angle_3C(20);
 delay_1s();
 //lift5
 angle_5B(40); angle_5C(90);
 delay_1s();
 //rest6
 angle_6B(70); angle_6C(20);
 delay_1s();
 //lift4
 angle_4B(40); angle_4C(90);
 delay_1s();
 //rest5
 angle_5B(70); angle_5C(20);
 delay_1s();
 //rest4
 angle_4B(70); angle_4C(20);
 delay_1s();
 /* for (i = 0;i<10;i++){
 angle_1B(140); angle_1C(90);
 delay_250ms();
 angle_1B(0); angle_1C(0);
 delay_250ms();
 }
  *//* //legs 2 and 4 move forward
 angle_2B(45); angle_2C(45); angle_4B(135); angle_4C(135); //front pair BC servo up 45
 delay_250ms();
 angle_2A(45); angle_4A(135); //front pair move forward while legs are up
 delay_250ms();
 angle_2B(90); angle_2C(90); angle_4B(90); angle_4C(90); // put down legs
 delay_250ms();
 
 //legs 1 and 6 move forward
 
 angle_1B(45); angle_1C(45); angle_6B(135); angle_6C(135); //middel pair BC servo up 45
 delay_250ms();
 angle_1A(45); angle_6A(135); //middel pair move back while legs are up
 delay_250ms();
 angle_1B(90); angle_1C(90); angle_6B(90); angle_6C(90); // put down legs
 delay_250ms();
 
 //legs 3 and 5 move forward
 angle_3B(45); angle_3C(45); angle_5B(135); angle_5C(135); //middel pair BC servo up 45
 delay_250ms();
 angle_3A(45); angle_5A(135); //middel pair move forward while legs are up
 delay_250ms();
 angle_3B(90); angle_3C(90); angle_5B(90); angle_5C(90); // put down legs
 delay_250ms(); 
 
 servo_calibration(); //push towards forward
 motion_busy = 0; 
  */
  }
  
  void stand(void){
  angle_1A(90); angle_1B(60); angle_1C(20); angle_2A(90); angle_2B(60); angle_2C(20);
//1,2,3C angle0 - vertical?
//4 5 6 angle180 - vertical?
angle_3A(90); angle_3B(60); angle_3C(20); angle_4A(90); angle_4B(60); angle_4C(20);
angle_5A(90); angle_5B(60); angle_5C(20); angle_6A(90); angle_6B(60); angle_6C(20);
  }

#pragma interrupt_handler uart0_rx_isr:iv_USART0_RXC
void uart0_rx_isr(void)
{
 // uart has received a character in UDR
	unsigned char data = UDR0;
 	// buzzer_on();
	// delay_250ms();
	// delay_250ms();
	// buzzer_off();
	
	step3();
}

void main(void)
{
  init_devices();
 //uart0_init();
 buzzer_on(); delay_1s(); buzzer_off();
 servo_calibration(); //must be called as the first instruction
 servo_on();//turning on the servo supply
 delay_1s();
 delay_1s();
 delay_1s();
 buzzer_on(); delay_1s(); buzzer_off();
 
 step3();
 delay_1s();
 step3();
 delay_1s();
 delay_1s();
 
 servo_calibration();
 stand();
 
// buzzer_on(); delay_1s(); buzzer_off();
 // // insert your functional code here...
 // servo_calibration(); //must be called as the first instruction
 // servo_on();//turning on the servo supply
 // delay_1s();
 // delay_1s();
 // delay_1s();
 // buzzer_on(); delay_1s(); buzzer_off();
 // stand();
 // delay_1s();
 // delay_1s();
 // delay_1s();
 // // basic_move();
 // step();
 // stand();
 // /*forward();
 // while(motion_busy == 1);
 // forward();
 // while(motion_busy == 1);
 // forward();
 // while(motion_busy == 1);
 
 // buzzer_on(); delay_1s(); buzzer_off();
 // back();
 // while(motion_busy == 1);
 // back();
 // while(motion_busy == 1);
 // back();
 
 // buzzer_on(); delay_1s(); buzzer_off();
 // while(motion_busy == 1);
 // robot_rotate_anticlockwise_7_5(); 
 // while(motion_busy == 1);
 // robot_rotate_anticlockwise_7_5(); 
 // while(motion_busy == 1);
 // robot_rotate_anticlockwise_7_5(); 
 // while(motion_busy == 1);
 // robot_rotate_clockwise_7_5();
 // while(motion_busy == 1);
 // robot_rotate_clockwise_7_5();
 // while(motion_busy == 1);
 // robot_rotate_clockwise_7_5();
 // while(motion_busy == 1); 
 
 
   // */
}

// void rotate(){
// motion_busy = 1; 
	
	
		// leg_up = 1;
		// angle_1B(0);
		// angle_6B(0);
		
		// angle_1C(40);
		// angle_6C(40);
		
		// angle_2B(70);
		// angle_3B(70);
		// angle_4B(70);
		// angle_5B(70);
	// }
	
// }



