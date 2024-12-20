#include <Wire.h>

#define cbi(sfr, bit)             (_SFR_BYTE(sfr) &= ~_BV(bit)) // Utilizado para poner a 0 el bit indicado por bit del registro indicado sfr
#define sbi(sfr, bit)             (_SFR_BYTE(sfr) |= _BV(bit))  // Utilizado para poner a 1 el bit indicado por bit del registro indicado sfr
#define relayNumToDigitalPin(P)   ( pgm_read_byte( relay_num_to_digital_pin + (P-1) ) ) // Macro que devuelve el pin correspondiente a un rele

byte data;

void setup() {
 // Wire.setClock(400000);
  Wire.begin(9);                // join i2c bus with address #9
  Wire.setClock(400000);
  Wire.onReceive(BlinkLED); // register event
  for (int i = 1; i <= 22; i++){
    uint8_t num_pin = relayNumToDigitalPin(i);
    digitalWrite(num_pin, LOW);
  }
}


byte I2C_OnOff;                                 

void BlinkLED(int Press)
{
  uint8_t num_pin = relayNumToDigitalPin(1);
  I2C_OnOff = Wire.read();                      
  if (I2C_OnOff == 1)
  {
   digitalWrite(num_pin, HIGH);                 
  }
  else if (I2C_OnOff == 0)
  {
   digitalWrite(num_pin, LOW);                 
  } 
}

void loop() {
  if (Wire.available()==4){
    int relay_number = 0;
    for (int i = 0; i <= 4; i++){
      data = Wire.read();
      for (int y = 0; y <= 8; y++) {
        byte n=(data>>y)&0x01;
        relay_number++;
        if (relay_number < 22){
          uint8_t num_pin = relayNumToDigitalPin(relay_number); // Obtenemos el numero de pin correspondiente al rele
          if (n == 0x01){
            digitalWrite(num_pin, HIGH);
          }
          else {
            digitalWrite(num_pin, LOW);
          }
        } 
      }
    } 
  }
}
