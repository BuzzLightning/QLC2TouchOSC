#ifndef TOTOUCHOSC
#define TOTOUCHOSC

QDomElement toTouchOSC(QDomNode workelmt);

void loadFile (QString INfilename, QDomDocument indoc);

void writeFile (QString OUTfilename, QDomDocument outdoc);

QDomNode verifyInputDoc(QDomDocument INdoc);

QDomDocument writeDoc(QDomNode inNode, int width, int height, QString orientation);

#endif // TOTOUCHOSC

