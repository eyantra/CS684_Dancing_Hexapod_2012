#include <iom2560v.h>
#include <macros.h>
#include "globalFunctions.h"
#include "dance_moves.h"


#ifndef NO_ACTION
#define NO_ACTION 200
#endif

unsigned char toggle = 0, motion_busy = 0;
unsigned char STAND_A = 90, STAND_B = 60, STAND_C = 20;
unsigned char stage = 0;

unsigned char getStage(void)
{
	return stage;
}

void setStage(unsigned char newStage)
{
	stage = newStage;
}

void stand(void)
{
	angle_1A(STAND_A); angle_1B(STAND_B); angle_1C(STAND_C); angle_2A(STAND_A); angle_2B(STAND_B); angle_2C(STAND_C);
	//1,2,3C angle0 - vertical?
	//4 5 6 angle180 - vertical?
	angle_3A(STAND_A); angle_3B(STAND_B); angle_3C(STAND_C); angle_4A(STAND_A); angle_4B(STAND_B); angle_4C(STAND_C);
	angle_5A(STAND_A); angle_5B(STAND_B); angle_5C(STAND_C); angle_6A(STAND_A); angle_6B(STAND_B); angle_6C(STAND_C);
}

void step_up(void)
{
	unsigned char pb =150, pc = 120;
	angle_all(NO_ACTION,pb,pc);
}

void step_up_slow(void)
{
	unsigned char pb = 150, pc = 120;
	angle_all(NO_ACTION,pb,pc);
}

void step_up_zhigzhig(unsigned char s)
{
	unsigned char i = s - 4;
	int j = 1;
	if (toggle == 0)
	{
		toggle = 1;
		j = 1;
	}
	else if (toggle == 1)
	{
		toggle = 0;
		j = -1;
	}
	
	angle_all(90+30*j,30+12*i,12*i);
}


