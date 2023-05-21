#include "i2c.hpp"

#define DEV_ADR 0x09
#define PIN_SDA 2
#define PIN_SCL 3

I2C i2c;

// Some memory for testing
uint8_t data[1] = {0};

void setup() {
  // put your setup code here, to run once:
  i2c.begin(PIN_SDA, PIN_SCL);
}

void loop() {
  data[0] = !data[0];
  i2c.write_byte_data(DEV_ADR, data, 1);
  delay(500);
}
