#include "Boton.h"
#include <Arduino.h>
#include "Estados.h"
//#include "Eventos.h"


Boton::Boton(int pin)
{
    pinMode(pin, INPUT);
    _pin = pin;
    _estadoActual = Estados::ESPERANDO_PULSACION;
}

Eventos Boton::Refresh()
{
    Eventos resultado = Eventos::NADA;
    switch (_estadoActual)
    {
    case ESPERANDO_PULSACION:
        if (digitalRead(_pin) == HIGH)
        {
            _inicioAntirrebote = millis();
            _estadoActual = Estados::ANTIRREBOTE_PULSACION;
        }
        break;
    case ANTIRREBOTE_PULSACION:
        if (millis() - _inicioAntirrebote >= _tiempoAntirrebote)
        {
            _estadoActual = Estados::ESPERANDO_SOLTACION;
        }
        break;
    case ESPERANDO_SOLTACION:
        if (digitalRead(_pin) != LOW)
        {
            break;
        }

        _estadoActual = Estados::ANTIRREBOTE_SOLTACION;
        resultado = (millis() - _inicioAntirrebote >= _TIEMPO_CLICK_LARGO) ? Eventos::CLICK : Eventos::CLICK_LARGO;
        _inicioAntirrebote = millis();
        break;
    case ANTIRREBOTE_SOLTACION:
        if (millis() - _inicioAntirrebote >= _tiempoAntirrebote)
        {
            _estadoActual = Estados::ESPERANDO_PULSACION;
        }
        break;
    }
    return resultado;
}
