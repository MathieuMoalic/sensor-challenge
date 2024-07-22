#include <LiquidCrystal.h>
#include <Servo.h>

// Initialize the library by associating any needed LCD interface pin
LiquidCrystal lcd(7, 8, 9, 10, 11, 12); // RS, E, D4, D5, D6, D7

Servo myServo; // Create a Servo object
const int servoPin = 5;
const int hallSensorPin = A0;
const int buttonPin = 6;

int offsetValue = 0;
bool servoMoving = false;
unsigned long startTime = 0;
const int gameDuration = 12000;
int score = -1;

void setup()
{
    myServo.attach(servoPin);  // Attach the servo to pin 5
    randomSeed(analogRead(0)); // Seed the random number generator

    // Set up the LCD's number of columns and rows:
    lcd.begin(16, 2);

    // Zero the magnetic reading at the beginning
    offsetValue = analogRead(hallSensorPin);
    lcd.setCursor(0, 0);
    lcd.print("Press to start.");

    // Set up the button pin
    pinMode(buttonPin, INPUT_PULLUP); // Use the internal pull-up resistor

    lcd.setCursor(0, 0);
    lcd.print("Press to start  ");
}

void loop()
{
    // If the button is pressed, update the offset value
    int buttonState = digitalRead(buttonPin);
    if (buttonState == LOW)
    {
        play();
    }
    delay(100);
}

void play()
{
    score = 0;
    unsigned long currentTime = millis(); // Get the current time
    unsigned long startTime = currentTime;
    lcd.setCursor(0, 0);
    lcd.print("Playing          ");
    lcd.setCursor(0, 1);
    lcd.print("Score: 0          ");
    int servoMoveCount = 0;
    int servoDelay = 10;

    while (servoMoveCount < 140)
    {
        int randomAngle = random(20, 181);            // Generate a random angle between 0 and 180
        moveServoToPosition(randomAngle, servoDelay); // Move the servo to the random angle with a speed delay

        // Read the magnetic value and update the score
        int sensorValue = analogRead(hallSensorPin);
        int zeroedValue = sensorValue - offsetValue;
        score += abs(zeroedValue);

        // Update the score on the LCD
        if (servoMoveCount % 10 == 0)
        {
            lcd.setCursor(7, 1);
            lcd.print(score);
            lcd.print("   ");       // Clear any previous value by adding spaces
            currentTime = millis(); // Update the current time
        }
        servoMoveCount = servoMoveCount + 1;
        if (servoMoveCount % 10 == 0)
        {
            servoDelay = servoDelay - 1;
        }
    }
    lcd.setCursor(0, 0);
    lcd.print("Press to start  ");
}

void moveServoToPosition(int targetPosition, int speedDelay)
{
    int currentPosition = myServo.read(); // Get the current position of the servo
    int stepDelay = max(speedDelay, 1);   // Ensure at least 1 ms delay to allow the servo to move
    int steps = abs(targetPosition - currentPosition);

    if (currentPosition < targetPosition)
    {
        for (int pos = currentPosition; pos <= targetPosition; pos++)
        {
            myServo.write(pos);
            delay(stepDelay);
        }
    }
    else
    {
        for (int pos = currentPosition; pos >= targetPosition; pos--)
        {
            myServo.write(pos);
            delay(stepDelay);
        }
    }
}
