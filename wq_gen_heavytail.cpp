#include "wq_gen_heavytail.h"

WQ_Gen_HeavyTail::WQ_Gen_HeavyTail(QObject *parent) :
    WQ_Generator(parent)
{
}

WQ_Gen_HeavyTail::~WQ_Gen_HeavyTail()
{
}

void WQ_Gen_HeavyTail::generarDatosSinteticos(double parametro_in)
{
    //En esta clase, parametro corresponde a beta
    parametro=parametro_in;
    start();
}

void WQ_Gen_HeavyTail::run()
{
    double alfa = 100.0; /// Arbitrario!!!

    short* datosGenerados = new short[60000000];
    for (int i = 0; i < 60000000; i++) datosGenerados[i] = 0;

    /// ***************************
//    double a=0.0;
//    double b=0.0;
//    double real=0.0;
//    double numero=0.0;

//    while (numero<60000000)
//    {
//        a=generarNumeroAleatorio()*alfa;
//        b=generarNumeroAleatorio()*500; //Arbitrario

//        real = alfa/(pow(b,parametro));

//        if(a< real){
//            datosGenerados[(int)numero]++;
//            numero+=b;
//        }
//    }
    /// ***************************

    QVector<int>* vector = new QVector<int>();
    double probabilidad=0.0;
    double time=0.0;
    double* probabilidades = new double[1000];
    for (int i = 0; i < 1000; ++i) probabilidades[i]=0.0;

    for (int i = 1; i < 1000000; ++i)
    {
        time = ((double)i)/1000.0;
        probabilidad= alfa/(pow(time, parametro));

        probabilidades[(int)time]+=probabilidad;

        for (int j = 0; j < probabilidad; ++j)
        {
            vector->append( (int)time);
        }
    }

    for (int i = 0; i < 1000; ++i) qDebug("probabilidad de %d: %f",i, probabilidades[i]);

    double tamano = (double)vector->size();

//    for (int var = 0; var < tamano; ++var) {
//        cout<<" "<<vector->at(var);
//    }

    cout<<endl<<endl<<"tamaño: "<<tamano<<endl;

    int numero = 0.0;
    numero += vector->at((int)(generarNumeroAleatorio()*tamano));

    while(numero<60000000)
    {
        datosGenerados[numero]++;
        numero += vector->at((int)(generarNumeroAleatorio()*tamano));
//        qDebug("numero: %d",numero);
    }

    emit datosGeneradosExitosamente("Heavy-Tail with β="+QString::number(parametro),datosGenerados);
}
