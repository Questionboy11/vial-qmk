#pragma once

#define EE_HANDS

/* TrackPoint (PS/2): CLK=D1(INT1), DATA=D0 */
#ifdef PS2_DRIVER_INTERRUPT
#    define PS2_CLOCK_PIN D1
#    define PS2_DATA_PIN D0

#    define PS2_INT_INIT()                         \
        do {                                       \
            EICRA |= ((1 << ISC11) | (0 << ISC10)); \
        } while (0)
#    define PS2_INT_ON()          \
        do {                      \
            EIMSK |= (1 << INT1); \
        } while (0)
#    define PS2_INT_OFF()          \
        do {                       \
            EIMSK &= ~(1 << INT1); \
        } while (0)
#    define PS2_INT_VECT INT1_vect
#endif

#define PS2_MOUSE_USE_REMOTE_MODE
