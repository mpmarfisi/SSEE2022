#ifndef AUTO_H
#define AUTO_H

class Auto
{
    public:
        Auto();
        Auto(float kilometraje_inicial);
        Auto(bool luces_inicial, bool estado_inicial);
        ~Auto();

        void  Prender(void);
        void  Acelerar(float aceleracion_);
        void  AccionarLuces(bool estado);

        float ObtenerKilometraje(void);
        int   ObtenerTemperatura(void);

    private:
        float kilometraje;
        int   temperatura;
        bool  estado;
        bool  luces;
        float aceleracion;
};

#endif // AUTO_H
