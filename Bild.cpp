#include "Bild.hpp"
using namespace std;


void Bild::erstellen (string dateiname, int anzahlSpalten, int anzahlZeilen) {
    Bild::anzahlSpalten = anzahlSpalten;
    Bild::anzahlZeilen = anzahlZeilen;
    Bild::matrix.clear ();
    Bild::matrix.resize (Bild::anzahlZeilen, vector <unsigned char> (Bild::anzahlSpalten, 0));
}


bool Bild::laden (string dateiname) {
    ifstream datei (dateiname + ".pgm");
    if (datei.is_open ()) {
        datei >> *this;
        datei.close ();
        return true;
    } else {
        datei.close ();
        return false;
    }
}


void Bild::speichern (string dateiname) {
    Bild::name = dateiname;
    ofstream datei (dateiname + ".pgm");
    datei << *this;
    datei.close ();
}


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