
//#include "globals.h"
#ifndef HEXAPOD_MOTION_H
#define HEXAPOD_MOTION_H 0

#ifndef NO_ACTION
#define NO_ACTION 200
#endif
int error_3B = 10, error_4B = 0, error_6B = 0;

void angle_value_calculation (void)
{
 unsigned int angle_value = 0;
 unsigned int temp = 0;
 if (degree > 180)
 degree = 180; // limiting the scope of the servo rotation
 
 angle_value = 0xBF39 + (64 * (unsigned char) degree); //actual constant is 64.4
 
 angle_lower_byte = (unsigned char) angle_value; //separating the lower byte
 
 temp = angle_value >> 8;
 angle_upper_byte = (unsigned char) temp; //separating the upper byte
}

void angle_1A (unsigned char angle)
{
 degree = angle;
 angle_value_calculation();
 angle_upper_byte_1A = angle_upper_byte;
 angle_lower_byte_1A = angle_lower_byte;
}

void angle_1B (unsigned char angle)
{
 degree = angle;
 angle_value_calculation();
 angle_upper_byte_1B = angle_upper_byte;
 angle_lower_byte_1B = angle_lower_byte;
}

void angle_1C (unsigned char angle)
{
 degree = angle;
 angle_value_calculation();
 angle_upper_byte_1C = angle_upper_byte;
 angle_lower_byte_1C = angle_lower_byte;
}

void angle_2A (unsigned char angle)
{
 degree = angle;
 angle_value_calculation();
 angle_upper_byte_2A = angle_upper_byte;
 angle_lower_byte_2A = angle_lower_byte;
}

void angle_2B (unsigned char angle)
{
 degree = angle;
 angle_value_calculation();
 angle_upper_byte_2B = angle_upper_byte;
 angle_lower_byte_2B = angle_lower_byte;
}

void angle_2C (unsigned char angle)
{
 degree = angle;
 angle_value_calculation();
 angle_upper_byte_2C = angle_upper_byte;
 angle_lower_byte_2C = angle_lower_byte;
}

void angle_3A (unsigned char angle)
{
 degree = angle;
 angle_value_calculation();
 angle_upper_byte_3A = angle_upper_byte;
 angle_lower_byte_3A = angle_lower_byte;
}

void angle_3B (unsigned char angle)
{
 degree = angle + error_3B;
 angle_value_calculation();
 angle_upper_byte_3B = angle_upper_byte;
 angle_lower_byte_3B = angle_lower_byte;
}

void angle_3C (unsigned char angle)
{
 degree = angle;
 angle_value_calculation();
 angle_upper_byte_3C = angle_upper_byte;
 angle_lower_byte_3C = angle_lower_byte;
}

void angle_4A (unsigned char angle)
{
 degree = angle;
 angle_value_calculation();
 angle_upper_byte_4A = angle_upper_byte;
 angle_lower_byte_4A = angle_lower_byte;
}

void angle_4B (unsigned char angle)
{
 degree = 180 - angle + error_4B;
 angle_value_calculation();
 angle_upper_byte_4B = angle_upper_byte;
 angle_lower_byte_4B = angle_lower_byte;
}

void angle_4C (unsigned char angle)
{
 degree = 180 - angle;
 angle_value_calculation();
 angle_upper_byte_4C = angle_upper_byte;
 angle_lower_byte_4C = angle_lower_byte;
}

void angle_5A (unsigned char angle)
{
 degree = angle;
 angle_value_calculation();
 angle_upper_byte_5A = angle_upper_byte;
 angle_lower_byte_5A = angle_lower_byte;
}

void angle_5B (unsigned char angle)
{
 degree =180 - angle;
 angle_value_calculation();
 angle_upper_byte_5B = angle_upper_byte;
 angle_lower_byte_5B = angle_lower_byte;
}

void angle_5C (unsigned char angle)
{
 degree = 180 - angle;
 angle_value_calculation();
 angle_upper_byte_5C = angle_upper_byte;
 angle_lower_byte_5C = angle_lower_byte;
}

void angle_6A (unsigned char angle)
{
 degree = angle;
 angle_value_calculation();
 angle_upper_byte_6A = angle_upper_byte;
 angle_lower_byte_6A = angle_lower_byte;
}

void angle_6B (unsigned char angle)
{
 degree = 180-angle + error_6B;
 angle_value_calculation();
 angle_upper_byte_6B = angle_upper_byte;
 angle_lower_byte_6B = angle_lower_byte;
}

void angle_6C (unsigned char angle)
{
 degree = 180 - angle;
 angle_value_calculation();
 angle_upper_byte_6C = angle_upper_byte;
 angle_lower_byte_6C = angle_lower_byte;
}

void angle_135(unsigned char A, unsigned char B, unsigned char C)
{
	if (A != NO_ACTION)
	{
		angle_1A(A);
		angle_3A(A);
		angle_5A(A);
	}
	
	if (B != NO_ACTION)
	{
		angle_1B(B);
		angle_3B(B);
		angle_5B(B);
	}
	
	if (C != NO_ACTION)
	{
		angle_1C(C);
		angle_3C(C);
		angle_5C(C);
	}
}

void angle_246(unsigned char A, unsigned char B, unsigned char C)
{
	if (A != NO_ACTION)
	{
		angle_2A(A);
		angle_4A(A);
		angle_6A(A);
	}
	
	if (B != NO_ACTION)
	{
		angle_2B(B);
		angle_4B(B);
		angle_6B(B);
	}
	
	if (C != NO_ACTION)
	{
		angle_2C(C);
		angle_4C(C);
		angle_6C(C);
	}
}

void angle_all(unsigned char A, unsigned char B, unsigned char C)
{
	angle_135(A, B, C);
	angle_246(A, B, C);
}

void servo_calibration (void)
{
angle_1A(90); angle_1B(90); angle_1C(0); angle_2A(90); angle_2B(90); angle_2C(0);
//1,2,3C angle0 - vertical?
//4 5 6 angle180 - vertical?
angle_3A(90); angle_3B(90); angle_3C(0); angle_4A(90); angle_4B(90); angle_4C(0);
angle_5A(90); angle_5B(90); angle_5C(0); angle_6A(90); angle_6B(90); angle_6C(0);
//angle_1A(90); angle_1B(90); angle_1C(90); angle_2A(90); angle_2B(90); angle_2C(90);
//angle_3A(90); angle_3B(90); angle_3C(90); angle_4A(90); angle_4B(90); angle_4C(90);
//angle_5A(90); angle_5B(90); angle_5C(90); angle_6A(90); angle_6B(90); angle_6C(90);
}

#endif