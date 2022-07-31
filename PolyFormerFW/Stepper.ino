//#include <AccelStepper.h>

//AccelStepper stepper(AccelStepper::FULL2WIRE, stepperStepPin, stepperDirPin); //Step, Dir

void stepperSetup()
{
//  stepper.setEnablePin(stepperEnPin);
//  stepper.setPinsInverted(stepperDirInvert, stepperStepInvert, stepperEnInvert); //Dir,Step,En

//  stepper.setMaxSpeed(stepperSpeed); //Speeds of more than 4000 steps per second are unreliable
//  stepper.setSpeed(stepperSpeed);
//  pinMode(stepperEnPin, OUTPUT);
//    digitalWrite(stepperEnPin, HIGH); //High disables the stepper


  TIM_TypeDef *Instance = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(stepperStepPin), PinMap_PWM);
  uint32_t channel = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(stepperStepPin), PinMap_PWM));
  // Instantiate HardwareTimer object. Thanks to 'new' instantiation, HardwareTimer is not destructed when setup() function is finished.
  HardwareTimer *MyTim = new HardwareTimer(Instance);

  // Configure and start PWM
  // MyTim->setPWM(channel, stepperStepPin, 5, 10, NULL, NULL); // No callback required, we can simplify the function call
  MyTim->setPWM(channel, stepperStepPin, stepperSpeed, 10); // 5 Hertz, 10% dutycycle
  
    pinMode(stepperEnPin, OUTPUT);
    digitalWrite(stepperEnPin, HIGH); //High disables the stepper
  
    pinMode(stepperDirPin, OUTPUT);
    digitalWrite(stepperDirPin, LOW);
}

void stepperLoop()
{
  if (heating == 2 && error == 0 && runSystem) {
//    stepper.enableOutputs();
    digitalWrite(stepperEnPin, LOW); //Low enables the stepper
//    stepper.runSpeed();
  } else {
//    stepper.disableOutputs();
    digitalWrite(stepperEnPin, HIGH); //High disables the stepper
  }
}
