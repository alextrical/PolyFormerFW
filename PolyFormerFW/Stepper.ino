void stepperSetup()
{
  TIM_TypeDef *Instance = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(stepperStepPin), PinMap_PWM);
  uint32_t channel = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(stepperStepPin), PinMap_PWM));
  // Instantiate HardwareTimer object. Thanks to 'new' instantiation, HardwareTimer is not destructed when setup() function is finished.
  HardwareTimer *MyTim = new HardwareTimer(Instance);

  // Configure and start PWM
  stepperSpeed = menuFeed.getAsFloatingPointValue()*menuSettingsMotorSteps.getAsFloatingPointValue()*menuSettingsGearboxRatio.getAsFloatingPointValue()*menuSettingsMicrosteps.getAsFloatingPointValue()/(3.1459*menuSettingsSpoolRadius.getAsFloatingPointValue());

  MyTim->setPWM(channel, stepperStepPin, stepperSpeed, 10); // 5 Hertz, 10% dutycycle

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
