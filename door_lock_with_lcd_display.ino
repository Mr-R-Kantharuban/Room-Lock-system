//sketch created by Akshay Joseph
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
// Constants for row and column sizes
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {10, 9, 8, 7};
byte colPins[COLS] = {6, 5, 4, 3};

LiquidCrystal_I2C lcd(0x27, 16, 2);

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// Length of password + 1 for null character
#define Password_Length 5
// Character to hold password input
char Data[Password_Length];
// Password
char Master[Password_Length] = "1234";
int led = 12;
byte data_count = 0;
 
// Character to hold key input
char customKey;   


void setup()
{
  Serial.begin(9600);
  lcd.begin();

  lcd.backlight();
  
 
  // Set lockOutput as an OUTPUT pin
  pinMode(led, OUTPUT);
  
}

void loop()
{
   lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
  char customKey = customKeypad.getKey();

  
  if (customKey) {
    // Enter keypress into array and increment counter
    Data[data_count] = customKey;
    lcd.setCursor(data_count, 1);
    lcd.print(Data[data_count]);
    data_count++;
  }

  if (data_count == Password_Length - 1) {
    lcd.clear();
 
    if (!strcmp(Data, Master)) {
      // Password is correct
      lcd.print("Correct");
      // Turn on relay for 5 seconds
      digitalWrite(led, HIGH);
      delay(5000);
      digitalWrite(led, LOW);
    }
    else {
      // Password is incorrect
      lcd.print("Incorrect");
      delay(1000);
    }
 
    // Clear data and LCD display
    lcd.clear();
    clearData();
  }

  
}


void clearData() {
  // Go through array and clear data
  while (data_count != 0) {
    Data[data_count--] = 0;
  }
  return;
}
