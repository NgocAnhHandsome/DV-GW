#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"
#include "src/ringbuffer.h"
#include "src/device_command.h"








void setUp(void)

{

}



void tearDown(void)

{

}



void test_function_command_asktype(void)

{



    _comm_data_struct_create_t struct_test_comm;

    _comm_data_struct_detect_t struct_data_test;



    struct_test_comm.port_number = COMM_Port8;

    struct_test_comm.type_msg = COMM_AskType;



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((comm_create_command(&struct_test_comm))), (UNITY_INT)(UNITY_INT8 )((COMM_OK)), (

   ((void *)0)

   ), (UNITY_UINT)(25), UNITY_DISPLAY_STYLE_INT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((comm_detect_command(struct_test_comm.datastr, &struct_data_test))), (UNITY_INT)(UNITY_INT8 )((COMM_OK)), (

   ((void *)0)

   ), (UNITY_UINT)(26), UNITY_DISPLAY_STYLE_INT8);

    printf("%s\n", struct_test_comm.datastr);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((struct_data_test.type_msg)), (UNITY_INT)(UNITY_INT8 )((COMM_AskType)), (

   ((void *)0)

   ), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_INT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((struct_data_test.port_number)), (UNITY_INT)(UNITY_INT8 )((COMM_Port8)), (

   ((void *)0)

   ), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_INT8);





    struct_test_comm.port_number = COMM_PortEnd;

    struct_test_comm.type_msg = COMM_AskType;

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((comm_create_command(&struct_test_comm))), (UNITY_INT)(UNITY_INT8 )((COMM_ERROR)), (

   ((void *)0)

   ), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_INT8);





    struct_test_comm.port_number = 10;

    struct_test_comm.type_msg = COMM_AskType;

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((comm_create_command(&struct_test_comm))), (UNITY_INT)(UNITY_INT8 )((COMM_ERROR)), (

   ((void *)0)

   ), (UNITY_UINT)(40), UNITY_DISPLAY_STYLE_INT8);

}



void test_function_command_answertype(void)

{



    _comm_data_struct_create_t struct_test_comm;

    _comm_data_struct_detect_t struct_data_test;

    struct_test_comm.port_number = COMM_Port8;

    struct_test_comm.type_msg = COMM_AnswerType;

    struct_test_comm.type_sensor = Sensor_1;



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((comm_create_command(&struct_test_comm))), (UNITY_INT)(UNITY_INT8 )((COMM_OK)), (

   ((void *)0)

   ), (UNITY_UINT)(52), UNITY_DISPLAY_STYLE_INT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((comm_detect_command(struct_test_comm.datastr, &struct_data_test))), (UNITY_INT)(UNITY_INT8 )((COMM_OK)), (

   ((void *)0)

   ), (UNITY_UINT)(53), UNITY_DISPLAY_STYLE_INT8);

    printf("%s\n", struct_test_comm.datastr);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((struct_data_test.type_msg)), (UNITY_INT)(UNITY_INT8 )((COMM_AnswerType)), (

   ((void *)0)

   ), (UNITY_UINT)(56), UNITY_DISPLAY_STYLE_INT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((struct_data_test.port_number)), (UNITY_INT)(UNITY_INT8 )((COMM_Port8)), (

   ((void *)0)

   ), (UNITY_UINT)(57), UNITY_DISPLAY_STYLE_INT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((struct_data_test.type_sensor)), (UNITY_INT)(UNITY_INT8 )((Sensor_1)), (

   ((void *)0)

   ), (UNITY_UINT)(58), UNITY_DISPLAY_STYLE_INT8);





    struct_test_comm.port_number = COMM_PortEnd;

    struct_test_comm.type_msg = COMM_AnswerType;

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((comm_create_command(&struct_test_comm))), (UNITY_INT)(UNITY_INT8 )((COMM_ERROR)), (

   ((void *)0)

   ), (UNITY_UINT)(63), UNITY_DISPLAY_STYLE_INT8);





    struct_test_comm.port_number = 10;

    struct_test_comm.type_msg = COMM_AnswerType;

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((comm_create_command(&struct_test_comm))), (UNITY_INT)(UNITY_INT8 )((COMM_ERROR)), (

   ((void *)0)

   ), (UNITY_UINT)(68), UNITY_DISPLAY_STYLE_INT8);





    struct_test_comm.port_number = COMM_Port8;

    struct_test_comm.type_msg = COMM_AnswerType;

    struct_test_comm.type_sensor = Sensor_end;

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((comm_create_command(&struct_test_comm))), (UNITY_INT)(UNITY_INT8 )((COMM_ERROR)), (

   ((void *)0)

   ), (UNITY_UINT)(74), UNITY_DISPLAY_STYLE_INT8);

}



