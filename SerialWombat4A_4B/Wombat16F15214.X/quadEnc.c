/*
Copyright 2020 Broadwell Consulting Inc.

Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR 
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
 * OTHER DEALINGS IN THE SOFTWARE.
*/

#include "serialWombat.h"
#include <stdint.h>

typedef struct quadEnc_n{
           uint8_t secondPin; 
           uint8_t debounceFrames;
           uint8_t debounceCount;
           uint8_t readState:1;
}quadEnc_t;

#define quadEnc  ((quadEnc_t*) CurrentPinRegister)

void init_quadEnc(void)
{
    
    switch(Rxbuffer[0])
    {
        case CONFIGURE_CHANNEL_MODE_0:

        {
           
            
         CurrentPinRegister->generic.mode =PIN_MODE_QUADRATURE_ENC;
        SetMode(quadEnc->secondPin, PIN_MODE_CONTROLLED);
        CurrentPinRegister->generic.buffer = 0; 
        quadEnc->debounceFrames = Rxbuffer[3]; 
        quadEnc->debounceCount = 0;
        quadEnc->secondPin = Rxbuffer[5] ;
        quadEnc->readState = Rxbuffer[6] & 0x01;
        CurrentPinInput();
        SetPin(quadEnc->secondPin, DIGITAL_INPUT);
        switch (Rxbuffer[7]) 
	{
        case 0:
        {
            
            CurrentPinNoPullUp();
            PinNoPullUp(quadEnc->secondPin);
        }
        break;
        
        case 1:
        {			
                    CurrentPinPullUp();
                    PinPullUp(quadEnc->secondPin);	
        }
        break;
        
       
            
	}        
        if (quadEnc->readState)
        {
           WP_IOCP |= CurrentPinMask;
           WP_IOCN &= CurrentPinMaskInverted; 
        }
        else
        {
             WP_IOCN |= CurrentPinMask;
             WP_IOCP &= CurrentPinMaskInverted; 
        }
        PIE0bits.IOCIE = 1;
	
        
        }
        
    
    break;
    
    }
} 

extern uint8_t copy_IOC_PortBuffer[IOC_BUFFER_SIZE];
void update_quadEnc(void)
{

    
    if (quadEnc->debounceCount != 0)
    {
        --quadEnc->debounceCount;
        return;
    }
    for (uint8_t i = 0; i != IOC_BUFFER_SIZE; ++i)
    {
        uint8_t currentInput;
        currentInput = copy_IOC_PortBuffer[i];
        if (currentInput & 0x80u)
        {
            //Not set.
            continue;
        }
        if (quadEnc->readState)
        {
            if (currentInput & CurrentPinMask)
            {
                 if (currentInput & PinMaskArray[quadEnc->secondPin])
                {
                   CurrentPinRegister->generic.buffer++;
                }
                else
                {
                     CurrentPinRegister->generic.buffer--;
                }
            }
            else
            {
               // Line is low.  Ignore           
            }
        }
        else
        {
            if (currentInput & CurrentPinMask)
            {
                // Line is high.  Ignore
            }
            else
            {
               
                if (currentInput & PinMaskArray[quadEnc->secondPin])
                {
                   CurrentPinRegister->generic.buffer++;
                }
                else
                {
                     CurrentPinRegister->generic.buffer--;
                }
            }
            
        }
        if (quadEnc->debounceFrames != 0)
        {
        quadEnc->debounceCount = quadEnc->debounceFrames;
        break;
        }
    }
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
   int vpin_data_quadEnc = 0;
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
        vpin_data_quadEnc = 0;
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
