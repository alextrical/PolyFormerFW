//Install the following libraries from the arduino Library manager
//TCMenu 2.3.1
//U8g2lib 2.33.15
//TMCStepper 0.7.3
//GyverNTC 1.2.0
//PID 1.2.0

//Add STM32Duino
//https://github.com/stm32duino/wiki/wiki/Getting-Started
//Use version 2.4.0 (If not available yet, use the main branch found here https://github.com/stm32duino/Arduino_Core_STM32), this adds support for the EBB42


#include "PolyFormerFW_menu.h"
#include "TMCStepper.h"           // TMCstepper - https://github.com/teemuatlut/TMCStepper 
#include "configuration.h"
const char pgmCommittedToRom[] PROGMEM = "Saved to ROM";
const char pgmCommittedToRomMessage[] PROGMEM = "just so you know";
const char pgmTuning[] PROGMEM = "Tuning PID";

//Hardware Variables
#define baudrate               9600
#define REFERENCE_RESISTANCE   4700
#define NOMINAL_RESISTANCE     100000
#define NOMINAL_TEMPERATURE    25
#define B_VALUE                4388 //104GT-2 alternative //4267 //104GT-2         //3950 //B3950

#define fwVersion              0.20

//System Variables
int error = 0; //Start with a clean sheet and no error /* 0=no error; 1=Heater decoupled during rising; 2=Heater decoupled during hold; 10=Over Temp; 11=Thermistor short; 12=No thermistor */
bool runSystem = false;
bool runMotor = false;
bool pidTuneRun = false;
double Setpoint;

// Polypen
// Variables will change:
int ledState = HIGH;        // the current state of the output pin
int buttonState;            // the current reading from the input pin
int lastButtonState = LOW;  // the previous reading from the input pin
// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


void setup() {
  // If you use i2c and serial devices, be sure to start wire / serial.
  Wire.setSDA(SDAPin);
  Wire.setSCL(SCLPin);
  Wire.begin();
  Wire.setClock(400000); //Optional - set I2C SCL to High Speed Mode of 400kHz

  // This is added by tcMenu Designer automatically during the first setup.
  setupMenu();

  // lastly we load state from EEPROM.
  menuMgr.load();
  serialSetup();
  stepperSetup();
  fanSetup();
  pidSetup();
}

void loop() {
  taskManager.runLoop();
  SerialLoop();
  fanLoop();
  //  // Run a loop until tuner.isFinished() returns true
  //  if (pidTuneRun) {
  //    pidTuneLoop();
  //  }else{
  pidLoop();
  //  }


  //Polypen magic
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonA);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only run the motor if the new button state is LOW
      if (buttonState == HIGH) {
        runMotor = false;
        stepperSppeed();
      } else {
        runMotor = true;
        stepperSppeed();
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;

}


void CALLBACK_FUNCTION onSaveSettings(int id) {
  menuMgr.save();

  // here is a brief example of how to show a dialog, usually for information
  // or yes/no answers.
  auto* dlg = renderer.getDialog();
  if (dlg && !dlg->isInUse()) {
    dlg->setButtons(BTNTYPE_NONE, BTNTYPE_OK);
    dlg->show(pgmCommittedToRom, false);
    dlg->copyIntoBuffer(pgmCommittedToRomMessage);
  }
}

void CALLBACK_FUNCTION onPIDTune(int id) {
  // TODO - your menu change code
  pidTune();
}

void CALLBACK_FUNCTION onStart(int id) {
  runSystem = !runSystem;
  stepperSppeed();
}

void CALLBACK_FUNCTION onGearboxChange(int id) {
  stepperSppeed();
}


void CALLBACK_FUNCTION onNameChanged(int id) {
  // TODO - your menu change code
}



void CALLBACK_FUNCTION onMotorCurrent(int id) {
  stepperCurrent();
}


void CALLBACK_FUNCTION onPidChange(int id) {
  pidChange();
}


void CALLBACK_FUNCTION onTemperatureChange(int id) {
  Setpoint = menuTemperature.getAsFloatingPointValue();
}
