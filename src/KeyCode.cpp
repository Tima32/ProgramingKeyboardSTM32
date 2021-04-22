#include "KeyCode.hpp"
#include "main.hpp"

namespace PS2ToHID
{
    // {HID_code, PS2_byte0, PS2_byte1, PS2_byte2, PS2_byte3}
    constexpr uint8_t convert_table[][4] =
        {
            {0x04, 0x1C, 0x00, 0x00}, //a
            {0x05, 0x32, 0x00, 0x00}, //b
            {0x06, 0x21, 0x00, 0x00}, //c
            {0x07, 0x23, 0x00, 0x00}, //d
            {0x08, 0x24, 0x00, 0x00}, //e
            {0x09, 0x2B, 0x00, 0x00}, //f
            {0x0A, 0x34, 0x00, 0x00}, //g
            {0x0B, 0x33, 0x00, 0x00}, //h
            {0x0C, 0x43, 0x00, 0x00}, //i
            {0x0D, 0x3B, 0x00, 0x00}, //j
            {0x0E, 0x42, 0x00, 0x00}, //k
            {0x0F, 0x4B, 0x00, 0x00}, //l
            {0x10, 0x3A, 0x00, 0x00}, //m
            {0x11, 0x31, 0x00, 0x00}, //n
            {0x12, 0x44, 0x00, 0x00}, //o
            {0x13, 0x4D, 0x00, 0x00}, //p
            {0x14, 0x15, 0x00, 0x00}, //q
            {0x15, 0x2D, 0x00, 0x00}, //r
            {0x16, 0x1B, 0x00, 0x00}, //s
            {0x17, 0x2C, 0x00, 0x00}, //t
            {0x18, 0x3C, 0x00, 0x00}, //u
            {0x19, 0x2A, 0x00, 0x00}, //v
            {0x1A, 0x1D, 0x00, 0x00}, //w
            {0x1B, 0x22, 0x00, 0x00}, //x
            {0x1C, 0x35, 0x00, 0x00}, //y
            {0x1D, 0x1A, 0x00, 0x00}, //z

            {0x1E, 0x16, 0x00, 0x00}, //1
            {0x1F, 0x1E, 0x00, 0x00}, //2
            {0x20, 0x26, 0x00, 0x00}, //3
            {0x21, 0x25, 0x00, 0x00}, //4
            {0x22, 0x2E, 0x00, 0x00}, //5
            {0x23, 0x36, 0x00, 0x00}, //6
            {0x24, 0x3D, 0x00, 0x00}, //7
            {0x25, 0x3E, 0x00, 0x00}, //8
            {0x26, 0x46, 0x00, 0x00}, //9
            {0x27, 0x45, 0x00, 0x00}, //0

            {0x28, 0x5A, 0x00, 0x00}, //Enter
            {0x29, 0x76, 0x00, 0x00}, //Espace
            {0x2A, 0x66, 0x00, 0x00}, //Backspace
            {0x2B, 0x0D, 0x00, 0x00}, //Tab
            {0x2C, 0x29, 0x00, 0x00}, //Space

            {0x2D, 0x4E, 0x00, 0x00}, //-
            {0x2E, 0x55, 0x00, 0x00}, //=

            {0x2F, 0x54, 0x00, 0x00}, //[{
            {0x30, 0x5B, 0x00, 0x00}, //]}
            {0x31, 0x5D, 0x00, 0x00}, // \\ |
            {0x32, 0x61, 0x00, 0x00}, // Non-US # and \ (Macro)
            {0x33, 0x4C, 0x00, 0x00}, //;:
            {0x34, 0x52, 0x00, 0x00}, //'"
            {0x35, 0x0E, 0x00, 0x00}, // `~
            {0x36, 0x41, 0x00, 0x00}, //,<
            {0x37, 0x49, 0x00, 0x00}, //.>
            {0x38, 0x4A, 0x00, 0x00}, // /?
            {0x39, 0x58, 0x00, 0x00}, //Caps Lock

            {0x3A, 0x05, 0x00, 0x00}, //F1
            {0x3B, 0x06, 0x00, 0x00}, //F2
            {0x3C, 0x04, 0x00, 0x00}, //F3
            {0x3D, 0x0C, 0x00, 0x00}, //F4
            {0x3E, 0x03, 0x00, 0x00}, //F5
            {0x3F, 0x0B, 0x00, 0x00}, //F6
            {0x40, 0x83, 0x00, 0x00}, //F7
            {0x41, 0x0A, 0x00, 0x00}, //F8
            {0x42, 0x01, 0x00, 0x00}, //F9
            {0x43, 0x09, 0x00, 0x00}, //F10
            {0x44, 0x78, 0x00, 0x00}, //F11
            {0x45, 0x07, 0x00, 0x00}, //F12

            {0x46, 0xE0, 0x7C, 0x00}, //PrintScrean
            {0x47, 0x7E, 0x00, 0x00}, //Scroll Lock
            {0x48, 0xE1, 0x14, 0x77}, //Pause
            {0x49, 0xE0, 0x70, 0x00}, //Insert
            {0x4A, 0xE0, 0x6C, 0x00}, //Home
            {0x4B, 0xE0, 0x7D, 0x00}, //PageUp
            {0x4C, 0xE0, 0x71, 0x00}, //Delete Forward
            {0x4D, 0xE0, 0x69, 0x00}, //End
            {0x4E, 0xE0, 0x7A, 0x00}, //PageDown

            {0x4F, 0xE0, 0x74, 0x00}, //Right arrow
            {0x50, 0xE0, 0x6B, 0x00}, //Left arrow
            {0x51, 0xE0, 0x72, 0x00}, //Down arrow
            {0x52, 0xE0, 0x75, 0x00}, //Up arrow

            {0x53, 0x77, 0x00, 0x00}, //Keypad Num Lock
            {0x54, 0xE0, 0x4A, 0x00}, //Keypad /
            {0x55, 0x7C, 0x00, 0x00}, //Keypad *
            {0x56, 0x7B, 0x00, 0x00}, //Keypad -
            {0x57, 0x79, 0x00, 0x00}, //Keypad +
            {0x58, 0xE0, 0x5A, 0x00}, //Keypad ENTER

            {0x59, 0x69, 0x00, 0x00}, //Keypad 1
            {0x5A, 0x72, 0x00, 0x00}, //Keypad 2
            {0x5B, 0x7A, 0x00, 0x00}, //Keypad 3
            {0x5C, 0x6B, 0x00, 0x00}, //Keypad 4
            {0x5D, 0x73, 0x00, 0x00}, //Keypad 5
            {0x5E, 0x74, 0x00, 0x00}, //Keypad 6
            {0x5F, 0x6C, 0x00, 0x00}, //Keypad 7
            {0x60, 0x75, 0x00, 0x00}, //Keypad 8
            {0x61, 0x7D, 0x00, 0x00}, //Keypad 9
            {0x62, 0x70, 0x00, 0x00}, //Keypad 0
            {0x63, 0x70, 0x00, 0x00}, //Keypad .

            {0x65, 0xE0, 0x2F, 0x00}, //Menu

            {0xE0, 0x14, 0x00, 0x00}, //LeftControl
            {0xE1, 0x12, 0x00, 0x00}, //LeftShift
            {0xE2, 0x11, 0x00, 0x00}, //LeftAlt
            {0xE3, 0xE0, 0x1F, 0x00}, //LeftGUI (Windows)
            {0xE4, 0xE0, 0x14, 0x00}, //RightControl
            {0xE5, 0x59, 0x00, 0x00}, //RightShift
            {0xE6, 0xE0, 0x11, 0x00}, //RightAlt
            {0xE7, 0xE0, 0x27, 0x00}, //RightGUI (Windows)

            {0xFF, 0xFF, 0xFF, 0xFF}};

