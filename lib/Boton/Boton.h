#include "Estados.h"

#ifndef Pepito
#define Pepito

class Boton
{
public:
    Boton(int pin);
    Boton(int pin, void (*fs)(), void (*fl)());
    void Refresh();
    void SetSimpleClickFunction(void (*f)());
    void SetLongClickFunction(void (*f1)());
private:
    int _pin;
    void Configure(int);
    void (*_simpleClickFunction)(); 
    void (*_longClickFunction)(); 
    Estados _estadoActual;
    unsigned long _inicioAntirrebote;
    const unsigned int _tiempoAntirrebote = 30;
    const unsigned int _TIEMPO_CLICK_LARGO = 1000;
};

#endif