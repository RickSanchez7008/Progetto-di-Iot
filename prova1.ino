#include "Stepper.h"
#include "IRremote.h"
#include "SR04.h"
#include "pitches.h"
#include <dht_nonblocking.h>

#define TIPO DHT_TYPE_11
#define STEPS  32 
#define AVANTI 6
#define DIETRO 7
#define TPIN 5
#define EPIN 4

long a;
int  Steps2Take; 
int receiver=12;
int i=0;
int melody[] = {NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
int duration = 500;
static const int PINTEMP = 3;

DHT_nonblocking dht_sensor( PINTEMP, TIPO );
SR04 sr04 = SR04(EPIN,TPIN);
Stepper stepper(STEPS,8,10,9,11);
IRrecv irrecv(receiver);
uint32_t last_decodedRawData = 0;



void setup() {
  irrecv.enableIRIn();
  pinMode(AVANTI,OUTPUT);
  pinMode(DIETRO,OUTPUT);
  Serial.begin(9600);
}

static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );


    if(dht_sensor.measure(temperature,humidity)==true)
    {
      return(true);
    }else{
      for(i=0;i<2;i++){
      tone(2,melody[8],duration);
      }
      i=0;
      return(false);
    }
}


void loop() {
  float temperature;
  float humidity;
  
  if (irrecv.decode()){
    if (irrecv.decodedIRData.flags)
    {
      irrecv.decodedIRData.decodedRawData = last_decodedRawData;
    }
    
    switch (irrecv.decodedIRData.decodedRawData)
    {
      case 0xA55AFF00: // caso "gira a destra" cliccando 6

        
        stepper.setSpeed(700);
        Steps2Take  =  -256;  //ruota di 45 gradi
        stepper.step(Steps2Take);
        delay(1000);       
        Steps2Take  =  +256; //torna nella posizione iniziale   
        stepper.step(Steps2Take);
        delay(200);  
      break;

      case 0xF708FF00: //caso "gira a sinistra" cliccando 4
        
        stepper.setSpeed(700); 
        Steps2Take  =  +256;  
        stepper.step(Steps2Take);
        delay(1000);       
        Steps2Take  =  -256;  
        stepper.step(Steps2Take);
        delay(200);  
      break;  

      case 0xE718FF00: //2 AVANTI
        digitalWrite(AVANTI,HIGH);
        digitalWrite(DIETRO,LOW); 
        delay(5000);
        digitalWrite(AVANTI,LOW);
        digitalWrite(DIETRO,LOW); 
        
      break;

      case 0xAD52FF00: //8  INDIETRO
        a=sr04.Distance();

        digitalWrite(DIETRO,HIGH);
        digitalWrite(AVANTI,LOW); 

        delay(2000);
        digitalWrite(AVANTI,LOW);
        digitalWrite(DIETRO,LOW); 

        if(a==3){
          tone(2,melody[1],duration);
          delay(500);
        }else if(a==2){
          tone(2,melody[2],duration);
          delay(500);
        }else if(a==1){
          tone(2,melody[3],duration);
          delay(500);
        }else{break;}

        case 0xA15EFF00: //avanti destra 3
        i=0;
          switch(i=0){
            case 0:
            stepper.setSpeed(700); 
            Steps2Take  =  -256;  
            stepper.step(Steps2Take);
            delay(100);
            case 1:
            digitalWrite(AVANTI,HIGH);
            digitalWrite(DIETRO,LOW);
            delay(5000);
            digitalWrite(AVANTI,LOW);
            digitalWrite(DIETRO,LOW);
            delay(100);
            case 2:
            Steps2Take  =  +256; //torna nella posizione iniziale   
            stepper.step(Steps2Take);
            delay(200); 
            i=1;
            break;
          }
          break;

        case 0xF30CFF00: //avanti sinistra 1
        i=0;
          switch(i=0){
            case 0:
            stepper.setSpeed(700);
            Steps2Take  =  +256;  //ruota di 45 gradi
            stepper.step(Steps2Take);
            delay(100);
            case 1:
            digitalWrite(AVANTI,HIGH);
            digitalWrite(DIETRO,LOW);
            delay(5000);
            digitalWrite(AVANTI,LOW);
            digitalWrite(DIETRO,LOW);
            delay(100);
            case 2:
            Steps2Take  =  -256;  
            stepper.step(Steps2Take);
            delay(200);  
            i=1;
            break;
          }
          break;

        case 0xBD42FF00: //7 dietro sinistra
           i=0;
            switch(i=0){
            case 0:
            stepper.setSpeed(700);
            Steps2Take  =  +256;  //ruota di 45 gradi
            stepper.step(Steps2Take);
            delay(100);
            case 1:
            digitalWrite(DIETRO,HIGH);
            digitalWrite(AVANTI,LOW); 
            delay(2000);
            digitalWrite(AVANTI,LOW);
            digitalWrite(DIETRO,LOW); 
            delay(100);
            case 2:
            Steps2Take  =  -256;  
            stepper.step(Steps2Take);
            delay(200);  
            i=1;
            break;
          }
          if(a==3){
          tone(2,melody[1],duration);
          delay(500);
          goto end;
          }else if(a==2){
          tone(2,melody[2],duration);
          delay(500);
          goto end;
          }else if(a==1){
          tone(2,melody[3],duration);
          delay(500);
          goto end;
          }



        case 0xB54AFF00: //9 dietro destra
                   i=0;
            switch(i=0){
            case 0:
            stepper.setSpeed(700);
            Steps2Take  =  -256;  //ruota di 45 gradi
            stepper.step(Steps2Take);
            delay(100);
            case 1:
            digitalWrite(DIETRO,HIGH);
            digitalWrite(AVANTI,LOW); 
            delay(2000);
            digitalWrite(AVANTI,LOW);
            digitalWrite(DIETRO,LOW); 
            delay(100);
            case 2:
            Steps2Take  =  +256;  
            stepper.step(Steps2Take);
            delay(200);  
            i=1;
            break;
          }
          if(a==3){
          tone(2,melody[1],duration);
          delay(500);
          }else if(a==2){
          tone(2,melody[2],duration);
          delay(500);
          }else if(a==1){
          tone(2,melody[3],duration);
          delay(500);
          }else{break;}

    }


    //spengo lo stepmotor
    end:
    last_decodedRawData = irrecv.decodedIRData.decodedRawData;
    irrecv.resume(); 
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    if( measure_environment( &temperature, &humidity ) == true ){ 
          if(temperature >= 41){
            for(i=0;i<3;i++){
              tone(2,melody[4],duration);
              delay(1000);
              }
              i=0;
              
          }
        }
  }
}



