#include <SPI.h>
#include <Wire.h>
#include <U8x8lib.h>

unsigned long  displayTime = 0;

//// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ SCLPin, /* data=*/ SDAPin, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the Display


void screenSetup() {
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_8x13B_1x2_f);
  u8x8.setFlipMode(1);
  u8x8.draw1x2String(4, 0, "PolyFormer");
  u8x8.drawString(5, 4, "PF.999");
  u8x8.drawString(4, 6, "SW V0.08");
  delay(5000);
  u8x8.setFont(u8x8_font_5x7_f);
  u8x8.clear();
}

void displayLoop() {
  //send-receive serial with processing if it's time
  if (millis() > displayTime)
  {
    //    display.clearDisplay(); // Clear the display buffer
    if (error == 0) {
      u8x8.draw1x2String(3, 0, "PolyFormer");
      //      u8x8.drawString(0, 2, "PF.999");

      u8x8.setFont(u8x8_font_open_iconic_play_2x2);
      if (runSystem) {
        //        u8x8.drawString(6, 3, "RUN ");
        u8x8.drawGlyph(0, 2, '@' + 5);
      } else {
        //        u8x8.drawString(6, 3, "STOP");
        u8x8.drawGlyph(0, 2, '@' + 11);
      }
      u8x8.setFont(u8x8_font_5x7_f);

      u8x8.drawString(12, 3, "PET");

      //      char tempBuffer[40];
      //      sprintf(tempBuffer, "T: %s | %s", currentTemperatureC, targetTemperatureC);
      //      u8x8.drawString(0, 4, tempBuffer);
      //  Serial.println(buffer);
      u8x8.setCursor(0, 4);
      u8x8.print("T: ");
      char outstr[5];
      dtostrf(currentTemperatureC, 5, 1, outstr);
      u8x8.print(outstr);
      u8x8.print("|");
      dtostrf(targetTemperatureC, -5, 1, outstr);
      u8x8.print(outstr);
      //            u8x8.print(targetTemperatureC);
      //            u8x8.print(" ");

      u8x8.setCursor(0, 5);
      u8x8.print("mm/s: ");
      if (runSystem) {
        u8x8.print(spoolSpeed);
      } else {
        u8x8.print("0  ");
      }

      u8x8.setCursor(0, 6);
      u8x8.print("Fan: ");
      if (fan1)
        u8x8.print(meltzoneFanSpeed);
      else
        u8x8.print("0");
      u8x8.print("%  ");

    } else {
      u8x8.setFont(u8x8_font_5x7_f);
      u8x8.draw1x2String(4, 0, " ERROR: ");
      u8x8.draw1x2String(4, 2, "        ");
      u8x8.setFont(u8x8_font_open_iconic_embedded_4x4);
      u8x8.drawGlyph(0, 0, '@' + 7);
      u8x8.drawGlyph(12, 0, '@' + 7);


      u8x8.setFont(u8x8_font_5x7_f);
      switch (error) {
        case 1 :
          u8x8.draw1x2String(0, 4, "Heater decoupled");
          u8x8.draw1x2String(0, 6, "    on Rise!    ");
          break;
        case 2 :
          u8x8.draw1x2String(0, 4, "Heater decoupled");
          u8x8.draw1x2String(0, 6, "    on Hold!    ");
          break;
        case 10 :
          u8x8.draw1x2String(0, 4, "      Over      ");
          u8x8.draw1x2String(0, 6, "  Temperature!  ");
          break;
        case 11:
          //          u8x8.draw1x2String(0, 2, "THERM. SHORT");
          u8x8.draw1x2String(0, 4, "   Thermistor   ");
          u8x8.draw1x2String(0, 6, "    Shorted!    ");
          break;
        case 12:
          //          u8x8.draw1x2String(0, 2, "NO THERM.");
          u8x8.draw1x2String(0, 4, "   Thermistor   ");
          u8x8.draw1x2String(0, 6, "    Missing!    ");
          break;
        default:
          char cstr[16];
          itoa(error, cstr, 10);
          u8x8.draw1x2String(0, 2, cstr);
      }

    }

    displayTime += 100;
  }
}
