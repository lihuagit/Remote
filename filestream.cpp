#include "filestream.h"

FileStream::FileStream()
{

}
void FileStream::OpenSendfile(){
    sfilepath=QFileDialog::getOpenFileName();
    QFile file(sfilepath);
    sfilename=file.fileName();
    sfilesize=file.size();
}


void FileStream::OpenRecFile(){
    rfilepath=QFileDialog::getSaveFileName();
}
