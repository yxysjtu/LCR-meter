//#include "dds.h"
//
//AD9834::AD9834(float mclk_in_MHz, const std::function<void(uint16_t)>& spi_write_func)
//  : mclk(mclk_in_MHz), spi(spi_write_func)
//{
//  ;
//}
//
//void AD9834::set_freq(float f_in_Hz)
//{
//  if (f_in_Hz < 0 || f_in_Hz > mclk * (1e6f/2))
//    return;
//  uint32_t freq_word = (f_in_Hz / 1e6f / mclk) * (1u << 31);
//  int round = (freq_word & ((1<<3)-1)) >= 4 ? 1 : 0;
//  freq_word >>= 3;
//  freq_word += round;
//  spi(0x2100);
//  spi(0x4000 | (freq_word & ((1<<14)-1)));
//  spi(0x4000 | freq_word >> 14);
//  spi(0x2000);
//}
//
