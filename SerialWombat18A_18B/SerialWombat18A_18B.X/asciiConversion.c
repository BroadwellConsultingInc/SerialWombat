#include <stdint.h>

uint8_t ascii_to_val(uint8_t a)
{
	if ( a <= '0')
        {
		return (0);
        }
        if ( a <='9')
        {
		return ( a - '0');
        }
        if ( a >= 'A' && a <= 'F')
        {
                return ((a + 10) - 'A');
        }
        if ( a >= 'a' && a <= 'f')
        {
                return ((a + 10) - 'a');
        }
        return (0);
}
void uint16ToAscii5(uint16_t val, uint8_t* buffer)
{
	*buffer = val / 10000;
	val -= *buffer * 10000;
	*buffer += '0';
	++buffer;

	*buffer = val / 1000;
	val -= *buffer * 1000;
	*buffer += '0';
	++buffer;

	*buffer = (uint8_t)(val / 100);
	val -= *buffer * 100;
	*buffer += '0';
	++buffer;

	*buffer = (uint8_t)(val / 10);
	val -= *buffer * 10;
	*buffer += '0';
	++buffer;

	*buffer = (uint8_t)(val+ '0');
}

void uint16ToAscii5NoHWMath(uint16_t val, uint8_t* buffer)
{
    
    *buffer = '0';
    while (val >= 10000)
    {
        val -= 10000;
        ++*buffer;
    }
	++ buffer;
    *buffer = '0';
    while (val >= 1000)
    {
        val -= 1000;
        ++*buffer;
    }
    ++ buffer;
    *buffer = '0';
    while (val >= 100)
    {
        val -= 100;
        ++*buffer;
    }
    ++ buffer;
    *buffer = '0';
    while (val >= 10)
    {
        val -= 10;
        ++*buffer;
    }
    ++ buffer;
    *buffer = (uint8_t)('0' + val);
}
