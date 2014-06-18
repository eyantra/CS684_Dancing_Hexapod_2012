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
unsigned char STAND_A = 90, STAND_B = 60, STAND_C = 20;

#define SIZE 50
unsigned char recv_buffer[SIZE];
unsigned int read_index, write_index;

void servo_on (void)
{ PORTB = PORTB | 0x01; }

void servo_off (void)
{ PORTB = PORTB & 0xFE; }
  
  void stand(void){
  angle_1A(STAND_A); angle_1B(STAND_B); angle_1C(STAND_C); angle_2A(STAND_A); angle_2B(STAND_B); angle_2C(STAND_C);
//1,2,3C angle0 - vertical?
//4 5 6 angle180 - vertical?
angle_3A(STAND_A); angle_3B(STAND_B); angle_3C(STAND_C); angle_4A(STAND_A); angle_4B(STAND_B); angle_4C(STAND_C);
angle_5A(STAND_A); angle_5B(STAND_B); angle_5C(STAND_C); angle_6A(STAND_A); angle_6B(STAND_B); angle_6C(STAND_C);
  }

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

void step_down(void)
{
	unsigned char pa = 30, pc = 0;;
	angle_1B(pa);
	angle_2B(pa);
	angle_3B(pa);
	angle_4B(pa);
	angle_5B(pa);
	angle_6B(pa);
	
	angle_1C(pc);
	angle_2C(pc);
	angle_3C(pc);
	angle_4C(pc);
	angle_5C(pc);
	angle_6C(pc);
	delay_250ms();
}

void slow_step_down(void)
{
	unsigned char i = 0;
	unsigned char pa = 30, pc = 0;
	
	for( i=1; i<16; i++)
	{
		pa = STAND_B - 2 * i;
		pc = STAND_C - 1 * i;
		if (i == 15)
			pc = 0;
		
		angle_1B(pa);
		angle_2B(pa);
		angle_3B(pa);
		angle_4B(pa);
		angle_5B(pa);
		angle_6B(pa);
	
		angle_1C(pc);
		angle_2C(pc);
		angle_3C(pc);
		angle_4C(pc);
		angle_5C(pc);
		angle_6C(pc);
		
		delay_50ms();
	}
}

void step_up(void)
{
	unsigned char pa = STAND_B, pc = STAND_C;;
	angle_1B(pa);
	angle_2B(pa);
	angle_3B(pa);
	angle_4B(pa);
	angle_5B(pa);
	angle_6B(pa);
	
	angle_1C(pc);
	angle_2C(pc);
	angle_3C(pc);
	angle_4C(pc);
	angle_5C(pc);
	angle_6C(pc);
	delay_250ms();
}

void step_bounce()
{
	step_down();
	// delay_250ms();
	step_up();
	// delay_1s();
	
}

void step16(void)
{
	motion_busy = 1; 
	
	if (leg_up == 0)
	{
		leg_up = 1;
		angle_1B(0);
		angle_6B(0);
		angle_1C(100);
		angle_6C(100);
		
		angle_2B(40);
		angle_3B(40);
		angle_4B(40);
		angle_5B(40);
		
		angle_2C(0);
		angle_3C(0);
		angle_4C(0);
		angle_5C(0);
	}
	else
	{
		leg_up = 0;
		stand();
		// angle_1B(STAND_B);
		// angle_6B(STAND_B);
		
		// angle_1C(STAND_C);
		// angle_6C(STAND_C);
		
		// angle_2B(STAND_B);
		// angle_3B(STAND_B);
		// angle_4B(STAND_B);
		// angle_5B(STAND_B);
	}
	
	motion_busy = 0;
}

void step25(void)
{
	motion_busy = 1; 
	
	if (leg_up == 0)
	{
		leg_up = 1;
		angle_2B(0);
		angle_5B(0);
		angle_2C(100);
		angle_5C(100);
		
		angle_1B(40);
		angle_3B(40);
		angle_4B(40);
		angle_6B(40);
		
		angle_1C(0);
		angle_3C(0);
		angle_4C(0);
		angle_6C(0);
	}
	else
	{
		leg_up = 0;
		stand();
		// angle_2B(STAND_B);
		// angle_5B(STAND_B);
		
		// angle_2C(STAND_C);
		// angle_5C(STAND_C);
		
		// angle_1B(STAND_B);
		// angle_3B(STAND_B);
		// angle_4B(STAND_B);
		// angle_6B(STAND_B);
	}
	
	motion_busy = 0;
}

