#include "oled.h"
#include "fonts.h"


void oled_write_command(uint8_t command)
{
    volatile char* address = (char*) 0x1000;
    address[0] = command;
}


void oled_write_data(uint8_t data)
{
    volatile char* address = (char*) 0x1200;  // using A[9] to indicate the command/data mode, since address is auto-incremented
    address[0] = data;
}

void oled_init()
{
	oled_write_command(0xae); // display off
	oled_write_command(0xa1); //segment remap
	oled_write_command(0xda); //common pads hardware: alternative
	oled_write_command(0x12);
	oled_write_command(0xc8); //common output scan direction:com63~com0
	oled_write_command(0xa8); //multiplex ration mode:63
	oled_write_command(0x3f);
	oled_write_command(0xd5); //display divide ratio/osc. freq. mode
	oled_write_command(0x80);
	oled_write_command(0x81); //contrast control
	oled_write_command(0x50);
	oled_write_command(0xd9); //set pre-charge period
	oled_write_command(0x21);
	oled_write_command(0x20); //Set Memory Addressing Mode
	oled_write_command(0x02); //Page addressing mode
	oled_write_command(0xdb); //VCOM deselect level mode
	oled_write_command(0x30);
	oled_write_command(0xad); //master configuration
	oled_write_command(0x00);
	oled_write_command(0xa4); //out follows RAM content
	oled_write_command(0xa6); //set normal display
	oled_write_command(0xaf); // display on
}

void display_on()
{
	oled_write_command(0xA5); // OLED command which turns-on the whole screen
}

void oled_go_to_line(uint8_t page)
{
    oled_write_command(0xB0 | (page & 0x07));
}

void oled_go_to_col(uint8_t col)
{
  // Setting lower 4 bits
  uint8_t lower_address = col & 0x0F;
  oled_write_command(lower_address);

  // Setting upper 4 bits
  uint8_t upper_address = 0x1F & ((col & 0xF0) >> 4);
  oled_write_command(upper_address);
}

void oled_pos(uint8_t page, uint8_t col)
{
    oled_go_to_line(page);
    oled_go_to_col(col);
}

void oled_reset()
{
  for (uint8_t page = 0; page <= 7; page++)
  {
    oled_pos(page, 0);
    for (uint8_t col = 0; col <= 127; col++)
	{
      oled_write_data(0x00);
    }
  }
}

void oled_clear_line(uint8_t page)
{
  oled_pos(page, 0);
  for (uint8_t col = 0; col <= 127; col++)
  {
      oled_write_data(0x00);
  }
}

void writing5(char c) // Writing single character using font5
{
	for (uint8_t i = 0; i<5; i++)
	{
		oled_write_data(pgm_read_byte(&font5[c-32][i]));
	}
}

void writing4(char c) // Writing single character using font4
{
	for (uint8_t i = 0; i<4; i++)
	{
		oled_write_data(pgm_read_byte(&font4[c-32][i]));
	}
}

void writing8(char c) // Writing single character using font8
{
	for (uint8_t i = 0; i<8; i++)
	{
		oled_write_data(pgm_read_byte(&font8[c-32][i]));
	}
}

void writing_oled4(const char* data) // Writing strings using font4
{
	int i = 0;
	while(data[i] != '\0')
	{
		writing4(data[i]);
		++i;
	}
}

void writing_oled5(const char* data) // Writing strings using font5
{
	int i = 0;
	while(data[i] != '\0')
	{
		writing5(data[i]);
		++i;
	}
}

void writing_oled8(const char* data) // Writing strings using font8
{
	int i = 0;
	while(data[i] != '\0')
	{
		writing8(data[i]);
		++i;
	}
}