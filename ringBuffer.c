/******************************************************************************/
/**
*      @file : ringBuffer.c
*   @version : 0
*      @date : 22 December 2021
*    @author : J Cowley
*
*******************************************************************************/

#include "ringBuffer.h"

struct ring_buffer
{
    size_t size_elem;
    size_t num_elem;
    uint8_t *buf;
    volatile size_t head;
    volatile size_t tail;

};

static struct ring_buffer rb;

static int ringBuffer_full(struct ring_buffer *rb);
static int ringBuffer_empty(struct ring_buffer *rb);


//---------------- ringBuffer_Init() -----------------
int ringBuffer_Init(rb_config_t *attr){
    int err = -1;

    if((attr->buffer != NULL) && (attr->size_elem > 0)){

        /* Check that buffer size is a pwr of 2 */
        if(((attr->num_elem - 1) & attr->num_elem) == 0){
            rb.head = 0;
            rb.tail = 0;
            rb.buf = attr->buffer;
            rb.size_elem = attr->size_elem;
            rb.num_elem = attr->num_elem;

            err = 0;
        }
    }

    return err;
}


//---------------- ringBuffer_write() -----------------
int ringBuffer_write(const void *data){
    int err = 0;
    if(ringBuffer_full(&rb) == 0){
        const size_t offset = (rb.head &(rb.num_elem - 1)) * rb.size_elem;
        memcpy(&(rb.buf[offset]), data, rb.size_elem);
        rb.head++;
    }

    else{
        err = -1;
    }

    return err;
}


//----------------- ringBuffer_read() -----------------
int ringBuffer_read(void *data){
    int err = 0;

    if(ringBuffer_empty(&rb) == 0){
        const size_t offset = (rb.tail & (rb.num_elem - 1)) * rb.size_elem;
        memcpy(data, &(rb.buf[offset]), rb.size_elem);
        rb.tail++;
    }
    else{
        err = -1;
    }

    return err;
}


//-----------------ringBuffer_available()-----------------

int ringBuffer_available(void){
    return((unsigned int)(rb.num_elem + rb.head - rb.tail)) & (rb.num_elem - 1);
}



//-------------- ringBuffer Helper functions --------------

static int ringBuffer_full(struct ring_buffer *rb){
    return((rb->head - rb->tail) == rb->num_elem) ? 1 : 0;
}

static int ringBuffer_empty(struct ring_buffer *rb){
    return((rb->head - rb->tail)== 0U) ? 1 : 0;
}





