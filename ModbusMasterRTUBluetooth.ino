#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

#include <ModbusMaster.h>
int errorcnt,oldErrorcnt =0;
int cycle;
int moisture, temperature, conductivity;
#define RS485LED 22

#define RXD2 16
#define TXD2 17

BluetoothSerial SerialBT;
ModbusMaster node;

void setup() {
  SerialBT.begin("ESP32Sensor");
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2); //using serial 2 to read the signal from MAX13487E
  Serial.println("The ESP32 device started, now you can pair it with bluetooth!");
  node.begin(254, Serial2);
  pinMode(RS485LED,OUTPUT);
}

void loop()
{
  uint8_t result;  

  // Read 16 registers starting at 0x3100)
  result = node.readHoldingRegisters(0x001, 8);
  if (result == node.ku8MBSuccess)
  {
    moisture=node.getResponseBuffer(0)/100;
    temperature=node.getResponseBuffer(3)/100;
    conductivity=node.getResponseBuffer(6);
    
    Serial.println("------------");
    Serial.println("Moisture: " + String(moisture) + " %");
    Serial.println("Temperature: " + String(temperature) + " 'C");
    Serial.println("Conductivity: " + String(conductivity) + " uS/cm");
    SerialBT.println("Moisture: " + String(moisture) + " %");
    SerialBT.println("Temperature: " + String(temperature) + " C");
    SerialBT.println("Conductivity: " + String(conductivity) + " uS/cm");
    digitalWrite(RS485LED,HIGH);
    Serial.print("ERROR count: ");
    Serial.println(errorcnt);    
    Serial.print("cycle: ");
    Serial.println(cycle);  
    cycle++;
  }
  else {
    errorcnt++;cycle++;
    Serial.println("ERROR count: " + String(errorcnt));
    digitalWrite(RS485LED,LOW);
  }
  delay(5000);
}
