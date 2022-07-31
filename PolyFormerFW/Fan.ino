#include <Thermistor.h>
#include <NTC_Thermistor.h>
bool fan1 = false; //Keep track of the fan state

#define ANALOG_RESOLUTION 65535 //16 Bit resolution, this can be higher than your MCU supports, and will adjust accordingly
double targetTemperatureC;

Thermistor* thermistor1;

void thermistorSetup() {
  thermistor1 = new NTC_Thermistor(
    Thermistor1Pin,
    REFERENCE_RESISTANCE,
    NOMINAL_RESISTANCE,
    NOMINAL_TEMPERATURE,
    B_VALUE,
    ANALOG_RESOLUTION // <- for a thermistor ADC resolution adjustment
  );
};

void fanSetup() {
  analogReadResolution(16); //Set Resolution of ADC to 16 bit, this will pad any lower resolution values, giving us future flexability
  pinMode(meltzoneFanPin, OUTPUT);
};

void fanLoop() {
  if (error == 0) {
    if ((thermistor1->readCelsius()) >= meltzoneFanTemp || targetTemperatureC >= meltzoneFanTemp )
    {
      analogWrite(meltzoneFanPin, meltzoneFanSpeed * 2.55);
      fan1 = true;
    } else {
      digitalWrite(meltzoneFanPin, LOW);
      fan1 = false;
    }
  } else {
    digitalWrite(meltzoneFanPin, HIGH); //Error detected, run fan at full power.
      fan1 = true;
  }

};
