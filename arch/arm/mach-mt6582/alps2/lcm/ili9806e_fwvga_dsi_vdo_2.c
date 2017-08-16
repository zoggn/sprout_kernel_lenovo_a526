#if defined(BUILD_LK)
#include <string.h>
#else
#include <linux/string.h>
#endif


#if defined(BUILD_LK)
#include "cust_gpio_usage.h"
#include <platform/mt_gpio.h>
#else
#include "cust_gpio_usage.h"
#include <mach/mt_gpio.h>
#endif

#include "lcm_drv.h"

// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  										(480)
#define FRAME_HEIGHT 										(854)

#define REGFLAG_DELAY             							0xFE
#define REGFLAG_END_OF_TABLE      							0xFFF   // END OF REGISTERS MARKER

#define LCM_DSI_CMD_MODE									0

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};
#define SET_RESET_PIN(v)    								(lcm_util.set_reset_pin((v)))

#define UDELAY(n) 											(lcm_util.udelay(n))
#define MDELAY(n) 											(lcm_util.mdelay(n))


// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)	        lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define write_cmd(cmd)										lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)					lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg(cmd)											lcm_util.dsi_dcs_read_lcm_reg(cmd)
#define read_reg_v2(cmd, buffer, buffer_size)   				lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)

struct LCM_setting_table {
    unsigned char cmd;
    unsigned char count;
    unsigned char para_list[64];
};

static struct LCM_setting_table lcm_initialization_setting_1[] = {
    { 0xFF, 0x05, {0xFF, 0x98, 0x06, 0x04, 0x01}},
    { 0x08, 0x01, {0x10}},
    { 0x21, 0x01, {0x01}},
    { 0x30, 0x01, {0x01}},
    { 0x31, 0x01, {0x02}},
    { 0x40, 0x01, {0x16}},
    { 0x41, 0x01, {0x33}},
    { 0x42, 0x01, {0x03}},
    { 0x43, 0x01, {0x09}},
    { 0x44, 0x01, {0x09}},
    { 0x50, 0x01, {0x80}},
    { 0x51, 0x01, {0x80}},
    { 0x52, 0x01, {0x00}},
    { 0x53, 0x01, {0x61}},
    { 0x57, 0x01, {0x50}},
    { 0x60, 0x01, {0x07}},
    { 0x61, 0x01, {0x00}},
    { 0x62, 0x01, {0x08}},
    { 0x63, 0x01, {0x00}},
    { 0xA0, 0x01, {0x00}},
    { 0xA1, 0x01, {0x0A}},
    { 0xA2, 0x01, {0x13}},
    { 0xA3, 0x01, {0x13}},
    { 0xA4, 0x01, {0x0D}},
    { 0xA5, 0x01, {0x1B}},
    { 0xA6, 0x01, {0x06}},
    { 0xA7, 0x01, {0x07}},
    { 0xA8, 0x01, {0x06}},
    { 0xA9, 0x01, {0x07}},
    { 0xAA, 0x01, {0x05}},
    { 0xAB, 0x01, {0x01}},
    { 0xAC, 0x01, {0x10}},
    { 0xAD, 0x01, {0x2F}},
    { 0xAE, 0x01, {0x2A}},
    { 0xAF, 0x01, {0x00}},
    { 0xC0, 0x01, {0x00}},
    { 0xC1, 0x01, {0x08}},
    { 0xC2, 0x01, {0x18}},
    { 0xC3, 0x01, {0x10}},
    { 0xC4, 0x01, {0x06}},
    { 0xC5, 0x01, {0x15}},
    { 0xC6, 0x01, {0x0B}},
    { 0xC7, 0x01, {0x09}},
    { 0xC8, 0x01, {0x02}},
    { 0xC9, 0x01, {0x08}},
    { 0xCA, 0x01, {0x08}},
    { 0xCB, 0x01, {0x05}},
    { 0xCC, 0x01, {0x09}},
    { 0xCD, 0x01, {0x26}},
    { 0xCE, 0x01, {0x21}},
    { 0xCF, 0x01, {0x00}},
    { 0xFF, 0x05, {0xFF, 0x98, 0x06, 0x04, 0x06}},
    { 0x00, 0x01, {0x21}},
    { 0x01, 0x01, {0x06}},
    { 0x02, 0x01, {0x00}},
    { 0x03, 0x01, {0x00}},
    { 0x04, 0x01, {0x01}},
    { 0x05, 0x01, {0x01}},
    { 0x06, 0x01, {0x80}},
    { 0x07, 0x01, {0x02}},
    { 0x08, 0x01, {0x05}},
    { 0x09, 0x01, {0x00}},
    { 0x0A, 0x01, {0x00}},
    { 0x0B, 0x01, {0x00}},
    { 0x0C, 0x01, {0x01}},
    { 0x0D, 0x01, {0x01}},
    { 0x0E, 0x01, {0x00}},
    { 0x0F, 0x01, {0x00}},
    { 0x10, 0x01, {0xF0}},
    { 0x11, 0x01, {0xF4}},
    { 0x12, 0x01, {0x00}},
    { 0x13, 0x01, {0x00}},
    { 0x14, 0x01, {0x00}},
    { 0x15, 0x01, {0xC0}},
    { 0x16, 0x01, {0x08}},
    { 0x17, 0x01, {0x00}},
    { 0x18, 0x01, {0x00}},
    { 0x19, 0x01, {0x00}},
    { 0x1A, 0x01, {0x00}},
    { 0x1B, 0x01, {0x00}},
    { 0x1C, 0x01, {0x00}},
    { 0x1D, 0x01, {0x00}},
    { 0x20, 0x01, {0x02}},
    { 0x21, 0x01, {0x13}},
    { 0x22, 0x01, {0x45}},
    { 0x23, 0x01, {0x67}},
    { 0x24, 0x01, {0x01}},
    { 0x25, 0x01, {0x23}},
    { 0x26, 0x01, {0x45}},
    { 0x27, 0x01, {0x67}},
    { 0x30, 0x01, {0x13}},
    { 0x31, 0x01, {0x22}},
    { 0x32, 0x01, {0x22}},
    { 0x33, 0x01, {0x22}},
    { 0x34, 0x01, {0x22}},
    { 0x35, 0x01, {0xBB}},
    { 0x36, 0x01, {0xAA}},
    { 0x37, 0x01, {0xDD}},
    { 0x38, 0x01, {0xCC}},
    { 0x39, 0x01, {0x66}},
    { 0x3A, 0x01, {0x77}},
    { 0x3B, 0x01, {0x22}},
    { 0x3C, 0x01, {0x22}},
    { 0x3D, 0x01, {0x22}},
    { 0x3E, 0x01, {0x22}},
    { 0x3F, 0x01, {0x22}},
    { 0x40, 0x01, {0x22}},
    { 0x52, 0x01, {0x10}},
    { 0x53, 0x01, {0x10}},
    { 0xFF, 0x05, {0xFF, 0x98, 0x06, 0x04, 0x07}},
    { 0x17, 0x01, {0x22}},
    { 0x02, 0x01, {0x77}},
    { 0xFF, 0x05, {0xFF, 0x98, 0x06, 0x04, 0x00}},
    { REGFLAG_END_OF_TABLE, 0x00, {}}
};

