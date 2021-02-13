#include "Warehouse.h"
#include <time.h>

using namespace std;

int Warehouse::numofPackages = 0;

Warehouse::Warehouse(int maxPackages)
{
    Warehouse::maxPackages = maxPackages;
    start = new Package[maxPackages];
}

void Warehouse::print()
{
    if(numofPackages > 0){
        cout << endl << "Anzahl der Waren: " << numofPackages << endl;
        cout << "Maximale Kapazitaet: " << maxPackages << endl << endl;
        sorting();
        string stringSize[] = {"Klein", "Medium", "Gross"};
        cout << "** Liste der Waren **" << endl;
        for(int i = 0; i < numofPackages; i++){
            cout << "Ware-ID: " << start[i].getID() << endl;
            cout << "Groesse: " << stringSize[start[i].getSize()] << endl;
            cout << "Beschreibung: " << start[i].getDescription() << endl;
            cout << endl;
        }
    }
    else {
        cout << "Lagerhaus ist leer." << endl;
    }

}

void Warehouse::packageIn(Package* const p)
{
    srand(time(NULL));

    if(numofPackages == maxPackages) expand();

    bool found = 0;
    int i = 0;
    while (i < numofPackages) {
        if(numofPackages > 0 && p->getDescription() == start[i].getDescription()
           && p->getSize() == start[i].getSize())
        {
            found = true;
            break;
        }
        i++;
    }
    if(found){
        p->setID(start[i].getID());
    }
    else {
        int newID = rand()%99+1;
        //Ueberprufung, ob die generierte ID mit unterschiedlichen Ware bereits zugewiesen ist
        int i = 0;
        while (i < numofPackages) {
            if(newID == start[i].getID()){
                newID = rand()%99+1;
                i = -1; //Damit wir die Schleife wieder von Anfang durchinterieren
            }
            i++;
        }
        p->setID(rand()%99+1);
    }

    //Ware ins Lagerhaus einlagern
    start[numofPackages] = *p;

    numofPackages++;
}

void Warehouse::packageOut(int ID)
{
    if(numofPackages > 0){
        bool found = false;
        Package* temp = new Package[numofPackages];
        int i = 0;
        while (i < numofPackages) {
            if(ID == start[i].getID()){
                cout << endl << "** Ausgelagerte Ware **" << endl;
                cout << "Ware-ID: " << start[i].getID() << endl;
                cout << "Groesse: " << start[i].getSize() << endl;
                cout << "Beschreibung: " << start[i].getDescription() << endl;
                cout << endl << endl;
                for(int j = i; j < numofPackages-1; j++){
                    start[j] = start[j+1];
                }
                for(int j = 0; j < numofPackages-1; j++){
                    temp[j] = start[j];
                }
                found = true;
                delete [] start;
                start = temp;
                numofPackages--;
                if(numofPackages != 0 && numofPackages <= maxPackages/2) reduce();
                break;
            }
            i++;
        }
        if(!found) cout << endl << "Ware nicht gefunden." << endl;
    }
    else {
        cout << endl << "Lagerhaus ist leer." << endl;
    }

}

void Warehouse::expand()
{
    maxPackages *= 2;
    Package* tempPackages = new Package[maxPackages];
    for(int i = 0; i < numofPackages; i++){
        tempPackages[i] = start[i];
    }
    delete[] start;
    start = tempPackages;
}

void Warehouse::reduce()
{
    maxPackages /= 2;
    Package* tempPackages = new Package[maxPackages];
    for(int i = 0; i < numofPackages; i++){
        tempPackages[i] = start[i];
    }
    delete[] start; //Lösche den alten Array
    start = tempPackages; //Definiere den Array mit dem neuen
} //Temp wird automatisch gelöscht

void Warehouse::sorting()
{
    int input = 0;
    cout << "Sortierung nach: " << endl << "1 - ID (Aufsteigend) \t 3 - Groesse (Aufsteigend)" << endl
         << "2 - ID (Absteigend) \t 4 - Groesse (Absteigend)" << endl;
    cin >> input;

    switch (input) {
    case 1: //Aufsteigende Sortierung nach ID
        for(int i = 0; i < numofPackages; i++){
            Package tmp = start[i];

            int j = i-1;
            while (j >= 0 && tmp.getID() < start[j].getID()) {
                start[j+1] = start[j];
                j--;
            }
            start[j+1] = tmp;
        }
        break;

    case 2: //Absteigende Sortierung nach ID
        for(int i = 0; i < numofPackages; i++){
            Package tmp = start[i];

            int j = i-1;
            while (j >= 0 && tmp.getID() > start[j].getID()) {
                start[j+1] = start[j];
                j--;
            }
            start[j+1] = tmp;
        }
        break;

    case 3: //Aufsteigende Sortierung nach Groesse
         for(int i = 0; i < numofPackages; i++){
             Package tmp = start[i];

             int j = i-1;
             while (j >= 0 && tmp.getSize() < start[j].getSize()) {
                 start[j+1] = start[j];
                 j--;
             }
             start[j+1] = tmp;
        }
        break;

    case 4: //Absteigende Sortierung nach Groesse
        for(int i = 0; i < numofPackages; i++){
            Package tmp = start[i];

            int j = i-1;
            while (j >= 0 && tmp.getSize() > start[j].getSize()) {
                start[j+1] = start[j];
                j--;
            }
            start[j+1] = tmp;
        }
        break;


    default :
        cout << "Falsche Eingabe." << endl;
    }
}
