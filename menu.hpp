#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>


/**
 * @brief Startet Menü-Abfolge.
 * Gibt den Programmtitel aus, ruft Startmenü zum ersten Mal auf und fragt nach erster Eingabe.
 */
void menu ();

/**
 * @brief Zahl-Eingabe nach Menü.
 * Fragt Zahl ab, die zu Menüeintrag passt.
 * 
 * Wenn input ganze Zahl (int), dann weiter mit menuAuswahl ().
 * Ansonsten Fehlermeldung, Fehlerstatus zurücksetzen, Input leeren, und erneute Abfrage.
 */
void menuEingabe ();

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
 *   CASE: [5] Startet @see zeichneLinie () und kehrt zum Zeichnen-Menü zurück.
 *   CASE: [6] Startet @see zeichneRechteck () und kehrt zum Zeichnen-Menü zurück.
 *   CASE: [7] Speichert offene Datei ab und kehrt zum Startmenü zurück. 
 */
void menuAuswahl (int input);

/**
 * @brief Gibt Startmenü aus.
 * Gibt Menü aus mit Optionen, um Bild auszuwählen.
 * 
 * @see menuAusgabeZeichnen ()
 */
void menuAusgabeStart ();

/**
 * @brief Gibt Zeichnen-Menü aus.
 * Gibt Menü aus mit Optionen, um auf Bild zu zeichnen.
 * 
 * @see menuAusgabeStart ()
 */
void menuAusgabeZeichnen ();


#endif