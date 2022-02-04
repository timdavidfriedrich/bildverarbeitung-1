#include "Bild.hpp"
#include "bearbeitung.hpp"


void Bild::erstellen (std::string dateiname, int anzahlSpalten, int anzahlZeilen) {
    Bild::anzahlSpalten = anzahlSpalten;
    Bild::anzahlZeilen = anzahlZeilen;
    Bild::matrix.clear ();
    Bild::matrix.resize (Bild::anzahlZeilen, std::vector <unsigned char> (Bild::anzahlSpalten, 0));
}


bool Bild::laden (std::string dateiname) {
    std::ifstream datei (dateiname + ".pgm");
    if (datei.is_open ()) {
        datei >> *this;
        datei.close ();
        return true;
    } else {
        datei.close ();
        return false;
    }
}


void Bild::speichern (std::string dateiname) {
    Bild::name = dateiname;
    std::ofstream datei (dateiname + ".pgm");
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


std::ifstream &operator >> (std::ifstream &stream, Bild &bild) {
    bild.matrix.clear ();

    int zeilennummer = 0;
    for (std::string streamZeile; getline (stream, streamZeile);) {
        if (streamZeile.find ("#") == std::string::npos) {
            std::stringstream ss (streamZeile);
            int zahl;
            std::string typ;

            if (zeilennummer == 0) {
                while (ss >> typ) if (typ != "P2") bildFehlerhaft();
            } else if (zeilennummer == 1) {
                std::vector <int> abmessungen;
                while (ss >> zahl) abmessungen.push_back (zahl);
                bild.anzahlZeilen = abmessungen [1];
                bild.anzahlSpalten = abmessungen [0];
            } else if (zeilennummer == 2) {
                while (ss >> zahl) bild.maxGrauwert = zahl;
            } else {
                std::vector <unsigned char> zeile;
                while (ss >> zahl) zeile.push_back (zahl);
                bild.matrix.push_back (zeile);
            }
            zeilennummer ++;
        }
    }

    return stream;
}


std::ostream &operator << (std::ostream &stream, const Bild &bild) {
    stream << "P2" << std::endl;
    stream << bild.anzahlSpalten << " " << bild.anzahlZeilen << std::endl;
    stream << (int) bild.maxGrauwert << std::endl;
    for (std::vector <unsigned char> zeile: bild.matrix) {
        for (unsigned char spalte: zeile) {
            stream << (int) spalte << " ";
        }
        stream << std::endl;
    }
    return stream;
}