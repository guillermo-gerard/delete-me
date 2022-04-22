#include <Arduino.h>
#include "Estados.h"

Estados estadoActual = ESPERANDO_PULSACION;

const uint8_t boton = D1;
const unsigned int TIEMPO_CLICK_LARGO = 1000;

void setup()
{
  Serial.begin(115200);
  Serial.println("Bienvenido");
  pinMode(boton, INPUT);
}

unsigned long inicioAntirrebote;
const int tiempoAntirrebote = 30;

void loop()
{
  switch (estadoActual)
  {
  case ESPERANDO_PULSACION:
    if (digitalRead(boton) == HIGH)
    {
      inicioAntirrebote = millis();
      estadoActual = ANTIRREBOTE_PULSACION;
    }
    break;
  case ANTIRREBOTE_PULSACION:
    if (millis() - inicioAntirrebote >= tiempoAntirrebote)
    {
      estadoActual = ESPERANDO_SOLTACION;
    }
    break;
  case ESPERANDO_SOLTACION:
    if (digitalRead(boton) != LOW){
      break;
    }
   
    estadoActual = ANTIRREBOTE_SOLTACION;
    (millis() - inicioAntirrebote >= TIEMPO_CLICK_LARGO) ? Serial.println("Click largo") : Serial.println("Click corto");
    inicioAntirrebote = millis();
    break;
  case ANTIRREBOTE_SOLTACION:
    if (millis() - inicioAntirrebote >= tiempoAntirrebote)
    {
      estadoActual = ESPERANDO_PULSACION;
    }
    break;
  }
}