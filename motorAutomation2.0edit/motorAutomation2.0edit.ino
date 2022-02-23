
#include <dht.h>
dht DHT;

#define relayoff HIGH
#define relayon LOW
#define up HIGH
#define down LOW 
#define input INPUT_PULLUP
#define output OUTPUT
#define fd 2
#define fu 3
#define sump 4
#define motor 5
#define exhaust 7
#define DHT11_PIN A1



float hum;  //Stores humidity value
float temp; //Stores temperature value
const long interval = 21600000; // 1 hour = 3600000 millisec
unsigned long previousMillis = 0;

void setup(){
  pinMode(fd, input); 
  pinMode(fu, input);
  pinMode(sump, input);
  pinMode(motor, output);
  pinMode(exhaust, output);
  digitalWrite(motor, relayoff);
  digitalWrite(exhaust, relayoff);
  
  }

void(* resetFunc) (void) = 0; //declare reset function @ address 0


void loop(){
     
// for motor control
  if ((digitalRead(fd) == down) && (digitalRead(sump) == down)){
    delay(1000);
    if ((digitalRead(fd) == down) && (digitalRead(sump) == down)){// Check whether my tank is less
    digitalWrite(motor, relayon);}}
    

    if (digitalRead(fu) == up){
    delay(1000);
    if (digitalRead(fu) == up){  
    digitalWrite(motor, relayoff);}}

    
  if (digitalRead(sump) == up){
    delay(1000);
    if (digitalRead(sump) == up){
    digitalWrite(motor, relayoff);
    }}
    
//For temperature and humidity measurement 
    int chk = DHT.read11(DHT11_PIN);
    //Read data and store it to variables hum and temp
    hum = DHT.humidity;
    temp= DHT.temperature;

    if (temp > 38){// yet to to changed by the surrounding
      delay(10000);
      if (temp > 38){
      digitalWrite(exhaust, relayon);
    }}
    else{
      digitalWrite(exhaust, relayoff);}

      
//Reseting Function
  
   unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
        
    resetFunc();  //call reset
  }
      
}
