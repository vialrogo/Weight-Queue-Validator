#include "wq_iofiles.h"

WQ_IOFiles::WQ_IOFiles(QObject *parent) :
    QThread(parent)
{
    vectorFiles = new QVector<QFile*>();
    vectorDatosFiles = new QVector<short*>();
}

WQ_IOFiles::~WQ_IOFiles()
{
    while (vectorFiles->size()>0) {
        vectorFiles->at(0)->close();
        delete vectorFiles->at(0);
        vectorFiles->remove(0);

        delete vectorDatosFiles->at(0);
        vectorDatosFiles->remove(0);
    }
    delete vectorFiles;
    delete vectorDatosFiles;
}

void WQ_IOFiles::run() //Tiene constantes quemadas en el código!
{
    //Esta función lee los archivos de una manera muy, muy específica, si se quere que ea mas archivos
    // habría que especificarlos y mirar como se hace para que no se trague toda la ram cargandolos

    QFile* file = vectorFiles->at(vectorFiles->size()-1);
    short* arreglo = new short[60000000]; //microsegundos!
    QTextStream textStream(file);
    QString linea;

    while (!textStream.atEnd())
    {
        linea = textStream.readLine();
        linea = linea.right(linea.size()-8); //corto los 8 número de la izquierda de la marca de tiempo para que queda en un double
        linea = linea.left(linea.size()-3); //redondeo a microsegundos
        linea = linea.remove(2,1); //quito el punto
        arreglo[linea.toInt()]++;
    }
    vectorDatosFiles->push_back(arreglo);

    emit archivoCargado(file->fileName());
}

void WQ_IOFiles::agregarArchivo(QString nombrearchivo)
{
    QFile* file = new QFile(nombrearchivo);

    if(file->open(QIODevice::ReadOnly))
    {
        vectorFiles->push_back(file);
        start();
    }
    else
    {
        delete file;
        emit archivoNoCargado(nombrearchivo);
    }
}

void WQ_IOFiles::elimiarArchivo(int numArchivo)
{
    vectorFiles->at(numArchivo)->close();
    delete vectorFiles->at(numArchivo);
    vectorFiles->remove(numArchivo);

    delete vectorDatosFiles->at(numArchivo);
    vectorDatosFiles->remove(numArchivo);
}

short* WQ_IOFiles::obtenerDatosArchivo(int numArchivo)
{
    return vectorDatosFiles->at(numArchivo);
}
