#include <Arduino.h>
#include "Estados.h"

Estados estadoActual = ESPERANDO_PULSACION;
unsigned long inicioAntirrebote;
const int tiempoAntirrebote = 30;
const unsigned int TIEMPO_CLICK_LARGO = 1000;

void RefreshEstadoBoton(uint8_t boton)
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
        if (digitalRead(boton) != LOW)
        {
            break;
        }

        estadoActual = ANTIRREBOTE_SOLTACION;
        (millis() - inicioAntirrebote >= TIEMPO_CLICK_LARGO) ? Serial.println(F("Click largo")) : Serial.println(F("Click corto"));
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
