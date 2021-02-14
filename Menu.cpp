#include "Menu.h"

using namespace std;

Menu::Menu()
	:
	w(2)
{
	
}

void Menu::showOptions()
{
    char eingabe;
    do {

        cout << "** Willkommen in der Lagerverwaltung. **" << endl;
        cout << "Bitte taetigen Sie Ihre Eingabe: " << endl;
        cout << "(b): Den Lagerbestand ausgeben." << endl;
        cout << "(a): Ein Objekt aus dem Lager auslagern." << endl;
        cout << "(e): Ein neues Objekt einlagern." << endl;
        cout << "(x): Die Eingabe beenden." << endl;
        cout << "Eingabe: ";
        cin >> eingabe;
        while (eingabe != 'a' && eingabe != 'b' && eingabe != 'e' && eingabe != 'x') {
            cout << "Falsche Eingabe. Wiederholen Sie." << endl;
            cout << "Eingabe: ";
            cin >> eingabe;
        }
        cout << endl;

        switch (eingabe) {
        case AUSGABE:
            char sorted;
            cout << "Sortiert? (y/n)" << endl;
            cin >> sorted;
            if (sorted == 'y') {
                w.print(true);
            }
            else
            {
                w.print(); //default false
            }
            break;

        case AUSLAGERN:
        {
            int id_input;
            cout << "Geben Sie die ID der auszulagernden Ware: ";
            cin >> id_input;
            bool found = false;
            Package* out = new Package;
            *out = w.packageOut(id_input, found);
            if (found) {
                string stringSize[] = { "Klein", "Medium", "Gross" };
                cout << endl << "** Ausgelagerte Ware **" << endl;
                cout << "Ware-ID: " << out->getID() << endl;
                cout << "Groesse: " << stringSize[out->getSize()] << endl;
                cout << "Beschreibung: " << out->getDescription() << endl;
                cout << endl << endl;
            }
            else
            {
                cout << "Ware nicht gefunden." << endl << endl;
            }
            delete out;
            break;
        }

        case EINLAGERN:
        {
            int size_input;
            std::string description_input;
            cout << "Geben Sie die Groesse der Ware und die Beschreibung dazu." << endl;
            cout << "Groesse:" << endl << "0 fuer klein\n1 fuer medium\n2 fuer gross" << endl;
            cin >> size_input;
            cout << "Beschreibung: ";
            cin >> description_input;
            Package* package = new Package((Package::packageSize)size_input, description_input);
            w.packageIn(package);
            delete package; //Ware, die wir erstellt haben, wird geloescht, weil die bereits ins Lager eingelagert ist
            cout << endl;
            cout << "Ware wurde eingelagert" << endl << endl;
            break;
        }
        }
    } while (eingabe != EXIT);
}
