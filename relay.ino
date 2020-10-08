#include <OneWire.h>
#include <DallasTemperature.h>
#include <TM1637Display.h>

#define CLK 2
#define DIO 3

TM1637Display display(CLK, DIO);

// Pin relay
int relayPin = 7;

// Max and Min Temperatures
float maxTemp = 30.00;
float minTemp = 25.55;

//Pin donde esta conectado dq
const byte pinDatosDQ = 9;


// Instancia a las clases OneWire y DallasTemperature
OneWire ourWire (pinDatosDQ);
DallasTemperature sensor (&ourWire);

void setup() {
  display.setBrightness(7);
  // Iniciamos la comunicacion serie
  Serial.begin(9600);
  //Iniciamos el bus 1-Wire
  sensor.begin();
  // Iniciamos relay
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
}

void loop() {
  float temp1 = sensor.getTempCByIndex(0);
  sensor.requestTemperatures();
    if (temp1 >= maxTemp) {
       powerOnRelay();
    } else if(temp1 <= minTemp) {
      powerOffRelay();
    }

    delay(1000);
  
  Serial.print (sensor.getTempCByIndex(0));
  Serial.println("Grados Centigrados");
  display.showNumberDecEx(temp1,64, false);
}

void powerOnRelay() {
  digitalWrite(relayPin, HIGH);
  Serial.println("RelayOn");
}

void powerOffRelay() {
  digitalWrite(relayPin, LOW);
  Serial.println("RelayOFF");
}

//int relayPin = 7;
//
//float maxTemperature = 27.55;
//float minTemperature = 25.55;
//
//void setup() {
//  Serial.begin(9600);
//  pinMode(relayPin, OUTPUT);
//
//}
//
//void loop() {
////  powerOnRelay();
//Serial.println("asd");
//}
//
//void powerOnRelay() {
//  digitalWrite(relayPin, HIGH);
//  Serial.println("RelayOn");
//  delay(2000);
//  digitalWrite(relayPin, LOW);
//  Serial.println("Relay OFF");
//}
