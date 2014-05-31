/*This file implements MTK boot mode.*/

#include <sys/types.h>
#include <debug.h>
#include <err.h>
#include <reg.h>

#include <platform/mt_typedefs.h>
#include <platform/boot_mode.h>
#include <platform/mt_reg_base.h>
#include <platform/mtk_key.h>

#include <target/cust_key.h>

#define MODULE_NAME "[BOOT_MENU]"
bool g_boot_menu = false;

void boot_mode_menu_select()
{
	int select = 0;  // 0=recovery mode, 1=fastboot.  2=normal boot, 3=boot from sd
	const char* title_msg = "Select Boot Mode:\n\tVOLUME_DOWN to select.\n\tVOLUME_UP is OK.\n\n";
	video_clean_screen();
	video_set_cursor(video_get_rows()/2, 0);
	video_printf(title_msg);
	video_printf("[Recovery     Mode]         <<==\n");
#ifdef MTK_FASTBOOT_SUPPORT
	video_printf("[Fastboot     Mode]             \n");
#endif
	video_printf("[Normal       Boot]             \n");
	video_printf("[Boot from MicroSD]             \n");
	while(1)
	{
		if(mtk_detect_key(MT65XX_MENU_SELECT_KEY))
		{
			g_boot_menu = true;
			switch(select) {

				case 0:
#ifdef MTK_FASTBOOT_SUPPORT
					select = 1;

					video_set_cursor(video_get_rows()/2, 0);
					video_printf(title_msg);
					video_printf("[Recovery     Mode]             \n");
					video_printf("[Fastboot     Mode]         <<==\n");
					video_printf("[Normal       Boot]             \n");
					video_printf("[Boot from MicroSD]             \n");
				break;
#endif
				case 1:
					select = 3;

					video_set_cursor(video_get_rows()/2, 0);
					video_printf(title_msg);
					video_printf("[Recovery     Mode]             \n");
#ifdef MTK_FASTBOOT_SUPPORT
					video_printf("[Fastboot     Mode]             \n");
#endif
					video_printf("[Normal       Boot]         <<==\n");
					video_printf("[Boot from MicroSD]             \n");
				break;
				
				case 3:
					select = 2;
					
					video_set_cursor(video_get_rows()/2, 0);
					video_printf(title_msg);
					video_printf("[Recovery     Mode]             \n");
#ifdef MTK_FASTBOOT_SUPPORT
					video_printf("[Fastboot     Mode]             \n");
#endif
					video_printf("[Normal       Boot]             \n");
					video_printf("[Boot from MicroSD]         <<==\n");
				break;
				
				case 2:
					select = 0;

					video_set_cursor(video_get_rows()/2, 0);
					video_printf(title_msg);
					video_printf("[Recovery     Mode]         <<==\n");
#ifdef MTK_FASTBOOT_SUPPORT
					video_printf("[Fastboot     Mode]             \n");
#endif
					video_printf("[Normal       Boot]             \n");
					video_printf("[Boot from MicroSD]             \n");
				break;

				default: 
				break;
			}
			dprintf(0,  "[VOL_UP]Key Detect, current select:%d\n", select);
			mdelay(300);
		}
		else if(mtk_detect_key(MT65XX_MENU_OK_KEY))//VOL_DOWN,
		{
			//use for OK
			break;
		}
		else
		{
		//pass
		}
	}
	if(select == 0)
	{
		g_boot_mode = RECOVERY_BOOT;
	}
	else if(select == 1)
	{
		g_boot_mode = FASTBOOT;
	}
	else if(select == 2)
	{
		g_boot_mode = NORMAL_BOOT;
	}
	else if(select == 3)
	{
		g_boot_mode = MICROSD_BOOT;
	}
	else
	{
		//pass
	}

	video_clean_screen();
	video_set_cursor(0, 0);
	return;
}


BOOL boot_menu_key_trigger(void)
{
#if 1
	//wait
	ulong begin = get_timer(0);
	printf("\n%s Check  boot menu\n",MODULE_NAME);
	printf("%s Wait 50ms for special keys\n",MODULE_NAME);

	mt65xx_backlight_on(); //[**add by Rachel,20121031,solve time solution**]

	//let some case of recovery mode pass.
	if(unshield_recovery_detection())
	{
		return TRUE;
	}

	while(get_timer(begin) < 1000)
	{
		if(mtk_detect_key(MT65XX_BOOT_MENU_KEY))
		{
							mtk_wdt_disable();
							boot_mode_menu_select();
							mtk_wdt_init();
							return TRUE;
		}
	}
#endif
	return FALSE;
}

BOOL boot_menu_detection(void)
{
	return boot_menu_key_trigger();
}


int unshield_recovery_detection(void)
{
	//because recovery_check_command_trigger's BOOL is different from the BOOL in this file.
	//so use code like this type.
	return recovery_check_command_trigger()? TRUE:FALSE;
}

