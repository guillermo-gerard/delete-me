#include "Boton.h"
#include <Arduino.h>
#include "Estados.h"

void Boton::Configure(int pin){
   pinMode(pin, INPUT);
   _pin = pin;
   _estadoActual = Estados::ESPERANDO_PULSACION;
}

Boton::Boton(int pin)
{
    Configure(pin);
}

Boton::Boton(int pin, void (*fs)(), void (*fl)()){
    Configure(pin);
    SetSimpleClickFunction(fs);
    SetLongClickFunction(fl);
}

void Boton::SetSimpleClickFunction(void (*f)())
{
    _simpleClickFunction = f;
}

void Boton::SetLongClickFunction(void (*f)())
{
    _longClickFunction = f;
}

void Boton::Refresh()
{
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
        (millis() - _inicioAntirrebote >= _TIEMPO_CLICK_LARGO) ? _simpleClickFunction(): _longClickFunction();
        _inicioAntirrebote = millis();
        break;
    case ANTIRREBOTE_SOLTACION:
        if (millis() - _inicioAntirrebote >= _tiempoAntirrebote)
        {
            _estadoActual = Estados::ESPERANDO_PULSACION;
        }
        break;
    }
}
