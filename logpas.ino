#include <SPI.h>                                      // библиотека для работы с SPI
#include <Ethernet2.h>                                // библиотека для работы с Ethernet Shield

EthernetClient client;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };  // MAC-адрес контроллера
byte login[], pass[];

void setup() {
  login[] = mac[];
  password()
}

void loop() {
}

void password(){
  for (int i=mac;i>0;i--) {
    pass[i] = mac[i];
  }
  return pass[];
}
