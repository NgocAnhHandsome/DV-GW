#include "src/ringbuffer.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"






void setUp(void)

{

}



void tearDown(void)

{

}



void test_function_ringbuffer_init_successful(void)

{

    _ringbuffer_t ringbuffer_Test;

    _rb_status_ Temp = 0;



    const unsigned int Init_value_head = 0;

    const unsigned int Init_value_tail = 0;

    char Arrary_Test[1000];



    Temp = ringbuffer_init(&ringbuffer_Test, Arrary_Test, 1000);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((Ringbuffer_OK)), (UNITY_INT)(UNITY_INT8 )((Temp)), (

   ((void *)0)

   ), (UNITY_UINT)(24), UNITY_DISPLAY_STYLE_INT8);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((Init_value_head)), (UNITY_INT)(UNITY_INT32)((ringbuffer_Test.head)), (

   ((void *)0)

   ), (UNITY_UINT)(25), UNITY_DISPLAY_STYLE_INT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((Init_value_head)), (UNITY_INT)(UNITY_INT32)((ringbuffer_Test.tail)), (

   ((void *)0)

   ), (UNITY_UINT)(26), UNITY_DISPLAY_STYLE_INT32);

    UnityAssertEqualNumber((UNITY_INT)((Arrary_Test)), (UNITY_INT)((ringbuffer_Test.data)), (

   ((void *)0)

   ), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_INT64);

}



void test_function_ringbuffer_init_error(void)

{

    _ringbuffer_t ringbuffer_Test;

    _rb_status_ Temp = 0;



    const unsigned int Init_value_head = 0;

    const unsigned int Init_value_tail = 0;

    char Arrary_Test[1000];



    Temp = ringbuffer_init(&ringbuffer_Test, Arrary_Test, 0);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((Ringbuffer_Error)), (UNITY_INT)(UNITY_INT8 )((Temp)), (

   ((void *)0)

   ), (UNITY_UINT)(40), UNITY_DISPLAY_STYLE_INT8);

}



void test_function_ringbuffer_push_pop(void)

{

    _ringbuffer_t ringbuffer_Test;

    _rb_status_ Temp = 0;



    const unsigned int Init_value_head = 0;

    const unsigned int Init_value_tail = 0;

    const unsigned int Size_Array = 50;

    char Arrary_Test[Size_Array], i;



    Temp = ringbuffer_init(&ringbuffer_Test, Arrary_Test, Size_Array);





    UnityAssertEqualNumber((UNITY_INT)((Arrary_Test)), (UNITY_INT)((ringbuffer_Test.data)), (

   ((void *)0)

   ), (UNITY_UINT)(56), UNITY_DISPLAY_STYLE_INT64);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((Init_value_head)), (UNITY_INT)(UNITY_INT32)((ringbuffer_Test.head)), (

   ((void *)0)

   ), (UNITY_UINT)(57), UNITY_DISPLAY_STYLE_INT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((Init_value_head)), (UNITY_INT)(UNITY_INT32)((ringbuffer_Test.tail)), (

   ((void *)0)

   ), (UNITY_UINT)(58), UNITY_DISPLAY_STYLE_INT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((Size_Array+1)), (UNITY_INT)(UNITY_INT32)((ringbuffer_Test.buffer_length)), (

   ((void *)0)

   ), (UNITY_UINT)(59), UNITY_DISPLAY_STYLE_INT32);



    for(i=0; i<Size_Array; i++)

    {

        char Temp_data = 0;

        if(ringbuffer_push(&ringbuffer_Test, i))

        {

            if(ringbuffer_pop(&ringbuffer_Test, &Temp_data) == Ringbuffer_pop_done)

            {

                UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((Temp_data)), (UNITY_INT)(UNITY_INT32)((i)), (

               ((void *)0)

               ), (UNITY_UINT)(68), UNITY_DISPLAY_STYLE_INT32);

            }

        }

    }

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((Size_Array)), (UNITY_INT)(UNITY_INT32)((ringbuffer_get_head(&ringbuffer_Test))), (

   ((void *)0)

   ), (UNITY_UINT)(72), UNITY_DISPLAY_STYLE_INT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((Size_Array)), (UNITY_INT)(UNITY_INT32)((ringbuffer_get_tail(&ringbuffer_Test))), (

   ((void *)0)

   ), (UNITY_UINT)(73), UNITY_DISPLAY_STYLE_INT32);

}



void test_function_ringbuffer_push_pop_circular(void)

