
#include <common.h>
#include <video.h>
#include <asm/io.h>
#include <asm/arch/mt65xx.h>
#include <asm/arch/mt65xx_typedefs.h>
#include <asm/arch/mtk_key.h>
#include <asm/arch/boot_mode.h>
#include <asm/arch/mtk_factory.h>

#define MODULE_NAME "[FACTORY]"

#define MT65XX_FACTORY_KEY 2 //for mt6589 fpga uboot early porting

BOOL factory_check_key_trigger(void)
{
	//wait
	ulong begin = get_timer(0);
	printf("\n%s Check factory boot\n",MODULE_NAME);
	printf("%s Wait 50ms for special keys\n",MODULE_NAME);
	
	/* If the boot reason is RESET, than we will NOT enter factory mode. */
	if(mtk_detect_pmic_just_rst())
	{
	  return false;
	}
	
    while(get_timer(begin)<50)
    {    
		if(mtk_detect_key(MT65XX_FACTORY_KEY))
		{	
			printf("%s Detect key\n",MODULE_NAME);
			printf("%s Enable factory mode\n",MODULE_NAME);		
			g_boot_mode = FACTORY_BOOT;
			//video_printf("%s : detect factory mode !\n",MODULE_NAME);
			return TRUE;
		}
	}
		
	return FALSE;		
}

BOOL factory_detection(void)
{
    if(factory_check_key_trigger())
    {
    	return TRUE;
    }
	
	return FALSE;
}


