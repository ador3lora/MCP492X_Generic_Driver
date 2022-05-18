/**
 * *****************************************************************************
 * @file    mcp492x_spi.c
 * @brief   Hardware abstraction layer
 *
 * *****************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>

#include "mcp492x_spi.h"

/* Export functions ----------------------------------------------------------*/

/* Send data to DAC */
int mcp492x_spi_write(unsigned int dev_idx, unsigned char src[2], int len) {
    if (dev_idx >= MCP492X_USED_NUM ||
        src == NULL ||
        len != 2) {
        return -2;
    }
    int ret = 0;
    if ((ret = mcp492x_cs_pin_write(dev_idx, false)) != 0) {
        if (ret == -1) {
            return -1;
        } else if (ret == -2) {
            return -2;
        }
    }
    /*------------------------------------------------------------------------*/
    /* Specify a custom SPI communication function here ----------------------*/
    /* The function must return a value (-1) in case of a hardware error -----*/
    /*------------------------------------------------------------------------*/
    if ((ret = mcp492x_cs_pin_write(dev_idx, true)) != 0) {
        if (ret == -1) {
            return -1;
        } else if (ret == -2) {
            return -2;
        }
    }
    return 0;
}

/* Set device chip select pin state */
int mcp492x_cs_pin_write(unsigned int dev_idx, bool value) {
    if (dev_idx >= MCP492X_USED_NUM) {
        return -2;
    }
    /*------------------------------------------------------------------------*/
    /* Specify a custom chip select output state change function here --------*/
    /* The function must return a value (-1) in case of a hardware error -----*/
    /*------------------------------------------------------------------------*/
    return 0;
}
