
#include "inc.h"


// data size without start and end bytes
#define DATA_SIZE   23

// protocol configuration
#define NUMBER_OF_CHANNELS      18
#define NUMBER_OF_BITS          11
#define MAX_CHANNEL_VALUE       0x7FF   // 11 bit
#define DIG_CH0_MASK            0x40
#define DIG_CH1_MASK            0x80


// parce union
typedef union
{
    uint8_t arr8[DATA_SIZE];
    uint16_t arr16[DATA_SIZE/2];
}
parce_t;


// FSM state
typedef enum
{
    start,  // temporary buffer is empty
    part,   // we have a part of package yet
    full    // we have a full packet
}
parce_state_t;


/// function to proceed state and get full packet into the temporary buffer
parce_state_t parceFsm(parce_state_t state, uint8_t* input, int length);
/// function to decode full packet into data
void parceDecode(void);


/// temporary buffer
parce_t buf;


void parceSbus(uint8_t* input, int length)
{
    // FSM state
    static parce_state_t state = start;
    
    // proceed state and put full packet into the temporary buffer
    state = parceFsm(state, input, length);

    // if there is a full packet
    if (state == full) {

        // decode full packet
        parceDecode();

        sbus_st.sbusTrustFlag = 1;
    }

}


// function to proceed state and get full packet into the temporary buffer
parce_state_t parceFsm(parce_state_t state, uint8_t* input, int length)
{
    // position of current byte
    int input_pos;
    static int buf_pos = 0;

    input_pos = 0;
    
    switch (state)
    {
    case full:  // reset
        state = start;

    case start:
        // temporary buffer is empty
        while (input_pos < length) {

            if (input[input_pos] == SBUS_STARTBYTE) {
                // start of data packet
                state = part;
                input_pos++;
                break;
            }

            input_pos++;
        }

        // no start byte was found
        if (state == start)
            break;

        // if start byte was found then copy data to the buffer

    case part:
        // we have a part of package yet

        // copy data to the buffer
        while (input_pos < length) {

            buf.arr8[buf_pos] = input[input_pos];
            buf_pos++;
            input_pos++;

            // buffer is full
            if (buf_pos >= DATA_SIZE)
                break;
        }

        // if buffer is full but there are still bytes into input
        // then check if there is end byte in right position
        if ((buf_pos >= DATA_SIZE) && (input_pos < length)) {

            buf_pos = 0;
            if (input[input_pos] == SBUS_ENDBYTE)
                // we got full packet
                state = full;
            else
                // something is wrong so reset state
                state = start;
        }


    }

    return(state);
    
}

// function to decode full packet into data
void parceDecode(void)
{
    // offset of desired 11-bit value within 32 bit (two 16-bit elements)
    int offset = 0;
    // index of buffer element
    int index = 0;
    // parts of number
    uint16_t low, high;

    // analog channels
    for (int i = 0; i < (NUMBER_OF_CHANNELS-2); i++) {

        // low bits (from the current array element)
        low = buf.arr16[index];
        low >>= offset;

        // high bits (from the next array element)
        if (offset >= (16 - NUMBER_OF_BITS)) {

            // next array element
            index++;

            high = buf.arr16[index];
            high <<= (16 - offset);
        }
        else
            high = 0;

        // offset value for the next channel
        offset += NUMBER_OF_BITS;
        offset %= 16;

        // get value
        sbus_st.channel[i] = low | high;
        sbus_st.channel[i] &= MAX_CHANNEL_VALUE;
    }

    // digital channels
    // (two bits from the last byte)
    sbus_st.channel[NUMBER_OF_CHANNELS-2] =
            ((buf.arr8[DATA_SIZE-1] & DIG_CH0_MASK) != 0) ? MAX_CHANNEL_VALUE : 0;
    sbus_st.channel[NUMBER_OF_CHANNELS-1] =
            ((buf.arr8[DATA_SIZE-1] & DIG_CH1_MASK) != 0) ? MAX_CHANNEL_VALUE : 0;

}


