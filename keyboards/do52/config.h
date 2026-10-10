#pragma once

/* USB is always connected to the right half (TrackPoint side) */
#define MASTER_RIGHT

/* TrackPoint (PS/2): CLK=B1(PCINT1), DATA=B2 */
#ifdef PS2_DRIVER_INTERRUPT
#    define PS2_CLOCK_PIN B1
#    define PS2_DATA_PIN B2

#    define PS2_INT_INIT()            \
        do {                          \
            PCICR |= (1 << PCIE0);    \
        } while (0)
#    define PS2_INT_ON()               \
        do {                           \
            PCMSK0 |= (1 << PCINT1);   \
        } while (0)
#    define PS2_INT_OFF()              \
        do {                           \
            PCMSK0 &= ~(1 << PCINT1);  \
        } while (0)
#    define PS2_INT_VECT PCINT0_vect
#endif

#define PS2_MOUSE_USE_REMOTE_MODE
#define PS2_MOUSE_ROTATE 90
