# Smart Water Management System with Bluetooth Control and Solar Power

This project is an Arduino-based smart water management system designed for efficient and automated water level monitoring and control. It is equipped with Bluetooth connectivity for remote operation and is powered by a solar panel, making it eco-friendly and energy-efficient.

## Features

- **Automatic Water Pump Control:** 
  - The system uses an ultrasonic sensor to measure the water level in a tank.
  - The pump automatically turns on when the water level is below 6 cm and turns off when it exceeds 12 cm.

- **Manual Control:**
  - A push button allows manual control of the pump.
  - Manual mode can also be controlled via Bluetooth commands, overriding the automatic function.

- **Bluetooth Connectivity:**
  - The system can be controlled remotely using a Bluetooth-enabled smartphone.
  - Users can switch between automatic and manual modes, control the pump, and manage the speaker.

- **LCD Display:**
  - The water level is displayed on a 16x2 LCD screen in centimeters.
  - The current pump status ("ON" or "OFF") is also shown.

- **Speaker Control:**
  - The system includes a speaker that can play a melody when triggered via Bluetooth.
  - The speaker can be turned off remotely using Bluetooth commands.

- **Solar Powered:**
  - The entire system is powered by a solar panel, enhancing energy efficiency and sustainability.

## Components Used

- **Arduino Board**
- **Ultrasonic Sensor**
- **Water Pump**
- **16x2 LCD Display with I2C Interface**
- **HC-06 Bluetooth Module**
- **Push Button**
- **Speaker**
- **Solar Panel**

## Circuit Diagram

<p align="center">
  <img src="https://github.com/user-attachments/assets/e1eea5cd-d60c-4547-8361-eb4a2d48d3ae" alt="Additional Image" />
</p>

## Code

The code for the project is available in the `code.ino` file. It includes:

- Initialization of the LCD display, Bluetooth module, and ultrasonic sensor.
- Logic for automatic and manual control of the water pump.
- Functions for Bluetooth communication and melody playback.
- A solar panel setup to power the Arduino and its components.

## How It Works

1. **Setup:** The system starts by initializing the components. The water level is continuously monitored using the ultrasonic sensor.
2. **Auto Mode:** The pump automatically activates or deactivates based on the water level. The status is displayed on the LCD.
3. **Manual Mode:** The pump can be controlled manually via a push button or Bluetooth commands. The speaker can also be controlled via Bluetooth.
4. **Bluetooth Control:** The user can switch modes, control the pump, and manage the speaker using a smartphone.
5. **Solar Power:** The system is powered by a solar panel, ensuring it runs efficiently without external power sources.

## Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/deemalvidarshana/Smart-water-level-controller.git
2. **Upload the code to your Arduino:**
   Open the code.ino file in the Arduino IDE.
   Connect your Arduino board to your computer.
   Upload the code.
3.**Set up the circuit:**
   Follow the circuit diagram to connect the components.
4.**Power the system:**
   Use the solar panel to power the Arduino and the connected components.

## Usage

Monitor the water level via the LCD screen.
Control the pump automatically based on water levels or manually using the push button or Bluetooth.
Use the mobile app to control the pump and speaker remotely.

## App
<p align="center">
  <img src="https://github.com/user-attachments/assets/daeb65c7-0bd7-4d5f-b1f1-7ba24384de52" alt="Circuit Diagram" />
</p>


## Future Enhancements

Integration with IoT: Connecting the system to a cloud service for remote monitoring and control.
Water Level Alerts: Sending alerts to the user's phone when the water level reaches critical levels.

## Acknowledgments

Special thanks to the open-source community for providing libraries and resources.
Inspiration from various Arduino and IoT projects available online.



