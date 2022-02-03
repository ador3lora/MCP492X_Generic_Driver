/**
 * *****************************************************************************
 * @file	mcp492x_driver.h
 * @brief	12-Bit DAC with SPI interface
 *
 * *****************************************************************************
 */

/* Define to prevent recursive inclusion */
#ifndef MCP492X_DRV_H__
#define MCP492X_DRV_H__

/* Includes ------------------------------------------------------------------*/

#include <stdbool.h>

/* Export typedef ------------------------------------------------------------*/

typedef struct mcp492x_s mcp492x_t;
typedef struct mcp492x_s *mcp492x_handle_t;

typedef struct mcp492x_config_s mcp492x_config_t;

/**
 * @brief	Structure that defines the values of the configuration bits of a
 * 			16-bit word transmitted to the DAC
 */
struct mcp492x_config_s {
	bool ab;	/*!< DACA or DACB select bit: 1 = write to DACB; 0 = write to DACA */
	bool buf;	/*!< VREF input buffer control bit: 1 = buffered; 0 = unbuffered */
	bool ga;	/*!< Output gain select bit: 1 = 1 * (VOUT = VREF * D/4096); 0 = 2 * (VOUT = 2 * VREF * D/4096) */
	bool shdn;	/*!< Output power down control bit: 1 = output power down control bit; 0 = output buffer disabled, output is high impedance */
};

struct mcp492x_s {
	unsigned int idx;
	mcp492x_config_t cfg;
	bool busy;
	bool err;
};

/* Export functions prototypes -----------------------------------------------*/

/**
 * @brief		Initialize the structure of the used device with the necessary
 * 				values
 * @param[out]	dev_hdl	Pointer to a structure describing the device
 * @param[in]	cfg		Pointer to a structure containing initial values
 * @return
 * 				- (-2): Parameter error
 * 				- 0: Success
 */
int mcp492x_init(	mcp492x_handle_t dev_hdl,
					mcp492x_t *cfg);

/**
 * @brief		Set the parameters for generating the write command
 * @param[out]	dev_hdl	Pointer to a structure describing the device
 * @param[in]	cfg		Pointer to a structure containing configuration values
 * @return
 * 				- (-2): Parameter error
 * 				- 0: Success
 */
int mcp492x_set_config(	mcp492x_handle_t dev_hdl,
						mcp492x_config_t *cfg);

/**
 * @brief		Set DAC output voltage value in binary code
 * *****************************************************************************
 * @attention	The mcp492x_config_t device structure must be initialized with
 * 				the correct values before use
 * *****************************************************************************
 * @param[in]	dev_hdl	Pointer to a structure describing the device
 * @param[in]	value	Value in binary code
 * @return
 * 				- (-2): Parameter error
 * 				- (-1): Bus error
 * 				- 0: Success
 */
int mcp492x_set_out_voltage_bin(mcp492x_handle_t dev_hdl,
								unsigned int value);

/**
 * @brief		Set DAC output voltage value in percent
 * *****************************************************************************
 * @attention	The mcp492x_config_t device structure must be initialized with
 * 				the correct values before use
 * *****************************************************************************
 * @param[in]	dev_hdl	Pointer to a structure describing the device
 * @param[in]	pct		Percentage
 * @return
 * 				- (-2): Parameter error
 * 				- (-1): Bus error
 * 				- 0: Success
 */
int mcp492x_set_out_voltage_pct(mcp492x_handle_t dev_hdl,
								unsigned int pct);

/**
 * @brief		Set chip select pin to active
 * @param[in]	dev_hdl	Pointer to a structure describing the device
 * @return
 * 				- (-2): Parameter error
 * 				- (-1): Hardware error
 * 				- 0: Success
 */
int mcp492x_select(mcp492x_handle_t dev_hdl);

/**
 * @brief		Set chip select pin to inactive
 * @param[in]	dev_hdl	Pointer to a structure describing the device
 * @return
 * 				- (-2): Parameter error
 * 				- (-1): Hardware error
 * 				- 0: Success
 */
int mcp492x_deselect(mcp492x_handle_t dev_hdl);

#endif	/* MCP492X_DRV_H__ */
