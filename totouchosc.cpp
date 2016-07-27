#include <QFile>
#include <stdio.h>
#include <QtXml>
#include <iostream>
using namespace std;

// Transform each subframe from QLC virtual console in a frame in a TouchOSC layout. The following elements are transformed : XYPad, Slider, SpeedDial (not the typing area), Buttons (Flash or Toggle), Multi-Buttons/Slider, Clock

QDomElement toTouchOSC(QDomNode paramelmt){

   QDomElement workelmt = paramelmt.toElement(); //changing the node into a element to work with it

   QDomElement outelmt;

   cout << qPrintable(workelmt.tagName()) << endl;

   outelmt = workelmt;

   if(workelmt.tagName() == "Frame"){



   }

   return outelmt;

}

// Function that import the XML file into a QDomDoc

void loadFile (const QString INfilename, QDomDocument indoc){

    QFile INfile(INfilename);

    if (!INfile.open(QFile::ReadOnly | QFile::Text) && !INfile.exists()){ // In case of opening error, it prints a message and exit
            std::cerr << "Error: Cannot read file " << qPrintable(INfilename)
                      << ": " << qPrintable(INfile.errorString())
                      << std::endl;
            exit(1);
    }else if (!indoc.setContent(&INfile)){ // In case of importing error, it prints a message and exit

        cout << "Error : The input document was not loaded correctly" << endl;
        exit(1);
    }

    INfile.close();

}

// Function that writes the QDomDoc into an XML file

void writeFile (const QString OUTfilename, QDomDocument outdoc){

    QFile OUTfile(OUTfilename);

    if(!OUTfile.open(QFile::WriteOnly | QFile::Text)  && !OUTfile.exists()){
        std::cerr << "Error: Cannot write file " << qPrintable(OUTfilename)
                  << ": " << qPrintable(OUTfile.errorString())
                  << std::endl;
       exit(1);
    }else{

      QTextStream ts(&OUTfile);

      ts << outdoc.toString();

      OUTfile.close();
    }

}

QDomNode verifyInputDoc(QDomDocument INdoc){

    QDomElement workspace = INdoc.documentElement();

    QDomNode virtualConsole;

    if (workspace.tagName() != "Workspace"){

        cout << "Error : The input document is invalid" << endl;
        exit(1);
    }else{

    virtualConsole = workspace.firstChildElement("VirtualConsole");

    }

    QDomNode mainFrame;

    if (virtualConsole.firstChildElement().tagName() != "Frame" && virtualConsole.firstChildElement().attribute("Caption") != ""){

        cout << "Error : The input document is invalid" << endl;
        exit(1);

    }else{

        mainFrame =  virtualConsole.firstChild();
    }

        return mainFrame.firstChild();
}

QDomDocument writeDoc(QDomNode inNode, int width, int height, QString orientation){

    QDomDocument outdoc;

    QDomProcessingInstruction instr = outdoc.createProcessingInstruction("xml", "version='1.0' encoding='UTF-8'");
    outdoc.appendChild(instr);

    QDomNode layout = outdoc.appendChild(outdoc.createElement("layout"));

    layout.toElement().setAttribute("version", "15");
    layout.toElement().setAttribute("mode", "3");
    layout.toElement().setAttribute("w", width);
    layout.toElement().setAttribute("h", height);
    layout.toElement().setAttribute("orientation", orientation);

    while (!inNode.isNull()){

        QDomElement outelmt = toTouchOSC(inNode);

        layout.appendChild(outdoc.createElement(outelmt.tagName()));

        inNode = inNode.nextSibling();

    }

    return outdoc;
}

