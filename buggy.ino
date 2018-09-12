
#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h"

#define SD_ChipSelectPin 53

#define GREEN_BUTTON 2
#define RED_BUTTON 3
#define BLUE_BUTTON 4

#define BLUE_LED 22
#define GREEN_LED 23
#define RED_LED 24
#define NOSE_LED 10

#define AUDIO 11
#define AUDIO_VOLUME 5
#define SERIAL_RATE 9600

TMRpcm output_audio;
long random_seed;
bool triggered;
int pin8state = 0;
int pin9state = 0;
int pin10state = 0;

void setup(){

  random_seed = 0;

  output_audio.speakerPin=AUDIO;

  Serial.begin(SERIAL_RATE);

  pinMode(BLUE_BUTTON,INPUT);
  pinMode(GREEN_BUTTON,INPUT);
  pinMode(RED_BUTTON,INPUT);

  pinMode(BLUE_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);
  pinMode(RED_LED,OUTPUT);
  pinMode(NOSE_LED,OUTPUT);


  if (SD.begin(SD_ChipSelectPin)){
    Serial.println("SD init successfully!");
    }

  else {
    Serial.println("SD init fail...");
    return;
    }

  output_audio.setVolume(AUDIO_VOLUME);

  welcome();

}


void loop() {

    pin8state = digitalRead(BLUE_BUTTON);
    pin9state = digitalRead(GREEN_BUTTON);
    pin10state = digitalRead(RED_BUTTON);

    if (pin8state==HIGH){
      //delay(1000);
      pin8state = LOW;
      Serial.println("premuto tasto blu");
      blue_function();
    }

    else if (pin9state==HIGH){
      //delay(1000);
      pin9state = LOW;
      Serial.println("premuto tasto verde");
      green_function();
    }

    else if (pin10state==HIGH){
      //delay(1000);
      pin10state = LOW;
      Serial.println("premuto tasto rosso");
      red_function();
    }

    random_seed++;

}


void welcome() {

  output_audio.play("welcome.wav");
  Serial.println("Playing welcome");
  leds_on();
  delay(3000);

}


void leds_on(){

  digitalWrite(BLUE_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, HIGH);

}


void blue_function(){

  Serial.println("Avviata blue_function()");
  digitalWrite(NOSE_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  word_selector(0);

}


void green_function(){

  Serial.println("Avviata green_function()");
  digitalWrite(NOSE_LED, HIGH);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, LOW);
  word_selector(1);

}


void red_function(){

  Serial.println("Avviata red_function()");
  digitalWrite(NOSE_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  word_selector(2);

}


void word_selector(int choice){

  output_audio.play("scelta.wav");
  delay(4300);
  randomSeed(int(random_seed));
  int randomSelection = random(0,9);
  String sorted;

  switch (choice){

    case 0:
      who_choose_audio();
      sorted = sort_who(randomSelection);
      break;

    case 1:
      where_choose_audio();
      sorted = sort_where(randomSelection);
      break;

    case 2:
      when_choose_audio();
      sorted = sort_when(randomSelection);
      break;

  }

  char* filename = strcat(sorted.c_str(),".wav");

  Serial.print("Playing ");
  Serial.println(filename);

  output_audio.play(filename);
  delay(2800);

  restart();

}


void restart(){

  leds_on();
  digitalWrite(NOSE_LED,LOW);
  output_audio.play("restart.wav");
  delay(2000);
}


void who_choose_audio(){
  output_audio.play("chi.wav");
  delay(2000);
}


void where_choose_audio(){
  output_audio.play("luogo.wav");
  delay(2000);
}


void when_choose_audio(){
  output_audio.play("quando.wav");
  delay(2000);
}


String sort_who(int number){

  String sorting;

  switch (number){

    case 0:
      sorting = "aquilone";
      break;
    case 1:
      sorting = "buggy";
      break;
    case 2:
      sorting = "farfalla";
      break;
    case 3:
      sorting = "folletto";
      break;
    case 4:
      sorting = "formica";
      break;
    case 5:
      sorting = "fragola";
      break;
    case 6:
      sorting = "gatto";
      break;
    case 7:
      sorting = "matita";
      break;
    case 8:
      sorting = "pittore";
      break;
    case 9:
      sorting = "uva";
      break;

  }


  output_audio.play("introchi.wav");
  delay(4500);

  return sorting;

}


String sort_where(int number){

  String sorting;

  switch (number){

    case 0:
      sorting = "bicchier";
      break;
    case 1:
      sorting = "bosco";
      break;
    case 2:
      sorting = "castello";
      break;
    case 3:
      sorting = "cucina";
      break;
    case 4:
      sorting = "fiume";
      break;
    case 5:
      sorting = "luna";
      break;
    case 6:
      sorting = "spazio";
      break;
    case 7:
      sorting = "nuvola";
      break;
    case 8:
      sorting = "oceano";
      break;
    case 9:
      sorting = "spiaggia";
      break;

  }

  output_audio.play("introdov.wav");
  delay(3500);

  return sorting;

}


String sort_when(int number){

  String sorting;

  switch (number){

    case 0:
      sorting = "autunno";
      break;
    case 1:
      sorting = "complean";
      break;
    case 2:
      sorting = "dormire";
      break;
    case 3:
      sorting = "estate";
      break;
    case 4:
      sorting = "inverno";
      break;
    case 5:
      sorting = "natale";
      break;
    case 6:
      sorting = "primaver";
      break;
    case 7:
      sorting = "riposano";
      break;
    case 8:
      sorting = "scuola";
      break;
    case 9:
      sorting = "tramonto";
      break;

  }

  output_audio.play("introqua.wav");
  delay(3000);

  return sorting;

}
