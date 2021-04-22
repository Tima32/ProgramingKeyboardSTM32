#include <Arduino.h>
#include "PS2Keyboard.hpp"
#include "Functions.hpp"

PS2Keyboard* ps2k = nullptr;
void KeyboardInterrupt()
{
    ps2k->interrupt();
}

PS2Keyboard::PS2Keyboard(uint8_t data_pin, uint8_t IRQ_pin):
    data_pin(data_pin), IRQ_pin(IRQ_pin), package_out({0}), package_new(false),
    mode(0), keyboard_byte_count(0), keyboard_byte_package(0),
    package({0}), package_size(1), package_cursor(0)
{
    if (ps2k)
    {
        DebugPrintLn("<PS2Keyboard>:Error: Only one keyboard host can exist.");
        return;
    }
    ps2k = this;
    pinMode(data_pin, INPUT);
    digitalWrite(data_pin, HIGH);
    attachInterrupt(IRQ_pin, KeyboardInterrupt, FALLING);
}
PS2Keyboard::Package PS2Keyboard::getPckage()
{
    package_new = false;
    return package_out;
}
bool PS2Keyboard::isNew()
{
    return package_new;
}

void PS2Keyboard::interrupt()
{
    if (mode)
    {
        //interruptSend();
    }
    else
    {
        interruptGet();
    }
    
}
void PS2Keyboard::interruptGet()
{
    static uint32_t old_millis = 0;
    uint32_t new_millis = millis();
    if (new_millis - old_millis > 1000 && new_millis < old_millis)
    {
        keyboard_byte_count = 0;
        keyboard_byte_package = 0;
    }
    old_millis = new_millis;

    if (0 < keyboard_byte_count && keyboard_byte_count < 10)
        keyboard_byte_package |= digitalRead(data_pin) << (keyboard_byte_count - 1);
    if (keyboard_byte_count == 10)
    {
        addToPackage();
        keyboard_byte_count = 0;
        keyboard_byte_package = 0;
        return;
    }
    keyboard_byte_count++;
}

void PS2Keyboard::addToPackage()
{
    if (keyboard_byte_package == 0xF0)
    {
        package.status = Package::Status::Release;
    }
    else if (keyboard_byte_package == 0xE0)
    {
        package_size += 1;
    }
    else if (keyboard_byte_package == 0xE1)
    {
        package_size += 2;
    }

    if (keyboard_byte_package != 0xF0)
    {
        package.key[package_cursor] = keyboard_byte_package;
        package_cursor++;
    }
    
    if (package_cursor == package_size)
    {
        package_out = package;
        package_new = true;

        package.key[0] = 0;
        package.key[1] = 0;
        package.key[2] = 0;
        package.status = Package::Status::Press;

        package_cursor = 0;
        package_size = 1;
    }
}