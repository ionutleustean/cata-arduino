
 /*
  This a simple example of the aREST Library for Arduino (Uno/Mega/Due/Teensy)
  using the Ethernet library (for example to be used with the Ethernet shield).
  See the README file for more details.
  Written in 2014 by Marco Schwartz under a GPL license.
*/

// Libraries
#include <SPI.h>
#include <Ethernet.h>
#include <aREST.h>
#include <avr/wdt.h>

int digitalPins[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

// Enter a MAC address for your controller below.
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xFE, 0x40 };

// IP address in case DHCP fails
IPAddress ip(192,168,1,177);

// Ethernet server
EthernetServer server(80);

// Create aREST instance
aREST rest = aREST();

// Variables to be exposed to the API
int temperature;
int humidity;

void setup(void)
{
  // Start Serial
  Serial.begin(115200); 

  rest.function("control", relayControl);

  // Give name & ID to the device (ID should be 6 characters long)
  rest.set_id("008");
  rest.set_name("dapper_drake");

  // Start the Ethernet connection and the server
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

  // Start watchdog
  wdt_enable(WDTO_4S);
}

void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  rest.handle(client);
  wdt_reset();

//pinul 6 buton porneste pinul 42
//pinul 7 buton porneste pinul 46
//pinul 5 buton porneste pinul 48
//pinul 3 buton porneste pinul 22

  toggleButton(6,42);
  toggleButton(7,46);
  toggleButton(5,48);
  toggleButton(3,22);

}

int relayControl(String command) {
  int pin = command.toInt();
  digitalPins[pin -1] = (digitalPins[pin -1] + 1 ) % 2;
  Serial.println(digitalPins[pin -1]);
  Serial.println(pin);
      pinMode(pin, OUTPUT);

  if(digitalPins[pin -1] == 1){
    Serial.println("high");
      digitalWrite(pin, HIGH);
  }
  else {
        Serial.println("low");
      digitalWrite(pin,LOW);
  }
  return 1;
}

void toggleButton(int button, int led) {
    int buttonState = digitalRead(button);

    if (buttonState == HIGH) {
      digitalWrite(led,  !digitalRead(led));  
    }
}
