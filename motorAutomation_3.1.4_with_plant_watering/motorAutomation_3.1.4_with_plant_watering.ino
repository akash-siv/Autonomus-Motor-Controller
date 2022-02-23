
#define relayoff HIGH
#define relayon LOW
#define sumplevel 2
#define tankhigh 7 // green white color cable
#define tanklow 6 // orange color cable and green common ground
#define motor_1 5
#define motor_2 4
#define plantrelay 8
#include <RTClib.h>
#include <Wire.h>
RTC_DS1307 rtc;
int var_motor_1 = 0;
int var_motor_2 = 0;

    

void setup(){
  pinMode(sumplevel, INPUT_PULLUP); 
  pinMode(tankhigh, INPUT_PULLUP);
  pinMode(tanklow, INPUT_PULLUP);
  pinMode(motor_1, OUTPUT);
  pinMode(motor_2, OUTPUT);
  pinMode(plantrelay, OUTPUT);
  digitalWrite(motor_2, relayoff);
  digitalWrite(motor_1, relayoff);
  digitalWrite(plantrelay, relayoff);

Serial.begin(9600);
Wire.begin();
   rtc.begin();
   if (! rtc.isrunning())
  {
    Serial.println("RTC is NOT running!");
}

//rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
 
  }


void loop(){
     
//motor_2 ON when sump level is high
  if ((digitalRead(tanklow) == LOW) && (digitalRead(sumplevel) == HIGH)){
    delay(1000);
    if ((digitalRead(tanklow) == LOW) && (digitalRead(sumplevel) == HIGH)){
    digitalWrite(motor_2, relayon);
    digitalWrite(motor_1, relayoff);
    var_motor_2 = 1;
    var_motor_1 = 0;}}
    
//motor_2 & motor_1 OFF when tank fills
    if (digitalRead(tankhigh) == HIGH){
    delay(1000);
    if (digitalRead(tankhigh) == HIGH){  
    digitalWrite(motor_2, relayoff);
    digitalWrite(motor_1, relayoff);
    var_motor_1 = 0;
    var_motor_2 = 0;}}

////motor_1 is OFF when sump is high
//    if (digitalRead(sumplevel) == HIGH){
//    delay(1000);
//    if (digitalRead(sumplevel) == HIGH){
//    digitalWrite(motor_1, relayoff);
//    var_motor_1 = 0;
//    }}
    

//motor_2 OFF when sumplevel is low & motor_1 ON   
    if ((digitalRead(sumplevel) == LOW) && (digitalRead(tanklow) == LOW)){
    delay(1000);
    if ((digitalRead(sumplevel) == LOW) && (digitalRead(tanklow) == LOW)){
    digitalWrite(motor_2, relayoff);
    var_motor_2 = 0;
    delay(7000);
    digitalWrite(motor_1, relayon);
    var_motor_1 = 1;
    }}


//motor_1 is OFF when motor_2 is ON and viceversa
   if (var_motor_2 == 1){
    digitalWrite(motor_1, relayoff);}
   if (var_motor_1 == 1){
    digitalWrite(motor_2, relayoff);}  


  DateTime now = rtc.now();
  Serial.print(now.year(), DEC);
  Serial.print("/");
  Serial.print(now.month(), DEC);
  Serial.print("/");
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(now.hour(), DEC);
  Serial.print(":");
  Serial.print(now.minute(), DEC);
  Serial.print(":");
  Serial.print(now.second(), DEC);
  Serial.print(")");
  Serial.println();

  Serial.println( );
  delay(1000);

  
//motor_1 and motor_2 ON and OFF by RTC for 7 secs
if ((var_motor_1 == 0) && (var_motor_2 == 0)){ 

  if((now.hour()== 05 & now.minute() == 00 ) || (now.hour()== 17 & now.minute() == 00 ))  //time should be changed based on the power fluctuation
{
 digitalWrite(motor_1, relayon);
 Serial.print("motor_1 ON by RTC");
 delay(7000);//run the motor for 7 secs
 digitalWrite(motor_1, relayoff);
 Serial.print("motor_1 OFF by RTC");
 
 
 delay(60000);//run the motor for 60 secs

  
  if (digitalRead(sumplevel) == HIGH){
  delay(1000);
  if (digitalRead(sumplevel) == HIGH){
  digitalWrite(motor_2, relayon);
  Serial.print("motor_2 ON by RTC");
  delay(7000);//run the motor for 7 secs
  digitalWrite(motor_2, relayoff);
  Serial.print("motor_2 OFF by RTC");
  }}
}}

//Turn on the plant watering at 5 clock at morning and 6 clock in evening.

 if((now.hour()== 06 & now.minute() == 00 ) || (now.hour()== 18 & now.minute() == 30 ))  //time should be changed based on the power fluctuation
{
    digitalWrite(plantrelay, relayon); // turn on irrigation.
  
           for(int i=0;i<=3600;i++){ //how much time you want to irrigate.
           delay(1000);}
           
    digitalWrite(plantrelay, relayoff);
  
  }


}
