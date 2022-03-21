#include "auto.h"

Auto::Auto()
{
    kilometraje = 0;
    luces = 0;
    estado = 0;
    temperatura = 50;
    aceleracion = 0;
}

Auto::Auto(float kilometraje_inicial)
{
    kilometraje = kilometraje_inicial;
    luces = 0;
    estado = 0;
    temperatura = 50;
    aceleracion = 0;
}

Auto::Auto(bool luces_inicial, bool estado_inicial)
{
    kilometraje = 0;
    luces = luces_inicial;
    estado = estado_inicial;
    temperatura = 50;
    aceleracion = 0;
}

Auto::~Auto()
{

}

void  Auto::Prender(void)
{
    estado = 1;
}
void  Auto::Acelerar(float aceleracion_)
{
    aceleracion = aceleracion_;
}
void  Auto::AccionarLuces(bool estado)
{
    luces = estado;
}

float Auto::ObtenerKilometraje(void)
{
    return kilometraje;
}

int   Auto::ObtenerTemperatura(void)
{
    return temperatura;
}
