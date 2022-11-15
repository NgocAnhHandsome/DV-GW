
#ifndef __RINGBUFFER_H__
#define __RINGBUFFER_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct 
{
    unsigned int head;
    unsigned int tail;
    unsigned int buffer_length;
    unsigned char *data;
}_ringbuffer_t;

typedef enum
{
    Ringbuffer_Error 	    = 0,
    Ringbuffer_OK 	    = 1,
    Ringbuffer_Full         = 2,
    Ringbuffer_empty        = 3,
    Ringbuffer_pop_done     = 4,
    Ringbuffer_push_done    = 5,
    Ringbuffer_get_arr_done = 6,
}_rb_status_;

/* Includes ------------------------------------------------------------------*/

_rb_status_ ringbuffer_init(_ringbuffer_t *_rb_type_t_, char *arr_buffer, unsigned int size);
_rb_status_ ringbuffer_push(_ringbuffer_t *_rb_type_t_, char data);
_rb_status_ ringbuffer_pop(_ringbuffer_t *_rb_type_t_, char *data);

_rb_status_ ringbuffer_get_arr(_ringbuffer_t *_rb_type_t_, char *data);

unsigned int ringbuffer_get_tail(_ringbuffer_t *_rb_type_t_);
unsigned int ringbuffer_get_head(_ringbuffer_t *_rb_type_t_);

#ifdef __cplusplus
}
#endif

#endif