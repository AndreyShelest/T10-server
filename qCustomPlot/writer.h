#ifndef WRITER_H
#define WRITER_H

#include <QWidget>
#include <QVector>
#include <QMessageBox>
#include <QFileDialog>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cassert>
#include <string.h>
#include <vector>
#include <list>
#include <QDebug>

class Writer
{
public:
    static bool Save2MAT(QString fileName, QVector<QVector<double> > *dataVector, QList<QString> *varNames);
    static bool Save2TXT(QString fileName, QVector<QVector<double> > *dataVector, QList<QString> *varNames);
    static bool Save2CSV(QString fileName, QVector<QVector<double> > *dataVector, QList<QString> *varNames);
    static FILE* OpenMAT(const char *name);
    static void writeTag(FILE *fp, int t, int n) ;
    static int getMatrixClass(int t);
    template<typename Tn > static void writeVector(int t, const QVector <double> &a, const char *name,FILE *fp);
    template< typename Tn > static int Ayuda(int t, unsigned m, unsigned n, const char *name,FILE *fp);
};

#endif // WRITER_H
