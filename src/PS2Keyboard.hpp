#pragma once
#include "main.hpp"

class PS2Keyboard
{
public:
    struct Package
    {
        enum class Status: uint8_t
        {
            Release,
            Press
        };

        uint8_t key[3];
        Status status;
    };

    PS2Keyboard(uint8_t data_pin, uint8_t IRQ_pin);
    Package getPckage();
    bool isNew();
    //void sendPackage();

private:
    const uint8_t data_pin;
    const uint8_t IRQ_pin;
    Package package_out;
    bool package_new;

    volatile bool mode;//0-get 1-send
    volatile uint8_t keyboard_byte_count;
    volatile uint8_t keyboard_byte_package;
    void interrupt();
    void interruptGet();
    
    Package package;
    volatile uint8_t package_size;
    volatile uint8_t package_cursor;
    void addToPackage();

    friend void KeyboardInterrupt();
};