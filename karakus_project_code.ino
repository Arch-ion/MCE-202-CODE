#include <Servo.h>
#include<LiquidCrystal.h>
Servo sg90;
Servo sg902;
LiquidCrystal lcd(13, 6, A1, A2, A3, A4);
const int buton = 4;
const int buzzer = 7;
const int echo = 3;
const int trig = 2;
const int led1 = 8;
const int led2 = 9;
const int led3 = 10;
const int led4 = 11;
const int led5 = 12;
const int pot_pini = A0;
int pot_deger = 0;
int pot_deger_ilk = 0;
int sure = 0;
int mesafe = 0;
int alarm_mesafesi = 0;
int max= 300;
int servo2 = 0;
void setup()
{
    lcd.begin(16, 2);
    sg90.attach(5);
    sg90.write(90);
    sg902.attach(A5);
    sg902.write(90);
    pinMode(buton, INPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    pinMode(led5, OUTPUT);
    pinMode(echo, INPUT);
    pinMode(trig, OUTPUT);
    Serial.begin(9600);
}
void loop()
{
    pot_deger_ilk = analogRead(pot_pini);
    while (1)
    {
        for (int i = 8; i < 13; i++)
        {
            digitalWrite(i, 1);
            delay(50);
            digitalWrite(i, 0);
        }
        pot_deger = analogRead(pot_pini);
        if (pot_deger_ilk > pot_deger + 10 || pot_deger_ilk < pot_deger - 10)
            break;
        
    }
    while (1)
    {
        pot_deger = analogRead(pot_pini);
        pot_deger = map(pot_deger, 100, 900, 1, 5);
        if (pot_deger == 1)
        {
            lcd.setCursor(0,0);          
        lcd.print("Distance Set"); 
        lcd.setCursor(2,1);           
        lcd.print("10 centimeters ");
            alarm_mesafesi = 10;
            digitalWrite(led1, 1);
            digitalWrite(led2, 0);
            digitalWrite(led3, 0);
            digitalWrite(led4, 0);
            digitalWrite(led5, 0);
        }
        else if (pot_deger == 2)
        {
            lcd.setCursor(0,0);          
        lcd.print("Distance Set"); 
        lcd.setCursor(2,1);           
        lcd.print("20 centimeters ");
            alarm_mesafesi = 20;
            digitalWrite(led1, 1);
            digitalWrite(led2, 1);
            digitalWrite(led3, 0);
            digitalWrite(led4, 0);
            digitalWrite(led5, 0);
        }
        else if (pot_deger == 3)
        {
            lcd.setCursor(0,0);          
        lcd.print("Distance Set"); 
        lcd.setCursor(2,1);           
        lcd.print("30 centimeters ");
            alarm_mesafesi = 30;
            digitalWrite(led1, 1);
            digitalWrite(led2, 1);
            digitalWrite(led3, 1);
            digitalWrite(led4, 0);
            digitalWrite(led5, 0);
        }
        else if (pot_deger == 4)
        {   
            lcd.setCursor(0,0);          
        lcd.print("Distance Set"); 
        lcd.setCursor(2,1);           
        lcd.print("40 centimeters ");
            alarm_mesafesi = 40;
            digitalWrite(led1, 1);
            digitalWrite(led2, 1);
            digitalWrite(led3, 1);
            digitalWrite(led4, 1);
            digitalWrite(led5, 0);
        }
        else if (pot_deger == 5)
        {
            lcd.setCursor(0,0);          
        lcd.print("Distance Set"); 
        lcd.setCursor(2,1);           
        lcd.print("50 centimeters ");
            alarm_mesafesi = 50;
            digitalWrite(led1, 1);
            digitalWrite(led2, 1);
            digitalWrite(led3, 1);
            digitalWrite(led4, 1);
            digitalWrite(led5, 1);
        }
        if (digitalRead(buton) == 1)
           break; 
    }
    for (int pos = 0; pos <= 170; pos++)
    {
        
        sg90.write(pos);        
        delay(15);
        mesafe == mesafe_olc();
        Serial.println(pos);
        if (mesafe <= alarm_mesafesi)
          {      
            lcd.clear();
              lcd.setCursor(0,0);          
            lcd.print("Object Detected"); 
            lcd.setCursor(2,1);           
              lcd.print(pos);
              lcd.print("  degree");
            digitalWrite(led1, 1);
            digitalWrite(led2, 1);
            digitalWrite(led3, 1);
            digitalWrite(led4, 1);
            digitalWrite(led5, 1);
            digitalWrite(buzzer, 1);
            break;
        }
        if (digitalRead(buton) == 1)
        {
              lcd.clear();
              lcd.setCursor(0,0);          
              lcd.print("Restarting"); 
              lcd.setCursor(2,1);           
              lcd.print("Progress");
            digitalWrite(led1, 0);
            digitalWrite(led2, 0);
            digitalWrite(led3, 0);
            digitalWrite(led4, 0);
            digitalWrite(led5, 0);
            digitalWrite(buzzer, 0);
        }
    }
    for (int pos = 170; pos >= 0; pos--)
    {
        Serial.println(pos);
        sg90.write(pos);
        delay(15);      
        mesafe == mesafe_olc();
        if (mesafe <= alarm_mesafesi)
        {             
              lcd.clear();
              lcd.setCursor(0,0);          
            lcd.print("Object Detected"); 
            lcd.setCursor(2,1);           
              lcd.print(pos);
              lcd.print("    degree");
            digitalWrite(led1, 1);
            digitalWrite(led2, 1);
            digitalWrite(led3, 1);
            digitalWrite(led4, 1);
            digitalWrite(led5, 1);
            digitalWrite(buzzer, 1);
            break;
        }
        if (digitalRead(buton) == 1)
        {
            digitalWrite(led1, 0);
            digitalWrite(led2, 0);
            digitalWrite(led3, 0);
            digitalWrite(led4, 0);
            digitalWrite(led5, 0);
            digitalWrite(buzzer, 0);
        }
    }
}
int mesafe_olc()
{    
    digitalWrite(trig, HIGH);
    delay(10);
    digitalWrite(trig, LOW);
    sure = pulseIn(echo, HIGH, 70*max);
  if(sure==0)
  {
    mesafe = max;
  }
  else{
    mesafe = sure*0.0343/2;
    if (mesafe>max)
    {
      mesafe=max;
    }    
    return mesafe;
    Serial.print("mesafe: ");
    Serial.println(mesafe);
}
}
