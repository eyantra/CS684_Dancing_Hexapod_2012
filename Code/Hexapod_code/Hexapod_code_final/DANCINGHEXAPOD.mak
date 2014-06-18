CC = iccavr
LIB = ilibw
CFLAGS =  -e -D__ICC_VERSION=723 -D__BUILD=14 -D_EE_EXTIO -DATMega1280  -l -g -MLongJump -MHasMul -MEnhanced -Wf-use_elpm 
ASFLAGS = $(CFLAGS) 
LFLAGS =  -g -nb:14 -e:0x20000 -ucrtatmega.o -bfunc_lit:0xe4.0x10000 -dram_end:0x21ff -bdata:0x200.0x21ff -dhwstk_size:30 -beeprom:0.4096 -fihx_coff -S2
FILES = main.o dance_moves.o 

DANCINGHEXAPOD:	$(FILES)
	$(CC) -o DANCINGHEXAPOD $(LFLAGS) @DANCINGHEXAPOD.lk   -lcatm128
main.o: D:\Softwares\iccv7avr\include\iom2560v.h D:\Softwares\iccv7avr\include\_iom640to2561v.h D:\Softwares\iccv7avr\include\macros.h D:\Softwares\iccv7avr\include\AVRdef.h .\helpers.h .\globals.h .\init.h .\communication.h .\hexapod_motion.h .\dance_moves.h
main.o:	main.c
	$(CC) -c $(CFLAGS) main.c
dance_moves.o: D:\Softwares\iccv7avr\include\iom2560v.h D:\Softwares\iccv7avr\include\_iom640to2561v.h D:\Softwares\iccv7avr\include\macros.h D:\Softwares\iccv7avr\include\AVRdef.h .\globalFunctions.h .\dance_moves.h
dance_moves.o:	dance_moves.c
	$(CC) -c $(CFLAGS) dance_moves.c
