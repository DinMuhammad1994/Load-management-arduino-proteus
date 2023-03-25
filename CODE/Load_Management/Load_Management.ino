
// Link https://www.microcontroller-project.com/acs712-current-sensor-with-arduino.html
#include <LiquidCrystal.h> //library for LCD
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

const int sensorIn = A0;
int m;// initialise variable m
float n;//initialise variable n
int mVperAmp = 600; // use 100 for 20A Module and 66 for 30A Module


double Power = 0;
double Voltage = 0;
double Current =0;
double VRMS = 0;
double AmpsRMS = 0;
int relay1= 6;
int relay2= 7;

void setup(){ 
 Serial.begin(9600);
 pinMode(A0,INPUT); // set pin a0 as input pin
  pinMode(A1,INPUT); // set pin a0 as input pin
 pinMode(relay1, OUTPUT);
 digitalWrite(relay1, LOW);
 pinMode(relay2, OUTPUT);
 digitalWrite(relay2, LOW);
}

void loop(){
Voltage = getVPP();
VRMS = (Voltage/2.0)*0.707; 
AmpsRMS = (VRMS * 1000)/mVperAmp;
 Current= AmpsRMS;
 m=analogRead(A1);// read analog values from pin A1 across capacitor
   n=(m* .304177);// converts analog value(x) into input ac supply value using this formula ( explained in woeking section)
  Power = (n*Current);
 Serial.print(Current);
 menu();

 if (Current > 6)
 {
   digitalWrite(relay1, HIGH);
  }
 else
 {
   digitalWrite(relay1, LOW);
  }
  if (Current > 12)
 {
   digitalWrite(relay2, HIGH);
  }
 else
 {
   digitalWrite(relay2, LOW);
  }
  delay(500);
}
 

void menu()
{
  lcd.begin(20,4);
  lcd.setCursor(0,0);
  lcd.print("---LOAD MANAGEMENT--");
  lcd.setCursor(2,1);
  lcd.print("Current=");
  lcd.setCursor(11,1);
  lcd.print(AmpsRMS,3);
  lcd.setCursor(16,1);
  lcd.print("A");
  lcd.setCursor(2,2);
  lcd.print("Voltage = ");
  lcd.setCursor(11,2);
   lcd.print(n,3);
   lcd.setCursor(18,2);
   lcd.print("V");
   lcd.setCursor(2,3);
  lcd.print("Power = ");
  lcd.setCursor(11,3);
   lcd.print(Power,3);
   lcd.setCursor(19,3);
   lcd.print("W");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("---LOAD MANAGEMENT--");

  lcd.setCursor(0,1);
  lcd.print("Transformer 01 = ON");
  
   if (Current> 6)
 {
   lcd.setCursor(0,2);
     lcd.print("Transformer 02 = ON");
  }
  
 else
 {
   lcd.setCursor(0,2);
    lcd.print("Transformer 02 = OFF");
  }
  if (Current> 12)
 {
   lcd.setCursor(0,3);
     lcd.print("Transformer 03 = ON");
  }
 else
 {
   lcd.setCursor(0,3);
    lcd.print("Transformer 03 = OFF");
  }
  }
  float getVPP()
{
  float result;
  
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(sensorIn);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the maximum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
 }

