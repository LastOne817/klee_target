#include <stdlib.h>
#include "bigint.h"
#include <string.h>

/*
   Adding Two Big Integers
   Saving result in BIGINT* result
   free() Required
   */
int
add_big(BIGINT* a, BIGINT* b, BIGINT* result)
{
    int* buf;
    int i;
    int size;

    if( a == NULL ||
            b == NULL)
        // Invalid Operands
        return BIGINT_NOT_VALID;

    if( result != NULL )
        // Result Destination is not Empty
        // Free to inhibit mem leak
        free_big(result);

    // Allocate enough spaces as calculation buffer
    buf = (int*)malloc(sizeof(int) *  (MAX( a -> len, b -> len) + 1));

    for( i = 0 ; i < MAX(a->len, b->len) + 1 ; i++ )
    {
        *(buf + i) = 0;
    }
    

    for( i = 0 ; i < MIN(a -> len, b -> len) ; i++ )
    {
        *(buf + i) = *(a -> val + i) + *(b -> val + i);
    }

    if(a->len < b->len)
    {
        for( ; i < b -> len ; i++ )
        {
            *(buf + i) = *(b -> val + i);
        }
    }
    else
    {
        for( ; i < a -> len ; i++ )
        {
            *(buf + i) = *(a -> val + i);
        }
    }

    // Normalize Big Integer
    size = normalize_big(buf, MAX(a->len, b->len) + 1);

    if( size <= 0 )
        return NORMALIZATION_FAILED;
    
    result = (BIGINT*)malloc(sizeof(BIGINT));
    result -> len = size;
    result -> val = buf;

    return 0;
}

/*
   Subtracting Two Big Integers
   Saving result in BIGINT* result
   free() Required
   */
int
sub_big(BIGINT* a, BIGINT* b, BIGINT* result)
{
    int* buf;
    int i;
    int size;

    if( a == NULL ||
            b == NULL)
        // Invalid Operands
        return BIGINT_NOT_VALID;

    if( result != NULL )
        // Result Destination is not Empty
        // Free to inhibit mem leak
        free_big(result);

    // Allocate enough spaces as calculation buffer
    buf = (int*)malloc(sizeof(int) *  (MAX( a -> len, b -> len) + 1));

    for( i = 0 ; i < MAX(a->len, b->len) + 1 ; i++ )
    {
        *(buf + i) = 0;
    }

    for( i = 0 ; i < MIN(a -> len, b -> len) ; i++ )
    {
        *(buf + i) = *(a -> val + i) - *(b -> val + i);
    }

    if(a->len < b->len)
    {
        for( ; i < b -> len ; i++ )
        {
            *(buf + i) = - *(b -> val + i);
        }
    }
    else
    {
        for( ; i < a -> len ; i++ )
        {
            *(buf + i) = *(a -> val + i);
        }
    }

    // Normalize Big Integer
    size = normalize_big(buf, MAX(a->len, b->len) + 1);

    if( size <= 0 )
        return NORMALIZATION_FAILED;
    
    result = (BIGINT*)malloc(sizeof(BIGINT));
    result -> len = size;
    result -> val = buf;

    return 0;
}

/*
   Multiplying Two Big Integers
   Saving result in BIGINT* result
   free() Required
   */
int
mul_big(BIGINT* a, BIGINT* b, BIGINT* result)
{
    int* buf;
    int i, j;
    int size;

    if( a == NULL ||
            b == NULL)
        // Invalid Operands
        return BIGINT_NOT_VALID;

    if( result != NULL )
        // Result Destination is not Empty
        // Free to inhibit mem leak
        free_big(result);

    // Allocate enough spaces as calculation buffer
    buf = (int*)malloc(sizeof(int) *  a -> len * b -> len);

    for( i = 0 ; i < MAX(a->len, b->len) + 1 ; i++ )
    {
        *(buf + i) = 0;
    }

    for( i = 0 ; i < a -> len ; i++ )
    {
        for( j = 0 ; j < b -> len ; j++ )
        {
            *(buf + i) += *(a->val + i) * *(b->val + j);
        }   
    }
    
    // Normalize Big Integer
    size = normalize_big(buf, a->len * b->len);

    if( size <= 0 )
        return NORMALIZATION_FAILED;
    
    result = (BIGINT*)malloc(sizeof(BIGINT));
    result -> len = size;
    result -> val = buf;

    return 0;
}

