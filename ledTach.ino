/*
written for arduino uno:
learn to write for nano, get nano connector and firmware
*/

//fastLED library
#include "FastLED.h"

//constants for LED control
#define LED_DATA_PIN 6 //digital out #6
#define COLOR_ORDER GRB//This is the correct order for the ws2812B being used
#define NUM_LEDS 8//switch to 16 when chaining two sticks together
#define LED_TYPE WS2812B

//god im so clever
#define BEGINNING_RPM 6000
#define INCR_AMT 1000

//brightness constants (pretty much arbitrary from other scripts)
//only used in flash to soften-up the transition
uint8_t lowBrightness = 32; //less
uint8_t highBrightness = 255;//pretty sure max

//make sure to declare led array outside of setup
CRGB tachometer[NUM_LEDS];

void setup() {
  //instantiator/constructor for "tachometer" array
  FastLED.addLeds<LED_TYPE, LED_DATA_PIN, COLOR_ORDER>(tachometer, NUM_LEDS);

  //connect with machine (not being used currently)
  Serial.begin(9600);
  Serial.print("setup complete");

  //construct/set up rpm reader/parser stuff HERE:
  
  //put any boot-up animation you want here
  bootAnimation();
}

//initialize variables (Build real rpm parser later)
int rpm = 5001;

//global flash flag, outside loop bc needs updating
int flashFlag = 0;

void loop() {
  //read in new RPM here (come up with functions later)
  
  setTach(rpm);
  
}









void setTach(int rpm){
  //note:
  //if immediate should be fastest way to do this in any environment,
  //return if rpm < beginning rpm to run faster (car/systems won't be strained here anyways)
  //inside function so that I can return and save time if negligible/low rpm
  //each if sets off all LEDs after it (which will be set back on if the rpm is high enough)
  //checking for a change in each led would be the same speed as this "run-through"

  //each cycle, set all LEDs off, set on each LED to each individ. if until exit
  setClear(0);
  
  //will HAVE to be the case if first statement not thrown,
  if(rpm > BEGINNING_RPM){
    //first LED on
    tachometer[0] = CRGB::Green;
  }else{
    FastLED.show();
    return;
  }
  
  if(rpm > BEGINNING_RPM+INCR_AMT){
    //second LED on
    tachometer[1] = CRGB::Green;
  }else{
    FastLED.show();
    return;
  }
  
  if(rpm > BEGINNING_RPM+INCR_AMT*2){
    //third LED on
    tachometer[2] = CRGB::Blue;
  }else{
    FastLED.show();
    return;
  }
  
  if(rpm > BEGINNING_RPM+INCR_AMT*3){
    //fourth LED on
    tachometer[3] = CRGB::Blue;
  }else{
    FastLED.show();
    return;
  }
  
  if(rpm > BEGINNING_RPM+INCR_AMT*4){
    //fiftth LED on
    tachometer[4] = CRGB::Orange;
  }else{
    FastLED.show();
    return;
  }
  
  if(rpm > BEGINNING_RPM+INCR_AMT*5){
    //sixth LED on
    tachometer[5] = CRGB::Orange;
  }else{
    FastLED.show();
    return;
  }
  
  if(rpm > BEGINNING_RPM+INCR_AMT*6){
    //seventh LED on
    tachometer[6] = CRGB::Red;
  }else{
    FastLED.show();
    return;
  }
  
  if(rpm > BEGINNING_RPM+INCR_AMT*7){
    //eigth LED on
    tachometer[7] = CRGB::Red;
    //no need for setClear because this is last LED
  }else{
    FastLED.show();
    return;
  }
  
  if(rpm > BEGINNING_RPM+INCR_AMT*8){
    
    //flash if greater than 14k (current setting)
    //could create loop to flash if
    //CALL FLASH FUNCTION HERE, protothread/scheduler so flash (and its pause) can occur while
    //other parts of the code function, this means update will also exist within flash function
    //http://arduino.stackexchange.com/questions/286/how-can-i-create-multiple-running-threads

    flashFlag = flash(flashFlag);

  }else{
    //this will show all LEDs lit up, no flash (under max rpm, at limit)
    FastLED.show();
    return;
  }
}


//write cool animations for standby/showoff
void loiter(){
  return;
}




void bootAnimation(){
  //write something cool later
  return;
}

//returns int bc call by value C++ bullshit
//flashflag should have a range of 0-3
int flash(int flashflag){
  if(flashflag == 0){
    //on full
    setAll();
    FastLED.show(highBrightness);
    //maybe move later
    delay(50);
    return 1;
  }else if(flashflag == 1){
    //on mid
    setAll();
    FastLED.show(lowBrightness);
    //maybe move later
    delay(50);
    return 2;
  }else if(flashflag == 2){
    //off
    setClear(0);
    FastLED.show();
    //maybe move later
    delay(50);
    return 3;
  }else if(flashflag == 3){
    //on mid
    setAll();//PASS BRIGHTNESS
    FastLED.show(lowBrightness);
    //maybe move later
    delay(50);
    return 0;
  }else{
    //dude you broke it
  }
  //returh flashflag
}

//this clears all the leds that exist after the first if statement
//that fails.  (leds will stay ON until correctly cleared)
//this function doesnt use show
void setClear(int cur){
  for(int current = cur; current < NUM_LEDS; current++) {
    tachometer[current] = CRGB::Black;
  }
}

//pass in color, set all in tach that color
void setAll(){
  for(int i = 0; i < NUM_LEDS; i++){
    tachometer[i] = CRGB::Red;
  }
}
/*
//not currently used
//quick function to clear whole tach
//might use in flash
void clearFull(){
  for(int current = 0; current < NUM_LEDS; current++) {
    tachometer[current] = CRGB::Black;
    FastLED.show();
  }
}
*/



