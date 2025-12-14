/* Ejercicio entregable 100
 Deben de utilizar este archivo los alumnos con c<5, d<5, u>=5
 siendo c,d,u las tres últimas cifras del DNI 22000cdu -W
Temperatura y motor paso a paso con encoder
 Para cambiar la Temperatura o haz click sobre el sensor DS18B20 durante la simulacion
 rellenar vuestro nombre y DNI
 NOMBRE ALUMNO: XXXXX
 DNI: XXXXX
 ENLACE WOKWI: XXXXXXX
*/
#include <Stepper.h>
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

Stepper myStepper(200, 14, 27, 26, 25);

const int encAPin = 23; // Pin para el canal A del encoder
const int encBPin = 22; // Pin para el canal B del encoder
const int encCPin = 16; // Pin para el canal C del encoder
const int encDPin = 15; // Pin para el canal D del encoder
const int tempPin = 4;  // Pin de datos del DS18B20 (OneWire)

OneWire oneWire(tempPin);
DallasTemperature sensors(&oneWire);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  myStepper.setSpeed(10);
  pinMode(encAPin, INPUT);
  pinMode(encBPin, INPUT);
  pinMode(encCPin, INPUT);
  pinMode(encDPin, INPUT);
  sensors.begin();
}

void loop()
{
  // put your main code here, to run repeatedly:
  // Avanza de 0 a 100 en pasos de 20 y muestra lecturas en cada punto
  for (int pos = 0; pos <= 100; pos += 20)
  {
    myStepper.step(20);
    delay(200);

    sensors.requestTemperatures();
    const float tempC = sensors.getTempCByIndex(0);

    Serial.print(digitalRead(encAPin));
    Serial.print(", ");
    Serial.print(digitalRead(encBPin));
    Serial.print(", ");
    Serial.print(digitalRead(encCPin));
    Serial.print(", ");
    Serial.print(digitalRead(encDPin));
    Serial.print(", ");
    Serial.println(tempC);
  }

  // Retrocede de 100 a 0 en pasos de 20 y muestra lecturas en cada punto
  for (int pos = 100; pos >= 0; pos -= 20)
  {
    myStepper.step(-20);
    delay(200);

    sensors.requestTemperatures();
    const float tempC = sensors.getTempCByIndex(0);

    Serial.print(digitalRead(encAPin));
    Serial.print(", ");
    Serial.print(digitalRead(encBPin));
    Serial.print(", ");
    Serial.print(digitalRead(encCPin));
    Serial.print(", ");
    Serial.print(digitalRead(encDPin));
    Serial.print(", ");
    Serial.println(tempC);
  }
}
