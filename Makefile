CC=/usr/bin/avr-gcc
MEGA=328p
CFLAGS=-Os -std=c99 -mmcu=atmega$(MEGA)
OBJ2HEX=/usr/bin/avr-objcopy 
PROG=/usr/bin/avrdude
TARGET=rgembigger
#TARGET=testtroller

program : $(TARGET).hex
	$(PROG) -c avrispv2 -p m$(MEGA) -P /dev/ttyACM0 -e
	$(PROG) -c avrispv2 -B8 -p m$(MEGA) -P /dev/ttyACM0 -U flash:w:$(TARGET).hex

%.obj : %.o
	$(CC) $(CFLAGS) $< -o $@

%.hex : %.obj
	$(OBJ2HEX) -j .text -j .data -O ihex $< $@  

clean :
	rm *.hex *.obj *.out 
