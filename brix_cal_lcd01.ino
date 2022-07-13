/*
Pineapple sugar content measurement V0.1
*/
#include "SparkFun_AS7265X.h" //Click here to get the library: http://librarymanager/All#SparkFun_AS7265X
AS7265X sensor; //เป็นการตัง้ชื่อ alias name สมารถตั้งชื่ออื่นๆ ได้เช่น spectro ชื่อจะถูกใช้ในการเรียกใช้ฟังก์ชันเช่น spectro.begin() specttro.getCalibratedA() เป็นต้น

#include <Wire.h>
#include <math.h>
#include <LiquidCrystal_I2C.h>
//ประกาศตัวแปรที่เก็บค่าการสะท้อนของแต่ละช่องของ AS7265X  
float A=0; float B=0; float E=0; float F=0; float G=0; float H=0; float R=0; float U=0; float K=0; float L=0;
float A1=0; float Ba=0; float E1=0; float F1=0; float G1=0; float H1=0; float R1=0; float U1=0; float K1=0; float L1=0;
//ประกาศตัวแปรสำหรับเก็บค่าความหวานและแทนช่องสัญญาณลงในสมการ
float brix; float C1; float C2;float C5; float C6; float C7; float C8; float C9; float C14; float C17; float C18;
LiquidCrystal_I2C lcd(0x27, 16, 2); //กำหนด address และขนาดของ LCD
const int buttonPin = D0; //กำหนดขาต่อกับสวิตซ์
int buttonState = 0;         // กำหนดค่าเริ่มต้นของสถานะสวิตซ์(ยังไม่กดเป็น 0)

void setup()
{
  //ตั้งค่าเริ่มต้นการสื่อสารผ่านพอร์ตอนุกรม
  Serial.begin(115200); 
  delay(1000);
  pinMode(buttonPin, INPUT);//กำหนดให้ขา D3 เป็นอินพุท
    if (sensor.begin() == false)
    {
    Serial.println("Sensor does not appear to be connected. Please check wiring. Freezing...");
    while (1)
      ;
    }
  Serial.println("Start");
  sensor.disableIndicator(); //Turn off the blue status LED on AS7265X
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0); // กำหนดตำแหน่งเคอร์เซอร์ที่ ตำแหน่งที่ 0 บรรทัดที่ 0
  lcd.print("Pineapple v 0.1");
  lcd.setCursor(0, 1); // กำหนดตำแหน่งเคอร์เซอร์ที่ ตำแหน่งที่ 0 บรรทัดที่ 1
  lcd.print("Point to Ref.");
  
}//end set up

void loop()
{
  //buttonState = digitalRead(buttonPin);//อ่านค่าสวิตซ์ ถ้ากดจะเป็น 1 ปล่อยเป็น 0
  // กดอ่านค่าอ้างอิง
  while (digitalRead(buttonPin) == LOW)
  {
    delay(500);
  } 
 
    Serial.println("Reading the reference...");
    lcd.clear();
    lcd.setCursor(0, 0); // กำหนดตำแหน่งเคอร์เซอร์ที่ แถวที่ 0 บรรทัดที่ 0
    lcd.print("Reading");
    A=0; B=0; E=0; F=0; G=0; H=0; R=0;U=0; K=0;L=0;
    for (int i = 0; i <= 9; i++) {
      sensor.takeMeasurementsWithBulb(); //This is a hard wait while all 18 channels are measured
      A=A+sensor.getCalibratedA();
      B=B+sensor.getCalibratedB();
      E=E+sensor.getCalibratedE();
      F=F+sensor.getCalibratedF();
      G=G+sensor.getCalibratedG();
      H=H+sensor.getCalibratedH();
      R=R+sensor.getCalibratedR();
      U=U+sensor.getCalibratedU();
      K=K+sensor.getCalibratedK();
      L=L+sensor.getCalibratedL();
    }//end for


    
    Serial.println("Point the sensor to  the Pineapple and press...");
    lcd.clear();
    lcd.setCursor(0, 0); // กำหนดตำแหน่งเคอร์เซอร์ที่ ตัวที่ 0 บรรทัดที่ 0
    lcd.print("Point to");
    lcd.setCursor(0, 1); // กำหนดตำแหน่งเคอร์เซอร์ที่ ตัวที่ 0 บรรทัดที่ 1
    lcd.print("Pineapple");
    
// กดอ่านค่าสับปะรด
  //buttonState = digitalRead(buttonPin);//อ่านค่าสวิตซ์ ถ้ากดจะเป็น 1 ปล่อยเป็น 0
  while (digitalRead(buttonPin) == LOW)
  {
    delay(500);
  } 
 

    lcd.clear();
    lcd.setCursor(0, 0); // กำหนดตำแหน่งเคอร์เซอร์ที่ แถวที่ 0 บรรทัดที่ 0
    lcd.print("Reading");
    Serial.read(); //Throw away the user's button
    Serial.println("Reading the Pine apple...");
    A1=0; Ba=0; E1=0; F1=0; G1=0; H1=0; R1=0;U1=0; K1=0;L1=0;
    for (int i = 0; i <= 9; i++) {
      sensor.takeMeasurementsWithBulb(); //This is a hard wait while all 18 channels are measured
      A1=A1+sensor.getCalibratedA();
      Ba=Ba+sensor.getCalibratedB();
      E1=E1+sensor.getCalibratedE();
      F1=F1+sensor.getCalibratedF();
      G1=G1+sensor.getCalibratedG();
      H1=H1+sensor.getCalibratedH();
      R1=R1+sensor.getCalibratedR();
      U1=U1+sensor.getCalibratedU();
      K1=K1+sensor.getCalibratedK();
      L1=L1+sensor.getCalibratedL();
    }//end for
  
  C1=log10(A/A1); C2=log10(B/Ba); C5=log(E/E1); C6=log10(F/F1); C7=log10(G/G1);
  C8=log10(H/H1); C9=log10(R/R1); C14=log10(U/U1); C17=log10(K/K1); C18=log10(L/L1);
  //Serial.print(C4);
  //Serial.println();
  brix =-11.861*C1+7.681*C2+11.219*C5-13.314*C6-8.630*C7+5.231*C8-7.101*C9+15.052*C14+11.988*C17-9.761*C18+19.578;
  lcd.clear();
  lcd.setCursor(0, 0); // กำหนดตำแหน่งเคอร์เซอร์ที่ ตำแหน่งที่ 0 บรรทัดที่ 0
  lcd.print("Brix = ");
  lcd.setCursor(1, 0); // กำหนดตำแหน่งเคอร์เซอร์ที่ ตำแหน่งที่ 0 บรรทัดที่ 1
  lcd.print(brix,1); lcd.print("brix(%)");
  Serial.print(brix);
  Serial.println();
  lcd.clear();
  lcd.setCursor(0, 0); // กำหนดตำแหน่งเคอร์เซอร์ที่ ตำแหน่งที่ 0 บรรทัดที่ 0
  lcd.print("Brix=");
  lcd.print(brix,1);
  lcd.setCursor(0, 1); // กำหนดตำแหน่งเคอร์เซอร์ที่ ตำแหน่งที่ 0 บรรทัดที่ 1
  lcd.print("Point to ref.");   
}// end  loop
