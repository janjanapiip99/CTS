//A5= SCL
//A4= SDA
#include<Wire.h>
const int MPU=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
unsigned long int milli_time;
float voltage;
int fsrAnalogPin = 1; // konek ke A1
int LEDpin = 11;      // LED ke pin 11 PWM
int fsrReading;      // baca analog FSR resistor divider
int LEDbrightness;


void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);
  Serial.begin(9600);
  pinMode(LEDpin, OUTPUT);
  Serial.println("CLEARDATA");
  Serial.println("LABEL,Computer Time,Time(Milli Sec.),Gyroscope,FSR,Flex");
 
}
void loop(){
  milli_time=millis();
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true); 
  GyX=Wire.read()<<8|Wire.read();  
  GyY=Wire.read()<<8|Wire.read();  
  GyZ=Wire.read()<<8|Wire.read(); 
  voltage=5.0*analogRead(A0)/1024.0;  //baca tegangan flex
  Serial.print("DATA,TIME,");
  Serial.print(milli_time);
  Serial.print(",");
  Serial.print("Gyroscope: ");
  Serial.print("X = "); Serial.print(GyX);
  Serial.print(" | Y = "); Serial.print(GyY);
  Serial.print(" | Z = "); Serial.println(GyZ);
  Serial.print(",");
  fsrReading = analogRead(fsrAnalogPin);
  Serial.print("Nilai FSR = ");
  Serial.println(fsrReading);
  Serial.print(",");
  Serial.println(voltage);
  Serial.println(" ");
  LEDbrightness = map(fsrReading, 0, 1023, 0, 255); // mengatur kecerahan LED berdasarkan tekanan FSR
  analogWrite(LEDpin, LEDbrightness);
  delay(500);
  
}
