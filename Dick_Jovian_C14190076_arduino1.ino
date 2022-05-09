#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#define RXpin 8
#define TXpin 9

SoftwareSerial mySerial(RXpin, TXpin);
LiquidCrystal lcd(7,6,5,4,3,2);

long readUltrasonicDistance(int trigPin, int echoPin)
{
  pinMode(trigPin, OUTPUT); 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

int jarak = 0,c = 0,x = 1;
char kar;
String pwd = "",pwd2 = "C1419007605122000";
int pir = 0;
int status = LOW;

void setup() 
{
 Serial.begin(115200); 
 mySerial.begin(2400);
 lcd.begin(16,2);
 lcd.print("Password : ");
}

void loop()
{  
  pir = digitalRead(11);
  if(pir == HIGH)
  {
   if(status == LOW)
   {
    status = HIGH;
   }
  }
  else
  {
   if(status == HIGH)
   {
    status = LOW;
   }
  }
  if(status == HIGH)
  {
   mySerial.print('P');
  }

 jarak = 0.01723 * readUltrasonicDistance(12, 12);
 if(jarak <= 51)
 {
  if(mySerial.available()) 
  {
   kar = mySerial.read();
   if(kar == '*')
   {
    if(pwd == pwd2)
    {
     mySerial.print('C');
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Goodbye!");
     lcd.setCursor(0,1);
     lcd.print("Door is locked."); 
     delay(1500);
     mySerial.print('M');
    }
    lcd.setCursor(0,0);
    lcd.print("Password :      ");
    lcd.setCursor(0,1);
    lcd.print("                ");
    pwd = "";
    c = 0;
    x = 1;
   }
   else if(kar == '#')
   {
    if(pwd == pwd2)
    {
     mySerial.print('O');
     lcd.clear();
     x = 0;
    }          
    else
    {
     mySerial.print('B');
     lcd.setCursor(0,0);
     lcd.print("Password salah!");
     lcd.setCursor(0,1);
     lcd.print("                ");
     delay(500);
      
     lcd.clear();  
     lcd.setCursor(0,0);
     lcd.print("Password : ");
     lcd.setCursor(0,1);
     lcd.print("                ");
     pwd = "";
     c = 0;
    }
   }
   else 
   {
    lcd.setCursor(0,0);
    lcd.print("Password : ");
    lcd.setCursor(c,1);
    c++;
    lcd.write(kar);
    Serial.write(kar);
    pwd += kar;
   }
  }
  else
  {
   if(x == 1)
   {
    lcd.setCursor(0,0);
    lcd.print("Password : ");
   }
   else if(x == 0)
   {
    lcd.setCursor(0,0);
    lcd.print("Welcome, ");
    lcd.setCursor(0,1);
    lcd.print("Mr.Jovian");
   }
  }   
 }
 else
 {
  lcd.clear();   
 }
}