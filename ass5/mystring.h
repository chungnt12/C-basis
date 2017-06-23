#ifndef __MYSTRING_H_
#define __MYSTRING_H_
#include <stdio.h>
#include <stdint.h>
#define TRUE 1
#define FALSE 0

#define DEBUG 0

#if defined(DEBUG) && (DEBUG)
	#define PRINTF  printf
#else
	#define PRINTF
#endif

/**
 * [getLine description]
 * @param str [description]
 * @param len [description]
 */
void getLine(uint8_t* str);
/**
 * [strFindIn description]
 * @param  str1 [description]
 * @param  str2 [description]
 * @return      [description]
 */
uint8_t strFindIn(uint8_t* str1, uint8_t* str2);

void fgetLine(FILE* pFile, uint8_t* string, uint8_t length, uint8_t condition);

void strCoppy(uint8_t* str1, uint8_t* str2, uint8_t begin, uint8_t stop);

#endif /*__MYSTRING_H_*/