/*
https://sites.google.com/a/gclue.jp/fab-zang-docs/ni-yinkiiot/adxl345-i2c
ADXL --- ESP8266
VDD  --- 3.3 V
GND  --- GND
Vs   --- OPEN
CS   --- VDD
SCL  --- D1
SDA  --- D2
SDO  --- GND
INT1 --- OPEN
INT2 --- OPEN
*/
#include <Wire.h>
#include <Arduino.h>
#define DEVICE_ADDR (0x53) // スレーブデバイスのアドレス
byte axis_buff[6];
#define Z_THREAD 10000
// I2Cへの書き込み
void writeI2c(byte register_addr, byte value) {
  Wire.beginTransmission(DEVICE_ADDR);  
  Wire.write(register_addr);         
  Wire.write(value);                 
  Wire.endTransmission();        
}

// I2Cへの読み込み
void readI2c(byte register_addr, int num, byte buffer[]) {
  Wire.beginTransmission(DEVICE_ADDR); 
  Wire.write(register_addr);           
  Wire.endTransmission();         

  Wire.beginTransmission(DEVICE_ADDR); 
  Wire.requestFrom(DEVICE_ADDR, num);   

  int i = 0;
  while(Wire.available())        
  { 
    buffer[i] = Wire.read();   
    i++;
  }
  Wire.endTransmission();         
}

void setup()
{
  Serial.begin(9600); // シリアルの開始デバック用
  Wire.begin();       // I2Cの開始
  
  //Serial.write("init");
  
  // DATA_FORMAT
  writeI2c(0x31, 0x00);
  // POWER_TCL
  writeI2c(0x2d, 0x08);
}

void loop()
{ 
  uint8_t length = 6;
  readI2c(0x32, length, axis_buff); //レジスターアドレス 0x32から6バイト読む
  int x = (((int)axis_buff[1]) << 8) | axis_buff[0];   
  int y = (((int)axis_buff[3]) << 8) | axis_buff[2];
  int z = (((int)axis_buff[5]) << 8) | axis_buff[4];
  // Serial.print("x: ");
  // Serial.print( x );
  // Serial.print(" y: ");
  // Serial.print( y );
  //Serial.print(" z: ");
  Serial.println(z);
  
  // if(Z_THREAD < z){
  //   Serial.println("Flap");
  // }
  // else{
  //   Serial.println("Stop");
  // }
  delay(100);
}

