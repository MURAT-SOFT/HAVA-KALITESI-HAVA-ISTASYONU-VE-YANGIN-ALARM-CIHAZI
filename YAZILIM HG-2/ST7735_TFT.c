//   C DERLEYICI SITRONIX ST7335R/S SURUCU PIC16/PIC18/PIC24/PIC32
#include <string.h>
int1 wrap = TRUE;
unsigned int8 colstart = 0, rowstart = 0, _tft_type;
#define _swap(a, b) { signed int16 t; t = a; a = b; b = t;}
#define _width         128
#define _height        160
#define ST7735_NOP     0x00
#define ST7735_SWRESET 0x01
#define ST7735_RDDID   0x04
#define ST7735_RDDST   0x09
#define ST7735_SLPIN   0x10
#define ST7735_SLPOUT  0x11
#define ST7735_PTLON   0x12
#define ST7735_NORON   0x13
#define ST7735_INVOFF  0x20
#define ST7735_INVON   0x21
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON  0x29
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define ST7735_RAMRD   0x2E
#define ST7735_PTLAR   0x30
#define ST7735_VSCRDEF 0x33
#define ST7735_COLMOD  0x3A
#define ST7735_MADCTL  0x36
#define ST7735_VSCRSADD 0x37
#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR  0xB4
#define ST7735_DISSET5 0xB6
#define ST7735_PWCTR1  0xC0
#define ST7735_PWCTR2  0xC1
#define ST7735_PWCTR3  0xC2
#define ST7735_PWCTR4  0xC3
#define ST7735_PWCTR5  0xC4
#define ST7735_VMCTR1  0xC5
#define ST7735_RDID1   0xDA
#define ST7735_RDID2   0xDB
#define ST7735_RDID3   0xDC
#define ST7735_RDID4   0xDD
#define ST7735_PWCTR6  0xFC
#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1
// ST7735R/S 1.8 INC TFT_RENKLI EKRAN RENK TANIMLARI
#define   ST7735_SIYAH   0x0000
#define   ST7735_MAVI    0x001F
#define   ST7735_KIRMIZI 0xF800
#define   ST7735_YESIL   0x07E0
#define   ST7735_CAM_RENK 0x07FF
#define   ST7735_MOR   0xF81F
#define   ST7735_SARI  0xFFE0
#define   ST7735_BEYAZ 0xFFFF
const char Font[] = {
0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x5F, 0x00, 0x00,
0x00, 0x07, 0x00, 0x07, 0x00,
0x14, 0x7F, 0x14, 0x7F, 0x14,
0x24, 0x2A, 0x7F, 0x2A, 0x12,
0x23, 0x13, 0x08, 0x64, 0x62,
0x36, 0x49, 0x56, 0x20, 0x50,
0x00, 0x08, 0x07, 0x03, 0x00,
0x00, 0x1C, 0x22, 0x41, 0x00,
0x00, 0x41, 0x22, 0x1C, 0x00,
0x2A, 0x1C, 0x7F, 0x1C, 0x2A,
0x08, 0x08, 0x3E, 0x08, 0x08,
0x00, 0x80, 0x70, 0x30, 0x00,
0x08, 0x08, 0x08, 0x08, 0x08,
0x00, 0x00, 0x60, 0x60, 0x00,
0x20, 0x10, 0x08, 0x04, 0x02,
0x3E, 0x51, 0x49, 0x45, 0x3E,
0x00, 0x42, 0x7F, 0x40, 0x00,
0x72, 0x49, 0x49, 0x49, 0x46,
0x21, 0x41, 0x49, 0x4D, 0x33,
0x18, 0x14, 0x12, 0x7F, 0x10,
0x27, 0x45, 0x45, 0x45, 0x39,
0x3C, 0x4A, 0x49, 0x49, 0x31,
0x41, 0x21, 0x11, 0x09, 0x07,
0x36, 0x49, 0x49, 0x49, 0x36,
0x46, 0x49, 0x49, 0x29, 0x1E,
0x00, 0x00, 0x14, 0x00, 0x00,
0x00, 0x40, 0x34, 0x00, 0x00,
0x00, 0x08, 0x14, 0x22, 0x41,
0x14, 0x14, 0x14, 0x14, 0x14,
0x00, 0x41, 0x22, 0x14, 0x08,
0x02, 0x01, 0x59, 0x09, 0x06,
0x3E, 0x41, 0x5D, 0x59, 0x4E,
0x7C, 0x12, 0x11, 0x12, 0x7C,
0x7F, 0x49, 0x49, 0x49, 0x36,
0x3E, 0x41, 0x41, 0x41, 0x22,
0x7F, 0x41, 0x41, 0x41, 0x3E,
0x7F, 0x49, 0x49, 0x49, 0x41,
0x7F, 0x09, 0x09, 0x09, 0x01,
0x3E, 0x41, 0x41, 0x51, 0x73,
0x7F, 0x08, 0x08, 0x08, 0x7F,
0x00, 0x41, 0x7F, 0x41, 0x00,
0x20, 0x40, 0x41, 0x3F, 0x01,
0x7F, 0x08, 0x14, 0x22, 0x41,
0x7F, 0x40, 0x40, 0x40, 0x40,
0x7F, 0x02, 0x1C, 0x02, 0x7F,
0x7F, 0x04, 0x08, 0x10, 0x7F,
0x3E, 0x41, 0x41, 0x41, 0x3E,
0x7F, 0x09, 0x09, 0x09, 0x06,
0x3E, 0x41, 0x51, 0x21, 0x5E,
0x7F, 0x09, 0x19, 0x29, 0x46
};
const char Font2[] = {
0x26, 0x49, 0x49, 0x49, 0x32,
0x03, 0x01, 0x7F, 0x01, 0x03,
0x3F, 0x40, 0x40, 0x40, 0x3F,
0x1F, 0x20, 0x40, 0x20, 0x1F,
0x3F, 0x40, 0x38, 0x40, 0x3F,
0x63, 0x14, 0x08, 0x14, 0x63,
0x03, 0x04, 0x78, 0x04, 0x03,
0x61, 0x59, 0x49, 0x4D, 0x43,
0x00, 0x7F, 0x41, 0x41, 0x41,
0x02, 0x04, 0x08, 0x10, 0x20,
0x00, 0x41, 0x41, 0x41, 0x7F,
0x04, 0x02, 0x01, 0x02, 0x04,
0x40, 0x40, 0x40, 0x40, 0x40,
0x00, 0x03, 0x07, 0x08, 0x00,
0x20, 0x54, 0x54, 0x78, 0x40,
0x7F, 0x28, 0x44, 0x44, 0x38,
0x38, 0x44, 0x44, 0x44, 0x28,
0x38, 0x44, 0x44, 0x28, 0x7F,
0x38, 0x54, 0x54, 0x54, 0x18,
0x00, 0x08, 0x7E, 0x09, 0x02,
0x18, 0xA4, 0xA4, 0x9C, 0x78,
0x7F, 0x08, 0x04, 0x04, 0x78,
0x00, 0x44, 0x7D, 0x40, 0x00,
0x20, 0x40, 0x40, 0x3D, 0x00,
0x7F, 0x10, 0x28, 0x44, 0x00,
0x00, 0x41, 0x7F, 0x40, 0x00,
0x7C, 0x04, 0x78, 0x04, 0x78,
0x7C, 0x08, 0x04, 0x04, 0x78,
0x38, 0x44, 0x44, 0x44, 0x38,
0xFC, 0x18, 0x24, 0x24, 0x18,
0x18, 0x24, 0x24, 0x18, 0xFC,
0x7C, 0x08, 0x04, 0x04, 0x08,
0x48, 0x54, 0x54, 0x54, 0x24,
0x04, 0x04, 0x3F, 0x44, 0x24,
0x3C, 0x40, 0x40, 0x20, 0x7C,
0x1C, 0x20, 0x40, 0x20, 0x1C,
0x3C, 0x40, 0x30, 0x40, 0x3C,
0x44, 0x28, 0x10, 0x28, 0x44,
0x4C, 0x90, 0x90, 0x90, 0x7C,
0x44, 0x64, 0x54, 0x4C, 0x44,
0x00, 0x08, 0x36, 0x41, 0x00,
0x00, 0x00, 0x77, 0x00, 0x00,
0x00, 0x41, 0x36, 0x08, 0x00,
0x02, 0x01, 0x02, 0x04, 0x02
};
void spi_yaz(unsigned int8 spidata){
  #ifndef TFT_SPI_HARDWARE
    int8 ss;
    for(ss = 0x80; ss; ss >>= 1) {
    if (spidata & ss)  output_high(TFT_DATA);
    else               output_low(TFT_DATA);
    output_high(TFT_CLK);
    output_low(TFT_CLK);}
  #else
    spi_write(spidata); 
  #endif
}
void KOMUT_YAZ(unsigned int8 cmd_){
  output_low(TFT_CS);
  output_low(TFT_DC);
  spi_yaz(cmd_);
  output_high(TFT_CS);
}
void BILGI_YAZ(unsigned int8 BILGI){
  output_low(TFT_CS);
  output_high(TFT_DC);
  spi_yaz(BILGI);
  output_high(TFT_CS);
}
void Bcmd(){
  KOMUT_YAZ(ST7735_SWRESET);
  delay_ms(50);
  KOMUT_YAZ(ST7735_SLPOUT);
  delay_ms(500);
   KOMUT_YAZ(ST7735_COLMOD);
  BILGI_YAZ(0x05);
  delay_ms(10);
   KOMUT_YAZ(ST7735_FRMCTR1);
  BILGI_YAZ(0x00);
  BILGI_YAZ(0x06);
  BILGI_YAZ(0x03);
  delay_ms(10);
   KOMUT_YAZ(ST7735_MADCTL);
  BILGI_YAZ(0x08);
   KOMUT_YAZ(ST7735_DISSET5);
  BILGI_YAZ(0x15);
  BILGI_YAZ(0x02);
   KOMUT_YAZ(ST7735_INVCTR);
  BILGI_YAZ(0x00);
   KOMUT_YAZ(ST7735_PWCTR1);
  BILGI_YAZ(0x02);
  BILGI_YAZ(0x70);
  delay_ms(10);
   KOMUT_YAZ(ST7735_PWCTR2);
  BILGI_YAZ(0x05);
   KOMUT_YAZ(ST7735_PWCTR3);
  BILGI_YAZ(0x01);
  BILGI_YAZ(0x02);
   KOMUT_YAZ(ST7735_VMCTR1);
  BILGI_YAZ(0x3C);
  BILGI_YAZ(0x38);
  delay_ms(10);
   KOMUT_YAZ(ST7735_PWCTR6);
  BILGI_YAZ(0x11);
  BILGI_YAZ(0x15);
   KOMUT_YAZ(ST7735_GMCTRP1);
  BILGI_YAZ(0x09); BILGI_YAZ(0x16); BILGI_YAZ(0x09); BILGI_YAZ(0x20);
  BILGI_YAZ(0x21); BILGI_YAZ(0x1B); BILGI_YAZ(0x13); BILGI_YAZ(0x19);
  BILGI_YAZ(0x17); BILGI_YAZ(0x15); BILGI_YAZ(0x1E); BILGI_YAZ(0x2B);
  BILGI_YAZ(0x04); BILGI_YAZ(0x05); BILGI_YAZ(0x02); BILGI_YAZ(0x0E);
   KOMUT_YAZ(ST7735_GMCTRN1);
  BILGI_YAZ(0x0B); BILGI_YAZ(0x14); BILGI_YAZ(0x08); BILGI_YAZ(0x1E);
  BILGI_YAZ(0x22); BILGI_YAZ(0x1D); BILGI_YAZ(0x18); BILGI_YAZ(0x1E);
  BILGI_YAZ(0x1B); BILGI_YAZ(0x1A); BILGI_YAZ(0x24); BILGI_YAZ(0x2B);
  BILGI_YAZ(0x06); BILGI_YAZ(0x06); BILGI_YAZ(0x02); BILGI_YAZ(0x0F);
  delay_ms(10);
   KOMUT_YAZ(ST7735_CASET);
  BILGI_YAZ(0x00); BILGI_YAZ(0x02); BILGI_YAZ(0x08); BILGI_YAZ(0x81);
   KOMUT_YAZ(ST7735_RASET);
  BILGI_YAZ(0x00); BILGI_YAZ(0x01); BILGI_YAZ(0x08); BILGI_YAZ(0xA0);
   KOMUT_YAZ(ST7735_NORON);
  delay_ms(10);
   KOMUT_YAZ(ST7735_DISPON);
  delay_ms(500);
}
void Rcmd1(){
   KOMUT_YAZ(ST7735_SWRESET);
  delay_ms(150);
   KOMUT_YAZ(ST7735_SLPOUT);
  delay_ms(500);
   KOMUT_YAZ(ST7735_FRMCTR1);
  BILGI_YAZ(0x01);
  BILGI_YAZ(0x2C);
  BILGI_YAZ(0x2D);
   KOMUT_YAZ(ST7735_FRMCTR2);
  BILGI_YAZ(0x01);
  BILGI_YAZ(0x2C);
  BILGI_YAZ(0x2D);
   KOMUT_YAZ(ST7735_FRMCTR3);
  BILGI_YAZ(0x01); BILGI_YAZ(0x2C); BILGI_YAZ(0x2D);
  BILGI_YAZ(0x01); BILGI_YAZ(0x2C); BILGI_YAZ(0x2D);
   KOMUT_YAZ(ST7735_INVCTR);
  BILGI_YAZ(0x07);
   KOMUT_YAZ(ST7735_PWCTR1);
  BILGI_YAZ(0xA2);
  BILGI_YAZ(0x02);
  BILGI_YAZ(0x84);
   KOMUT_YAZ(ST7735_PWCTR2);
  BILGI_YAZ(0xC5);
   KOMUT_YAZ(ST7735_PWCTR3);
  BILGI_YAZ(0x0A);
  BILGI_YAZ(0x00);
   KOMUT_YAZ(ST7735_PWCTR4);
  BILGI_YAZ(0x8A);
  BILGI_YAZ(0x2A);
   KOMUT_YAZ(ST7735_PWCTR5);
  BILGI_YAZ(0x8A);
  BILGI_YAZ(0xEE);
   KOMUT_YAZ(ST7735_VMCTR1);
  BILGI_YAZ(0x0E);
   KOMUT_YAZ(ST7735_INVOFF);
   KOMUT_YAZ(ST7735_MADCTL);
  BILGI_YAZ(0xC8);
   KOMUT_YAZ(ST7735_COLMOD);
  BILGI_YAZ(0x05); 
}
void Rcmd2green(){
   KOMUT_YAZ(ST7735_CASET);
  BILGI_YAZ(0x00); BILGI_YAZ(0x02);
  BILGI_YAZ(0x00); BILGI_YAZ(0x7F + 0x02);
   KOMUT_YAZ(ST7735_RASET);
  BILGI_YAZ(0x00); BILGI_YAZ(0x01);
  BILGI_YAZ(0x00); BILGI_YAZ(0x9F + 0x01);
}
void Rcmd2red(){
   KOMUT_YAZ(ST7735_CASET);
  BILGI_YAZ(0x00); BILGI_YAZ(0x00);
  BILGI_YAZ(0x00); BILGI_YAZ(0x7F);
   KOMUT_YAZ(ST7735_RASET);
  BILGI_YAZ(0x00); BILGI_YAZ(0x00);
  BILGI_YAZ(0x00); BILGI_YAZ(0x9F);
}
void Rcmd3(){
   KOMUT_YAZ(ST7735_GMCTRP1);
  BILGI_YAZ(0x02); BILGI_YAZ(0x1C); BILGI_YAZ(0x07); BILGI_YAZ(0x12);
  BILGI_YAZ(0x37); BILGI_YAZ(0x32); BILGI_YAZ(0x29); BILGI_YAZ(0x2D);
  BILGI_YAZ(0x29); BILGI_YAZ(0x25); BILGI_YAZ(0x2B); BILGI_YAZ(0x39);
  BILGI_YAZ(0x00); BILGI_YAZ(0x01); BILGI_YAZ(0x03); BILGI_YAZ(0x10);
   KOMUT_YAZ(ST7735_GMCTRN1);
  BILGI_YAZ(0x03); BILGI_YAZ(0x1D); BILGI_YAZ(0x07); BILGI_YAZ(0x06);
  BILGI_YAZ(0x2E); BILGI_YAZ(0x2C); BILGI_YAZ(0x29); BILGI_YAZ(0x2D);
  BILGI_YAZ(0x2E); BILGI_YAZ(0x2E); BILGI_YAZ(0x37); BILGI_YAZ(0x3F);
  BILGI_YAZ(0x00); BILGI_YAZ(0x00); BILGI_YAZ(0x02); BILGI_YAZ(0x10);
   KOMUT_YAZ(ST7735_NORON);
  delay_ms(10);
   KOMUT_YAZ(ST7735_DISPON);
  delay_ms(100);
}
void pencere_adresi_ayarla(unsigned int8 x0, unsigned int8 y0, unsigned int8 x1, unsigned int8 y1){
   KOMUT_YAZ(ST7735_CASET);
  BILGI_YAZ(0);
  BILGI_YAZ(x0 + colstart);
  BILGI_YAZ(0);
  BILGI_YAZ(x1 + colstart);
   KOMUT_YAZ(ST7735_RASET);
  BILGI_YAZ(0);
  BILGI_YAZ(y0 + rowstart);
  BILGI_YAZ(0);
  BILGI_YAZ(y1 + rowstart);
   KOMUT_YAZ(ST7735_RAMWR); // TFT_EKRAN RAM BELLEK YAZ
}
void PIXEL_CIZ(unsigned int8 x_KORDINAT, unsigned int8 y_KORDINAT, unsigned int16 renk){
  if((x_KORDINAT >= _width) || (y_KORDINAT >= _height)) 
    return;
  pencere_adresi_ayarla(x_KORDINAT,y_KORDINAT,x_KORDINAT+1,y_KORDINAT+1);// EKRAN HAFIZA ADRESI HAZIRLA
  BILGI_YAZ(renk >> 8);// BILGILERI YAZ.
  BILGI_YAZ(renk & 0xFF);
}
void D_DIKDORTGEN(unsigned int8 x, unsigned int8 y, unsigned int8 w, unsigned int8 h, unsigned int16 color){
  unsigned int8 hi, lo;
  if((x >= _width) || (y >= _height))
    return;
  if((x + w - 1) >= _width)  
    w = _width  - x;
  if((y + h - 1) >= _height) 
    h = _height - y;
  pencere_adresi_ayarla(x, y, x+w-1, y+h-1);
  hi = color >> 8; lo = color;
  output_high(tft_dc);
  output_low(tft_cs);
  for(y=h; y>0; y--) {
    for(x = w; x > 0; x--) {
      spi_yaz(hi);
      spi_yaz(lo);
    }
  }
  output_high(tft_cs);
}
void EKRAN_BOYA(unsigned int16 color) {
  D_DIKDORTGEN(0, 0, _width, _height, color);
}
void DIKEY_CIZGI_CIZ(unsigned int8 x, unsigned int8 y, unsigned int8 h, unsigned int16 color){
  unsigned int8 hi, lo;
  if((x >= _width) || (y >= _height))
    return;
  if((y + h - 1) >= _height)
    h = _height - y;
  hi = color >> 8; lo = color;
  pencere_adresi_ayarla(x, y, x, y + h - 1);
  output_high(tft_dc);
  output_low(tft_cs);
  while (h--) {
    spi_yaz(hi);
    spi_yaz(lo);
  }
  output_high(tft_cs);
}
void drawFastHLine(unsigned int8 x, unsigned int8 y, unsigned int8 w, unsigned int16 color){
  unsigned int8 hi, lo;
  if((x >= _width) || (y >= _height))
    return;
  if((x + w - 1) >= _width)
    w = _width - x;
  hi = color >> 8; lo = color;
  pencere_adresi_ayarla(x, y, x + w - 1, y);
  output_high(tft_dc);
  output_low(tft_cs);
  while (w--) {
    spi_yaz(hi);
    spi_yaz(lo);
  }
  output_high(tft_cs);
}
void DAIRE_CIZ(signed int16 x0, signed int16 y0, signed int16 r, unsigned int16 color) {
  signed int16 f, ddF_x, ddF_y, x, y;
  f = 1 - r, ddF_x = 1, ddF_y = -2 * r, x = 0, y = r;
  PIXEL_CIZ(x0  , y0 + r, color);
  PIXEL_CIZ(x0  , y0 - r, color);
  PIXEL_CIZ(x0+r, y0    , color);
  PIXEL_CIZ(x0-r, y0    , color);
  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
    PIXEL_CIZ(x0 + x, y0 + y, color);
    PIXEL_CIZ(x0 - x, y0 + y, color);
    PIXEL_CIZ(x0 + x, y0 - y, color);
    PIXEL_CIZ(x0 - x, y0 - y, color);
    PIXEL_CIZ(x0 + y, y0 + x, color);
    PIXEL_CIZ(x0 - y, y0 + x, color);
    PIXEL_CIZ(x0 + y, y0 - x, color);
    PIXEL_CIZ(x0 - y, y0 - x, color);
  }
}
void drawCircleHelper(signed int16 x0, signed int16 y0, signed int16 r, unsigned int8 cornername, unsigned int16 color) {
  signed int16 f, ddF_x, ddF_y, x, y;
  f = 1 - r, ddF_x = 1, ddF_y = -2 * r, x = 0, y = r;
  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;
    if (cornername & 0x4) {
      PIXEL_CIZ(x0 + x, y0 + y, color);
      PIXEL_CIZ(x0 + y, y0 + x, color);
    }
    if (cornername & 0x2) {
      PIXEL_CIZ(x0 + x, y0 - y, color);
      PIXEL_CIZ(x0 + y, y0 - x, color);
    }
    if (cornername & 0x8) {
      PIXEL_CIZ(x0 - y, y0 + x, color);
      PIXEL_CIZ(x0 - x, y0 + y, color);
    }
    if (cornername & 0x1) {
      PIXEL_CIZ(x0 - y, y0 - x, color);
      PIXEL_CIZ(x0 - x, y0 - y, color);
    }
  }
}
void fillCircleHelper(signed int16 x0, signed int16 y0, signed int16 r, unsigned int8 cornername, signed int16 delta, unsigned int16 color) {
  signed int16 f, ddF_x, ddF_y, x, y;
  f = 1 - r, ddF_x = 1, ddF_y = -2 * r, x = 0, y = r;
  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;

    if (cornername & 0x1) {
      DIKEY_CIZGI_CIZ(x0+x, y0-y, 2*y+1+delta, color);
      DIKEY_CIZGI_CIZ(x0+y, y0-x, 2*x+1+delta, color);
    }
    if (cornername & 0x2) {
      DIKEY_CIZGI_CIZ(x0-x, y0-y, 2*y+1+delta, color);
      DIKEY_CIZGI_CIZ(x0-y, y0-x, 2*x+1+delta, color);
    }
  }
}
void fillCircle(signed int16 x0, signed int16 y0, signed int16 r, unsigned int16 color) {
  DIKEY_CIZGI_CIZ(x0, y0 - r, 2 * r + 1, color);
  fillCircleHelper(x0, y0, r, 3, 0, color);
}
void drawRect(unsigned int8 x, unsigned int8 y, unsigned int8 w, unsigned int8 h, unsigned int16 color){
  DIKEY_CIZGI_CIZ(x, y, w, color);
  drawFastHLine(x, y + h - 1, w, color);
  DIKEY_CIZGI_CIZ(x, y, h, color);
  DIKEY_CIZGI_CIZ(x + w - 1, y, h, color);
}
void drawLine(signed int16 x0, signed int16 y0, signed int16 x1, signed int16 y1, unsigned int16 color){
  signed int16 steep, dx, dy, err, ystep;
  steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    _swap(x0,y0);
    _swap(x1,y1);
  }
  if (x0 > x1) {
    _swap(x0,x1);
    _swap(y0,y1);
  }
  dx = x1 - x0;
  dy = abs(y1-y0);

  err = dx / 2;
  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0<=x1; x0++) {
    if (steep) {
      PIXEL_CIZ(y0, x0, color);
    } else {
      PIXEL_CIZ(x0, y0, color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}
void fillRect(unsigned int8 x, unsigned int8 y, unsigned int8 w, unsigned int8 h, unsigned int16 color) {
  signed int16 i;
  // Update in subclasses if desired!
  for (i = x; i < x + w; i++) {
    DIKEY_CIZGI_CIZ(i, y, h, color);
  }
}
void drawRoundRect(unsigned int8 x, unsigned int8 y, unsigned int8 w, unsigned int8 h, unsigned int8 r, unsigned int16 color) {
  drawFastHLine(x+r  , y    , w-2*r, color);
  drawFastHLine(x+r  , y+h-1, w-2*r, color);
  DIKEY_CIZGI_CIZ(x    , y+r  , h-2*r, color);
  DIKEY_CIZGI_CIZ(x+w-1, y+r  , h-2*r, color);
  drawCircleHelper(x+r    , y+r    , r, 1, color);
  drawCircleHelper(x+w-r-1, y+r    , r, 2, color);
  drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
  drawCircleHelper(x+r    , y+h-r-1, r, 8, color);
}
void fillRoundRect(unsigned int8 x, unsigned int8 y, unsigned int8 w, unsigned int8 h, unsigned int8 r, unsigned int16 color) {
  fillRect(x+r, y, w-2*r, h, color);
  fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
  fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
}
void drawTriangle(signed int16 x0, signed int16 y0, signed int16 x1, signed int16 y1, signed int16 x2, signed int16 y2, unsigned int16 color) {
  drawLine(x0, y0, x1, y1, color);
  drawLine(x1, y1, x2, y2, color);
  drawLine(x2, y2, x0, y0, color);
}
void fillTriangle(signed int16 x0, signed int16 y0, signed int16 x1, signed int16 y1, signed int16 x2, signed int16 y2, unsigned int16 color) {
  signed int16 a, b, y, last, dx01, dy01, dx02, dy02, dx12, dy12, sa, sb;
  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1) {
    _swap(y0, y1); _swap(x0, x1);
  }
  if (y1 > y2) {
    _swap(y2, y1); _swap(x2, x1);
  }
  if (y0 > y1) {
    _swap(y0, y1); _swap(x0, x1);
  }
  if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
    a = b = x0;
    if(x1 < a)      a = x1;
    else if(x1 > b) b = x1;
    if(x2 < a)      a = x2;
    else if(x2 > b) b = x2;
    drawFastHLine(a, y0, b-a+1, color);
    return;
  }
    dx01 = x1 - x0;
    dy01 = y1 - y0;
    dx02 = x2 - x0;
    dy02 = y2 - y0;
    dx12 = x2 - x1;
    dy12 = y2 - y1;
    sa   = 0;
    sb   = 0;
  if(y1 == y2) last = y1;   // Include y1 scanline
  else         last = y1-1; // Skip it
  for(y=y0; y<=last; y++) {
    a   = x0 + sa / dy01;
    b   = x0 + sb / dy02;
    sa += dx01;
    sb += dx02;
    /* longhand:
    a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) _swap(a,b);
    drawFastHLine(a, y, b - a + 1, color);
  }
  // For lower part of triangle, find scanline crossings for segments
  // 0-2 and 1-2.  This loop is skipped if y1=y2.
  sa = dx12 * (y - y1);
  sb = dx02 * (y - y0);
  for(; y<=y2; y++) {
    a   = x1 + sa / dy12;
    b   = x0 + sb / dy02;
    sa += dx12;
    sb += dx02;
    /* longhand:
    a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) _swap(a,b);
    drawFastHLine(a, y, b-a+1, color);
  }
}
void drawChar(unsigned int8 x, unsigned int8 y, unsigned int8 c, unsigned int16 color, unsigned int16 bg,  unsigned int8 size){
  int8 i, j;
  if((x >= _width) || (y >= _height))
    return;
  if(size < 1) size = 1;
  if((c < ' ') || (c > '~'))
    c = '?';
  for(i=0; i<5; i++ ) {
    unsigned int8 line;
    if(c < 'S')
      line = font[(c - 32)*5 + i];
    else
      line = font2[(c - 'S')*5 + i];
    for(j=0; j<7; j++, line >>= 1) {
      if(line & 0x01) {
        if(size == 1) PIXEL_CIZ(x+i, y+j, color);
        else          fillRect(x+(i*size), y+(j*size), size, size, color);
      }
      else if(bg != color) {
           if(size == 1) PIXEL_CIZ(x+i, y+j, bg);
           else          fillRect(x+i*size, y+j*size, size, size, bg);
        }
    }
  }
}
void setTextWrap(int1 w){
  wrap = w;
}
void YAZI_YAZ(unsigned int8 x, unsigned int8 y, char *_text, unsigned int16 color, unsigned int16 bg, unsigned int8 size){
  unsigned int8 cursor_x, cursor_y;
  unsigned int16 textsize, i;
  cursor_x = x, cursor_y = y;
  textsize = strlen(_text);
  for(i = 0; i < textsize; i++){
    if(wrap && ((cursor_x + size * 5) > _width)){
      cursor_x = 0;
      cursor_y = cursor_y + size * 7 + 3 ;
      if(cursor_y > _height) cursor_y = _height;
      if(_text[i] == 0x20) goto _skip; }
    drawChar(cursor_x, cursor_y, _text[i], color, bg, size);
    cursor_x = cursor_x + size * 6;
    if(cursor_x > _width) cursor_x = _width;
    _skip:;}
}
void invertDisplay(int1 i) {
  if(i)
     KOMUT_YAZ(ST7735_INVON);
  else
     KOMUT_YAZ(ST7735_INVOFF);
}
void setScrollDefinition(unsigned int8 top_fix_height, unsigned int8 bottom_fix_height, int1 _scroll_direction){
  unsigned int8 scroll_height;
  scroll_height = _height - top_fix_height - bottom_fix_height;
   KOMUT_YAZ(ST7735_VSCRDEF);
  BILGI_YAZ(0x00);
  BILGI_YAZ(top_fix_height);
  BILGI_YAZ(0x00);
  BILGI_YAZ(scroll_height);
  BILGI_YAZ(0x00);
  BILGI_YAZ(bottom_fix_height);
   KOMUT_YAZ(ST7735_MADCTL);
  if(_scroll_direction){
    if(_tft_type == 0){
      BILGI_YAZ(0xD8);
    }
    if(_tft_type == 1){
      BILGI_YAZ(0xD0);
    }
    if(_tft_type == 2){
      BILGI_YAZ(0x18);
    }
  }
  else{
    if(_tft_type == 0){
      BILGI_YAZ(0xC8);
    }
    if(_tft_type == 1){
      BILGI_YAZ(0xC0);
    }
    if(_tft_type == 2){
      BILGI_YAZ(0x08);
    }
  }
}
void VerticalScroll(unsigned int8 _vsp) {
   KOMUT_YAZ(ST7735_VSCRSADD);
  BILGI_YAZ(0x00);
  BILGI_YAZ(_vsp);
}
void NormalDisplay(){
   KOMUT_YAZ(ST7735_NORON);
}
int16 Color565(int16 r, int16 g, int16 b){           // Convert 24-bit color to 16-bit color
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void TFT_GreenTab_Initialize(){
  output_high(TFT_CS);
  output_low(TFT_DC);
  output_drive(TFT_CS);
  output_drive(TFT_DC);
  #ifndef TFT_SPI_HARDWARE
    output_low(TFT_CLK);
    output_low(TFT_DATA);
    output_drive(TFT_CLK);
    output_drive(TFT_DATA);
  #else
    SETUP_SPI(SPI_MASTER | SPI_H_TO_L | SPI_CLK_DIV_4 | SPI_XMIT_L_TO_H);
  #endif
  Rcmd1();
  Rcmd2green();
  Rcmd3();
  colstart = 2;
  rowstart = 1;
  _tft_type = 0;
}
void TFT_RedTab_Initialize(){
  output_high(TFT_CS);
  output_low(TFT_DC);
  output_drive(TFT_CS);
  output_drive(TFT_DC);
  #ifndef TFT_SPI_HARDWARE
    output_low(TFT_CLK);
    output_low(TFT_DATA);
    output_drive(TFT_CLK);
    output_drive(TFT_DATA);
  #else
    SETUP_SPI(SPI_MASTER | SPI_H_TO_L | SPI_CLK_DIV_4 | SPI_XMIT_L_TO_H);
  #endif
  Rcmd1();
  Rcmd2red();
  Rcmd3();
  _tft_type = 0;
}
void TFT_BlackTab_Initialize(){
  output_high(TFT_CS);
  output_low(TFT_DC);
  output_drive(TFT_CS);
  output_drive(TFT_DC);
  #ifndef TFT_SPI_HARDWARE
    output_low(TFT_CLK);
    output_low(TFT_DATA);
    output_drive(TFT_CLK);
    output_drive(TFT_DATA);
  #else
    SETUP_SPI(SPI_MASTER | SPI_H_TO_L | SPI_CLK_DIV_4 | SPI_XMIT_L_TO_H);
  #endif
  Rcmd1();
  Rcmd2red();
  Rcmd3();
   KOMUT_YAZ(ST7735_MADCTL);
  BILGI_YAZ(0xC0);
  _tft_type = 1;
}
void TFT_ST7735B_Initialize(){
  output_high(TFT_CS);
  output_low(TFT_DC);
  output_drive(TFT_CS);
  output_drive(TFT_DC);
  #ifndef TFT_SPI_HARDWARE
    output_low(TFT_CLK);
    output_low(TFT_DATA);
    output_drive(TFT_CLK);
    output_drive(TFT_DATA);
  #else
    SETUP_SPI(SPI_MASTER | SPI_H_TO_L | SPI_CLK_DIV_4 | SPI_XMIT_L_TO_H);
  #endif
  Bcmd();
  _tft_type = 2;
}

#if defined (DRAW_BMP_FROM_MMCSD_CARD)                       // Additional code for drawing BMP image files from MMC/SD card
#ifndef pixel_buffer
#define pixel_buffer  10
#endif
int1 bmpDraw(int8 x, int8 y, int8 *bmpname){
  int1 ec = 0, padding = 0;
  int8 bmpdata[pixel_buffer*3],
       planes, depth, r, g, b, col, row;
  int16 i, buffer=pixel_buffer*3, format, width, height, color;
  int32 offset, compression, bmp_size, row_size, padding_factor;
  if((x >= _width) || (y >= _height))
    return 1;
  if(fat16_open_file(bmpname) != 0)
    return 1;
  ec |= sdcard_read_byte(address_pointer + 1, &format);
  format <<= 8;
  ec |= sdcard_read_byte(address_pointer, &format);
  if(format != 0x4D42)                                             // BMP file format signature
    return 1;                                                      // Return error
  ec |= sdcard_read_byte(address_pointer + 0x0D, &offset);
  offset <<= 8;
  ec |= sdcard_read_byte(address_pointer + 0x0C, &offset);
  offset <<= 8;
  ec |= sdcard_read_byte(address_pointer + 0x0B, &offset);
  offset <<= 8;
  ec |= sdcard_read_byte(address_pointer + 0x0A, &offset);
  ec |= sdcard_read_byte(address_pointer + 0x13, &width);
  width <<= 8;
  ec |= sdcard_read_byte(address_pointer + 0x12, &width);
  ec |= sdcard_read_byte(address_pointer + 0x17, &height);
  height <<= 8;
  ec |= sdcard_read_byte(address_pointer + 0x16, &height);
  ec |= sdcard_read_byte(address_pointer + 0x1A, &planes);
  ec |= sdcard_read_byte(address_pointer + 0x1C, &depth);
  ec |= sdcard_read_byte(address_pointer + 0x21, &compression);
  compression <<= 8;
  ec |= sdcard_read_byte(address_pointer + 0x20, &compression);
  compression <<= 8;
  ec |= sdcard_read_byte(address_pointer + 0x1f, &compression);
  compression <<= 8;
  ec |= sdcard_read_byte(address_pointer + 0x1e, &compression);
  if(ec != 0 || compression != 0 || depth != 24 || planes != 1)
    return 1;
  bmp_size = file_size - offset;                                // bmp_size: BMP image raw size
  row_size = bmp_size/height;                                   // row_size: number of bytes per row
  if((x + width  - 1) >=  _width){                              // _width is the TFT screen width
    width = _width  - x;
    padding = 1;                                                //Padding = 1 ==> only upper left part will be displayed
    padding_factor = width / pixel_buffer;
    if(width % pixel_buffer)
      padding_factor++;
    padding_factor *= buffer;
  }
  if((y + height - 1) >= _height){                              // _height is the TFT screen height
    offset += row_size * (height - _height + y);                // Only upper part will be displayed
    height = _height - y;
  }
  file_pointer     = offset;
  address_pointer += offset;
  i = buffer;
  for(row = height; row > 0; row--){
  for(col = 0; col < width; col++){
    if(i >= buffer){
      i = 0;
      if(fat16_read_data(buffer, bmpdata) != 0)
        return 1;
    }
    b = bmpdata[i++];
    g = bmpdata[i++];
    r = bmpdata[i++];
    color = Color565(r, g, b);
    drawPixel(x + col, y + row, color);
  }
    if(padding == 1){
      i = buffer;
      file_pointer    += row_size - padding_factor;
      address_pointer += row_size - padding_factor;
    }
  }
  return 0;
}
#endif
