#include "STM32_CAN.h"

// CAN message structures (visualized in the form of arrays)
static CAN_message_t CAN_outMsg1;
static CAN_message_t CAN_outMsg2;

const int analogInput = PA1;  // ADC pin
const int hertzDelay = 100;  // time to wait between sends
const int onboardLED = PB2;
const char subpackID = 'S1';  // choose any ID from S1 - S6
float adcValue = 1;
float temperature = 0;

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
      CAN_outMsg1.id = 0x11; 
      CAN_outMsg2.id = 0x12; 
      break; 
    case 'S2': 
      CAN_outMsg1.id = 0x21; 
      CAN_outMsg2.id = 0x22; 
      break; 
    case 'S3': 
      CAN_outMsg1.id = 0x31;
      CAN_outMsg2.id = 0x32; 
      break; 
    case 'S4': 
      CAN_outMsg1.id = 0x41; 
      CAN_outMsg2.id = 0x42; 
      break; 
    case 'S5': 
      CAN_outMsg1.id = 0x51; 
      CAN_outMsg2.id = 0x52; 
      break; 
    case 'S6': 
      CAN_outMsg1.id = 0x61; 
      CAN_outMsg2.id = 0x62; 
      break; 
  }

  CAN_outMsg1.len = CAN_outMsg2.len = 6;
  Serial.println("Setup complete. Sending bogus multiplexer values over CAN...");
}

void loop() {
  // Toggle LED
  digitalWrite(onboardLED, !digitalRead(onboardLED));

 adcValue = analogRead(analogInput) * (3.3/1023.0);

  temperature = (1.0 / ((1.0/298.15) + (1.0/3435.0) * log(((10000.0 * (3.3 / adcValue)) - 10000.0) / 10000.0))) - 273.15;
  // temperature = (1/298.15) + (1/3435) * log(10000 * 3.3 / 1.0);
  //temperature = log(10000.0 * (3.3 / 1.0));
  for (int i = 0; i < 6; i++) {
    CAN_outMsg1.buf[i] = (uint8_t)temperature;
    // CAN_outMsg2.buf[i] = (uint8_t)temperature;
  }
  Serial.print("ADC Value: ");
  Serial.println(adcValue);
  Serial.print("Temperature: ");
  Serial.println(temperature);

  Can.write(CAN_outMsg1);
  // Can.write(CAN_outMsg2);
  delay(hertzDelay);

}
