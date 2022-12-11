#ifndef __THREAD_CONSTANTS_H
#define __THREAD_CONSTANTS_H

/* 12 LSB used for fractional part. */
#define MLFQ_PRECISION 12

/* Add two fixed-point value. */
#define MLFQ_ADD(X,Y) (X + Y)

/* Substract two fixed-point value. */
#define MLFQ_SUB(X,Y) (X - Y)

/* Multiply a fixed-point value X by an int value Y. */
#define MLFQ_MUL_PRE(X,Y) (X * Y)

/* Divide a fixed-point value X by an int value Y. */
#define MLFQ_DIV_PRE(X,Y) (X / Y)

/* Add a fixed-point value X and an int value Y. */
#define MLFQ_ADD_PRE(X,Y) (X + (Y << MLFQ_PRECISION))

/* Substract an int value Y from a fixed-point value X */
#define MLFQ_SUB_PRE(X,Y) (X - (Y << MLFQ_PRECISION))

/* Convert a value to fixed-point value. */
#define MLFQ_CONST(X) ((int)(X << MLFQ_PRECISION))

/* Multiply two fixed-point value. */
#define MLFQ_MUL(X,Y) ((int)(((int64_t) X) * Y >> MLFQ_PRECISION))

/* Divide two fixed-point value. */
#define MLFQ_DIV(X,Y) ((int)((((int64_t) X) << MLFQ_PRECISION) / Y))

/* Get integer part of a fixed-point value. */
#define MLFQ_INT_PART(X) (X >> MLFQ_PRECISION)

/* Get rounded integer of a fixed-point value. */
#define MLFQ_ROUND(X) (X >= 0 ? ((X + (1 << (MLFQ_PRECISION - 1))) >> MLFQ_PRECISION) \
        : ((X - (1 << (MLFQ_PRECISION - 1))) >> MLFQ_PRECISION))

#endif /* threads/constants.h */
