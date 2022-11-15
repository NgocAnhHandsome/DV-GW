#include "device_command.h"


static void string_crc(char * destination);
static void string_cat(char *destination, const char * source);
static void string_copy(char * destination, const char * source);
static char string_split(char destination[][20], const char *source);
static unsigned char string_length(const char *data);
static unsigned char string_cmp_len(const char *destination, const char * source, const unsigned char length);

static char* conver_unsigned_intTostr(const unsigned int _data_);
static unsigned int conver_unsigned_strToint(const char *_data_);

static char* conver_floatTostr(const float _data_, unsigned char afterpoint);
static float conver_strTofloat(const char *_data_);

static unsigned char checksum(const char *_data_str_);

_comm_status_e comm_create_command(_comm_data_struct_create_t *_data_struct_)
{
    if(_data_struct_->port_number >= COMM_PortEnd)
    {
        return COMM_ERROR;
    }

    switch(_data_struct_->type_msg)
    {
        case COMM_AskType:
            string_copy(_data_struct_->datastr, (char*)COMM_HEADER);
            string_cat(_data_struct_->datastr, ",");
            string_cat(_data_struct_->datastr, conver_unsigned_intTostr(_data_struct_->type_msg));
            string_cat(_data_struct_->datastr, ",");
            string_cat(_data_struct_->datastr, conver_unsigned_intTostr(_data_struct_->port_number));
            string_cat(_data_struct_->datastr, ",");
            string_crc(_data_struct_->datastr);
        break;

        case COMM_AnswerType:
            if(_data_struct_->type_sensor >= Sensor_end)
            {
                return COMM_ERROR;
            }
            string_copy(_data_struct_->datastr, (char*)COMM_HEADER);
            string_cat(_data_struct_->datastr, ",");
            string_cat(_data_struct_->datastr, conver_unsigned_intTostr(_data_struct_->type_msg));
            string_cat(_data_struct_->datastr, ",");
            string_cat(_data_struct_->datastr, conver_unsigned_intTostr(_data_struct_->port_number));
            string_cat(_data_struct_->datastr, ",");
            string_cat(_data_struct_->datastr, conver_unsigned_intTostr(_data_struct_->type_sensor));
            string_cat(_data_struct_->datastr, ",");
            string_crc(_data_struct_->datastr);
        break;

        case COMM_AskData:
            string_copy(_data_struct_->datastr, (char*)COMM_HEADER);
            string_cat(_data_struct_->datastr, ",");
            string_cat(_data_struct_->datastr, conver_unsigned_intTostr(_data_struct_->type_msg));
            string_cat(_data_struct_->datastr, ",");
            string_cat(_data_struct_->datastr, conver_unsigned_intTostr(_data_struct_->port_number));
            string_cat(_data_struct_->datastr, ",");
            string_crc(_data_struct_->datastr);
            return COMM_OK;
        break;

        case COMM_AnswerData:
           string_copy(_data_struct_->datastr, (char*)COMM_HEADER);
            string_cat(_data_struct_->datastr, ",");
            string_cat(_data_struct_->datastr, conver_unsigned_intTostr(_data_struct_->type_msg));
            string_cat(_data_struct_->datastr, ",");
            string_cat(_data_struct_->datastr, conver_unsigned_intTostr(_data_struct_->port_number));
            string_cat(_data_struct_->datastr, ",");
            string_cat(_data_struct_->datastr, conver_unsigned_intTostr(_data_struct_->type_sensor));
            string_cat(_data_struct_->datastr, ",");
            if(_data_struct_->type_sensor == Sensor_1)
            {
                string_cat(_data_struct_->datastr, conver_floatTostr(_data_struct_->Sensor.Sensor_1, 4)); //
                string_cat(_data_struct_->datastr, ",");
            }
            string_crc(_data_struct_->datastr);
						return COMM_OK;
        break;
    }
    return COMM_OK;
}
/*
_comm_status_e comm_detect_command(const char *_str_datain_, _comm_data_struct_detect_t *_data_struct_)
{
    char temp_str[10][20];
    if((!string_cmp_len(_str_datain_, COMM_HEADER, 5))||(_str_datain_[string_length(_str_datain_)-1] != '#'))
    {
        return COMM_ERROR;
    }
    
    if(!string_split(temp_str, _str_datain_))
    {
        return COMM_ERROR;
    }
   
    _data_struct_->type_msg =  conver_unsigned_strToint(temp_str[1]);
		
    if(_data_struct_->type_msg == COMM_AskType)
    {
        _data_struct_->port_number =  conver_unsigned_strToint(temp_str[2]);
        if(conver_unsigned_strToint(temp_str[3]) != checksum(_str_datain_))
        {
            return COMM_ERROR;
        }
    }
    else if(_data_struct_->type_msg == COMM_AnswerType)
    {
        _data_struct_->port_number = conver_unsigned_strToint(temp_str[2]);
        _data_struct_->type_sensor = conver_unsigned_strToint(temp_str[3]);
        if(conver_unsigned_strToint(temp_str[4]) != checksum(_str_datain_))
        {
            return COMM_ERROR;
        }
    }
    else if(_data_struct_->type_msg == COMM_AskData)
    {
        _data_struct_->port_number =  conver_unsigned_strToint(temp_str[2]);
        if(conver_unsigned_strToint(temp_str[3]) != checksum(_str_datain_))
        {
            return COMM_ERROR;
        }
    }
    else if(_data_struct_->type_msg == COMM_AnswerData)
    {
        _data_struct_->port_number = conver_unsigned_strToint(temp_str[2]);
        _data_struct_->type_sensor = conver_unsigned_strToint(temp_str[3]);
        _data_struct_->Sensor.Sensor_1 = conver_strTofloat(temp_str[4]);
    }
    return COMM_OK;
}
*/

