/* Ejercicio entregable 101
 Deben de utilizar este archivo los alumnos con c>=5, d<5, u>=5
 siendo c, d y u las tres últimas cifras del DNI 22000cdu -W
 Sensor de temperatura y motor paso a paso con potenciometro
 Para cambiar la temperatura haz click sobre el anemometro durante la simulacion
 rellenar vuestro nombre y DNI
 NOMBRE ALUMNO: XXXXX
 DNI: XXXXX
 ENLACE WOKWI: XXXXXXXXXXX
*/

#include <Stepper.h>
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

Stepper myStepper(200, 14, 27, 26, 25);

const int potPin = 34; // Pin del potenciometro
const int tempPin = 4; // Pin de datos del DS18B20 (OneWire)

OneWire oneWire(tempPin);
DallasTemperature sensors(&oneWire);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  myStepper.setSpeed(10);
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

    Serial.print(analogRead(potPin));
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

    Serial.print(analogRead(potPin));
    Serial.print(", ");
    Serial.println(tempC);
  }
}
