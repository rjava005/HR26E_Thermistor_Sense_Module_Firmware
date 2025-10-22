# HR26E_Thermistor_Sense_Module_Firmware
Main Repository for storing STM32F1 firmware files for reading ADC thermistor voltages and converting to cell temp and sending packaged data to CAN bus.

This project uses a STM32F1 BluePill, a Waveshare SN65HVD230 CAN Tranceiver, and a FT232RL USB to TTL Serial Converter. 

The module will use a multiplexor to select various thermistor inputs, which the BluePill will read and transmit over CANBus. 

This repository uses the STM32_CAN repository from pazi88 in order to interface with the BluePill's CAN Controller. Link: https://github.com/pazi88/STM32_CAN