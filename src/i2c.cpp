#include "I2C.hpp"

void I2C::begin(uint8_t sda, uint8_t scl)
{
  _sda = sda;
  _scl = scl;

  SDA_HIGH;
  SCL_HIGH;
}

uint8_t I2C::write_byte_data(uint8_t adr, uint8_t *data, uint8_t len){
  transmission_begin(adr);
  uint8_t ret = transmission_write(data, len);
  transmission_end();

  return ret;
}

void I2C::transmission_begin(uint8_t adr)
{
  _adr = adr;
  start();
}

void I2C::transmission_end()
{
  _adr = 0;
  stop();
}

uint8_t I2C::transmission_write(uint8_t *data, uint8_t len)
{
  ADR7_AS_WRITE8(_adr);
  send_u8(&_adr);
  uint8_t ret = check_ack();

  for (uint8_t i = 0; i < len; i++)
  {
    if (ret)
      break;

    send_u8(&data[i]);
    ret = check_ack();
  }

  return ret;
}


void I2C::send_u8(uint8_t *data)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if ((0x80 >> i) & *data)
    {
      SDA_HIGH;
    }
    else
    {
      SDA_LOW;
    }
    scl_tick();
    SDA_LOW;
  }
}

uint8_t I2C::check_ack()
{
  uint8_t ret = 0;

  SDA_HIGH;
  SCL_HIGH;

  delayMicroseconds(SCL_CLOCK_STRECH);
  ret = digitalRead(_sda);

  SCL_LOW;

  return ret;
}

void I2C::send_ack()
{
  SDA_LOW;
  scl_tick();
  SDA_HIGH;
}

void I2C::scl_tick()
{
  SCL_HIGH;
  delayMicroseconds(SCL_CLOCK_STRECH);
  SCL_LOW;
}

void I2C::start()
{
  SDA_LOW;
  SCL_LOW;
}

void I2C::stop()
{
  SDA_LOW;
  SCL_HIGH;
  SDA_HIGH;
}
