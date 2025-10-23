## Aufgabenblock 1 – To-Do / Checkliste

### **Projekt Setup**

* [ ] Neues Eclipse-Projekt **„Aufgabenblock 1“** erstellen
* [ ] C++-Dialekt auf **C++17** umstellen
* [ ] Testkompilierung sicherstellen

---

### **4.2 Fahrzeuge (Einfache Klassen)**

#### Grundklasse Fahrzeug

* [ ] Klasse `Fahrzeug` anlegen
* [ ] **Private Member:**

  * [ ] `psName` (string)
  * [ ] `piID` (const int)
  * [ ] `static int piMaxID` (hochzählend)
* [ ] Konstruktoren:

  * [ ] Default-Konstruktor → leerer Name, ID automatisch
  * [ ] Konstruktor mit `string` → Name setzen, ID automatisch
* [ ] **Destruktor** mit `cout`-Ausgabe
* [ ] **Ausgaben** im Konstruktor/Destruktor (Name + ID)
* [ ] Alles was geht als `const` markieren

#### Test / main.cpp

* [ ] Funktion `vAufgabe1()` schreiben
* [ ] Einige Fahrzeuge **statisch** und **dynamisch (`new`)** erzeugen
* [ ] Dynamische wieder **löschen**
* [ ] Danach **Smartpointer-Tests**:

  * [ ] `make_unique` und `make_shared` für `Fahrzeug`
  * [ ] `use_count` vorher/nachher ausgeben
  * [ ] `vector<unique_ptr<Fahrzeug>>` testen
  * [ ] `vector<shared_ptr<Fahrzeug>>` testen
  * [ ] Debugger verwenden → beobachten, wann Destruktoren feuern

#### Erweiterung Fahrzeug

* [ ] Member hinzufügen:

  * [ ] `pdMaxGeschwindigkeit`, `pdGesamtStrecke`, `pdGesamtZeit`, `pdZeit`
* [ ] Neuer Konstruktor (Name + MaxGeschwindigkeit)

  * [ ] Geschwindigkeit > 0 mit `?:`-Operator prüfen
* [ ] `vAusgeben()` → Daten ausgeben, aber kein `endl`
* [ ] `vKopf()` (static) → Überschrift drucken

  * [ ] Mit `<iomanip>` formatieren (`setw`, `setprecision`, `setiosflags`)

#### Simulation

* [ ] Globale Variable `double dGlobaleZeit = 0.0;`

  * [ ] In Klassen per `extern` bekannt machen
* [ ] `vSimulieren()`:

  * [ ] Zeitdifferenz berechnen (`dGlobaleZeit - pdZeit`)
  * [ ] Strecke & Gesamtzeit aktualisieren
  * [ ] `pdZeit` neu setzen
  * [ ] Doppelaufrufe in gleichem Zeittakt verhindern
* [ ] `vAufgabe1a()`:

  * [ ] Namen & MaxSpeed für 3 Fahrzeuge einlesen
  * [ ] Mit `make_unique` in `vector` speichern
  * [ ] Globale Zeit in Schleife hochzählen
  * [ ] In jedem Schritt → `vSimulieren()` + `vAusgeben()`

---

### **4.3 Fahrräder & PKW (Vererbung)**

* [ ] Klassen `PKW` und `Fahrrad` von `Fahrzeug` ableiten
* [ ] `Fahrzeug` aufteilen:

  * [ ] private → nur intern
  * [ ] protected → für abgeleitete nutzbar
  * [ ] virtuelle Methoden vorbereiten (`virtual`, `override`)
* [ ] `PKW`:

  * [ ] Neue Member: `pdVerbrauch`, `pdTankvolumen`, `pdTankinhalt`
  * [ ] Konstruktor mit Verbrauch + (optional 55 l Tankvolumen)
  * [ ] Tank = halbes Tankvolumen
  * [ ] Funktion `dTanken(double dMenge = inf)`:

    * [ ] Kein Wert → volltanken
    * [ ] Nicht über Tankvolumen hinaus
    * [ ] Rückgabe = tatsächlich getankt
  * [ ] `vSimulieren()` überschreiben:

    * [ ] Verbrauch, Tankinhalt aktualisieren
    * [ ] Stehenbleiben bei leerem Tank
* [ ] `vAusgeben()` in PKW erweitern (Verbrauch, Tankinhalt)

  * [ ] Basisklassen-`vAusgeben()` aufrufen
  * [ ] `vKopf()` um Spalten erweitern
* [ ] `Fahrrad`:

  * [ ] `dGeschwindigkeit()` überschreiben:

    * [ ] Alle 20 km → –10 %
    * [ ] min. 12 km/h
  * [ ] `Fahrzeug::vSimulieren()` nutzt jetzt `dGeschwindigkeit()`
  * [ ] `vAusgeben()` → aktuelle Geschwindigkeit

#### Test

* [ ] `vAufgabe2()`:

  * [ ] Anzahl PKW/Fahrräder einlesen
  * [ ] `vector<unique_ptr<Fahrzeug>>`
  * [ ] Fahrzeuge simulieren (Zeitschritte)
  * [ ] Nach 3 Stunden PKWs volltanken
  * [ ] Ausgaben nach jedem Schritt
  * [ ] `fabs()` + ϵ bei double-Vergleichen

---

### **4.4 Operatoren überladen**

* [ ] `vAusgeben(ostream&) const` → virtuell machen
* [ ] `operator<<` außerhalb der Klasse definieren:

  ```cpp
  ostream& operator<<(ostream& os, const Fahrzeug& f);
  ```

  * [ ] Ruft `f.vAusgeben(os)` auf
  * [ ] Eine Definition für alle Klassen (Polymorphie)
* [ ] Test: `cout << *aPKW << endl;`
* [ ] `operator<` in `Fahrzeug`:

  * [ ] vergleicht `pdGesamtStrecke`
* [ ] Copy-Konstruktor `= delete`
* [ ] Zuweisungsoperator `operator=()`:

  * [ ] Nur Stammdaten (Name, MaxSpeed) kopieren
  * [ ] ID nicht duplizieren
* [ ] `vAufgabe3()`:

  * [ ] Alle Operatoren testen

---
