# ModBlue
This repository is added to provide simple code for Arduino Modbus Master that reads data from Modbus Slave and then transmits data using bluetooth serial port.

## Instructions
1. Clone the repository.
2. Extract [LIB/ModbusMaster.zip](https://github.com/syedmohiuddinzia/ModBlue/blob/main/LIB/ModbusMaster.zip) in Arduino Library folder.
3. Connect Arduino hardware using serial port and upload [ModbusMasterRTUBluetooth.ino](https://github.com/syedmohiuddinzia/ModBlue/blob/main/ModbusMasterRTUBluetooth.ino).
4. Extract [ModbusClientX.zip](https://github.com/syedmohiuddinzia/ModSenCom/blob/main/ModbusClientX.zip) and run ***ModbusClientX.exe*** in release directory.
5. Connect RS485 Sensor using RS485 to UART module as shown in the image below such that

    | RS485 Sensor | RS485  UART | Arduino MCU |
    |:-------:|:-----:|:-------:|
    | A       | A     |         |
    | B       | B     |         |
    | VCC     | VCC   | VCC     |
    | GND     | GND   | GND     |
    |         | RX    | RX      |
    |         | TX    | TX      |

6. Connect Modbus RTU with the RS485 Port and Sensor Baudrate *i.e. 9600*.
7. On next window of Modbus Client, change # of addresses to *8*, click on *Read from 0 to 7* and keep in mind that Slave Address *254* (Soil temperature & moisture sensor) is selected.
8. Now data on specific holding registers can be read.
9. To write data on specific holding registers, double click and write a new value and then press enter.

## Datasheet - (Modbus Holding Register)
| Address   | Variable      | Read/Write    |
| :-----:   | :------:      | :--------:    |
| 00        | Moisture      | Read          |
| 03        | Temperature   | Read          |
| 06        | Conductivity  | Read          |
