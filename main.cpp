#include <QFile>
#include <stdio.h>
#include <QtXml>
#include <iostream>
#include "totouchosc.h"
using namespace std;

int main(int argc, char *argv[])
{

    QDomDocument indoc("indoc");

    QDomDocument outdoc("outdoc");

    QString filenameIN ;

    QString filenameOUT;

    if (argc < 3){

        cout << "Error : you must specify the input filename (QLC) first and then the output filename (TouchOSC)" << endl;

        return 0;
    }else{

        filenameIN = argv[1];
    }

    QFile file(filenameIN);

    if (!file.open(QFile::ReadOnly | QFile::Text) && !file.exists()){
            std::cerr << "Error: Cannot read file " << qPrintable(filenameIN)
                      << ": " << qPrintable(file.errorString())
                      << std::endl;
            return 0;

            if (!indoc.setContent(&file)){

                file.close();
            }

            file.close();
    }

    QDomElement workspace = indoc.documentElement();

    QDomNode virtualConsole;

    if (workspace.tagName() != "Workspace"){

        cout << "Error : The input document is invalid" << endl;
        return 0;
    }else{

    virtualConsole = workspace.firstChildElement("VirtualConsole");

    }

    QDomNode mainFrame;

    if (virtualConsole.firstChildElement().tagName() != "Frame" && virtualConsole.firstChildElement().attribute("Caption") != ""){

        cout << "Error : The input document is invalid" << endl;
        return 0;

    }else{

        mainFrame =  virtualConsole.firstChild();

    }

    QDomNode elmt = mainFrame.firstChild();

    while (!elmt.isNull()){

        toTouchOSC(elmt.toElement());

    }

    return 0;
}
