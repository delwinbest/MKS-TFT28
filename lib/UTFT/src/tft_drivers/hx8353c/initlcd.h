case HX8353C:
	
//new init
#if defined(STM32F107xC)

		LCD_Write_COM(0xFE);                     // lcd Type check
      LCD_Write_COM(0xEF);
      LCD_Write_COM(0x36);

		if (orient==1)
		{LCD_Write_DATA(0x64);//rotate 180deg
		}
		else
		{
			LCD_Write_DATA(0xa4);//orientation
		}
	  LCD_Write_COM(0x3A);
      LCD_Write_DATA(5);
      LCD_Write_COM(0xE8);
      LCD_Write_DATA(0x12);
      LCD_Write_DATA(0x22);
      LCD_Write_COM(0xE3);
      LCD_Write_DATA(1);
      LCD_Write_DATA(4);
      LCD_Write_COM(0xA5);
      LCD_Write_DATA(0x40);
      LCD_Write_DATA(0x40);
      LCD_Write_COM(0xA4);
      LCD_Write_DATA(0x44);
      LCD_Write_DATA(0x44);
      LCD_Write_COM(0xAB);
      LCD_Write_DATA(8);
      LCD_Write_COM(0xAA);
      LCD_Write_DATA(0x88);
      LCD_Write_DATA(0x88);
      LCD_Write_COM(0xAE);
      LCD_Write_DATA(0xB);
      LCD_Write_COM(0xAC);
      LCD_Write_DATA(0);
      LCD_Write_COM(0xAF);
      LCD_Write_DATA(0x77);
      LCD_Write_COM(0xAD);
      LCD_Write_DATA(0x77);
      
      LCD_Write_COM(0x2A);
      LCD_Write_DATA(0);
      LCD_Write_DATA(0);
      LCD_Write_DATA(0);
      LCD_Write_DATA(0xEF);
      LCD_Write_COM(0x2B);
      LCD_Write_DATA(0);
      LCD_Write_DATA(0);
      LCD_Write_DATA(1);
      LCD_Write_DATA(0x3F);
      
      LCD_Write_COM(0x2C);
      
      LCD_Write_COM(0xF0);
      LCD_Write_DATA(2);
      LCD_Write_DATA(0);
      LCD_Write_DATA(0);
      LCD_Write_DATA(1);
      LCD_Write_DATA(1);
      LCD_Write_DATA(7);
      
      LCD_Write_COM(0xF1);
      LCD_Write_DATA(1);
      LCD_Write_DATA(3);
      LCD_Write_DATA(0);
      LCD_Write_DATA(0x36);
      LCD_Write_DATA(41);
      LCD_Write_DATA(0x13);
      
      LCD_Write_COM(0xF2);
      LCD_Write_DATA(8);
      LCD_Write_DATA(6);
      LCD_Write_DATA(0x24);
      LCD_Write_DATA(3);
      LCD_Write_DATA(5);
      LCD_Write_DATA(0x34);
      
      LCD_Write_COM(0xF3);
      LCD_Write_DATA(0x16);
      LCD_Write_DATA(0xC);
      LCD_Write_DATA(0x5A);
      LCD_Write_DATA(4);
      LCD_Write_DATA(3);
      LCD_Write_DATA(0x69);
      
      LCD_Write_COM(0xF4);
      LCD_Write_DATA(0xD);
      LCD_Write_DATA(0x18);
      LCD_Write_DATA(0x15);
      LCD_Write_DATA(5);
      LCD_Write_DATA(5);
      LCD_Write_DATA(0);
      
      LCD_Write_COM(0xF5);
      LCD_Write_DATA(0xD);
      LCD_Write_DATA(0x18);
      LCD_Write_DATA(0x17);
      LCD_Write_DATA(0x35);
      LCD_Write_DATA(0x39);
      LCD_Write_DATA(0);
      LCD_Write_COM(0x11);
	
	delay(150);
      LCD_Write_COM(0x29);
      LCD_Write_COM(0x2C);
	
		break;
	#else
	
	LCD_Write_COM(0xB9);//SETEXTC
		LCD_Write_DATA(0xFF);
		LCD_Write_DATA(0x83);
		LCD_Write_DATA(0x53);

		LCD_Write_COM(0xB0);//RADJ
		LCD_Write_DATA(0x3C);
		LCD_Write_DATA(0x01);

		LCD_Write_COM(0xB6);//VCOM
		LCD_Write_DATA(0x94);
		LCD_Write_DATA(0x6C);
		LCD_Write_DATA(0x50);   

		LCD_Write_COM(0xB1);//PWR
		LCD_Write_DATA(0x00);
		LCD_Write_DATA(0x01);
		LCD_Write_DATA(0x1B);
		LCD_Write_DATA(0x03);
		LCD_Write_DATA(0x01);
		LCD_Write_DATA(0x08);
		LCD_Write_DATA(0x77);
		LCD_Write_DATA(0x89);

		LCD_Write_COM(0xE0); //Gamma setting for tpo Panel
		LCD_Write_DATA(0x50);
		LCD_Write_DATA(0x77);
		LCD_Write_DATA(0x40);
		LCD_Write_DATA(0x08);
		LCD_Write_DATA(0xBF);
		LCD_Write_DATA(0x00);
		LCD_Write_DATA(0x03);
		LCD_Write_DATA(0x0F);
		LCD_Write_DATA(0x00);
		LCD_Write_DATA(0x01);
		LCD_Write_DATA(0x73);
		LCD_Write_DATA(0x00);
		LCD_Write_DATA(0x72);
		LCD_Write_DATA(0x03);
		LCD_Write_DATA(0xB0);
		LCD_Write_DATA(0x0F);
		LCD_Write_DATA(0x08);
		LCD_Write_DATA(0x00);
		LCD_Write_DATA(0x0F);

		LCD_Write_COM(0x3A);   
		LCD_Write_DATA(0x05);  //05 
		LCD_Write_COM(0x36);    
		LCD_Write_DATA(0xC0); //83  //0B 

		LCD_Write_COM(0x11); // SLPOUT  
		delay(150);

		LCD_Write_COM(0x29);    // display on

		delay(150);
		LCD_Write_COM(0x2D);  //Look up table

		for(int j=0;j<32;j++)
		{ LCD_Write_DATA(2*j); } //Red
		for(int j=0;j<64;j++)
		{ LCD_Write_DATA(1*j); } //Green
		for(int j=0;j<32;j++)
		{ LCD_Write_DATA(2*j); } //Blue 

		LCD_Write_COM(0x2c);  
		delay(150);	 
	break;
#endif