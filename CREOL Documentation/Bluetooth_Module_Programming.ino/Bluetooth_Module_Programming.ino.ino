/*
 Name:    Bluetooth.ino
 Created: 2016/7/30 13:26:47
 Author:  Fing
HC-06  arduino
VCC---> 5V
GND--->GND
TXD--->D2
RXD--->D3
*/
#include "SoftwareSerial.h"
// Using software serial port, can speak digital port analog into serial port
SoftwareSerial BT(2, 3);  //New object, receive foot 2, send foot 3
char val;  //Store received variables
int baud = 38400;


void setup() {
   pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);   //Serial Port Connection with Computer
  Serial.println("BT Module is ready!");
  BT.begin(38400);  //set baud rate
 delay(3000); //delay 3 seconds

  BT.print("at\r\n"); //Send AT.
  delay(500); //delay 500 seconds

  Serial.println("\nDebug Information: ");
  
  BT.print("AT+VERSION\r\n"); 
  delay(500); //delay 500 seconds
  BT.print("AT+UART\r\n");
  delay(500); //delay 500 seconds
  BT.print("AT+PSWD\r\n");
  delay(500); //delay 500 seconds
  BT.print("AT+ADDR?\r\n");
  delay(500); //delay 500 seconds

  while (BT.available()) {
    Serial.print(BT.read());    
  }

  
  Serial.println("\nSetting data: ");
  
  //Set information
  BT.print("AT+UART=230400,0,0\r\n");
  delay(500); //delay 500 seconds
  BT.print("AT+NAME=SpectraMiniCCD\r\n");
  delay(500); //delay 500 seconds

  while (BT.available()) {
    Serial.print(BT.read());    
  }
  
  Serial.println("\nUpdated Data: ");
  
  BT.print("AT+UART\r\n");
  delay(500); //delay 500 seconds
  
}
 
void loop() {
  //If the serial port receives the data, it outputs it to the Bluetooth serial port.
  if (Serial.available()) {
    val = Serial.read();
    BT.print(val);
  }
 
  //If the Bluetooth module data is received, it is output to the screen.
  if (BT.available()) {
    val = BT.read();
    Serial.print(val);    
  }
}
