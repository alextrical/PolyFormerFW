/* PolyFormer Firmware early alpha test

   Designed by Alextrical, helped by the community

   Libraries used:
   AccelStepper             http://www.airspayce.com/mikem/arduino/AccelStepper/
   Adafruit GFX Library     https://github.com/adafruit/Adafruit-GFX-Library
   Adafruit SSD1306         https://github.com/adafruit/Adafruit_SSD1306
   Bounce2                  https://github.com/thomasfredericks/Bounce2
   NTC_Thermistor           https://github.com/YuriiSalimov/NTC_Thermistor
   PID                      https://github.com/br3ttb/Arduino-PID-Library
   Wire                     https://github.com/arduino/ArduinoCore-avr/tree/master/libraries/Wire

   Planned to use
   EEPROM
   STM32Encoder
   sTune
*/


//User set variables here
#define pfSerial          999 //Set the serial number here

//Hardware Variables
#define baudrate        9600
#define displayRotation 2 //0:Landscape, 2:Landscape 180

////BlackPill
//#define Thermistor1Pin  PA2
//#define HeaterPin       PA7
//#define stepperStepPin  PB0
//#define stepperDirPin   PB7
//#define stepperEnPin    PB5
//#define meltzoneFanPin  PA6
//#define SDAPin          PB9
//#define SCLPin          PB8
//#define buttonPin       PB12
#define stepperDirInvert false
#define stepperStepInvert false
#define stepperEnInvert true

//EBB42 v1.1
#define Thermistor1Pin  PA3
#define HeaterPin       PA2
#define meltzoneFanPin  PA0
#define stepperStepPin  PD0
#define stepperDirPin   PD1
#define stepperEnPin    PD2
#define SDAPin          PB4
#define SCLPin          PB3
#define buttonPin       PA14
#define stepperDirInvert false
#define stepperStepInvert false
#define stepperEnInvert false

//EBB42 v1.0
//#define Thermistor1Pin
//#define HeaterPin
//#define meltzoneFanPin
//#define stepperStepPin
//#define stepperDirPin
//#define stepperEnPin
//#define SDAPin
//#define SCLPin
//#define buttonPin

//Hotend tuning, and Thermistor config
//  float Kp; ///< Pgain (proportional gain) for PID temperature control
//                  ///< [0,01 Units].
//  float Ki; ///< Igain (integral) for PID temperature control [0,01 Units].
//  float Kd; ///< Dgain (damping) for PID temperature control [0,01 Units].
double Kp = 9.96, Ki = 0.36, Kd = 0;
#define REFERENCE_RESISTANCE   4700
#define NOMINAL_RESISTANCE     100000
#define NOMINAL_TEMPERATURE    25
#define B_VALUE                3950

double extruderTemp = 200; //Temperature for Hotend
#define meltzoneFanTemp 40 //Temperature the fan will kick in at
#define meltzoneFanSpeed 100 //Maximum percentage to run the fan at 0-100%
#define temperatureWindow 5 //+- Temperature control window that we are stable inside of

#define stepperMicrosteps 16 //Assuming we are using a TMC2208
#define motorStepsPerRevolution 200
#define gearboxRatio 29 //:1
#define gearboxRadius 320 //Radius of the filament spool
//int outputRPM = 54;
int spoolSpeed = 10; //mm/s
bool runSystem = true;

int stepperSpeed = ((stepperMicrosteps * motorStepsPerRevolution * gearboxRatio) / gearboxRadius) * spoolSpeed; //Steps per second. The fastest motor speed that can be reliably supported is about 4000 steps per second at a clock frequency of 16 MHz on Arduino such as Uno etc. Faster processors can support faster stepping speeds.
//#define stepperSpeed 5760

//System Variables
int error = 0; //Start with a clean sheet and no error /* 0=no error; 1=Heater decoupled during rising; 2=Heater decoupled during hold; 10=Over Temp; 11=Thermistor short; 12=No thermistor */
#define heaterMaxTemp 275 //Shut down device if this temp is exceeded
#define heaterMinDefectTemp -10
#define heaterMaxDefectTemp 290
#define fwVersion 0.08

void setup() {

  serialSetup();
  thermistorSetup();
  PIDSetup();
  fanSetup();
  screenSetup();
  stepperSetup();
  buttonSetup();
}

void loop() {
  PIDLoop();
  fanLoop();
  displayLoop();
  stepperLoop();
  SerialLoop();
  buttonLoop();
}
