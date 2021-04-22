#include <Arduino.h>
#include <stdlib.h>
#include "main.hpp"
#include "FixedString.hpp"
#include "Functions.hpp"
#include "PS2Keyboard.hpp"
#include "KeyCode.hpp"

USBHID HID;

const uint8_t reportDescription[] = {
    HID_MOUSE_REPORT_DESCRIPTOR(),
    HID_CONSUMER_REPORT_DESCRIPTOR(),
    HID_KEYBOARD_REPORT_DESCRIPTOR()};

USBCompositeSerial cserial;
HIDConsumer consumer(HID);
HIDKeyboard keyboard(HID);
HIDMouse mouse(HID);

PS2Keyboard ps2Keyboard(PB4, PB3);

void setup()
{
  HID.begin(cserial, reportDescription, sizeof(reportDescription));
  while (!USBComposite)
    ;
  keyboard.begin();
}

void Commands(const FixedString<256> &str)
{
  const char *param[3];
  uint8_t param_count = 3;

  if (!ParsParam(str, param, param_count))
  {
    //debug message
    DebugPrintLn("<commands>:error: The parameter array is too small ", param_count);
    return;
  }

  //keyboard
  if (Parameter::Cmp(param[0], "kpn")) //key press number [kpn 1]
  {
    DebugPrintLn("<commands>:info: kpn");
    if (param_count < 2)
    {
      DebugPrintLn("<commands:ccn>:error: Not enough arguments.");
      return;
    }
    uint8_t key = Parameter::ahextoi16(param[1]);
    keyboard.pressKeyCode(key);
  }
  else if (Parameter::Cmp(param[0], "krn")) //key release number
  {
    DebugPrintLn("<commands>:info: krn");
    if (param_count < 2)
    {
      DebugPrintLn("<commands:krn>:error: Not enough arguments.");
      return;
    }
    uint8_t key = Parameter::ahextoi16(param[1]);
    keyboard.releaseKeyCode(key);
  }
  else if (Parameter::Cmp(param[0], "kcn")) //key click number
  {
    DebugPrintLn("<commands>:info: kcn");
    if (param_count < 2)
    {
      DebugPrintLn("<commands:kcn>:error: Not enough arguments.");
      return;
    }
    uint8_t key = Parameter::ahextoi16(param[1]);
    keyboard.pressKeyCode(key);
    keyboard.pressKeyCode(key);
  }
  //consumer
  else if (Parameter::Cmp(param[0], "cpn")) //consumer press number
  {
    DebugPrintLn("<commands>:info: cpn");
    if (param_count < 2)
    {
      DebugPrintLn("<commands:cpn>:error: Not enough arguments.");
      return;
    }
    uint16_t key = Parameter::ahextoi16(param[1]);
    consumer.press(key);
  }
  else if (Parameter::Cmp(param[0], "crn")) //consumer release number
  {
    DebugPrintLn("<commands>:info: crn");
    consumer.release();
  }
  else if (Parameter::Cmp(param[0], "ccn")) //consumer click number
  {
    DebugPrintLn("<commands>:info: ccn");
    if (param_count < 2)
    {
      DebugPrintLn("<commands:ccn>:error: Not enough arguments.");
      return;
    }
    uint16_t key = Parameter::ahextoi16(param[1]);
    consumer.press(key);
    consumer.release();
  }

  //mouse
  else if (Parameter::Cmp(param[0], "mpn")) //mouse press number
  {
    DebugPrintLn("<commands>:info: mpn");
    if (param_count < 2)
    {
      DebugPrintLn("<commands:mpn>:error: Not enough arguments.");
      return;
    }
    uint8_t key = Parameter::ahextoi16(param[1]);
    mouse.press(key);
  }
  else if (Parameter::Cmp(param[0], "mrn")) //mouse release number
  {
    DebugPrintLn("<commands>:info: mrn");
    if (param_count < 2)
    {
      DebugPrintLn("<commands:mrn>:error: Not enough arguments.");
      return;
    }
    uint8_t key = Parameter::ahextoi16(param[1]);
    mouse.release(key);
  }
  else if (Parameter::Cmp(param[0], "mcn")) //mouse click number
  {
    DebugPrintLn("<commands>:info: mcn");
    if (param_count < 2)
    {
      DebugPrintLn("<commands:mcn>:error: Not enough arguments.");
      return;
    }
    uint8_t key = Parameter::ahextoi16(param[1]);
    mouse.press(key);
    mouse.release(key);
  }

  //all
  else if (Parameter::Cmp(param[0], "rab")) //release all button [rab]
  {
    keyboard.releaseAll();
    consumer.release();
    mouse.release(MOUSE_ALL);
  }

  else if (Parameter::Cmp(param[0], "ksm")) // Key set mode number [ksm 04(A) 05(standart & press)]
  {
    DebugPrintLn("<commands>:info: ksm");
    if (param_count < 3)
    {
      DebugPrintLn("<commands:ksm>:error: Not enough arguments.");
      return;
    }
    uint8_t key = Parameter::ahextoi16(param[1]);
    uint8_t mode = Parameter::ahextoi16(param[2]);
    KeyProcessor::data.mode[key] = (KeyProcessor::Data::Mode)mode;
  }
  else if (Parameter::Cmp(param[0], "kgm")) // Key get mode [kgm 04(A)] -> [kgmr 05(standart & press)]
  {
    DebugPrintLn("<commands>:info: kgm");
    if (param_count < 2)
    {
      DebugPrintLn("<commands:kgm>:error: Not enough arguments.");
      return;
    }
    uint8_t key = Parameter::ahextoi16(param[1]);
    cserial.print("kgm ");
    cserial.println(KeyProcessor::data.mode[key], HEX);
  }

  else if (Parameter::Cmp(param[0], "kspm")) //Key set press map [kspm 4(A) 1234]
  {
    DebugPrintLn("<commands>:info: kspm");
    if (param_count < 3)
    {
      DebugPrintLn("<commands:kspm>:error: Not enough arguments.");
      return;
    }
    uint8_t key = Parameter::ahextoi16(param[1]);
    uint16_t pos = Parameter::ahextoi16(param[2]);
    KeyProcessor::data.press_map[key] = pos;
  }
  else if (Parameter::Cmp(param[0], "ksrm")) //Key set release map [ksrm 4(A) 1234]
  {
    DebugPrintLn("<commands>:info: ksrm");
    if (param_count < 3)
    {
      DebugPrintLn("<commands:ksrm>:error: Not enough arguments.");
      return;
    }
    uint8_t key = Parameter::ahextoi16(param[1]);
    uint16_t pos = Parameter::ahextoi16(param[2]);
    KeyProcessor::data.release_map[key] = pos;
  }

  else if (Parameter::Cmp(param[0], "ksc")) //Key set commands [ksc] [12] [34] ... [ksce]
  {
    DebugPrintLn("<commands>:info: ksc begin");

    FixedString<256> s;
    size_t counter = 0;
    while (1)
    {
      //ждем след данные
      while(1)
      {
        if (s.readSerial())
          break;
      }

      //проверяем конец передачи
      if (Parameter::Cmp(s.toCStr(), "ksce"))
        break;
      
      uint16_t com = Parameter::ahextoi16(s.toCStr());
      KeyProcessor::Data::CommandData* cd = reinterpret_cast<KeyProcessor::Data::CommandData*>(&com);
      KeyProcessor::data.commands[counter] = *cd;
      counter++;
    }
  }

  //GetDeviceName
  else if (Parameter::Cmp(param[0], "gdn"))
  {
    cserial.println("TimProgrammingKeyboard");
  }
}

