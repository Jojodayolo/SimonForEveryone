//Includes
#include <Wtv020sd16p.h>
#include <Bounce2.h>
// defining LedsPin
  #define LED_RED 26
  #define LED_BLUE 25
  #define LED_GREEN 27
  #define LED_YELLOW 14
// defining buttonsPins
  #define BUTTON_RED 34
  #define BUTTON_BLUE 39
  #define BUTTON_GREEN 35
  #define BUTTON_YELLOW 32
// defining AudioPins
  #define RESET_PIN 0  // The pin number of the reset pin.
  #define CLOCK_PIN 4  // The pin number of the clock pin.
  #define DATA_PIN 15  // The pin number of the data pin.
  #define BUSY_PIN 2  // The pin number of the busy pin.
//defining audio Files
  //Collors
    #define RED_SOUND 1
    #define BLUE_SOUND 2
    #define GREEN_SOUND 4
    #define YELLOW_SOUND 3
  //Menue
    #define INTRODUCTION_SOUND 5

//Global variabels 
  bool redButtonPressed = false;
  bool blueButtonPressed = false;
  bool greenButtonPressed = false;
  bool yellowButtonPressed = false;
  int globalGameMode = 0;
  bool firstMenuCall = true; 
  int gameSpeed = 1000;
//Musster Storage
  byte pattern[100];
  byte patternPoss = 0;
  byte patternLength = 0;

//Define Audio Module
  Wtv020sd16p wtv020sd16p(RESET_PIN,CLOCK_PIN,DATA_PIN,BUSY_PIN);
  
// Define Inputs / outputs
  void defineIO(){
    //Buttons
    pinMode(BUTTON_RED,INPUT);
    pinMode(BUTTON_BLUE,INPUT);
    pinMode(BUTTON_GREEN,INPUT);
    pinMode(BUTTON_YELLOW,INPUT);
    //led pins 
    pinMode(LED_RED,OUTPUT);
    digitalWrite(LED_RED, false);
    pinMode(LED_BLUE,OUTPUT);
    digitalWrite(LED_BLUE, false); 
    pinMode(LED_GREEN,OUTPUT);
    digitalWrite(LED_GREEN, false); 
    pinMode(LED_YELLOW,OUTPUT);
    digitalWrite(LED_YELLOW, false);  
  }

//Led Function 
  void ledOn(int pin){
    digitalWrite(pin,true);
  }
  void ledOff(int pin){
    digitalWrite(pin,false);
  }

//Led Blink
  void ledBlink(int pin, int t){
    ledOn(pin);
    delay(t);
    ledOff(pin);
  }

//Shows Pattern With out Audio
  void showPattern(){
    delay(500);
    int i = 0;
    while(i < patternLength){
      Serial.println(pattern[i]);
        if(pattern[i] == 0){ //Wenn farbe rot
            ledBlink(LED_RED,gameSpeed);
        }
        else if(pattern[i] == 1){ // Wenn farbe balu
            ledBlink(LED_BLUE,gameSpeed);
        }
        else if(pattern[i] == 2){ //Wenn Farbe grün
            ledBlink(LED_GREEN,gameSpeed);
        }
        else if(pattern[i] == 3){ //Wenn Farbe Gelb
            ledBlink(LED_YELLOW,gameSpeed);
        }
        delay(200);
        i++;
    }
  }
//Show Pattern With Sound output
  void showPatternSound(){
    delay(500);
    int i = 0;
    while(i < patternLength){
      Serial.println(pattern[i]);
        if(pattern[i] == 0){
            ledOn(LED_RED);
            wtv020sd16p.asyncPlayVoice(RED_SOUND);
            delay(1000);
            ledOff(LED_RED);
        }
        else if(pattern[i] == 1){
            ledOn(LED_BLUE);
            wtv020sd16p.asyncPlayVoice(BLUE_SOUND);
            delay(1000);
            ledOff(LED_BLUE);
        }
        else if(pattern[i] == 2){
            ledOn(LED_GREEN);
            wtv020sd16p.asyncPlayVoice(GREEN_SOUND);
            delay(1000);
            ledOff(LED_GREEN);
        }
        else if(pattern[i] == 3){
            ledOn(LED_YELLOW);
            wtv020sd16p.asyncPlayVoice(YELLOW_SOUND);
            delay(1000);
            ledOff(LED_YELLOW);
        }
        delay(200); 
        i++;
    }
  }
//Game Over Sequenz
  void gameOver(){
        Serial.println("Game Over");
        globalGameMode = 0;
        firstMenuCall = true;
        patternPoss = 0;
        patternLength = 0;
        ledOn(LED_RED);
        ledOn(LED_BLUE);
        ledOn(LED_GREEN);
        ledOn(LED_YELLOW);
        delay(500);
        ledOff(LED_RED);
        ledOff(LED_BLUE);
        ledOff(LED_GREEN);
        ledOff(LED_YELLOW);
        redButtonPressed = false;
        blueButtonPressed = false;
        greenButtonPressed = false;
        yellowButtonPressed = false;
  }