    uint8_t convert(const uint8_t key[4])
    {
        for (uint8_t i = 0; convert_table[i][0] != 0xFF; i++)
        {
            if (convert_table[i][1] == key[0] &&
                convert_table[i][2] == key[1] &&
                convert_table[i][3] == key[2])
                return convert_table[i][0];
        }
        return 0;
    }
} // namespace PS2ToHID

namespace KeyProcessor
{
    Data data;
    Data::Data()
    {
        for (uint8_t i = 0; i < 0xFF; i++)
            mode[i] = Mode::Standart;
    }

    bool command_mode = true;

    void RunCommand(uint8_t key, PS2Keyboard::Package::Status status)
    {
        uint16_t cn; //command number
        if (status == PS2Keyboard::Package::Status::Press)
        {
            cn = data.press_map[key];
        }
        else
        {
            cn = data.release_map[key];
        }

        while (data.commands[cn].action != Data::CommandData::Action::Break)
        {
            //keyboard
            if (data.commands[cn].action == Data::CommandData::Action::KeyboardPress)
            {
                keyboard.pressKeyCode(data.commands[cn].key_code);
            }
            else if (data.commands[cn].action == Data::CommandData::Action::KeyboardRelease)
            {
                keyboard.releaseKeyCode(data.commands[cn].key_code);
            }

            //consumer
            else if (data.commands[cn].action == Data::CommandData::Action::ConsumearPress)
            {
                consumer.press(data.commands[cn].key_code);
            }
            else if (data.commands[cn].action == Data::CommandData::Action::ConsumearRelease)
            {
                consumer.release();
            }

            //mouse
            else if (data.commands[cn].action == Data::CommandData::Action::MousePress)
            {
                mouse.press(data.commands[cn].key_code);
            }
            else if (data.commands[cn].action == Data::CommandData::Action::MouseRelease)
            {
                mouse.release(data.commands[cn].key_code);
            }

            cn++;
        }
        cserial.println();
        return;
    }
} // namespace KeyProcessor