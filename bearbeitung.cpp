#include "bearbeitung.hpp"
#include "Bild.hpp"


Bild bild; // Bild-Instanz, dessen Daten manipuliert wird.


void bildErstellen () {
    std::string dateiname;
    int anzahlSpalten;
    int anzahlZeilen;

    std::cout << "\n (?) Welcher Name soll für die Datei gewählt werden (ohne Endung)? \n >>  ";
    std::cin >> dateiname;
    std::cout << "\n (?) Wie viele Pixel breit soll das Bild sein (max. " << Bild::maxSpalten << ")? \n >>  ";
    std::cin >> anzahlSpalten;
    std::cout << "\n (?) Wie viele Pixel hoch soll das Bild sein? \n >>  ";
    std::cin >> anzahlZeilen;

    if (std::cin) {
        if (anzahlSpalten > 0 && anzahlZeilen > 0) {
            if (anzahlSpalten <= Bild::maxSpalten) {
                bild.erstellen (dateiname, anzahlSpalten, anzahlZeilen);
                bild.speichern (dateiname);
                std::cout << "\n\n" << bild;
            } else {
                std::cout << "\n (!) Das Bild darf maximal " << Bild::maxSpalten << " Pixel breit sein! \n";
                bildErstellen ();
            }
        } else {
            std::cout << "\n (!) Das Bild muss mindestens 1 x 1 Pixel groß sein! \n";
            bildErstellen ();
        }
    } else {
        std::cout << " \n\n (!) Bitte geben Sie ganze Zahlen für die Maße ein." << std::endl;
        std::cin.clear (); std::string muelleimer; getline (std::cin, muelleimer); // cin leeren
        bildErstellen ();
    }
    
}


bool bildLaden () {
    std::string dateiname;

    std::cout << "\n (?) Wie heißt die Datei, die bearbeitet werden soll (ohne Endung)? \n >>  ";
    std::cin >> dateiname;

    if (bild.laden (dateiname)) {
        bild.speichern (dateiname);
        std::cout << "\n\n" << bild;  
        return true;
    } else {
        std::cout << "\n (!) Die Datei \"" << dateiname << ".pgm\" existiert nicht! \n";
        return false;
    }
}


bool bildKopieren () {
    std::string dateiname;
    std::string neuerName;

    std::cout << "\n (?) Wie heißt die Originaldatei, die kopiert werden soll (ohne Endung)? \n >>  ";
    std::cin >> dateiname;
    std::cout << "\n (?) Welcher Name soll für die Kopie gewählt werden (ohne Endung)? \n >>  ";
    std::cin >> neuerName;

    if (bild.laden (dateiname)) {
        bild.speichern (neuerName);
        std::cout << "\n\n" << bild;  
        return true;
    } else {
        std::cout << "\n (!) Die Datei \"" << dateiname << ".pgm\" existiert nicht! \n";
        return false;
    }
}


void bildEntfernen () {
    std::string dateiname;

    std::cout << "\n (?) Wie heißt die Datei, die gelöscht werden soll (ohne Endung)? \n >>  ";
    std::cin >> dateiname;

    try {
        if (std::filesystem::remove (dateiname + ".pgm")) {
            std::cout << "\n (:) Die Datei \"" << dateiname << ".pgm\" wurde gelöscht." << std::endl;
        } else {
            std::cout << "\n (!) Die Datei \"" << dateiname << ".pgm\" existiert nicht! \n";
        }
    }
    catch (const std::filesystem::filesystem_error &e) {
        std::cout << "\n (!) FATALER FEHLER: " << e.what () << "\n" << std::endl;
    }
}