//Classic Game
  void classicGame(){
    if(patternLength == patternPoss){
      int newCollor = random(4);
      Serial.print("New Collo:");
      Serial.println(newCollor);
      pattern[patternLength] = newCollor;
      patternLength++;
      patternPoss = 0;
      showPattern();
    }else{
      //check for blue button press
      if(redButtonPressed){
        Serial.println("Red Button Pressed and registerd ");
        //check if pattern is corect
        ledBlink(LED_RED,200);
        redButtonPressed = false;
        if(pattern[patternPoss] == 0){
          Serial.println("Red Button was correct");
          patternPoss++;
          return;
        }else{
          gameOver();
          return;
        }
      }
      //check for blue button press
      if(blueButtonPressed){
        Serial.println("Blue Button Pressed and registerd ");
        //check if pattern is correct
        ledBlink(LED_BLUE,200);
        blueButtonPressed = false;
        if(pattern[patternPoss] == 1){
          Serial.println("blue Button was correct");
          patternPoss++;
          return;
        }else{
          gameOver();
          return;
        }
      }
      //check for green button press
      if(greenButtonPressed == true){
        Serial.println("green Button Pressed and registerd ");
        //check if pattern is correct
        ledBlink(LED_GREEN,200);
        greenButtonPressed = false;
        if(pattern[patternPoss] == 2){
          Serial.println("green Button was correct");
          patternPoss++;
          return;
        }else{
          gameOver();
          return;
        }
      }
      //check for yellow button press
      if(yellowButtonPressed == true){
        Serial.println("yellow Button Pressed and registerd ");
        //check if pattern is correct
        ledBlink(LED_YELLOW,200);
        yellowButtonPressed = false;
        if(pattern[patternPoss] == 3){
          Serial.println("blue Button was correct");
          patternPoss++;
          return;
        }else{
          gameOver();
          return;
        }
      }      
    }
  }

//Audio Game
  void audioGame(){
    if(patternLength == patternPoss){
      patternLength++;
      pattern[patternLength] = random(4);
      patternPoss = 0;
      showPatternSound();
    }else{
      //check for blue button press
      if(redButtonPressed){
        Serial.println("Red Button Pressed and registerd ");
        //check if pattern is corect
         ledBlink(LED_RED,200);
        redButtonPressed = false;
        if(pattern[patternPoss] == 0){
          Serial.println("Red Button was correct");
          patternPoss++;
          return;
        }else{
          gameOver();
          return;
        }
      }
      //check for blue button press
      if(blueButtonPressed){
        Serial.println("Blue Button Pressed and registerd ");
        //check if pattern is correct
         ledBlink(LED_BLUE,200);
        blueButtonPressed = false;
        if(pattern[patternPoss] == 1){
          Serial.println("blue Button was correct");
          patternPoss++;
          return;
        }else{
          gameOver();
          return;
        }
      }
      //check for green button press
      if(greenButtonPressed == true){
        Serial.println("green Button Pressed and registerd ");
        //check if pattern is correct
         ledBlink(LED_GREEN,200);
        greenButtonPressed = false;
        if(pattern[patternPoss] == 2){
          Serial.println("green Button was correct");
          patternPoss++;
          return;
        }else{
          gameOver();
          return;
        }
      }
      //check for yellow button press
      if(yellowButtonPressed == true){
        Serial.println("yellow Button Pressed and registerd ");
        //check if pattern is correct
         ledBlink(LED_YELLOW,200);
        yellowButtonPressed = false;
        if(pattern[patternPoss] == 3){
          Serial.println("blue Button was correct");
          patternPoss++;
          return;
        }else{
          gameOver();
          return;
        }
      }      
    }
  }

//deboucer
Bounce debounceRed = Bounce();
Bounce debounceBlue = Bounce();
Bounce debounceGreen = Bounce();
Bounce debounceYellow = Bounce();


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  wtv020sd16p.reset();
  randomSeed(analogRead(13));
  defineIO();
  debounceRed.attach(BUTTON_RED);
  debounceRed.interval(25);
  debounceBlue.attach(BUTTON_BLUE);
  debounceBlue.interval(25);
  debounceGreen.attach(BUTTON_GREEN);
  debounceGreen.interval(25);
  debounceYellow.attach(BUTTON_YELLOW);
  debounceYellow.interval(25);
}

void loop() {
	//Cecking Button Presses
  debounceRed.update();
  debounceBlue.update();
  debounceGreen.update();
  debounceYellow.update();
  //Checking Buttons For Menue
  if(debounceRed.fell()){
    redButtonPressed = true;
    Serial.println("RED BUTTON!!!");
  }
  if(debounceBlue.fell()){
    blueButtonPressed = true;
    Serial.println("BLUE BUTTON!!!");
  }
  if(debounceGreen.fell()){
    greenButtonPressed = true;
    Serial.println("GREEN BUTTON!!!");
  }
  if(debounceYellow.fell()){
    yellowButtonPressed = true;
    Serial.println("YELLOW BUTTON!!!");
  }
  if(globalGameMode == 0){
	//if no game running
    if(firstMenuCall){
	  //If gaame endet 
      wtv020sd16p.playVoice(INTRODUCTION_SOUND);
      firstMenuCall = false;
    }
    if(redButtonPressed){
		//if red Button Pressed start game without voice
        Serial.println("Start Game");
        globalGameMode = 1;
        ledOn(LED_RED);
        ledOn(LED_BLUE);
        ledOn(LED_GREEN);
        ledOn(LED_YELLOW);
        delay(500);
        ledOff(LED_RED);
        ledOff(LED_BLUE);
        ledOff(LED_GREEN);
        ledOff(LED_YELLOW);
        firstMenuCall = true;
        redButtonPressed = false;
    }
    if(greenButtonPressed){
		//if green button presset start game with voice
        Serial.println("Start Audio Game");
        globalGameMode = 2;
        ledOn(LED_RED);
        ledOn(LED_BLUE);
        ledOn(LED_GREEN);
        ledOn(LED_YELLOW);
        delay(500);
        ledOff(LED_RED);
        ledOff(LED_BLUE);
        ledOff(LED_GREEN);
        ledOff(LED_YELLOW);
        firstMenuCall = true;
        greenButtonPressed = false;
    }
  }
  if(globalGameMode == 1){
	  //if game mode eins call the classic game 
    classicGame();
  }
  if(globalGameMode == 2){
	  //if game mode eins call the classic game
    audioGame();
  }

}