{

    _ringbuffer_t ringbuffer_Test;

    _rb_status_ Temp = 0;



    const unsigned int Init_value_head = 0;

    const unsigned int Init_value_tail = 0;

    const unsigned int Size_Array = 50;

    char Arrary_Test[Size_Array], i;

    unsigned char circular_add_test = 20;

    Temp = ringbuffer_init(&ringbuffer_Test, Arrary_Test, Size_Array);





    UnityAssertEqualNumber((UNITY_INT)((Arrary_Test)), (UNITY_INT)((ringbuffer_Test.data)), (

   ((void *)0)

   ), (UNITY_UINT)(89), UNITY_DISPLAY_STYLE_INT64);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((Init_value_head)), (UNITY_INT)(UNITY_INT32)((ringbuffer_Test.head)), (

   ((void *)0)

   ), (UNITY_UINT)(90), UNITY_DISPLAY_STYLE_INT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((Init_value_head)), (UNITY_INT)(UNITY_INT32)((ringbuffer_Test.tail)), (

   ((void *)0)

   ), (UNITY_UINT)(91), UNITY_DISPLAY_STYLE_INT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((Size_Array+1)), (UNITY_INT)(UNITY_INT32)((ringbuffer_Test.buffer_length)), (

   ((void *)0)

   ), (UNITY_UINT)(92), UNITY_DISPLAY_STYLE_INT32);



    for(i=0; i<Size_Array + circular_add_test; i++)

    {

        char Temp_data = 0;

        if(ringbuffer_push(&ringbuffer_Test, i))

        {

            if(ringbuffer_pop(&ringbuffer_Test, &Temp_data) == Ringbuffer_pop_done)

            {

                UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((Temp_data)), (UNITY_INT)(UNITY_INT32)((i)), (

               ((void *)0)

               ), (UNITY_UINT)(101), UNITY_DISPLAY_STYLE_INT32);

            }

        }

    }

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((circular_add_test - 1)), (UNITY_INT)(UNITY_INT32)((ringbuffer_get_head(&ringbuffer_Test))), (

   ((void *)0)

   ), (UNITY_UINT)(105), UNITY_DISPLAY_STYLE_INT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((circular_add_test - 1)), (UNITY_INT)(UNITY_INT32)((ringbuffer_get_tail(&ringbuffer_Test))), (

   ((void *)0)

   ), (UNITY_UINT)(106), UNITY_DISPLAY_STYLE_INT32);

}





void test_function_ringbuffer_error(void)

{

    _ringbuffer_t ringbuffer_Test;

    _rb_status_ Temp = 0;



    char Temp_data = 0;

    const unsigned int Init_value_head = 0;

    const unsigned int Init_value_tail = 0;

    const unsigned int Size_Array = 50;

    char Arrary_Test[Size_Array], i;

    unsigned char circular_add_test = 20;



    Temp = ringbuffer_init(&ringbuffer_Test, Arrary_Test, Size_Array);





    UnityAssertEqualNumber((UNITY_INT)((Arrary_Test)), (UNITY_INT)((ringbuffer_Test.data)), (

   ((void *)0)

   ), (UNITY_UINT)(125), UNITY_DISPLAY_STYLE_INT64);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((Init_value_head)), (UNITY_INT)(UNITY_INT32)((ringbuffer_Test.head)), (

   ((void *)0)

   ), (UNITY_UINT)(126), UNITY_DISPLAY_STYLE_INT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((Init_value_head)), (UNITY_INT)(UNITY_INT32)((ringbuffer_Test.tail)), (

   ((void *)0)

   ), (UNITY_UINT)(127), UNITY_DISPLAY_STYLE_INT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((Size_Array+1)), (UNITY_INT)(UNITY_INT32)((ringbuffer_Test.buffer_length)), (

   ((void *)0)

   ), (UNITY_UINT)(128), UNITY_DISPLAY_STYLE_INT32);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((ringbuffer_pop(&ringbuffer_Test, &Temp_data))), (UNITY_INT)(UNITY_INT8 )((Ringbuffer_Error)), (

   ((void *)0)

   ), (UNITY_UINT)(130), UNITY_DISPLAY_STYLE_INT8);



    for(i=0; i<Size_Array + circular_add_test; i++)

    {

        if(!ringbuffer_push(&ringbuffer_Test, i))

        {

            printf("PUSH ERROR\n");

        }

    }



    for(i=20; i<Size_Array + (circular_add_test*2); i++)

    {

        if(ringbuffer_pop(&ringbuffer_Test, &Temp_data) == Ringbuffer_pop_done)

        {

            UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((Temp_data)), (UNITY_INT)(UNITY_INT32)((i)), (

           ((void *)0)

           ), (UNITY_UINT)(144), UNITY_DISPLAY_STYLE_INT32);

        }

    }

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((circular_add_test - 1)), (UNITY_INT)(UNITY_INT32)((ringbuffer_get_head(&ringbuffer_Test))), (

   ((void *)0)

   ), (UNITY_UINT)(147), UNITY_DISPLAY_STYLE_INT32);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT32)((circular_add_test - 1)), (UNITY_INT)(UNITY_INT32)((ringbuffer_get_tail(&ringbuffer_Test))), (

   ((void *)0)

   ), (UNITY_UINT)(148), UNITY_DISPLAY_STYLE_INT32);

}



