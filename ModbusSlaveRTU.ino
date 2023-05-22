#include <SoftwareSerial.h>
#include <ModbusRTUSlave.h>
#include <EEPROM.h>
int eepromAddress1=0;
int eepromAddress2=0;

const byte id = 1;
const unsigned long baud = 9600;
const unsigned int bufSize = 256;
const unsigned int numHoldingRegisters =4 ;
const byte rxPin = 3;
const byte txPin = 4;
byte buf[bufSize];
SoftwareSerial mySerial(rxPin, txPin);
ModbusRTUSlave modbus(mySerial, buf, bufSize);

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float humidity; //very wet soil 810, dry soil 0, (humidity/790)*100
unsigned int percentage_humidity,temperature;
int humidityValue, temperatureValue;

unsigned long target_time = 0L ;
const unsigned long PERIOD = 1000UL;

long holdingRegisterRead(unsigned int address) {
  switch (address) {
    case 0:return percentage_humidity;
    case 1:return temperature;
    case 2:return humidityValue;
    case 3:return temperatureValue;  

  }}

boolean holdingRegisterWrite(word address, word value) {
  switch (address) {
    case 2:humidityValue=value;break;
    case 3:temperatureValue=value;break;
  }return true;
}

void setup() {
  humidityValue=EEPROM.read(1); //5
  temperatureValue=EEPROM.read(2); //10
  Serial.begin(9600);
  sensors.begin();
  mySerial.begin(baud);
  modbus.begin(id, baud);
  modbus.configureHoldingRegisters(numHoldingRegisters, holdingRegisterRead, holdingRegisterWrite);
}

void loop(void) {
  modbus.poll();
    if (millis () - target_time >= PERIOD)
  {
    target_time += PERIOD ;   // change scheduled time exactly, no slippage will happen
    sensors.requestTemperatures(); 
    temperature=sensors.getTempCByIndex(0);
    humidity = analogRead(A4);
    if(humidity<438){humidity=438;}
    else if (humidity>750){humidity=750;} // 438-720
    percentage_humidity = map(humidity, 438, 750, 0, 100);
    Serial.println("humidity: " + String(percentage_humidity) + ", temperature: " + String(temperature));
    Serial.println("humidityValue: " + String(humidityValue) + ", temperatureValue: " + String(temperatureValue));
    //Serial.println(humidity);
    EEPROM.update(1, humidityValue);
    EEPROM.update(2, temperatureValue);
  }
}
