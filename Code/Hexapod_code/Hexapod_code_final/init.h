
//#include "globals.h"
#include "communication.h"

void reset_SP_LEFT (void)
{ PORTL = PORTL & 0xFD; }

void set_SP_LEFT (void)
{ PORTL = PORTL | 0x02; }

void reset_1A (void)
{ PORTD = PORTD & 0xDF; }

void set_1A (void)
{ PORTD = PORTD | 0x20; }

void reset_1B (void)
{ PORTL = PORTL & 0xFB; }

void set_1B (void)
{ PORTL = PORTL | 0x04; }

void reset_1C (void)
{ PORTG = PORTG & 0xFD; }

void set_1C (void)
{ PORTG = PORTG | 0x02; }

void reset_2A (void)
{ PORTL = PORTL & 0xBF; }

void set_2A (void)
{ PORTL = PORTL | 0x40; }

void reset_2B (void)
{ PORTD = PORTD & 0xEF; }

void set_2B (void)
{ PORTD = PORTD | 0x10; }

void reset_2C (void)
{ PORTL = PORTL & 0x7F; }

void set_2C (void)
{ PORTL = PORTL | 0x80; }

void reset_3A (void)
{ PORTH = PORTH & 0xBF; }

void set_3A (void)
{ PORTH = PORTH | 0x40; }

void reset_3B (void)
{ PORTH = PORTH & 0xEF; }

void set_3B (void)
{ PORTH = PORTH | 0x10; }

void reset_3C (void)
{ PORTH = PORTH & 0xDF; }

void set_3C (void)
{ PORTH = PORTH | 0x20; }


void reset_SP_RIGHT (void)
{ PORTJ = PORTJ & 0x7F; }

void set_SP_RIGHT (void)
{ PORTJ = PORTJ | 0x80; }

void reset_4A (void)
{ PORTG = PORTG & 0xFE; }

void set_4A (void)
{ PORTG = PORTG | 0x01; }

void reset_4B (void)
{ PORTD = PORTD & 0x7F; }

void set_4B (void)
{ PORTD = PORTD | 0x80; }

void reset_4C (void)
{ PORTD = PORTD & 0xBF; }

void set_4C (void)
{ PORTD = PORTD | 0x40; }

void reset_5A (void)
{ PORTJ = PORTJ & 0xDF; }

void set_5A (void)
{ PORTJ = PORTJ | 0x20; }

void reset_5B (void)
{ PORTJ = PORTJ & 0xBF; }

void set_5B (void)
{ PORTJ = PORTJ | 0x40; }

void reset_5C (void)
{ PORTJ = PORTJ & 0xEF; }

void set_5C (void)
{ PORTJ = PORTJ | 0x10; }

void reset_6A (void)
{ PORTJ = PORTJ & 0xF7; }

void set_6A (void)
{ PORTJ = PORTJ | 0x08; }

void reset_6B (void)
{ PORTJ = PORTJ & 0xFD; }

void set_6B (void)
{ PORTJ = PORTJ | 0x02; }

void reset_6C (void)
{ PORTJ = PORTJ & 0xFB; }

void set_6C (void)
{ PORTJ = PORTJ | 0x04; }


void port_init(void)
{
 PORTA = 0x00;
 DDRA  = 0xFF;
 PORTB = 0x00;
 DDRB  = 0x01;
 PORTC = 0x00; //m103 output only
 DDRC  = 0xFF;
 PORTD = 0x00;
 DDRD  = 0xF0;
 PORTE = 0x00;
 DDRE  = 0x00;
 PORTF = 0x00;
 DDRF  = 0x00;
 PORTG = 0x00;
 DDRG  = 0x03;
 PORTH = 0x00;
 DDRH  = 0x70;
 PORTJ = 0x00;
 DDRJ  = 0xFE; //0xFE original
 PORTK = 0x00;
 DDRK  = 0x00;
 PORTL = 0x00;
 DDRL  = 0xC7;
}

//TIMER1 initialize - prescale:1
// WGM: 0) Normal, TOP=0xFFFF
// desired value: 400Hz
// actual value: 400.007Hz (0.0%)
void timer1_init(void)
{
 TCCR1B = 0x00; //stop
 TCNT1H = 0x94; //setup
 TCNT1L = 0x01;
 OCR1AH = 0x6B;
 OCR1AL = 0xFF;
 OCR1BH = 0x6B;
 OCR1BL = 0xFF;
 OCR1CH = 0x00;
 OCR1CL = 0x00;
 ICR1H  = 0x6B;
 ICR1L  = 0xFF;
 TCCR1A = 0x00;
 TCCR1C = 0x00;
 TCCR1B = 0x01; //start Timer
}

#pragma interrupt_handler timer1_compa_isr:iv_TIM1_COMPA
void timer1_compa_isr(void)
{
 //compare occured TCNT1=OCR1A
 if (arm_number == 0) { reset_1A(); }
 if (arm_number == 1) { reset_2A(); }
 if (arm_number == 2) { reset_3A(); }
 if (arm_number == 3) { reset_4A(); }
 if (arm_number == 4) { reset_5A(); }
 if (arm_number == 5) { reset_6A(); }
}

#pragma interrupt_handler timer1_compb_isr:iv_TIM1_COMPB
void timer1_compb_isr(void)
{
 //compare occured TCNT1=OCR1B
 if (arm_number == 0) { reset_1B(); }
 if (arm_number == 1) { reset_2B(); }
 if (arm_number == 2) { reset_3B(); }
 if (arm_number == 3) { reset_4B(); }
 if (arm_number == 4) { reset_5B(); }
 if (arm_number == 5) { reset_6B(); }
}

