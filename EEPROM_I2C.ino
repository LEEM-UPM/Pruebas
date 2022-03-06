#include <SoftwareSerial.h>

#include<Wire.h>
#define EEPROM_I2C_ADDRESS 0x50


// Función para leer de la EEPROM
byte readEEPROM(int address) {
  byte rcvData = 0xFF;
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);
  Wire.write((int)(address >> 8));   // MSB
  Wire.write((int)(address & 0x00FF)); // LSB
  Wire.endTransmission();
  Wire.requestFrom(EEPROM_I2C_ADDRESS, 1);
  rcvData =  Wire.read();
  return rcvData;
}


void writeEEPROM(uint16_t address, byte val) {
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);
  Wire.write((uint8_t)(address >> 8));   // MSB
  Wire.write((uint8_t)(address & 0xFF)); // LSB
  Wire.write(val);
  Wire.endTransmission();
  delay(5);
}

void writeEEPROM_Page(uint16_t address, byte *val, uint16_t tam) {
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);
  Wire.write((uint8_t)(address >> 8));   // MSB
  Wire.write((uint8_t)(address & 0xFF)); // LSB
  for (uint16_t i = 0; i < tam; i++) {
    Wire.write(*val);
    val++;
  }
  Wire.endTransmission();
}

void setup() {

  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);

  delay(2500);
  Serial.println("Inicio");

  byte pac[256];
  for (byte j = 0; j < 255; j++) {
    pac[j] = j;
  }

  writeEEPROM_Page(0, pac, 256);

  for (byte i = 0; i < 255; i++) {
    Serial.println(readEEPROM(i));
    delay(5);
  }

  /*
    byte pac[256];
    for (byte j = 0; j < 255; j++) {
    pac[j] = j;
    }

    for (byte i = 0; i < 16; i++) {
    writeEEPROM_Page(i * 16, pac + i * 16, 16);
    delay(5);
    }
  */


  /*
    byte pac[256];
    for (byte j = 0; j < 255; j++) {
    pac[j] = j;
    }

    unsigned long t_o = millis();
    for (byte k = 0; k < 255; k++) {
    for (byte i = 0; i < 16; i++) {
      writeEEPROM_Page(k * 256 + i * 16, pac + i * 16, 16);
      delay(5);
    }
    }

    Serial.println("Tiempo de escritura en paquetes de 64kB");
    Serial.println(millis() - t_o);
    delay(1000);

    uint16_t correctas = 0;
    uint16_t error = 0;

    for (uint16_t i = 0; i < 65535; i++) {
    if (readEEPROM(i) == 15) { //(i & 0xFF)){
      correctas++;
    }
    else {
      error++;
    }
    }
    Serial.print("Correctas:");
    Serial.println(correctas);
    Serial.print("Erroneas:");
    Serial.println(error);
  */




  // Test byte package
  /*
    unsigned long t_o = millis();
    for (uint16_t i = 0; i < 65280; i += 256) {
    writeEEPROM_Page(i, pac, 255);
    }
    Serial.println("Tiempo de escritura en paquetes de 64kB");
    Serial.println(millis() - t_o);
    delay(1000);

    uint16_t correctas = 0;
    uint16_t error = 0;

    for (uint16_t i = 0; i < 65535; i++) {
    if (readEEPROM(i) == 15) { //(i & 0xFF)){
      correctas++;
    }
    else {
      error++;
    }
    }
    Serial.print("Correctas:");
    Serial.println(correctas);
    Serial.print("Erroneas:");
    Serial.println(error);
  */

  /*
    // Test byte a byte
    unsigned long t_o = millis();
    for (uint16_t i = 0; i < 65535; i++){
    writeEEPROM(i, 0x2A);
    //Serial.println(i);
    }
    Serial.println("Tiempo de escritura de 64kB");
    Serial.println(millis() - t_o);

    delay(1000);

    uint16_t correctas = 0;
    uint16_t error = 0;

    for (uint16_t i = 0; i < 65535; i++){
    if(readEEPROM(i) == 0x2A ){ //(i & 0xFF)){
      correctas++;
    }
    else{
      error++;
    }
    }
    Serial.print("Correctas:");
    Serial.println(correctas);
    Serial.print("Erroneas:");
    Serial.println(error);
  */
}

void loop() {

}
