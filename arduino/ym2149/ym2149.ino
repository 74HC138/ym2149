#include <TimerOne.h>

int clockPin  = 11;
//int BC1       = 12;
//int BDir      = 13;
int reset     = 10;

byte inBuffer[16];
int bufferCount;

void setup() {
  Serial.begin(250000);
  PORTF = 0;                  //for data
  DDRF = 0;
  //pinMode(BC1, OUTPUT);
  //pinMode(BDir, OUTPUT);
  pinMode(reset, OUTPUT);
  digitalWrite(reset, HIGH);
  DDRA = 255;                 //for BDir and BC1
  initClock();
  resetIC();
  delay(5);
  for (byte i=0; i<16; i++) {
    send_data(i, 0);          //clearing all registers
  }
}

void loop() {
  if (Serial.available()) {
    inBuffer[bufferCount] = Serial.read();  //adding serial input to buffer
    bufferCount++;
  }
  if (bufferCount >= 16) {                  //when buffer is full dump to chip
    for (byte i = 0; i < 16; i++) {
      send_data(i, inBuffer[i]);
    }
    bufferCount = 0;
  }
}

void initClock() {               // chip clock init
  pinMode(clockPin, OUTPUT);
  TCCR1A = ( (1 << COM1A0));
  TCCR1B = ((1 << WGM12) | (1 << CS10));
  TIMSK1 = 0;
  OCR1A = 3;                     //change this value for different frequencies
  //0 = 8mhz
  //1 = 4mhz
  //3 = 2mhz
  //7 = 1mhz
}
void resetIC() {                //reset the chip
  digitalWrite(reset, LOW);     //reset line is active low
  delay(1);
  digitalWrite(reset, HIGH);
}
void set_data_out(void) {
  DDRF = 0xff;
}
void set_data_in(void) {
  DDRF = 0x00;
}
void set_address(char addr) {
  set_data_out();
  setAdressMode();
  PORTF = addr;
  delayMicroseconds(1);
  setInactive();
  delayMicroseconds(1);
}
void set_data(char data) {
  set_data_out();
  PORTF = data;
  setWriteMode();
  delayMicroseconds(1);
  setInactive();
  delayMicroseconds(1);
}
char get_data(void) {
  char data;
  set_data_in();
  setReadMode();
  delayMicroseconds(1);
  data = PINF;
  setInactive();
  delayMicroseconds(1);
  return data;
}
void send_data(char addr, char data) {
  set_address(addr);
  set_data(data);
}
char read_data(char addr) {
  set_address(addr);
  return get_data();
}
void setInactive() {
  PORTA = 0;
  //digitalWrite(BDir, LOW);      //changed to direct port because of speed problems
  //digitalWrite(BC1, LOW);
}
void setWriteMode() {
  PORTA = 2;
  //digitalWrite(BDir, HIGH);
  //digitalWrite(BC1, LOW);
}
void setReadMode() {
  PORTA = 1;
  //digitalWrite(BDir, LOW);
  //digitalWrite(BC1, HIGH);
}
void setAdressMode() {
  PORTA = 3;
  //digitalWrite(BDir, HIGH);
  //digitalWrite(BC1, HIGH);
}
