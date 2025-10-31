#include "STM32_CAN.h"

// CAN message structures (visualized in the form of arrays)
static CAN_message_t CAN_outMsg1;
static CAN_message_t CAN_outMsg2;

const int hertzDelay = 100;  // time to wait between sends
const int onboardLED = PB2;
const char subpackID = 'S1';  // choose any ID from S1 - S6

STM32_CAN Can(CAN1, ALT);  // PB8 = RX, PB9 = TX

uint8_t muxData1[6] = {10,20,30,40,50,60};
uint8_t muxData2[6] = {70,80,90,100,110,120};

void setup() {
  pinMode(onboardLED, OUTPUT);
  Serial.begin(115200);
  Serial.println("Starting Multiplexer simulation...");

  Can.begin(false);
  Can.setBaudRate(500000);

  // set up CAN id according to subpackID
  switch(subpackID) {
    case 'S1': 
      CAN_outMsg1.id = 0x101; 
      CAN_outMsg2.id = 0x102; 
      break; 
    case 'S2': 
      CAN_outMsg1.id = 0x201; 
      CAN_outMsg2.id = 0x202; 
      break; 
    case 'S3': 
      CAN_outMsg1.id = 0x301;
      CAN_outMsg2.id = 0x302; 
      break; 
    case 'S4': 
      CAN_outMsg1.id = 0x401; 
      CAN_outMsg2.id = 0x402; 
      break; 
    case 'S5': 
      CAN_outMsg1.id = 0x501; 
      CAN_outMsg2.id = 0x502; 
      break; 
    case 'S6': 
      CAN_outMsg1.id = 0x601; 
      CAN_outMsg2.id = 0x602; 
      break; 
  }

  CAN_outMsg1.len = CAN_outMsg2.len = 6;

  for (int i = 0; i < 6; i++) {
    CAN_outMsg1.buf[i] = muxData1[i];
    CAN_outMsg2.buf[i] = muxData2[i];
  }

  Serial.println("Setup complete. Sending bogus multiplexer values over CAN...");
}

void loop() {
  // Toggle LED
  digitalWrite(onboardLED, !digitalRead(onboardLED));

  Can.write(CAN_outMsg1);
  delay(hertzDelay);
  Can.write(CAN_outMsg2);
  delay(hertzDelay);

}