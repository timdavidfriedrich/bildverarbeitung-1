#ifndef BILD_HPP
#define BILD_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


/**
 * @brief Bild-Klasse
 * Regelt Datei-Management (erstellen, speichern, löschen etc.),
 * Bildverarbeitung (in Matrix laden etc.) und 
 * Bildbearbeitung (Linien und Rechtecke zeichnen).
 * 
 * EXPLIZIT GEFORDERT 
 */
class Bild {

    private:

        /* Eigentliches Bild mit Grauwerten in 2x2 Feld */
        std::vector <std::vector <unsigned char>> matrix;

    public:

        /* Dateiname, der u.a. zum Speichern verwendet wird */
        std::string name = "Neues Bild";

        /* Bildhöhe und Bildbreite (zum Rechnen benötigt) */
        int anzahlZeilen, anzahlSpalten = 0;

        /* Maximale Bildbreite (Empfehlung .pgm-Dokumentation) */
        const static int maxSpalten = 70;

        /* Max. Grauwert einzelner Pixel bzw. max. unsigned-char-Kapazität */
        unsigned char maxGrauwert = 255;


        /**
         * @brief Erstellt neues Bild.
         * Erstellt PGM-Datei mit bestimmter Größe.
         * Die vorherige Matrix wird geleert und durch eine neue ersetzt. Alle Grauwerte gleich 0.
         * 
         * @param dateiname Name der zu erstellenden Datei (exkl. ".pgm")
         * @param anzahlSpalten Breite des Bildes bzw. Anzahl unsigned chars in Zeilen-Vektoren
         * @param anzahlZeilen Höhe des Bukdes bzw. Anzahl Zeilen-Vektoren in Matrix-Vektor
         */
        void erstellen (std::string dateiname, int anzahlSpalten, int anzahlZeilen);


        /**
         * @brief Lädt Bild aus Datei.
         * Öffnet Datei, lädt Datei-Inhalt in Bild.
         * 
         * @param dateiname Name der gewählten Datei (exkl. ".pgm")
         * @return true, wenn erfolgreich
         * @return false, wenn Datei nicht gefunden
         * 
         * IMPLIZIT GEFORDERT
         */
        bool laden (std::string dateiname);


        /**
         * @brief Speichert Bild.
         * Öffnet vorhandene/neue Datei und lädt Bilddaten hinein.
         * 
         * @param dateiname Name der gewählten Datei (exkl. ".pgm")
         * 
         * IMPLIZIT GEFORDERT
         */        
        void speichern (std::string dateiname);


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
         * @see zeichneRechteck ()
         * 
         * EXPLIZIT GEFORDERT
         */
        bool zeichneLinie (int vonX, int vonY, int nachX, int nachY, unsigned char grauwert);


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
         * @see zeichneLinie ()
         * 
         * EXPLIZIT GEFORDERT (abgesehen von "unsigned char grauwert")
         */
        void zeichneRechteck (int vonX, int vonY, int nachX, int nachY, unsigned char grauwert);


        /**
         * @brief Operator zum Laden.
         * Leert aktuelle Matrix, liest Zeilen aus Stream und pusht Zeilen-Vektoren mit Werten in Matrix.
         * Ignoriert Zeilen, die "#" enthalten (Kommentare).
         * Wenn erste Zeile nicht "P2", Fehler. Zweite Zeile sind Abmessungen, dritte Zeile maxGrauwert.
         * 
         * @param stream Input-Stream (i.d.R. Datei)
         * @param bild Bildinstanz, die Bilddaten aufnehmen soll
         * @return ifstream& Gibt Stream an Vorgang zurück
         * 
         * EXPLIZIT GEFORDERT
         */
        friend std::ifstream &operator >> (std::ifstream &stream, Bild &bild);


        /**
         * @brief Operator zum Speichern.
         * Lädt erste Zeile als "P2" in Stream. Zweite Zeile sind Abmessungen, dritte Zeile maxGrauwert.
         * Für alle weiteren Zeilen, werden einzelne Werte in Zeilen und Spalten formatiert.
         * 
         * @param stream Output-Stream (i.d.R. für Datei oder cout)
         * @param bild Bildinstanz, deren Daten gespeichert werden sollen
         * @return ostream& Gibt Stream an Vorgang zurück
         * 
         * EXPLIZIT GEFORDERT
         */
        friend std::ostream &operator << (std::ostream &stream, const Bild &bild);

};


#endif