unsigned long int milli_time;
float voltage;
void setup(){
  Serial.begin(9600);
  Serial.println("CLEARDATA");
  Serial.println("LABEL,Computer Time,Time(Milli Sec.),Volt");
  
}
void loop(){
  milli_time=millis();
  voltage=5.0*analogRead(A0)/1024.0;
  Serial.print("DATA,TIME,");
  Serial.print(milli_time);
  Serial.print(",");
  Serial.println(voltage);

  delay(100);
  
}