/*
   Comparing Two Big Integers
   Return negative if a is smaller,
        0 if same,
        positive if b is smaller.
   */
int
compare_big(BIGINT* a, BIGINT* b)
{
    int i;

    // Check whether a and b are valid Big Integers
    if( a == NULL ||
            b == NULL)
        return BIGINT_NOT_VALID;

    // If signs are different
    if( *(a->val) * *(b->val) < 0)
    {
        if( *(a->val) < 0 )
            return -1;
        else return 1;
    }

    // If both a and b are positive
    if( *(a->val) > 0 )
    {
        if( a->len < b->len )
            return -1;
        else if( a->len > b->len )
            return 1;
        else
        {
            for( i = a->len - 1 ; i >= 0 ; i-- )
            {
                if( *(a->val + i) < *(b->val + i) )
                    return -1;
                else if( *(a->val + i) > *(b->val + i) )
                    return 1;
            }
            
        }
    }
    return 0;
}

/*
   Cloning Big Integer
   free() Required
   */
int
clone_big(BIGINT* src, BIGINT* dest)
{
    // Check whether src is valid
    if( src == NULL )
        return BIGINT_NOT_VALID;

    // Check whether dest is already acquired
    if( dest != NULL )
        free(dest);

    dest = (BIGINT*)malloc(sizeof(BIGINT));
    dest->len = src->len;
    dest->val = (int*)malloc(sizeof(int) * src->len);

    return 0;
}

/*
   Creating Big Integer from String
   Returns null if String is Invalid
   free() Required
   */
BIGINT*
from_str(char* src)
{
    int len;
    int i;
    int sign;
    BIGINT* result;

    if( src == NULL )
        return NULL;

    if( (*src < '0' || *src > '9') &&
            *src != '-' )
        return NULL;
    
    len = strlen(src);

    for( i = 1 ; i < len ; i++ )
    {
        if( *(src + i) < '0' || *(src + i) > '9' )
            return NULL;
    }

    result = (BIGINT*)malloc(sizeof(BIGINT));
    result->len = (len + 3) / 4;
    result->val = (int*)malloc(sizeof(int) * result->len);

    i = 0;
    if( *src == '-' )
    {
        sign = -1;
        i++;
    }
    else
    {
        sign = 1;
    }

    for( ; i < len ; i++ )
    {
        
    }
    
}

/*
   Returns representing string
   free() Required
   */
char* to_str(BIGINT* src);

/*
   Deallocated Memory after use
   */
int free_big(BIGINT* num)
{
    if( num == NULL )
        return BIGINT_NOT_VALID;

    free( num->val );
    free( num );

    return 0;
}

/*
   Normalize Big Integer Array
   Reallocate Memory to fit
   Returns whether Success
   */
int
normalize_big(int* val, int box_size)
{
    int i;
    int* buf;
    int size;

    // Check whether val is properly allocated
    if( val == NULL )
        return NORMALIZATION_FAILED;

    // Allocate Buffer
    buf = (int*)malloc(sizeof(int) * box_size);
    // Initialize Buffer
    for( i = 0 ; i < box_size ; i++ )
    {
        *(buf + i) = 0;
    }

    // Normalize Values
    for( i = 0 ; i < box_size ; i++ )
    {
        if( *(val + i) >= 0)
        {
            if( *(val + i) >= 10000)
            {
                *(val + i + 1) += *(val + i) / 10000;
                *(val + i) %= 10000;
            }
        }
        else
        {
            if( *(val + i) <= -10000)
            {
                *(val + i + 1) += *(val + i) / 10000;
                *(val + i) %= 10000;
            }
        }
    }

    size = box_size - 1;
    while( *(val + size) != 0 )
    {
        size--;
    }
    
    free(val);
    val = buf;

    return size;
}