#pragma interrupt_handler timer1_compc_isr:iv_TIM1_COMPC
void timer1_compc_isr(void)
{
 //compare occured TCNT1=OCR1c
 if (arm_number == 0) { reset_1C(); }
 if (arm_number == 1) { reset_2C(); }
 if (arm_number == 2) { reset_3C(); }
 if (arm_number == 3) { reset_4C(); }
 if (arm_number == 4) { reset_5C(); }
 if (arm_number == 5) { reset_6C(); }
}

#pragma interrupt_handler timer1_ovf_isr:iv_TIM1_OVF
void timer1_ovf_isr(void)
{
 //TIMER1 has overflowed
 TCNT1H = 0x94; //reload counter high value
 TCNT1L = 0x01; //reload counter low value
 delay_count++;
 arm_number ++;
 if (arm_number>7)
 {
  	arm_number = 0;
 }
   
 if (arm_number == 0)
 {
  set_1A(); 
  set_1B(); 
  set_1C();
  OCR1AH = angle_upper_byte_1A;
  OCR1AL = angle_lower_byte_1A;
  OCR1BH = angle_upper_byte_1B;
  OCR1BL = angle_lower_byte_1B;
  OCR1CH = angle_upper_byte_1C;
  OCR1CL = angle_lower_byte_1C;
 }
 
 if (arm_number == 1)
 {
  set_2A(); 
  set_2B(); 
  set_2C();
  OCR1AH = angle_upper_byte_2A;
  OCR1AL = angle_lower_byte_2A;
  OCR1BH = angle_upper_byte_2B;
  OCR1BL = angle_lower_byte_2B;
  OCR1CH = angle_upper_byte_2C;
  OCR1CL = angle_lower_byte_2C;
 }
 
 if (arm_number == 2)
 {
  set_3A(); 
  set_3B(); 
  set_3C();
  OCR1AH = angle_upper_byte_3A;
  OCR1AL = angle_lower_byte_3A;
  OCR1BH = angle_upper_byte_3B;
  OCR1BL = angle_lower_byte_3B;
  OCR1CH = angle_upper_byte_3C;
  OCR1CL = angle_lower_byte_3C;
 }
 
 if (arm_number == 3)
 {
  set_4A(); 
  set_4B(); 
  set_4C();
  OCR1AH = angle_upper_byte_4A;
  OCR1AL = angle_lower_byte_4A;
  OCR1BH = angle_upper_byte_4B;
  OCR1BL = angle_lower_byte_4B;
  OCR1CH = angle_upper_byte_4C;
  OCR1CL = angle_lower_byte_4C;
 }
 
 if (arm_number == 4)
 {
  set_5A(); 
  set_5B(); 
  set_5C();
  OCR1AH = angle_upper_byte_5A;
  OCR1AL = angle_lower_byte_5A;
  OCR1BH = angle_upper_byte_5B;
  OCR1BL = angle_lower_byte_5B;
  OCR1CH = angle_upper_byte_5C;
  OCR1CL = angle_lower_byte_5C;
 }
 
 if (arm_number == 5)
 {
  set_6A(); 
  set_6B(); 
  set_6C();
  OCR1AH = angle_upper_byte_6A;
  OCR1AL = angle_lower_byte_6A;
  OCR1BH = angle_upper_byte_6B;
  OCR1BL = angle_lower_byte_6B;
  OCR1CH = angle_upper_byte_6C;
  OCR1CL = angle_lower_byte_6C;
 }
 //serial communication related code
 serial_communication_interval ++;
  if (serial_communication_interval > 40) //gives time interval of 40*2.5ms = 100ms
 {
  serial_communication_interval = 0;
  serial_communication_channel_number++;
  if(serial_communication_channel_number > 4) //set maximum number of command (can be set up to 7)
  {
  serial_communication_channel_number  = 3; //set first command to begin with (can be set up to 1)
  }
  UDR0 = serial_communication_channel_number;
 }
}

//UART0 initialize
// desired baud rate: 9600
// actual: baud rate:9600 (0.0%)
// char size: 8 bit
// parity: Disabled
void uart0_init(void)
{
 UCSR0B = 0x00; //disable while setting baud rate
 UCSR0A = 0x00;
 UCSR0C = 0x06;
 UBRR0L = 0x47; //set baud rate lo
 UBRR0H = 0x00; //set baud rate hi
 UCSR0B = 0x98;
}

//#pragma interrupt_handler uart0_rx_isr:iv_USART0_RXC
// void uart0_rx_isr(void)
// {
 // uart has received a character in UDR
 // remote_data[serial_communication_channel_number] = UDR0;  
// }

//call this routine to initialize all peripherals
void init_devices(void)
{
 //stop errant interrupts until set up
 CLI(); //disable all interrupts
 XMCRA = 0x00; //external memory
 XMCRB = 0x00; //external memory
 port_init();
 timer1_init();
 uart0_init();
 
 //uart3_init();

 MCUCR  = 0x00;
 EICRA  = 0x00; //pin change int edge 0:3
 EICRB  = 0x00; //pin change int edge 4:7
 PCICR  = 0x00; //pin change int enable
 PCMSK0 = 0x00; //pin change mask
 PCMSK1 = 0x00; //pin change mask
 PCMSK2 = 0x00; //pin change mask
 EIMSK  = 0x00;
 TIMSK0 = 0x00; //timer0 interrupt sources
 TIMSK1 = 0x0F; //timer1 interrupt sources
 TIMSK2 = 0x00; //timer2 interrupt sources
 TIMSK3 = 0x00; //timer3 interrupt sources
 TIMSK4 = 0x00; //timer4 interrupt sources
 TIMSK5 = 0x00; //timer5 interrupt sources
 
 SEI(); //re-enable interrupts
 //all peripherals are now initialized
}
