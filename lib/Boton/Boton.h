#include <Eventos.h>
#include "Estados.h"

#ifndef Pepito
#define Pepito

class Boton
{
public:
    Boton(int pin);
    Eventos Refresh();
private:
    int _pin;
    Estados _estadoActual;
    unsigned long _inicioAntirrebote;
    const int _tiempoAntirrebote = 30;
    const unsigned int _TIEMPO_CLICK_LARGO = 1000;
};

#endif