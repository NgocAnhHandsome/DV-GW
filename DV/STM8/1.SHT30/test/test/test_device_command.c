

#include "device_command.h"
#include "ringbuffer.h"
#include "unity.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void test_function_command_asktype(void)
{
    /*Khởi tạo struct*/
    _comm_data_struct_create_t struct_test_comm;
    _comm_data_struct_detect_t struct_data_test;

    struct_test_comm.port_number = COMM_Port8;
    struct_test_comm.type_msg = COMM_AskType;
    /*Tạo được lệnh*/
    TEST_ASSERT_EQUAL_INT8(comm_create_command(&struct_test_comm), COMM_OK);
    TEST_ASSERT_EQUAL_INT8(comm_detect_command(struct_test_comm.datastr, &struct_data_test), COMM_OK);
    printf("%s\n", struct_test_comm.datastr);
    
    TEST_ASSERT_EQUAL_INT8(struct_data_test.type_msg, COMM_AskType);
    TEST_ASSERT_EQUAL_INT8(struct_data_test.port_number, COMM_Port8);

    /*Không tạo được lệnh*/
    struct_test_comm.port_number = COMM_PortEnd;
    struct_test_comm.type_msg = COMM_AskType;
    TEST_ASSERT_EQUAL_INT8(comm_create_command(&struct_test_comm), COMM_ERROR);

    /*port lớn hơn 9 không tạo được lệnh*/
    struct_test_comm.port_number = 10;
    struct_test_comm.type_msg = COMM_AskType;
    TEST_ASSERT_EQUAL_INT8(comm_create_command(&struct_test_comm), COMM_ERROR);
}

void test_function_command_answertype(void)
{
    /*Khởi tạo struct*/
    _comm_data_struct_create_t struct_test_comm;
    _comm_data_struct_detect_t struct_data_test;
    struct_test_comm.port_number = COMM_Port8;
    struct_test_comm.type_msg = COMM_AnswerType;
    struct_test_comm.type_sensor = Sensor_1;
    /*Tạo được lệnh*/
    TEST_ASSERT_EQUAL_INT8(comm_create_command(&struct_test_comm), COMM_OK);
    TEST_ASSERT_EQUAL_INT8(comm_detect_command(struct_test_comm.datastr, &struct_data_test), COMM_OK);
    printf("%s\n", struct_test_comm.datastr);

    TEST_ASSERT_EQUAL_INT8(struct_data_test.type_msg, COMM_AnswerType);
    TEST_ASSERT_EQUAL_INT8(struct_data_test.port_number, COMM_Port8);
    TEST_ASSERT_EQUAL_INT8(struct_data_test.type_sensor, Sensor_1);

    /*Không tạo được lệnh*/
    struct_test_comm.port_number = COMM_PortEnd;
    struct_test_comm.type_msg = COMM_AnswerType;
    TEST_ASSERT_EQUAL_INT8(comm_create_command(&struct_test_comm), COMM_ERROR);

    /*port lớn hơn 9 không tạo được lệnh*/
    struct_test_comm.port_number = 10;
    struct_test_comm.type_msg = COMM_AnswerType;
    TEST_ASSERT_EQUAL_INT8(comm_create_command(&struct_test_comm), COMM_ERROR);

    /*loại cảm biến lớn hơn type_end*/
    struct_test_comm.port_number = COMM_Port8;
    struct_test_comm.type_msg = COMM_AnswerType;
    struct_test_comm.type_sensor = Sensor_end;
    TEST_ASSERT_EQUAL_INT8(comm_create_command(&struct_test_comm), COMM_ERROR);
}

