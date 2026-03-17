#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/i2c.h"
#include "ssd1306.h"

#define WIFI_SSID      "Lapcom"
#define WIFI_PASSWORD  "12345678"
#define WIFI_TIMEOUT_S 20

#define I2C_PORT    i2c1
#define I2C_SDA_PIN 14
#define I2C_SCL_PIN 15
#define OLED_ADDR   0x3C
#define OLED_WIDTH  128
#define OLED_HEIGHT 64

static ssd1306_t oled;

static void oled_print(const char *lines[], int count) {
    ssd1306_clear(&oled);
    for (int i = 0; i < count; i++)
        ssd1306_draw_string(&oled, 0, i * 12, 1, lines[i]);
    ssd1306_show(&oled);
}

static const char *link_str(int s) {
    switch (s) {
        case CYW43_LINK_DOWN:    return "DOWN";
        case CYW43_LINK_JOIN:    return "JOINING";
        case CYW43_LINK_NOIP:    return "NO IP";
        case CYW43_LINK_UP:      return "UP";
        case CYW43_LINK_FAIL:    return "FAIL";
        case CYW43_LINK_NONET:   return "NO NET";
        case CYW43_LINK_BADAUTH: return "BADAUTH";
        default:                 return "UNKNOWN";
    }
}

int main(void) {
    stdio_init_all();

    i2c_init(I2C_PORT, 400000);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);

    ssd1306_init(&oled, OLED_WIDTH, OLED_HEIGHT, OLED_ADDR, I2C_PORT);

    const char *b[] = {"BitDogLab", "Iniciando..."};
    oled_print(b, 2);
    sleep_ms(1000);

    const char *w[] = {"Init WiFi..."};
    oled_print(w, 1);

    if (cyw43_arch_init()) {
        const char *e[] = {"ERRO:", "cyw43 init fail"};
        oled_print(e, 2);
        while (true) tight_loop_contents();
    }

    cyw43_arch_enable_sta_mode();

    cyw43_arch_wifi_connect_async(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK);

    for (int i = 0; i < WIFI_TIMEOUT_S; i++) {
        cyw43_arch_poll();
        int st = cyw43_tcpip_link_status(&cyw43_state, CYW43_ITF_STA);

        char l2[22], l3[22];
        snprintf(l2, sizeof(l2), "Rede: %s", WIFI_SSID);
        snprintf(l3, sizeof(l3), "%s %ds", link_str(st), i);
        const char *p[] = {"Conectando...", l2, l3};
        oled_print(p, 3);

        if (st == CYW43_LINK_UP) {
            uint8_t *ip = (uint8_t *)&cyw43_state.netif[0].ip_addr.addr;
            char ip_s[22];
            snprintf(ip_s, sizeof(ip_s), "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
            const char *ok[] = {"WiFi OK!", WIFI_SSID, ip_s};
            oled_print(ok, 3);
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
            while (true) { cyw43_arch_poll(); sleep_ms(100); }
        }

        if (st == CYW43_LINK_FAIL || st == CYW43_LINK_BADAUTH || st == CYW43_LINK_NONET) {
            char er[22];
            snprintf(er, sizeof(er), "Erro: %s", link_str(st));
            const char *fail[] = {"ERRO WiFi!", er, "Verifique SSID"};
            oled_print(fail, 3);
            while (true) tight_loop_contents();
        }

        sleep_ms(1000);
    }

    const char *to[] = {"Timeout!", "Sem resposta", "do roteador"};
    oled_print(to, 3);
    while (true) tight_loop_contents();
}
