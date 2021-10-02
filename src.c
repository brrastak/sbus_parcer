#include "inc.h"


void printSbusSt(sbus_dbg_port_t port) {
	switch (port) {
	case print:
	{
		for (int i = 0; i < SBUS_NUMBER_OF_CHENNELS; i++) {
			printf("%4u", sbus_st.channel[i]);
			if (i < SBUS_NUMBER_OF_CHENNELS - 1) {
				printf(",");
			}
		}
		printf("\n");
		break;
	}
	default:
		return;
	}

}

void printArrU8(uint8_t* input, int length){
	for (int i = 0; i < length; i++) {
		printf("%3u", input[i]);
		if (i < length - 1) {
			printf(",");
		}
	}
	printf("\n");
}

void printArrU16(uint16_t* input, int length) {
	for (int i = 0; i < length; i++) {
		printf("%5u", input[i]);
		if (i < length - 1) {
			printf(",");
		}
	}
	printf("\n");
}

