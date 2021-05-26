//MIE430 - Final Project
//Main loop code that runs the game

#include <FastLED.h>
#include <LiquidCrystal.h>
#define LED_PIN_1   2
#define LED_PIN_2   3
#define LED_PIN_3   4
#define LED_PIN_4   7

#define FAIL_FLAG   13
#define SUCC_FLAG   8

#define NUM_LEDS    20
#define NUM_f       4

#define BUTTON_1    A0
#define BUTTON_2    A1
#define BUTTON_3    A2
#define BUTTON_4    A3

#define LCD_D7      12
#define LCD_D6      11 //PWM
#define LCD_D5      10
#define LCD_D4      9 //PWM
#define RS          5
#define ENABLE      6 //PWM
LiquidCrystal lcd(RS, ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];
CRGB leds4[NUM_LEDS];

boolean* getPress(boolean* button_press){
    if (analogRead(BUTTON_1)>500){
       button_press[0] = 1;
    }
    if (analogRead(BUTTON_2)>500){
       button_press[1] = 1;
    }
    if (analogRead(BUTTON_3)>500){
       button_press[2] = 1;
    }
    if (analogRead(BUTTON_4)>500){
       button_press[3] = 1;
    }
    return button_press;
}

int getButton(int freq, int prev_freq, int prev_button){
  //returns a new button/strip # given a frequency, previous freq, and prev button
  if (freq == 0){
    return 0;
  }
  if (freq > prev_freq){
    if (prev_button == 4){
      return 3;
    }
    return prev_button + 1;
  }
  else if (freq == prev_freq){
    return prev_button;
  }
  else {
    if (prev_button == 1){
      return 2;
    }
    return prev_button - 1;
  }
}

void displayBoard(int index, int length_i, const int *notes, const int *times, int prev_freq, int prev_button, int scale){
    //given a certain note number, displays the next 20 note values on the led board
    int num = 0;
    int freq;
    int note_len;
    int cur_freq;
    int cur_button;
    
    while (num < NUM_LEDS) { //loop through the entire song at for len_i in times
    
        note_len = scale*times[length_i];
        while (index < note_len){
          
           cur_freq = notes[length_i];
           cur_button = getButton(cur_freq,prev_freq,prev_button);
           
           prev_freq = cur_freq;
           prev_button = cur_button;

           if (cur_button == 1) {
              leds1[num] = CRGB(30,0,0);
              leds2[num] = CRGB(0,0,0);
              leds3[num] = CRGB(0,0,0);
              leds4[num] = CRGB(0,0,0);
              FastLED.show();
           } else if (cur_button == 2) {
              leds2[num] = CRGB(0,30,0);
              leds1[num] = CRGB(0,0,0);
              leds3[num] = CRGB(0,0,0);
              leds4[num] = CRGB(0,0,0);
              FastLED.show();
           } else if (cur_button == 3) {
              leds3[num] = CRGB(0,10,30);
              leds1[num] = CRGB(0,0,0);
              leds2[num] = CRGB(0,0,0);
              leds4[num] = CRGB(0,0,0);
              FastLED.show();
           } else if (cur_button == 4) {
              leds4[num] = CRGB(20,20,0);
              leds1[num] = CRGB(0,0,0);
              leds2[num] = CRGB(0,0,0);
              leds3[num] = CRGB(0,0,0);
              FastLED.show();
           } else{ 
              leds1[num] = CRGB(0,0,0);
              leds2[num] = CRGB(0,0,0);
              leds3[num] = CRGB(0,0,0);
              leds4[num] = CRGB(0,0,0);
           }
           index ++;
           num ++;
           if (num == NUM_LEDS){ //exit condition
            break;
           }
        }
        length_i ++;
        index = 0;
    }
}

