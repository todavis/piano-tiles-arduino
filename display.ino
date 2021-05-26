#include <LiquidCrystal.h>

// Connections:
// rs (LCD pin 4) to Arduino pin 12
// rw (LCD pin 5) to Arduino pin 11
// enable (LCD pin 6) to Arduino pin 10
// LCD pin 15 to Arduino pin 13
// LCD pins d4, d5, d6, d7 to Arduino pins 5, 4, 3, 2
// LCD pin 3 1k resistor to GNDf
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

int backLight = 13;    // pin 13 will control the backlight

void LCD_print(char* phrase1, char* phrase2){
  //clears the LCD display
  //prints phrase1 starting at row1, column1
  //prints phrase2 starting at row2, column1
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(phrase1);
  lcd.setCursor(0,1);
  lcd.print(phrase2);
}

void LCD_print_score(int score){
  //clears LCD
  //prints "Score:" on first line
  //prints score on second line
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Score:");
  lcd.setCursor(0,1);
  lcd.print(score);
}
void setup()
{
  //SETUP
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH); // turn backlight on. Replace 'HIGH' with 'LOW' to turn it off.
  lcd.begin(16,2);              // columns, rows.  use 16,2 for a 16x2 LCD, etc.
  //SETUP FINISH
  
  //some test code
  char* ph1 = "HELLO, WORLD";
  char* ph2 = "lol";
  LCD_print(ph1, ph2);
  delay(1000);
  LCD_print_score(323);
  //lcd.clear();                  // start with a blank screen
  //lcd.setCursor(0,0);           // set cursor to column 0, row 0 (the first row)
  //lcd.print("Hello, World");    // change text to whatever you like. keep it clean!
  //lcd.setCursor(0,1);           // set cursor to column 0, row 1
  //lcd.print("com");
  
  // if you have a 4 row LCD, uncomment these lines to write to the bottom rows
  // and change the lcd.begin() statement above.
  //lcd.setCursor(0,2);         // set cursor to column 0, row 2
  //lcd.print("Row 3");
  //lcd.setCursor(0,3);         // set cursor to column 0, row 3
  //lcd.print("Row 4");
}

void loop()
{ 
}

/* ------------------------------------------------------------------------------- */
