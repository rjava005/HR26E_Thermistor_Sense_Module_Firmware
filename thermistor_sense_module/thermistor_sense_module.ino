#include "STM32_CAN.h"

const int analogInput = PA0;
STM32_CAN Can(CAN1, ALT);

static CAN_message_t CAN_outMsg;

// ---------- SETUP ----------
void setup() {
  pinMode(PB2, OUTPUT);
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting ADC + CAN test...");

  Can.begin(true);
  Can.setBaudRate(500000);

  // Setup CAN message
  CAN_outMsg.id = 0x067;
  CAN_outMsg.len = 8;

  // ADC configuration
  analogReadResolution(12); // 12-bit ADC
}

// ---------- CAN SEND FUNCTION ----------
void SendData(int adcValue) {
  CAN_outMsg.buf[0] = (unsigned char)(adcValue & 0xFF);
  CAN_outMsg.buf[1] = (unsigned char)((adcValue >> 8) & 0xFF);
  CAN_outMsg.buf[2] = (unsigned char)((adcValue >> 16) & 0xFF);

  CAN_outMsg.buf[3] = 'H';
  CAN_outMsg.buf[4] = 'e';
  CAN_outMsg.buf[5] = 'l';
  CAN_outMsg.buf[6] = 'l';
  CAN_outMsg.buf[7] = 'o';

  Can.write(CAN_outMsg);
}

// ---------- LOOP ----------
void loop() {
  int adcValue = analogRead(analogInput);
  float voltage = (adcValue / 4095.0) * 3.3;

  // Print ADC value for validation
  Serial.print("ADC: ");
  Serial.print(adcValue);
  Serial.print("   Voltage: ");
  Serial.print(voltage, 3);
  Serial.println(" V");

  // Send over CAN
  SendData(adcValue);

  delay(10000);
}