#include "types.h"
#include "utilities.h"
#pragma code APPLICATION




void init_pwm_follow_direct()
{ 
        uint16 temp16;
	tp->pwm_follow_direct.commandpin = rxbuffer[3];
	
	tp->generic.buffer = RXBUFFER16(6);
        temp16 = get_buffer(tp->pwm_follow_direct.commandpin); 
	tp->pwm_follow_direct.offset = 0;
	tp->pwm_follow_direct.scalar = 256;
	tp->pwm_follow_direct.samplecounter = 0 ;
	tp->pwm_follow_direct.sampletime = 0;

	if (tp->generic.mode == PIN_MODE_ANALOG_OUT_FOLLOW)
	{
			CVRCON = 0x00C0 | (temp16 >> 11);
	}

	if (tp->generic.mode == PIN_MODE_PWM_FOLLOW_DIRECT)
	{
		pin_low(virtual_pin);
        tp->pwm_follow_direct.pwmPeriod = RXBUFFER16(4);
        tp->pulse_output.lastDMA = 0;
	}

}

void init_pwm_follow_direct1()
{
	tp->pwm_follow_direct.commandpin = 255;
	tp->pwm_follow_direct.sampletime = RXBUFFER16(3);
	tp->pwm_follow_direct.scalar = RXBUFFER16(5);
}

void init_pwm_follow_direct2()
{
	//TODO not tested
	tp->generic.buffer = 0;
	tp->pwm_follow_direct.commandpin = rxbuffer[3];
	ASSIGN_RXBUFFER16(tp->pwm_follow_direct.offset,4);
}
void update_pwm_follow_direct(void)
{
	if (tp->pwm_follow_direct.commandpin == 255)
	{
		return;
	}
	if (tp->pwm_follow_direct.samplecounter)
	{
		--tp->pwm_follow_direct.samplecounter;
	}
	else
	{
		uint32_t temp32;
		tp->pwm_follow_direct.samplecounter = tp->pwm_follow_direct.sampletime;
		temp32 = get_buffer(tp->pwm_follow_direct.commandpin);
		temp32 *= tp->pwm_follow_direct.scalar;
		temp32 >>=8;
		int32_t stemp32 = temp32;
		stemp32 += tp->pwm_follow_direct.offset;
		if (stemp32 > 65535)
		{
			stemp32 = 65535;
		}
		else if (stemp32 < 0)
		{
			stemp32 = 0;
		}
		if (tp->generic.mode == PIN_MODE_PWM_FOLLOW_DIRECT)
		{
			tp->pulse_output.highReload = (((uint32_t) stemp32 * tp->pwm_follow_direct.pwmPeriod) >> 16);
			tp->pulse_output.lowReload = tp->pwm_follow_direct.pwmPeriod - tp->pulse_output.highReload;
		}
		else if (tp->generic.mode == PIN_MODE_ANALOG_OUT_FOLLOW)
		{
			CVRCON = 0x00C0 | (((uint16_t)stemp32) >> 11);
		}

	}
	if (tp->generic.mode == PIN_MODE_PWM_FOLLOW_DIRECT)
	{
	updatePulse(virtual_pin);
	}
}
