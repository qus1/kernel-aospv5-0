#include <cust_vibrator.h>
#include <linux/types.h>

static struct vibrator_hw cust_vibrator_hw = {
	.vib_timer = 25,
  #ifdef CUST_VIBR_LIMIT
	.vib_limit = 9,
  #endif
  #ifdef CUST_VIBR_VOL
#ifdef CONFIG_CPU_LOW_POWER
	.vib_vol = 0x1,//qus1 fix high vibration on boot 0x0(1.2v), 0x1(1.3v), 0x2(1.5v), 0x3(1.8v), 0x4(2.0v), def 0x5(2.8V), 0x6(3.0v), 0x7(3.3v)
#else
	.vib_vol = 0x5,
#endif
  #endif
};

struct vibrator_hw *get_cust_vibrator_hw(void)
{
    return &cust_vibrator_hw;
}

