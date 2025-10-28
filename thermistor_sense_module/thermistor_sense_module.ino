#include "STM32_CAN.h"

// CAN message structures
static CAN_message_t CAN_outMsg1;
static CAN_message_t CAN_outMsg2;

// hertz delay constant
const int hertzDelay = 100;

/* pin setup 
* PA0 - PA3 connect to gpio to S0-S3 channel selectors on multiplexer, need to be configured as digital outputs
* PA4 is the enable bit for the mux (whatever that means)
*/
const int analogInput = PA0;  // ADC pin
const int onboardLED =  PB2;

// choose between s1-s6
const char subpackID = 'S1';

STM32_CAN Can(CAN1, ALT);     // PB8 = RX, PB9 = TX

void SendData(CAN_message_t msg) {
  // Pack the 32-bit voltage value into 4 bytes
  // CAN_outMsg.buf[0] = (voltage_mV & 0xFF);
  // CAN_outMsg.buf[1] = ((voltage_mV >> 8) & 0xFF);
  // CAN_outMsg.buf[2] = 'm';

  // CAN_outMsg.buf[3] = 'V';
  // CAN_outMsg.buf[4] = 'o';
  // CAN_outMsg.buf[5] = 'l';
  // CAN_outMsg.buf[6] = 't';
  // CAN_outMsg.buf[7] = 's';

  // Can.write(CAN_outMsg);
}

void setup() {
  pinMode(onboardLED, OUTPUT);   // Just to have a test pin if needed

  Serial.begin(115200);   // Serial monitor
  
  Serial.println("Starting ADC + CAN test...");

  // Initialize CAN at 500 kbps
  Can.begin(false);
  Can.setBaudRate(500000);

  // set up CAN id according to subpackID
  switch(subpackID) {
    case 'S1':
      CAN_outMsg1.id = '0x1S1';
      CAN_outMsg2.id = '0x1S2';
      break;
    case 'S2':
      CAN_outMsg1.id = '0x2S1';
      CAN_outMsg2.id = '0x2S2';
      break;
    case 'S3':
      CAN_outMsg1.id = '0x3S1';
      CAN_outMsg2.id = '0x3S2';
      break;    
    case 'S4':
      CAN_outMsg1.id = '0x4S1';
      CAN_outMsg2.id = '0x4S2';
      break;
    case 'S5':
      CAN_outMsg1.id = '0x5S1';
      CAN_outMsg2.id = '0x5S2';
      break;
    case 'S6':
      CAN_outMsg1.id = '0x6S1';
      CAN_outMsg2.id = '0x6S2';
      break;
  }

  // each module will output 2 can messages, each with length of 6 bytes, one for each temperature
  CAN_outMsg1.len = 6;
  CAN_outMsg2.len = 6;

  // 12-bit ADC for Blue Pill
  analogReadResolution(12); 
}

void loop() {
  uint16_t adcValue = analogRead(analogInput);

  // turn measured voltage into millivolt value
  float voltage = (adcValue * 3.3) / 4095.0;
  uint16_t voltage_mV = voltage * 1000; 
  Serial.print("ADC: ");
  Serial.print(adcValue);
  Serial.print(" Voltage: ");
  Serial.print(voltage_mV);
  Serial.println(" mV");

  // SendData(voltage_mV);

  // todo: pack all of this into a for loop (?)

  // todo: turn measured millivolt value into a temperature reading

  // todo: package temperature reading into message struct


  delay(hertzDelay);
}
