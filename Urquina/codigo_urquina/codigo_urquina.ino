//Codigo del Equipo y simulacion LAB-4_T_EQU-6, equipo 06.
#include <TimerOne.h>

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int pin_pwm=9; 
const int rs = 13, en = 12, d4 = 8, d5 = 10, d6 = 11, d7 = A1;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int pin0=0,pin1=1,pin2=2,pin3=3,pin4=4,pin5=5,pin6=6,pin7=7,select=A0;

void setup() {
  // set up the LCD's number of columns and rows:
lcd.begin(16,2);
  pinMode(0,INPUT);
  pinMode(1,INPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  pinMode(9,OUTPUT); //Salida de reloj para el ADC
  pinMode(A0,OUTPUT);
  Reloj();
}

void loop() {
  //DEFINICION SENSOR DE CORRIENTE ACS 712 20A
  float ins=2.5;//intercecion eje y;
  float sens=0.1;//sencibilidad sensor
  float tencion;//voltaje sensor
  float corriente;//corrienteg
  //FIN DEFINICION SENSOR DE CORRIENTE
  
  int decimal,a0,a1,a2,a3,a4,a5,a6,a7;
  float temp,lum;

  lcd.clear();
  lcd.clear();
  lcd.clear();
  lcd.clear();
  lcd.clear();
  
  for (int i=0 ; i<939 ; i++){
   digitalWrite(select,HIGH);
  a0=digitalRead(pin0);
  a1=digitalRead(pin1);
  a2=digitalRead(pin2);
  a3=digitalRead(pin3);
  a4=digitalRead(pin4);
  a5=digitalRead(pin5);
  a6=digitalRead(pin6);
  a7=digitalRead(pin7);
  decimal=a0*(1)+a1*(2)+a2*(4)+a3*(8)+a4*(16)+a5*(32)+a6*(64)+a7*(128);

  //Ecuacion Para Sensor De ...
   //la tencion es
tencion=(decimal*5.0)/255;
//para evaluar varia muestra de la corriente
corriente=(tencion-ins)/sens;
 
 // lum=((0.000000000000007)*(decimal)*(decimal))+(0.000000000000005*(decimal))+0.4926;
  lcd.setCursor(0,1);
  lcd.print("A");
  lcd.setCursor(2,1);
  lcd.print(corriente);
  lcd.setCursor(9,1);
  lcd.print("Amp");;
  }

  
   lcd.clear();
  lcd.clear();
   lcd.clear();
   lcd.clear();
   lcd.clear();

  
  for (int i=0 ; i<939 ; i++){
    digitalWrite(select,LOW);
  a0=digitalRead(pin0);
  a1=digitalRead(pin1);
  a2=digitalRead(pin2);
  a3=digitalRead(pin3);
  a4=digitalRead(pin4);
  a5=digitalRead(pin5);
  a6=digitalRead(pin6);
  a7=digitalRead(pin7);
  decimal=a0*(1)+a1*(2)+a2*(4)+a3*(8)+a4*(16)+a5*(32)+a6*(64)+a7*(128);
  //Ecuacion para la Temperatura
  temp=((0.0012*decimal*decimal) + (1.8864*decimal) + 0.4926);
  temp=temp+0.6;
  lcd.setCursor(0,0);
  lcd.print("T");
  lcd.setCursor(2,0);
  lcd.print(temp);
  lcd.setCursor(9,0);
  lcd.print("Celsius");
  }  
}
void Reloj(){
  //Se configura el Timer2(8bits) mediante registros
  TCCR2A = B00000000; //Timer2 en operación normal
  TCCR2B = B00000001; //Prescaler en 1 (P=1)
  TCNT2  = 0;  //Inicializar valor de cuenta en 0
  //Fórmula para valor de comparación: (16MHz/(P*F,deseada)) - 1
  OCR2A = 15;// (16E6) / (1*1E6) - 1 = 15
  TIMSK2 = B00000010; //Habilitar la interrupción A del Timer2
  sei(); //Habilitar interrupciones
}

//Programación de la interrupción del Timer2
ISR(TIMER2_COMPA_vect){
  //Invertir el pin 9 (PB1) para generar onda cuadrada
  PORTB=PORTB^0B00000010;
}
