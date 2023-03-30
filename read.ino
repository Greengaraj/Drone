#include <SPI.h>                                    // библиотека для работы с SPI
#include <SD.h>                                     // библиотека для работы с SD-картами

constexpr uint8_t SD_CS_PIN = 8;                    // имя для CS пина microSD-карты

String dataString = "";

void setup() {
  Serial.begin(9600);                               // открываю последовательный порт для мониторинга действий в программе
  Serial.println("Initializing SD card...");        // вывожу сообщение в Serial-порт о поиске карты памяти

  if (!SD.begin(SD_CS_PIN)) {                       // если microSD-карта не была обнаружена
    Serial.println("Card failed, or not present");  // вывожу сообщение об ошибке
    return;
  } else {
    Serial.println("Card initialized.");
  }
}
 
void loop() {
  dataString = "";
  saveSD();
  readSD()
}

void readSD() {
  File dataFile = SD.read("token.txt");
  if (dataFile) {                                     // если файл доступен для чтенния
    Serial.println(dataString);
    dataFile.close();                                 // закрываю файл
    Serial.println("Read OK");                        // вывожу сообщение об удачной записи
  } else {                                            // если файл не доступен
    Serial.println("Error opening datalog.txt");      // вывожу сообщение о неудачной записи
  }
}

void saveSD() {
  File dataFile = SD.open("token.txt", FILE_WRITE); // создаю файл для записи
  if (dataFile) {                                     // если файл доступен для записи
    dataFile.println(dataString);                     // сохраняю данные
    dataFile.close();                                 // закрываю файл
    Serial.println("Save OK");                        // вывожу сообщение об удачной записи
  } else {                                            // если файл не доступен
    Serial.println("Error opening datalog.txt");      // вывожу сообщение о неудачной записи
  }
}
