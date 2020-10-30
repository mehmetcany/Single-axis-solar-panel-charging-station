#include <Servo.h>
#include <LiquidCrystal.h>
Servo YATAY;


int pos1 = 90; // servo1 başlangıç konumu


const int LDR_SOL = A0;
const int LDR_SAG = A1; 



int SOL = 0; 
int SAG = 0; 


LiquidCrystal lcd(7, 8, 9, 10, 11, 12); 
int analogInput = A3; 
float vout = 0.0;
float vin = 0.0;
float R1 = 100000.0; // 100K Direnç 
float R2 = 10000.0; //  10K Direnç
int value = 0;
void setup(){
   pinMode(analogInput, INPUT);
   lcd.begin(16, 2);
   lcd.print(" PANEL GERILIMI"); // LCD ekranın ilk satırına yazdırılacak yazı
   YATAY.attach(6); //alt motor
   Serial.begin(9600);

}
void loop(){
  
   value = analogRead(analogInput);
   vout = (value * 3.0) / 1024.0; 
   vin = vout / (R2/(R1+R2)); 
   if (vin<0.09) {
   vin=0.0;
} 
lcd.setCursor(0, 1);
lcd.print("     ");
lcd.print(vin); // Bulduğumuz vin değerini LCD ekranın ikinci satırına yazdırıyoruz
lcd.print(" V ");
SOL = analogRead(LDR_SOL);
SAG = analogRead(LDR_SAG);


Serial.print("Panel Gerilimi = ");
Serial.println(vin);
Serial.print("Panelin Donus Acisi = ");
Serial.println(pos1);
delay(50);
//ldr analog (0-1024) bilgileri okur. 
//LDR bir ucu - de ise 
//bu değerler ışık şiddeti ile doğru orantılıdır.
//ışık artarsa değer de artar.

 if (SOL > ( SAG  ))
 {
 if (pos1 > 0)
 pos1-=1;
 YATAY.write(pos1);
 }
 if (SAG > ( SOL  ))
 {
 if ( pos1 < 180 )
 pos1++;
 YATAY.write(pos1);
 } 
}
