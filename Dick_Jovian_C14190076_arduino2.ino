#include <SoftwareSerial.h>
#include <Keypad.h>
#include <Servo.h>
#define RXpin 11
#define TXpin 12

SoftwareSerial mySerial(RXpin, TXpin);

const int ROW = 4;
const int COL = 4;
char key[ROW][COL] = 
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPin[ROW]= {9,8,7,6};
byte colPin[COL]= {5,4,3,2};
Keypad keypad = Keypad(makeKeymap(key),rowPin,colPin,ROW,COL);

Servo myServo;
bool check1 = false;
bool check2 = false;
bool check3 = false;
int buzzer = 10;
long timer = 60000;//60detik

void setup()
{
 Serial.begin(115200);
 mySerial.begin(2400);
 myServo.attach(13);
}

void loop()
{
 float sensor_suhu = analogRead(A0);
 float suhu = ((((sensor_suhu / 1024)*5)-0.5)*100)+0.23;
 int asap = analogRead(A2);
  
 char pwd = keypad.getKey();
 if (pwd)
 {
  Serial.print(pwd);
  mySerial.write(pwd);
 }
  
 char read = mySerial.read();
 if(read == 'O')
 {
  myServo.write(-90);
  check2 = true;
 }
 else if(read == 'C')
 {
  myServo.write(90);
  check2 = false;
 }
 else if(read == 'B')
 {
  check1 = true; 
 }
 else if(read == 'M')
 {
  check1 = false; 
 }
 else if(read == 'P')
 {
  Serial.println("PIR is on");
  Serial.print("Suhu : ");
  Serial.println(suhu);
  Serial.print("Asap : ");
  Serial.println(asap);
 }
 
 if(suhu > 100 || asap > 200)
 {
  check3 = true;
 }
 else if(suhu <= 50 && asap < 200)
 {
  check3 = false;
 }
 
 if(check1 == false && check3 == true)
 {
  tone(buzzer, 1000);
 }
 else if(check1 == false && check3 == false)
 {
  noTone(buzzer);
 } 
 else if(check2 == true && check3 == true)
 {
  tone(buzzer, 1000);
 }
 else if(check2 == true && check3 == false)
 {
  noTone(buzzer);
 } 
 
 if(check2 == true)
 {
  unsigned long start = millis();
  if (start > timer)
  {
   tone(buzzer, 1000);
  }
 }
 else if(check2 == false && check1 == false && check3 == false)
 {
  noTone(buzzer);
 }  
 else if(check2 == false && check1 == true )
 {
  tone(buzzer, 1000);
 }
}