void step34(void)
{
	motion_busy = 1; 
	
	if (leg_up == 0)
	{
		leg_up = 1;
		angle_3B(0);
		angle_4B(0);
		angle_3C(100);
		angle_4C(100);
		
		angle_2B(40);
		angle_1B(40);
		angle_6B(40);
		angle_5B(40);
		
		angle_2C(0);
		angle_1C(0);
		angle_6C(0);
		angle_5C(0);
	}
	else
	{
		leg_up = 0;
		stand();
		// angle_4B(STAND_B);
		// angle_3C(STAND_C);
		// angle_3B(STAND_B);
		
		// angle_4C(STAND_C);
		
		// angle_2B(STAND_B);
		// angle_1B(STAND_B);
		// angle_6B(STAND_B);
		// angle_5B(STAND_B);
	}
	
	motion_busy = 0;
}

void legs246_up_left()
{
	unsigned char i=0;
	//angle_246(30, 10, 140);
	for(i=1; i<21; i++)
	{
		angle_246(STAND_A - 3*i, 30 - i, 7*i);
		delay_50ms();
	}
}

void danceMove_HandsAir(void)
{
	motion_busy = 1;
	stand();
	delay_1s();
	
	
	step_bounce();
	step_bounce();
	
	delay_1s();
	step16();
	delay_250ms();
	delay_250ms();
	step16();
	delay_250ms();
	delay_250ms();
	
	step25();
	delay_250ms();
	delay_250ms();
	step25();
	delay_250ms();
	delay_250ms();
	
	step34();
	delay_250ms();
	delay_250ms();
	step34();
	delay_250ms();
	delay_250ms();
	
	step_bounce();
	step_bounce();
	motion_busy = 0;
}

