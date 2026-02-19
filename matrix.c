/*
 * File:   matrix_key.c
 * Author: User
 *
 * Created on 18 December, 2024, 6:55 PM
 */


#include <xc.h>

void init_matrix_keypad()
{
    TRISB = 0X1E;
    RB0 = 0;
    RBPU = 0;
    RB5 = RB6 = RB7 = 1;
}
unsigned char scan_key(void)
{
    RB5 = 0;
    RB6 = 1;
    RB7 = 1;

    if (RB1 == 0)
    {
        return 1;
    }
    else if (RB2 == 0)
    {
        return 4;
    }
    else if (RB3 == 0)
    {
        return 7;
    }
    else if (RB4 == 0)
    {
        return 10;
    }
    RB5 = 1;
    RB6 = 0;
    RB7 = 1;
    if (RB1 == 0)
    {
        return 2;
    }
    else if (RB2 == 0)
    {
        return 5;
    }
    else if (RB3 == 0)
    {
        return 8;
    }
    else if (RB4 == 0)
    {
        return 11;
    }

    RB5 = 1;
    RB6 = 1;
    RB7 = 0;
    RB7 = 0;

    if (RB1 == 0)
    {
        return 3;
    }
    else if (RB2 == 0)
    {
        return 6;
    }
    else if (RB3 == 0)
    {
        return 9;
    }
    else if (RB4 == 0)
    {
        return 12;
    }
    return 0xFF;
}

unsigned char read_switches(unsigned char detection_type)
{
    static unsigned char once = 1, key;

    key = scan_key();
    if (detection_type == 1)
    {
        if (key != 0xFF && once)
        {
            once = 0;
            return key;
        }
        else if (key == 0xFF)
        {
            once = 1;
        }
        return 0xFF;
    }
    else if (detection_type == 0 && key != 0xFF)
    {
        return key;
    }
     return 0xFF;
}


