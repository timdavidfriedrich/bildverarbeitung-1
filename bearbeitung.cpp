#include "bearbeitung.hpp"
#include "Bild.hpp"
using namespace std;


Bild bild; // Bild-Instanz, deren Daten manipuliert werden.


/**
 * @brief Abfrage zur Bilderstellung.
 * Fragt nach Dateiname und Bildmaße, mit denen Bild erstellt werden soll.
 * Speichert erstelltes Bild anschließend und gibt es aus.
 */
void bildErstellen () {
    string dateiname;
    int anzahlSpalten;
    int anzahlZeilen;

    cout << "\n (?) Welcher Name soll für die Datei gewählt werden (ohne Endung)? \n >> ";
    cin >> dateiname;
    cout << "\n (?) Wie viele Pixel breit soll das Bild sein (max. " << Bild::maxSpalten << ")? \n >> ";
    cin >> anzahlSpalten;
    cout << "\n (?) Wie viele Pixel hoch soll das Bild sein? \n >> ";
    cin >> anzahlZeilen;

    bild.erstellen (dateiname, anzahlSpalten, anzahlZeilen);
    bild.speichern (dateiname);
    cout << "\n\n" << bild;
}


/**
 * @brief Abfrage zum Laden eines Bilds.
 * Fragt nach Namen von originaler Datei, lädt und speichert diese, und gibt sie aus.
 */
void bildLaden () {
    string dateiname;

    cout << "\n (?) Wie heißt die Datei, die bearbeitet werden soll (ohne Endung)? \n >> ";
    cin >> dateiname;

    bild.laden (dateiname);
    bild.speichern (dateiname);
    cout << "\n\n" << bild;
}


/**
 * @brief Abfrage zum Kopieren eines Bilds.
 * Fragt nach Namen von originaler Datei, lädt diese und speichert Daten in neuer Datei.
 * Gibt anschließend Bild aus.
 */
void bildKopieren () {
    string dateiname;
    string neuerName;

    cout << "\n (?) Wie heißt die Originaldatei, die kopiert werden soll (ohne Endung)? \n >> ";
    cin >> dateiname;
    cout << "\n (?) Welcher Name soll für die Kopie gewählt werden (ohne Endung)? \n >> ";
    cin >> neuerName;

    bild.laden (dateiname);
    bild.speichern (neuerName);
    cout << "\n\n" << bild;
}


/**
 * @brief Entfernt Bilddatei.
 * Versucht Datei mit bestimmten Namen zu löschen. Wenn nicht vorhanden, Fehler.
 * Danach Zurücksetzung des Fehlerstatuses und Entleerung der Eingabe.
 */
void bildEntfernen () {
    string dateiname;

    cout << "\n (?) Wie heißt die Datei, die gelöscht werden soll (ohne Endung)? \n >> ";
    cin >> dateiname;

    try {
        if (filesystem::remove (dateiname + ".pgm")) {
            cout << "\n (:) Die Datei \"" << dateiname << ".pgm\" wurde gelöscht." << endl;
        } else {
            cout << "\n (!) Die Datei \"" << dateiname << ".pgm\" existiert nicht!";
            cin.clear (); // Fehler-Reset
            string muelleimer; 
            getline (cin, muelleimer); // Abladen in String
            bildEntfernen (); // Erneute Abfrage
        }
    }
    catch (const filesystem::filesystem_error &e) {
        cout << "\n (!) FATALER FEHLER: " << e.what () << endl;
    }
}


/**
 * @brief Abfrage zur Linienzeichnung.
 * Fragt nach Linien-Koordinaten und Linien-Grauwert. Führt Zeichnung aus.
 * Wenn erfolgreich (nicht diagonal), dann Ausgabe des Bildes mit Änderung.
 * Ansonsten erneute Abfrage.
 */
void bildZeichneLinie () {
    int vonX, vonY, nachX, nachY;
    int intGrauwert;
    unsigned char grauwert;

    cout << "\n (?) Von welchem Punkt aus soll die Linie beginnen (Format: \"X Y\", Beispiel: \"0 4\")? \n >> ";
    cin >> vonX >> vonY;
    cout << "\n (?) An welchem Punkt soll die Linie enden (Format: \"X Y\", Beispiel: \"6 4\")? \n >> ";
    cin >> nachX >> nachY;
    cout << "\n (?) Welchen Grauwert soll die Linie annehmen (0 bis " << (int) bild.maxGrauwert << ")? \n >> ";
    cin >> intGrauwert;

    if (vonX < bild.anzahlSpalten && vonY < bild.anzahlZeilen && nachX < bild.anzahlSpalten && nachY < bild.anzahlZeilen) {
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
    bild.speichern (bild.name);
}


/**
 * @brief Abfrage zur Rechteckzeichnung.
 * Fragt nach Rechteck-Koordinaten und Rechteck-Grauwert. Führt Zeichnung aus.
 * Gibt anschließend geändertes Bild aus und speichert in Datei.
 */
void bildZeichneRechteck () {
    int vonX, vonY, nachX, nachY;
    int intGrauwert;
    unsigned char grauwert;

    cout << "\n (?) An welchem Punkt soll sich die erste Ecke des Rechtecks befinden (Format: \"X Y\", Beispiel: \"3 1\")? \n >> ";
    cin >> vonX >> vonY;
    cout << "\n (?) An welchem Punkt soll sich die entgegengesetze Ecke befinden (Format: \"X Y\", Beispiel: \"6 10\")? \n >> ";
    cin >> nachX >> nachY;
    cout << "\n (?) Welchen Grauwert soll der Rand des Rechtecks annehmen (0 bis " << (int) bild.maxGrauwert << ")? \n >> ";
    cin >> intGrauwert;

    if (vonX < bild.anzahlSpalten && vonY < bild.anzahlZeilen && nachX < bild.anzahlSpalten && nachY < bild.anzahlZeilen) {
        if (grauwert >= 0 && grauwert <= bild.maxGrauwert) {
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
    bild.speichern (bild.name);
}