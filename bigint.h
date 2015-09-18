#ifndef __BIGINT__
#define __BIGINT__

#define BIGINT_NOT_VALID -1

#define MAX(n,m) ((n)>(m))?(n):(m)
#define MIN(n,m) ((n)<(m))?(n):(m)

/*
   Struct for Big Integer
   */
typedef struct _bigint
{
    /*
       Actual Value Storage
       For convenience, modulo 10^4
       */
    int* val;
    int len;
}
BIGINT;

/*
   Adding Two Big Integers
   Saving result in BIGINT* result
   free() Required
   */
int add_big(BIGINT* a, BIGINT* b, BIGINT* result);

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

#endif
