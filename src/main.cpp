#include <Arduino.h>
#include "Boton.h"
#include <Eventos.h>

Boton boton1(D1);

void setup()
{
  Serial.begin(115200);
  Serial.println("Bienvenido");
}

void loop()
{
  Eventos resultado_boton1 = boton1.Refresh();
  if(resultado_boton1 == Eventos::CLICK)

}