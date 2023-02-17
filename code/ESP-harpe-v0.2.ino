#include <ESP8266WiFi.h>

int counter = 0;
const int sleepTimeS = 600; //  Seconds for DeepSleep

const int MOSpin = D6;
const int RAINpin = D1;
const int LEDpin = D2;

void setup() {

  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();  
 
  Serial.begin(115200);
  Serial.println("\n\n\n");
  Serial.println("Booting.........................\n");
    
  pinMode(MOSpin, OUTPUT);
  pinMode(RAINpin, INPUT);
  pinMode(LEDpin, OUTPUT);

  digitalWrite(MOSpin, LOW);  
  Serial.println("High Voltage OFF");
  digitalWrite(LEDpin, LOW);
  Serial.println("LED OFF");
  Serial.println("\nSetup done - entering Loop...\n");



}

void loop() {

  int RAIN = digitalRead(RAINpin);
  int LIGHT = analogRead(A0); 


  if ((LIGHT == 1024) && (RAIN == HIGH)){
   digitalWrite(MOSpin, HIGH);  
   Serial.print("LIGHT = ");
   Serial.print(LIGHT);
   Serial.print(" - RAIN = ");
   Serial.print(RAIN);
   Serial.println(" -> MOSpin set HIGH -> High Voltage ON");    
   digitalWrite(MOSpin, HIGH); 
   Serial.println("Blinking LED");
   digitalWrite(LEDpin, HIGH);   
   delay(500);
   digitalWrite(MOSpin, LOW);
   digitalWrite(LEDpin, LOW);  
  } else {
   digitalWrite(MOSpin, LOW);  
   digitalWrite(LEDpin, LOW);
   Serial.print("LIGHT = ");
   Serial.print(LIGHT);
   Serial.print(" - RAIN = ");
   Serial.print(RAIN);
   Serial.println(" > MOSpin set LOW -> High Voltage OFF");      
   Serial.print("Entering DeepSleep for ");
   Serial.print(sleepTimeS);
   Serial.println(" seconds...\n");
   ESP.deepSleep(sleepTimeS*1e6, WAKE_RFCAL);  
  }

 
  Serial.println("End of Loop - Waiting 3.5sec ...\n\n");   
  
  delay(3500);

}
