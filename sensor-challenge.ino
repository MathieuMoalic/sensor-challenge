#include <LiquidCrystal.h>

// Initialize the library by associating any needed LCD interface pin
LiquidCrystal lcd(7, 8, 9, 10, 11, 12); // RS, E, D4, D5, D6, D7

const int hallSensorPin = A0;
const int buttonPin = 6;
const int ledPin = 13;

int offsetValue = 0;

void setup()
{
    // Set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    lcd.print("Magnetic Value:");

    // Set up the button pin
    pinMode(buttonPin, INPUT_PULLUP); // Use the internal pull-up resistor

    // Set up the buzzer pin
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW); // Ensure the buzzer is off initially
}

void loop()
{
    // Read the button state
    int buttonState = digitalRead(buttonPin);

    // If the button is pressed, update the offset value
    if (buttonState == LOW)
    { // Button is pressed when LOW
        offsetValue = analogRead(hallSensorPin);
        lcd.setCursor(0, 0);
        lcd.print("Zero Set        "); // Clear any previous message
        delay(500);                    // Debounce delay
        lcd.setCursor(0, 0);
        lcd.print("Magnetic Value: ");
    }

    // Read the analog value from the Hall sensor
    int sensorValue = analogRead(hallSensorPin);

    // Calculate the zeroed value
    int zeroedValue = sensorValue - offsetValue;

    // Display the sensor value on the LCD
    lcd.setCursor(0, 1);
    lcd.print("Value: ");
    lcd.print(zeroedValue);
    lcd.print("   "); // Clear any previous value by adding spaces

    // Check if the absolute value exceeds the threshold and buzz if it does
    if (abs(zeroedValue) > 3)
    {
        digitalWrite(ledPin, HIGH); // Turn the buzzer on
    }
    else
    {
        digitalWrite(ledPin, LOW); // Turn the buzzer off
    }

    // Add a small delay to make the readings more readable
    delay(500);
}
