#include <stdio.h>
#include <stdint.h>

#define SBUS_STARTBYTE         0x0f ///< ��������� ���� ��������� sbus
#define SBUS_ENDBYTE           0x00 ///< �������� ���� ��������� sbus
#define SBUS_NUMBER_OF_CHENNELS 18 ///<  ���������� ������� sbus


///��������� ��� ������ ������� �� sbus
typedef struct {
	uint16_t channel[SBUS_NUMBER_OF_CHENNELS]; ///< �������� ������� sbus
	uint8_t sbusTrustFlag; ///< ���� ������������ � 1, ����� ��������� sbus ����� ��������
}sbus_st_t;

///���������� ������ ��� �������� ��������� �������� ������� sbus
sbus_st_t sbus_st;

/**
 * @brief ������ ������� sbus
 * @details ������ ���������� ��������� ��������� ��������� ������ �����
 * � ���������� �� � �������.
 * @param input ��������� �� ������ �������� ��������
 * @param length ����� ��������� ������ ��������
 * @retval None
 */
void parceSbus(uint8_t* input, int length);

///����� ������ ���������� ���������� ��� sbus
typedef enum SBUS_DBG_PORT_E{
	uart,
	xbee,
	usb,
	print
}sbus_dbg_port_t;

/**
 * @brief ������� ������� ��������� sbus_st � ��������� ����
 * @param port ��������� �� ������ �������� ��������
 * @retval None
 */
void printSbusSt(sbus_dbg_port_t port);

/**
 * @brief ������� ����� ���� uint_8 � �������
 * @param input ��������� �� ������
 * @param length ����� �������
 * @retval None
 */
void printArrU8(uint8_t* input, int length);

/**
 * @brief ������� ����� ���� uint_16 � �������
 * @param input ��������� �� ������
 * @param length ����� �������
 * @retval None
 */
void printArrU16(uint16_t* input, int length);