void basic_move(void)
{

	 motion_busy = 1; 
	  stand();
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
	 
	 stand();
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

#pragma interrupt_handler uart0_rx_isr:iv_USART0_RXC
void uart0_rx_isr(void)
{
 // uart has received a character in UDR
	unsigned char data = UDR0;
	
	recv_buffer[write_index] = data;
	write_index++;
	
	if (write_index == SIZE)
		write_index = 0;
	
 	// buzzer_on();
	// delay_250ms();
	// delay_250ms();
	// buzzer_off();
	
}

void rotate(){
	unsigned char pa = 30, pb = 150, i = 0;

	motion_busy = 1; 
	stand();
	
	for ( i = 0; i < 5; i ++)
	{
		angle_1A(pa);
		angle_2A(pa);
		angle_3A(pa);
		angle_4A(pa);
		angle_5A(pa);
		angle_6A(pa);
		
		delay_250ms();
		delay_250ms();
		
		angle_1A(pb);
		angle_2A(pb);
		angle_3A(pb);
		angle_4A(pb);
		angle_5A(pb);
		angle_6A(pb);
		
		
		delay_250ms();
		delay_250ms();
	}
	
	stand();
	delay_1s();
	motion_busy = 0;
	
}

void finale(void)
{
	unsigned char b = 180;
	motion_busy = 1;
	
	stand();
	delay_1s();
	
	// back legs to the back
	angle_6B(30);
	angle_3B(30);
	delay_250ms();
	angle_6A(50);
	angle_3A(130);
	delay_1s();
	angle_6B(90);
	angle_3B(60);
	delay_1s();
	
	// angle_2B(30);
	// angle_5B(30);
	// delay_250ms();
	// angle_2A(30);
	// angle_5A(150);
	// delay_1s();
	// angle_2B(60);
	// angle_5B(60);
	// delay_1s();
		
	angle_1B(b);
	angle_2B(b);
	angle_3B(b);
	angle_4B(b);
	angle_5B(b);
	angle_6B(b);
	buzzer_on();
	delay_1s();
	buzzer_off();
	
	angle_6C(40);
	delay_1s();
	angle_6C(50);
	delay_1s();
	angle_6C(60);
	delay_1s();
	angle_6C(70);
	delay_1s();
	angle_6C(80);
	delay_1s();
	angle_6C(90);
	delay_1s();
	// delay_1s();

	
	// angle_1B(0);
	// angle_4B(0);
	// delay_250ms();
		
	
	motion_busy = 0;
}

void slowTripod(void)
{
	unsigned char i = 0;
	motion_busy = 1;
	stand();
	delay_1s();
	
	slow_step_down();
	
	legs246_up_left();
	
	for (i=1; i < 21; i++)
	{
		angle_135(NO_ACTION , 30 + 4*i, 3*i);
		angle_246(30 + 6*i, NO_ACTION, NO_ACTION);
		delay_50ms();
	}
	//delay_1s();
	
	for (i=1; i < 21; i++)
	{
		angle_135(NO_ACTION , 110 - 4*i, 60 - 3*i);
		angle_246(150 - 6*i, NO_ACTION, NO_ACTION);
		delay_50ms();
	}
	//delay_1s();
	for (i=1; i < 21; i++)
	{
		angle_135(NO_ACTION , 30 + 4*i, 3*i);
		angle_246(30 + 6*i, NO_ACTION, NO_ACTION);
		delay_50ms();
	}
	//delay_1s();
	
	for (i=1; i < 21; i++)
	{
		angle_135(NO_ACTION , 110 - 4*i, 60 - 3*i);
		angle_246(150 - 6*i, NO_ACTION, NO_ACTION);
		delay_50ms();
	}
	//delay_1s();
	
	for(i=1; i<21; i++)
	{
		angle_246(30 + 3*i, 10 + i, 140 - 7*i);
		delay_50ms();
	}
	
	for(i=1; i<21; i++)
	{
		if (i < 11)
		{
			angle_135(NO_ACTION, 30+i, i);
			angle_246(NO_ACTION, 30+i, i);
		}
		else
		{
			angle_135(NO_ACTION, 50+i, i);
			angle_246(NO_ACTION, 50+i, i);
		}
		delay_50ms();
	}
	
	stand();
	delay_1s();
	
	motion_busy = 0;
}

void processCommand(unsigned char cmd)
{
	// if (cmd == '1')
	// {	
		// step16();
		// delay_250ms();
		// step16();
		// delay_250ms();
	// }
	// else if (cmd == '2')
	// {
		// step25();
		// delay_250ms();
		// step25();
		// delay_250ms();
	// }
	
	if (cmd == 'a') 
	{
		basic_move();
	}
	
	else if (cmd == 'b') 
	{
		rotate();
	}
	else if (cmd == 'c') 
	{
		slowTripod();
	}
	else if (cmd == 'd') 
	{
		danceMove_HandsAir();
	}
	else if (cmd == 'e') 
	{
		finale();
	}
	
}

void main(void)
{

 unsigned char cmd;
  init_devices();
 //uart0_init();
 buzzer_on(); delay_1s(); buzzer_off();
 servo_calibration(); //must be called as the first instruction
 servo_on();//turning on the servo supply
 stand();
 delay_1s();
 delay_1s();
 delay_1s();
 buzzer_on(); delay_1s(); buzzer_off();
 
 read_index = 0;
 write_index = 0;
 while(1)
 {
	if (read_index != write_index)
	{
		cmd = recv_buffer[read_index];
		read_index++;
		if (read_index == SIZE) read_index = 0;
		processCommand(cmd);
		buzzer_on(); delay_50ms(); buzzer_off();
	}
	
 }
 // step3();
 // delay_1s();
 // step3();
 // delay_1s();
 // delay_1s();
 
 // servo_calibration();
 
 // rotate();
 // delay_1s();
 
 //danceMove_HandsAir();
 
 //slowTripod();
 //stand();
 
 //finale();
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
