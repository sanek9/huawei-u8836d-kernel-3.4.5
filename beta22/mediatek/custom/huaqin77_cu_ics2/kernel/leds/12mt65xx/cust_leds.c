#include <cust_leds.h>
#include <mach/mt_pwm.h>

#include <linux/kernel.h>
#include <mach/pmic_mt6329_hw_bank1.h> 
#include <mach/pmic_mt6329_sw_bank1.h> 
#include <mach/pmic_mt6329_hw.h>
#include <mach/pmic_mt6329_sw.h>
#include <mach/upmu_common_sw.h>
#include <mach/upmu_hw.h>

#include <mach/mt_gpio.h>
#include "cust_gpio_usage.h"
#include <asm/delay.h>

#include <linux/semaphore.h>
#include <linux/errno.h>
#include <linux/mutex.h>
#include <linux/version.h>
#include <linux/delay.h>

extern int mtkfb_set_backlight_level(unsigned int level);
extern int mtkfb_set_backlight_pwm(int div);

#define ERROR_BL_LEVEL 0xFFFFFFFF

unsigned int brightness_mapping(unsigned int level)
{
#if 0
	if(level>=30 && level<=255) { // user changable by using Setting->Display->Brightness
		return (level-14)/16;
	}
	else if(level>0 && level<30) { // used to fade out for 7 seconds before shut down backlight
		return 0;
	}
#else
	//hupeng 0105, map level to 64 levels
	if(level>=30 && level<=255) { // user changable by using Setting->Display->Brightness
		#if defined(HQ_PROJECT_A61P_HUAWEI)
		return (level+1)/4;		/* lcd-backlight setting for A61 */
		#else
		return (level-22)/4;
		#endif
	}
	else if(level>0 && level<30) { // used to fade out for 7 seconds before shut down backlight
/*		#if defined(HQ_PROJECT_A61P_HUAWEI)
		//modify for QQ browser is too dark in night mode ,HQ00149545
			if(level==26)
			   return 6;
		#endif
*/		return 1;
	}
	else
	{
		return 0;
	}
#endif
	return ERROR_BL_LEVEL;
}

unsigned int Cust_SetBacklight(int level, int div)
{
    mtkfb_set_backlight_pwm(div);
    mtkfb_set_backlight_level(brightness_mapping(level));
    return 0;
}
#define KTD253_MAX_LEVEL 64
static int g_ktd_level = 0;
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36))
    DECLARE_MUTEX(ktd253_mutex);           
#else // (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))        
    DEFINE_SEMAPHORE(ktd253_mutex);
#endif
#if 0
  #define LED_DBG(fmt, arg...) \
	printk("[LED-LCM] %s (line:%d) :" fmt "\r\n", __func__, __LINE__, ## arg)
#else
  #define LED_DBG(fmt, arg...) do {} while (0)
#endif

unsigned int Cust_SetBacklight_KTD253(int level, int div)
{
	LED_DBG("[Leds] level = %d", level);
	int loop, ktd_level, pulse = 0;
	if ( level < 0 || level > 255 ){
		LED_DBG("The level is out of range.");
		return -EFAULT;
	}
	if (down_interruptible(&ktd253_mutex)){
		LED_DBG("The KTD253 is bussy.");
		return -EAGAIN;
	}
	mt_set_gpio_mode(GPIO68, GPIO_MODE_GPIO);
	mt_set_gpio_dir(GPIO68, GPIO_DIR_OUT);	
	if (level){
		/*
		 * Mapping soft level (0~255) to hard level (32~1)
		 * "1" is the top level for KTD253
		 */
		ktd_level = (255 - level) / 4 + 1;
		if (g_ktd_level != ktd_level){
			if (ktd_level > g_ktd_level)
				pulse = ktd_level - g_ktd_level;
			else
				pulse = KTD253_MAX_LEVEL - g_ktd_level + ktd_level ;

			//local_irq_disable();
			LED_DBG("[Leds] pulse = %d", pulse);
			LED_DBG("[Leds] ktd_level = %d", ktd_level);
			preempt_disable();
			for (loop = 0; loop < pulse; loop++){
				mt_set_gpio_out(GPIO68,0);
				udelay(1);	    
				mt_set_gpio_out(GPIO68,1);
				udelay(1);
			}
			preempt_enable();
			//local_irq_enable();
			g_ktd_level = ktd_level;
		}
	}
	else{
		LED_DBG("The KTD253 will shut down.");
		mt_set_gpio_out(GPIO68,0);
		msleep(5);
		g_ktd_level = 0;
	}
	up(&ktd253_mutex);
    return 0;
}

//kaka_12_0112  add

int chr_det_led_control(int level,int div){
	if(level)
		upmu_chr_chrind_on(0x01);
	else
		upmu_chr_chrind_on(0);
}

//kaka_12_0112 end

static struct cust_mt65xx_led cust_led_list[MT65XX_LED_TYPE_TOTAL] = {
	{"red",               MT65XX_LED_MODE_CUST, (int)chr_det_led_control,{0}}, //kaka_12_0112
	{"green",             MT65XX_LED_MODE_PMIC, MT65XX_LED_PMIC_NLED_ISINK5,{0}},//kaka_12_0112
	{"blue",              MT65XX_LED_MODE_PMIC, MT65XX_LED_PMIC_NLED_ISINK4,{0}},//kaka_12_0112
	{"jogball-backlight", MT65XX_LED_MODE_NONE, -1,{0}},
	{"keyboard-backlight",MT65XX_LED_MODE_NONE, -1,{0}},
	{"button-backlight",  MT65XX_LED_MODE_PMIC, MT65XX_LED_PMIC_BUTTON,{0}}, //kaka_11_1230 Keypad LED
	{"lcd-backlight",     MT65XX_LED_MODE_CUST, Cust_SetBacklight_KTD253,{0}}, //kaka_12_0330 ICS GPIO set to PWM3
        {"torch",MT65XX_LED_MODE_PWM,PWM1,{0}},
        {"flash-light",       MT65XX_LED_MODE_GPIO, GPIO_CAMERA_FLASH_EN_PIN,{0}}, //kaka_12_0112 FlashLight control  for FTM use only
};

struct cust_mt65xx_led *get_cust_led_list(void)
{
	return cust_led_list;
}

