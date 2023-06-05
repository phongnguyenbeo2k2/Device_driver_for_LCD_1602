#ifndef I2C_LCD_H
#define I2C_LCD_H

#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define I2C_ADDRESS_LCD         0x27
#define I2C_DEVICE_FILE_PATH    "/dev/i2c-2"
#define LCD_CLEAR_DISPLAY       0x01
#define LCD_FUNCTION_SET        0x20
#define LCD_FUNCTION_DL_4BIT    0x00
#define LCD_FUNCTION_2_LINE     0x08
#define LCD_FUNCTION_F_5x08     0x00
#define LCD_DISPLAY_CONTROL     0x08
#define LCD_ENTRY_MODE_SET	    0x04
#define LCD_ENTRY_MODE_ID	    0x02
#define LCD_RS_CLEAR		    0x00
#define LCD_RS_SET		        (1 << 0)
#define LCD_RW_SET		        (1 << 1)
#define LCD_EN_SET 		        (1 << 2)
#define LCD_EN_CLEAR		    0x00
#define LCD_BLACK_LIGHT		    (1 << 3)
#define LCD_NO_BLACK_LIGHT	    0x00
#define LCD_CURSOR_BLINK_ON	    (1 << 0)
#define LCD_CURSOR_BLINK_OFF     0x00
#define LCD_RETURN_HOME 	    0x02
#define LCD_CURSOR_ON		    (1 << 1)
#define LCD_CURSOR_OFF		    0X00
#define LCD_DISPLAY_ON 		    (1 << 2)
#define LCD_DISPLAY_OFF 	    0x00

uint8_t  lcd_write(uint8_t  address, uint8_t *pData, uint8_t len );
void lcd_sendCommand (char command); // send Command to LCD
void lcd_sendData (uint8_t data); // send Data to LCD
void lcd_setCursorPosition (uint8_t row , uint8_t colum); // set proper cursor position on LCD
void lcd_clear(void); // clear display and reset address counter of DDRAM equal to 0
void lcd_init(void); //initialize LCD
void lcd_sendString (char *str); 
void lcd_set_cursor_on();// turn on cursor
void lcd_set_cursor_off(); // turn off cursor
void lcd_set_cursor_blink_on(); // turn on blink cursor
void lcd_set_cursor_blink_off(); // turn off blink cursor
void lcd_set_display_on();  // turn on display
void lcd_set_display_off(); // turn off display
void lcd_set_blacklight_on(); // turn on display on
void lcd_set_blacklight_off(); // turn off display off
void lcd_create_char(uint8_t location, uint8_t charmap[]); // define  new char for LCD



#endif