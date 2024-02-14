#include <Wire.h>
#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include "Adafruit_TCS34725.h"

#include <SoftwareSerial.h>
SoftwareSerial softSerial(8,9);
#define FPSerial softSerial

#define lightA    A1
#define lightB    A6
#define lightUVA  A2
#define lightUVB  A3

#define key1 10
#define key2 11
#define key3 12

#define commonAnode true
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
float color[3];
int brightA,brightB,UVA,UVB;
const int cashNumb[7] = {100,50,20,10,5,2,1};
int note=0,Numb = 0, totalCash = 0;
bool volUP, volDN, keyOK;
bool statusObj = false, statusNote = false;

DFRobotDFPlayerMini myDFPlayer;

void setup() {
  Serial.begin(115200);
  FPSerial.begin(9600);
  tcs.begin();

  pinMode(lightA, INPUT);
  pinMode(lightB, INPUT);
  pinMode(lightUVA, INPUT);
  pinMode(lightUVB, INPUT);
  pinMode(key1, INPUT);
  pinMode(key2, INPUT);
  pinMode(key3, INPUT);

  myDFPlayer.begin(FPSerial,true,true);
  myDFPlayer.setTimeOut(500);

  myDFPlayer.volume(25);  //Set volume value (0~30).
}

void voice(int nominal)
{
  int satuan = nominal%10/1;
  int puluhan = nominal%100/10;
  int ratusan = nominal%1000/100;
  int ribuan = nominal%10000/1000;

  if(ribuan > 0){if(ribuan == 1){myDFPlayer.play(11);delay(1000);} else{myDFPlayer.play(ribuan+1);delay(2000);} myDFPlayer.play(14);delay(2000);}
  if(ratusan > 0){if(ratusan == 1){myDFPlayer.play(11);delay(1000);} else{myDFPlayer.play(ratusan+1);delay(2000);}myDFPlayer.play(16);delay(2000);}
  if(puluhan > 0){if(puluhan == 1){myDFPlayer.play(11);delay(1000);} else{myDFPlayer.play(puluhan+1);delay(2000);} myDFPlayer.play(1);delay(2000);}
  if(satuan > 0){if(satuan == 1){myDFPlayer.play(11);delay(1000);} else{myDFPlayer.play(satuan+1);delay(2000);}} myDFPlayer.play(13);delay(2000);
  
  Serial.println();
  Serial.print("Total : Rp.");
  Serial.print(ribuan);
  Serial.print(ratusan);
  Serial.print(puluhan);
  Serial.print(satuan);
  Serial.println(".000");
}

void loop() {
  brightA = analogRead(lightA);
  brightB = analogRead(lightB);
  UVA = analogRead(lightUVA);
  UVB = analogRead(lightUVB);
  volUP = digitalRead(key1);
  volDN = digitalRead(key2);
  keyOK = digitalRead(key3);

  if(!volUP){note++; delay(500);}
  if(!volDN){note--; delay(500);}

  if(note<0){note=0;}
  else if(note>18){note=18;}
  if(!keyOK){voice(totalCash);totalCash = 0; delay(500);}
  
  if(brightA+brightB >= 1400){statusObj = true;}
  else{statusObj = false;}

  if(!statusNote and statusObj)
  {
    delay(500);
    statusNote = true;
    tcs.setInterrupt(false);
    delay(60);
    tcs.getRGB(&color[0], &color[1], &color[2]);
    tcs.setInterrupt(true);
    Neural_Network();
    voice(cashNumb[Numb]);
  }
  if(statusNote and !statusObj)
  {
    statusNote = false; myDFPlayer.play(18);  
    totalCash += cashNumb[Numb];
    Serial.print("R:"); Serial.print(color[0]); 
    Serial.print(" G:"); Serial.print(color[1]); 
    Serial.print(" B:"); Serial.print(color[2]);
//    Serial.print(" ST"); Serial.print(statusObj); 
//    Serial.print(" "); Serial.print(UVA);
//    Serial.print(" "); Serial.print(UVB);
    Serial.print("\n");
    delay(500);
  }
//    Serial.print("R:"); Serial.print(color[0]); 
//    Serial.print(" G:"); Serial.print(color[1]); 
//    Serial.print(" B:"); Serial.print(color[2]);
//    Serial.print(" SA"); Serial.print(brightA); 
//    Serial.print(" SB"); Serial.print(brightB);
//    Serial.print(" UVA"); Serial.print(UVA);
//    Serial.print(" UVB"); Serial.print(UVB);
//    Serial.print("\n");
}