void PS2KeyCommandMode()
{
  auto p = ps2Keyboard.getPckage();
  uint8_t HID_code = PS2ToHID::convert(p.key);

  //#DEBUG
  if (HID_code == 0)
  {
    cserial.println("<loop>:Error: PS/2 key code not found");
    cserial.print(p.key[0], HEX);
    cserial.print(p.key[1], HEX);
    cserial.print(p.key[2], HEX);
    cserial.println();
    return;
  }

  //standart action
  if (KeyProcessor::data.mode[HID_code] & KeyProcessor::Data::Mode::Standart)
  {
    if (p.status == PS2Keyboard::Package::Status::Press)
    {
      keyboard.pressKeyCode(HID_code);
    }
    else
    {
      keyboard.releaseKeyCode(HID_code);
    }
  }

  //command
  if (KeyProcessor::data.mode[HID_code] & KeyProcessor::Data::Mode::Command)
  {
    KeyProcessor::RunCommand(HID_code, p.status);
  }

  //Send
  if (KeyProcessor::data.mode[HID_code] & KeyProcessor::Data::Mode::Send)
  {
    if (p.status == PS2Keyboard::Package::Status::Press)
      cserial.print("kpn ");
    else
      cserial.print("krn ");
    
    cserial.println(HID_code, HEX);
  }

  //SwitchMode
  if (KeyProcessor::data.mode[HID_code] & KeyProcessor::Data::Mode::SwitchMode)
  {
    if (p.status == PS2Keyboard::Package::Status::Press)
      KeyProcessor::command_mode = !KeyProcessor::command_mode;
  }
}
void PS2Key()
{
  auto p = ps2Keyboard.getPckage();
  uint8_t HID_code = PS2ToHID::convert(p.key);

  //#DEBUG
  if (HID_code == 0)
  {
    cserial.println("<loop>:Error: PS/2 key code not found");
    cserial.print(p.key[0], HEX);
    cserial.print(p.key[1], HEX);
    cserial.print(p.key[2], HEX);
    cserial.println();
    return;
  }

  //standart action
  if ((KeyProcessor::data.mode[HID_code] & KeyProcessor::Data::Mode::SwitchMode) != true)
  {
    if (p.status == PS2Keyboard::Package::Status::Press)
    {
      keyboard.pressKeyCode(HID_code);
    }
    else
    {
      keyboard.releaseKeyCode(HID_code);
    }
  }

  //command

  //Send

  //SwitchMode
  if (KeyProcessor::data.mode[HID_code] & KeyProcessor::Data::Mode::SwitchMode)
  {
    if (p.status == PS2Keyboard::Package::Status::Press)
      KeyProcessor::command_mode = !KeyProcessor::command_mode;
  }
}

void loop()
{
  if (cserial.isConnected())
    pinMode(LED_BUILTIN, OUTPUT);
  else
    pinMode(LED_BUILTIN, INPUT);
  

  //uint32_t time = millis();
  FixedString<256> s;
  if (s.readSerial())
  {
    DebugPrintLn("<main>:info: Enter string ", s.getSize(), " \"", s.toCStr(), "\"");
    Commands(s);
  }
  if (ps2Keyboard.isNew())
  {
    if (KeyProcessor::command_mode)
      PS2KeyCommandMode();
    else
      PS2Key();
    
  }
  //time = millis() - time;
  //if (time > 1)
  //  DebugPrintLn("<loop>:Info: time: ", time);
}