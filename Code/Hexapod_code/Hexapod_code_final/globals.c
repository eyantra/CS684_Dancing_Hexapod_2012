unsigned char arm_number = 0;
unsigned char angle_upper_byte = 0; 
unsigned char angle_lower_byte = 0;
unsigned char degree = 0;
unsigned char angle_upper_byte_1A, angle_lower_byte_1A; angle_upper_byte_1B, angle_lower_byte_1B; angle_upper_byte_1C, angle_lower_byte_1C;
unsigned char angle_upper_byte_2A, angle_lower_byte_2A; angle_upper_byte_2B, angle_lower_byte_2B; angle_upper_byte_2C, angle_lower_byte_2C;
unsigned char angle_upper_byte_3A, angle_lower_byte_3A; angle_upper_byte_3B, angle_lower_byte_3B; angle_upper_byte_3C, angle_lower_byte_3C;
unsigned char angle_upper_byte_4A, angle_lower_byte_4A; angle_upper_byte_4B, angle_lower_byte_4B; angle_upper_byte_4C, angle_lower_byte_4C;
unsigned char angle_upper_byte_5A, angle_lower_byte_5A; angle_upper_byte_5B, angle_lower_byte_5B; angle_upper_byte_5C, angle_lower_byte_5C;
unsigned char angle_upper_byte_6A, angle_lower_byte_6A; angle_upper_byte_6B, angle_lower_byte_6B; angle_upper_byte_6C, angle_lower_byte_6C;
unsigned int delay_count = 0;
//variables relatd to the serial commuication or remote control
unsigned int serial_communication_interval = 0;
unsigned char serial_communication_channel_number  = 0;
unsigned char remote_data [8]; //see remote channel allocation in the notes above
unsigned char motion_busy = 0; //sets to one if any of the motion function is called.
