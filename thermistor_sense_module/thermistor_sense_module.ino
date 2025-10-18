#include "STM32_CAN.h"

static CAN_message_t CAN_outMsg;
const int analogInput = PA0;

STM32_CAN Can(CAN1, ALT);
// PB8 = RX, PB9 = TX


/* this function is credited to the STM32_CAN github page, with minor edits to remove the counter value.  */
void SendData(int adcValue) 
{
  // first 3 bytes are going to be the packed adcValue
  CAN_outMsg.buf[0] = (unsigned char)(adcValue & 0xFF);
  CAN_outMsg.buf[1] = (unsigned char)((adcValue >> 8) & 0xFF);
  CAN_outMsg.buf[2] = (unsigned char)((adcValue >> 16) & 0xFF);

  // just send hello cuz its cute
  CAN_outMsg.buf[3] = 'H';
  CAN_outMsg.buf[4] = 'e';
  CAN_outMsg.buf[5] = 'l';
  CAN_outMsg.buf[6] = 'l';
  CAN_outMsg.buf[7] = 'o';
  Can.write(CAN_outMsg);
}


void setup() {
  // put your setup code here, to run once:
  pinMode(PB2, OUTPUT);

  Serial.begin(115200);

  Can.begin(true);
  Can.setBaudRate(500000);

  // no filters for now. not expecting to require filters for a module that only sends data
  CAN_outMsg.id = (0x067);
  CAN_outMsg.len = 8;

  // the example put a hardware timer here. save that for later if needed? send thermistor values at a regular hertz

  analogReadResolution(12);
}

void loop() {
  // put your main code here, to run repeatedly:
  SendData(analogRead(analogInput));
}
