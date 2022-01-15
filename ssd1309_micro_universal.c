/* 
 * File:   ssd1309_micro_universal
 * Author: Marco Ortali
 *
 * Created on 14 gen 2022, 21.36
 */

#include "ssd1309_micro_universal.h"
#include "ssd1309_micro_universal_fonts.h"
#include "ssd1309_micro_universal_softi2c.h"

//i2c pins defined in ssd1309_micro_universal_softspi.h

//8BIT Address!
#define I2C_ADDRESS 0x78

const uint8_t ssd1306_init_sequence [32] = {// Initialization Sequence
    0xAE,
    0xD5, 0x80, // Set display clock divide ratio/oscillator frequency, set divide ratio
    0xA8, 0x3F, // Set multiplex ratio (1 to 64) ... (height - 1)
    0xD3, 0x00, // Set display offset. 00 = no offset
    0x40 | 0x00, // Set start line address, at 0.
    0x8D, 0x14, // Charge Pump Setting, 14h = Enable Charge Pump
    0x20, 0x00, // Set Memory Addressing Mode - 00=Horizontal, 01=Vertical, 10=Page, 11=Invalid
    0xA0 | 0x01, // Set Segment Re-map
    0xC8, // Set COM Output Scan Direction
    0xDA, 0x12, // Set COM Pins Hardware Configuration - 128x32:0x02, 128x64:0x12
    0x81, 0xCF, // Set contrast control register
    0xD9, 0xF1, // Set pre-charge period (0x22 or 0xF1)
    0xDB, 0x40, // Set Vcomh Deselect Level - 0x00: 0.65 x VCC, 0x20: 0.77 x VCC (RESET), 0x30: 0.83 x VCC
    0x2E, // Deactivate Scroll command
    0xA4, // Entire Display ON (resume) - output RAM to display
    0xA6, // Set Normal/Inverse Display mode. A6=Normal; A7=Inverse
    0x22, 0x00, 0x3f, // Set Page Address (start,end)
    0x21, 0x00, 0x7f, // Set Column Address (start,end)
    0xAF // Set Display ON/OFF - AE=OFF, AF=ON
};

void i2c_init() {
    //TODO: Eventually if you want to use hw i2c, put initialization here.
}

void i2c_send_byte(uint8_t dat) {
    I2C_Start();
    I2C_WriteByte(dat);
    I2C_Stop();
}

void write_command(uint8_t cmd) {
    I2C_Start();
    I2C_WriteByte(I2C_ADDRESS);
    I2C_WriteByte(0x00);
    I2C_WriteByte(cmd);
    I2C_Stop();
}

void begin_data() {
    I2C_Start();
    I2C_WriteByte(I2C_ADDRESS);
    I2C_WriteByte(0x40);
}

void i2c_oled_setpos(uint8_t x, uint8_t y) {
    I2C_Start();
    I2C_WriteByte(I2C_ADDRESS);
    I2C_WriteByte(0x00); 

    I2C_WriteByte(0xb0 + y);
    I2C_WriteByte(((x & 0xf0) >> 4) | 0x10); 
    I2C_WriteByte((x & 0x0f) | 0x01);

    I2C_Stop();
}

void i2c_oled_fillScreen(uint8_t fill_Data) {
    uint8_t m, n;
    for (m = 0; m < 8; m++) {
        write_command(0xb0 + m); 
        write_command(0x00);
        write_command(0x00);
        begin_data();
        for (n = 0; n < 128; n++) {
            I2C_WriteByte(fill_Data);
        }
        I2C_Stop();
    }
}

void i2c_oled_clear(){
    i2c_oled_fillScreen(0);
}


void i2c_oled_out(uint8_t x, uint8_t y, char ch[]) {
    uint8_t c, i, j = 0;
    while (ch[j] != '\0') {
        c = ch[j] - 32;
        if (x > 126) {
            x = 0;
            y++;
        }
        i2c_oled_setpos(x, y);
        begin_data();
        for (i = 0; i < 6; i++) {
            I2C_WriteByte(font6x8[c * 6 + i]);
        }
        I2C_Stop();
        x += 6;
        j++;
    }
}

void i2c_oled_big_out(uint8_t x, uint8_t y, char ch[]) {
    uint8_t c = 0, i = 0, j = 0;
    while (ch[j] != '\0') {
        c = ch[j] - 32;
        if (x > 120) {
            x = 0;
            y += 2;
        }
        i2c_oled_setpos(x, y);
        begin_data();
        for (i = 0; i < 8; i++) {
            I2C_WriteByte(font8X16[c * 16 + i]);
        }
        I2C_Stop();
        i2c_oled_setpos(x, y + 1);
        begin_data();
        for (i = 0; i < 8; i++) {
            I2C_WriteByte(font8X16[c * 16 + i + 8]);
        }
        I2C_Stop();
        x += 8;
        j++;
    }
}

void i2c_oled_bitmap(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, const char BMP[]) {
    unsigned int j = 0;
    uint8_t x, y;

    if (y1 % 8 == 0)
        y = y1 / 8;
    else
        y = y1 / 8 + 1;
    for (y = y0; y < y1; y++) {
        i2c_oled_setpos(x0, y);
        begin_data();
        for (x = x0; x < x1; x++) {
            I2C_WriteByte(BMP[j++]);
        }
        I2C_Stop();
    }
}

void i2c_oled_init() {
    for (uint8_t k = 0; k < 32; k++) {
        write_command(ssd1306_init_sequence[k]);
    }
}