void test_function_command_askdata(void)

{



    _comm_data_struct_create_t struct_test_comm;

    _comm_data_struct_detect_t struct_data_test;

    struct_test_comm.port_number = COMM_Port8;

    struct_test_comm.type_msg = COMM_AskData;



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((comm_create_command(&struct_test_comm))), (UNITY_INT)(UNITY_INT8 )((COMM_OK)), (

   ((void *)0)

   ), (UNITY_UINT)(85), UNITY_DISPLAY_STYLE_INT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((comm_detect_command(struct_test_comm.datastr, &struct_data_test))), (UNITY_INT)(UNITY_INT8 )((COMM_OK)), (

   ((void *)0)

   ), (UNITY_UINT)(86), UNITY_DISPLAY_STYLE_INT8);

    printf("%s\n", struct_test_comm.datastr);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((struct_data_test.type_msg)), (UNITY_INT)(UNITY_INT8 )((COMM_AskData)), (

   ((void *)0)

   ), (UNITY_UINT)(89), UNITY_DISPLAY_STYLE_INT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((struct_data_test.port_number)), (UNITY_INT)(UNITY_INT8 )((COMM_Port8)), (

   ((void *)0)

   ), (UNITY_UINT)(90), UNITY_DISPLAY_STYLE_INT8);





    struct_test_comm.port_number = COMM_PortEnd;

    struct_test_comm.type_msg = COMM_AskData;

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((comm_create_command(&struct_test_comm))), (UNITY_INT)(UNITY_INT8 )((COMM_ERROR)), (

   ((void *)0)

   ), (UNITY_UINT)(95), UNITY_DISPLAY_STYLE_INT8);





    struct_test_comm.port_number = 10;

    struct_test_comm.type_msg = COMM_AskData;

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((comm_create_command(&struct_test_comm))), (UNITY_INT)(UNITY_INT8 )((COMM_ERROR)), (

   ((void *)0)

   ), (UNITY_UINT)(100), UNITY_DISPLAY_STYLE_INT8);

}



void test_function_command_answerdata (void)

