#include <Arduino.h>
#include "boton.h"


const uint8_t boton = D1;

void setup()
{
  Serial.begin(115200);
  Serial.println("Bienvenido");
  pinMode(boton, INPUT);
}

void loop()
{
  RefreshEstadoBoton(boton);
}