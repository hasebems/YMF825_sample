/*
 Conditions only for Arduino UNO
   RST_N- Pin9   
   SS   - Pin10
   MOSI - Pin11
   MISO - Pin12
   SCK  - Pin13
 */
#include <SPI.h>
//0 :5V 1:3.3V
#define OUTPUT_power 0

// only for Arduino UNO
void set_ss_pin(int val) {
    if(val ==HIGH) PORTB |= (4);
    else PORTB &= ~(4);
}

// only for Arduino UNO
void set_rst_pin(int val) {
    if(val ==HIGH) PORTB |= (2);
    else PORTB &= ~(2);
}

void if_write(char addr,unsigned char* data,char num){
  char i;
  char snd;
    set_ss_pin(LOW);
    SPI.transfer(addr);
    for(i=0;i<num;i++){
      SPI.transfer(data[i]);    
    }
    set_ss_pin(HIGH);  
}

void if_s_write(char addr,unsigned char data){
  if_write(addr,&data,1);
}

unsigned char if_s_read(char addr){
  
    unsigned char rcv;
    
    set_ss_pin(LOW);    
    SPI.transfer(0x80|addr);
    rcv = SPI.transfer(0x00);
    set_ss_pin(HIGH);  
    return rcv;  
}

void init_825(void) {
   set_rst_pin(LOW);
   delay(1);
   set_rst_pin(HIGH);
   if_s_write( 0x1D, OUTPUT_power );
   if_s_write( 0x02, 0x0E );
   delay(1);
   if_s_write( 0x00, 0x01 );//CLKEN
   if_s_write( 0x01, 0x00 ); //AKRST
   if_s_write( 0x1A, 0xA3 );
   delay(1);
   if_s_write( 0x1A, 0x00 );
   delay(30);
   if_s_write( 0x02, 0x04 );//AP1,AP3
   delay(1);
   if_s_write( 0x02, 0x00 );
   //add
   if_s_write( 0x19, 0xF0 );//MASTER VOL
   if_s_write( 0x1B, 0x3F );//interpolation
   if_s_write( 0x14, 0x00 );//interpolation
   if_s_write( 0x03, 0x01 );//Analog Gain
   
   if_s_write( 0x08, 0xF6 );
   delay(21);
   if_s_write( 0x08, 0x00 );
   if_s_write( 0x09, 0xF8 );
   if_s_write( 0x0A, 0x00 );
   
   if_s_write( 0x17, 0x40 );//MS_S
   if_s_write( 0x18, 0x00 );
}

void set_tone(void){
  unsigned char tone_data[35] ={
    0x81,//header
    //T_ADR 0
    0x01,0x85,
    0x00,0x7F,0xF4,0xBB,0x00,0x10,0x40,
    0x00,0xAF,0xA0,0x0E,0x03,0x10,0x40,
    0x00,0x2F,0xF3,0x9B,0x00,0x20,0x41,
    0x00,0xAF,0xA0,0x0E,0x01,0x10,0x40,
    0x80,0x03,0x81,0x80,
  };
  
   if_s_write( 0x08, 0xF6 );
   delay(1);
   if_s_write( 0x08, 0x00 );
  
   if_write( 0x07, &tone_data[0], 35 );//write to FIFO
}

void set_ch(void){
   if_s_write( 0x0F, 0x30 );// keyon = 0
   if_s_write( 0x10, 0x71 );// chvol
   if_s_write( 0x11, 0x00 );// XVB
   if_s_write( 0x12, 0x08 );// FRAC
   if_s_write( 0x13, 0x00 );// FRAC  
}

void keyon(unsigned char fnumh, unsigned char fnuml){
   if_s_write( 0x0B, 0x00 );//voice num
   if_s_write( 0x0C, 0x54 );//vovol
   if_s_write( 0x0D, fnumh );//fnum
   if_s_write( 0x0E, fnuml );//fnum
   if_s_write( 0x0F, 0x40 );//keyon = 1  
}

void keyoff(void){
   if_s_write( 0x0F, 0x00 );//keyon = 0
}

void setup() {
  // put your setup code here, to run once:
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  set_ss_pin(HIGH);
 
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  SPI.setDataMode(SPI_MODE0);
  SPI.begin();

  init_825();
  set_tone();
  set_ch();
}

void loop() {
  // put your main code here, to run repeatedly:
  keyon(0x14,0x65);
  delay(500);
  keyoff();
  delay(200);
  keyon(0x1c,0x11);
  delay(500);
  keyoff();
  delay(200);
  keyon(0x1c,0x42);
  delay(500);
  keyoff();
  delay(200);
  keyon(0x1c,0x5d);
  delay(500);
  keyoff();
  delay(200);
  keyon(0x24,0x17);
  delay(500);
  keyoff();
  delay(200);
}
