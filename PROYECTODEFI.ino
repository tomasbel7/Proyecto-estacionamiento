#include <Wire.h>

#include <LiquidCrystal_I2C.h>

#include <Servo.h>

#define ledr 7
#define ledv 8

Servo motor1;
Servo motor2;

const int AutosMax = 4;
int NAutos = 0;
int lcdAutos = 4;

const int Trigger1 = 2;
const int Echo1 = 3;
const int Trigger2 = 4;
const int Echo2 = 5;

LiquidCrystal_I2C lcd(0x27,  16, 2);


void setup() {
delay(1000);
  Serial.begin(9600);
  
  motor1.attach(9);
  motor2.attach(10);
  
  motor1.write(0);
  motor2.write(0);
  
  pinMode(Trigger1, OUTPUT);
  pinMode(Echo1, INPUT);
  digitalWrite(Trigger1, LOW);
  pinMode(Trigger2, OUTPUT);
  pinMode(Echo2, INPUT);
  digitalWrite(Trigger2, LOW);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("   Bienvenido   ");
  lcd.setCursor(0, 1);
  lcd.print(lcdAutos);
  lcd.print(" lugares libres");
  
  pinMode(ledr, OUTPUT);
  pinMode(ledv, OUTPUT);
}

void loop() {
  
  long t1; 
  long d1; 
  digitalWrite(Trigger1, HIGH);
  delayMicroseconds(10);          
  digitalWrite(Trigger1, LOW);
  
  t1 = pulseIn(Echo1, HIGH); 
  d1 = t1/59;             
  
  Serial.print("Distancia1: ");
  Serial.print(d1);      
  Serial.print("cm");
  Serial.println();
  delay(100);
  
  long t2; 
  long d2; 
  digitalWrite(Trigger2, HIGH);
  delayMicroseconds(10);          
  digitalWrite(Trigger2, LOW);
  
  t2 = pulseIn(Echo2, HIGH); 
  d2 = t2/59;             
  
  Serial.print("Distancia2: ");
  Serial.print(d2);      
  Serial.print("cm");
  Serial.println();
  delay(100);
  
  Pled();

  if (d1<4 && NAutos<AutosMax) {
  
    arri1();
    
    NAutos++;
    lcdAutos--;
    
    delay(4000);
    
    Actlcd();
    
    aba1();

  } 
  
  if (d2<4 && NAutos>0) {

	arri2();
    
    NAutos--;
    lcdAutos++;
    
    delay(4000);
    
    Actlcd(); 
    
    aba2();

  }
}

void Actlcd() {
	if (NAutos==AutosMax) {
	lcd.clear();
  	lcd.setCursor(0, 0);
  	lcd.print(" No hay lugares ");
    lcd.setCursor(0, 1);
  	lcd.print("  disponibles   ");  
 } else {
	lcd.setCursor(0, 0);
  	lcd.print("   Bienvenido   ");
  	lcd.setCursor(0, 1);
  	lcd.print(lcdAutos);
  	lcd.print(" lugares libres");
 }
}

void Pled() {
  if (NAutos<AutosMax) {
  	digitalWrite(ledv, HIGH);
    digitalWrite(ledr, LOW);
  }
  else {
  	digitalWrite(ledv, LOW);
    digitalWrite(ledr, HIGH);
  }
  	
}

void arri1() {
  for (int pos = 0; pos<=90; pos+=1) {
  	motor1.write(pos);
  	delay(10);
  }
}  

void arri2() {
  for (int pos = 0; pos<=90; pos+=1) {
  	motor2.write(pos);
  	delay(10);
  }
}
  
void aba1() {
  for (int pos = 90; pos>=0; pos-=1) {
  	motor1.write(pos);
  	delay(10);
  }
}
  
void aba2() {
  for (int pos = 90; pos>=0; pos-=1) {
  	motor2.write(pos);
  	delay(10);
  }
}