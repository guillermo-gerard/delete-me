#include <Arduino.h>
#include "Boton.h"

void printLongClick1();
void printSimpleClick1();
void printSimpleClick2();

Boton boton1(D1, printSimpleClick1, printLongClick1);
Boton boton2(D2, printSimpleClick2, printSimpleClick2);

void setup()
{
  Serial.begin(115200);
  Serial.println("Bienvenido");
}

void loop()
{
  boton1.Refresh();
  boton2.Refresh();
}

void printLongClick1(){
  Serial.println("hubo un click largo en el boton 1");
}

void printSimpleClick1(){
  Serial.println("hubo un click simple en el boton 1");
}

void printSimpleClick2(){
  Serial.println("se presiono el 2");
}
