#ifndef I2C_H_
#define I2C_H_

#include "Arduino.h"

class I2C
{
    #define SCL_CLOCK_STRECH 10

    #define SDA_HIGH pinMode(_sda, INPUT);
    #define SDA_LOW  pinMode(_sda, OUTPUT);

    #define SCL_HIGH pinMode(_scl, INPUT);
    #define SCL_LOW  pinMode(_scl, OUTPUT);

    #define ADR7_AS_WRITE8(A) (A) <<= 1; (A) &= 0xfe;
    #define ADR7_AS_READ8(A)  (A) <<= 1; (A) |= 0x01;

    public:
        void     begin(uint8_t sda = 2, uint8_t scl = 3);
        uint8_t  write_byte_data(uint8_t adr, uint8_t *data, uint8_t len);

    private:
        uint8_t  _sda;
        uint8_t  _scl;
        uint8_t  _adr;

        void     transmission_begin(uint8_t adr);
        void     transmission_end();

        uint8_t  transmission_write(uint8_t *data, uint8_t len);

        void     send_u8(uint8_t *data);

        uint8_t  check_ack();
        void     send_ack();
        void     scl_tick();
        void     stop();
        void     start();
};

#endif
