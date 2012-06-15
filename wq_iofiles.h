#ifndef WQ_IOFILE_H
#define WQ_IOFILE_H

#include <QFile>
#include <QTextStream>
#include <QVector>

class WQ_IOFiles : public QObject
{
    Q_OBJECT

private:
    QVector<QFile*>* vectorFiles;
    QVector<double* >* vectorDatosFiles;
    QVector<int> vectorNumeroDatosFiles;

public:
    WQ_IOFiles(QObject *parent = 0);
    ~WQ_IOFiles();
    bool agregarArchivo(QString nombrearchivo, int numTruncamiento, int numRedondeo, double numEscala);

public slots:
    void elimiarArchivo(int numArchivo);
    QVector<double>* obtenerDatosArchivo(int numArchivo);
};

#endif // WQ_IOFILE_H
