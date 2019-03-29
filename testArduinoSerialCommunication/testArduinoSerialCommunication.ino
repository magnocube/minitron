#include <Arduino.h>
#include <HardwareSerial.h>


char SerialInData[20]; // Allocate some space for the string
char SerialInChar; // Where to store the character read
byte SerialIndex = 0; // Index into array; where to store the character
HardwareSerial mySerial(2); // use uart2


void setup() {
  mySerial.begin(9600, SERIAL_8N1, 16, 17); // pins 16 rx2, 17 tx2, 19200 bps, 8 bits no parity 1 stop bit
  Serial.begin(9600);
}

void loop() {
  if (mySerial.available() > 0) {
    while (mySerial.available() > 0 && SerialInChar != '\n') {
      if (SerialIndex < 19) // One less than the size of the array
      {
        SerialInChar = mySerial.read(); // Read a character
        SerialInData[SerialIndex] = SerialInChar; // Store it
        SerialIndex++; // Increment where to write next
        SerialInData[SerialIndex] = '\0'; // Null terminate the string
      } else {
        break;  // validate if this line works
      }
    }
    Serial.print(SerialInData);
    SerialIndex = 0;
    SerialInChar = 0;
    mySerial.println("confrimed");

  }

}
