#include <Wire.h>

const int ADXL345 = 0x53; // Direccion I2C
float X_out, Y_out, Z_out;

// Offset a calibrar por cada acelerometro
#define OFFSET_X 0.00
#define OFFSET_Y 0.00
#define OFFSET_Z 0.16

void setup() {
  Serial.begin(9600);
  ADXL345_16g_init();
}


void loop() {
  ADXL345_16g_read_acc();
}

void ADXL345_16g_read_acc() {
  // === Read acceleromter data === //
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32);
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true);
  X_out = ( Wire.read() | Wire.read() << 8);
  X_out = X_out / 32 - OFFSET_X;
  Y_out = ( Wire.read() | Wire.read() << 8);
  Y_out = Y_out / 32 - OFFSET_Y;
  Z_out = ( Wire.read() | Wire.read() << 8);
  Z_out = Z_out / 32 - OFFSET_Z;
}

void ADXL345_16g_init() {
  Wire.begin();

  // Inicio de la comunicación
  Wire.beginTransmission(ADXL345);
  Wire.write(0x2D);
  Wire.write(8);
  Wire.endTransmission();
  delay(10);

  // Rango máximo +-16g
  Wire.beginTransmission(ADXL345);
  Wire.write(0x31);
  Wire.write(B00000011);
  Wire.endTransmission();
}
