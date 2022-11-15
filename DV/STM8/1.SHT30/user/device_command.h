
#ifndef __DIVICE_COMM_H__
#define __DIVICE_COMM_H__

#ifdef __cplusplus
extern "C" {
#endif

#define COMM_HEADER "$COMM"

typedef enum
{
    COMM_AskType              = 1,
    COMM_AnswerType           = 2,
    COMM_AskData              = 3,
    COMM_AnswerData           = 4,
}_comm_type_command_e;

typedef enum
{
    COMM_Port1 = 0,              
    COMM_Port2,          
    COMM_Port3,              
    COMM_Port4,  
    COMM_Port5,
    COMM_Port6,
    COMM_Port7,
    COMM_Port8,           
    COMM_PortEnd
}_comm_port_number_e;

typedef enum 
{
    Sensor_1 = 0,
    Sensor_2,
    Sensor_3,
    Sensor_end,
}_comm_type_sensor_e;

typedef enum 
{
    COMM_OK,
    COMM_ERROR,
}_comm_status_e;


typedef struct
{
    float Sensor_1;
    float Sensor_2;
    float Sensor_3;
    float Sensor_4;
    float Sensor_5;
    float Sensor_6;
    float Sensor_7;
    float Sensor_8;
    float Sensor_9;
    float Sensor_10;
    float Sensor_11;
    float Sensor_12;
    float Sensor_13;
    float Sensor_14;
    float Sensor_15;
}_comm_data_sensor_t;

typedef struct 
{
    _comm_port_number_e         port_number;
    _comm_type_command_e        type_msg;
    _comm_type_sensor_e         type_sensor;
    char                        datastr[50];
    _comm_data_sensor_t         Sensor;
}_comm_data_struct_create_t;

typedef struct 
{
    _comm_port_number_e         port_number;
    _comm_type_command_e        type_msg;
    _comm_type_sensor_e         type_sensor;
    _comm_data_sensor_t         Sensor;
}_comm_data_struct_detect_t;

_comm_status_e comm_create_command(_comm_data_struct_create_t *_data_struct_);
_comm_status_e comm_detect_command(char *_str_datain_, _comm_data_struct_detect_t *_data_struct_);

#ifdef __cplusplus
}
#endif

#endif