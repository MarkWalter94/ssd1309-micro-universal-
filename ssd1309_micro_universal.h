/* 
 * File:   ssd1309_micro_universal
 * Author: Marco Ortali
 *
 * Created on 14 gen 2022, 21.36
 */

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

    /**
     * @brief Initializes the display.
     */
    void i2c_oled_init();

    /**
     * @brief Writes a command to the display.
     * 
     * @param cmd command to write.
     */
    void write_command(uint8_t cmd);

    /**
     * @brief Sets the position of the display caret.
     * 
     * @param x x address.
     * @param y y address.
     */
    void i2c_oled_setpos(uint8_t x, uint8_t y);

    /**
     * @brief fills the lcd screen.
     * 
     * @param fill_Data 
     */
    void i2c_oled_fillScreen(uint8_t fill_Data);

    /**
     * @brief Clears the screen.
     * 
     */
    void i2c_oled_clear();

    /**
     * @brief Puts a string to the display at a defined position.
     * 
     * @param x x pos.
     * @param y y pos.
     * @param ch string.
     */
    void i2c_oled_out(uint8_t x, uint8_t y, char ch[]);

    /**
     * @brief Same as see i2c_oled_out but with bigger font.
     * 
     * @param x x pos.
     * @param y y pos.
     * @param ch string.
     */
    void i2c_oled_big_out(uint8_t x, uint8_t y, char ch[]);

    /**
     * @brief Puts a bitmap to the display.
     * 
     * @param x0 starting pos x.
     * @param y0 starting pos y.
     * @param x1 ending pos x.
     * @param y1 ending pos y.
     * @param BMP bitmap matrix.
     */
    void i2c_oled_bitmap(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, const char BMP[]);

#ifdef __cplusplus
}
#endif