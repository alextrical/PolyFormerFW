/*
    The code in this file uses open source libraries provided by thecoderscorner

    DO NOT EDIT THIS FILE, IT WILL BE GENERATED EVERY TIME YOU USE THE UI DESIGNER
    INSTEAD EITHER PUT CODE IN YOUR SKETCH OR CREATE ANOTHER SOURCE FILE.

    All the variables you may need access to are marked extern in this file for easy
    use elsewhere.
 */

#include <tcMenu.h>
#include "PolyFormerFW_menu.h"
#include "ThemeMonoBordered.h"

// Global variable declarations
const  ConnectorLocalInfo applicationInfo = { "PolyFormer", "fddaa423-cb5c-4024-8f67-a9742f4457f3" };
ArduinoEEPROMAbstraction glArduinoEeprom(&EEPROM);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C gfx(U8G2_R2, U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE);
U8g2Drawable gfxDrawable(&gfx, &Wire);
GraphicsDeviceRenderer renderer(30, applicationInfo.name, &gfxDrawable);

// Global Menu Item declarations
const AnyMenuInfo minfoSettingsSaveSettings = { "SaveSettings", 20, 0xffff, 0, onSaveSettings };
ActionMenuItem menuSettingsSaveSettings(&minfoSettingsSaveSettings, NULL);
const AnalogMenuInfo minfoKd = { "Kd", 19, 34, 10000, onPidChange, 0, 10, "D" };
AnalogMenuItem menuKd(&minfoKd, 0, NULL);
const AnalogMenuInfo minfoKi = { "Ki", 18, 32, 10000, onPidChange, 0, 10, "I" };
AnalogMenuItem menuKi(&minfoKi, 0, &menuKd);
const AnalogMenuInfo minfoKp = { "Kp", 17, 30, 10000, onPidChange, 0, 10, "P" };
AnalogMenuItem menuKp(&minfoKp, 0, &menuKi);
const AnyMenuInfo minfoSettingsTemperaturePIDTune = { "PIDTune", 16, 0xffff, 0, onPIDTune };
ActionMenuItem menuSettingsTemperaturePIDTune(&minfoSettingsTemperaturePIDTune, &menuKp);
RENDERING_CALLBACK_NAME_INVOKE(fnSettingsTemperatureRtCall, backSubItemRenderFn, "Temperature", -1, NO_CALLBACK)
const SubMenuInfo minfoSettingsTemperature = { "Temperature", 15, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackSettingsTemperature(fnSettingsTemperatureRtCall, &menuSettingsTemperaturePIDTune);
SubMenuItem menuSettingsTemperature(&minfoSettingsTemperature, &menuBackSettingsTemperature, &menuSettingsSaveSettings);
const AnalogMenuInfo minfoSettingsPersonalisationSerialNumber = { "Serial Number", 23, 28, 999, NO_CALLBACK, 0, 1, "" };
AnalogMenuItem menuSettingsPersonalisationSerialNumber(&minfoSettingsPersonalisationSerialNumber, 0, NULL);
RENDERING_CALLBACK_NAME_INVOKE(fnSettingsPersonalisationUserNameRtCall, textItemRenderFn, "User Name", 18, onNameChanged)
TextMenuItem menuSettingsPersonalisationUserName(fnSettingsPersonalisationUserNameRtCall, 22, 10, &menuSettingsPersonalisationSerialNumber);
RENDERING_CALLBACK_NAME_INVOKE(fnSettingsPersonalisationRtCall, backSubItemRenderFn, "Personalisation", -1, NO_CALLBACK)
const SubMenuInfo minfoSettingsPersonalisation = { "Personalisation", 21, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackSettingsPersonalisation(fnSettingsPersonalisationRtCall, &menuSettingsPersonalisationUserName);
SubMenuItem menuSettingsPersonalisation(&minfoSettingsPersonalisation, &menuBackSettingsPersonalisation, &menuSettingsTemperature);
const char enumStrSettingsGearboxMicrosteps_0[] = "0";
const char enumStrSettingsGearboxMicrosteps_1[] = "2";
const char enumStrSettingsGearboxMicrosteps_2[] = "4";
const char enumStrSettingsGearboxMicrosteps_3[] = "8";
const char enumStrSettingsGearboxMicrosteps_4[] = "16";
const char enumStrSettingsGearboxMicrosteps_5[] = "32";
const char enumStrSettingsGearboxMicrosteps_6[] = "64";
const char* const enumStrSettingsGearboxMicrosteps[]  = { enumStrSettingsGearboxMicrosteps_0, enumStrSettingsGearboxMicrosteps_1, enumStrSettingsGearboxMicrosteps_2, enumStrSettingsGearboxMicrosteps_3, enumStrSettingsGearboxMicrosteps_4, enumStrSettingsGearboxMicrosteps_5, enumStrSettingsGearboxMicrosteps_6 };
const EnumMenuInfo minfoSettingsGearboxMicrosteps = { "Microsteps", 26, 36, 6, onGearboxChange, enumStrSettingsGearboxMicrosteps };
EnumMenuItem menuSettingsGearboxMicrosteps(&minfoSettingsGearboxMicrosteps, 0, NULL);
const AnalogMenuInfo minfoSettingsGearboxMotorCurrent = { "MotorCurrent", 14, 16, 1900, onMotorCurrent, 100, 1, "mA" };
AnalogMenuItem menuSettingsGearboxMotorCurrent(&minfoSettingsGearboxMotorCurrent, 0, &menuSettingsGearboxMicrosteps);
const AnalogMenuInfo minfoSettingsSpoolRadius = { "SpoolRadius", 12, 12, 450, onGearboxChange, 50, 1, "mm" };
AnalogMenuItem menuSettingsSpoolRadius(&minfoSettingsSpoolRadius, 0, &menuSettingsGearboxMotorCurrent);
const AnalogMenuInfo minfoSettingsGearboxRatio = { "GearboxRatio", 11, 10, 99, onGearboxChange, 1, 1, "to1" };
AnalogMenuItem menuSettingsGearboxRatio(&minfoSettingsGearboxRatio, 0, &menuSettingsSpoolRadius);
const AnalogMenuInfo minfoSettingsMotorSteps = { "MotorSteps", 10, 8, 396, onGearboxChange, 4, 1, "Step" };
AnalogMenuItem menuSettingsMotorSteps(&minfoSettingsMotorSteps, 0, &menuSettingsGearboxRatio);
RENDERING_CALLBACK_NAME_INVOKE(fnSettingsGearboxRtCall, backSubItemRenderFn, "Gearbox", -1, NO_CALLBACK)
const SubMenuInfo minfoSettingsGearbox = { "Gearbox", 9, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackSettingsGearbox(fnSettingsGearboxRtCall, &menuSettingsMotorSteps);
SubMenuItem menuSettingsGearbox(&minfoSettingsGearbox, &menuBackSettingsGearbox, &menuSettingsPersonalisation);
RENDERING_CALLBACK_NAME_INVOKE(fnSettingsRtCall, backSubItemRenderFn, "Settings", -1, NO_CALLBACK)
const SubMenuInfo minfoSettings = { "Settings", 6, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackSettings(fnSettingsRtCall, &menuSettingsGearbox);
SubMenuItem menuSettings(&minfoSettings, &menuBackSettings, NULL);
const AnalogMenuInfo minfoFan = { "Fan", 5, 6, 100, NO_CALLBACK, 0, 1, "%" };
AnalogMenuItem menuFan(&minfoFan, 0, &menuSettings);
const AnalogMenuInfo minfoTemperature = { "Setpoint", 3, 4, 150, onTemperatureChange, 100, 1, "C" };
AnalogMenuItem menuTemperature(&minfoTemperature, 0, &menuFan);
const AnalogMenuInfo minfoFeed = { "Feed", 2, 2, 149, onGearboxChange, 1, 10, "mm s" };
AnalogMenuItem menuFeed(&minfoFeed, 0, &menuTemperature);
const FloatMenuInfo minfoActualTemp = { "Actual Temp", 24, 0xffff, 2, NO_CALLBACK };
FloatMenuItem menuActualTemp(&minfoActualTemp, &menuFeed);
const AnyMenuInfo minfoStart = { "Start", 1, 0xffff, 0, onStart };
ActionMenuItem menuStart(&minfoStart, &menuActualTemp);

void setupMenu() {
    // First we set up eeprom and authentication (if needed).
    menuMgr.setEepromRef(&glArduinoEeprom);
    // Now add any readonly, non-remote and visible flags.
    menuActualTemp.setReadOnly(true);

    // Code generated by plugins.
    gfx.begin();
    renderer.setUpdatesPerSecond(10);
    switches.init(internalDigitalIo(), SWITCHES_NO_POLLING, true);
    menuMgr.initForEncoder(&renderer, &menuStart, encA, encB, encSW);
    renderer.setTitleMode(BaseGraphicalRenderer::TITLE_FIRST_ROW);
    renderer.setUseSliderForAnalog(false);
    installMonoBorderedTheme(renderer, MenuFontDef(nullptr, 1), MenuFontDef(u8g2_font_finderskeepers_tf, 1), true);
}