void bildZeichneLinie () {
    int vonX, vonY, nachX, nachY;
    int intGrauwert;
    unsigned char grauwert;

    std::cout << "\n (?) Von welchem Punkt aus soll die Linie beginnen (Format: \"X Y\", Beispiel: \"0 4\")? \n >>  ";
    std::cin >> vonX >> vonY;
    std::cout << "\n (?) An welchem Punkt soll die Linie enden (Format: \"X Y\", Beispiel: \"6 4\")? \n >>  ";
    std::cin >> nachX >> nachY;
    std::cout << "\n (?) Welchen Grauwert soll die Linie annehmen (0 bis " << (int) bild.maxGrauwert << ")? \n >>  ";
    std::cin >> intGrauwert;

    if (std::cin) {
        if (vonX < bild.anzahlSpalten && vonY < bild.anzahlZeilen && nachX < bild.anzahlSpalten && nachY < bild.anzahlZeilen && vonX >= 0 && vonY >= 0 && nachX >= 0 && nachY >= 0) {
            if (intGrauwert >= 0 && intGrauwert <= (int) bild.maxGrauwert) {
                grauwert = intGrauwert;
                if (bild.zeichneLinie (vonX, vonY, nachX, nachY, grauwert)) {
                    std::cout << "\n\n" << bild;
                } else {
                    std::cout << " \n (!) Linien dürfen nicht diagonal gezogen werden!" << std::endl;
                    bildZeichneLinie ();
                }
            } else {
                std::cout << " \n (!) Der Grauwert darf maximal " << (int) bild.maxGrauwert << " betragen!" << std::endl;
                bildZeichneLinie ();
            }
        } else {
            std::cout << " \n (!) Mindestens einer der Punkte befindet sich außerhalb des Bildbereichs!" << std::endl;
            bildZeichneLinie ();
        }
    } else {
        std::cout << " \n (!) Falsches Format!" << std::endl;
        std::cin.clear (); std::string muelleimer; getline (std::cin, muelleimer); // cin leeren
        bildZeichneLinie ();
    }

    bild.speichern (bild.name);
}


void bildZeichneRechteck () {
    int vonX, vonY, nachX, nachY;
    int intGrauwert;
    unsigned char grauwert;

    std::cout << "\n (?) An welchem Punkt soll sich die erste Ecke des Rechtecks befinden (Format: \"X Y\", Beispiel: \"3 1\")? \n >>  ";
    std::cin >> vonX >> vonY;
    std::cout << "\n (?) An welchem Punkt soll sich die entgegengesetze Ecke befinden (Format: \"X Y\", Beispiel: \"6 10\")? \n >>  ";
    std::cin >> nachX >> nachY;
    std::cout << "\n (?) Welchen Grauwert soll der Rand des Rechtecks annehmen (0 bis " << (int) bild.maxGrauwert << ")? \n >>  ";
    std::cin >> intGrauwert;
    
    if (std::cin) {
        if (vonX < bild.anzahlSpalten && vonY < bild.anzahlZeilen && nachX < bild.anzahlSpalten && nachY < bild.anzahlZeilen && vonX >= 0 && vonY >= 0 && nachX >= 0 && nachY >= 0) {
            if (intGrauwert >= 0 && intGrauwert <= (int) bild.maxGrauwert) {
                grauwert = intGrauwert;
                bild.zeichneRechteck (vonX, vonY, nachX, nachY, grauwert);
                std::cout << "\n\n" << bild;
            } else {
                std::cout << " \n (!) Der Grauwert darf maximal " << (int) bild.maxGrauwert << " betragen!" << std::endl;
                bildZeichneRechteck ();
            }
        } else {
            std::cout << " \n (!) Mindestens einer der Punkte befindet sich außerhalb des Bildbereichs!" << std::endl;
            bildZeichneRechteck ();
        }
    } else {
        std::cout << " \n (!) Falsches Format!" << std::endl;
        std::cin.clear (); std::string muelleimer; getline (std::cin, muelleimer); // cin leeren
        bildZeichneLinie ();
    }

    bild.speichern (bild.name);
}


void bildFehlerhaft () {
    std::cout << "\n (!) Die gewählte Datei ist fehlerhaft!" << std::endl;
}