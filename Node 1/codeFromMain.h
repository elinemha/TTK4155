
#ifndef codeFromMain
#define codeFromMain

//Code from main
/*

	///////////////////////////BEFORE WHILE LOOP///////////////////////////////
	
	
	//status = mcp2515_read_status();
	//printf("Status: %x \n", status);
	
	
	//mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);
	mcp2515_write(MCP_CANCTRL, MODE_LOOPBACK);
	
	uint8_t value = mcp2515_read( MCP_CANSTAT);
	printf("%x \n", value);
	if (( value & MODE_MASK ) != MODE_LOOPBACK ) {
		printf (" MCP2515 is NOT in loopback mode  !\n");
	}
	else{
		printf (" MCP2515 is in loopback mode   !\n");
	}
	
	mcp2515_request_to_send(MCP_RTS_TX0);
	
	status = mcp2515_read_status();
	printf("Status: %x \n", status);
	
	//can_message cm;
	//cm.id = 2;
	//cm.length = '6';
	//cm.data = 'abcdef';
	
	//mcp2515_write(MCP_TXB1CTRL, 0x00);
	
	value = mcp2515_read(MCP_TX0IF);
	printf("TXF: %x \n", value);
	
	mcp_write_tx0_buffer(0x75);
	
	value = mcp2515_read(MCP_TX0IF);
	printf("TXF: %x \n", value);
	value = mcp2515_read(MCP_RX0IF);
	printf("RXF: %x \n", value);
	
	data_spi = mcp_read_rx0_buffer();
	printf("MCP Data: %x \n", data_spi);
	
	value = mcp2515_read(MCP_RX0IF);
	printf("RXF: %x \n", value);
	
	status = mcp2515_read_status();
	printf("Status: %x \n", status);
	
	//mcp2515_write(MCP_TXB1CTRL, 0x00);
	
	
	PORTB &= ~(1 << DDB4 );
	SPI_write(MCP_RESET);
	PORTB |= (1 << DDB4 );
	_delay_ms(50);
	
	PORTB &= ~(1 << DDB4 );
	SPI_write( MCP_WRITE ); // Send read instruction
	SPI_write( MCP_CANCTRL ); // Send address
	SPI_write(MODE_CONFIG);
	PORTB |= (1 << DDB4 );
	_delay_ms(50);
	
	PORTB &= ~(1 << DDB4 ); // Select CAN - controller
	SPI_write( MCP_WRITE ); // Send read instruction
	SPI_write( MCP_CANCTRL ); // Send address
	SPI_write( MODE_NORMAL ); // Send data
	PORTB |= (1 << DDB4 ); // Deselect CAN - controller
	*/


///////////////////////IN WHILE LOOP//////////////////////////////////////////////////////

/*
		

		SPI_Init();
		
		PORTB &= ~(1 << DDB4 );
		SPI_write(MCP_RESET);
		PORTB |= (1 << DDB4 );
		_delay_ms(1000);
		
		PORTB &= ~(1 << DDB4 ); // Select CAN - controller
		SPI_write( MCP_WRITE ); // Send read instruction
		SPI_write( MCP_CANCTRL ); // Send address
		SPI_write( MODE_LOOPBACK ); // Send data
		PORTB |= (1 << DDB4 ); // Deselect CAN - controller
		_delay_ms(1000);
		
		PORTB &= ~(1 << DDB4 ); // Select CAN - controller
		SPI_write( MCP_READ ); // Send read instruction
		SPI_write( MCP_CANSTAT ); // Send address
		data_spi = SPI_read () ; // Read result
		PORTB |= (1 << DDB4 ); // Deselect CAN - controller
		printf("SPI0  %02X \n", data_spi);
		_delay_ms(4000);
		
		for (uint8_t i=1; i<10; i++)
		{
			mcp_write_tx0_buffer(i);
		}
		
		for (uint8_t i=1; i<10; i++)
		{
			data_spi = mcp_read_rx0_buffer();
			printf("Trial and error: %02X \n", data_spi);
		}
		*/
		//PORTB &= ~(1 << DDB4 ); // Select CAN - controller
		//SPI_write( MCP_READ ); // Send read instruction
		//SPI_write( MCP_CANSTAT ); // Send address
		//data_spi = SPI_read () ;
		//PORTB |= (1 << DDB4 ); 
		//_delay_us(100);
	/*	
		PORTB &= ~(1 << PB4 );
		SPI_write(0xAA);
		SPI_write(0xAA);
		PORTB |= (1 << PB4 );
		_delay_us(100);
		
	*/

		//////////////////////////////////
		///////// JOYSTICK ///////////////
		//////////////////////////////////
		
		/*
		volatile uint8_t a = adc_read(0);
		volatile uint8_t b = adc_read(1);
		volatile uint8_t c = adc_read(2);
		volatile uint8_t d = adc_read(3);
		
		// printf("hey", ADC_test(1));
		printf("Pos X: %02X \n", a);
		printf("Pos Y: %02X \n", b);
		printf("Left Slider Value: %02X \n", c);
		printf("Right Slider Value: %02X \n", d);
		_delay_ms(1000);
		//SRAM_test();
		
		
		pos_s = read_slider_pos();
		pos_s = calibrate_slider_pos(pos_s);
		print_slider_pos(pos_s);

		pos_j = read_joystick_pos();
		pos_j = joystick_analog_pos(pos_j);
		print_joystick_pos(pos_j);

		dir_j = input_joystick_dir(pos_j);
		print_joystick_dir(dir_j);
		
		right_button_press();
		left_button_press();
		
		_delay_ms(1000);
		*/
		
		
		/////////////////////////////////
		////////////// OLED /////////////
		/////////////////////////////////
		/*
		pos_j = read_joystick_pos();
		pos_j = joystick_analog_pos(pos_j);
		dir_j = input_joystick_dir(pos_j);
		
		if(dir_j == UP)
		{
			if(position > 0)
			{
				position = position - 1;
			}
		}
		else if(dir_j == DOWN)
		{
			if(position < 7)
			{
				position = position + 1;
			}
		}
		_delay_ms(300);
		
		
		oled_reset();
		
		oled_pos(0x00, 0x00);
		char mystring[] = "OPTIONS  ";
		writing_oled8(mystring);
		
		oled_pos(0x01, 0x00);
		char mystring1[] = "SETTINGS  ";
		writing_oled8(mystring1);
		
		oled_pos(0x02, 0x00);
		char mystring2[] = "SOUND   ";
		writing_oled8(mystring2);
		
		oled_pos(0x03, 0x00);
		char mystring3[] = "START   ";
		writing_oled8(mystring3);
		
		oled_pos(0x04, 0x00);
		char mystring4[] = "EXIT    ";
		writing_oled8(mystring4);
		
		oled_pos(position, 0x00);
		char mystring5[] = "<<-----";
		writing_oled4(mystring5);
		
		//printf("Menu Position: %4d\n ", position);
		
		//display_on();
		//oled_reset();
		//int joy = 0;
		int joy = joystick_button_press();
		if (joy==0)
		{
			printf("Button is pressed!  %4d\n", joy);
			printf("Menu Position: %4d\n ", position);
		}
		*/
		