void displayNumber(int i){
    // displays a large countdown value on the LED board
    if (i==1){
      leds2[7] = CRGB(0,30,0);
      leds2[8] = CRGB(0,30,0);
      leds2[9] = CRGB(0,30,0);
      leds2[10] = CRGB(0,30,0);
      leds2[11] = CRGB(0,30,0);
      leds2[12] = CRGB(0,30,0);
      leds3[11] = CRGB(0,30,0);
      leds3[7] = CRGB(0,30,0);
      leds1[7] = CRGB(0,30,0);
    } else if (i==2){
      leds1[7] = CRGB(0,30,0);
      leds2[7] = CRGB(0,30,0);
      leds3[7] = CRGB(0,30,0);
      leds3[8] = CRGB(0,30,0);
      leds2[9] = CRGB(0,30,0);
      leds1[10] = CRGB(0,30,0);
      leds1[11] = CRGB(0,30,0);
      leds2[12] = CRGB(0,30,0);
      leds3[11] = CRGB(0,30,0);
    } else if (i==3){
      leds1[7] = CRGB(0,30,0);
      leds2[7] = CRGB(0,30,0);
      leds3[7] = CRGB(0,30,0);
      leds1[8] = CRGB(0,30,0);
      leds1[9] = CRGB(0,30,0);
      leds1[10] = CRGB(0,30,0);
      leds2[10] = CRGB(0,30,0);
      leds1[11] = CRGB(0,30,0);
      leds2[12] = CRGB(0,30,0);
      leds3[12] = CRGB(0,30,0);
    }
    FastLED.show();
}
void setup() {
    FastLED.addLeds<WS2812, LED_PIN_1, GRB>(leds1, NUM_LEDS); //LED initialization
    FastLED.addLeds<WS2812, LED_PIN_2, GRB>(leds2, NUM_LEDS);
    FastLED.addLeds<WS2812, LED_PIN_3, GRB>(leds3, NUM_LEDS);
    FastLED.addLeds<WS2812, LED_PIN_4, GRB>(leds4, NUM_LEDS);
    
    Serial.begin(9600); //Serial output begin
    
    pinMode(BUTTON_1,INPUT); //Set buttons = input
    pinMode(BUTTON_2,INPUT);
    pinMode(BUTTON_3,INPUT);
    pinMode(BUTTON_4,INPUT);
    
    pinMode(FAIL_FLAG,OUTPUT); //communication to other microC (outputs)
    pinMode(SUCC_FLAG,OUTPUT);
    
    digitalWrite(SUCC_FLAG,LOW); //initialize to low
    digitalWrite(FAIL_FLAG,LOW);

    lcd.begin(16, 2);
    lcd.print("hello, world!");
}

