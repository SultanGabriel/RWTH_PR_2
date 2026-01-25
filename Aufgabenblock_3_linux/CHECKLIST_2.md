Natürlich ✅ hier kommt deine **Abhak-Checkliste für 6.3 Aufbau des Verkehrssystems** – im gleichen Stil wie davor, damit du stumpf durchgehen kannst und weißt: **alles erledigt → weiter geht’s.**

---

# ✅ Checkliste: AB3 – 6.3 Aufbau des Verkehrssystems

## 1) Ziel der Aufgabe erfüllt (Netzwerk statt Einzelweg)

* [ ] Ich habe **mehr als einen Weg** im System
* [ ] Ich habe **mehr als eine Kreuzung** im System
* [ ] Wege sind **über Kreuzungen verbunden**
* [ ] Fahrzeuge können **von Weg zu Weg wechseln** (nicht nur auf 1 Weg sterben)

---

## 2) Architektur / Ownership sauber gelöst (Pointer-Hölle vermeiden)

* [ ] **Simulation / main besitzt** die Kreuzungen (z. B. `unique_ptr<Kreuzung>`)
* [ ] Wege werden **nur an einer Stelle erzeugt** (nicht doppelt / nicht kopiert)
* [ ] Kreuzungen speichern ausgehende Wege nur als **Referenz / Pointer** (kein Besitz-Durcheinander)
* [ ] Fahrzeuge liegen **in genau einer Liste gleichzeitig**
* [ ] Fahrzeug-Transfers passieren mit `std::move(...)` (kein Copy)

---

## 3) Wege korrekt verbunden (Graph-Logik passt)

Für jeden Weg gilt:

* [ ] Weg hat **Start-Kreuzung**
* [ ] Weg hat **Ziel-Kreuzung**
* [ ] Weg ist **bei der Start-Kreuzung als “ausgehend” registriert**
* [ ] Wenn Rückrichtung gewünscht → **extra Weg** (AB != BA)

---

## 4) Simulation tickt global korrekt (richtige Reihenfolge pro Zeitschritt)

* [ ] Ich habe einen globalen Tick / Zeitfortschritt (`dGlobaleZeit`, `dt`)
* [ ] Pro Tick werden **alle Wege simuliert**
* [ ] Danach werden Transfers / Kreuzungslogik verarbeitet
  (Wichtig: nicht mitten im Weg-Loop)

✅ Good Reihenfolge:

* [ ] 1) `Weg::vSimulieren()` für alle Wege
* [ ] 2) `Kreuzung::vWeiterleiten()` / Transfers durchführen
* [ ] 3) Ausgabe / Debug

---

## 5) Ankunft am Wegende sauber erkannt

* [ ] Jedes Fahrzeug kann erkennen: **“ich bin am Ende des Weges”**
* [ ] Beim Erreichen des Endes wird es **aus der Weg-Liste entfernt**
* [ ] Es wird an die **Ziel-Kreuzung übergeben** (nicht gelöscht / nicht vergessen)

⚠️ Fail-Indikator:

* [ ] Fahrzeuge bleiben am Wegende “kleben” und bewegen sich weiter ins Nirvana

---

## 6) Transfer-Mechanik bugfrei (Iterator-safe)

* [ ] Ich verändere **keine Fahrzeugliste während ich sie iteriere**
* [ ] Ich nutze eine **Transfer-/Pufferliste**

  * [ ] z. B. `Weg::pAbgaben()` / `list<unique_ptr<Fahrzeug>>`
* [ ] Fahrzeuge werden erst nach dem Simulieren wirklich umgehängt

---

## 7) Kreuzung routet Fahrzeuge weiter (nächster Weg wird gewählt)

* [ ] Kreuzung hat eine Liste der **ausgehenden Wege**
* [ ] Kreuzung wählt für jedes ankommende Fahrzeug einen **Folgeweg**
* [ ] Fahrzeug wird dort mit `Weg::vAnnahme(...)` aufgenommen

✅ Routing-Logik vorhanden (egal wie simpel):

* [ ] “nimm ersten Weg”
* [ ] “random outgoing”
* [ ] “round-robin”
  *(Hauptsache: reproduzierbar & funktioniert)*

---

## 8) Annahme auf neuen Wegen korrekt

* [ ] Fahrzeug startet auf dem neuen Weg mit sinnvoller Startposition (meist `s=0`)
* [ ] Fahrzeug wird hinten in die Wegliste eingefügt (Überholverbot bleibt korrekt)
* [ ] Bei direkt vollem Weg/Edgecases: Verhalten ist definiert (notfalls trotzdem hinten)

---

## 9) Sonderfälle / Stabilität

* [ ] Kreuzung hat **keine ausgehenden Wege** → Fahrzeug verschwindet / stoppt sauber (keine Crashes)
* [ ] Mehrere Fahrzeuge kommen im selben Tick an → alle werden korrekt verarbeitet
* [ ] Es gibt kein “doppeltes Auto” (nicht auf 2 Wegen gleichzeitig)
* [ ] Reihenfolge bleibt stabil (6.2 Überholverbot wird nicht kaputt gemacht)

---

## 10) Debug-Ausgabe vorhanden (damit du’s sofort siehst)

* [ ] Ich kann ausgeben, welche Fahrzeuge auf welchem Weg sind
* [ ] Ich sehe beim Tick, wenn Fahrzeuge wechseln:

  * [ ] “Fahrzeug X verlässt Weg A → Kreuzung B → nimmt Weg C”
* [ ] Ich erkenne schnell, ob Fahrzeuge verschwinden oder dupliziert werden

---

# ✅ Funktioniert-Test (3 Checks, wenn die grün sind → 6.3 done)

### Test A: Minimalnetz (2 Kreuzungen, 1 Weg)

* [ ] Fahrzeug fährt A→B, kommt an, wird korrekt übergeben
* [ ] Kein Crash, kein Kleben

### Test B: 3 Kreuzungen (A→B→C)

* [ ] Fahrzeug fährt über mehrere Wege weiter
* [ ] Routing an B funktioniert

### Test C: 2 Fahrzeuge hintereinander

* [ ] Beide wechseln sauber den Weg
* [ ] Reihenfolge bleibt korrekt (hinten bleibt hinten)

---

# ✅ End-Check (wenn du DAS sagen kannst → weiter zu 6.4)

> „Meine Simulation besteht aus Kreuzungen und Wegen, Fahrzeuge wechseln am Wegende korrekt zur nächsten Kreuzung und werden auf einen Folgeweg übernommen – ohne Überholen, ohne doppelte Ownership, ohne Iterator-Crash.“

✅ Dann bist du durch.

---

Wenn du willst, kann ich dir als nächstes eine **Mini-Referenz-Struktur** geben (welche Methoden in `Weg`, `Kreuzung`, `Simulation` minimal nötig sind), komplett RWTH-clean und ohne Overengineering.

