#include <stdlib.h>
#include "bigint.h"

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

    for( i = 0 ; i < MIN(a -> len, b -> len) ; i++ )
    {
        
    }
    

    return 0;
}

/*
   Subtracting Two Big Integers
   Saving result in BIGINT* result
   free() Required
   */
int sub_big(BIGINT* a, BIGINT* b, BIGINT* result);


/*
   Multiplying Two Big Integers
   Saving result in BIGINT* result
   free() Required
   */
int mul_big(BIGINT* a, BIGINT* b, BIGINT* result);

/*
   Comparing Two Big Integers
   Return negative if a is smaller,
        0 if same,
        positive if b is smaller.
   */
int compare_big(BIGINT* a, BIGINT* b);

/*
   Cloning Big Integer
   free() Required
   */
int clone_big(BIGINT* src, BIGINT* dest);

/*
   Creating Big Integer from String
   Returns null if String is Invalid
   free() Required
   */
BIGINT* from_str(char* src);

/*
   Returns representing string
   free() Required
   */
char* to_str(BIGINT* src);

/*
   Deallocated Memory after use
   */
int free_big(BIGINT* num);
