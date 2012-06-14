#include "wq_iofiles.h"

WQ_IOFiles::WQ_IOFiles(QObject *parent) :
    QObject(parent)
{
    vectorFiles = new QVector<QFile*>();
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

    if(abrioArchivo)
    {
        vectorFiles->push_back(file);
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
}
