
#ifndef LSTD_H_
#define LSTD_H_

/*Integer 8bits data type*/
typedef unsigned char       u8_t;
typedef signed char         s8_t;

/*Integer 16bits data type*/
typedef unsigned short int u16_t;
typedef signed short int   s16_t;

/*Integer 32bits data type*/
typedef unsigned long int  u32_t;
typedef signed long int    s32_t;

/*Float 32bits data type*/
typedef float              f32_t;

/*Float 64bits data type*/
typedef double             f64_t;

typedef unsigned long long  u64_t;

typedef  void(*CallbackFunc_t)(void);

#define NULL_PTR  ((void *) 0)


#endif /* LSTD_H_ */
