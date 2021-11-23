#ifndef FILESTREAM_H
#define FILESTREAM_H
#include <QString>
#include <QFile>
#include <QIODevice>
#include <QFileDialog>
#include <string>
using namespace std;

class FileStream
{
public:
    FileStream();

    string Getsfilepath() { return sfilepath.toStdString(); }
    string Getsfilename() { return sfilename.toStdString(); }
    unsigned long long Getsfilesize() { return sfilesize; }

private:
    QString sfilepath;
    QString rfilepath;
    QString sfilename;
    qint64 sfilesize;
    QString rfilename;
    qint64 rfilesize;

    void OpenSendfile();
    void OpenRecFile();

};

#endif // FILESTREAM_H
