/******************************************************************************/
/**
*      @file : ringBuffer.h
*   @version : 0
*      @date : 22 December 2021
*    @author : J Cowley
*
*******************************************************************************/

#ifndef RING_BUFFER_H
#define RING_BUFFER_H

/*******************************    LIBRARIES   *******************************/

#include "msp.h"
#include <stddef.h>


typedef struct{
    size_t size_elem;
    size_t num_elem;
    void *buffer;
} rb_config_t;


/*******************************    FUNCTIONS   *******************************/

int ringBuffer_Init(rb_config_t *config);


//------- ringBuffer_write() -------------------
// puts a character in to the ring buffer
// returns 0 if successful, -1 otherwise
int ringBuffer_write(const void *data);



//------- ringBuffer_read() -------------------
// reads a character from the ring buffer
// returns 0 if successful, -1 otherwise
int ringBuffer_read(void *data);



//------- ringBuffer_available() -------------------
// returns the number of bytes in the ring buffer
int ringBuffer_available();


#endif /* RING_BUFFER_H */

