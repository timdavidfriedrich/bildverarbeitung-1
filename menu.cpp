#include "menu.hpp"
#include "bearbeitung.hpp"
using namespace std;


void menu () {
    cout << " \n\n"
            << " -- PGM-BILDVERARBEITUNG -- "
            << endl;
    menuAusgabeStart ();
    menuEingabe ();
}


void menuEingabe () {
    int input;
    cout << " >>  ";
    cin >> input;
    if (cin) {
        menuAuswahl (input);
    } else {
        cout << "\n\n (!) Bitte geben Sie eine ganze Zahl ein. \n (?) Was möchten Sie tun?" << endl;
        cin.clear (); // Fehler-Reset
        string muelleimer; // Temporärer String
        getline (cin, muelleimer); // Abladen in String
        menuEingabe ();
    }
}


void menuAuswahl (int input) {
    switch (input) {
        case 1:
            bildErstellen ();
            menuAusgabeZeichnen ();
            menuEingabe ();
            break;
        case 2:
            if (bildLaden ()) {
                menuAusgabeZeichnen ();
            } else {
                menuAusgabeStart ();
            }
            menuEingabe ();
            break;
        case 3:
            if (bildKopieren ()) {
                menuAusgabeZeichnen ();
            } else {
                menuAusgabeStart ();
            }
            menuEingabe ();
            break;
        case 4:
            bildEntfernen ();
            menuAusgabeStart ();
            menuEingabe ();
            break;
        case 5:
            bildZeichneLinie ();
            menuAusgabeZeichnen ();
            menuEingabe ();
            break;
        case 6:
            bildZeichneRechteck ();
            menuAusgabeZeichnen ();
            menuEingabe ();
            break;    
        case 7:
            menuAusgabeStart ();
            menuEingabe ();
            break;
        case 0:
            cout << "\n\n (:) Programm beendet. Erneut abrufbar mit \"./PGM\". \n\n" << endl;
            break;
        default:
            cout << "\n (!) Diese Zahl verweist auf keinen Menüpunkt! \n (?) Was möchten Sie tun?" << endl;
            menuEingabe ();
            break;
    }
}


void menuAusgabeStart () {
    cout << " \n\n"
         << " [1] Neue Bilddatei erzeugen \n"
         << " [2] Bilddatei direkt bearbeiten \n"
         << " [3] Bilddatei kopieren \n"
         << " [4] Bilddatei entfernen \n"
         << " [0] Beenden \n"
         << " \n"
         << " (?) Was möchten Sie tun?"
         << endl;
}


void menuAusgabeZeichnen () {
    cout << " \n\n"
         << " [5] Linie zeichnen \n"
         << " [6] Rechteck zeichnen \n"
         << " [7] Zurück \n"
         << " \n"
         << " (?) Was möchten Sie tun?"
         << endl;
}
