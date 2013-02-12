#include "qCustomPlot/writer.h"

// Constants for most important, basic MAT types
#define miINT8 1
#define miUINT8 2
#define miINT16 3
#define miUINT16 4
#define miINT32 5
#define miUINT32 6
#define miSINGLE 7
#define miDOUBLE 9
#define miMATRIX 14

// Matlab array types (classes)
#define mwCHAR_CLASS 4
#define mwDOUBLE_CLASS 6
#define mwSINGLE_CLASS 7
#define mwINT8_CLASS 8
#define mwUINT8_CLASS 9
#define mwINT16_CLASS 10
#define mwUINT16_CLASS 11
#define mwINT32_CLASS 12
#define mwUINT32_CLASS 13
#define mwCELL_CLASS 1

/*! \class Writer
  \brief \a Abstract class used to save the data form the robot simulation with a specific format

  The objetive of the Writer Class has is to save the data given for the system in files with a specific format.
  Both name and root of the file can be modified.
  */

/**
 * Function designed to create a MAT-File
 *@param fileName string with the full file path
 *@param dataVector Pointer to the data vectors
 *@param varNames Pointer to the list of names
 *
 */
bool Writer::Save2MAT(QString fileName, QVector<QVector <double> > *dataVector,QList  <QString> *varNames)
{
    char buff[300];
    strcpy( buff, "" );

    QByteArray byteArray = fileName.toLatin1();
    const char* cString = byteArray.constData();

    sprintf(buff,"%s",cString);

    FILE *file;
    file= OpenMAT(buff);

    for (int i=0;i<dataVector->size();i++) {
        QVector <double>  W;
        W=dataVector->value(i);
        QByteArray byteArray = varNames->value(i).toLatin1();
        const char* cString = byteArray.constData();
        writeVector <double>(miDOUBLE,W,cString,file);
    }
    fclose(file);
    return true;
}

/**
 *  Function which creates a text-File
 *@param fileName string with the full file path
 *@param dataVector Pointer to the data vectors
 *@param varNames Pointer to the list of names
 */
bool Writer::Save2TXT(QString fileName, QVector<QVector <double> > *dataVector,QList  <QString> *varNames)
{
    char buff[300];
    strcpy( buff, "" );

    QByteArray byteArray = fileName.toLatin1();
    const char* cString = byteArray.constData();

    sprintf(buff,"%s",cString);

//qDebug()<<dataVector->value(0);
    FILE *file=fopen(buff,"w");
    if (file==NULL){
       QMessageBox (QMessageBox::Critical, "Save2TXT", "Name not found");
        return false;
    }
    if (dataVector->isEmpty()){
       QMessageBox (QMessageBox::Critical, "Save2TXT", "Empty Vectors");
        return false;
    }

    for (int i=0;i<dataVector->size();i++){

        QByteArray byteArray = varNames->value(i).toLatin1();
        const char* cString = byteArray.constData();

        fprintf(file,cString);

        if ((dataVector)->value(i).isEmpty()){
            fprintf(file," \n");
            continue;
        }

        for(int j=0;j<(dataVector)->value(i).size();j++){
            fprintf(file," %g",dataVector->value(i).value(j));
        }
        fprintf(file,"\n");

    }
    fclose(file);
    return true;
}

/**
 *Function created to generate a file which has to be read by EXCEL.
 *@param fileName string with the full file path
 *@param dataVector Pointer to the data vectors
 *@param varNames Pointer to the list of names
 */
bool Writer::Save2CSV (QString fileName, QVector<QVector <double> > *dataVector,QList  <QString> *varNames)
{
    char buff[300];
    strcpy( buff, "" );

    QByteArray byteArray = fileName.toLatin1();
    const char* cString = byteArray.constData();

    sprintf(buff,"%s",cString);

    FILE *file=fopen(buff,"w");
    if (file==NULL){
        QMessageBox (QMessageBox::Critical, "Save2CSV", "Name not found");
        return false;
    }

    if (dataVector->isEmpty()){
        QMessageBox (QMessageBox::Critical, "Save2CSV", "Empty Vectors");
        return false;
    }

    for (int i=0;i<dataVector->size();i++){

        QByteArray byteArray = varNames->value(i).toLatin1();
        const char* cString = byteArray.constData();

        fprintf(file,cString);


        if ((dataVector)->value(i).isEmpty()){
            fprintf(file," \n");
            continue;
        }
        for(int j=0;j<(dataVector)->value(i).size();j++){
            sprintf(buff," %g",dataVector->value(i).value(j));
            fprintf(file,buff);
        }
        fprintf(file,"\n");
    }
    fclose(file);
    return true;
}

