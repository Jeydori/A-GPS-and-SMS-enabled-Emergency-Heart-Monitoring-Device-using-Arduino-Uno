# A-GPS-and-SMS-enabled-Emergency-Heart-Monitoring-Device-using-Arduino-Uno
cheap components are used like MAX30100, SIM800L, GPS NEO6MV2, OLED I2C, etc.


**Content In Progress**

In this tutorial, we will create a heart monitoring device using an Arduino Uno, MAX30100 pulse oximeter sensor, and a GPS module. The device will measure heart rate and blood oxygen saturation (SpO2) levels of a person and send an emergency SMS with the readings and location when a button is pressed. We will also display the real-time data on an OLED display.

**Components Needed:**
- Arduino Uno
- MAX30100 Pulse Oximeter Sensor
- GPS Module (e.g., NEO-6M)
- OLED Display (128x64)
- Push Button
- Jumper Wires
- Breadboard

**Wiring Diagram:**

![Wiring Diagram](https://your-image-url.com)

**Step 1: Setting up the Hardware**

1. Connect the MAX30100 sensor to the Arduino Uno as follows:
   - VCC to 5V
   - GND to GND
   - SDA to A4
   - SCL to A5

2. Connect the GPS module to the Arduino Uno as follows:
   - VCC to 5V
   - GND to GND
   - TXD to pin 8 (RX)
   - RXD to pin 9 (TX)

3. Connect the OLED display to the Arduino Uno as per the wiring diagram.

4. Connect the push button to pin 2.

## Step 2: Installing Libraries

1. Open the Arduino IDE.

2. Go to **Sketch > Include Library > Manage Libraries**.

3. Search for and install the following libraries:
   - MAX30100 by OXullo Intersecans
   - TinyGPS++ by Mikal Hart
   - U8glib by olikraus (for OLED display)

## Step 3: Uploading the Code

Copy and paste the provided source code into the Arduino IDE.

```cpp
// Paste the source code here
```

## Step 4: Understanding the Code

1. **SoftwareSerial**: This library is used to create software-based serial communication for the GPS module and SIM800 module.

2. **MAX30100_PulseOximeter**: Library for interfacing with the MAX30100 pulse oximeter sensor.

3. **TinyGPS++**: Library for parsing NMEA GPS data.

4. **U8glib**: Library for driving OLED displays.

5. **setup()**: Initializes the components and sets up communication with the GPS and SIM800 modules.

6. **loop()**: Monitors the button state and either sends an emergency SMS or updates the sensor data.

7. **inputs()**: Reads GPS data and heart rate/SpO2 data from the sensor.

8. **displayData()**: Displays heart rate, SpO2, latitude, and longitude on the OLED display.

9. **sendSMS()**: Sends an emergency SMS with the sensor readings and location to a specified phone number.

## Step 5: Testing the Device

1. Upload the code to the Arduino Uno.

2. Power the Arduino and place your finger on the MAX30100 sensor to simulate measurement.

3. Observe the real-time data on the OLED display.

4. Press the button to trigger an emergency SMS with the readings and location.

## Conclusion

In this tutorial, we created an A-GPS and SMS-enabled heart monitoring device using an Arduino Uno, MAX30100 pulse oximeter sensor, and GPS module. The device measures heart rate and SpO2 levels, displays the data on an OLED display, and sends an emergency SMS with the readings and location when a button is pressed. This project showcases the integration of different components for health monitoring and emergency communication.

