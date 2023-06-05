#include "i2c-lcd.h"

int fd; // file description of i2c file 
char smile[] = {0x00, 0x00, 0x0A, 0x00, 0x11, 0x0E, 0x00, 0x00 }; // pattern of smile character
char bell[]  = {0x00, 0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x04, 0x00}; // pattern of bell character

uint8_t  lcd_write(uint8_t  address, uint8_t *pData, uint8_t len )
{
	int ret;
	char buf[len + 1];
	buf[0] = address;
	for (int i = 1; i < (len +1); i++)
	{
		buf[i] =*(pData+(i-1));
	}
	ret = write(fd, buf, (len + 1));
	if (ret <= 0)
	{
		perror ("Write failed/n");
		return -1;
	}

}	

void lcd_sendCommand (char command)
{
	const char commandBit4to7 = (command & 0xf0);
	const char commandBit0to3 = (0xF0 & (command << 4));
	uint8_t commandBuf[4];
	commandBuf[0] = commandBit4to7 | LCD_EN_SET |LCD_BLACK_LIGHT|LCD_RS_CLEAR;
	commandBuf[1] = commandBit4to7 | LCD_BLACK_LIGHT|LCD_RS_CLEAR|LCD_EN_CLEAR;
	commandBuf[2] = commandBit0to3 | LCD_EN_SET | LCD_BLACK_LIGHT|LCD_RS_CLEAR ;
	commandBuf[3] = commandBit0to3 | LCD_BLACK_LIGHT|LCD_RS_CLEAR|LCD_EN_CLEAR ;
	lcd_write(I2C_ADDRESS_LCD, (uint8_t *)commandBuf, 4);
}

void lcd_sendData (uint8_t data)
{
	const uint8_t dataBit4to7 = (0xF0 & data);
	const uint8_t dataBit0to3 = (0xF0 & (data << 4 ));
	uint8_t dataBuf[4];
	dataBuf[0] = dataBit4to7 | LCD_EN_SET |LCD_BLACK_LIGHT |LCD_RS_SET;
	dataBuf[1] = dataBit4to7 | LCD_BLACK_LIGHT | LCD_RS_SET|LCD_EN_CLEAR;
	dataBuf[2] = dataBit0to3 | LCD_EN_SET | LCD_BLACK_LIGHT| LCD_RS_SET;
	dataBuf[3] = dataBit0to3 | LCD_BLACK_LIGHT | LCD_RS_SET|LCD_EN_CLEAR;
	lcd_write(I2C_ADDRESS_LCD, (uint8_t *) dataBuf, 4);
}

void lcd_setCursorPosition (uint8_t row , uint8_t colum)
{
	switch (row)
	{
		case 1: 
			colum |= 0x80;
			break;
		case 2: 
			colum |= 0xC0;
			break;
	}
	lcd_sendCommand(colum);
}

void lcd_clear(void)
{
	lcd_sendCommand (0x80);
	for (int i = 0; i < 70; i ++)
	{
		lcd_sendData(' ');
	}
}

void  lcd_init(void)
{
	lcd_sendCommand (LCD_FUNCTION_SET | LCD_FUNCTION_DL_4BIT | LCD_FUNCTION_2_LINE | LCD_FUNCTION_F_5x08); // lcd mode 4 bit, display on 2 lines, font char 5x8
	usleep(8000);
       lcd_sendCommand (LCD_DISPLAY_CONTROL );
	usleep(8000);
	lcd_sendCommand (LCD_CLEAR_DISPLAY); // clear entire display and reset address counter of DDRAM equal to 0
	usleep(8000);
	lcd_sendCommand (LCD_ENTRY_MODE_SET | LCD_ENTRY_MODE_ID); // cursor incremented by 1
	usleep (8000);
	lcd_sendCommand(LCD_DISPLAY_CONTROL | LCD_DISPLAY_ON); // turn on display lcd
	usleep(8000);
}

void lcd_sendString (char *str)
{
	while (*str )
	{
		lcd_sendData (*str++);
	}
}

void lcd_set_cursor_on()
{
	char command = LCD_DISPLAY_CONTROL | LCD_CURSOR_ON| LCD_DISPLAY_ON;
	lcd_sendCommand(command);
}

void lcd_set_cursor_off()
{
	char command = LCD_DISPLAY_CONTROL | LCD_CURSOR_OFF | LCD_DISPLAY_ON;
	lcd_sendCommand(command);
}

void lcd_set_cursor_blink_on()
{
	char command = LCD_DISPLAY_CONTROL | LCD_CURSOR_BLINK_ON | LCD_DISPLAY_ON;
	lcd_sendCommand(command);
}
void lcd_set_cursor_blink_off()
{
	char command = LCD_DISPLAY_CONTROL | LCD_CURSOR_BLINK_OFF| LCD_DISPLAY_ON;
	lcd_sendCommand(command);
}

void lcd_set_display_on()
{
	char command = LCD_DISPLAY_CONTROL | LCD_DISPLAY_ON;
	lcd_sendCommand(command);
}

void lcd_set_display_off()
{
	char command = LCD_DISPLAY_CONTROL | LCD_DISPLAY_OFF;
	lcd_sendCommand(command);
}

void lcd_set_blacklight_on()
{
	uint8_t  data = LCD_BLACK_LIGHT;
	lcd_write(I2C_ADDRESS_LCD, &data, 1);
}
void lcd_set_blacklight_off()
{
	uint8_t data = LCD_NO_BLACK_LIGHT;
	lcd_write(I2C_ADDRESS_LCD, &data, 1);
}

void lcd_create_char(uint8_t location, uint8_t charmap[])
{
	uint8_t i = 0;
	switch(location)
	{
	case 0: 	
		lcd_sendCommand(0x40);
		for (i = 0; i < 8; i ++)
			{
			lcd_sendData(charmap[i]);
			}
		break;
	case 1: 
		lcd_sendCommand(0x48);
		for (i = 0; i < 8; i++) lcd_sendData(charmap[i]);
		break;
	case 2: 
		lcd_sendCommand(0x40 + 16);
		for (i = 0; i < 8; i++) lcd_sendData(charmap[i]);
		break;
	case 3: lcd_sendCommand(0x40 + 24);
		for (i = 0; i < 8; i ++)
		lcd_sendData(charmap[i]);
		break;
	case 4:
		lcd_sendCommand(0x40 + 32);
		for (i = 0; i < 8; i++)
		lcd_sendData(charmap[i]);
		break;
	case 5: 
		lcd_sendCommand (0x40 + 40);
		for (i = 0; i < 8; i++);
		lcd_sendData(charmap[i]);
		break;
	case 6:
		lcd_sendCommand (0x40 + 48);
		for (i = 0; i < 8; i++);
		lcd_sendData(charmap[i]);
		break;
	case 7:
		lcd_sendCommand (0x40 + 56);
		for (i = 0; i < 8; i ++);
		lcd_sendData(charmap[i]);
	}
}	

