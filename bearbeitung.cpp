#include "bearbeitung.hpp"
#include "Bild.hpp"
using namespace std;


Bild bild; // Bild-Instanz, dessen Daten manipuliert wird.


void bildErstellen () {
    string dateiname;
    int anzahlSpalten;
    int anzahlZeilen;

    cout << "\n (?) Welcher Name soll für die Datei gewählt werden (ohne Endung)? \n >>  ";
    cin >> dateiname;
    cout << "\n (?) Wie viele Pixel breit soll das Bild sein (max. " << Bild::maxSpalten << ")? \n >>  ";
    cin >> anzahlSpalten;
    cout << "\n (?) Wie viele Pixel hoch soll das Bild sein? \n >>  ";
    cin >> anzahlZeilen;

    if (cin) {
        if (anzahlSpalten > 0 && anzahlZeilen > 0) {
            if (anzahlSpalten <= Bild::maxSpalten) {
                bild.erstellen (dateiname, anzahlSpalten, anzahlZeilen);
                bild.speichern (dateiname);
                cout << "\n\n" << bild;
            } else {
                cout << "\n (!) Das Bild darf maximal " << Bild::maxSpalten << " Pixel breit sein! \n";
                bildErstellen ();
            }
        } else {
            cout << "\n (!) Das Bild muss mindestens 1 x 1 Pixel groß sein! \n";
            bildErstellen ();
        }
    } else {
        cout << " \n\n (!) Bitte geben Sie ganze Zahlen für die Maße ein." << endl;
        cin.clear (); string muelleimer; getline (cin, muelleimer); // cin leeren
        bildErstellen ();
    }
    
}


bool bildLaden () {
    string dateiname;

    cout << "\n (?) Wie heißt die Datei, die bearbeitet werden soll (ohne Endung)? \n >>  ";
    cin >> dateiname;

    if (bild.laden (dateiname)) {
        bild.speichern (dateiname);
        cout << "\n\n" << bild;  
        return true;
    } else {
        cout << "\n (!) Die Datei \"" << dateiname << ".pgm\" existiert nicht! \n";
        return false;
    }
}


bool bildKopieren () {
    string dateiname;
    string neuerName;

    cout << "\n (?) Wie heißt die Originaldatei, die kopiert werden soll (ohne Endung)? \n >>  ";
    cin >> dateiname;
    cout << "\n (?) Welcher Name soll für die Kopie gewählt werden (ohne Endung)? \n >>  ";
    cin >> neuerName;

    if (bild.laden (dateiname)) {
        bild.speichern (neuerName);
        cout << "\n\n" << bild;  
        return true;
    } else {
        cout << "\n (!) Die Datei \"" << dateiname << ".pgm\" existiert nicht! \n";
        return false;
    }
}


void bildEntfernen () {
    string dateiname;

    cout << "\n (?) Wie heißt die Datei, die gelöscht werden soll (ohne Endung)? \n >>  ";
    cin >> dateiname;

    try {
        if (filesystem::remove (dateiname + ".pgm")) {
            cout << "\n (:) Die Datei \"" << dateiname << ".pgm\" wurde gelöscht." << endl;
        } else {
            cout << "\n (!) Die Datei \"" << dateiname << ".pgm\" existiert nicht! \n";
        }
    }
    catch (const filesystem::filesystem_error &e) {
        cout << "\n (!) FATALER FEHLER: " << e.what () << "\n" << endl;
    }
}


void bildZeichneLinie () {
    int vonX, vonY, nachX, nachY;
    int intGrauwert;
    unsigned char grauwert;

    cout << "\n (?) Von welchem Punkt aus soll die Linie beginnen (Format: \"X Y\", Beispiel: \"0 4\")? \n >>  ";
    cin >> vonX >> vonY;
    cout << "\n (?) An welchem Punkt soll die Linie enden (Format: \"X Y\", Beispiel: \"6 4\")? \n >>  ";
    cin >> nachX >> nachY;
    cout << "\n (?) Welchen Grauwert soll die Linie annehmen (0 bis " << (int) bild.maxGrauwert << ")? \n >>  ";
    cin >> intGrauwert;

    if (cin) {
        if (vonX < bild.anzahlSpalten && vonY < bild.anzahlZeilen && nachX < bild.anzahlSpalten && nachY < bild.anzahlZeilen && vonX >= 0 && vonY >= 0 && nachX >= 0 && nachY >= 0) {
            if (intGrauwert >= 0 && intGrauwert <= (int) bild.maxGrauwert) {
                grauwert = intGrauwert;
                if (bild.zeichneLinie (vonX, vonY, nachX, nachY, grauwert)) {
                    cout << "\n\n" << bild;
                } else {
                    cout << " \n (!) Linien dürfen nicht diagonal gezogen werden!" << endl;
                    bildZeichneLinie ();
                }
            } else {
                cout << " \n (!) Der Grauwert darf maximal " << (int) bild.maxGrauwert << " betragen!" << endl;
                bildZeichneLinie ();
            }
        } else {
            cout << " \n (!) Mindestens einer der Punkte befindet sich außerhalb des Bildbereichs!" << endl;
            bildZeichneLinie ();
        }
    } else {
        cout << " \n (!) Falsches Format!" << endl;
        cin.clear (); string muelleimer; getline (cin, muelleimer); // cin leeren
        bildZeichneLinie ();
    }

    bild.speichern (bild.name);
}


void bildZeichneRechteck () {
    int vonX, vonY, nachX, nachY;
    int intGrauwert;
    unsigned char grauwert;

    cout << "\n (?) An welchem Punkt soll sich die erste Ecke des Rechtecks befinden (Format: \"X Y\", Beispiel: \"3 1\")? \n >>  ";
    cin >> vonX >> vonY;
    cout << "\n (?) An welchem Punkt soll sich die entgegengesetze Ecke befinden (Format: \"X Y\", Beispiel: \"6 10\")? \n >>  ";
    cin >> nachX >> nachY;
    cout << "\n (?) Welchen Grauwert soll der Rand des Rechtecks annehmen (0 bis " << (int) bild.maxGrauwert << ")? \n >>  ";
    cin >> intGrauwert;
    
    if (cin) {
        if (vonX < bild.anzahlSpalten && vonY < bild.anzahlZeilen && nachX < bild.anzahlSpalten && nachY < bild.anzahlZeilen && vonX >= 0 && vonY >= 0 && nachX >= 0 && nachY >= 0) {
            if (intGrauwert >= 0 && intGrauwert <= (int) bild.maxGrauwert) {
                grauwert = intGrauwert;
                bild.zeichneRechteck (vonX, vonY, nachX, nachY, grauwert);
                cout << "\n\n" << bild;
            } else {
                cout << " \n (!) Der Grauwert darf maximal " << (int) bild.maxGrauwert << " betragen!" << endl;
                bildZeichneRechteck ();
            }
        } else {
            cout << " \n (!) Mindestens einer der Punkte befindet sich außerhalb des Bildbereichs!" << endl;
            bildZeichneRechteck ();
        }
    } else {
        cout << " \n (!) Falsches Format!" << endl;
        cin.clear (); string muelleimer; getline (cin, muelleimer); // cin leeren
        bildZeichneLinie ();
    }

    bild.speichern (bild.name);
}