{



    _comm_data_struct_create_t struct_test_comm;

    _comm_data_struct_detect_t struct_data_test;



    struct_test_comm.port_number = COMM_Port8;

    struct_test_comm.type_msg = COMM_AnswerData;

    struct_test_comm.type_sensor = Sensor_1;

    struct_test_comm.Sensor.Sensor_1 = 1234.567;



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((comm_create_command(&struct_test_comm))), (UNITY_INT)(UNITY_INT8 )((COMM_OK)), (

   ((void *)0)

   ), (UNITY_UINT)(114), UNITY_DISPLAY_STYLE_INT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((comm_detect_command(struct_test_comm.datastr, &struct_data_test))), (UNITY_INT)(UNITY_INT8 )((COMM_OK)), (

   ((void *)0)

   ), (UNITY_UINT)(115), UNITY_DISPLAY_STYLE_INT8);

    printf("%s\n", struct_test_comm.datastr);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((struct_data_test.type_msg)), (UNITY_INT)(UNITY_INT8 )((COMM_AnswerData)), (

   ((void *)0)

   ), (UNITY_UINT)(118), UNITY_DISPLAY_STYLE_INT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((struct_data_test.port_number)), (UNITY_INT)(UNITY_INT8 )((COMM_Port8)), (

   ((void *)0)

   ), (UNITY_UINT)(119), UNITY_DISPLAY_STYLE_INT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((struct_data_test.type_sensor)), (UNITY_INT)(UNITY_INT8 )((Sensor_1)), (

   ((void *)0)

   ), (UNITY_UINT)(120), UNITY_DISPLAY_STYLE_INT8);

    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((struct_data_test.Sensor.Sensor_1)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((struct_data_test.Sensor.Sensor_1))), (UNITY_FLOAT)((UNITY_FLOAT)((1234.56789))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(121)));



    struct_test_comm.Sensor.Sensor_1 = -1234.567;



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((comm_create_command(&struct_test_comm))), (UNITY_INT)(UNITY_INT8 )((COMM_OK)), (

   ((void *)0)

   ), (UNITY_UINT)(125), UNITY_DISPLAY_STYLE_INT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((comm_detect_command(struct_test_comm.datastr, &struct_data_test))), (UNITY_INT)(UNITY_INT8 )((COMM_OK)), (

   ((void *)0)

   ), (UNITY_UINT)(126), UNITY_DISPLAY_STYLE_INT8);

    printf("%s\n", struct_test_comm.datastr);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((struct_data_test.type_msg)), (UNITY_INT)(UNITY_INT8 )((COMM_AnswerData)), (

   ((void *)0)

   ), (UNITY_UINT)(129), UNITY_DISPLAY_STYLE_INT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((struct_data_test.port_number)), (UNITY_INT)(UNITY_INT8 )((COMM_Port8)), (

   ((void *)0)

   ), (UNITY_UINT)(130), UNITY_DISPLAY_STYLE_INT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((struct_data_test.type_sensor)), (UNITY_INT)(UNITY_INT8 )((Sensor_1)), (

   ((void *)0)

   ), (UNITY_UINT)(131), UNITY_DISPLAY_STYLE_INT8);

    UnityAssertFloatsWithin((UNITY_FLOAT)((UNITY_FLOAT)((struct_data_test.Sensor.Sensor_1)) * (UNITY_FLOAT)(0.00001f)), (UNITY_FLOAT)((UNITY_FLOAT)((struct_data_test.Sensor.Sensor_1))), (UNITY_FLOAT)((UNITY_FLOAT)((-1234.56789))), ((

   ((void *)0)

   )), (UNITY_UINT)((UNITY_UINT)(132)));

}





void test_function_command_detect(void)

{

   char *data_test = "$COM,2,7,0,29#";

    _comm_data_struct_detect_t struct_data_test;

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((comm_detect_command(data_test, &struct_data_test))), (UNITY_INT)(UNITY_INT8 )((COMM_ERROR)), (

   ((void *)0)

   ), (UNITY_UINT)(140), UNITY_DISPLAY_STYLE_INT8);



    data_test = "$COMM,2,7,0,29";

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((comm_detect_command(data_test, &struct_data_test))), (UNITY_INT)(UNITY_INT8 )((COMM_ERROR)), (

   ((void *)0)

   ), (UNITY_UINT)(143), UNITY_DISPLAY_STYLE_INT8);



    data_test = "$COMM,1,7,1#";

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((comm_detect_command(data_test, &struct_data_test))), (UNITY_INT)(UNITY_INT8 )((COMM_ERROR)), (

   ((void *)0)

   ), (UNITY_UINT)(146), UNITY_DISPLAY_STYLE_INT8);



    data_test = "$COMM,2,7,0,1#";

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((comm_detect_command(data_test, &struct_data_test))), (UNITY_INT)(UNITY_INT8 )((COMM_ERROR)), (

   ((void *)0)

   ), (UNITY_UINT)(149), UNITY_DISPLAY_STYLE_INT8);



    data_test = "$COMM,3,7,1#";

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((comm_detect_command(data_test, &struct_data_test))), (UNITY_INT)(UNITY_INT8 )((COMM_ERROR)), (

   ((void *)0)

   ), (UNITY_UINT)(152), UNITY_DISPLAY_STYLE_INT8);



     data_test = "$COMM,2,s7,0,29#";

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((comm_detect_command(data_test, &struct_data_test))), (UNITY_INT)(UNITY_INT8 )((COMM_ERROR)), (

   ((void *)0)

   ), (UNITY_UINT)(155), UNITY_DISPLAY_STYLE_INT8);

}
