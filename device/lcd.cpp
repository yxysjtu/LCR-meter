//#include "lcd.h"
//
////这里定义在库内部而不是外部，因为这个类不是我设计的，也懒得改接口细节了
//
//GPIO lcd_cs(GPIO_LCD_PORT, GPIO_LCD_CS_PIN);
//GPIO lcd_dc(GPIO_LCD_PORT, GPIO_LCD_DC_PIN);
//
//SPI lcd_spi(SPI_LCD_INST);
//
//void lcd_callback(SpiCmd cmd, uint8_t* pdata, size_t size)
//{
//  switch (cmd)
//  {
//  case SpiCmd::cs_low:
//    lcd_cs.set_pin(0);
//    break;
//  case SpiCmd::cs_high:
//    lcd_cs.set_pin(1);
//    break;
//  case SpiCmd::dc_low:
//    lcd_dc.set_pin(0);
//    break;
//  case SpiCmd::dc_high:
//    lcd_dc.set_pin(1);
//    break;
//  case SpiCmd::reset_low:
//    // HAL_GPIO_WritePin(LCD_RES_GPIO_Port, LCD_RES_Pin, GPIO_PIN_RESET);
//    break;
//  case SpiCmd::reset_high:
//    // HAL_GPIO_WritePin(LCD_RES_GPIO_Port, LCD_RES_Pin, GPIO_PIN_SET);
//    break;
//  case SpiCmd::delay:
//    HAL_Delay(size);
//    break;
//
//  case SpiCmd::transmit:
//  {
//    //spi_transmit_8(pdata, size);
//    lcd_spi.transmitDatas_blocking(pdata, size);
//  }
//
//  }
//}
