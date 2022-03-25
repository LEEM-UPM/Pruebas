#include <Wire.h>

const int KX134 = 0x1F; // 0x1E
float X_out = 0.0, Y_out = 0.0, Z_out = 0.0;

// Offset a calibrar por cada acelerometro
#define OFFSET_X 0.00
#define OFFSET_Y 0.08
#define OFFSET_Z 0.00

void setup() {
  Serial.begin(9600);
  KX134_64g_init();
}


float z_max = 0.0;

void loop() {
  KX134_64g_read_acc();

  /*
    if (abs(Z_out) > z_max) {
    z_max = abs(Z_out);
    Serial.print(Z_out);
    Serial.println('\t');
    }*/


  Serial.print(X_out);
  Serial.print('\t');
  Serial.print(Y_out);
  Serial.print('\t');
  Serial.print(Z_out);
  Serial.println('\t');
  delay(100);


}

void KX134_64g_read_acc() {

  uint16_t raw[3];

  Wire.beginTransmission(KX134);
  Wire.write(0x08);
  Wire.endTransmission(false);
  Wire.requestFrom(KX134, 6, true);

  //const float convRange2G =  0.00006103518784142582;
  //const float convRange4G =  0.0001220703756828516;
  //const float convRange8G =  0.0002441407513657033;
  const float convRange64G = .001953125095370342112;
  X_out = ((float)( Wire.read() | Wire.read() << 8)) * convRange64G - OFFSET_X;
  Y_out = ((float)( Wire.read() | Wire.read() << 8)) * convRange64G - OFFSET_Y;
  Z_out = ((float)( Wire.read() | Wire.read() << 8)) *  convRange64G - OFFSET_Z;
}


bool KX134_64g_init() {
  Wire.begin();

  Wire.beginTransmission(KX134);
  if (Wire.endTransmission() != 0) {
    
    // OPCIONES PARA PONER EL RANGO DE LECTURA:
    /*
      #define KX134_RANGE8G  0x00
      #define KX134_RANGE16G 0x01
      #define KX134_RANGE32G 0x02
      #define KX134_RANGE64G 0x03
    */
    byte tempRegVal;
    tempRegVal = B11000000;       // Inicialización acelerómetro
    tempRegVal |= (0x03 << 3);    // Cambiar aquí el rango de lectura
    Wire.beginTransmission(KX134);
    Wire.write(0x1B);
    Wire.write(tempRegVal);
    Wire.endTransmission();
    // Salida por defecto a 50Hz

    // Desactivación del filtro paso bajo
    Wire.beginTransmission(KX134);
    Wire.write(0x21);
    Wire.write(B10000110);
    Wire.endTransmission();
    return 1;
  }

  return 0;
}
