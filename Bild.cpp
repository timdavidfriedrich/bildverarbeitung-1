#include "Bild.hpp"
using namespace std;


/**
 * @brief Erstellt neues Bild.
 * Erstellt PGM-Datei mit bestimmter Größe.
 * Die vorherige Matrix wird geleert und durch eine neue ersetzt. Alle Grauwerte gleich 0.
 * 
 * @param dateiname Name der zu erstellenden Datei (exkl. ".pgm")
 * @param anzahlSpalten Breite des Bildes bzw. Anzahl unsigned chars in Zeilen-Vektoren
 * @param anzahlZeilen Höhe des Bukdes bzw. Anzahl Zeilen-Vektoren in Matrix-Vektor
 */
void Bild::erstellen (string dateiname, int anzahlSpalten, int anzahlZeilen) {
    Bild::anzahlSpalten = anzahlSpalten;
    Bild::anzahlZeilen = anzahlZeilen;
    Bild::matrix.clear ();
    Bild::matrix.resize (Bild::anzahlZeilen, vector <unsigned char> (Bild::anzahlSpalten, 0));
}


/**
 * @brief Lädt Bild aus Datei.
 * Öffnet Datei, lädt Datei-Inhalt in Bild.
 * 
 * @param dateiname = Name der gewählten Datei (exkl. ".pgm")
 */
void Bild::laden (string dateiname) {
    ifstream datei (dateiname + ".pgm");
    if (datei.is_open ()) {
        datei >> *this;
    } else {
        cout << "\n (!) Die Datei \"" << dateiname << ".pgm\" existiert nicht!";
    }
    datei.close ();
}


/**
 * @brief Speichert Bild.
 * Öffnet vorhandene/neue Datei und lädt Bilddaten hinein.
 * 
 * @param dateiname = Name der gewählten Datei (exkl. ".pgm")
 */
void Bild::speichern (string dateiname) {
    Bild::name = dateiname;
    ofstream datei (dateiname + ".pgm");
    datei << *this;
    datei.close ();
}


/**
 * @brief Zeichnet Linie in Bild.
 * Matrix-Einträge gleicher Spalte/Zeile von Start zu Ende auf neuen Grauwert gesetzt.
 * Zudem Überprüfung, ob Startpunkt größer oder kleiner als Ende (=> unterschiedliche Rechnung).
 * 
 * @pre Koordinanten innerhalb des Bildes
 * @pre Grauwerte nicht über Limit
 * @pre Punkte in gleicher Spalte (X gleich) oder Reihe (Y gleich)
 * @param vonX X-Koordinate des Linien-Anfangs
 * @param vonY Y-Koordinate des Linien-Anfangs
 * @param nachX X-Koordinate des Linien-Endes
 * @param nachY Y-Koordinate des Linien-Endes
 * @param grauwert Grauwert, den Linie annehmen soll
 * @return true, wenn Zeichnung möglich (X oder Y gleich)
 * @return false, wenn diagonal
 */
bool Bild::zeichneLinie (int vonX, int vonY, int nachX, int nachY, unsigned char grauwert) {
    if (vonX == nachX) {
        if (vonY <= nachY) {
            for (int y = 0; y <= nachY - vonY; y++) matrix [vonY + y] [vonX]  = grauwert;
        } else {
            for (int y = 0; y <= vonY - nachY; y++) matrix [nachY + y] [vonX] = grauwert;
        }
        return true;
    } else if (vonY == nachY) {
        if (vonX <= nachX) {
            for (int x = 0; x <= nachX - vonX; x++) matrix [vonY] [vonX + x] = grauwert;
        } else {
            for (int x = 0; x <= vonX - nachX; x++) matrix [vonY] [nachX + x] = grauwert;
        }
        return true;
    } else {
        return false;
    }
}


