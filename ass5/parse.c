#include "parse.h"
#include "mystring.h"
#include <stdlib.h>
void outputParseData(parse_data_struct_t* pOutput)
{
	if(pOutput->address != DEFAULT_ADDRESS)
	{
		printf("Address: %x\n", pOutput->address);
	}
	if(pOutput->dataLength != DEFAULT_DATA_LENGTH)
	{
		printf("Data length: %x\n", pOutput->dataLength);
	}
	if(pOutput->data[0] != DEFAULT_DATA)
	{
		printf("Data: %s\n", pOutput->data);
	}
}
void outputStatus(parse_status_t* pStatus)
{
	switch(*pStatus)
	{
		case e_parseStatus_done:
			printf("Done!\n");
			break;
		case e_parseStatus_inprogress:
			printf("Inprogress!\n");
			break;
		case e_parseStatus_error:
			printf("Error!\n");
			break;
		default:
			printf("Undefined!\n");
			break;
	}
}
uint32_t setHex(uint8_t pInput[], uint8_t mode, uint8_t address)
{
	uint8_t count = 0;
	uint32_t temp = 0;
	for (count = 0; count < mode/4; ++count)
	{
		SET_8BIT(temp, pInput[count + address], pInput[ ++count + address]);
	}
	return temp;
}

parse_status_t parseData(uint8_t pInput[], parse_data_struct_t *pOutput)
{
	parse_status_t status;
	if(pInput[0] == 'S')
	{
		switch(pInput[1])
		{
		case '0':
			pOutput->dataLength = setHex(pInput,MODE_8BIT,2);
			pOutput->address = setHex(pInput,MODE_16BIT,4);
			strCoppy(pOutput->data,pInput,8,(pOutput->dataLength-3)*2);
			status = e_parseStatus_inprogress;
			break;
		case '1':
			pOutput->dataLength = setHex(pInput,MODE_8BIT,2);
			pOutput->address = setHex(pInput,MODE_16BIT,4);
			strCoppy(pOutput->data,pInput,8,(pOutput->dataLength-3)*2);
			status = e_parseStatus_inprogress;
			break;
		case '2':
			pOutput->dataLength = setHex(pInput,MODE_8BIT,2);
			pOutput->address = setHex(pInput,MODE_24BIT,4);
			strCoppy(pOutput->data,pInput,8,(pOutput->dataLength-4)*2);
			status = e_parseStatus_inprogress;
			break;
		case '3':
			pOutput->dataLength = setHex(pInput,MODE_8BIT,2);
			pOutput->address = setHex(pInput,MODE_32BIT,4);
			strCoppy(pOutput->data,pInput,8,(pOutput->dataLength-5)*2);
			status = e_parseStatus_inprogress;
			break;
		case '5':
			pOutput->dataLength = setHex(pInput,MODE_8BIT,2);
			pOutput->address = DEFAULT_ADDRESS;
			strCoppy(pOutput->data,pInput,4,8);
			status = e_parseStatus_inprogress;
			break;
		case '7':
			pOutput->dataLength = setHex(pInput,MODE_8BIT,2);
			pOutput->address = setHex(pInput,MODE_32BIT,4);
			pOutput->data[0] = DEFAULT_DATA;
			status = e_parseStatus_done;
			break;
		case '8':
			pOutput->dataLength = setHex(pInput,MODE_8BIT,2);
			pOutput->address = setHex(pInput,MODE_24BIT,4);
			pOutput->data[0] = DEFAULT_DATA;
			status = e_parseStatus_done;
			break;
		case '9':
			pOutput->dataLength = setHex(pInput,MODE_8BIT,2);
			pOutput->address = setHex(pInput,MODE_16BIT,4);
			pOutput->data[0] = DEFAULT_DATA;
			status = e_parseStatus_done;
			break;
		default:
			pOutput->dataLength = DEFAULT_DATA_LENGTH;
			pOutput->address = DEFAULT_ADDRESS;
			pOutput->data[0] = DEFAULT_DATA;
			status = e_parseStatus_error;
			break;
		}
	}
	return status;
}

int main(int argc, char const *argv[])
{
    uint8_t string[79];
    parse_status_t status = e_parseStatus_undefined;
    parse_data_struct_t pOutput;
    FILE* pFile;
    pFile = fopen("filehandling.srec","r");
    while(!feof(pFile))
    {
        fgetLine(pFile,string,79,'S');
	    status = parseData(string,&pOutput);
	    outputParseData(&pOutput);
	    outputStatus(&status);
	}
    return 0;
}