#ifndef DDS_H_
#define DDS_H_

//#include <cstdint>
//#include <functional>

class AD9834
{
public:
	SPI& AD9834_spi;
	GPIO& CS;

	float mclk_in_MHz;
    AD9834(SPI& AD9834_spi, GPIO& CS, float mclk_in_MHz): AD9834_spi(AD9834_spi), CS(CS), mclk_in_MHz(mclk_in_MHz){}
	void set_freq(float f_in_Hz){
		if (f_in_Hz < 0 || f_in_Hz > mclk_in_MHz * (1e6f/2))
			return;
		  uint32_t freq_word = (f_in_Hz / 1e6f / mclk_in_MHz) * (1u << 31);
		  int round = (freq_word & ((1<<3)-1)) >= 4 ? 1 : 0;
		  freq_word >>= 3;
		  freq_word += round;
		  CS.set_pin(0);
		  AD9834_spi.write(0x2100);
		  AD9834_spi.write(0x4000 | (freq_word & ((1<<14)-1)));
		  AD9834_spi.write(0x4000 | freq_word >> 14);
		  AD9834_spi.write(0x2000);
		  CS.set_pin(1);
  }
};

#endif /* DDS_H_ */
