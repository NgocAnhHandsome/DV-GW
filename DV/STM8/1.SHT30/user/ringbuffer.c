
#include "ringbuffer.h"

static void ringbuffer_increase_head(_ringbuffer_t *_rb_type_t_);
static void ringbuffer_increase_tail(_ringbuffer_t *_rb_type_t_);
static _rb_status_ ringbuffer_full(_ringbuffer_t *_rb_type_t_);
static _rb_status_ ringbuffer_empty(_ringbuffer_t *_rb_type_t_);
_rb_status_ ringbuffer_init(_ringbuffer_t *_rb_type_t_, char *arr_buffer, unsigned int size)
{
    if((size <= 0))
    {
        return Ringbuffer_Error;
    }
    else
    {
        _rb_type_t_->head          = 0;
        _rb_type_t_->tail          = 0;
        _rb_type_t_->data          = arr_buffer;
        _rb_type_t_->buffer_length = size+1;
    }
    return Ringbuffer_OK;
}

_rb_status_ ringbuffer_push(_ringbuffer_t *_rb_type_t_, char data)
{
    
    if((Ringbuffer_Full == ringbuffer_full(_rb_type_t_)))
    {
        ringbuffer_increase_tail(_rb_type_t_);
    }
    _rb_type_t_->data[_rb_type_t_->head] = data;
    ringbuffer_increase_head(_rb_type_t_);
    return Ringbuffer_push_done;
}

_rb_status_ ringbuffer_pop(_ringbuffer_t *_rb_type_t_, char *data)
{
    if(Ringbuffer_empty == ringbuffer_empty(_rb_type_t_))
    {
        return Ringbuffer_Error;
    }
    else
    {
        *data = _rb_type_t_->data[_rb_type_t_->tail];
        ringbuffer_increase_tail(_rb_type_t_);
    }
    return Ringbuffer_pop_done;
}

_rb_status_ ringbuffer_full(_ringbuffer_t *_rb_type_t_)
{
    if((_rb_type_t_->tail) != ((_rb_type_t_->head + 1) % _rb_type_t_->buffer_length))
    {
        return Ringbuffer_Error;
    }
    return Ringbuffer_Full;
}

_rb_status_ ringbuffer_empty(_ringbuffer_t *_rb_type_t_)
{
    if((_rb_type_t_->head) != (_rb_type_t_->tail))
    {
        return Ringbuffer_Error;
    }
    return Ringbuffer_empty;
}

unsigned int ringbuffer_get_tail(_ringbuffer_t *_rb_type_t_)
{
    return _rb_type_t_->tail;
}

unsigned int ringbuffer_get_head(_ringbuffer_t *_rb_type_t_)
{
    return _rb_type_t_->head;
}

static void ringbuffer_increase_head(_ringbuffer_t *_rb_type_t_)
{
     _rb_type_t_->head = ((_rb_type_t_->head + 1) % _rb_type_t_->buffer_length);
}

static void ringbuffer_increase_tail(_ringbuffer_t *_rb_type_t_)
{
    _rb_type_t_->tail = ((_rb_type_t_->tail + 1) % _rb_type_t_->buffer_length);
}

_rb_status_ ringbuffer_get_arr(_ringbuffer_t *_rb_type_t_, char *data)
{
    unsigned char flagcheck = 0;
    unsigned int temp_tail = ringbuffer_get_tail(_rb_type_t_);
    unsigned int temp_head = ringbuffer_get_head(_rb_type_t_);
    unsigned int location_end = 0;
    char tempdata;

    if(ringbuffer_empty(_rb_type_t_) == Ringbuffer_empty)
    {
        return Ringbuffer_Error;
    }
    
    while(1)
    {
        if(temp_tail == temp_head)
        {
            return Ringbuffer_Error;
        }
        else
        {
            if(_rb_type_t_->data[temp_tail] == '$')
            {
                flagcheck = 1;
                _rb_type_t_->tail = temp_tail;
            }
            else if((_rb_type_t_->data[temp_tail] == '#')&&(flagcheck == 1))
            {
                flagcheck = 2; 
                location_end = temp_tail;
                break;
            }
            temp_tail = ((temp_tail + 1) % _rb_type_t_->buffer_length);
        }
    }

    while(1)
    {
        ringbuffer_pop(_rb_type_t_, &tempdata);
        if((tempdata=='$')||(tempdata=='C')||(tempdata=='O')||(tempdata=='M')||(tempdata=='-')||(tempdata==',')||(tempdata=='#')||(tempdata=='.')||((tempdata>='0')&&(tempdata<='9')))
        {
            if(tempdata == '#')
            {
                *data = tempdata;
                data++;
                *data = '\0';
                break;
            }
            else
            {
                *data = tempdata;
                data++;
            }
        }
        else
        {
            return Ringbuffer_Error;
        }
    }
    return Ringbuffer_get_arr_done;
}