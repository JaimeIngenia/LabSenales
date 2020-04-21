#include  <Wire.h>
#include<LiquidCrystal.h>

LiquidCrystal LCD(13,12,8,10,11,A1);


//defincion pines de entradad digital
int SELET=A0;
int c0 = 0;//*1
int c1 = 1;//*2
int c2 = 2;//*4
int c3 = 3;//*8
int c4 = 4;//*16
int c5 = 5;//*32
int c6 = 6;//*64
int c7 = 7;//*128


const int freqOutputPin = 9;  
const int ocr1aval  = 16;


void setup() {
  //definicion de pines con entradas de datos analogos
  pinMode(A0, OUTPUT);
  digitalWrite(A0, HIGH);
  pinMode(A1, OUTPUT);
  digitalWrite(A1, HIGH);
//definicion pines como entrada de datos digitales
pinMode(c0, INPUT);pinMode(c1, INPUT);pinMode(c2, INPUT);pinMode(c3, INPUT);pinMode(c4, INPUT); pinMode(c5, INPUT); pinMode(c6, INPUT); pinMode(c7, INPUT);
//inicializar LCD
LCD.begin(16,2);
LCD.home ();

  pinMode(freqOutputPin, OUTPUT);

  TCCR1A = ( (1 << COM1A0));

  TCCR1B = ((1 << WGM12) | (1 << CS10));

  TIMSK1 = 0;

  OCR1A = ocr1aval;



}

void loop() {
//DEFINICION SENSOR DE TEMPERATURA LM 35
float temp;
//FIN DEFINICION SENSOR DE TEMPERATURA
//DEFINICION SENSOR DE CORRIENTE ACS 712 20A
float ins=2.5;//intercecion eje y;
float sens=0.1;//sencibilidad sensor
float tencion;//voltaje sensor
float corriente;//corrienteg
//FIN DEFINICION SENSOR DE CORRIENTE
//iniciacion dato
int dato=0;
  //iniciacion bits
float s0=0; float s1=0; float s2=0; float s3=0; float s4=0; float s5=0; float s6=0; float s7=0;

//sensor de temperatura lm 35
for(int i=0; i<870; i++)
 {
digitalWrite(SELET, LOW);
s0=digitalRead(c0)*1; 
s1=digitalRead(c1)*2; 
s2=digitalRead(c2)*4; 
s3=digitalRead(c3)*8; 
s4=digitalRead(c4)*16; 
s5=digitalRead(c5)*32; 
s6=digitalRead(c6)*64; 
s7=digitalRead(c7)*128;

dato=s0+s1+s2+s3+s4+s5+s6+s7;

 //la temperatura es
temp=(dato*100)/255;
//para evaluar varia muestra de la corriente
temp=temp+0.3;
//para imprimir la temperatura en la LCD
LCD.setCursor(6,0);
LCD.print(temp,3);
LCD.setCursor(1,1);
LCD.print("Grados Celsius");

 }
 //fin codigo sensor temperatura
LCD.clear();
//sensor de corriente ACS 712 20A
s0=0;s1=0; s2=0; s3=0;  s4=0; s5=0;  s6=0;  s7=0;
for(int i=0;i<870;i++)
 { 
 digitalWrite(SELET, HIGH);
s0=digitalRead(c0)*1; 
s1=digitalRead(c1)*2; 
s2=digitalRead(c2)*4; 
s3=digitalRead(c3)*8; 
s4=digitalRead(c4)*16; 
s5=digitalRead(c5)*32; 
s6=digitalRead(c6)*64; 
s7=digitalRead(c7)*128;
dato=s0+s1+s2+s3+s4+s5+s6+s7;
 //la tencion es
tencion=(dato*5.0)/255;
//para evaluar varia muestra de la corriente
corriente=(tencion-ins)/sens;
//para imprimir la corriente en el LCD
LCD.setCursor(6,0);
LCD.print(corriente,3);
LCD.setCursor(5,1);
LCD.print("Amperios");
 }
 LCD.clear();
 delay (10);
}
//fin codigo sensor de corriente
