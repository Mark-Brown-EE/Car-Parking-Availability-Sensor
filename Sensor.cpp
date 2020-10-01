//include the library header file for HC-12 chip
#include <SoftwareSerial.h>
SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin
const unsigned int TRIG_PIN1=13; //Trigger pin for sensor 1
const unsigned int ECHO_PIN1=12; //Echo pin for sensor 1
const unsigned int TRIG_PIN2=9; //Trigger pin for sensor 2
const unsigned int ECHO_PIN2=8; //Echo pin for sensor 2
int count = 0; //create an int to count the occupied spaces
int TotalSpace = 2; //set total number of spaces
int FreeSpace = 0; //int for calculating no. of free spaces
int led1 = 7; // the pin led1 is connected to
int led2 = 6; // the pin led2 is connected to
void setup() {
pinMode(TRIG_PIN1, OUTPUT); //Declare TRIG_PIN1 as an output
pinMode(ECHO_PIN1, INPUT); //Declare ECHO_PIN1 as an input
pinMode(TRIG_PIN2, OUTPUT); //Declare TRIG_PIN2 as an output
pinMode(ECHO_PIN2, INPUT); //Declare ECHO_PIN2 as an intput
pinMode(led1, OUTPUT); // Declare led1 as an output
pinMode(led2, OUTPUT); // Declare led2 as an output
Serial.begin(9600); // Serial port to computer
HC12.begin(9600); // Serial port to HC12
}
void loop() {
digitalWrite(TRIG_PIN1, LOW); //turn off trig pin in case it was already
on
20
delayMicroseconds(2); // wait 2 microseconds
digitalWrite(TRIG_PIN1, HIGH); //activate trig pin
//the trig pin needs to be high for atleast 10 microseconds to activate
delayMicroseconds(10); // wait 10 microseconds
digitalWrite(TRIG_PIN1, LOW); //deactivate trig pin
const unsigned long duration1 = pulseIn(ECHO_PIN1, HIGH); // declaring
long int to calculate the time
int distance1 = duration1/29/2; //calculating distance in cm
digitalWrite(TRIG_PIN2, LOW); //turn off trig pin in case it was already
on
delayMicroseconds(2); // wait 2 microseconds
digitalWrite(TRIG_PIN2, HIGH);
//the trig pin needs to be high for atleast 10 microseconds to activate
delayMicroseconds(10); // wait 10 microseconds
digitalWrite(TRIG_PIN2, LOW); //deactivate trig pin
const unsigned long duration2 = pulseIn(ECHO_PIN2, HIGH); // declaring
long int to calculate the time
int distance2 = duration2/29/2; // calculating distance in cm
if(duration1==0 || duration2==0){
//if no duration is calculated print error message to serial monitor
Serial.write("Warning: no pulse from sensor");
}
else{
//printing distances to serial monitor
Serial.print("\nsensor 1 distance to car: ");
Serial.print(distance1);
Serial.println(" cm");
Serial.print("sensor 2 distance to car: ");
Serial.print(distance2);
Serial.println(" cm");
}
if (distance1 < 10){
//if the distance is less than 10cm the space is considered full
Serial.println("Space 1 full"); // print info on serial monitor
distance1 = 1; //set the variable distance1 = 1 for calculating no. of
free spaces
digitalWrite(led1, LOW); //turn led1 off
}
else{
//if the distance is greater than 10cm the space is considered empty
Serial.println("Space 1 empty");
digitalWrite(led1, HIGH); // Turn led1 on
distance1 = 0; //set the variable distance1 = 0 for calculating no. of
free spaces
}
if (distance2 < 10){
//if the distance is less than 10cm the space is considered full
Serial.println("Space 2 full"); // print info on serial monitor
distance2 = 1; //set the variable distance2 = 1 for calculating no. of
free spaces
digitalWrite(led2, LOW); //Turn led2 off
}
else{
21
//if the distance is greater than 10cm the space is considered empty
Serial.println("Space 2 empty");
distance2 = 0; //set the variable distance2 = 0 for calculating no. of
free spaces
digitalWrite(led2, HIGH); // Turn led2 on
}
//add all occupied spaces together
count = distance1 + distance2;
//calculate no. of free spaces (total - total occupied)
FreeSpace = TotalSpace - count;
Serial.print("Available spaces: ");
Serial.println(FreeSpace); //print no. of available spaces to serial
monitor
HC12.write(FreeSpace); //write the no. of available spaces to HC-12
//No. of spaces available will be updated every 1.5 seconds
delay(1500);
}
