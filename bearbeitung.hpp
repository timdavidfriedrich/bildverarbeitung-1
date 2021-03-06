#ifndef BEARBEITUNG_HPP
#define BEARBEITUNG_HPP

#include <iostream>
#include <filesystem>


/**
 * @brief Abfrage zur Bilderstellung.
 * Fragt nach Dateiname und Bildmaße, mit denen Bild erstellt werden soll.
 * Speichert erstelltes Bild anschließend und gibt es aus.
 * 
 * @see erstellen ()
 * @see speichern ()
 */
void bildErstellen ();


/**
 * @brief Abfrage zum Laden eines Bilds.
 * Fragt nach Namen von originaler Datei, lädt und speichert diese, und gibt sie aus.
 * 
 * @see laden ()
 * @see speichern ()
 * @see bildKopieren () 
 */
bool bildLaden ();


/**
 * @brief Abfrage zum Kopieren eines Bilds.
 * Fragt nach Namen von originaler Datei, lädt diese und speichert Daten in neuer Datei.
 * Gibt anschließend Bild aus.
 * 
 * @see laden ()
 * @see speichern ()
 * @see bildLaden () 
 */
bool bildKopieren ();


/**
 * @brief Entfernt Bilddatei.
 * Versucht Datei mit bestimmten Namen zu löschen. Wenn nicht vorhanden, Fehler.
 * Danach Zurücksetzung des Fehlerstatuses und Entleerung der Eingabe.
 */
void bildEntfernen ();


/**
 * @brief Abfrage zur Linienzeichnung.
 * Fragt nach Linien-Koordinaten und Linien-Grauwert.
 * Wenn Koordinaten im Bild und Grauwert gültig, dann Zeichnung.
 * Ist Zeichnung fehlgeschlagen (weil z.B. diagonal), dann erneute Abfrage.
 * Gibt anschließend geändertes Bild aus und speichert in Datei.
 * 
 * @see zeichneLinie ()
 * @see bildZeichneRechteck ()
 */
void bildZeichneLinie ();


/**
 * @brief Abfrage zur Rechteckzeichnung.
 * Fragt nach Rechteck-Koordinaten und Rechteck-Grauwert.
 * Wenn Koordinaten im Bild und Grauwert gültig, dann Zeichnung.
 * Gibt anschließend geändertes Bild aus und speichert in Datei.
 * 
 * @see zeichneRechteck ()
 * @see bildZeichneLinie ()
 */
void bildZeichneRechteck ();


/**
 * @brief Meldung Fehlerhaftes Bild
 * Gibt Fehlermeldung aus, wenn kein PGM.
 * 
 * @pre Erste Zeile von Datei kein "P2"
 */
void bildFehlerhaft ();


#endif