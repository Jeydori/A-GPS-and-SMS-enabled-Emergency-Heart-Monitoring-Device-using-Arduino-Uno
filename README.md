# A-GPS-and-SMS-enabled-Emergency-Heart-Monitoring-Device-using-Arduino-Uno
cheap components are used like MAX30100, SIM800L, GPS NEO6MV2, OLED I2C, etc.

![image](https://github.com/Jeydori/A-GPS-and-SMS-enabled-Emergency-Heart-Monitoring-Device-using-Arduino-Uno/assets/92672461/51e1743d-9e06-4c7f-b845-699db22515f4)


**Introduction**

In today's rapidly advancing world, the convergence of technology and healthcare has paved the way for innovative solutions that can save lives in critical situations. In this tutorial, we will delve into the creation of an A-GPS and SMS enabled emergency heart monitoring device using the versatile Arduino Uno microcontroller. This project amalgamates multiple cutting-edge components to craft a wearable device capable of monitoring a person's heart rate and blood oxygen saturation (SpO2) in real time. In the event of an emergency, the device can swiftly transmit an SMS alert, complete with vital statistics and accurate GPS coordinates, to a designated recipient. 

Our project centers around the following main components:

1. **SIM800L GSM Module:** This module facilitates cellular communication, enabling the device to send SMS alerts, an essential feature for emergency situations.

2. **3.7V Li-Po Battery:** Due to SIM800L's high current consumption and an operating voltage that is not common in the whole circuit, we will use this external supply for it to operate.

3. **NEO-6M GPS Module:** By interfacing with satellites, the NEO-6M module provides accurate global positioning coordinates, crucial for determining the wearer's precise location during an emergency.

4. **MAX30100 Pulse Oximeter Sensor:** This sensor is at the heart of the project, quite literally. It measures both heart rate and blood oxygen saturation, pivotal health metrics in assessing one's condition.

5. **OLED Display (128x64) with I2C Interface:** An OLED screen offers a visually appealing and concise method of conveying real-time data to the user.

6. **Push Button:** The inclusion of a physical button allows the user to trigger an emergency alert manually, ensuring immediate attention when necessary.

The integration of these components into a cohesive system showcases the potential of technology to enhance emergency response and medical monitoring.

Throughout this tutorial, we will comprehensively examine the provided source code, which meticulously orchestrates the communication, data processing, and alert mechanisms of this intricate device. By dissecting each segment of the code, we will gain an understanding of how it interacts with the hardware components to create a functional and potentially life-saving device.

So, without further ado, let's embark on this journey of learning and innovation as we unravel the inner workings of the A-GPS and SMS enabled emergency heart monitoring device using the Arduino Uno.


**Components Required:**

- 1x Arduino Uno
- 1x SIM800L GSM Module
- 1x NEO-6MV2 GPS Module
- 1x MAX30100 Pulse Oximeter
- 1x OLED Display (SSD1306) with I2C Interface
- 1x Push Button
- Jumper Wires / solid wires
- 1x Breadboard
- 1x 10k ohm resistor (pulldown resistor)
- 3.7V Li-Po Battery

**Wiring Diagram:**

Connect the components as shown in the wiring diagram above:
         SIM800L    Arduino Uno
         VCC        5V
         GND        GND
         TXD        Pin 4
         RXD        Pin 3
         
         NEO-6M     Arduino Uno
         VCC        5V
         GND        GND
         TX         Pin 8
         RX         Pin 9
         
         MAX30100   Arduino Uno
         VCC        5V
         GND        GND
         SDA        A4 (SDA)
         SCL        A5 (SCL)
         
         OLED       Arduino Uno
         VCC        5V
         GND        GND
         SDA        A4 (SDA)
         SCL        A5 (SCL)
         
         Button     Arduino Uno
         Pin        7


**Source Code Explanation:**

```cpp
#include <SoftwareSerial.h>
#include "MAX30100_PulseOximeter.h"
#include <TinyGPS++.h>
#include "U8glib.h"
```

The `#include` directives are used to import necessary libraries for the project. These libraries provide functions and classes that simplify communication with the components.

```cpp
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST);
char str[10];
```

The `U8glib` library is used for controlling the OLED display. Here, an instance `u8g` of the display is created, and a character array `str` is defined for converting numerical values to strings.

```cpp
const byte button = 2;
byte buttState;
```

The `button` pin is defined as a constant, and variables `buttState` are declared to hold the state of the push button.

```cpp
SoftwareSerial gpsSerial(8, 9);
SoftwareSerial simSerial(4, 3);
```

Two instances of `SoftwareSerial` are created to establish serial communication with the GPS module (`gpsSerial`) and the SIM800L GSM module (`simSerial`) using the specified pins.

```cpp
PulseOximeter pox;
TinyGPSPlus gps;
float heartRate, lat, lng, spo2;
bool gpsDataAvailable = false;
```

Instances of `PulseOximeter` and `TinyGPSPlus` classes are created for interfacing with the MAX30100 Pulse Oximeter sensor and the NEO-6M GPS module. Variables are defined to store heart rate (`heartRate`), latitude (`lat`), longitude (`lng`), and blood oxygen saturation (`spo2`) values. The `gpsDataAvailable` flag indicates whether valid GPS data is available.

```cpp
uint32_t lastMillis = 0;
uint32_t max30100Interval = 1500;
```

Variables `lastMillis` and `max30100Interval` are used for timing the heart rate and SpO2 measurements using the MAX30100 sensor.

```cpp
void(* resetFunc) (void) = 0;
```

A function pointer `resetFunc` is defined. This will be used to reset the Arduino, essentially restarting the device.

```cpp
void setup() {
  pinMode(button, INPUT);
  u8g.setColorIndex(1);
  // ... Initializing SIM800L, GPS, and PulseOximeter ...
}
```

In the `setup()` function:
- The push button is set as an input.
- The OLED display color is set.
- The SIM800L module is initialized and configured for sending SMS.
- The GPS module is initialized.
- The PulseOximeter module is initialized, and the IR LED current for the MAX30100 sensor is set.

```cpp
void loop() {
  buttState = digitalRead(button);

  if (buttState == 1) {
    sendSMS();
  } else {
    inputs();
  }
}
```

In the `loop()` function:
- The state of the push button is read.
- If the button is pressed (`buttState == 1`), the `sendSMS()` function is called. Otherwise, the `inputs()` function is called.

```cpp
void inputs() {
  unsigned long currentMillis = millis();
  
  // ... Reading GPS data ...
  
  if (currentMillis - lastMillis > max30100Interval) {
    lastMillis = currentMillis;
    // ... Reading heart rate and SpO2 data ...
  }
  pox.update();
}
```

The `inputs()` function reads GPS data from the NEO-6M module and stores latitude and longitude if valid data is available. It also reads heart rate and SpO2 data from the MAX30100 sensor at a defined interval using the `max30100Interval`.

```cpp
void displayData() {
  // ... Displaying data on the OLED screen ...
}
```

The `displayData()` function is responsible for updating and displaying data on the OLED screen using the `U8glib` library.

```cpp
void sendSMS() {
  // ... Sending an emergency SMS ...
  resetFunc(); // Reset Arduino to restart the device
}
```

The `sendSMS()` function sends an emergency SMS using the SIM800L module with the wearer's vital information and GPS location. After sending the SMS, it calls `resetFunc()` to reset the Arduino, essentially restarting the device.

This source code combines different components and functionalities to create an A-GPS and SMS enabled emergency heart monitoring device. The device monitors heart rate, SpO2, and GPS data, and it can send an emergency alert SMS with relevant information to a predefined phone number. Additionally, it displays the monitored data on an OLED screen for real-time feedback. The button press simulates an emergency scenario for testing the SMS alert functionality.

Here is the full sketch for further use:
   without oled:
      https://github.com/Jeydori/A-GPS-and-SMS-enabled-Emergency-Heart-Monitoring-Device-using-Arduino-Uno/blob/main/GPS%20and%20SMS%20Heart%20Monitoring%20Device%20(no%20oled).ino
      
      sample video:
         https://github.com/Jeydori/A-GPS-and-SMS-enabled-Emergency-Heart-Monitoring-Device-using-Arduino-Uno/blob/main/GPS%20and%20SMS%20Heart%20Monitoring%20Device%20(no%20oled).mp4

   with oled:
      https://github.com/Jeydori/A-GPS-and-SMS-enabled-Emergency-Heart-Monitoring-Device-using-Arduino-Uno/blob/main/GPS%20and%20SMS%20Heart%20Monitoring%20Device.ino



**Conclusion:**

In this tutorial, you've learned how to create an A-GPS and SMS-enabled emergency heart monitoring device using an Arduino Uno and various components. The device continuously monitors heart rate and blood oxygen levels and can send an emergency SMS with vital readings and location information when the push button is pressed. This project demonstrates the integration of different modules to create a potentially life-saving device.

