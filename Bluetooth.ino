#include <SoftwareSerial.h>               // Library for communicating with the module via the UART software bus
#include <iarduino_Bluetooth_HC05.h>      // Library for working with the HC-05/HC-06 module

SoftwareSerial softSerial(2,3);           // I create a SoftSerial object specifying the pins RX, TX. Pin 2 = TX of the module, pin 3 = RX of the module
iarduino_Bluetooth_HC05 hc05(4);          // I create an hc05 object by specifying the Arduino pin that connects to the module's Key output

int myArray[3] = {123,456,789};           // I define an array with data that will be transmitted

void setup()
{
  Serial.begin(9600);                     // I open the COM port and specify the data transfer rate
  Serial.print("begin: ");
  if(hc05.begin(softSerial))
  {
    Serial.println("Ok");                 // I initiate work with the HC-05/HC-06 module, specifying the SoftSerial object through which communication is carried out
  }
  else
  {
    Serial.println("Error");              // If the work with the module is not initiated, then I output an error message
  }
}

void loop ()
{
  int i = hc05.find(10);                  // I search for devices, no longer than 10 seconds
  if(i){
    Serial.print("found ");
    Serial.print(i);
    Serial.println(" devices:");
    for(int j=0; j<i; j++)
    {
      Serial.print("Name: ");
      Serial.print(hc05.findName[j]);
      Serial.print(", Address: ");
      Serial.print(hc05.findAddr[j]);
      Serial.println(";");
    }
  }
  else
  {
    Serial.println("Device not found.");
  }
}
