#ifndef __PARSE_H_
#define __PARSE_H_

#include <stdio.h>
#include <stdint.h>

#define MAX_DATA_SIZE 64 /*size max data*/
#define MAX_STRING_LENGTH 79 /*length string max */

#define SET_8BIT(output,byteH,byteL) output = (((byteH - 48) << 4) | (byteL - 48))
#define MODE_8BIT 8
#define MODE_16BIT 16
#define MODE_24BIT 24
#define MODE_32BIT 32

#define DEFAULT_ADDRESS 0xffffffff
#define DEFAULT_DATA_LENGTH 0xff
#define DEFAULT_DATA '\0'

typedef enum {
    e_parseStatus_done = 0U,
    e_parseStatus_inprogress = 1U,
    e_parseStatus_error = 2U,
    e_parseStatus_undefined = 3U
} parse_status_t;

typedef struct
{
    uint32_t address;
    uint8_t data[MAX_DATA_SIZE];
    uint8_t dataLength;
} parse_data_struct_t;
parse_status_t parseData(uint8_t pInput[], parse_data_struct_t *pOutput);


#endif /*__PARSE_H_*/

