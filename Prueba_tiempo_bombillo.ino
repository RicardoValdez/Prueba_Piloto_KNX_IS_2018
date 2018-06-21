#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 RTC;

int tiempo;   //variable global de tiempo encendido
int led = 13; //PIN de encendido del LED cada vez que el bombillo se enciende
int luz = 3;  //PIN de detección de encendido del bombillo
boolean luzConect;

void setup() {
  Wire.begin(); // Inicia el puerto I2C
  RTC.begin(); // Inicia la comunicación con el RTC
  //RTC.adjust(DateTime(__DATE__, __TIME__)); // Establece la fecha y hora (Comentar una vez establecida la hora)
  pinMode(led, OUTPUT);
  pinMode(luz, INPUT);
  Serial.begin(9600);
}

void loop() {
  //Cada vez que se se detecta un TRUE en el pin de encendido del bombillo, se registra la hora y se cuenta el tiempo encendido en segundos
  luzConect=digitalRead(luz);
  if (luzConect)  {
    DateTime now = RTC.now(); // Obtiene la fecha y hora del RTC
    Serial.print(now.day(), DEC); //Día
    Serial.print(' ');
    Serial.print(now.hour(), DEC); // Horas
    Serial.print(':');
    Serial.print(now.minute(), DEC); // Minutos
    Serial.print(':');
    Serial.print(now.second(), DEC); // Segundos
    Serial.println();
    digitalWrite(led, HIGH);
    tiempo = tiempo + 1;
    Serial.println();
    Serial.print(tiempo);
  }
  else  {
    digitalWrite(led, LOW);
  }
  delay(1000); // La información se actualiza cada 1 seg.
}
