#ifndef TOTOUCHOSC
#define TOTOUCHOSC

QDomNode toTouchOSC(QDomNode workelmt);

void loadFile (QString INfilename, QDomDocument indoc);

void writeFile (QString OUTfilename, QDomDocument outdoc);

QDomNode verifyInputDoc(QDomDocument INdoc);

QDomDocument writeDoc(QDomNode inNode, int width, int height, QString orientation);

QDomNode TOSCFrameCreating(QDomNode nodetoconvert, int framewidth, int frameheight);

QString base64_encode(QString string);

#endif // TOTOUCHOSC

