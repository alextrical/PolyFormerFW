// Automatically retrieve TIM instance and channel associated to stepperStepPin
// This is used to be compatible with all STM32 series automatically.
TIM_TypeDef *Instance = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(stepperStepPin), PinMap_PWM);
uint32_t channel = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(stepperStepPin), PinMap_PWM));


// Instantiate HardwareTimer object. Thanks to 'new' instantiation, HardwareTimer is not destructed when setup() function is finished.
HardwareTimer *MyTim = new HardwareTimer(Instance);

void pwm_stepperStepPin(int frequency)
{
  //  MyTim->setCaptureCompare(channel, duty, PERCENT_COMPARE_FORMAT);
  //  MyTim->setPWM(channel, stepperStepPin, frequency, 50);
  MyTim->setOverflow(1000000 / frequency, MICROSEC_FORMAT); // 100000 microseconds = 100 milliseconds
  delay(50);
}

void stepperSetup()
{
  //    pinMode(stepperEnPin, OUTPUT);
  //  digitalWrite(stepperEnPin, LOW); //High disables the stepper
  //
  //  pinMode(stepperDirPin, OUTPUT);
  //  digitalWrite(stepperDirPin, LOW);
  //
  //  // Configure and start PWM
  //  // MyTim->setPWM(channel, stepperStepPin, 5, 10, NULL, NULL); // No callback required, we can simplify the function call
  //  MyTim->setPWM(channel, stepperStepPin, 5000, 50); // 5 Hertz, 10% dutycycle


  stepperSpeed = menuMotorSteps.getAsFloatingPointValue() * menuFeed.getAsFloatingPointValue() * menuGearboxRatio.getAsFloatingPointValue() * menuMicrosteps.getAsFloatingPointValue();

  // Configure and start PWM
  // MyTim->setPWM(channel, pin, 5, 10, NULL, NULL); // No callback required, we can simplify the function call
  MyTim->setPWM(channel, stepperStepPin, stepperSpeed, 50); // 5 Hertz, 10% dutycycle


  //
  //  pinMode(stepperEnPin, OUTPUT);
  //  digitalWrite(stepperEnPin, LOW); //High disables the stepper
  //
  //  pinMode(stepperDirPin, OUTPUT);
  //  digitalWrite(stepperDirPin, LOW);
  //
  pinMode(stepperEnPin, OUTPUT);
  digitalWrite(stepperEnPin, HIGH); //High disables the stepper

  pinMode(stepperDirPin, OUTPUT);
  digitalWrite(stepperDirPin, LOW);
}

void stepperLoop()
{
  if (/*heating == 2 &&*/ error == 0 && runSystem) {
    digitalWrite(stepperEnPin, LOW); //Low enables the stepper
  } else {
    digitalWrite(stepperEnPin, HIGH); //High disables the stepper
  }
}
