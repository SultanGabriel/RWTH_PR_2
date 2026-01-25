Klar ✅ hier ist eine **saubere Abhak-Checkliste** für **Aufgabenblock 3 – 6.2 Überholverbot (Simulation Verkehrssystem)**, damit du **systematisch prüfen kannst**, ob dein Code wirklich alles erfüllt und du safe weiter machen kannst.

---

# ✅ Checkliste: AB3 – 6.2 Überholverbot (Simulation Verkehrssystem)

## 1) Grundidee verstanden (Soll-Verhalten)

* [ ] Auf einem **Weg mit Überholverbot** darf **kein Fahrzeug ein anderes überholen**
* [ ] Fahrzeuge bleiben in **fester Reihenfolge** wie sie auf den Weg gekommen sind
* [ ] Wenn ein Fahrzeug vorne langsamer ist → das hintere muss sich **anpassen** (nicht vorbeiziehen)
* [ ] Es gibt **keine Positionsüberschneidung** / kein “durchspringen” in der Simulation

---

## 2) Datenstruktur / Reihenfolge bleibt stabil

* [ ] Deine Fahrzeugliste am Weg (z. B. `list<unique_ptr<Fahrzeug>>`) bleibt **in Einfüge-Reihenfolge**
* [ ] Beim Simulieren wird die Liste **nicht sortiert** (wichtig!)
* [ ] Beim Einfügen neuer Fahrzeuge:

  * [ ] kommen sie **hinten dran** (nicht irgendwo mitten rein)

---

## 3) Bewegungsberechnung: Kein “nach vorne springen”

Beim Updaten der Strecke (`dGlobaleZeit` / `dt`) gilt:

* [ ] Für jedes Fahrzeug wird die neue Position berechnet
* [ ] ABER: neue Position darf **nicht größer sein als die Position des Vordermanns**
* [ ] Hinteres Fahrzeug bekommt ggf. eine **gekappte Distanz** (Clamp)

💡 typische Regel:

* [ ] `s_neu_hinten <= s_vorne - sicherheitsabstand` *(oder zumindest <= s_vorne)*

---

## 4) Sicherheitsabstand / “Kleben vermeiden”

Je nach Aufgabenstellung:

* [ ] Fahrzeuge dürfen nicht exakt **identisch** stehen (sieht buggy aus)
* [ ] Es gibt entweder:

  * [ ] einen kleinen Abstand (z. B. `0.001`)
  * [ ] oder du setzt es sauber mit “min(… , vorne - epsilon)”

---

## 5) Sonderfälle sauber behandelt

* [ ] Wenn das vordere Fahrzeug **am Ende des Weges ankommt** → was passiert mit dem dahinter?

  * [ ] fährt korrekt nach bis zum Limit
  * [ ] springt nicht drüber hinaus
* [ ] Wenn das vordere Fahrzeug **steht** (v=0) → das hintere fährt auch nicht vorbei
* [ ] Wenn Fahrzeuge **gleich schnell** sind → bleibt die Reihenfolge trotzdem stabil
* [ ] Wenn hinten schneller ist → wird es **gebremst / gekappt**, nicht überholt

---

## 6) Einfahrlogik / Ankunftslogik (kritisch!)

* [ ] Fahrzeuge werden korrekt in den Weg aufgenommen
* [ ] Beim Entfernen / Weiterleiten (falls vorhanden):

  * [ ] Reihenfolge bleibt korrekt
  * [ ] kein Fahrzeug “überspringt” beim Entfernen einen anderen

---

## 7) Konsolen-Ausgabe / Debug-Hebel vorhanden (Gamechanger)

Damit du direkt siehst ob’s stimmt:

* [ ] Du kannst pro Weg printen:

  * [ ] Reihenfolge der Fahrzeuge
  * [ ] Position `s`
  * [ ] Geschwindigkeit `v`
* [ ] Nach jedem Zeitschritt erkennst du sofort:

  * [ ] hintere Fahrzeuge werden “gedeckelt”
  * [ ] kein Fahrzeug taucht plötzlich vor einem anderen auf

✅ Mini-Debugformat Idee:

* [ ] `Weg X: [AutoA s=..., AutoB s=..., ...]` in Reihenfolge

---

## 8) Testfälle (wenn die bestehen → du bist durch)

Mach diese 3 Tests — wenn alle passen, bist du fertig:

### Test A: Schnelles Auto hinter langsamem

* [ ] vorne: v=30
* [ ] hinten: v=120
  ➡️ hinten darf **niemals** die Position des vorderen übersteigen

### Test B: 3 Fahrzeuge in Kette

* [ ] v1 langsam, v2 schnell, v3 schneller
  ➡️ alle bleiben sauber in Reihenfolge ohne “Shuffle”

### Test C: Neues Fahrzeug kommt rein

* [ ] während Simulation neues Auto hinzufügen
  ➡️ es startet hinten und bleibt hinten

---

## 9) Häufige Fehler (wenn einer zutrifft → nochmal fixen)

* [ ] Du sortierst Fahrzeuge nach `s` → **NEIN** (macht Überholverbot kaputt)
* [ ] Du rechnest jedes Fahrzeug unabhängig ohne Bezug zum Vordermann → führt zu Überholen
* [ ] Du entfernst Fahrzeuge aus der Liste während du drüber iterierst (ohne Sicherung)
* [ ] Du nutzt “int” statt “double” für Positionen → Sprünge / Clipping Fehler

---

# ✅ End-Check (1 Satz Wahrheitstest)

Wenn du nach jedem Sim-Schritt sagen kannst:

> “Kein Fahrzeug hat den Vordermann überholt, die Reihenfolge ist stabil und hinten passt sich an.”

➡️ dann ist **6.2 Überholverbot** in deinem Code **sauber erledigt** ✅

---

Wenn du willst, schick mir **deine Weg-Simulationsfunktion** (die Schleife, wo Fahrzeuge bewegt werden), dann markier ich dir **genau die 3-5 Stellen**, wo man das Überholverbot clean enforced — minimal und RWTH-safe.