static struct LCM_setting_table lcm_initialization_setting_2[] = {
    { 0x11, 0x01, {0x00}},
    { REGFLAG_DELAY, 120, {}},
    { 0x29, 0x01, {0x00}},
    { REGFLAG_DELAY, 10, {}},
    { 0xFF, 0x05, {0xFF, 0x98, 0x06, 0x04, 0x08}},
    { REGFLAG_END_OF_TABLE, 0x00, {}}
};

static struct LCM_setting_table lcm_deep_sleep_mode_in_setting[] = {
    { 0xFF, 0x05, {0xFF, 0x98, 0x06, 0x04, 0x00}},
    { REGFLAG_DELAY, 1, {}},
    { 0xFF, 0x05, {0xFF, 0x98, 0x06, 0x04, 0x00}},
    { 0x28, 0x01, {0x00}},
    { REGFLAG_DELAY, 10, {}},
    { 0x10, 0x01, {0x00}},
    { REGFLAG_DELAY, 120, {}},
    { REGFLAG_END_OF_TABLE, 0x00, {}}
};

static void push_table(struct LCM_setting_table *table, unsigned int count, unsigned char force_update) {
  unsigned int i;
  for(i = 0; i < count; i++) {
    unsigned cmd;
    cmd = table[i].cmd;
    switch (cmd) {
      case REGFLAG_DELAY :
        MDELAY(table[i].count);
        break;
      case REGFLAG_END_OF_TABLE :
        break;
      default:
        dsi_set_cmdq_V2(cmd, table[i].count, table[i].para_list, force_update);
    }
  }
};

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
  memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}

static void lcm_get_params(LCM_PARAMS *params)
{
  memset(params, 0, sizeof(LCM_PARAMS));
  params->type = 2;
  params->dsi.LANE_NUM = 2;
  params->dsi.data_format.format = 2;
  params->dsi.PS = 2;
  params->width = 480;
  params->dsi.vertical_sync_active = 4;
  params->height = 854;
  params->dsi.mode = 1;
  params->dsi.data_format.color_order = 0;
  params->dsi.horizontal_sync_active = 10;
  params->dsi.data_format.trans_seq = 0;
  params->dsi.data_format.padding = 0;
  params->dsi.packet_size = 256;
  params->dsi.intermediat_buffer_num = 0;
  params->dsi.vertical_backporch = 16;
  params->dsi.vertical_frontporch = 20;
  params->dsi.vertical_active_line = 854;
  params->dsi.horizontal_backporch = 80;
  params->dsi.horizontal_frontporch = 80;
  params->dsi.horizontal_active_pixel = 480;
  params->dsi.PLL_CLOCK = 250;
  params->dsi.ssc_disable = 0;
  params->dsi.ssc_range = 1;
}

static void lcm_init(void)
{
  SET_RESET_PIN(1);
  MDELAY(1);
  SET_RESET_PIN(0);
  MDELAY(10);
  SET_RESET_PIN(1);
  MDELAY(120);
  push_table(lcm_initialization_setting_1, sizeof(lcm_initialization_setting_1) / sizeof(struct LCM_setting_table), 1);
  push_table(lcm_initialization_setting_2, sizeof(lcm_initialization_setting_2) / sizeof(struct LCM_setting_table), 1);
}

static void lcm_suspend(void)
{
  push_table(lcm_deep_sleep_mode_in_setting, sizeof(lcm_deep_sleep_mode_in_setting) / sizeof(struct LCM_setting_table), 1);
}

static void lcm_resume(void)
{
  lcm_init();
}

static unsigned int lcm_compare_id(void)
{
  return 1;
}

LCM_DRIVER ili9806e_fwvga_dsi_vdo_2_lcm_drv =
{
    .name			= "ili9806e_fwvga_dsi_vdo_2",
	.set_util_funcs = lcm_set_util_funcs,
	.get_params     = lcm_get_params,
	.init           = lcm_init,
	.suspend        = lcm_suspend,
	.resume         = lcm_resume,
	.compare_id     = lcm_compare_id,
};
