#include "main.h"

extern int fd; // file description of i2c file 
extern char smile[]; // pattern of smile character
extern char bell[]; // pattern of bell character

int main (void)
{
	fd = open(I2C_DEVICE_FILE_PATH,O_RDWR);
	if (fd < 0)
	{
		printf ("Failure to open i2c-2 device file.\n");
		return -1;
		close(fd);
	}else printf ("open file sucessfully.\n");
	int connect_lcd = ioctl(fd,I2C_SLAVE,I2C_ADDRESS_LCD);
	if (fd < 0)
	{
		perror("Failure to set I2C address of LCD with Beagle Bone.\n");
		close(fd);
		return -1;
	}else printf ("Successfully.\n");

	lcd_init();

	lcd_set_blacklight_off();
	sleep(1);
	lcd_set_blacklight_on();

	lcd_setCursorPosition(1,4);
	lcd_sendString("PIF LAB");
	lcd_create_char(0, smile);
	lcd_setCursorPosition(2,5);
	lcd_sendData(0);
	lcd_create_char(1, bell);
	lcd_setCursorPosition(2,6);
	lcd_sendData(1);
	lcd_set_cursor_on();
	lcd_set_cursor_blink_on();
	sleep(3);
	lcd_set_cursor_blink_off();
	lcd_set_cursor_off();

	lcd_set_display_off();
	sleep(1);
	lcd_set_display_on();
	lcd_clear();
	lcd_setCursorPosition(1,0);
	lcd_sendString("Hello World");
	sleep(1);
	return 0;	
}