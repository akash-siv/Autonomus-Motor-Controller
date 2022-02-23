#define relayon HIGH
#define relayoff LOW
#define input INPUT_PULLUP
#define output OUTPUT
#define fd 2
#define fu 3
#define sd 6
#define su 7
#define sump 4
#define motorA 5
#define motorBon 8
#define motorBoff 9 

int mytankA = 0;
int mytankB = 0;
int normal = 0;
int mc = 0;

void setup(){
  pinMode(fd, input); 
  pinMode(fu, input);
  pinMode(sd, input); 
  pinMode(su, input);
  pinMode(sump, input);
  pinMode(motorA, output);
  pinMode(motorBon, output);
  pinMode(motorBoff, output);
  digitalWrite(motorA, relayoff);
  digitalWrite(motorBon, relayon);
  digitalWrite(motorBoff, relayon);
  delay(1000);
  mytankA = 0;
  mytankB = 0;}

void loop(){
  // for fresh water tank
  if ((digitalRead(fd) == HIGH) && (digitalRead(sump) == HIGH)){
    delay(1000);
    if ((digitalRead(fd) == HIGH) && (digitalRead(sump) == HIGH)){// Check whether my tank is less
    digitalWrite(motorA, relayon);
    mytankA = 1;}}
    

  if ((mytankA == 1) && (digitalRead(sump) == HIGH)){// When my tank is on then check when it is full
    delay(1000);
    if ((mytankA == 1) && (digitalRead(sump) == HIGH)){
    if (digitalRead(fu) == HIGH){
    delay(1000);
    if (digitalRead(fu) == HIGH){  
    digitalWrite(motorA, relayoff);
    mytankA = 0;}}}}

  if (digitalRead(sump) == LOW){
    delay(1000);
    if (digitalRead(sump) == LOW){
    digitalWrite(motorA, relayoff);
    mytankA = 0;
    }
  }
    // SALT WATER TANK
    if (digitalRead(sd) == HIGH){
    delay(1000);
    if (digitalRead(sd) == HIGH) {// for bore motor
    digitalWrite(motorBon, relayoff);
    delay(1000);
    digitalWrite(motorBon, relayon);
    mytankB = 1;}}
    

    if (mytankB == 1) {// When my tank is on then check when it is full
    delay(1000);
    if (mytankB == 1) {
    if (digitalRead(su) == HIGH){
    delay(1000);
    if (digitalRead(su) == HIGH){  
    digitalWrite(motorBoff, relayoff);
    delay(1000);
    digitalWrite(motorBoff, relayon);
    mytankB = 0;}}}}


  }


