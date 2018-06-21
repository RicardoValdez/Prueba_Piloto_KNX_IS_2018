#include <Adafruit_NeoPixel.h>
#include <math.h>

//Pines para el control del NeoPixel
#define PIN_persiana_cocina 6
#define PIN_persiana_sala_comun 12
#define N_leds 20

//Pines para la entrada de señales de persiana
#define PIN_subir_cocina 4
#define PIN_bajar_cocina 3
#define PIN_subir_sala_comun 10
#define PIN_bajar_sala_comun 9

//Variables globales
int contador_sala_comun, contador_cocina = 0;
bool bajar_sala_comun, subir_sala_comun;
bool bajar_cocina, subir_cocina;

Adafruit_NeoPixel strip_cocina = Adafruit_NeoPixel(N_leds, PIN_persiana_cocina, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_sala_comun = Adafruit_NeoPixel(N_leds, PIN_persiana_sala_comun, NEO_GRB + NEO_KHZ800);

void setup() {
  strip_cocina.begin();  //Inicializa la cinta de LEDs
  strip_cocina.show();   //Apaga los LEDs
  strip_sala_comun.begin();  //Inicializa la cinta de LEDs
  strip_sala_comun.show();   //Apaga los LEDs
  pinMode(PIN_subir_cocina, INPUT);
  pinMode(PIN_bajar_cocina, INPUT);
  pinMode(PIN_subir_sala_comun, INPUT);
  pinMode(PIN_bajar_sala_comun, INPUT);
  Serial.begin(9600);
}
  
void loop() {
  
  //Lectura de los pines de entrada
  bajar_cocina = digitalRead(PIN_bajar_cocina);
  subir_cocina = digitalRead(PIN_subir_cocina);
  bajar_sala_comun = digitalRead(PIN_bajar_sala_comun);
  subir_sala_comun = digitalRead(PIN_subir_sala_comun);

  //Lógica de control del NeoPixel
  if (bajar_cocina) {
    contador_cocina = contador_cocina - 1;
    if (contador_cocina < 0) {
      contador_cocina = 0;
    }
    strip_cocina.setPixelColor(contador_cocina, 0);
    strip_cocina.show();
  }
  
  if (subir_cocina)  {
    if (contador_cocina > 19) {
      contador_cocina = 19;
    }
    strip_cocina.setPixelColor(contador_cocina, 12, (contador_cocina+1)*12, 12);  //(red, green, blue)
    strip_cocina.show();
    contador_cocina = contador_cocina + 1;
  }

    if (bajar_sala_comun) {
      contador_sala_comun = contador_sala_comun - 1;
      if (contador_sala_comun < 0) {
        contador_sala_comun = 0;
    }
    strip_sala_comun.setPixelColor(contador_sala_comun, 0);
    strip_sala_comun.show();
  }
  
  if (subir_sala_comun)  {
    if (contador_sala_comun > 19) {
      contador_sala_comun = 19;
    }
    strip_sala_comun.setPixelColor(contador_sala_comun, 12, 12, (contador_sala_comun+1)*12);  //(red, green, blue)
    strip_sala_comun.show();
    contador_sala_comun = contador_sala_comun + 1;
  }
  delay(300);
}