void test_function_command_askdata(void)
{
 /*Khởi tạo struct*/
    _comm_data_struct_create_t struct_test_comm;
    _comm_data_struct_detect_t struct_data_test;
    struct_test_comm.port_number = COMM_Port8;
    struct_test_comm.type_msg = COMM_AskData;
    /*Tạo được lệnh*/
    TEST_ASSERT_EQUAL_INT8(comm_create_command(&struct_test_comm), COMM_OK);
    TEST_ASSERT_EQUAL_INT8(comm_detect_command(struct_test_comm.datastr, &struct_data_test), COMM_OK);
    printf("%s\n", struct_test_comm.datastr);

    TEST_ASSERT_EQUAL_INT8(struct_data_test.type_msg, COMM_AskData);
    TEST_ASSERT_EQUAL_INT8(struct_data_test.port_number, COMM_Port8);

    /*Không tạo được lệnh*/
    struct_test_comm.port_number = COMM_PortEnd;
    struct_test_comm.type_msg = COMM_AskData;
    TEST_ASSERT_EQUAL_INT8(comm_create_command(&struct_test_comm), COMM_ERROR);

    /*port lớn hơn 9 không tạo được lệnh*/
    struct_test_comm.port_number = 10;
    struct_test_comm.type_msg = COMM_AskData;
    TEST_ASSERT_EQUAL_INT8(comm_create_command(&struct_test_comm), COMM_ERROR);
}

void test_function_command_answerdata (void)
{
 /*Khởi tạo struct*/
    _comm_data_struct_create_t struct_test_comm;
    _comm_data_struct_detect_t struct_data_test;

    struct_test_comm.port_number = COMM_Port8;
    struct_test_comm.type_msg = COMM_AnswerData;
    struct_test_comm.type_sensor = Sensor_1;
    struct_test_comm.Sensor.Sensor_1 = 1234.567;
    /*Tạo được lệnh*/
    TEST_ASSERT_EQUAL_INT8(comm_create_command(&struct_test_comm), COMM_OK);
    TEST_ASSERT_EQUAL_INT8(comm_detect_command(struct_test_comm.datastr, &struct_data_test), COMM_OK);
    printf("%s\n", struct_test_comm.datastr);

    TEST_ASSERT_EQUAL_INT8(struct_data_test.type_msg, COMM_AnswerData);
    TEST_ASSERT_EQUAL_INT8(struct_data_test.port_number, COMM_Port8);
    TEST_ASSERT_EQUAL_INT8(struct_data_test.type_sensor, Sensor_1);
    TEST_ASSERT_EQUAL_FLOAT(struct_data_test.Sensor.Sensor_1, 1234.56789);

    struct_test_comm.Sensor.Sensor_1 = -1234.567;
    /*Tạo được lệnh*/
    TEST_ASSERT_EQUAL_INT8(comm_create_command(&struct_test_comm), COMM_OK);
    TEST_ASSERT_EQUAL_INT8(comm_detect_command(struct_test_comm.datastr, &struct_data_test), COMM_OK);
    printf("%s\n", struct_test_comm.datastr);

    TEST_ASSERT_EQUAL_INT8(struct_data_test.type_msg, COMM_AnswerData);
    TEST_ASSERT_EQUAL_INT8(struct_data_test.port_number, COMM_Port8);
    TEST_ASSERT_EQUAL_INT8(struct_data_test.type_sensor, Sensor_1);
    TEST_ASSERT_EQUAL_FLOAT(struct_data_test.Sensor.Sensor_1, -1234.56789);
}


void test_function_command_detect(void)
{
   char *data_test = "$COM,2,7,0,29#";
    _comm_data_struct_detect_t struct_data_test;
    TEST_ASSERT_EQUAL_INT8(comm_detect_command(data_test, &struct_data_test), COMM_ERROR);

    data_test = "$COMM,2,7,0,29";
    TEST_ASSERT_EQUAL_INT8(comm_detect_command(data_test, &struct_data_test), COMM_ERROR);

    data_test = "$COMM,1,7,1#";
    TEST_ASSERT_EQUAL_INT8(comm_detect_command(data_test, &struct_data_test), COMM_ERROR);

    data_test = "$COMM,2,7,0,1#";
    TEST_ASSERT_EQUAL_INT8(comm_detect_command(data_test, &struct_data_test), COMM_ERROR);

    data_test = "$COMM,3,7,1#";
    TEST_ASSERT_EQUAL_INT8(comm_detect_command(data_test, &struct_data_test), COMM_ERROR);

     data_test = "$COMM,-2,s7,0,29#";
    TEST_ASSERT_EQUAL_INT8(comm_detect_command(data_test, &struct_data_test), COMM_ERROR);
}