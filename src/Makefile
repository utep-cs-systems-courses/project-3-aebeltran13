# makfile configuration
COMMON_OBJECTS  = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as
AR		= msp430-elf-ar

all: main.elf 

#additional rules for files
main.elf: ${COMMON_OBJECTS} p1_interrupt_handler.o wdInterruptHandler.o buzzer.o stateMachines.o led.o switches.o main.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lLcd -lTimer -lp2sw

load: main.elf
	msp430loader.sh main.elf
clean:
	rm -f *.o *.elf *.a

