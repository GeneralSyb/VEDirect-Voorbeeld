#include "VEDirect.h"

// 32-bit Integer (getal zonder decimalen) voor de State Of Charge (lading van accu), vermogen, voltage en stroom
int32_t VE_soc, VE_power, VE_voltage, VE_current;

// Bool (true of false) voor het alarm, niet echt nodig.
uint8_t VE_alarm;

// Variabele die gebruikt wordt om te communiceren met de BMV.
// In het example van de library wordt gebruik gemaakt van 'Serial3', maar op de ESP32 is dit 'Serial2'
VEDirect myve(Serial2);


// Alles tussen de haakjes van setup draait maar een keer. Je kunt hier wel een loop in plaatsen, maar dat is hier niet nodig.
void setup() {
  // De serial port starten bet een bitrate van 115200 bits per seconde.
  // Dit is nodig om gebruik te maken van de serial console in de arduino IDE.
  Serial.begin(115200);
}

// Alles binnen de haakjes van loop blijft lopen terwijl de microcontroller aan staat.
// Dus zodra hij klaar is met wat er binnen deze haakjes staat, begint hij weer gewoon bovenaan deze loop.
void loop() {
  // Checkt eerst of er een verbinding is
  if (myve.begin()) {
    // Er is een connectie.
    // Hier worden de variabelen geupdate met de waardes die klaarstaan.
    VE_soc = myve.read(VE_SOC);
    VE_power = myve.read(VE_POWER);
    VE_voltage = myve.read(VE_VOLTAGE);
    VE_current = myve.read(VE_CURRENT);
    VE_alarm = myve.read(VE_ALARM);     
  } else {
    // Er is geen connectie, dus wordt er in het serial console een error gegeven.
    Serial.println("Er is geen VE.Direct connectie.")
  }

  // Zet alle gemeten waardes in de serial console
  Serial.print("SOC: "); // print is zonder dat hij naar de volgende regel gaat aan het einde van de zin, println doet dat wel.
  Serial.println(VE_soc, DEC); // DEC betekent dat hij de variable 'vertaald' naar cijfers, omdat het eerst gewoon bytes zijn.

  Serial.print("Power: ");
  Serial.println(VE_power, DEC);

  Serial.print("Voltage: ");
  Serial.println(VE_voltage, DEC);

  Serial.print("Current");
  Serial.println(VE_current, DEC);

  Serial.print("Alarm: ");
  Serial.println(VE_alarm, DEC);

  Serial.println(); // witregel


  // Niet echt nodig, maar in het geval er data is die niet een eerdergebruikte label heeft, dan zit die hier tussen.
  Serial.println("Data dump:");
  myve.read(VE_DUMP);
  Serial.println(); // Witregel

  delay(10000); // wachten voor 10.000 ms, dus 10 seconden.
}
