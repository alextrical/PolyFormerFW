#include "PolyFormerFW_menu.h"
const char pgmCommittedToRom[] PROGMEM = "Saved to ROM";

void setup() {
  // If you use i2c and serial devices, be sure to start wire / serial.
 Wire.setSDA(PB9); //BlackPill
 Wire.setSCL(PB8); //BlackPill
  // Wire.setSDA(PB9);
  // Wire.setSCL(PB8);
  Wire.begin();

  // here we initialise the EEPROM class to 512 bytes of storage
  // don't commit often to this, it's in FLASH
//  EEPROM.begin(512);

  // This is added by tcMenu Designer automatically during the first setup.
  setupMenu();

  // lastly we load state from EEPROM.
  menuMgr.load();

}

void loop() {
  taskManager.runLoop();

}


void CALLBACK_FUNCTION onSaveSettings(int id) {
  // TODO - your menu change code
  menuMgr.save();

  // here is a brief example of how to show a dialog, usually for information
  // or yes/no answers.
  auto* dlg = renderer.getDialog();
  if(dlg && !dlg->isInUse()) {
    dlg->setButtons(BTNTYPE_NONE, BTNTYPE_OK);
    dlg->show(pgmCommittedToRom, false);
    dlg->copyIntoBuffer("just so you know");
  }
}

void CALLBACK_FUNCTION onPIDTune(int id) {
  // TODO - your menu change code
}

void CALLBACK_FUNCTION onStart(int id) {
  // TODO - your menu change code
}


void CALLBACK_FUNCTION onNameChanged(int id) {
  // TODO - your menu change code
}
