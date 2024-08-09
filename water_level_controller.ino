#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

// Initialize the LCD with the I2C address 0x27 and 16x2 display size
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Declare variables for duration, distance, and pump state
long duration, distance;
bool pump = false, manualMode = false;
bool bluetoothPumpControl = false; // Variable to track Bluetooth pump control

SoftwareSerial bluetooth(6, 7); // RX, TX

// Define musical note frequencies
#define NOTE_C4 262
#define NOTE_G3 196
#define NOTE_A3 220
#define NOTE_B3 247
#define NOTE_B4 494

// Define melody and note durations
int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4};

void setup() {
    lcd.init(); // Initialize the LCD
    lcd.backlight(); // Turn on the LCD backlight
    lcd.print("DIST :      "); // Print initial message
    lcd.setCursor(0, 1);
    lcd.print("WATER PUMP:");

    // Set pin modes
    pinMode(2, OUTPUT); // Trigger pin for ultrasonic sensor
    pinMode(3, INPUT); // Echo pin for ultrasonic sensor
    pinMode(10, INPUT_PULLUP); // Button pin with internal pull-up resistor
    pinMode(11, INPUT_PULLUP); // Mode selection pin with internal pull-up resistor
    pinMode(13, OUTPUT); // Pump control pin
    pinMode(5, OUTPUT); // Speaker control pin

    bluetooth.begin(9600); // Start Bluetooth serial communication
    Serial.begin(9600); // Start serial communication for debugging
    Serial.println("Setup complete. System is ready.");
}

void loop() {
    // Trigger the ultrasonic sensor
    digitalWrite(2, HIGH);
    delayMicroseconds(2);
    digitalWrite(2, LOW);
    duration = pulseIn(3, HIGH); // Read the echo duration
    distance = microsecondsToDistance(duration); // Convert duration to distance in cm

    // Display the distance on the LCD
    lcd.setCursor(5, 0);
    lcd.print(distance);
    lcd.print(" cm   ");

    Serial.print("Distance measured: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (!manualMode && !bluetoothPumpControl) { // Auto mode and not controlled by Bluetooth
        if (distance < 6) {
            pump = false;
            Serial.println("Auto Mode: Pump OFF due to low water level.");
        } else if (distance > 12) {
            pump = true;
            Serial.println("Auto Mode: Pump ON due to high water level.");
        }
    }

    // Update the pump status and display on the LCD
    digitalWrite(13, pump ? LOW : HIGH);

    lcd.setCursor(12, 1);
    if (pump) {
        lcd.print("ON  ");
    } else {
        lcd.print("OFF ");
    }

    // Manual control using button press (pin 10)
    static bool buttonState = false;
    if (!digitalRead(10)) {
        if (!buttonState) {
            buttonState = true;
            pump = !pump; // Toggle pump state
            Serial.print("Manual Mode: Button pressed. Pump ");
            Serial.println(pump ? "ON" : "OFF");
            delay(300); // debounce delay
        }
    } else {
        buttonState = false;
    }

    // Bluetooth communication
    if (bluetooth.available()) {
        char command = bluetooth.read();
        Serial.print("Bluetooth command received: ");
        Serial.println(command);

        if (command == '5') { 
            bluetoothPumpControl = true;
            manualMode = true;
            Serial.println("Bluetooth: Switched to manual mode.");
        } else if (command == '4') { 
            bluetoothPumpControl = false;
            manualMode = false;
            Serial.println("Bluetooth: Switched to automatic mode.");
        } else if (command == '6') { 
            digitalWrite(13, LOW);
            pump = false;
            bluetoothPumpControl = true; 
            Serial.println("Bluetooth: Pump OFF.");
        } else if (command == '7') { 
            digitalWrite(13, HIGH);
            pump = true;
            bluetoothPumpControl = true; 
            Serial.println("Bluetooth: Pump ON.");
        } else if (command == '8') { // Turn speaker on
            playMelody(5);
            Serial.println("Bluetooth: Speaker ON, playing melody.");
        } else if (command == '9') { // Turn speaker off
            noTone(5);
            Serial.println("Bluetooth: Speaker OFF.");
        }
    }

    // Send distance data and system mode to the app
    bluetooth.print("Distance: ");
    bluetooth.print(distance);
    bluetooth.println(" cm");

    bluetooth.print("Mode: ");
    if (manualMode) {
        bluetooth.println("Manual");
    } else {
        bluetooth.println("Automatic");
    }

     // Send tank animation based on distance
    if (distance > 100) {
        bluetooth.println("Tank: Empty");
        Serial.println("Tank status: Empty");
    } else if (distance < 10) {
        bluetooth.println("Tank: Full");
        Serial.println("Tank status: Full");
    }

    delay(1400); // Adjust delay as needed
}

// Function to play a melody on a specified pin
void playMelody(int melodyPin) {
    for (int thisNote = 0; thisNote < 8; thisNote++) {
        int noteDuration = 1000 / noteDurations[thisNote]; // Calculate note duration
        tone(melodyPin, melody[thisNote], noteDuration); // Play the note
        int pauseBetweenNotes = noteDuration * 1.30; // Calculate pause between notes
        delay(pauseBetweenNotes); // Wait before playing the next note
        noTone(melodyPin); // Stop the tone
    }
}

// Function to convert microseconds to distance
long microsecondsToDistance(long microseconds) {
    return microseconds / 29 / 2;
}
