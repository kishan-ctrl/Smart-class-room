#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address and size

const int enterIRPin = 9; // IR sensor input for entering students
const int leaveIRPin = 7; // IR sensor input for leaving students
const int fanPin = 10;     // Fan control pin
const int redLEDPin = 6;   // Red LED control pin
const int greenLEDPin = 7; // Green LED control pin
const int blueLEDPin = 8;  // Blue LED control pin

int enteringCount = 0; // Initialize the entering student count
int leavingCount = 0;  // Initialize the leaving student count

bool entering = false; // To keep track of students entering
bool leaving = false;  // To keep track of students leaving

void setup() {
  lcd.init();      // Initialize the LCD
  lcd.backlight(); // Turn on the backlight
  pinMode(enterIRPin, INPUT);
  pinMode(leaveIRPin, INPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
  updateDisplay();
}

void loop() {
  // Check if a student has entered
  if (digitalRead(enterIRPin) == HIGH && !entering) {
    entering = true;
    enteringCount++; // Increment entering student count when someone enters
    updateDisplay();
  } else if (digitalRead(enterIRPin) == LOW) {
    entering = false;
  }

  // Check if a student has left
  if (digitalRead(leaveIRPin) == HIGH && !leaving) {
    leaving = true;
    leavingCount++; // Increment leaving student count when someone leaves
    updateDisplay();
  } else if (digitalRead(leaveIRPin) == LOW) {
    leaving = false;
  }
}

void updateDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Students: ");
  lcd.setCursor(9, 0);
  lcd.print(enteringCount - leavingCount);

  // Control the fan and LEDs based on the student count
  if (enteringCount - leavingCount > 0) {
    digitalWrite(fanPin, HIGH);     // Turn on the fan
    digitalWrite(redLEDPin, HIGH);   // Turn on the red LED
    digitalWrite(greenLEDPin, HIGH); // Turn on the green LED
    digitalWrite(blueLEDPin, HIGH);  // Turn on the blue LED
  } else {
    digitalWrite(fanPin, LOW);      // Turn off the fan
    digitalWrite(redLEDPin, LOW);    // Turn off the red LED
    digitalWrite(greenLEDPin, LOW);  // Turn off the green LED
    digitalWrite(blueLEDPin, LOW);   // Turn off the blue LED
  }
}
