#ifndef COMPILING_FIRMWARE
	#include <stdio.h>
#endif
#include "types.h"
#include "utilities.h"




// rxbuffer[2] == INPUT_TRANSITION_COUNTER 
// rxbuffer[3] == debounce frames high
// rxbuffer[4] == debounce frames low
// rxbuffer[5] == 0 = Count Transition high to low 
//                1 = Count Transition low to high 
//                2 = Count both transitions 
// rxbuffer[6,7]  max value

void init_counter(void)
{
	if (rxbuffer[0] == 200)
	{
      //TODO  vpin_input();
	txbuffer[3] = HIGH_BYTE_16(tp->generic.buffer);
	txbuffer[4] = LOW_BYTE_16(tp->generic.buffer);
        tp->generic.buffer = 0; 
	ASSIGN_RXBUFFER16(tp->counter.debouncesamples,3); 
	tp->counter.debouncecounter = 0;
        tp->counter.mode = rxbuffer[5] & 0x03;  // If 1 bit is set, ignore high to low.  If 2 bit is set, ignore low to high
	ASSIGN_RXBUFFER16(tp->counter.max,6);
	tp->counter.currentState = vpin_read();
	tp->counter.increment = 1;
	}
	if (rxbuffer[0] == 201)
	{
		ASSIGN_RXBUFFER16(tp->counter.increment,3); 

	}
}

void update_counter(void)
{
	uint8_t lastDMA = tp->counter.lastNextDMA;
	uint8_t currentState = tp->counter.currentState;
	uint16_t bitmap = vpinBitmap();
	uint16_t counter = tp->generic.buffer;
	switch(vpinPort())
	{
		case 0:  // Port A
		{
			//TODO add port a
		}
		break;

		case 1:  // PORT B
		{
			while (DMACNT3 == 0); // Wait for reload
			
			int currentNextDMALocation = SIZE_OF_DMA_ARRAY - DMACNT3 ; // The next DMA location that will be written
			if (currentNextDMALocation < lastDMA)
			{
				// DMA rolled over.  Finish the end.
				for (;lastDMA < SIZE_OF_DMA_ARRAY; ++lastDMA)
				{
					//Process data
					if (InputArrayB[lastDMA] & bitmap)
					{
						//Input High
						if (!currentState)
						{
							//Was low!
							++ tp->counter.debouncecounter;
							if (tp->counter.debouncecounter > tp->counter.debouncesamples)
							{	
								tp->counter.debouncecounter = 0;
								currentState = 1;

								if (tp->counter.mode & 0x01)
								{
									continue;
								}
								
								uint32_t sum;
								sum = counter + tp->counter.increment;
								if (tp->counter.max > 0 && sum > tp->counter.max )
								{
									sum = tp->counter.max ;
								}
								counter = (uint16_t) sum;
							}
						
						}
						else
						{
							tp->counter.debouncecounter = 0;
							// Stayed the same.  Do nothing
                            
						}

					}
					else
					{

						//Input Low
						if (currentState)
						{
							++ tp->counter.debouncecounter;
							if (tp->counter.debouncecounter > tp->counter.debouncesamples)
							{	
								tp->counter.debouncecounter = 0;
								currentState = 0;

								if (tp->counter.mode & 0x02)
								{
									continue;
								}

								uint32_t sum;
								sum = counter + tp->counter.increment;
								if (tp->counter.max  > 0 && sum > tp->counter.max )
								{
									sum = tp->counter.max ;
								}
								counter = (uint16_t) sum;
							}
						}
						else
						{
							tp->counter.debouncecounter = 0;
							// Stayed the same.  Do nothing
						}
					}
				}
				lastDMA = 0;
			}
			for (; lastDMA < currentNextDMALocation; ++lastDMA)
			{
					//Process data
					if (InputArrayB[lastDMA] & bitmap)
					{
						//Input High
						if (!currentState)
						{
							//Was low!
							++ tp->counter.debouncecounter;
							if (tp->counter.debouncecounter > tp->counter.debouncesamples)
							{	
								tp->counter.debouncecounter = 0;
								currentState = 1;

								if (tp->counter.mode & 0x01)
								{
									continue;
								}
								
								uint32_t sum;
								sum = counter + tp->counter.increment;
								if (tp->counter.max > 0 && sum > tp->counter.max )
								{
									sum = tp->counter.max ;
								}
								counter = (uint16_t) sum;
							}
						
						}
						else
						{
							tp->counter.debouncecounter = 0;
							// Stayed the same.  Do nothing
                            
						}

					}
					else
					{

						//Input Low
						if (currentState)
						{
							++ tp->counter.debouncecounter;
							if (tp->counter.debouncecounter > tp->counter.debouncesamples)
							{	
								tp->counter.debouncecounter = 0;
								currentState = 0;

								if (tp->counter.mode & 0x02)
								{
									continue;
								}

								uint32_t sum;
								sum = counter + tp->counter.increment;
								if (tp->counter.max  > 0 && sum > tp->counter.max )
								{
									sum = tp->counter.max ;
								}
								counter = (uint16_t) sum;
							}
						}
						else
						{
							tp->counter.debouncecounter = 0;
							// Stayed the same.  Do nothing
						}
					}
			}
		}
		break;


	}
	tp->counter.currentState = currentState ;
	tp->generic.buffer = counter;
	tp->counter.lastNextDMA = lastDMA;
}



