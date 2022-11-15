
#include "unity.h"
#include "ringbuffer.h"

#define Size_ringbuffer 1000
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
    char Arrary_Test[Size_ringbuffer];

    Temp = ringbuffer_init(&ringbuffer_Test, Arrary_Test, Size_ringbuffer);
    TEST_ASSERT_EQUAL_INT8(Ringbuffer_OK, Temp);
    TEST_ASSERT_EQUAL_INT32(Init_value_head, ringbuffer_Test.head);
    TEST_ASSERT_EQUAL_INT32(Init_value_head, ringbuffer_Test.tail);
    TEST_ASSERT_EQUAL_INT64(Arrary_Test, ringbuffer_Test.data);
}

void test_function_ringbuffer_init_error(void)
{
    _ringbuffer_t ringbuffer_Test;
    _rb_status_ Temp = 0;

    const unsigned int Init_value_head = 0;
    const unsigned int Init_value_tail = 0;
    char Arrary_Test[Size_ringbuffer];

    Temp = ringbuffer_init(&ringbuffer_Test, Arrary_Test, 0);
    TEST_ASSERT_EQUAL_INT8(Ringbuffer_Error, Temp);
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


    TEST_ASSERT_EQUAL_INT64(Arrary_Test, ringbuffer_Test.data);             // check address
    TEST_ASSERT_EQUAL_INT32(Init_value_head, ringbuffer_Test.head);         // check khởi tạo head
    TEST_ASSERT_EQUAL_INT32(Init_value_head, ringbuffer_Test.tail);         // check khơi tạo tail
    TEST_ASSERT_EQUAL_INT32(Size_Array+1, ringbuffer_Test.buffer_length);   // check leng array
    
    for(i=0; i<Size_Array; i++)
    {
        char Temp_data = 0;
        if(ringbuffer_push(&ringbuffer_Test, i))
        {
            if(ringbuffer_pop(&ringbuffer_Test, &Temp_data) == Ringbuffer_pop_done)
            {
                TEST_ASSERT_EQUAL_INT32(Temp_data, i);
            }
        }
    }
    TEST_ASSERT_EQUAL_INT32(Size_Array, ringbuffer_get_head(&ringbuffer_Test));
    TEST_ASSERT_EQUAL_INT32(Size_Array, ringbuffer_get_tail(&ringbuffer_Test));
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


    TEST_ASSERT_EQUAL_INT64(Arrary_Test, ringbuffer_Test.data);             // check address
    TEST_ASSERT_EQUAL_INT32(Init_value_head, ringbuffer_Test.head);         // check khởi tạo head
    TEST_ASSERT_EQUAL_INT32(Init_value_head, ringbuffer_Test.tail);         // check khơi tạo tail
    TEST_ASSERT_EQUAL_INT32(Size_Array+1, ringbuffer_Test.buffer_length);   // check độ dài chuỗi array
    
    for(i=0; i<Size_Array + circular_add_test; i++)
    {
        char Temp_data = 0;
        if(ringbuffer_push(&ringbuffer_Test, i))
        {
            if(ringbuffer_pop(&ringbuffer_Test, &Temp_data) == Ringbuffer_pop_done)
            {
                TEST_ASSERT_EQUAL_INT32(Temp_data, i);
            }
        }
    }
    TEST_ASSERT_EQUAL_INT32(circular_add_test - 1, ringbuffer_get_head(&ringbuffer_Test));
    TEST_ASSERT_EQUAL_INT32(circular_add_test - 1, ringbuffer_get_tail(&ringbuffer_Test));
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


    TEST_ASSERT_EQUAL_INT64(Arrary_Test, ringbuffer_Test.data);             // check address
    TEST_ASSERT_EQUAL_INT32(Init_value_head, ringbuffer_Test.head);         // check khởi tạo head
    TEST_ASSERT_EQUAL_INT32(Init_value_head, ringbuffer_Test.tail);         // check khơi tạo tail
    TEST_ASSERT_EQUAL_INT32(Size_Array+1, ringbuffer_Test.buffer_length);   // check độ dài chuỗi array
    
    TEST_ASSERT_EQUAL_INT8(ringbuffer_pop(&ringbuffer_Test, &Temp_data), Ringbuffer_Error);

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
            TEST_ASSERT_EQUAL_INT32(Temp_data, i);
        }
    }
    TEST_ASSERT_EQUAL_INT32(circular_add_test - 1, ringbuffer_get_head(&ringbuffer_Test));
    TEST_ASSERT_EQUAL_INT32(circular_add_test - 1, ringbuffer_get_tail(&ringbuffer_Test));
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
/*||||||||||||||||||||||||||||||||||||||||(pass 1)||||||||||||||||||||||||||||||||||||||||*/
    ringbuffer_init(&ringbuffer_Test, Arrary_Test, Size_Array);
    TEST_ASSERT_EQUAL_INT8(ringbuffer_get_arr(&ringbuffer_Test, Temp_data), Ringbuffer_Error);
    
    while(arr_sample_pass_1[count_arr]!='\0')
    {
        if(!ringbuffer_push(&ringbuffer_Test, arr_sample_pass_1[count_arr]))
        {
            printf("PUSH ERROR\n");
        }
        count_arr++;
    }
    TEST_ASSERT_EQUAL_INT8(ringbuffer_get_arr(&ringbuffer_Test, Temp_data), Ringbuffer_get_arr_done);
    printf("pass_1: %s\n", Temp_data);
