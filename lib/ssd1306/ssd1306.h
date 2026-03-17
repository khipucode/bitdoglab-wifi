#ifndef SSD1306_H
#define SSD1306_H

#include "hardware/i2c.h"
#include <stdint.h>
#include <stdbool.h>

// ── Dimensões suportadas ───────────────────────────────────
#define SSD1306_BUF_LEN(w, h) ((w) * (h) / 8)

typedef struct {
    uint8_t  width;
    uint8_t  height;
    uint8_t  addr;
    i2c_inst_t *i2c;
    uint8_t  buf[128 * 64 / 8];   // tamanho máximo
} ssd1306_t;

// ── API pública ────────────────────────────────────────────
void ssd1306_init(ssd1306_t *oled, uint8_t width, uint8_t height,
                  uint8_t addr, i2c_inst_t *i2c);
void ssd1306_clear(ssd1306_t *oled);
void ssd1306_show(ssd1306_t *oled);
void ssd1306_draw_pixel(ssd1306_t *oled, int x, int y, bool on);
void ssd1306_draw_char(ssd1306_t *oled, int x, int y, int scale, char c);
void ssd1306_draw_string(ssd1306_t *oled, int x, int y, int scale, const char *str);

#endif // SSD1306_H
