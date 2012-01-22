/*
 MPR121.h
 MPR121 WhellPad Example Code
 
 by:Waiman Zhao
 Mail:Binpower@foxmail.com
 created on: 11/2/14
 license: CC-SA 3.0
 
 Hardware: 3.3V Arduino Pro Mini
           SDA -> A4
           SCL -> A5
           IRQ -> D2
*/

#include <Wire.h>
#include <Arduino.h>

#define MPR121 0x5B	// ADD pin is Vcc So address is 0x5B

// MPR121 Register Defines
#define E0BV	0x1E
#define E1BV	0x1F
#define E2BV	0x20
#define E3BV	0x21
#define E4BV	0x22
#define E5BV	0x23
#define E6BV	0x24
#define E7BV	0x25
#define E8BV	0x26
#define E9BV	0x27
#define E10BV	0x28
#define E11BV	0x29
#define E12BV	0x2A


#define MHD_R	0x2B
#define NHD_R	0x2C
#define	NCL_R 	0x2D
#define	FDL_R	0x2E
#define	MHD_F	0x2F
#define	NHD_F	0x30
#define	NCL_F	0x31
#define	FDL_F	0x32


#define	ELE0_T	0x41
#define	ELE0_R	0x42
#define	ELE1_T	0x43
#define	ELE1_R	0x44
#define	ELE2_T	0x45
#define	ELE2_R	0x46
#define	ELE3_T	0x47
#define	ELE3_R	0x48
#define	ELE4_T	0x49
#define	ELE4_R	0x4A
#define	ELE5_T	0x4B
#define	ELE5_R	0x4C
#define	ELE6_T	0x4D
#define	ELE6_R	0x4E
#define	ELE7_T	0x4F
#define	ELE7_R	0x50
#define	ELE8_T	0x51
#define	ELE8_R	0x52
#define	ELE9_T	0x53
#define	ELE9_R	0x54
#define	ELE10_T	0x55
#define	ELE10_R	0x56
#define	ELE11_T	0x57
#define	ELE11_R	0x58


#define	AFE1_CFG	0x5C
#define	AFE2_CFG	0x5D
#define	ELE_CFG		0x5E


#define GPIO_CTRL0	0x73
#define	GPIO_CTRL1	0x74
#define GPIO_DATA	0x75
#define	GPIO_DIR	0x76
#define	GPIO_EN		0x77
#define	GPIO_SET	0x78
#define	GPIO_CLEAR	0x79
#define	GPIO_TOGGLE	0x7A


#define	ATO_CFG0	0x7B
#define	ATO_CFGU	0x7D
#define	ATO_CFGL	0x7E
#define	ATO_CFGT	0x7F
#define	RES_CF          0x80

// Global Constants	//隔住阻焊层
#define TOU_THRESH	0x06
#define	REL_THRESH	0x03
#define	START_BV	0x90
// Global Constants	//隔住0.5mm
//#define TOU_THRESH	0x06
//#define	REL_THRESH	0x03



void mpr121Write(uint8_t reg,uint8_t data){
   Wire.beginTransmission((uint8_t)MPR121);
   Wire.write(reg); 
   Wire.write(data); 
   Wire.endTransmission();
}

void mpr121Read(uint8_t reg,uint8_t length,uint8_t *ReturnData)
{
   Wire.beginTransmission(MPR121);
   Wire.write(reg); 
   //Wire.endTransmission();
   Wire.requestFrom((uint8_t)MPR121, length);  
   uint8_t i=0;
   while(Wire.available())    // slave may send less than requested
   { 
     ReturnData[i] = Wire.read(); // receive a byte as character
     i++;
   }
}

int readTouch()
{
   Wire.requestFrom((uint8_t)MPR121,(uint8_t)2);  
   uint8_t a,b;
   if(Wire.available()>=2)    // slave may send less than requested
   { 
     a = Wire.read(); // receive a byte as character
     b = Wire.read();
     return (a | (int)(b<<8));
   }else
   {
     return 0;
   }   
}