/////////////////////////////////////////////////////////////////////////
//  CODE FROM HERE DOWN IS TESTING CODE FOR USE ON PC, not FIRMWARE

#ifdef TEST_COUNTER 
#define NUM_OF_DATA_INDEX 6

// Test 0, ___---___, count every change, 0 debounce
int const test0_data[] = {0,100,
                          1,100,
			  0,100};
//debounce frames, mode, freeze, max, initial_val,result, # of data
int const test0_init[] = {0,2,0,65535,0,2,sizeof(test0_data) / 8 };

// Test 1, _100_-100-_100_, count rising, 0 debounce

int const test1_data[] = {0,100,
                          1,100,
			  0,100};
//debounce frames, mode, freeze, max, result, # of data
int const test1_init[] = {0,1,0,65535,0,1,sizeof(test1_data) / 8 };

// Test 2, _100_-10-_100_, count rising, 10 debounce

int const test2_data[] = {0,100,
                          1,10,
			  0,100};
//debounce frames, mode, freeze, max, result, # of data
int const test2_init[] = {10, //Debounce frames
   			1,   // MODE
			0, //Freeze
			65535,//  Max
			0, //Initial_val
			1, //EXPECTED result
			sizeof(test2_data) / 8 };

// Test 3, _100_-9-_100_, count rising, 10 debounce

int const test3_data[] = {0,100,
                          1,9,
			  0,100};
//debounce frames, mode, freeze, max, result, # of data
int const test3_init[] = {10, //Debounce frames
   			1,   // MODE
			0, //Freeze
			65535,//  Max
			0, //Initial_val
			0, //EXPECTED result
			sizeof(test3_data) / 8 };
// Test 4, _100_-9-_100_, count falling, 10 debounce

int const test4_data[] = {0,100,
                          1,9,
			  0,100};
//debounce frames, mode, freeze, max, result, # of data
int const test4_init[] = {10, //Debounce frames
   			0,   // MODE
			0, //Freeze
			65535,//  Max
			0, //Initial_val
			0, //EXPECTED result
			sizeof(test4_data) / 8 };

// Test 5, _1_-1-_1_-1-, count rising, 0 debounce

int const test5_data[] = {0,1,
                          1,1,
                          0,1,
			  1,1};
//debounce frames, mode, freeze, max, result, # of data
int const test5_init[] = {0, //Debounce frames
   			0,   // MODE
			0, //Freeze
			65535,//  Max
			0, //Initial_val
			2, //EXPECTED result
			sizeof(test5_data) / 8 };

