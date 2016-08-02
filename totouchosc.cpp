#include <QCoreApplication>
#include <QFile>
#include <stdio.h>
#include <QtXml>
#include <iostream>
#include <QString>
#include <math.h>
using namespace std;

QString base64_encode(QString string);

QDomNode TOSCFrameCreating(QDomNode nodetoconvert, int framewidth, int frameheight,  int outwidth, int outheight);

int *elmtparams(QDomNode nodeparams, int inwidth, int inheight, int outwidth, int outheight, int arr[4]);

// Transform each subframe from QLC virtual console in a frame in a TouchOSC layout. The following elements are transformed : XYPad, Slider, SpeedDial (not the typing area), Buttons (Flash or Toggle), Multi-Buttons/Slider, Clock

QDomNode toTouchOSC(QDomNode paramelmt, int widthout, int heightout){

    QDomElement workelmt = paramelmt.toElement(); //changing the node into a element to work with it

    QDomNode nodeout;


    if(workelmt.tagName() == "Frame"){

        std::cout << "This frame : " << qPrintable(workelmt.attribute("Caption")) << " is taken into account" << endl;

        int framewidth;

        framewidth = paramelmt.firstChildElement("WindowState").attribute("Width").toInt();

        int frameheight;

        frameheight = paramelmt.firstChildElement("WindowState").attribute("Height").toInt();

        std::cout << "The width of this frame is : " << framewidth << endl;

        nodeout = TOSCFrameCreating(paramelmt, framewidth, frameheight, widthout, heightout);

    }else{

        std::cout << "This element : " << qPrintable(workelmt.attribute("Caption")) << " is not taken into account" << endl;
        nodeout.clear();
    }


    return nodeout;

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

        std::cout << "Error : The input document was not loaded correctly" << endl;
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

// Function that validate the format of the input XML document

QDomNode verifyInputDoc(QDomDocument INdoc){

    QDomElement workspace = INdoc.documentElement();

    QDomNode virtualConsole;

    if (workspace.tagName() != "Workspace"){

        std::cout << "Error : The input document is invalid" << endl;
        exit(1);
    }else{

    virtualConsole = workspace.firstChildElement("VirtualConsole");

    }

    QDomNode mainFrame;

    if (virtualConsole.firstChildElement().tagName() != "Frame" && virtualConsole.firstChildElement().attribute("Caption") != ""){

        std::cout << "Error : The input document is invalid" << endl;
        exit(1);

    }else{

        mainFrame =  virtualConsole.firstChild();
    }

        return mainFrame.firstChild();
}

// Function that writes the doc in the right XML format

QDomDocument writeDoc(QDomNode inNode, int width, int height, QString orientation){

    QDomDocument outdoc;

    QDomProcessingInstruction instr = outdoc.createProcessingInstruction("xml", "version='1.0' encoding='UTF-8'");
    outdoc.appendChild(instr); // Version node

    QDomNode layout = outdoc.appendChild(outdoc.createElement("layout")); // Specs node creation

    layout.toElement().setAttribute("version", "15");
    layout.toElement().setAttribute("mode", "3");
    layout.toElement().setAttribute("w", width);
    layout.toElement().setAttribute("h", height);
    layout.toElement().setAttribute("orientation", orientation);



    while (!inNode.isNull()){

        QDomNode outnode = toTouchOSC(inNode, width, height);

        if(!outnode.isNull()){

            layout.appendChild(outnode);
        }
        inNode = inNode.nextSibling();

    }

    return outdoc;
}

QDomNode TOSCFrameCreating(QDomNode nodetoconvert, int framewidth, int frameheight, int outwidth, int outheight){

    QString toencodename = nodetoconvert.toElement().attribute("Caption");

    QString encodedString = base64_encode(toencodename); // Converts the name of the QLC frame into base_64

    cout << "Encoded string : " << qPrintable(encodedString) << endl;

    QDomNode nodeconverted;

    QDomNode nodetmp;

    QDomDocument doctmp;

    nodeconverted = doctmp.appendChild(doctmp.createElement("tabpage"));

    nodeconverted.toElement().setAttribute("name", encodedString);

    cout << "Tag name : " << qPrintable(nodeconverted.toElement().tagName()) << endl;

    cout << "Name : " << qPrintable(nodeconverted.toElement().attribute("name")) << endl;

    nodetmp = nodetoconvert.firstChild();

    while (!nodetmp.isNull()){

        QString debugstring1 = nodetmp.toElement().tagName();

        QString debugstring2 = nodetmp.toElement().attribute("WidgetStyle");

        if(nodetmp.toElement().tagName() == "Slider" && nodetmp.toElement().attribute("WidgetStyle") == "Slider"){

            QString nameslider = nodetmp.toElement().attribute("Caption");

            QString namesliderencoded = base64_encode(nameslider);

            QString invertslider = nodetmp.toElement().attribute("InvertedAppearance");

            int sliderposX = ((nodetmp.firstChildElement("WindowState").attribute("X").toInt())*outwidth)/framewidth;

            int sliderposY = ((nodetmp.firstChildElement("WindowState").attribute("Y").toInt())*outheight)/frameheight;

            int sliderwidth = ((nodetmp.firstChildElement("WindowState").attribute("Width").toInt())*outwidth)/framewidth;

            int sliderheight = ((nodetmp.firstChildElement("WindowState").attribute("Width").toInt())*outheight)/frameheight;

            nodeconverted.appendChild(nodeconverted.toDocument().createElement("control"));

            nodeconverted.firstChildElement("control").setAttribute("x", sliderposX);

        }

        nodetmp = nodetmp.nextSibling();

    }

    return nodeconverted;

}

QString base64_encode(QString string){
    QByteArray ba;
    ba.append(string);
    return ba.toBase64();
}
