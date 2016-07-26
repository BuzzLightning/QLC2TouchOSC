#include <QFile>
#include <stdio.h>
#include <QtXml>
#include <iostream>
using namespace std;

void toTouchOSC(QDomElement workelmt){

   cout << qPrintable(workelmt.tagName()) << endl;

}