/*
		for (uint8_t page = 0; page <= 7; page++) {
			oled_pos(page,0);
			for (uint8_t col = 0; col <= 127; col++) {
				//oled_pos(page, col);
				oled_write_data(oled_data);
				//oled_data += 1;
				_delay_ms(100);
			}
			//_delay_ms(5000);
		}*/

	//writing('P');
	//writing('M');
	
		///////////////////////////////////AFTER MAIN LOOP///////////////////////////////////
		
	
/*


//	unsigned char data;
//sei();
//ADC_clock();	//USART_Transmit('A');
//DDRA = 0xFF;
//PORTA = 0x00;

//printf("hello");
//printf(stdin);

//for (int i = 0; i < 1; ++i)
//printf("Starting Clock\n");
//ADC_clock();
//printf("Ending Clock\n");
*/

//uint8_t oled_data = 0xFF;
	//uint8_t pos = 0x04;
	/*
	for (uint8_t i=0; i<10; i++)
	{
		mcp_write_tx0_buffer(i);
	}
	
	for (uint8_t i=0; i<10; i++)
	{
		data_spi = mcp_read_rx0_buffer();	
		printf("Trial and error: %02X \n", data_spi);
	}
	*/
	//PORTB &= ~(1 << PB4 );
	
		/*
		PORTB &= ~(1 << DDB4 );
		
		//mcp2515_write(MCP_CNF1, 0x04 );
		//data_spi = mcp2515_read(MCP_CNF1);
		//printf("Trial and error  %02X \n", data_spi);	
		SPI_write(0xFF);
		data_spi = SPI_read();	
		printf("SPI0  %02X \n", data_spi);
		_delay_ms(1000);
		SPI_write(0xFF);
		data_spi = SPI_read();
		printf("SPI0  %02X \n", data_spi);
		_delay_ms(1000);
		SPI_write(0xFF);
		data_spi = SPI_read();
		printf("SPI0  %02X \n", data_spi);
		_delay_ms(1000);
		SPI_write(0xFF);
		data_spi = SPI_read();
		printf("SPI0  %02X \n", data_spi);
		_delay_ms(1000);
		
		PORTB |= (1 << DDB4 );
		_delay_ms(5000);
		PORTB &= ~(1 << DDB4 );
		
		//mcp2515_write(MCP_CNF1, 0x04 );
		//data_spi = mcp2515_read(MCP_CNF1);
		//printf("Trial and error  %02X \n", data_spi);
		SPI_write(0x00);
		data_spi = SPI_read();
		printf("SPI0  %02X \n", data_spi);
		_delay_ms(1000);
		SPI_write(0x00);
		data_spi = SPI_read();
		printf("SPI0  %02X \n", data_spi);
		_delay_ms(1000);
		SPI_write(0x00);
		data_spi = SPI_read();
		printf("SPI0  %02X \n", data_spi);
		_delay_ms(1000);
		SPI_write(0x00);
		data_spi = SPI_read();
		printf("SPI0  %02X \n", data_spi);
		_delay_ms(1000);
		
		PORTB |= (1 << DDB4 );
		_delay_ms(5000);*/
		
/*
		mcp_write_tx0_buffer(0x0F);
		data_spi = mcp_read_rx0_buffer();
		
		printf("Trial and error: %02X \n", data_spi);
		_delay_ms(100);
		*/
			//writing_oled(mystring);



#endif