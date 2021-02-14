#include "Warehouse.h"
#include <time.h>

using namespace std;


Warehouse::Warehouse(int _maxPackages)
    : 
    maxPackages(_maxPackages),
    start(new Package[maxPackages]), 
    numofPackages(0)
{
}

void Warehouse::print(bool sorted)
{   
    if (numofPackages > 0) {
        cout << endl << "Anzahl der Waren: " << numofPackages << endl;
        cout << "Maximale Kapazitaet: " << maxPackages << endl << endl;
        
        if (sorted) {
            sorting();
        }

        string stringSize[] = { "Klein", "Medium", "Gross" };
        cout << "** Liste der Waren **" << endl;
        for (int i = 0; i < numofPackages; i++) {
            cout << "Ware-ID: " << start[i].getID() << endl;
            cout << "Groesse: " << stringSize[start[i].getSize()] << endl;
            cout << "Beschreibung: " << start[i].getDescription() << endl;
            cout << endl;
        }
    }
    else {
        cout << "Lagerhaus ist leer." << endl << endl;
    }

}

void Warehouse::packageIn(Package* const p)
{
    srand(time(NULL));

    if (numofPackages == maxPackages) expand();

    bool found = 0;
    int i = 0;
    while (i < numofPackages) {
        if (numofPackages > 0 && p->getDescription() == start[i].getDescription()
            && p->getSize() == start[i].getSize())
        {
            found = true;
            break;
        }
        i++;
    }
    if (found) {
        p->setID(start[i].getID());
    }
    else {
        int newID = rand() % 99 + 1;
        //Ueberprufung, ob die generierte ID mit unterschiedlichen Ware bereits zugewiesen ist
        int i = 0;
        while (i < numofPackages) {
            if (newID == start[i].getID()) {
                newID = rand() % 99 + 1;
                i = 0;
            }
            else
            {
                i++;
            }
        }
        p->setID(rand() % 99 + 1);
    }

    //Ware ins Lagerhaus einlagern
    start[numofPackages] = *p;

    numofPackages++;
}

Package Warehouse::packageOut(int ID, bool& found)
{
        Package* temp = new Package[numofPackages];
        int i = 0;
        while (i < numofPackages) {
            if (ID == start[i].getID()) {
                Package* gefunden = new Package;
                *gefunden = start[i];

                for (int j = i; j < numofPackages - 1; j++) {
                    start[j] = start[j + 1];
                }
                for (int j = 0; j < numofPackages - 1; j++) {
                    temp[j] = start[j];
                }
                found = true;
                delete[] start;
                start = temp;
                numofPackages--;
                if (numofPackages != 0 && numofPackages <= maxPackages / 2) reduce();
                
                return *gefunden;
            }
            i++;
        }
        if (!found) {
            Package* emptyObject = new Package();
            return *emptyObject;
        }

}

void Warehouse::expand()
{
    cout << "Lager war voll. Groesse wurde verdoppelt" << endl;
    maxPackages *= 2;
    Package* tempPackages = new Package[maxPackages];
    for (int i = 0; i < numofPackages; i++) {
        tempPackages[i] = start[i];
    }
    delete[] start;
    start = tempPackages;
}

void Warehouse::reduce()
{
    cout << "Lager war zu gross. Groesse wurde reduziert" << endl;
    maxPackages /= 2;
    Package* tempPackages = new Package[maxPackages];
    for (int i = 0; i < numofPackages; i++) {
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
        for (int i = 0; i < numofPackages; i++) {
            Package tmp = start[i];

            int j = i - 1;
            while (j >= 0 && tmp.getID() < start[j].getID()) {
                start[j + 1] = start[j];
                j--;
            }
            start[j + 1] = tmp;
        }
        break;

    case 2: //Absteigende Sortierung nach ID
        for (int i = 0; i < numofPackages; i++) {
            Package tmp = start[i];

            int j = i - 1;
            while (j >= 0 && tmp.getID() > start[j].getID()) {
                start[j + 1] = start[j];
                j--;
            }
            start[j + 1] = tmp;
        }
        break;

    case 3: //Aufsteigende Sortierung nach Groesse
        for (int i = 0; i < numofPackages; i++) {
            Package tmp = start[i];

            int j = i - 1;
            while (j >= 0 && tmp.getSize() < start[j].getSize()) {
                start[j + 1] = start[j];
                j--;
            }
            start[j + 1] = tmp;
        }
        break;

    case 4: //Absteigende Sortierung nach Groesse
        for (int i = 0; i < numofPackages; i++) {
            Package tmp = start[i];

            int j = i - 1;
            while (j >= 0 && tmp.getSize() > start[j].getSize()) {
                start[j + 1] = start[j];
                j--;
            }
            start[j + 1] = tmp;
        }
        break;


    default:
        cout << "Falsche Eingabe." << endl;
    }
}