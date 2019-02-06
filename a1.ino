
#include <Adafruit_APDS9960_Particle.h>

Adafruit_APDS9960 apds;

//motor 1
int ain1 = D7;
int ain2 = D6;

//motor 2
int bin1 = D3;
int bin2 = D4;

int sensorPin = A0;

int analogVal = 0; //setting value to store info from photoresistor



void setup() {
    
  Serial.begin(9600);

  if(!apds.begin()){
    Serial.println("Helppppp we've failed to initialize! Please check my wiring :(");
  }
  else Serial.println("Device initialized!");
  
  apds.enableProximity(true);
  apds.enableGesture(true);
  
  pinMode (ain1, OUTPUT);
  pinMode (ain2, OUTPUT);
  pinMode (bin1, OUTPUT);
  pinMode (bin2, OUTPUT);
  pinMode (D2, OUTPUT); //slp

  
  delay(500);
}

void loop() {
  analogVal = analogRead(sensorPin);
  analogVal = 4095 - analogVal;
  Serial.printf("\nA: %d\t", analogVal);
  

  int speed = (255 * analogVal)/4095;
  Serial.printf("AINVERT: %d\t", speed);
  
  analogWrite(D2, speed); //connected to DRV8833's SLP
  handleGesture();
}


void handleGesture() {
    
  uint8_t gesture = apds.readGesture();
  
  if (gesture == APDS9960_DOWN) {
    Serial.println("v");
    digitalWrite(bin1, HIGH);
    digitalWrite(bin2, LOW);
  }

  if (gesture == APDS9960_UP) {
    Serial.println("^");
    digitalWrite(bin1, LOW);
    digitalWrite(bin2, HIGH);
  }
    
  if (gesture == APDS9960_LEFT) {
    Serial.println("<");
    digitalWrite(ain1, LOW);
    digitalWrite(ain2, HIGH);
  }
    
  if(gesture == APDS9960_RIGHT) {
    Serial.println(">");
    digitalWrite(ain1, HIGH);
    digitalWrite(ain2, LOW);
  }
}
