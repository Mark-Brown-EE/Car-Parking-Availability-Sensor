// include the library header files for HC-12 chip and LCD
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(13, 12, 5, 4, 3, 2);
SoftwareSerial HC12(10, 11); // HC-12 TX (transmit) Pin, HC-12 RX (receive)
Pin
int Total; //declare int for total no. of spaces available
void setup() {
Serial.begin(9600); // Serial port to computer
HC12.begin(9600); // Serial port to HC12
// set up the LCD's number of columns and rows:
lcd.begin(16, 2);
// Print "available spaces " to the LCD.
lcd.print("Available spaces");
}
void loop() {
while (HC12.available()) { // If HC-12 has data
Total = HC12.read(); //read the data and assign to variable
total
Serial.print("Available spaces: ");
Serial.println(Total); // Send the data to Serial monitor
}
// set the cursor to column 0, line 1
lcd.setCursor(0, 1);
// print the number of available spaces on LCD
lcd.print(Total);
}
