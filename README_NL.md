# 1-DOF Robotarm Gebruikershandleiding

Welkom! Deze handleiding legt uit hoe je de 1-DOF (vrijheidsgraden) robotarm bedient met seriële commando's.

## Verbinden met de Robotarm

1.  Verbind de robotarm met je computer via de meegeleverde USB-kabel.
2.  Open een seriële monitor applicatie (bijv. de Arduino IDE Seriële Monitor, PuTTY, of PlatformIO's Seriële Monitor).
3.  Stel de verbinding in met de volgende instellingen:
    *   **Poort**: De COM- of TTY-poort toegewezen aan de robotarm.
    *   **Baudrate**: `115200`
    *   **Regelafsluiting**: Newline (`\n`)

Na het verbinden begroet de robotarm je met een welkomstbericht.

## Bediening Commando's

Om de arm te bedienen, stuur je een van de volgende commando's via de seriële monitor, gevolgd door Enter.

### 1. Ga naar Positie

Beweegt de arm direct naar een specifieke hoek.

*   **Commando**: `P<hoek>`
*   **`<hoek>`**: Een geheel getal dat de doelhoek aangeeft (van 0 tot 180).
*   **Voorbeeld**: `P90` - Dit commando zet de arm op de 90-graden positie.

### 2. Ga naar Positie in Tijd

Beweegt de arm soepel naar een doelhoek over een opgegeven tijdsduur.

*   **Commando**: `T<hoek>,<duur>`
*   **`<hoek>`**: De doelhoek (0-180).
*   **`<duur>`**: De tijd voor de beweging in milliseconden (bijv. 1000ms = 1 seconde).
*   **Voorbeeld**: `T180,2000` - Dit commando beweegt de arm naar 180 graden over een periode van 2 seconden.

## Begrijpen van Feedbackberichten

De robotarm geeft realtime feedback over zijn status. Elk bericht heeft een prefix die het type aangeeft:

*   **`[INFO]`**: Geeft algemene informatie, zoals wanneer een beweging begint.
    *   *Voorbeeld*: `[INFO] Start beweging van 90 naar 180 in 2000ms`

*   **`[SUCCESS]`**: Bevestigt dat een commando succesvol is uitgevoerd.
    *   *Voorbeeld*: `[SUCCESS] Beweging voltooid.`
    *   *Voorbeeld*: `[SUCCESS] Naar positie bewogen: 90`

*   **`[ERROR]`**: Verschijnt als je een ongeldig of onbekend commando stuurt.
    *   *Voorbeeld*: `[ERROR] Onbekend commando: X123`
    *   *Voorbeeld*: `[ERROR] Ongeldig formaat. Gebruik T<hoek>,<tijd>`