/**
 * @brief Zeichnet Rechteck-Rand in Bild.
 * Zeichnet 2 Linien (vgl. zeichneLinie ()) von Start-X/Y zu End-X/Y und je deren parallele Linie (gesamt 4).
 * Zudem Überprüfung, ob Start rechts/links und höher/tiefer von Ende (=> unterschiedliche Rechnung). 
 * 
 * @pre Koordinanten innerhalb des Bildes
 * @pre Grauwerte nicht über Limit
 * @param vonX X-Koordinate der ersten Ecke
 * @param vonY Y-Koordinate der ersten Ecke
 * @param nachX X-Koordinate der gegenüberliegenden Ecke
 * @param nachY Y-Koordinate der gegenüberliegenden Ecke
 * @param grauwert Grauwert, den Rechteck-Rand annehmen soll
 */
void Bild::zeichneRechteck (int vonX, int vonY, int nachX, int nachY, unsigned char grauwert) {
    if (vonX <= nachX) {
        for (int x = 0; x <= nachX - vonX; x++) {
            matrix [vonY] [vonX + x] = grauwert;
            matrix [nachY] [vonX + x] = grauwert;
        }
    } else {
        for (int x = 0; x <= vonX - nachX; x++) {
            matrix [vonY] [nachX + x] = grauwert;
            matrix [nachY] [nachX + x] = grauwert;
        }
    }
    if (vonY <= nachY) {
        for (int y = 0; y <= nachY - vonY; y++) {
            matrix [vonY + y] [vonX] = grauwert;
            matrix [vonY + y] [nachX] = grauwert;
        }
    } else {
        for (int y = 0; y <= vonY - nachY; y++) {
            matrix [nachY + y] [vonX] = grauwert;
            matrix [nachY + y] [nachX] = grauwert;
        }
    }
}


/**
 * @brief Operator zum Laden.
 * Leert aktuelle Matrix, liest Zeilen aus Stream und pusht Zeilen-Vektoren mit Werten in Matrix.
 * Ignoriert Zeilen, die "#" enthalten (Kommentare).
 * Wenn erste Zeile nicht "P2", Fehler. Zweite Zeile sind Abmessungen, dritte Zeile maxGrauwert.
 * 
 * @param stream Input-Stream (i.d.R. Datei)
 * @param bild Bildinstanz, die Bilddaten aufnehmen soll
 * @return ifstream& Gibt Stream an Vorgang zurück
 */
ifstream &operator >> (ifstream &stream, Bild &bild) {
    bild.matrix.clear ();

    int zeilennummer = 0;
    for (string streamZeile; getline (stream, streamZeile);) {
        if (streamZeile.find ("#") == string::npos) {
            stringstream ss (streamZeile);
            int zahl;
            string typ;

            if (zeilennummer == 0) {
                while (ss >> typ) if (typ != "P2") cout << "\n (!) Die gewählte Datei ist fehlerhaft!" << endl;
            } else if (zeilennummer == 1) {
                vector <int> abmessungen;
                while (ss >> zahl) abmessungen.push_back (zahl);
                bild.anzahlZeilen = abmessungen [1];
                bild.anzahlSpalten = abmessungen [0];
            } else if (zeilennummer == 2) {
                while (ss >> zahl) bild.maxGrauwert = zahl;
            } else {
                vector <unsigned char> zeile;
                while (ss >> zahl) zeile.push_back (zahl);
                bild.matrix.push_back (zeile);
            }
            zeilennummer ++;
        }
    }

    return stream;
}

/**
 * @brief Operator zum Speichern.
 * Lädt erste Zeile als "P2" in Stream. Zweite Zeile sind Abmessungen, dritte Zeile maxGrauwert.
 * Für alle weiteren Zeilen, werden einzelne Werte in Zeilen und Spalten formatiert.
 * 
 * @param stream Output-Stream (i.d.R. für Datei oder cout)
 * @param bild Bildinstanz, deren Daten gespeichert werden sollen
 * @return ostream& Gibt Stream an Vorgang zurück
 */
ostream &operator << (ostream &stream, const Bild &bild) {
    stream << "P2" << endl;
    stream << bild.anzahlSpalten << " " << bild.anzahlZeilen << endl;
    stream << (int) bild.maxGrauwert << endl;
    for (vector <unsigned char> zeile: bild.matrix) {
        for (unsigned char spalte: zeile) {
            stream << (int) spalte << " ";
        }
        stream << endl;
    }
    return stream;
}
