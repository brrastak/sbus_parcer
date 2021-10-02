#include <stdio.h>
#include <stdint.h>

#define SBUS_STARTBYTE         0x0f ///< стартовый байт протокола sbus
#define SBUS_ENDBYTE           0x00 ///< конечный байт протокола sbus
#define SBUS_NUMBER_OF_CHENNELS 18 ///<  количество каналов sbus


///структура для приема посылок от sbus
typedef struct {
	uint16_t channel[SBUS_NUMBER_OF_CHENNELS]; ///< Значения каналов sbus
	uint8_t sbusTrustFlag; ///< Флаг выставляется в 1, когда значениям sbus можно доверять
}sbus_st_t;

///глобальный объект для хранения последних значений каналов sbus
sbus_st_t sbus_st;

/**
 * @brief Парсер посылок sbus
 * @details Данный обработчик позваляет принимать сообщения разной длины
 * и отправляет их в очередь.
 * @param input Указатель на массив принятых значений
 * @param length длина принятого пакета значений
 * @retval None
 */
void parceSbus(uint8_t* input, int length);

///выбор вывода отладочной ниформации для sbus
typedef enum SBUS_DBG_PORT_E{
	uart,
	xbee,
	usb,
	print
}sbus_dbg_port_t;

/**
 * @brief выводит текущую структуру sbus_st в выбранный порт
 * @param port Указатель на массив принятых значений
 * @retval None
 */
void printSbusSt(sbus_dbg_port_t port);

/**
 * @brief выводит масси топа uint_8 в консоль
 * @param input указатель на массив
 * @param length длина массива
 * @retval None
 */
void printArrU8(uint8_t* input, int length);

/**
 * @brief выводит масси топа uint_16 в консоль
 * @param input указатель на массив
 * @param length длина массива
 * @retval None
 */
void printArrU16(uint16_t* input, int length);

