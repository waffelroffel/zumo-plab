<b>//TODO</b>
- Logikk for å finne tilbake til midten etter e.g. attack-state
- Logikk for manuvrering når robotten treffer ytre linje
- PID-reg. for ultralyd-sensor for attack-state
- Logikk for acceleramoter (er motorkraft det eneste som flytter på robotten?)
- Programflyt og void loop() struktur

<b>AVTALTE FUNKSJONER OG GLOBALE VARIABLER:</b>

<b>FUKSJONER: </b>
void updateSpeeds(int left, int right); // setter motorkraft, og endrer globale var

<b>GLOBALE-VARIABLER:</b>
// current hastighet på høyre og venstre motor (endres kun av updateSpeeds)
int right_speed;
int right_speed;