_comm_status_e comm_detect_command(char *_str_datain_, _comm_data_struct_detect_t *_data_struct_)
{
    char temp_str[10][20];
    if((!string_cmp_len(_str_datain_, COMM_HEADER, 5))||(_str_datain_[string_length(_str_datain_)-1] != '#'))
    {
        return COMM_ERROR;
    }
    
    if(!string_split(temp_str, _str_datain_))
    {
        return COMM_ERROR;
    }
   
    _data_struct_->type_msg =  conver_unsigned_strToint(temp_str[1]);
  
    if(_data_struct_->type_msg == COMM_AskType)
    {
        _data_struct_->port_number =  conver_unsigned_strToint(temp_str[2]);
        if(conver_unsigned_strToint(temp_str[3]) != checksum(_str_datain_))
        {
            return COMM_ERROR;
        }
    }
    else if(_data_struct_->type_msg == COMM_AnswerType)
    {
        _data_struct_->port_number = conver_unsigned_strToint(temp_str[2]);
        _data_struct_->type_sensor = conver_unsigned_strToint(temp_str[3]);
        if(conver_unsigned_strToint(temp_str[4]) != checksum(_str_datain_))
        {
            return COMM_ERROR;
        }
    }
    else if(_data_struct_->type_msg == COMM_AskData)
    {
        _data_struct_->port_number =  conver_unsigned_strToint(temp_str[2]);
        if(conver_unsigned_strToint(temp_str[3]) != checksum(_str_datain_))
        {
            return COMM_ERROR;
        }
    }
    else if(_data_struct_->type_msg == COMM_AnswerData)
    {
        _data_struct_->port_number = conver_unsigned_strToint(temp_str[2]);
        _data_struct_->type_sensor = conver_unsigned_strToint(temp_str[3]);
        _data_struct_->Sensor.Sensor_1 = conver_strTofloat(temp_str[4]);
    }
    return COMM_OK;
}

static unsigned char string_length(const char *data)
{
    unsigned char count = 0;
    
    while(*(data+count) != '\0')
    {
        count++;
    }
    return count;
}

void string_copy(char *destination, const char *source)
{
    unsigned char lengt_source = string_length(source), i = 0;

    for(i=0; i<lengt_source; i++)
    {
        *(destination+i) = *(source+i);
    }
    *(destination+i) = '\0';
}

