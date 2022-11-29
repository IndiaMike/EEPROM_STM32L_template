/*
 * eeprom.h
 *
 *  Created on: Nov 10, 2022
 *      Author: Programista
 */

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

#define DATA_EEPROM_BASE_ADDR ((uint32_t)0x08080000) /* Data EEPROM base address */
#define DATA_EEPROM_END_ADDR ((uint32_t)0x080807FF) /* Data EEPROM end address */


typedef struct
{
	uint32_t data1;
	uint32_t data2;
}Eeprom_registers; //struktura danych do której odczytane zostana wartosci z EEPROM

typedef struct
{
	uint16_t zmienna1;
	uint16_t zmienna2;
}TStruct_write;   //struktura do zapisania w EEPROM

#define CONFIG ((Eeprom_registers *) DATA_EEPROM_BASE_ADDR)



void Write_Registers_to_Eeprom(void);

#endif /* INC_EEPROM_H_ */
