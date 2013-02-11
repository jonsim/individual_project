#include "Common.h"


sint8_t make_sint8_t (const uint8_t b)
{
    return (b - 0xFF);
}


uint16_t make_uint16_t (const uint8_t bh, const uint8_t bl)
{
    uint16_t r = (bh << 8) + bl;
    return r;
}


sint16_t make_sint16_t (const uint8_t bh, const uint8_t bl)
{
    sint16_t r = ((bh << 8) + bl) - 0xFFFF;
    return r;
}


void msleep (const uint32_t msec)
{
    usleep(msec * 1000);
}


int _kbhit (void)
{
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}