/*||||||||||||||||||||||||||||||||||||||||(pass 2)||||||||||||||||||||||||||||||||||||||||*/
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
    TEST_ASSERT_EQUAL_INT8(ringbuffer_get_arr(&ringbuffer_Test, Temp_data), Ringbuffer_get_arr_done);
    printf("pass_2: %s\n", Temp_data);
/*||||||||||||||||||||||||||||||||||||||||(pass 3)||||||||||||||||||||||||||||||||||||||||*/
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
    TEST_ASSERT_EQUAL_INT8(ringbuffer_get_arr(&ringbuffer_Test, Temp_data), Ringbuffer_get_arr_done);
    printf("pass_3: %s\n", Temp_data);
/*||||||||||||||||||||||||||||||||||||||||(pass 4)||||||||||||||||||||||||||||||||||||||||*/
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
    TEST_ASSERT_EQUAL_INT8(ringbuffer_get_arr(&ringbuffer_Test, Temp_data), Ringbuffer_get_arr_done);
    printf("pass_4: %s\n", Temp_data);
/*||||||||||||||||||||||||||||||||||||||||(pass 5)||||||||||||||||||||||||||||||||||||||||*/
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
    TEST_ASSERT_EQUAL_INT8(ringbuffer_get_arr(&ringbuffer_Test, Temp_data), Ringbuffer_get_arr_done);
    printf("pass_5: %s\n", Temp_data);
/*||||||||||||||||||||||||||||||||||||||||(pass 6)||||||||||||||||||||||||||||||||||||||||*/
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

    TEST_ASSERT_EQUAL_INT8(ringbuffer_get_arr(&ringbuffer_Test, Temp_data), Ringbuffer_get_arr_done);
    printf("pass_6_1: %s\n", Temp_data);
    TEST_ASSERT_EQUAL_INT8(ringbuffer_get_arr(&ringbuffer_Test, Temp_data), Ringbuffer_get_arr_done);
    printf("pass_6_2: %s\n", Temp_data);
    TEST_ASSERT_EQUAL_INT8(ringbuffer_get_arr(&ringbuffer_Test, Temp_data), Ringbuffer_get_arr_done);
    printf("pass_6_3: %s\n", Temp_data);
    TEST_ASSERT_EQUAL_INT8(ringbuffer_get_arr(&ringbuffer_Test, Temp_data), Ringbuffer_get_arr_done);
    printf("pass_6_4: %s\n", Temp_data);
    TEST_ASSERT_EQUAL_INT8(ringbuffer_get_arr(&ringbuffer_Test, Temp_data), Ringbuffer_Error);
/*||||||||||||||||||||||||||||||||||||||||(fail 1)||||||||||||||||||||||||||||||||||||||||*/
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
    TEST_ASSERT_EQUAL_INT8(ringbuffer_get_arr(&ringbuffer_Test, Temp_data), Ringbuffer_Error);
/*||||||||||||||||||||||||||||||||||||||||(fail 2)||||||||||||||||||||||||||||||||||||||||*/
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
    TEST_ASSERT_EQUAL_INT8(ringbuffer_get_arr(&ringbuffer_Test, Temp_data), Ringbuffer_Error);
/*||||||||||||||||||||||||||||||||||||||||(fail 3)||||||||||||||||||||||||||||||||||||||||*/
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
    TEST_ASSERT_EQUAL_INT8(ringbuffer_get_arr(&ringbuffer_Test, Temp_data), Ringbuffer_Error);
}

// for(int i=0; i < count_arr; i++)
// {
//     if(ringbuffer_pop(&ringbuffer_Test, &Temp_test))
//     {
//         printf("%c", Temp_test);
//     }
//     else
//     {
//         printf("errror\n");
//         break;
//     }
// }