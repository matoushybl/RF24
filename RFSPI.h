//
// Created by matous on 4/18/20.
//

#ifndef PWM_RFSPI_H
#define PWM_RFSPI_H


#include <cstdint>

class RFSPI {
public:

/**
	* SPI constructor
	*/
    RFSPI();

/**
* Start SPI
*/
    void begin();

/**
* Transfer a single byte
* @param tx_ Byte to send
* @return Data returned via spi
*/
    uint8_t transfer(uint8_t tx_);

/**
* Transfer a buffer of data
* @param tbuf Transmit buffer
* @param rbuf Receive buffer
* @param len Length of the data
*/
    void transfernb(char* tbuf, char* rbuf, uint32_t len);

/**
* Transfer a buffer of data without an rx buffer
* @param buf Pointer to a buffer of data
* @param len Length of the data
*/
    void transfern(char* buf, uint32_t len);

    virtual ~ RFSPI();

private:
};


#endif //PWM_RFSPI_H