void mpr121QuickConfig(void){
	// STOP
	mpr121Write(ELE_CFG, 0x00);
        mpr121Write(RES_CF, 0X63);
        delay(10);
	// Section A
	// This group controls filtering when data is > baseline.
	mpr121Write(MHD_R, 0x01);
	mpr121Write(NHD_R, 0x01);
	mpr121Write(NCL_R, 0x00);
	mpr121Write(FDL_R, 0x00);

	// Section B
	// This group controls filtering when data is < baseline.
	mpr121Write(MHD_F, 0x01);
	mpr121Write(NHD_F, 0x01);
	mpr121Write(NCL_F, 0xFF);
	mpr121Write(FDL_F, 0x02);

	// Section C
	// This group sets touch and release thresholds for each electrode
	mpr121Write(ELE0_T, TOU_THRESH);
	mpr121Write(ELE0_R, REL_THRESH);
	mpr121Write(ELE1_T, TOU_THRESH);
	mpr121Write(ELE1_R, REL_THRESH);
	mpr121Write(ELE2_T, TOU_THRESH);
	mpr121Write(ELE2_R, REL_THRESH);
	mpr121Write(ELE3_T, TOU_THRESH);
	mpr121Write(ELE3_R, REL_THRESH);
	mpr121Write(ELE4_T, TOU_THRESH);
	mpr121Write(ELE4_R, REL_THRESH);
	mpr121Write(ELE5_T, TOU_THRESH);
	mpr121Write(ELE5_R, REL_THRESH);
	mpr121Write(ELE6_T, TOU_THRESH);
	mpr121Write(ELE6_R, REL_THRESH);
	mpr121Write(ELE7_T, TOU_THRESH);
	mpr121Write(ELE7_R, REL_THRESH);
	mpr121Write(ELE8_T, TOU_THRESH);
	mpr121Write(ELE8_R, REL_THRESH);
	mpr121Write(ELE9_T, TOU_THRESH);
	mpr121Write(ELE9_R, REL_THRESH);
	mpr121Write(ELE10_T, TOU_THRESH);
	mpr121Write(ELE10_R, REL_THRESH);
	mpr121Write(ELE11_T, TOU_THRESH);
	mpr121Write(ELE11_R, REL_THRESH);

	// Section D
	// Set the Filter Configuration
	// Set ESI2
	mpr121Write(AFE1_CFG, 0x10);
	//AFE配置1 （默认=0x10）
	//	一级采样FFI:00-6次
	//	充放电电流CDC:100000 - 32uA
	mpr121Write(AFE2_CFG, 0x04);
	//AFE配置2	（默认=0x24）
	//	充电时间CDT:010 - 1us
	//	二级采样SFI:00 - 4次
	//	二级采样间隔ESI:100 - 16ms


	// Section E
	// Electrode Configuration
	// Enable 6 Electrodes and set to run mode
	// Set ELE_CFG to 0x00 to return to standby mode
	mpr121Write(ELE_CFG, 0x8C);	// Enables all 12 Electrodes

	//AFE配置1
	//	CL
	//	ELEPROX
	//	ELE:
	// Section F
	// Enable Auto Config and auto Reconfig
	/*mpr121Write(ATO_CFG0, 0x0B);
	mpr121Write(ATO_CFGU, 0xC9);	// USL = (Vdd-0.7)/vdd*256 = 0xC9 @3.3V   mpr121Write(ATO_CFGL, 0x82);	// LSL = 0.65*USL = 0x82 @3.3V
	mpr121Write(ATO_CFGT, 0xB5);*/	// Target = 0.9*USL = 0xB5 @3.3V
}


int8_t wheelKey(void)
{
      switch(readTouch())
      {
		case 0x0001:
			return 1;
		break;
		case 0x0003:
			return 2;
		break;
		case 0x0002:
			return 3;
		break;
		case 0x0006:
			return 4;
		break;
		case 0x0004:
			return 5;
		break;
		case 0x000C:
			return 6;
		break;
		case 0x0008:
			return 7;
		break;
		case 0x0018:
			return 8;
		break;
		case 0x0010:
			return 9;
		break;
		case 0x0030:
			return 10;
		break;
		case 0x0020:
			return 11;
		break;
		case 0x0060:
			return 12;
		break;
		case 0x0040:
			return 13;
		break;
		case 0x00C0:
			return 14;
		break;
		case 0x0080:
			return 15;
		break;
		case 0x0081:
			return 16;
		break;
		default:
			return -1;
		break;		
      }
}


int8_t keypad(void)
{
      switch(readTouch())
      {
		case 0x0001:
			return 1;
		break;
		case 0x0002:
			return 4;
		break;
		case 0x0004:
			return 7;
		break;
		case 0x0008:
			return 11;
		break;
		case 0x0010:
			return 2;
		break;
		case 0x0020:
			return 5;
		break;
		case 0x0040:
			return 8;
		break;
		case 0x0080:
			return 0;
		break;
		case 0x0100:
			return 3;
		break;
		case 0x0200:
			return 6;
		break;
		case 0x0400:
			return 9;
		break;
		case 0x0800:
			return 12;
		break;
		default:
			return -1;
		break;		
      }
}
