#include <PID_v1.h>

//Decoupling
unsigned long decoupleTestPeriod = 1000; // Time in ms between setting and testing decoupling while heating.
unsigned long decoupleTestPeriodHeated = 1000; // Time in ms between setting and testing decoupling when fully heated.
#define decouplingTestMaxHoldVariance 20 //Max temperature fluctuation once the heater has reached its window
#define decouplingTestMinTempRise 0.5
#define preheatTimeCutoff 10000
unsigned long lastDecoupleTest;        // Last time of decoupling sensor-heater test
unsigned long preheatTime;        // Last time of decoupling sensor-heater test
double lastDecoupleTemp;

//Define Variables we'll be connecting to
double currentTemperatureC, Output;
int heating = 0; //0 - Off, 1 - Heating, 2 - stabilised
int extruderTempErrors = 0;
unsigned long PIDTime = 0;

//Specify the links and initial tuning parameters
PID heaterPID(&currentTemperatureC, &Output, &targetTemperatureC, Kp, Ki, Kd, P_ON_M, DIRECT);

void PIDSetup() {
  //turn the PID on
  currentTemperatureC = thermistor1->readCelsius();
  lastDecoupleTemp = currentTemperatureC;
  heaterPID.SetMode(AUTOMATIC);
}

void PIDLoop() {
  unsigned long time = millis();
  if (millis() > PIDTime) { //Run the temperature checks every 1/10th of a second
    currentTemperatureC = thermistor1->readCelsius();
    if (runSystem) {
      heaterPID.Compute();
      if (targetTemperatureC != extruderTemp)
      {
        targetTemperatureC = extruderTemp;
      }
    } else {
      Output = 0;
      targetTemperatureC = 0;
    }


    if (targetTemperatureC >= 20.0f && currentTemperatureC < targetTemperatureC - temperatureWindow && heating == 0 && error == 0) {
      heating = 1; //Temperature is rising to setpoint
      Serial.println("Heating");
      preheatTime = time;
    } else if (targetTemperatureC >= 20.0f && currentTemperatureC >= targetTemperatureC - temperatureWindow && heating != 2 && error == 0) {
      heating = 2; //temperature is cose to/at setpoint
      Serial.println("Reached setpoint");
    } else if ((targetTemperatureC < 20.0f || error != 0) && heating != 0) {
      heating = 0;
      Serial.println("Heater Off");
      targetTemperatureC = 0;
      runSystem = false;
    }


    //Safety checks to be done here
    // Check for obvious sensor errors
    if (targetTemperatureC > 0 /*is heating*/ ) {
      if (currentTemperatureC < heaterMinDefectTemp) {// no temp sensor , disable heater
        if (extruderTempErrors < 10) { // Ignore short temporary failures
          extruderTempErrors++;
          Serial.println ("E 12+");
        } else {
          error = 12; //12=No thermistor
        }
      } else if (currentTemperatureC > heaterMaxDefectTemp) {//short in sensor, disable heater
        if (extruderTempErrors < 10) { // Ignore short temporary failures
          extruderTempErrors++;
          Serial.println ("E 11+");
        } else {
          error = 11; //11=Thermistor short
        }
      } else   if (currentTemperatureC > heaterMaxTemp) {
        if (extruderTempErrors < 10) { // Ignore short temporary failures
          extruderTempErrors++;
          Serial.println ("E 10+");
        } else {
          error = 10; //10=Over Temp
        }
      }
    }



    // Run test if heater and sensor are decoupled
    bool decoupleTestRequired = !error && decoupleTestPeriod > 0 && (time - lastDecoupleTest) > decoupleTestPeriod && (time - preheatTime) > preheatTimeCutoff ; // time enough for temperature change?
    if (decoupleTestRequired && heating && runSystem) {                                                             // Only test when powered
      Serial.println("decoupleTestRequired");
//      if (heating == 1) {                                                                                           // Phase 1: Heating fully until target range is reached
//        if (currentTemperatureC - lastDecoupleTemp < decouplingTestMinTempRise) {                               // failed test
//          if (extruderTempErrors < 10) { // Ignore short temporary failures
//            extruderTempErrors++;
//            Serial.println ("E 1+");
//          } else {
//            Serial.print ("Error:Temp. raised too slow. Rise = ");
//            Serial.print (currentTemperatureC - lastDecoupleTemp);
//            Serial.print (" after ");
//            Serial.print (time - lastDecoupleTest);
//            Serial.println (" ms");
//            error = 1; //1=Heater decoupled during rising
//          }
//        }
//        lastDecoupleTest = time;
//      } else {                                                                                                      // Phase 2: Holding temperature inside a target corridor
//        if (fabs(currentTemperatureC - targetTemperatureC) > decouplingTestMaxHoldVariance) {                   // failed test
//          if (extruderTempErrors < 10) { // Ignore short temporary failures
//            extruderTempErrors++;
//            Serial.println ("E 2+");
//          } else {
//            Serial.print ("Error:Temp. raised to slow. Rise = ");
//            Serial.print (currentTemperatureC - lastDecoupleTemp);
//            Serial.print (" after ");
//            Serial.print (time - lastDecoupleTest);
//            Serial.println (" ms");
//            error = 2; //2=Heater decoupled during hold
//          }
//          lastDecoupleTest = time;
//        } else {
//          lastDecoupleTest = time - decoupleTestPeriod + decoupleTestPeriodHeated; // once running test every second
//        }
//      }
        lastDecoupleTemp = currentTemperatureC;
    }








    if (targetTemperatureC < 20.0f) { // heating is off
      digitalWrite(HeaterPin, LOW); // off is off, even if PID wants a heat peak!
    } else {
      if (error == 0) { //only run heater if there are no errors
        analogWrite(HeaterPin, Output); //Heat the heater only if no errors
      } else {
        digitalWrite(HeaterPin, LOW); //Dissable heater if any errors happen
        targetTemperatureC = 0;
        runSystem = false;
      }
    }

    PIDTime += 100;
  }
}