/**
 * Funcion which has to create a MAT-File with a given name, besides it writes the header file.
 * @param name The name that the user wants for the file.
 */
FILE* Writer::OpenMAT(const char *name)
{
    FILE *fp;
    char buf[128];
    memset(buf, ' ', 124);
    sprintf(buf, "MATLAB 5.0 MAT-file,");
    buf[124] = 0x00;
    buf[125] = 0x01;

    // Endian indicator
    buf[126] = 'I';
    buf[127] = 'M';

    fp = fopen(name, "w");
    assert(fp);
    fwrite(buf, 1, 128, fp);

    return fp;
}

/**
 * Function that has to write vectors in a Mat-File
 * @param t Kind of data
 * @param a Vector that the user wants to write
 * @param name Name of the vector in the MAT-file
 * @param fp Pointer to the MAT-file
 */
template<typename Tn >
void Writer::writeVector(int t, const QVector<double> &a, const char *name,FILE *fp)
{
    unsigned long numOfRows = 1;
    unsigned long numOfCols = a.size();
    int szb = Ayuda< Tn >(t, numOfRows, numOfCols, name,fp);

    // write vector...
    for (unsigned j = 0; j < numOfCols; j++) {
        Tn v = a.value(j);
        fwrite(&v, sizeof(Tn), 1, fp);
    }

    // Padding bytes
    int pad = (8 - (szb % 8)) % 8;
    while (pad--)
        fputc(0, fp);
}

/**
 *  This function has to adapt the data to the format that is used by MAT-files.
 * @param t Kind of data
 * @param m Number of rows
 * @param n Number of columns
 * @param name Name of the vector in the MAT-file
 * @param fp Pointer to the MAT-file
 */
template< typename Tn >
int Writer::Ayuda(int t, unsigned m, unsigned n, const char *name,FILE *fp)
{
    int nlen = strlen(name);
    int szb = n * m * sizeof(Tn);

    // Size in bytes---includes padding to 64bit boundary
    int sz = 16 + 16 + 8 + nlen + (8 - nlen % 8)%8 + 8 + szb + (8 - szb % 8)%8;
    writeTag(fp, miMATRIX, sz);

    // Write array flags
    writeTag(fp, miUINT32, 8);
    char buf[8];
    memset(buf, 0, 8);
    buf[0] = getMatrixClass(t);
    fwrite(buf, 8, 1, fp);

    // Dimensions array (2 dimensions only)
    writeTag(fp, miINT32, 8);
    fwrite(&m, 1, 4, fp);
    fwrite(&n, 1, 4, fp);

    // Name of matrix
    writeTag(fp, miINT8, nlen);
    while (*name != 0)
        fputc(*name++, fp);
    // (Padding)
    nlen = (8 - nlen % 8) % 8;
    while (nlen--)
        fputc(0, fp);

    // Actual array
    writeTag(fp, t, szb);

    return szb;
}

/**
 * Function that puts the header of each element of the vector in MAT-Files.
 * @param fp Pointer to the MAT-file.
 * @param t Kind of data
 * @param n Size of this data
 *
 */
void Writer::writeTag(FILE *fp, int t, int n) {
    fwrite(&t, 4, 1, fp);
    fwrite(&n, 4, 1, fp);
}

/**
  * Function that returns the kind of array or vector that we have to create in the MAT-File
  * @param t Kind of data that we want to write
 */
int Writer::getMatrixClass(int t) {
    switch (t) {
        case miSINGLE : return mwSINGLE_CLASS;
        case miDOUBLE : return mwDOUBLE_CLASS;
        case miINT8 : return mwINT8_CLASS;
        case miUINT8 : return mwUINT8_CLASS;
        case miINT16 : return mwINT16_CLASS;
        case miUINT16 : return mwUINT16_CLASS;
        case miINT32 : return mwINT32_CLASS;
        case miUINT32 : return mwUINT32_CLASS;
    }
    std::cerr << "Matrix type not supported in this implementation!" << std::endl;

    return mwDOUBLE_CLASS;
}
