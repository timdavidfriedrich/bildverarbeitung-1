#include "menu.hpp"
#include "bearbeitung.hpp"
using namespace std;


/**
 * @brief Startet Menü-Abfolge.
 * Gibt den Programmtitel aus, ruft Startmenü zum ersten Mal auf und fragt nach erster Eingabe.
 * 
 * NICHT EXPLIZIT GEFORDERT
 */
void menu () {
    cout << " \n\n"
            << " -- PGM-BILDVERARBEITUNG -- "
            << endl;
    menuAusgabeStart ();
    menuEingabe ();
}


/**
 * @brief Zahl-Eingabe nach Menü.
 * Fragt Zahl ab, die zu Menüeintrag passt.
 * 
 * Wenn input ganze Zahl (int), dann weiter mit menuAuswahl ().
 * Ansonsten Fehlermeldung, Fehlerstatus zurücksetzen, Input leeren, und erneute Abfrage.
 * 
 * NICHT EXPLIZIT GEFORDERT
 */
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


/**
 * @brief Verarbeitet Menü-Input.
 * Verarbeitet die eingebene Zahl und erteilt entsprechend neue Anweisungen.
 * 
 * @param input Eingebene Zahl bei menuEingabe ()
 * 
 * SWITCH: input
 *   Startmenü
 *   CASE: [1] Erstellt neue Bilddaten und gibt Zeichnen-Menü aus.
 *   CASE: [2] Lädt Bilddaten aus Datei ohne Kopie und gibt Zeichnen-Menü aus.
 *   CASE: [3] Kopiert Datei, lädt Bilddaten aus Kopie und gibt Zeichnen-Menü aus.
 *   CASE: [4] Löscht Datei mit gegebenen Namen.
 *   CASE: [0] Beendet Programm.
 *   Zeichnen-Menü
 *   CASE: [5] Startet zeichneLinie () und kehrt zum Zeichnen-Menü zurück.
 *   CASE: [6] Startet zeichneRechteck () und kehrt zum Zeichnen-Menü zurück.
 *   CASE: [7] Speichert offene Datei ab und kehrt zum Startmenü zurück. 
 * 
 * NICHT EXPLIZIT GEFORDERT
 */
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


/**
 * @brief Gibt Startmenü aus.
 * Gibt Menü aus mit Optionen, um Bild auszuwählen.
 * 
 * NICHT EXPLIZIT GEFORDERT
 */
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


/**
 * @brief Gibt Zeichnen-Menü aus.
 * Gibt Menü aus mit Optionen, um auf Bild zu zeichnen.
 * 
 * NICHT EXPLIZIT GEFORDERT
 */
void menuAusgabeZeichnen () {
    cout << " \n\n"
         << " [5] Linie zeichnen \n"
         << " [6] Rechteck zeichnen \n"
         << " [7] Zurück \n"
         << " \n"
         << " (?) Was möchten Sie tun?"
         << endl;
}
