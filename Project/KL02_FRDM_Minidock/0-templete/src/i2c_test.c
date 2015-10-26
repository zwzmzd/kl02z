#include "at24cxx.h"
#include "i2c.h"

int cmd_i2c(int argc, char * const argv[])
{
    int ret;
    I2C_QuickInit(I2C0_SCL_PB03_SDA_PB04, 576000);
    at24cxx_init(HW_I2C0);
    ret = at24cxx_self_test();
    return ret;
}

