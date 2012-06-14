#include "wq_iofiles.h"

WQ_IOFiles::WQ_IOFiles(QObject *parent) :
    QObject(parent)
{
    vectorFiles = new QVector<QFile*>();
    vectorDatosFiles = new QVector<QVector<double>*>();
}

WQ_IOFiles::~WQ_IOFiles()
{
    while (vectorFiles->size()>0) {
        vectorFiles->at(0)->close();
        delete vectorFiles->at(0);
        vectorFiles->remove(0);
    }
    delete vectorFiles;
}

bool WQ_IOFiles::agregarArchivo(QString nombrearchivo)
{
    QFile* file = new QFile(nombrearchivo);
    bool abrioArchivo = file->open(QIODevice::ReadOnly);
    QString linea;
//    QTextStream textStream;
    bool ok;

    if(abrioArchivo)
    {
        vectorFiles->push_back(file);
        QVector<double>* vectorDatos = new QVector<double>();

        QTextStream textStream(file);

        while (!textStream.atEnd())
        {
            linea = textStream.readLine();
            linea = linea.right(linea.size()-8); //corto los 8 número de la izquierda de la marca de tiempo para que queda en un double
            vectorDatos->push_back(linea.toDouble(&ok));
        }

        vectorDatosFiles->push_back(vectorDatos);
    }
    else
    {
        delete file;
    }

    return abrioArchivo;
}

void WQ_IOFiles::elimiarArchivo(int numArchivo)
{
    vectorFiles->at(numArchivo)->close();
    delete vectorFiles->at(numArchivo);
    vectorFiles->remove(numArchivo);

    delete vectorDatosFiles->at(numArchivo);
    vectorDatosFiles->remove(numArchivo);
}
