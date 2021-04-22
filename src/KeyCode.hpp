#pragma once
#include <Arduino.h>
#include "PS2Keyboard.hpp"

namespace PS2ToHID
{
    // {HID_code, PS2_byte0, PS2_byte1, PS2_byte2}
    extern const uint8_t convert_table[][4];

    // 0x00 not found
    extern uint8_t convert(const uint8_t key[3]);
} // namespace PS2ToHID

namespace KeyProcessor
{
    struct Data
    {
        Data();

        enum Mode : uint8_t
        {
            Ignore =     0b0000, //0x0
            Standart =   0b0001, //0x1
            Command =    0b0010, //0x2
            Send =       0b0100, //0x4
            SwitchMode = 0b1000, //0x8 // Switch between standard and programmable mode. 
        };
        struct CommandData
        {
            enum Action : uint8_t
            {
                Break,
                KeyboardPress,
                KeyboardRelease,
                ConsumearPress,
                ConsumearRelease,
                MousePress,
                MouseRelease
            };

            Action action;
            uint8_t key_code;
        };

        Mode mode[0xFF];
        uint16_t press_map[0xFF];
        uint16_t release_map[0xFF];
        CommandData commands[4096];
    };
    extern Data data;
    extern bool command_mode;

    extern void RunCommand(uint8_t key, PS2Keyboard::Package::Status status);
} // namespace KeyProcessor