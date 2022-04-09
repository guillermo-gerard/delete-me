#include <Arduino.h>

const uint8_t boton = D1;

void setup()
{
  Serial.begin(115200);
  Serial.println("Bienvenido");
  pinMode(boton, INPUT);
}

unsigned long inicioAntirrebote;
const int tiempoAntirrebote = 30;
int estadoActual = 0;

const int ESPERANDO_PULSACION = 0;
const int ANTIRREBOTE_PULSACION = 1;
const int ESPERANDO_SOLTACION = 2;
const int ANTIRREBOTE_SOLTACION = 3;

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
    if (digitalRead(boton) == LOW)
    {
      inicioAntirrebote = millis();
      estadoActual = ANTIRREBOTE_SOLTACION;
      Serial.println("Pulsado");
    }
    break;
  case ANTIRREBOTE_SOLTACION:
    if (millis() - inicioAntirrebote >= tiempoAntirrebote)
    {
      estadoActual = ESPERANDO_PULSACION;
    }
    break;
  }
}