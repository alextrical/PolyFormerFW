#define DRIVER_ADDRESS    0b00    // TMC2209 Driver address
#define R_SENSE           0.11f   // SilentStepStick series use 0.11
int microstep;

//#define RMS_CURRENT       600     // Motor RMS current in mA
//#define MICROSTEPS        0       // Microsteps; note that MicroPlyer will interpolate to 256
#define SPREADCYCLE       true   // Spreadcycle can have higher RPM but is louder
#define STALL_VALUE     100 // [0..255]


HardwareSerial Serial2(PA15, PA14_ALT1);

TMC2209Stepper driver(&Serial2, R_SENSE, DRIVER_ADDRESS);   // Create TMC driver

void stepperSetup()
{
  pinMode(stepperEnPin, OUTPUT);

  Serial2.begin(115200);
  USART2->CR1 &= ~USART_CR1_UE;   // UE = 0... disable USART
  USART2->CR2 |= USART_CR2_SWAP;  //Swap TX/RX pins2
  USART2->CR3 |= USART_CR3_HDSEL; //Set Half-duplex selection
  USART2->CR1 |= USART_CR1_UE;    // UE = 1... Enable USART

  digitalWrite(stepperEnPin, LOW);            // Enable TMC2209 board

  driver.begin();
//  driver.toff(5);                       // Enables driver in software
//  //  driver.rms_current(RMS_CURRENT);      // Set motor RMS current (mA)
//  stepperMicrosteps();
//  stepperCurrent();
//  driver.en_spreadCycle(SPREADCYCLE);   // Toggle spreadCycle on TMC2208/2209/2224
//  driver.pwm_autoscale(true);           // Needed for stealthChop

  driver.toff(menuSettingsGearboxToff.getCurrentValue()); //4
  // driver.blank_time(menuSettingsGearboxblankTime.getCurrentValue()); //24
  stepperCurrent();
  stepperMicrosteps();
  driver.TCOOLTHRS(0xFFFFF); // 20bit max
  driver.semin(menuSettingsGearboxSeMin.getCurrentValue()); //5
  driver.semax(menuSettingsGearboxSeMax.getCurrentValue()); //2
  driver.sedn(0b01);
  driver.SGTHRS(menuSettingsGearboxStallValue.getCurrentValue());
  driver.I_scale_analog(menuSettingsGearboxIScaleAnalog.getCurrentValue());
  
}

void stepperSppeed()
{ 
  driver.shaft(menuReverse.getCurrentValue()); // SET DIRECTION
  stepperMicrosteps();
  int32_t dest_speed;
  if (runSystem && runMotor /*&& therm.getTemp() > (menuTemperature.getAsFloatingPointValue() - 10)*/) { //run only if temperature is within 10C of setpoint
    dest_speed = microstep * menuFeed.getAsFloatingPointValue() * menuSettingsMotorSteps.getCurrentValue() * menuSettingsGearboxRatio.getAsFloatingPointValue() / (3.1459 * menuSettingsSpoolRadius.getCurrentValue());
  } else {
    dest_speed = 0;
  }
  Serial.println("dest_speed: ");
  Serial.println(dest_speed);
  driver.VACTUAL(dest_speed);
}

void stepperMicrosteps() {
  //  uint16_t currentValue = menuItem.getCurrentValue();
  switch (menuSettingsGearboxMicrosteps.getCurrentValue()) {
    case 1:
      microstep = 2;
      break;
    case 2:
      microstep = 4;
      break;
    case 3:
      microstep = 8;
      break;
    case 4:
      microstep = 16;
      break;
    case 5:
      microstep = 32;
      break;
    case 6:
      microstep = 64;
      break;
    case 7:
      microstep = 128;
      break;
    case 8:
      microstep = 256;
      break;
    default:
      microstep = 1;
      break;
  }
  Serial.print("Microsteps: ");
  Serial.println(microstep);
  driver.microsteps(microstep);        // Set microsteps
}

void stepperCurrent() {
  driver.rms_current(menuSettingsGearboxMotorCurrent.getCurrentValue());      // Set motor RMS current (mA)
}

void updateStepperDisplay() {
    Serial.print("0 ");
    Serial.print(driver.SG_RESULT(), DEC);
    Serial.print(" ");
    Serial.print(driver.cs_actual(), DEC);
    Serial.print(" ");
    Serial.println(driver.cs2rms(driver.cs_actual()), DEC);

    menuSettingsGearboxSGRESULT.setFloatValue(driver.SG_RESULT(), DEC);
    menuSettingsGearboxCsActual.setFloatValue(driver.cs_actual(), DEC);
    menuSettingsGearboxCs2rms.setFloatValue(driver.cs2rms(driver.cs_actual()), DEC);
}
