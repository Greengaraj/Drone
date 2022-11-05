#include <TroykaGPS.h>                                            // Library for working with a GPS device
#include <SoftwareSerial.h>                                       // Library for the operation of software Serial

#define GPS_SERIAL mySerial                                       // Serial-the port to which the GPS module is connected

float height, Calculated_height;                                  // Variable for storing the value of the current altitude and altitude above sea level
float Altitude = 173;                                             // Altitude above sea level for the city of Mikhnevo (for the city of Moscow and Stupino = 186, for Domodedovo = 161)

SoftwareSerial mySerial(4, 5);                                    // I create an object to work with the software Serial and pass it the TX and RX pins
GPS gps(GPS_SERIAL);                                              // Creating an object of the GPS class and passing the GPS_SERIAL object to it

void setup(){
  Serial.begin(115200);                                           // I open the serial port to monitor the actions in the program and transmit a speed of 115200 baud
  while (!Serial) {}                                              // I'm waiting for the COM port to open to track all events
  Serial.print("Serial init OK\r\n");
  GPS_SERIAL.begin(115200);                                       // I open a Serial connection with the GPS module at a speed of 115200 baud
  Serial.println("GPS init is OK on speed 115200");
}

void loop(){
  if (gps.available()) {                                          // If the data came from the GPS module
    gps.readParsing();                                            // Reading the data
    switch(gps.getState()) {                                      // Checking the status of the GPS module
      case GPS_OK:                                                // Everything is OK
        Serial.print("Height: ");                                 // I display the current height of the drone
        HeightCalculation();
        break;
      case GPS_ERROR_DATA:                                        // Data error
        Serial.println("GPS error data");
        break;
      case GPS_ERROR_SAT:                                         // No connection to satellites
        Serial.println("GPS no connect to satellites!!!");
        break;
    }
  }
}

void HeightCalculation(){                                         // Function for calculating the current height
  height = gps.getAltitude();                                     // Reading the current height
  Calculated_height = height - Altitude;                          // The height of the city above sea level is subtracted from the measured height
  Serial.println(Calculated_height);                              // I display the current height of the drone
}
