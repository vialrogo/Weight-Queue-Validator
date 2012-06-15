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
    /// /////// Temporales ///////
    int numTruncamiento=8;
    int numRedondeo=0;
    double numEscala=1.0;
    /// //////////////////////////

    QFile* file = new QFile(nombrearchivo);
    bool abrioArchivo = file->open(QIODevice::ReadOnly);
    QString linea;
    bool ok;
    double valorTotal=0.0;
    int contadorEscala=numEscala;

    if(abrioArchivo)
    {
        vectorFiles->push_back(file);
        QVector<double>* vectorDatos = new QVector<double>();

        QTextStream textStream(file);

        while (!textStream.atEnd())
        {
            linea = textStream.readLine();
            linea = linea.right(linea.size()-numTruncamiento); //corto los 8 número de la izquierda de la marca de tiempo para que queda en un double
            linea = linea.left(linea.size()-numRedondeo);
            valorTotal+=linea.toDouble(&ok);
            contadorEscala--;

            if(contadorEscala==0) //Cuando se han sumado los datos correspondientes los agrego al vector
            {
                vectorDatos->push_back(valorTotal/numEscala);
                contadorEscala=numEscala;
                valorTotal=0.0;
            }
        }
        vectorDatosFiles->push_back(vectorDatos);
//        qDebug("%d",vectorDatos->size());
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

QVector<double>* WQ_IOFiles::obtenerDatosArchivo(int numArchivo)
{
    return vectorDatosFiles->at(numArchivo);
}
