#include <Arduino.h>

const uint8_t boton = D1;

void setup()
{
  Serial.begin(115200);
  pinMode(boton, INPUT);
}

unsigned long inicioAntirrebote;
const int tiempoAntirrebote = 20;
bool botonEnAntirrebote = false;
bool estadoBoton = false;

void loop()
{
  int botonPresionado = digitalRead(boton);

  if (botonPresionado && !botonEnAntirrebote && !estadoBoton)
  {
    inicioAntirrebote = millis();
    botonEnAntirrebote = true;
    Serial.println("boton presionado");
    estadoBoton = true;
  }
  if (millis() - tiempoAntirrebote >= inicioAntirrebote + tiempoAntirrebote)
  {
    botonEnAntirrebote = false;
  }
  if (!botonPresionado && !botonEnAntirrebote && estadoBoton)
  {
    estadoBoton = false;
  }
}
