/**
 * *****************************************************************************
 * @file    mcp492x_driver.c
 * @brief   12-Bit DAC with SPI interface
 *
 * *****************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "mcp492x_spi.h"
#include "mcp492x_driver.h"

/* Private functions prototypes ----------------------------------------------*/

/**
 * @brief       Generate command to send to DAC
 * @param[in]   cfg     Pointer to a structure containing configuration values
 * @param[in]   value   Value in binary code
 * @param[out]  cmd_buf Command data buffer
 * @param[in]   len     Buffer length
 * @return
 *              - (-1): Parameter error
 *              - 0: Success
 */
static int _mcp492x_generate_command(   mcp492x_config_t *cfg,
                                        unsigned int value,
                                        unsigned char cmd_buf[2],
                                        int len);

/* Private functions ---------------------------------------------------------*/

/* Generate command to send to DAC */
static int _mcp492x_generate_command(mcp492x_config_t *cfg, unsigned int value, unsigned char cmd_buf[2], int len) {
    if (cfg == NULL ||
        cmd_buf == NULL ||
        len != 2) {
        return -1;
    }
    memset(cmd_buf, 0, len * sizeof(unsigned char));
    if (cfg->ab == true)    { cmd_buf[0] |= (1UL << 7); }
    if (cfg->buf == true)   { cmd_buf[0] |= (1UL << 6); }
    if (cfg->ga == true)    { cmd_buf[0] |= (1UL << 5); }
    if (cfg->shdn == true)  { cmd_buf[0] |= (1UL << 4); }
    cmd_buf[0] |= ((value >> 8) & 0x0F);
    cmd_buf[1] = value & 0x00FF;
    return 0;
}

/* Export functions ----------------------------------------------------------*/

/* Initialize the structure of the used device with the necessary values */
int mcp492x_init(mcp492x_handle_t dev_hdl, mcp492x_t *cfg) {
    if (dev_hdl == NULL ||
        cfg == NULL) {
        return -2;
    }
    dev_hdl->idx = cfg->idx;
    dev_hdl->cfg.ab = cfg->cfg.ab;
    dev_hdl->cfg.buf = cfg->cfg.buf;
    dev_hdl->cfg.ga = cfg->cfg.ga;
    dev_hdl->cfg.shdn = cfg->cfg.shdn;
    dev_hdl->busy = cfg->busy;
    dev_hdl->err = cfg->err;
    return 0;
}

/* Set the parameters for generating the write command */
int mcp492x_set_config(mcp492x_handle_t dev_hdl, mcp492x_config_t *cfg) {
    if (dev_hdl == NULL ||
        cfg == NULL) {
        return -2;
    }
    while (dev_hdl->busy == true);
    dev_hdl->busy = true;
    dev_hdl->cfg.ab = cfg->ab;
    dev_hdl->cfg.buf = cfg->buf;
    dev_hdl->cfg.ga = cfg->ga;
    dev_hdl->cfg.shdn = cfg->shdn;
    dev_hdl->busy = false;
    return 0;
}

/* Set DAC output voltage value in binary code */
int mcp492x_set_out_voltage_bin(mcp492x_handle_t dev_hdl, unsigned int value) {
    if (dev_hdl == NULL) {
        return -2;
    }
    int ret = 0;
    unsigned char cmd_buf[2] = { 0, 0 };
    if (_mcp492x_generate_command(  &dev_hdl->cfg,
                                    value,
                                    cmd_buf,
                                    sizeof cmd_buf) != 0) {
        return -2;
    }
    while (dev_hdl->busy == true);
    dev_hdl->busy = true;
    if ((ret = mcp492x_spi_write(dev_hdl->idx, cmd_buf, sizeof cmd_buf)) != 0) {
        if (ret == -1) {
            dev_hdl->err = true;
            ret = -1;
        } else if (ret == -2) {
            ret = -2;
        }
    }
    dev_hdl->busy = false;
    return (int)ret;
}

/* Set DAC output voltage value in percent */
int mcp492x_set_out_voltage_pct(mcp492x_handle_t dev_hdl, unsigned int pct) {
    if (dev_hdl == NULL) {
        return -2;
    }
    unsigned int value = 0;
    if (pct > 100) {
        pct %= 100;
    }
    value = (819 * pct) / 20;
    return (int)mcp492x_set_out_voltage_bin(dev_hdl, value);
}

/* Set chip select pin to active */
int mcp492x_select(mcp492x_handle_t dev_hdl) {
    if (dev_hdl == NULL) {
        return -2;
    }
    int ret = 0;
    while (dev_hdl->busy == true);
    dev_hdl->busy = true;
    if ((ret = mcp492x_cs_pin_write(dev_hdl->idx, false)) != 0) {
        if (ret == -1) {
            dev_hdl->err = true;
            ret = -1;
        } else if (ret == -2) {
            ret = -2;
        }
    }
    dev_hdl->busy = false;
    return (int)ret;
}

/* Set chip select pin to inactive */
int mcp492x_deselect(mcp492x_handle_t dev_hdl) {
    if (dev_hdl == NULL) {
        return -2;
    }
    int ret = 0;
    while (dev_hdl->busy == true);
    dev_hdl->busy = true;
    if ((ret = mcp492x_cs_pin_write(dev_hdl->idx, true)) != 0) {
        if (ret == -1) {
            dev_hdl->err = true;
            ret = -1;
        } else if (ret == -2) {
            ret = -2;
        }
    }
    dev_hdl->busy = false;
    return (int)ret;
}
