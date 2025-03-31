

#define NUMBER_OF_PULSES 16
typedef struct ppm_n{
inputProcess_t inputProcess;
	uint8_t icResource;
	uint16_t data[NUMBER_OF_PULSES];
	uint8_t pulseToPinMapping[8];
	uint16_t trainCounter;
	uint16_t dataI;
	uint16_t trainSeparation;
	uint16_t pulsesExpected;
	uint16_t minimumDuration;
	uint16_t maximumDuration;
	uint8_t pulseAfterSeparation:1;  // 1 = Pulse immediately after separation is measured.  0 = pulse immediately after separation is spacer
}ppm_t;


void initPPM()
{
	ppm_t* ppm = (ppm_t*)CurrentPinRegister;
    if (Rxbuffer[0] != CONFIGURE_CHANNEL_MODE_0 && CurrentPinRegister->generic.mode != PIN_MODE_PPM)
	{
		error(SW_ERROR_PIN_CONFIG_WRONG_ORDER);
		return;
	}
    BUILD_BUG_ON( sizeof(ppm_t) >  BYTES_PER_PIN_REGISTER);   
	switch (Rxbuffer[0])
	{
		case CONFIGURE_CHANNEL_MODE_0:
		{
			CurrentPinRegister->generic.mode = PIN_MODE_PPM;
			ppm->icResource = timingResourceInputCaptureClaim(TIMING_RESOURCE_ANY_HARDWARE_IC);
			ppm->dataI = 0;
			ppm->trainCounter = 0;
			int i;
			for (i = 0; i < NUMBER_OF_PULSES; ++i)
			{
				ppm->data[i] = 0;
			}

			for (i = 0; i < 8; ++i)
			{
				ppm->pulseToPinMapping[i] = 255;
			}
			ppm->trainSeparation = RXBUFFER16(3);
			ppm->pulsesExpected =  Rxbuffer[5];
			ppm->pulseAfterSeparation = Rxbuffer[6];
			ppm_>minimumDuration = 500;
			ppm_>maximumDuration = 1500;
inputProcessInit(&ppm_->inputProcess);
		}
		break;
		case CONFIGURE_CHANNEL_MODE_1:
		{
			ppm_>minimumDuration = RXBUFFER16(3);
			ppm_>maximumDuration = RXBUFFER16(5);
		}
		break;
		case CONFIGURE_CHANNEL_MODE_2:
		{
			//Set up pin mapping for virtual pins
		}
		break;
case CONFIGURE_CHANNEL_MODE_INPUT_PROCESSING:
			{
				inputProcessCommProcess(&pulseTimer->inputProcess);
			}
			break;
		default:
			{
				error(SW_ERROR_INVALID_COMMAND);      
			}
			break;
	}

}

void ppmUpdate()
{
	ppm_t* ppm = (ppm_t*)CurrentPinRegister;
	uint8_t transitioncount = 0;
	// Add your application code
	while (!IC1_IsCaptureBufferEmpty() && transitioncount < 5)
	{
		++ transitioncount;
		uint16_t d = IC1_CaptureDataRead();
		uint16_t t = d;
		d = d - ppm_last;
		ppm_last = t;
		d*= 4;
		if (d < 450) continue;
		if (d > ppm->trainSeparation)
		{
			ppm->dataI = 0;
		}
		ppm->data[ppm->dataI] = d ;
		++ppm->dataI;
		if (ppm->dataI >= pulsesExpected)
		{
			++ppm->trainCounter;
			ppm->dataI = 0;

			int i;
			if (pulseAfterSeparation)
			{
				i = 1;
			}
			else
			{
				i = 2;
			}
			for (; i < pulsesExpected; i+= 2)
			{
				if (pulseToPinMapping[i/2] == 255)
				{
					continue;
				}
				uint32_t pulse = ppm->data[i];
				if (pulse < ppm->minimumDuration)
				{
					pulse = 0;
				}
				else if (pulse > ppm->maximumDuration)
				{
					pulse = 65535;
				}
				else
				{
					pulse = (pulse - ppm->minimumDuration) * 65536 / (ppm->maximumDuration - ppm->minimumDuration);
				}

				setVirtualPinHardware(pulseToPinMapping[i/2],pulse);
			}

		}
	}
}