void loop() { // execution loop of the game   

    const int notes[] PROGMEM = {0,1174, 1567, 1479, 1396, 1318, 1244, 1108, 1244, 1174, 783, 880, 932, 1174, 1567, 1760, 1864, 2489, 1567, 1479, 1396, 1318, 1244, 1108, 1244, 1174, 783, 880, 932, 1174, 1567, 1760, 1864, 2489, 587, 880, 932, 587, 587, 783, 698, 622, 587, 587, 880, 932, 587, 587, 783, 587, 466, 369, 880, 932, 587, 440, 440, 587, 783, 698, 622, 587, 523, 466, 523, 587, 783, 587,0};
    //const int notes[] PROGMEM = {0,880, 830, 880, 830, 880, 659, 880, 587, 440, 554, 880, 830, 880, 830, 880, 659, 880, 587, 440, 554, 880, 830, 880, 440, 830, 880, 440, 659, 880, 440, 587, 440, 554, 587, 440, 659, 554, 415, 493, 440, 415, 440, 329, 440, 493, 554, 329, 440, 493, 554, 329, 554, 587, 659, 329, 554, 587, 659, 329, 587, 554, 493, 329, 587, 554, 493, 440, 554, 880, 830, 880, 440, 830, 880, 440, 659, 880, 440, 587, 440, 554, 587, 659, 1108, 987, 659, 987, 1108, 987, 880, 830, 659, 880, 329, 440, 493, 554, 329, 440, 493, 554, 329, 554, 587, 659, 329, 554, 587, 659, 329, 587, 554, 493, 329, 587, 554, 493, 880, 987, 880, 830, 880, 440, 659, 440, 880, 987, 880, 830, 880, 440, 659, 440, 880, 987, 880, 830, 880, 987, 1108, 1174, 1318, 1108, 987, 880, 830, 493, 880, 987, 880, 830, 880, 440, 659, 440, 880, 987, 880, 830, 880, 440, 659, 440, 880, 987, 880, 830, 880, 987, 1108, 1174, 1318, 1108, 987, 880, 830, 493, 880, 987, 880, 830, 880, 440, 659, 440, 880, 987, 880, 830, 880, 440, 659, 440, 880, 987, 880, 830, 880, 987, 1108, 1174, 1318, 1108, 987, 880, 830, 493, 880, 987, 880, 830, 880, 440, 659, 440, 880, 987, 880, 830, 880, 440, 659, 440, 880, 987, 880, 830, 880, 987, 1108, 1174, 1318, 1108, 987, 880, 830, 493, 415, 329, 880, 830, 880, 440, 830, 880, 440, 659, 880, 440, 587,0};
    const int times[] PROGMEM = {20,4, 1, 1, 2, 2, 2, 2, 2, 12, 2, 2, 4, 4, 4, 4, 8, 12, 1, 1, 2, 2, 2, 2, 2, 12, 2, 2, 4, 4, 4, 4, 8, 4, 4, 6, 6, 16, 4, 5, 6, 4, 12, 4, 6, 6, 12, 8, 8, 8, 4, 12, 6, 6, 4, 8, 4, 4, 6, 6, 4, 8, 8, 8, 8, 8, 8, 16, 20};
    //const int times[] PROGMEM = {20,2, 2, 2, 2, 2, 2, 2, 14, 2, 2, 2, 2, 2, 2, 2, 2, 2, 14, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 1, 12, 2, 2, 6, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 1, 6, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,20};

    FastLED.clear(); //sleep mode no button has started the program
    boolean noButton = true;
    boolean pressButton[NUM_f] = {0,0,0,0};
    while (noButton){
      *pressButton = getPress(pressButton);
      for (int i= 0; i<sizeof(pressButton)/sizeof(pressButton[0]);i++){
        if (pressButton[i] != 0){
          noButton = false;
          break;}
      }
    }
    
    for (int i=3; i>0; i--){ //countdown loop before game start
      displayNumber(i);
      delay(1000);
    }
    
    int note_len;
    int min_num = 1;
    unsigned long note_time;

    int songON = true;
    int hit_time = 15; // hitbox time of 1 second for each not
    int len_i = 0; // i^th note time length
    int ind = 0; //time interval for the ith note length
    int time_i = 0; // i^th time interval
    int curFreq;
    int curButton;
    int prevFreq = 0;
    int prevButton = 0;
    int score = 0;
    boolean success;
    boolean wrong = false;
    boolean flag_high = true;

    int scale = 3; // length of smallest note
    digitalWrite(SUCC_FLAG,LOW);
    
    while (songON){ //while the song is playing/player has not failed
      while (len_i < sizeof(times)/sizeof(times[0])) { //loop through the entire song at for len_i in times

          ind = 0;
          note_len = scale*times[len_i];
          curFreq = notes[len_i];
          success = 0;
          
          curButton = getButton(curFreq,prevFreq,prevButton);
          
          boolean correctButton[NUM_f] = {0,0,0,0}; 
          if (correctButton != 0){
            correctButton[curButton-1] = 1;
          }
          boolean pressButton[NUM_f] = {0,0,0,0};
         
          while (ind < note_len){ // loop through the length of each not at len_i
            displayBoard(ind,len_i, notes, times, prevFreq, prevButton,scale); // display next 20 notes
            ind ++;
            time_i ++;
  
            note_time = millis();
            while(millis() - note_time < hit_time){ //while a note is in the hit box
              *pressButton = getPress(pressButton);

              //break if an incorrect button pressed
              if (correctButton[0] == 0 and pressButton[0] == 1){
                  wrong = true;
                  break;
              }
              if (correctButton[1] == 0 and pressButton[1] == 1){
                  wrong = true;
                  break;
              }
              if (correctButton[2] == 0 and pressButton[2] == 1){
                  wrong = true;
                  break;
              }
              if (correctButton[3] == 0 and pressButton[3] == 1){
                  wrong = true;
                  break;
              }
              //if correct button matches button presses
              if (pressButton[0] == correctButton[0] and pressButton[1] == correctButton[1] and pressButton[2] == correctButton[2] and pressButton[3] == correctButton[3]){
                if (curButton != 0){ //if there is press required
                  if (success == 0){ //first time the note is hit
                    digitalWrite(SUCC_FLAG,HIGH); //send start tone signal
                  }
                  score ++; 
                }
                success = 1;
              }

              if (false){
                Serial.print(success);
                Serial.print("   ");
                Serial.print(len_i);
                Serial.print('\n');
              }
            }
            if (false) { // true -> higher difficulty
              if (wrong){ //incorrect press condition
                success = 0;
                break;
              }
            }
          }

          digitalWrite(SUCC_FLAG,LOW); //note ends -> stop tone
          prevFreq = curFreq;
          prevButton = curButton;

          if (success == 0){ //the note has not been hit - exit song
            digitalWrite(FAIL_FLAG,HIGH); //send fail condition
            songON = false;
            delay(1000);
            digitalWrite(FAIL_FLAG,LOW); //stop sending
            break;
          } 
          len_i++;
     }
  }
}   