void step_down(void)
{
	unsigned char pb = 30, pc = 0;
	angle_all(NO_ACTION,pb,pc);
}
void step16(void)
{
	if (toggle == 0)
	{
		toggle = 1;
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
		toggle = 0;
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
}

void step25(void)
{
	if (toggle == 0)
	{
		toggle = 1;
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
		toggle = 0;
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
}

void step34(void)
{
	if (toggle == 0)
	{
		toggle = 1;
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
		toggle = 0;
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
}

void danceMove_HANDS_AIR(void)
{
	unsigned char stage = getStage();

	motion_busy = 1;
	
	if (stage == 0)
	{
		stand();
	}
	else if (stage == 1)
	{
		step16();
	}
	else if (stage == 2)
	{
		step16();
	}
	else if (stage == 3)
	{
		step25();
	}
	else if (stage == 4)
	{
		step25();
	}
	else if (stage == 5)
	{
		step34();
	}
	else if (stage == 6)
	{
		step34();
	}
	else if (stage == 7)
	{
		step_down();
	}
	else if (stage == 8)
	{
		stand();
	}
	delay_50ms();
	if (stage == 8)
		setStage(1);
	else
		setStage(stage + 1);
	
	motion_busy = 0;
}
void slow_step_down(unsigned int time)
{
	unsigned char i = 0;
	unsigned char pa = 30, pc = 0;
	
	for( i=1; i<16; i++)
	{
		pa = STAND_B - 2 * i;
		pc = STAND_C - 1 * i;
		if (i == 15){
			pc = 0;
		}
		angle_all(NO_ACTION,pa,pc);
		delay_xms(time);
	}
}
void legs246_up_left(unsigned int time)
{
	unsigned char i=0;
	//angle_246(30, 10, 140);
	for(i=1; i<21; i++)
	{
		angle_246(STAND_A - 3*i, 30 - i, 7*i);
		delay_xms(time);
	}
}

unsigned char time_temp;

void danceMove_SlowTripod(unsigned char t){
	unsigned char i = 0;
	unsigned char stage = getStage();
	unsigned int j = 0;
	unsigned int time = t;
	
	i=0;
	motion_busy = 1;
	stand();
	slow_step_down(time);	
	legs246_up_left(time);
	
	for (i=1; i < 21; i++)
	{
		angle_135(NO_ACTION , 30 + 4*i, 3*i);
		angle_246(30 + 6*i, NO_ACTION, NO_ACTION);
		delay_xms(time);
	}
	//delay_1s();
	
	for (i=1; i < 21; i++)
	{
		angle_135(NO_ACTION , 110 - 4*i, 60 - 3*i);
		angle_246(150 - 6*i, NO_ACTION, NO_ACTION);
		delay_xms(time);
	}
	//delay_1s();
	for (i=1; i < 21; i++)
	{
		angle_135(NO_ACTION , 30 + 4*i, 3*i);
		angle_246(30 + 6*i, NO_ACTION, NO_ACTION);
		delay_xms(time);
	}
	//delay_1s();
	
	for (i=1; i < 21; i++)
	{
		angle_135(NO_ACTION , 110 - 4*i, 60 - 3*i);
		angle_246(150 - 6*i, NO_ACTION, NO_ACTION);
		delay_xms(time);
	}
	
	
	for(i=1; i<21; i++)
	{
		angle_246(30 + 3*i, 10 + i, 140 - 7*i);
		delay_xms(time);
	}
	
	for(i=1; i<21; i++)
	{
		if (i < 11)
		{
			angle_135(NO_ACTION, 30+2*i, i);
			angle_246(NO_ACTION, 30+2*i, i);
		}
		else
		{
			angle_135(NO_ACTION, 50+i, i);
			angle_246(NO_ACTION, 50+i, i);
		}
		delay_xms(time);
	}
	
	stand();
	motion_busy = 0;
	

}

void danceMove_RobotVibrate(void)
{
	unsigned char stage = getStage();
	unsigned int i = 0;
	unsigned char angle_B = 30;
	unsigned char angle_C = 0;

	int j = 1;

	motion_busy = 1;
	stand();
	
	
	step_down();

	delay_250ms();
	step_up_slow();
		delay_250ms();
	step_down();
	delay_250ms();
	for (i=0;i<=5;i++){
		angle_B = 30 + 3*(5-i);
		angle_C = 2*(5-i);
		angle_all(NO_ACTION,angle_B,angle_C);
	
		delay_100ms();
	
		angle_B = 30;
		angle_C = 0;
		angle_all(NO_ACTION,angle_B,angle_C);
	
		delay_100ms();
	
	}

	
	
	
	
	
	
	delay_250ms();
	stand();
	motion_busy = 0;
}

void danceMove_circularRaise(void)
{
	 unsigned char stage = getStage();

	motion_busy = 1;
	if ( stage == 0 ){
	stand();
	}
	else if (stage == 1 ){
	angle_1B(30);
	}
	else if (stage == 2 ){
	angle_1B(60);
	}
	// 2
	else if (stage == 3 ){
	angle_2B(30);
	}
	else if (stage == 4 ){
	angle_2B(60);
	}
	
	//3
	else if (stage == 5 ){
	angle_3B(30);
	}
	else if (stage == 6 ){
	angle_3B(60);
	}
	//6
	else if (stage == 7 ){
	angle_6B(30);
	}
	else if (stage == 8){
	angle_6B(60);
	}
	if (stage == 8)
		setStage(1);
	else
		setStage(stage + 1);
		motion_busy = 0;
}

void danceMove_zhigzhigRise(void)
{
	unsigned int i = 0;
	unsigned char angle_B = 30;
	unsigned char angle_C = 0;
	unsigned char stage = getStage();

	motion_busy = 1;
	
	if (stage == 0)
	{
		stand();
		toggle = 0;
	}
	else if (stage == 1){
	step_down();
	}
	else if (stage == 2 || stage == 3) {
	}
	
	else if (stage >=4 && stage <= 14){
	step_up_zhigzhig(stage);
	}
	else if (stage > 14 && stage <= 18){
		
	}
	else if (stage == 19){
		step_down();
		delay_100ms();
		for (i=0;i<=5;i++){
	
		angle_B = 30 + 6*(5-i);
		angle_C = 4*(5-i);
		angle_all(NO_ACTION,angle_B,angle_C);
		
		delay_100ms();
		
		angle_B = 30;
		angle_C = 0;
		angle_all(NO_ACTION,angle_B,angle_C);
		
		delay_100ms();
		}
	}
	else if (stage >= 20 && stage < 26){
	
	}
	else if (stage == 26 ){
	stand();
	}
	else if (stage ==27){
	}
	else if (stage == 28) {
		finale();
	}
	
	if (stage == 29){
		
	}
	else{
		setStage(stage + 1);
	}
	
	
	motion_busy = 0;
}




void danceMove_ZHIGZHIG(void)
{
	unsigned char stage = getStage();

	motion_busy = 1;
	
	if (stage == 0)
	{
		stand();
		toggle = 0;
		setStage(stage + 1);
	}
	else if (toggle == 0)
	{
		toggle = 1;
		angle_all(20, NO_ACTION, NO_ACTION);
	}
	else if (toggle == 1)
	{
		toggle = 0;
		angle_all(160, NO_ACTION, NO_ACTION);
	}
	
	motion_busy = 0;
}

void danceMove_KICK(void)
{
	unsigned char stage = getStage();

	motion_busy = 1;
	
	if (stage == 0)
	{
		stand();
		toggle = 0;
		setStage(stage + 1);
	}
	else if (toggle == 0)
	{
		toggle = 1;
		
		angle_1B(30);
		angle_6B(30);
		angle_1C(60);
		angle_6C(60);
		
	}
	else if (toggle == 1)
	{
		toggle = 0;
		angle_1B(STAND_B);
		angle_6B(STAND_B);
		angle_1C(STAND_C);
		angle_6C(STAND_C);
		

	}
	
	motion_busy = 0;
}

void finale(void)
{	unsigned char i = 0;
	unsigned char angle_B = 150;
	unsigned char angle_C = 120;
	motion_busy = 1;
	
	stand();
	delay_1s();
	
	// back legs to the back
	angle_6B(30);
	angle_3B(30);
	delay_250ms();
	angle_6A(50);
	angle_3A(130);
	delay_250ms();
	angle_6B(60);
	angle_3B(60);
	delay_250ms();
	
	// angle_2B(30);
	// angle_5B(30);
	// delay_250ms();
	// angle_2A(30);
	// angle_5A(150);
	// delay_1s();
	// angle_2B(60);
	// angle_5B(60);
	// delay_1s();
		

	step_up();
	delay_250ms();
	angle_2A(30);
	angle_5A(150);
	
	
	delay_250ms();
	
	
	
	angle_1B(0);
	angle_4B(0);
	angle_3C(0);
	angle_6C(0);
	
	delay_250ms();
	
	for (i=1;i<5;i++){
	angle_1C(160);
	angle_4C(160);
	angle_2B(170);
	angle_5B(170);
	
	delay_250ms();
	angle_1C(120);
	angle_4C(120);
	angle_2B(150);
	angle_2B(150);
	
	delay_250ms();
	
	}
	

	
	motion_busy = 0;
}

void performDanceMove(unsigned char moveId)
{
	if (moveId == 'a')
	{
		danceMove_KICK();
	}
	else if (moveId == 'b')
	{
		danceMove_KICK();
	}
	else if (moveId == 'c'){
		danceMove_ZHIGZHIG();
	}
	else if (moveId == 'd'){
		danceMove_circularRaise();
	}
	else if (moveId == 'e'){
		danceMove_HANDS_AIR();
	}
	else if (moveId == 'f'){
		danceMove_zhigzhigRise();
	}
	else if (moveId == 'g') {
		danceMove_SlowTripod(time_temp);
	}
	
	 
}

void performDanceMoveTime(unsigned char moveId,unsigned char time){
 if (moveId == 'g'){
	time_temp = time;
	danceMove_SlowTripod(time);
	}

}

void cancelMove(void)
{
	stand();
	delay_250ms();
	setStage(0);
}
