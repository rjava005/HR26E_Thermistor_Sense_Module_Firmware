#include "STM32_CAN.h"

static CAN_message_t CAN_outMsg;
const int analogInput = PA0;  // ADC pin

STM32_CAN Can(CAN1, ALT);     // PB8 = RX, PB9 = TX

void SendData(uint16_t voltage_mV) {
  // Pack the 32-bit voltage value into 4 bytes
  CAN_outMsg.buf[0] = (voltage_mV & 0xFF);
  CAN_outMsg.buf[1] = ((voltage_mV >> 8) & 0xFF);
  CAN_outMsg.buf[2] = 'm';

  CAN_outMsg.buf[3] = 'V';
  CAN_outMsg.buf[4] = 'o';
  CAN_outMsg.buf[5] = 'l';
  CAN_outMsg.buf[6] = 't';
  CAN_outMsg.buf[7] = 's';

  Can.write(CAN_outMsg);
}

void setup() {
  pinMode(PB2, OUTPUT);   // Just to have a test pin if needed
  Serial.begin(115200);   // Serial monitor
  delay(1000);
  Serial.println("Starting ADC + CAN test...");

  // Initialize CAN at 500 kbps
  Can.begin(false);
  Can.setBaudRate(500000);

  CAN_outMsg.id = 0x076;
  CAN_outMsg.len = 8;

  analogReadResolution(12); // 12-bit ADC for Blue Pill
}

void loop() {

  uint16_t adcValue = analogRead(analogInput);

  float voltage = (adcValue * 3.3) / 4095.0;
  uint16_t voltage_mV = voltage * 1000; 

  Serial.print("ADC: ");
  Serial.print(adcValue);
  Serial.print(" Voltage: ");
  Serial.print(voltage_mV);
  Serial.println(" mV");

  SendData(voltage_mV);
}
