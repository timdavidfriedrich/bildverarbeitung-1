#ifndef BILD_HPP
#define BILD_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;


/**
 * @brief Bild-Klasse
 * Regelt Datei-Management, Bildverarbeitung und -bearbeitung.
 * 
 * @param anzahlZeilen Bildhöhe (zum Rechnen benötigt)
 * @param anzahlSpalten Bildbreite (zum Rechnen benötigt)
 * @param matrix Eigentliches Bild mit Grauwerten
 * @param name Dateiname, der u.a. zum Speichern verwendet wird
 * @param maxSpalten Maximale Bildbreite (Empfehlung .pgm-Dokumentation)
 * @param maxGrauwert Max. Grauwert einzelner Pixel bzw. max. unsigned-char-Kapazität
 * 
 * EXPLIZIT GEFORDERT (zumindest Klasse mit Matrix, Operatoren und Zeichnen-Funktionen)
 */
class Bild {

    private:
        vector <vector <unsigned char>> matrix;

    public:
        string name = "Neues Bild";
        int anzahlZeilen, anzahlSpalten = 0;
        const static int maxSpalten = 70; // .pgm-Standard
        unsigned char maxGrauwert = 255;

        void erstellen (string dateiname, int anzahlSpalten, int anzahlZeilen);
        bool laden (string dateiname);
        void kopieren (string originalname, string dateiname);
        void speichern (string dateiname);
        bool zeichneLinie (int vonX, int vonY, int nachX, int nachY, unsigned char grauwert);
        void zeichneRechteck (int vonX, int vonY, int nachX, int nachY, unsigned char grauwert);
        friend ifstream &operator >> (ifstream &stream, Bild &bild);
        friend ostream &operator << (ostream &stream, const Bild &bild);

};


#endif