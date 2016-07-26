#include <QFile>
#include <stdio.h>
#include <QtXml>
#include <iostream>
using namespace std;

QDomElement toTouchOSC(QDomNode paramelmt){

   QDomElement workelmt = paramelmt.toElement();

   QDomElement outelmt;

   cout << qPrintable(workelmt.tagName()) << endl;

   outelmt = workelmt;

   if(workelmt.tagName() == "Frame"){


   }

   return outelmt;

}
