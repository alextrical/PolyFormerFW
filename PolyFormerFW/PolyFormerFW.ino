#include "PolyFormerFW_menu.h"
const char pgmCommittedToRom[] PROGMEM = "Saved to ROM";
const char pgmTuning[] PROGMEM = "PID Tuning";

//Hardware Variables
#define baudrate        9600
#define REFERENCE_RESISTANCE   4700
#define NOMINAL_RESISTANCE     100000
#define NOMINAL_TEMPERATURE    25
#define B_VALUE                3950

//System Variables
int error = 0; //Start with a clean sheet and no error /* 0=no error; 1=Heater decoupled during rising; 2=Heater decoupled during hold; 10=Over Temp; 11=Thermistor short; 12=No thermistor */
bool runSystem = false;

//int stepperSpeed = ((stepperMicrosteps * motorStepsPerRevolution * gearboxRatio) / gearboxRadius) * spoolSpeed; //Steps per second. The fastest motor speed that can be reliably supported is about 4000 steps per second at a clock frequency of 16 MHz on Arduino such as Uno etc. Faster processors can support faster stepping speeds.
int stepperSpeed = 0;

//BlackPill
#define SDAPin          PB9
#define SCLPin          PB8
#define stepperStepPin  PB0
#define stepperDirPin   PB7
#define stepperEnPin    PB5
#define Thermistor1Pin  PA2
#define Heater1Pin      PA7
#define meltzoneFanPin  PA6


////EBB42 v1.1
//#define SDAPin          PB4
//#define SCLPin          PB3
//#define stepperStepPin  PD0
//#define stepperDirPin   PD1
//#define stepperEnPin    PD2


void setup() {
  // If you use i2c and serial devices, be sure to start wire / serial.
  Wire.setSDA(SDAPin); //BlackPill
  Wire.setSCL(SCLPin); //BlackPill
  Wire.begin();

  // here we initialise the EEPROM class to 512 bytes of storage
  // don't commit often to this, it's in FLASH
  //  EEPROM.begin(512);

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
  stepperLoop();
  fanLoop();
  pidLoop();
}


void CALLBACK_FUNCTION onSaveSettings(int id) {
  // TODO - your menu change code
  menuMgr.save();

  // here is a brief example of how to show a dialog, usually for information
  // or yes/no answers.
  auto* dlg = renderer.getDialog();
  if (dlg && !dlg->isInUse()) {
    dlg->setButtons(BTNTYPE_NONE, BTNTYPE_OK);
    dlg->show(pgmCommittedToRom, false);
    dlg->copyIntoBuffer("just so you know");
  }
}

void CALLBACK_FUNCTION onPIDTune(int id) {
  // TODO - your menu change code
//  pidTune();
}

void CALLBACK_FUNCTION onPIDChange(int id) {
  //apply PID gains
  pidChange();
}

void CALLBACK_FUNCTION onStart(int id) {
  // TODO - your menu change code
  //digitalWrite(stepperEnPin, LOW); //Low enables the stepper
  runSystem = !runSystem;

  if(runSystem){
  Serial.println("Run");
  }else{
  Serial.println("Stop");
  }
}

void CALLBACK_FUNCTION onGearboxChange(int id) {
  // TODO - your menu change code
  Serial.print("MotorSteps");
  Serial.println(menuMotorSteps.getAsFloatingPointValue());
  Serial.print("GearboxRatio");
  Serial.println(menuGearboxRatio.getAsFloatingPointValue());
  Serial.print("SpoolRadius");
  Serial.println(menuSpoolRadius.getAsFloatingPointValue());
  Serial.print("Microsteps");
  Serial.println(menuMicrosteps.getAsFloatingPointValue());
  stepperSpeed = menuMotorSteps.getAsFloatingPointValue()*menuFeed.getAsFloatingPointValue()*menuGearboxRatio.getAsFloatingPointValue()*menuMicrosteps.getAsFloatingPointValue();
  Serial.print("stepperSpeed");
  Serial.println(stepperSpeed);
  pwm_stepperStepPin(stepperSpeed);
}


void CALLBACK_FUNCTION onNameChanged(int id) {
  // TODO - your menu change code
}
