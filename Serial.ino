unsigned long  serialTime = 0;

void serialSetup() {
  Serial.begin(baudrate);
  Serial.println("PolyFormer");
  Serial.println();
  Serial.print("Firmware Version: V");
  Serial.println(fwVersion);
  printMenu();
}

void SerialLoop() {
  //send-receive serial with processing if it's time
  if (millis() > serialTime)
  {
    SerialReceive();
    SerialSend();
    serialTime += 1000;
    menuActualTemp.setFloatValue(therm.getTemp());
  }
}

void SerialSend()
{
      Serial.print("setpoint: "); Serial.print(Setpoint); Serial.print(" ");
      Serial.print("input: "); Serial.print(Input); Serial.print(" ");
      Serial.print("output: "); Serial.print(Output); Serial.print(" ");
    Serial.println();
    Serial.println(menuSettingsMotorSteps.getAsFloatingPointValue());
    Serial.println(menuSettingsGearboxRatio.getAsFloatingPointValue());
    Serial.println(menuSettingsSpoolRadius.getAsFloatingPointValue());
    Serial.println(menuSettingsGearboxMicrosteps.getCurrentValue());
    Serial.println(menuSettingsGearboxMotorCurrent.getCurrentValue());

    Serial.println(therm.getTemp());
    updateStepperDisplay();

    // Serial.print("0 ");
    // Serial.print(driver.SG_RESULT(), DEC);
    // Serial.print(" ");
    // Serial.print(driver.cs_actual(), DEC);
    // Serial.print(" ");
    // Serial.println(driver.cs2rms(driver.cs_actual()), DEC);

    // menuSettingsGearboxSG_RESULT.setFloatValue(driver.SG_RESULT(), DEC);
    // menuSettingsGearboxcs_actual.setFloatValue(driver.cs_actual(), DEC);
    // menuSettingsGearboxcs2rms.setFloatValue(driver.cs2rms(driver.cs_actual()), DEC);

//      if (tuning) {
//        Serial.println("tuning mode");
//      } else {
//        //    Serial.print("kp: ");Serial.print(heaterPID.GetKp());Serial.print(" ");
//        //    Serial.print("ki: ");Serial.print(heaterPID.GetKi());Serial.print(" ");
//        //    Serial.print("kd: ");Serial.print(heaterPID.GetKd());
//        Serial.println();
//      }
}

void SerialReceive()
{
  if (Serial.available())
  {
    char b = Serial.read();
    Serial.flush();
    //if ((b == 't' && !tuning) || (b == 't' && tuning))changeAutoTune();
    if (b == '1')runSystem = true;
    if (b == '0')runSystem = false;
    if (b == 'm')printMenu();
  }
}

void printMenu() {
  Serial.println("Menu");
  Serial.println("");
  Serial.println("t : Toggle PID Auto Tune");
  Serial.println("1 : Enable heater");
  Serial.println("0 : Disable heater");
}