// Test 6, _1_-1-_1_-1-, count falling, 0 debounce

int const test6_data[] = {0,1,
                          1,1,
                          0,1,
			  1,1};

int const test6_init[] = {0, //Debounce frames
   			1,   // MODE
			0, //Freeze
			65535,//  Max
			0, //Initial_val
			1, //EXPECTED result
			sizeof(test6_data) / 8 };

// Test 7, _1_-1-_1_-1-, count both, 0 debounce

int const test7_data[] = {0,1,
                          1,1,
                          0,1,
			  1,1};

int const test7_init[] = {0, //Debounce frames
   			2,   // MODE
			0, //Freeze
			65535,//  Max
			0, //Initial_val
			3, //EXPECTED result
			sizeof(test7_data) / 8 };

// Test 8, _1_-1-_1_-1-, count both, 0 debounce, rollover

int const test8_data[] = {0,1,
                          1,1,
                          0,1,
			  1,1};

int const test8_init[] = {0, //Debounce frames
   			2,   // MODE
			0, //Freeze
			65535,//  Max
			65535, //Initial_val
			2, //EXPECTED result
			sizeof(test8_data) / 8 };

// Test 9, _1_-1-_1_-1-, count both, 0 debounce, rollover, freeze

int const test9_data[] = {0,1,
                          1,1,
                          0,1,
			  1,1};

int const test9_init[] = {0, //Debounce frames
   			2,   // MODE
			1, //Freeze
			65535,//  Max
			65534, //Initial_val
			65535, //EXPECTED result
			sizeof(test9_data) / 8 };

int const*  test_vectors[]= {test0_init,test0_data,
                             test1_init,test1_data,
                             test2_init,test2_data,
                             test3_init,test3_data,
                             test4_init,test4_data,
                             test5_init,test5_data,
                             test6_init,test6_data,
                             test7_init,test7_data,
                             test8_init,test8_data,
                             test9_init,test9_data
                            };

#define NUMBER_OF_TESTS (sizeof(test_vectors) / 8) 
   int data_point;
   int test = 0;
   int iteration = 0;
   int vpin_data_counter = 0;
   int const* vpin_data_vector;
   uint8 test_pin;

int main(void)
{
   int i;
   int const* init_data; 
   int data_points;
   int returnval = 0;

   test_pin = 2;
   system_init();

   for (test = 0;test < NUMBER_OF_TESTS; ++test)
   {
      vpin_data_vector = test_vectors[test * 2 + 1];
      vpin_data_counter = 0;
      init_data = test_vectors[test *2];
      data_points = init_data[NUM_OF_DATA_INDEX]; 
     
      rxbuffer[0] = CONFIGURE_CHANNEL_MODE_0;
      rxbuffer[1] = test_pin; 
      rxbuffer[2] = PIN_MODE_COUNTER;

      rxbuffer[3] = init_data[0]/256;
      rxbuffer[4] = init_data[0]%256;

      rxbuffer[5] = init_data[1];
      if (init_data[2])
      {
	 rxbuffer[5] |= 0x10;
      }
      rxbuffer[6] = init_data[3]/256;
      rxbuffer[7] = init_data[3]%256;
      set_pin(map_pin(test_pin),vpin_data_vector[0]);

      process_rxbuffer();


      set_buffer(map_pin(test_pin), init_data[4]);
      for (data_point = 0; data_point <  data_points; ++ data_point)
      {
	 for (iteration = 0; iteration < vpin_data_vector[data_point * 2 + 1]; ++iteration)
	 {
	    set_pin(map_pin(test_pin),vpin_data_vector[data_point * 2]);  
		 process_pins();
	 }


      }
	 if (get_buffer(map_pin(test_pin)) == init_data[5])
	 {
	    printf ("Test %d passed\n", test);
	 }
	 else
	 {
	    printf("Test %d expected %d, got %d\n",test, init_data[5],get_buffer(map_pin(test_pin)) );
	    returnval = 1 ;
	 }


   }
   return (returnval);
}
#endif
