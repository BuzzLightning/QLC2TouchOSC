#include <QFile>
#include <stdio.h>
#include <QtXml>
#include <iostream>
#include "totouchosc.h"
using namespace std;

int main(int argc, char *argv[])
{

    QDomDocument docin("");

    QDomDocument docout("");

    QString filenameIN ;

    QString filenameOUT;

    if (argc < 3){

        cout << "Error : you must specify the input filename (QLC) first and then the output filename (TouchOSC)" << endl;

        return 1;
    }else{

        filenameIN = argv[1];
        filenameOUT = argv[2];
    }

    bool condW;
    bool condH;

    int userwidth;
    int userheight;

    QString orientationString;

    do
    {
       cout << "Enter the width you want the layout to have (maximum 1920) :";
       cin >> userwidth;

       condW = cin.fail();

       cin.clear();
       cin.ignore(1920, '\n');

    }while(condW || userwidth > 1920);

    do
    {
       cout << "Enter the height you want the layout to have (maximum 1920) :";
       cin >> userheight;

       condH = cin.fail();

       cin.clear();
       cin.ignore(1920, '\n');

    }while(condH || userheight > 1920);

    if(userheight<= userwidth){
        orientationString = "horizontal";
    }else{
        orientationString = "vertical";
    }

    loadFile(filenameIN, docin);

    QDomNode startNode = verifyInputDoc(docin);

    docout = writeDoc(startNode, userwidth, userheight, orientationString);

    writeFile(filenameOUT, docout);

    return 0;
}
