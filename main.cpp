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

    QDomProcessingInstruction instr = outdoc.createProcessingInstruction("xml", "version='1.0' encoding='UTF-8'");
    outdoc.appendChild(instr);

    outdoc.removeChild(outdoc.doctype());

    QString filenameIN ;

    QString filenameOUT;

    if (argc < 3){

        cout << "Error : you must specify the input filename (QLC) first and then the output filename (TouchOSC)" << endl;

        return 0;
    }else{

        filenameIN = argv[1];
        filenameOUT = argv[2];
    }

    QFile INfile(filenameIN);

    if (!INfile.open(QFile::ReadOnly | QFile::Text) && !INfile.exists()){
            std::cerr << "Error: Cannot read file " << qPrintable(filenameIN)
                      << ": " << qPrintable(INfile.errorString())
                      << std::endl;
            return 0;
    }else if (!indoc.setContent(&INfile)){

        cout << "Error : The input document was not loaded correctly" << endl;
        return 0;
    }

    INfile.close();

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

        QDomElement outelmt = toTouchOSC(elmt);

        outdoc.appendChild(outdoc.createElement(outelmt.tagName()));

        elmt = elmt.nextSibling();

    }

    QFile OUTfile(filenameOUT);

    if(!OUTfile.open(QFile::WriteOnly | QFile::Text)  && !OUTfile.exists()){
        std::cerr << "Error: Cannot write file " << qPrintable(filenameOUT)
                  << ": " << qPrintable(OUTfile.errorString())
                  << std::endl;
        return 0;
    }else{

      QTextStream ts(&OUTfile);

      ts << outdoc.toString();

      OUTfile.close();
    }
    return 0;
}
