#include <cust_mag.h>
#include <linux/types.h>

#ifdef MT6573
#include <mach/mt6573_pll.h>
#endif

#ifdef MT6577
#include <mach/mt_typedefs.h>
#include <mach/mt_pm_ldo.h>
#endif

/*---------------------------------------------------------------------------*/
/*
int cust_mag_power(struct mag_hw *hw, unsigned int on, char* devname)
{
    if (hw->power_id == MT65XX_POWER_NONE)
        return 0;
    if (on)
        return hwPowerOn(hw->power_id, hw->power_vol, devname);
    else
        return hwPowerDown(hw->power_id, devname); 
}*/
/*---------------------------------------------------------------------------*/
static struct mag_hw cust_mag_hw = {
    .i2c_num = 0,
    .direction = 1,
    .power_id = MT65XX_POWER_NONE,  /*!< LDO is not used */
    .power_vol= VOL_DEFAULT,        /*!< LDO is not used */
};
/*---------------------------------------------------------------------------*/
struct mag_hw* get_cust_mag_hw(void) 
{
    return &cust_mag_hw;
}

struct mag_hw* akm8975_get_cust_mag_hw(void) 
{
    return &cust_mag_hw;
}

