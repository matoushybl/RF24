//
// Created by matous on 4/18/20.
//

#include "RFSPI.h"
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

RFSPI::RFSPI() {
}

void RFSPI::begin() {
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_SPI1);
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO4);
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO0 | GPIO1 | GPIO2 | GPIO3  | GPIO5 | GPIO6 | GPIO7);
    gpio_set_af(GPIOA, GPIO_AF0, GPIO5 | GPIO6 | GPIO7);


    gpio_set(GPIOA, GPIO4);
    SPI1_CR1 &= ~SPI_CR1_SPE;
    SPI1_CR1 = SPI_CR1_MSTR | SPI_CR1_MSBFIRST | SPI_CR1_SSM | SPI_CR1_SSI | (SPI_CR1_BR_FPCLK_DIV_8 << 3);
    SPI1_CR2 = SPI_CR2_DS_8BIT | SPI_CR2_FRXTH;

    SPI1_CR1 |= SPI_CR1_SPE;
}

uint8_t RFSPI::transfer(uint8_t tx_) {
    SPI1_DR8 = tx_;
    while ((SPI1_SR & SPI_SR_RXNE) == 0);
    return SPI1_DR8;
}

void RFSPI::transfernb(char *tbuf, char *rbuf, uint32_t len) {
    for (uint32_t i = 0; i < len; ++i) {
        rbuf[i] = transfer(tbuf[i]);
    }
}

void RFSPI::transfern(char *buf, uint32_t len) {
    for (uint32_t i = 0; i < len; ++i) {
        transfer(buf[i]);
    }
}

RFSPI::~RFSPI() {

}
