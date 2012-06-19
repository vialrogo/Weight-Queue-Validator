#ifndef WQ_IOFILE_H
#define WQ_IOFILE_H

#include <QFile>
#include <QThread>
#include <QTextStream>
#include <QVector>
#include <math.h>

class WQ_IOFiles : public QThread
{
    Q_OBJECT

private:
    QVector<QFile*>* vectorFiles;
    QVector<short* >* vectorDatosFiles;

protected:
    void run();

public:
    WQ_IOFiles(QObject *parent = 0);
    ~WQ_IOFiles();
    void agregarArchivo(QString nombrearchivo);

public slots:
    void elimiarArchivo(int numArchivo);
    short* obtenerDatosArchivo(int numArchivo);

signals:
    void archivoCargado(QString nombreArchivo);
    void archivoNoCargado(QString nombreArchivo);
    void archivoEliminado(int numArchivo);
};

#endif // WQ_IOFILE_H
