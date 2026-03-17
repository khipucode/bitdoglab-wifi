# BitDogLab — WiFi + OLED (C / Pico SDK)

Conecta a rede WiFi e exibe o IP no display OLED SSD1306.

## Estrutura

```
bitdoglab_wifi/
├── CMakeLists.txt
├── main.c
└── lib/
    └── ssd1306/
        ├── CMakeLists.txt
        ├── ssd1306.h
        └── ssd1306.c
```

## Pré-requisitos

- [pico-sdk](https://github.com/raspberrypi/pico-sdk) instalado
- `cmake`, `ninja` (ou `make`) e arm-none-eabi-gcc no PATH
- Variável de ambiente `PICO_SDK_PATH` apontando para o SDK

```bash
export PICO_SDK_PATH=~/pico/pico-sdk
```

## Compilar

```bash
mkdir build && cd build
cmake .. -G Ninja        # ou apenas: cmake ..
ninja                    # ou: make -j4
```

O arquivo `bitdoglab_wifi.uf2` será gerado em `build/`.

## Gravar na placa

1. Segure o botão **BOOTSEL** da Pico W e conecte o USB.
2. Ela aparece como um drive `RPI-RP2`.
3. Copie o `bitdoglab_wifi.uf2` para o drive.

## Pinagem usada

| Pino | GPIO | Função       |
|------|------|--------------|
| SDA  | GP14 | OLED I2C SDA |
| SCL  | GP15 | OLED I2C SCL |
| —    | —    | WiFi (CYW43) |
