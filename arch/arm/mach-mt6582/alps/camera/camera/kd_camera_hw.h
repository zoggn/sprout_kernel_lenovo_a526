#ifndef _KD_CAMERA_HW_H_
#define _KD_CAMERA_HW_H_
 

#include <mach/mt_gpio.h>
#include <mach/mt_pm_ldo.h>




//
//Power 
#define CAMERA_POWER_VCAM_A MT6323_POWER_LDO_VCAMA
#define CAMERA_POWER_VCAM_D MT6323_POWER_LDO_VCAMD
#define CAMERA_POWER_VCAM_A2 MT6323_POWER_LDO_VCAM_AF
#define CAMERA_POWER_VCAM_D2 MT6323_POWER_LDO_VCAM_IO

//FIXME, should defined in DCT tool 
//
/*
#ifndef GPIO_CAMERA_LDO_EN_PIN 
#define GPIO_CAMERA_LDO_EN_PIN GPIO94
#endif 
//
#ifndef GPIO_CAMERA_CMRST_PIN 
#define GPIO_CAMERA_CMRST_PIN GPIO9
#endif 
//
#ifndef GPIO_CAMERA_CMRST_PIN_M_GPIO
#define GPIO_CAMERA_CMRST_PIN_M_GPIO GPIO_MODE_00
#endif 
//
#ifndef GPIO_CAMERA_CMPDN_PIN 
#define GPIO_CAMERA_CMPDN_PIN GPIO10
#endif 
//
#ifndef GPIO_CAMERA_LDO_EN_PIN_M_GPIO
#define GPIO_CAMERA_LDO_EN_PIN_M_GPIO GPIO_MODE_00
#endif 
//
#ifndef GPIO_CAMERA_CMPDN_PIN_M_GPIO
#define GPIO_CAMERA_CMPDN_PIN_M_GPIO  GPIO_MODE_00 
#endif 
//
#ifndef GPIO_CAMERA_CMRST1_PIN
#define GPIO_CAMERA_CMRST1_PIN GPIO16
#endif
//
#ifndef GPIO_CAMERA_CMRST1_PIN_M_GPIO
#define GPIO_CAMERA_CMRST1_PIN_M_GPIO GPIO_MODE_00
#endif
//
#ifndef GPIO_CAMERA_CMPDN1_PIN
#define GPIO_CAMERA_CMPDN1_PIN GPIO18
#endif
//
#ifndef GPIO_CAMERA_CMPDN1_PIN_M_GPIO
#define GPIO_CAMERA_CMPDN1_PIN_M_GPIO GPIO_MODE_00
#endif
*/


//i2c id for sensor device, MT8320_fpga, the I2C is attached on 1
//#define IMG_SENSOR_I2C_GROUP_ID 0

//#define A60373_WRITE_ID (0xC0)
//#define A60373_READ_ID (0xC1)



#endif 
