//
// ESP32-S3 Demo for Arduino IDE
//
// Requires Adafruit Neopixel Library
// This sketch demonstrates:
// - Reading three buttons with internal pull-ups.
// - Controlling the onboard RGB LED (NeoPixel) on GPIO 48.
// - Sending data to both the native USB serial (Serial) and a secondary hardware UART (Serial1).
// 
//

// 1. INCLUDE LIBRARIES
#include <Adafruit_NeoPixel.h>

// 2. PIN & CONFIGURATION DEFINITIONS

// -- Hardware Pins --
const int NEOPIXEL_PIN = 48; // GPIO for the onboard RGB LED
const int BUTTON_1_PIN = 8;
const int BUTTON_2_PIN = 9;
const int BUTTON_3_PIN = 16;

// -- UART Pins (for Serial1) --
const int UART_TX_PIN = 1; // Connect this to the RX of your other device
const int UART_RX_PIN = 2; // Connect this to the TX of your other device

// -- NeoPixel Configuration --
const int NUM_PIXELS = 1; // There is only one RGB LED on the board
Adafruit_NeoPixel strip(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// -- Timing for Periodic Message --
unsigned long previousMillis = 0;
const long interval = 2000; // Interval to print the counter (2000ms = 2 seconds)
int counter = 0;


void setup() {
  // 3. INITIALIZE SERIAL PORTS
  
  // Initialize Native USB Serial Port. This is the one you'll see in the Arduino Serial Monitor.
  Serial.begin(115200);
  
  // Initialize the secondary Hardware UART (UART1) on GPIO 1 and 2.
  // Syntax: Serial1.begin(baud-rate, protocol, RX_PIN, TX_PIN);
  Serial1.begin(115200, SERIAL_8N1, UART_RX_PIN, UART_TX_PIN);

  // Wait a moment for serial ports to initialize, especially the USB one.
  delay(1000); 

  Serial.println("--- ESP32-S3 Demo Sketch Initialized ---");
  Serial.println("Monitoring Native USB (Serial)");
  
  Serial1.println("--- ESP32-S3 Demo Sketch Initialized ---");
  Serial1.println("Monitoring Hardware UART (Serial1) on TX:1, RX:2");

  // 4. INITIALIZE BUTTONS
  // Configure the button pins as inputs with their internal pull-up resistors enabled.
  // This means the pin will be HIGH when the button is not pressed and LOW when it is.
  pinMode(BUTTON_1_PIN, INPUT_PULLUP);
  pinMode(BUTTON_2_PIN, INPUT_PULLUP);
  pinMode(BUTTON_3_PIN, INPUT_PULLUP);
  Serial.println("Buttons on pins 8, 9, 16 are configured.");

  // 5. INITIALIZE NEOPIXEL
  strip.begin();
  strip.setBrightness(40); // Set a moderate brightness (0-255) to avoid being blinded!
  strip.clear(); // Initialize all pixels to 'off'
  strip.show();
  Serial.println("RGB LED on pin 48 is configured.");
}


void loop() {
  // 6. PERIODIC COUNTER MESSAGE
  // This section uses millis() to send a message every 'interval' milliseconds without blocking the code.
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Save the last time the message was sent
    counter++; // Increment the counter

    // Print to both serial ports
    String message = "Periodic update. Counter: " + String(counter);
    Serial.println(message);
    Serial1.println(message);
  }

  // 7. CHECK BUTTON STATES
  // The logic is structured with if-else if to handle one button press at a time.
  // digitalRead() will be LOW if a button is pressed because we are using INPUT_PULLUP.
  if (digitalRead(BUTTON_1_PIN) == LOW) {
    String message = "Button on pin 8 pressed!";
    Serial.println(message);
    Serial1.println(message);
    strip.setPixelColor(0, strip.Color(255, 0, 0)); // Set LED to RED ❤️
    strip.show();
  } 
  else if (digitalRead(BUTTON_2_PIN) == LOW) {
    String message = "Button on pin 9 pressed!";
    Serial.println(message);
    Serial1.println(message);
    strip.setPixelColor(0, strip.Color(0, 255, 0)); // Set LED to GREEN 💚
    strip.show();
  } 
  else if (digitalRead(BUTTON_3_PIN) == LOW) {
    String message = "Button on pin 16 pressed!";
    Serial.println(message);
    Serial1.println(message);
    strip.setPixelColor(0, strip.Color(0, 0, 255)); // Set LED to BLUE 💙
    strip.show();
  } 
  else {
    // If no buttons are being pressed, turn the LED off.
    strip.clear();
    strip.show();
  }
  
  // A small delay to prevent bouncing and overwhelming the serial ports.
  delay(50); 
}