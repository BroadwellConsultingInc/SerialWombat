
extern void error(void);
__attribute__((__weak__)) void  init_quadEnc(void);
void  init_quadEnc()
{
	error();
}

void __attribute__((weak)) update_quadEnc()
{
}

void  __attribute__((weak)) initServoSimple()
{
	error();
}

void __attribute__((weak)) initServo()
{
	error();
}

void __attribute__((weak)) updateServo()
{
}

void __attribute__((weak)) initPWM()
{
	error();
}

void __attribute__((weak)) updatePWM()
{
}