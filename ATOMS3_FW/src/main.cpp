#include <Arduino.h>
#include <M5Unified.h>
#include <Wire.h>

#define I2C_ADDR_SDP810 0x25

#define NX 128
uint8_t p = 0;
uint8_t val[NX];
uint8_t modeS = 1;
#define N_SPEED 3
uint8_t wait[] = { 5, 20, 100 };
uint8_t v0 = 64;

#define N_MAG 3
uint8_t modeM = 0;
float mags[] = {10, 100, 1000};
uint16_t color;
uint16_t colors[] = { WHITE, GREEN, CYAN };

// LCD: 128x128
void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  M5.Lcd.clear();
//  Serial.begin(115200);
  Serial.begin(115200, SERIAL_8N1, 2, 1); // RX/TX (Grove)
//  Serial2.begin(115200, 2, 1); // RX/TX (Grove)
  Wire.begin(38, 39); // SDA, SCL
  Wire.beginTransmission(I2C_ADDR_SDP810);
  Wire.write(0x36); Wire.write(0x1e); // diff. pres. continuous, no average
  Wire.endTransmission();
}

// 2's complement
int conv_2s(uint16_t d)
{
  if (d & 0x8000) return(- ((~d & 0x7fff) + 1));
  else return(d);
}

void loop() {
  uint8_t px = p;
  uint8_t dp = 0;
  uint8_t dat[16];
 
//  Wire.requestFrom(I2C_ADDR_SDP810, 9);
//  while(Wire.available() && dp < 9) dat[dp++] = Wire.read();
  Wire.requestFrom(I2C_ADDR_SDP810, 3);
  while(Wire.available() && dp < 3) dat[dp++] = Wire.read();
 
  uint16_t DPb, Tempb, SFb;
  DPb   = dat[0] << 8 | dat[1];
//  Tempb = dat[3] << 8 | dat[4];
//  SFb   = dat[6] << 8 | dat[7];
//  Serial.print(DPb, HEX); Serial.print(" ");
//  Serial.print(Tempb, HEX); Serial.print(" ");
//  Serial.print(SFb, HEX); Serial.print(" | ");
  int DPi, Tempi, SFi;
  DPi   = conv_2s(DPb);
//  Tempi = conv_2s(Tempb);
//  SFi   = conv_2s(SFb);
//  Serial.print(DPi); Serial.print(" ");
//  Serial.print(Tempi); Serial.print(" ");
//  Serial.print(SFi); Serial.print(" | ");
  float DP, Temp;
  DP = (float)DPi / 240.0;
//  Temp = (float)Tempi / 200.0;
//  Serial.print(t++); Serial.print(" ");
//  Serial.print(DP); Serial.print(" ");
//  Serial.print(Temp); Serial.println("");

  int vn = (int)(DP * mags[modeM]) + 64;
  if (vn < 0) vn = 0;
  if (vn > 127) vn = 127;
//  printf("%d %f %f\n", vn, mags[modeM], DP); 
//  Serial.printf("%04x\n", (DPi & 0xffff));
  Serial.printf("%d\n", (DPi & 0xffff));
//  Serial.printf("%f\n", DP);
//  Serial.printf("%d %f\n", vn, DP);
//  Serial.printf("%c%c%c%c", 0x55, 0xaa, dat[0], dat[1]);
  val[px] = vn;
  color = colors[modeM];
  for (uint8_t x = 0; x < NX; x++){
    M5.Lcd.drawFastVLine(x, 0, 128, BLACK);
    M5.Lcd.drawPixel(x, val[px], color);
    px = (px + 1) % NX;
  }
  p = (p + 1) % NX;
  M5.update();
  if (M5.BtnA.wasDoubleClicked()){
    modeS = (modeS + 1) % N_SPEED;
  }
  if (M5.BtnA.wasSingleClicked()){
    modeM = (modeM + 1) % N_MAG;
  }
  delay(wait[modeS]);
}