static void string_cat(char *destination, const char * source)
{
    while(*destination != '\0')
    {
        destination++;
    }

    while(*source != '\0')
    {
        *destination++ = *source++;
    }
    *destination = '\0';
}

static char string_split(char destination[][20], const char *source)
{
		//$COMM,1,2,3,4,5#
    unsigned char i = 0, row = 0, col = 0;
    
    while(source[i]!='#')
    {
        if(source[i] == ',')
        {
            destination[col][row] = '\0';
            col++;
            row = 0;
        }
        else
        {
            if(col >= 1)
            {
                
                if(((source[i] >= '0')&&(source[i] <= '9'))||(source[i] == '.')||(source[i] == '-'))
                {
                    destination[col][row] = source[i];
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                destination[col][row] = source[i];
            }
            row++;
        }
        i++;
    }
    destination[col][row] = '\0';
    return 1;
}

static char* conver_unsigned_intTostr(const unsigned int _data_)
{
    static char arr[20];
    unsigned char i = 0;
    unsigned int tempdata = _data_, tempsum = 0;
    
    if(_data_ == 0)
    {
        arr[0] = '0';
        arr[1] = '\0';
        return arr;
    }

    while(tempdata)
    {
        tempsum =  (tempsum*10) + (tempdata%10);
        tempdata /= 10;
    }

    while(tempsum)
    {
        arr[i] = (tempsum%10) + '0';
        tempsum /= 10;
        i++;
    }

    arr[i] = '\0';
    return arr;
}

static unsigned int conver_unsigned_strToint(const char *_data_)
{
    static unsigned int tempdata;
    tempdata = 0;
    while(*(_data_)!='\0')
    {
        tempdata = (tempdata*10) + (*(_data_) - '0');
        _data_++;
    }
    return tempdata;
}

static char* conver_floatTostr(const float _data_, unsigned char afterpoint)
{
    static char arr[20];
    unsigned char i=0;
    float tempdata = _data_, fpart;
    unsigned int ipart = 0;
    arr[0] = '\0';
    if(_data_ < 0.0)
    {
        string_copy(arr, "-");
        tempdata *= -1.0;
    }
    
    ipart = (int)tempdata;
    fpart = tempdata - (float)ipart;
    for(i=0; i<afterpoint; i++)
    {
        fpart *=10.0;
    }
		
    string_cat(arr, conver_unsigned_intTostr(ipart));
    string_cat(arr,".");
    string_cat(arr, conver_unsigned_intTostr((unsigned int)fpart));
    return arr;
}

static float conver_strTofloat(const char *_data_)
{
    static float tempdata = 0.0;
    tempdata = 0.0;
    float sign_var = 1.0;
    unsigned int tempdivide = 10;

    if(*(_data_) == '-')
    {
        sign_var = -1.0;
        _data_++;
    }
    
    while(*(_data_)!='.')
    {
        tempdata = (tempdata*10.0) + (*(_data_) - '0');
        _data_++;
    }
    _data_++;
    while(*(_data_)!='\0')
    {
        tempdata +=  (float)(*(_data_) - '0')/tempdivide;
        tempdivide *= 10;
        _data_++;
    }
    return (tempdata*sign_var);
}


static unsigned char string_cmp_len(const char * destination, const char * source, const unsigned char length)
{
    int i=0;
    for(i=0; i<length; i++)
    {
        if(destination[i] != source[i])
        {
            return 0;
        }
    }
    return 1;
}

static void string_crc(char * destination)
{
    unsigned char temp_crc = 0;
    char *arr = destination;
    while(*arr != '\0')
    {
        temp_crc ^= *arr++;
    }
    string_cat(destination, conver_unsigned_intTostr(temp_crc));
    string_cat(destination, "#");
}

static unsigned char checksum(const char *_data_str_)
{
	
    unsigned char location, i = 0;
    static unsigned char tempcrc;
    tempcrc = 0;
    while(*(_data_str_+i)!= '\0')
    {
        if(*(_data_str_+i) == ',')
        {
            location = i;
        }
				 i++;	
    }
	
    for(i=0; i<=location; i++)
    {
        tempcrc ^= *(_data_str_+i);
    }
    return tempcrc;
}