void test_function_ringbuffer_get_arr(void)

{

    _ringbuffer_t ringbuffer_Test;



    char *arr_sample_pass_1 = "$COMM,1,2,3,4,5#";

    char *arr_sample_pass_2 = "$COMM,1.23,2,-3.456,4,5#";

    char *arr_sample_pass_3 = "$COMM,0,0,0,0,0$COMM,1,2,3,4,5#";

    char *arr_sample_pass_4 = "COMM,0,0,0,0,0#$COMM,1,2,3,4,5#";

    char *arr_sample_pass_5 = "$COMM,1,2,3,4,9COMM,0,0,0,0,0#";

    char *arr_sample_pass_6 = "$COMM,1# $COMM,2,2,0,2#$COMM,3,3,33#   $COMM,4,3,44#";



    char *arr_sample_fail_1 = "COMM,1,2,3,4,5#";

    char *arr_sample_fail_2 = "$COMM,1,2,3,4,5";

    char *arr_sample_fail_3 = "$COMM,aa1,s2,3,4,5#";



    char Temp_data[30], Temp_test, count_arr = 0;

    const unsigned int Size_Array = 60;



    char Arrary_Test[Size_Array], i;

    unsigned char circular_add_test = 20;



    ringbuffer_init(&ringbuffer_Test, Arrary_Test, Size_Array);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((ringbuffer_get_arr(&ringbuffer_Test, Temp_data))), (UNITY_INT)(UNITY_INT8 )((Ringbuffer_Error)), (

   ((void *)0)

   ), (UNITY_UINT)(173), UNITY_DISPLAY_STYLE_INT8);



    while(arr_sample_pass_1[count_arr]!='\0')

    {

        if(!ringbuffer_push(&ringbuffer_Test, arr_sample_pass_1[count_arr]))

        {

            printf("PUSH ERROR\n");

        }

        count_arr++;

    }

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((ringbuffer_get_arr(&ringbuffer_Test, Temp_data))), (UNITY_INT)(UNITY_INT8 )((Ringbuffer_get_arr_done)), (

   ((void *)0)

   ), (UNITY_UINT)(183), UNITY_DISPLAY_STYLE_INT8);

    printf("pass_1: %s\n", Temp_data);



    ringbuffer_init(&ringbuffer_Test, Arrary_Test, Size_Array);

    count_arr = 0;

    while(arr_sample_pass_2[count_arr]!='\0')

    {

        if(!ringbuffer_push(&ringbuffer_Test, arr_sample_pass_2[count_arr]))

        {

            printf("PUSH ERROR\n");

        }

        count_arr++;

    }

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((ringbuffer_get_arr(&ringbuffer_Test, Temp_data))), (UNITY_INT)(UNITY_INT8 )((Ringbuffer_get_arr_done)), (

   ((void *)0)

   ), (UNITY_UINT)(196), UNITY_DISPLAY_STYLE_INT8);

    printf("pass_2: %s\n", Temp_data);



    ringbuffer_init(&ringbuffer_Test, Arrary_Test, Size_Array);

    count_arr = 0;

    while(arr_sample_pass_3[count_arr]!='\0')

    {

        if(!ringbuffer_push(&ringbuffer_Test, arr_sample_pass_3[count_arr]))

        {

            printf("PUSH ERROR\n");

        }

        count_arr++;

    }

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((ringbuffer_get_arr(&ringbuffer_Test, Temp_data))), (UNITY_INT)(UNITY_INT8 )((Ringbuffer_get_arr_done)), (

   ((void *)0)

   ), (UNITY_UINT)(209), UNITY_DISPLAY_STYLE_INT8);

    printf("pass_3: %s\n", Temp_data);



    ringbuffer_init(&ringbuffer_Test, Arrary_Test, Size_Array);

    count_arr = 0;

    while(arr_sample_pass_4[count_arr]!='\0')

    {

        if(!ringbuffer_push(&ringbuffer_Test, arr_sample_pass_4[count_arr]))

        {

            printf("PUSH ERROR\n");

        }

        count_arr++;

    }

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((ringbuffer_get_arr(&ringbuffer_Test, Temp_data))), (UNITY_INT)(UNITY_INT8 )((Ringbuffer_get_arr_done)), (

   ((void *)0)

   ), (UNITY_UINT)(222), UNITY_DISPLAY_STYLE_INT8);

    printf("pass_4: %s\n", Temp_data);



    ringbuffer_init(&ringbuffer_Test, Arrary_Test, Size_Array);

    count_arr = 0;

    while(arr_sample_pass_5[count_arr]!='\0')

    {

        if(!ringbuffer_push(&ringbuffer_Test, arr_sample_pass_5[count_arr]))

        {

            printf("PUSH ERROR\n");

        }

        count_arr++;

    }

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((ringbuffer_get_arr(&ringbuffer_Test, Temp_data))), (UNITY_INT)(UNITY_INT8 )((Ringbuffer_get_arr_done)), (

   ((void *)0)

   ), (UNITY_UINT)(235), UNITY_DISPLAY_STYLE_INT8);

    printf("pass_5: %s\n", Temp_data);



    ringbuffer_init(&ringbuffer_Test, Arrary_Test, Size_Array);

    count_arr = 0;

    while(arr_sample_pass_6[count_arr]!='\0')

    {

        if(!ringbuffer_push(&ringbuffer_Test, arr_sample_pass_6[count_arr]))

        {

            printf("PUSH ERROR\n");

        }

        count_arr++;

    }



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((ringbuffer_get_arr(&ringbuffer_Test, Temp_data))), (UNITY_INT)(UNITY_INT8 )((Ringbuffer_get_arr_done)), (

   ((void *)0)

   ), (UNITY_UINT)(249), UNITY_DISPLAY_STYLE_INT8);

    printf("pass_6_1: %s\n", Temp_data);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((ringbuffer_get_arr(&ringbuffer_Test, Temp_data))), (UNITY_INT)(UNITY_INT8 )((Ringbuffer_get_arr_done)), (

   ((void *)0)

   ), (UNITY_UINT)(251), UNITY_DISPLAY_STYLE_INT8);

    printf("pass_6_2: %s\n", Temp_data);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((ringbuffer_get_arr(&ringbuffer_Test, Temp_data))), (UNITY_INT)(UNITY_INT8 )((Ringbuffer_get_arr_done)), (

   ((void *)0)

   ), (UNITY_UINT)(253), UNITY_DISPLAY_STYLE_INT8);

    printf("pass_6_3: %s\n", Temp_data);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((ringbuffer_get_arr(&ringbuffer_Test, Temp_data))), (UNITY_INT)(UNITY_INT8 )((Ringbuffer_get_arr_done)), (

   ((void *)0)

   ), (UNITY_UINT)(255), UNITY_DISPLAY_STYLE_INT8);

    printf("pass_6_4: %s\n", Temp_data);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((ringbuffer_get_arr(&ringbuffer_Test, Temp_data))), (UNITY_INT)(UNITY_INT8 )((Ringbuffer_Error)), (

   ((void *)0)

   ), (UNITY_UINT)(257), UNITY_DISPLAY_STYLE_INT8);



    ringbuffer_init(&ringbuffer_Test, Arrary_Test, Size_Array);

    count_arr = 0;

    while(arr_sample_fail_1[count_arr]!='\0')

    {

        if(!ringbuffer_push(&ringbuffer_Test, arr_sample_fail_1[count_arr]))

        {

            printf("PUSH ERROR\n");

        }

        count_arr++;

    }

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((ringbuffer_get_arr(&ringbuffer_Test, Temp_data))), (UNITY_INT)(UNITY_INT8 )((Ringbuffer_Error)), (

   ((void *)0)

   ), (UNITY_UINT)(269), UNITY_DISPLAY_STYLE_INT8);



    ringbuffer_init(&ringbuffer_Test, Arrary_Test, Size_Array);

    count_arr = 0;

    while(arr_sample_fail_2[count_arr]!='\0')

    {

        if(!ringbuffer_push(&ringbuffer_Test, arr_sample_fail_2[count_arr]))

        {

            printf("PUSH ERROR\n");

        }

        count_arr++;

    }

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((ringbuffer_get_arr(&ringbuffer_Test, Temp_data))), (UNITY_INT)(UNITY_INT8 )((Ringbuffer_Error)), (

   ((void *)0)

   ), (UNITY_UINT)(281), UNITY_DISPLAY_STYLE_INT8);



    ringbuffer_init(&ringbuffer_Test, Arrary_Test, Size_Array);

    count_arr = 0;

    while(arr_sample_fail_3[count_arr]!='\0')

    {

        if(!ringbuffer_push(&ringbuffer_Test, arr_sample_fail_3[count_arr]))

        {

            printf("PUSH ERROR\n");

        }

        count_arr++;

    }

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((ringbuffer_get_arr(&ringbuffer_Test, Temp_data))), (UNITY_INT)(UNITY_INT8 )((Ringbuffer_Error)), (

   ((void *)0)

   ), (UNITY_UINT)(293), UNITY_DISPLAY_STYLE_INT8);

}
