/*
    The code in this file uses open source libraries provided by thecoderscorner

    DO NOT EDIT THIS FILE, IT WILL BE GENERATED EVERY TIME YOU USE THE UI DESIGNER
    INSTEAD EITHER PUT CODE IN YOUR SKETCH OR CREATE ANOTHER SOURCE FILE.

    All the variables you may need access to are marked extern in this file for easy
    use elsewhere.
 */

#ifndef MENU_GENERATED_CODE_H
#define MENU_GENERATED_CODE_H

#include <Arduino.h>
#include <tcMenu.h>
#include "tcMenuU8g2.h"
#include <RuntimeMenuItem.h>
#include <IoAbstractionWire.h>
#include <IoAbstraction.h>
#include <ArduinoEEPROMAbstraction.h>

// variables we declare that you may need to access
extern const PROGMEM ConnectorLocalInfo applicationInfo;
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C gfx;
// extern U8G2_SH1106_128X64_NONAME_F_HW_I2C gfx;
extern GraphicsDeviceRenderer renderer;

// Any externals needed by IO expanders, EEPROMs etc
extern IoAbstractionRef ioexp_IO;

// Global Menu Item exports
extern ActionMenuItem menuSettingsSaveSettings;
extern AnalogMenuItem menuKd;
extern AnalogMenuItem menuKi;
extern AnalogMenuItem menuKp;
extern ActionMenuItem menuSettingsTemperaturePIDTune;
extern BackMenuItem menuBackSettingsTemperature;
extern SubMenuItem menuSettingsTemperature;
extern AnalogMenuItem menuSettingsPersonalisationSerialNumber;
extern TextMenuItem menuSettingsPersonalisationUserName;
extern BackMenuItem menuBackSettingsPersonalisation;
extern SubMenuItem menuSettingsPersonalisation;
extern FloatMenuItem menuSettingsGearboxCs2rms;
extern FloatMenuItem menuSettingsGearboxCsActual;
extern FloatMenuItem menuSettingsGearboxSGRESULT;
extern AnalogMenuItem menuSettingsGearboxStallValue;
extern BooleanMenuItem menuSettingsGearboxStealth;
extern AnalogMenuItem menuSettingsGearboxIScaleAnalog;
extern AnalogMenuItem menuSettingsGearboxSeMax;
extern AnalogMenuItem menuSettingsGearboxSeMin;
extern AnalogMenuItem menuSettingsGearboxBlankTime;
extern AnalogMenuItem menuSettingsGearboxToff;
extern BooleanMenuItem menuReverse;
extern EnumMenuItem menuSettingsGearboxMicrosteps;
extern AnalogMenuItem menuSettingsGearboxMotorCurrent;
extern AnalogMenuItem menuSettingsSpoolRadius;
extern AnalogMenuItem menuSettingsGearboxRatio;
extern AnalogMenuItem menuSettingsMotorSteps;
extern BackMenuItem menuBackSettingsGearbox;
extern SubMenuItem menuSettingsGearbox;
extern BackMenuItem menuBackSettings;
extern SubMenuItem menuSettings;
extern AnalogMenuItem menuFan;
extern AnalogMenuItem menuTemperature;
extern AnalogMenuItem menuFeed;
extern FloatMenuItem menuActualTemp;
extern ActionMenuItem menuStart;

// Provide a wrapper to get hold of the root menu item and export setupMenu
inline MenuItem& rootMenuItem() { return menuStart; }
void setupMenu();

// Callback functions must always include CALLBACK_FUNCTION after the return type
#define CALLBACK_FUNCTION

void CALLBACK_FUNCTION onGearboxChange(int id);
void CALLBACK_FUNCTION onMotorCurrent(int id);
void CALLBACK_FUNCTION onNameChanged(int id);
void CALLBACK_FUNCTION onPIDTune(int id);
void CALLBACK_FUNCTION onPidChange(int id);
void CALLBACK_FUNCTION onSaveSettings(int id);
void CALLBACK_FUNCTION onStart(int id);
void CALLBACK_FUNCTION onTemperatureChange(int id);

#endif // MENU_GENERATED_CODE_H
