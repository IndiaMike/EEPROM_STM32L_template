/*
 * eeprom.c
 *
 *  Created on: Nov 10, 2022
 *      Author: Programista
 */
#include "main.h"
#include "eeprom.h"

TStruct_write data_to_write;

//uint32_t data_to_write;


static void LockEeprom(void);
static void EepromProgram(uint32_t addr, uint32_t ee_data);
static void UnlockEeprom(void);

void Write_Registers_to_Eeprom(void)
{

uint32_t i;
uint32_t* p_tFlashRegs;

   i = 0;
   p_tFlashRegs = (uint32_t*)&data_to_write;   /* Point to data to write */

   UnlockEeprom(); /* Unlock the EEPROM and enable flash interrupts */
   FLASH->PECR = FLASH->PECR & ~(FLASH_PECR_ERASE | FLASH_PECR_DATA); /* Reset the ERASE and DATA                                                                               bits in the FLASH_PECR register to disable any residual erase */

   /* Put the next line in a loop if sequential bits to be written with i as loop counter */

   EepromProgram(DATA_EEPROM_BASE_ADDR + (4 * i), *(p_tFlashRegs + i)); /* Increase eeprom address by 4 for each                                                                word to write.  */
   LockEeprom(); /* Lock the EEPROM */
}

/* Unlock the EEPROM: */

void UnlockEeprom(void)
{
   while ((FLASH->SR & FLASH_SR_BSY) != 0) /* Wait for FLASH to be free */
   {

/*   insert timeout test */


   }


   if ((FLASH->PECR & FLASH_PECR_PELOCK) != 0) /* If PELOCK is locked */
   {
      FLASH->PEKEYR = FLASH_PEKEY1; /* Unlock PELOCK */
      FLASH->PEKEYR = FLASH_PEKEY2;
   }
   FLASH->PECR = FLASH->PECR | (FLASH_PECR_ERRIE | FLASH_PECR_EOPIE); /* enable flash interrupts */
}

/**
* Brief This function programs a word of data EEPROM.
* The ERASE bit and DATA bit are cleared in PECR at the beginning
* words are automatically erased if required before programming
* Param addr is the 32-bit EEPROM address to program, data is the 32 bit word to program
* Retval None
*/


void EepromProgram(uint32_t addr, uint32_t ee_data)
{
/* NOTE: The EEPROM must be unlocked and the flash interrupts must have been enabled prior to calling this function.*/


   *(uint32_t *)(addr) = ee_data; /* write data to EEPROM */


   __WFI();
}

/* Lock the EEPROM: */

void LockEeprom(void)
{
   while ((FLASH->SR & FLASH_SR_BSY) != 0) /* Wait for FLASH to be free */
   {
/*   insert timeout test */
   }
   FLASH->PECR = FLASH->PECR & ~(FLASH_PECR_ERRIE | FLASH_PECR_EOPIE); /* disable flash interrupts */
   FLASH->PECR = FLASH->PECR | FLASH_PECR_PELOCK; /* Lock memory with PELOCK */
}
