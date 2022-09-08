/******************************************************************************/
/**
*      @file : iBUS.c
*   @version : 0
*      @date : 23 December 2021
*    @author : J Cowley
*
*******************************************************************************/
#include "CLK.h"  // for millis()
#include "iBUS.h"

#define PROTOCOL_LENGTH   0x20
#define PROTOCOL_OVERHEAD 3
#define PROTOCOL_TIMEGAP  3
#define PROTOCOL_CHANNELS 10
#define PROTOCOL_CMD40    0x40

uint8_t i = 0;

enum State{GET_LENGTH, GET_DATA, GET_CHKSUML, GET_CHKSUMH, DISCARD};

typedef struct {
    uint8_t state;
    uint32_t last;
    uint8_t buffer[PROTOCOL_LENGTH];
    uint8_t ptr;
    uint8_t len;
    uint16_t channel[PROTOCOL_CHANNELS];
    uint16_t chksum;
    uint8_t chksuml;

} iBUS_t;

iBUS_t iBUS;


//-------------- iBUS_Init() --------------------------------------
void iBUS_Init(void){
    iBUS.state = DISCARD;
    iBUS.last = millis();
    iBUS.ptr = 0;
    iBUS.len = 0;
    iBUS.chksum = 0;
    iBUS.chksuml = 0;
}

//-------------- iBUS_loop() --------------------------------------
void iBUS_loop(void){
    while (ringBuffer_available() > 0)          //check to see how many bytes are in the RX buffer
    {
        uint32_t now = millis();                // get a time stamp in milliseconds

        if(now - iBUS.last > PROTOCOL_TIMEGAP)  // check to see if now - last is >= 3 ms // Packets are received very ~7ms so use ~half that for the gap
        {
            iBUS.state = GET_LENGTH;
        }

        iBUS.last = now;                        // set up for next loop

        uint8_t v = UART_getchar();             // get a byte from the RX buffer

        switch(iBUS.state)
        {
        case GET_LENGTH:
            if(v <= PROTOCOL_LENGTH)            // first byte of the message is 0x20 == length of the message
            {
                iBUS.ptr = 0;                   // set ptr to beginning of data buffer
                iBUS.len = v - PROTOCOL_OVERHEAD;
                iBUS.chksum = 0xFFFF - v;       // initialize checksum
                iBUS.state = GET_DATA;
            }
            else{
                iBUS.state = DISCARD;
            }
            break;

        case GET_DATA:
            iBUS.buffer[iBUS.ptr++] = v;         // save the byte in the buffer and then increment ptr?
            iBUS.chksum -= v;                    // update checksum
            if(iBUS.ptr == iBUS.len){            // if we've finished collecting all the bytes...
                iBUS.state = GET_CHKSUML;
            }
            break;

        case GET_CHKSUML:
            iBUS.chksuml = v;                    // grab the next byte and store it in chksuml
            iBUS.state = GET_CHKSUMH;
            break;

        case GET_CHKSUMH:

            // Validate checksum
            if(iBUS.chksum == (uint16_t)((v << 8) + iBUS.chksuml)) //v now = checksum high, shifting it right by 8 bits puts it in the upper byte
            {
                // Execute command - we only know command 0x40 (extra validation)
                switch (iBUS.buffer[0]){
                case PROTOCOL_CMD40:
                    // Valid - extract channel data
                    for(i = 1; i < PROTOCOL_CHANNELS * 2 + 1; i+= 2){
                        iBUS.channel[i/2] = iBUS.buffer[i] | (iBUS.buffer[i+1] << 8); // extract little endian data from buffer
                    }
                    break;


                default:
                    break;
                }
            }
            iBUS.state = DISCARD;
            break;


        case DISCARD:
        default:
            break;
        }
    }

}


uint16_t iBUS_readChannel(uint8_t channelNum){
    if(channelNum < PROTOCOL_CHANNELS){
        return iBUS.channel[channelNum];
    }
    else{
        return 0;
    }
}
