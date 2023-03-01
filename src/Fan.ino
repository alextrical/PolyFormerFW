//Measure NTC value
float lastT = 19.68;

// ~~~~~~ A,B,C ~~~~~~
#define TA1 7.97110609710217e-4 //104GT-2
#define TB1 2.13433144381270e-4 //104GT-2
#define TC1 6.5338987554e-8     //104GT-2


bool fan1 = false; //Keep track of the fan state

#define meltzoneFanTemp 40 //Temperature the fan will kick in at
double targetTemperatureC = 0;
double celsius;

// TPin = Analog Pin 
// R1 = R Serries resistor
// A, B , C = the Steinhart–Hart coefficients, which vary depending on the type and model of thermistor and the temperature range of interest.
float f_ReadTemp_ThABC(byte TPin, float R1, float A, float B, float C) {

	float R2 = R1 / ((1023.0 / analogRead(TPin)) - 1);             // for pull-up configuration
	
	float logR2 = log(R2);           // Pre-Calcul for Log(R2)
	float T = (1.0 / (A + B*logR2 + C*logR2*logR2*logR2)); 
	T =  T - 273.15;             // convert Kelvin to *C
	return T;
}


void thermistorSetup() {
};

void fanSetup() {
  analogReadResolution(10); //Set Resolution of ADC to 10 bit, this will pad any lower resolution values, giving us future flexability
  pinMode(meltzoneFanPin, OUTPUT);
};

void fanLoop() {
  if (error == 0) {
    if (f_ReadTemp_ThABC(thermistorPin, REFERENCE_RESISTANCE, TA1, TB1, TC1) >= meltzoneFanTemp /*|| targetTemperatureC >= meltzoneFanTemp*/ )
    {
      analogWrite(meltzoneFanPin, menuFan.getAsFloatingPointValue() * 2.55);
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
