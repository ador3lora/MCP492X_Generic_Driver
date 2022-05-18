/**
 * *****************************************************************************
 * @file    mcp492x_spi.h
 * @brief   Hardware abstraction layer
 *
 * *****************************************************************************
 */

/* Define to prevent recursive inclusion */
#ifndef MCP492X_HAL_H__
#define MCP492X_HAL_H__

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>

/* Export constants ----------------------------------------------------------*/

#define MCP492X_USED_NUM    1U

/* Export functions prototypes -----------------------------------------------*/

/**
 * @brief       Send data to DAC
 * @param[in]   dev_idx Device index on the board from 0 to MCP492X_USED_NUM - 1
 * @param[in]   src     Buffer containing data to send
 * @param[in]   len     Data buffer length in bytes
 * @return
 *              - (-2): Parameter error
 *              - (-1): Bus error
 *              - 0: Success
 */
int mcp492x_spi_write(  unsigned int dev_idx,
                        unsigned char src[2],
                        int len);

/**
 * @brief       Set device chip select pin state
 * @param[in]   dev_idx Device index on the board from 0 to MCP492X_USED_NUM - 1
 * @param[in]   value   Set or reset pin
 * @return
 *              - (-2): Parameter error
 *              - (-1): HW error
 *              - 0: Success
 */
int mcp492x_cs_pin_write(   unsigned int dev_idx,
                            bool value);

#endif  /* MCP492X_HAL_H__ */
