#include <QCoreApplication>
#include <QFile>
#include <QXmlStreamWriter>
//#include <stdio.h>
#include <QtXml/qdom.h>
#include <QtXml/QDomDocument>
#include <iostream>
using namespace std;



int main(int argc, char *argv[])
{

    QDomDocument doc("mydocument");
    QFile file("index.xml");
    if (!file.open(QIODevice::ReadOnly))
        cout << "Error opening \n";
    if (!doc.setContent(&file)) {
        file.close();
    }
    file.close();

    // print out the element names of all elements that are direct children
    // of the outermost element.
    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();
    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
            cout << qPrintable(e.tagName()) << endl; // the node really is an element.
        }
        n = n.nextSibling();
    }

//    // Here we append a new element to the end of the document
//    QDomElement elem = doc.createElement("img");
//    elem.setAttribute("src", "myimage.png");
//    docElem.appendChild(elem);

    return 0;
}

