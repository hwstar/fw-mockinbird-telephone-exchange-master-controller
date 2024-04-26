#include "mf_receiver.h"
#include "top.h"
#include "uart.h"
#include "i2c_engine.h"
#include "console.h"
#include "logging.h"
#include "tone_plant.h"
#include "drv_dtmf.h"
#include "drv_xps.h"
#include "xps_logical.h"
#include "event.h"
#include "card_comm.h"
#include "file_io.h"
#include "hw_pres.h"



static const char *TAG = "top";


/* Debug code, remove */
void dummy_callback(uint32_t channel_number) {

}


/*
 * Called once before RTOS initialization
 */

void Top_setup(void) {
	System_console.setup();
	Logger.setup();
	MF_decoder.setup();
	Tone_plant.setup();
}


void Top_init(void) {

	osDelay(1000);

	/* Resources */
	Logger.init();
	I2c.init();
	MF_decoder.init();
	Dtmf_receivers.init();
	Tone_plant.init();
	Xps_driver.init();
	Xps_logical.init();
	Card_comm.init();




	/* After resources. Depends on resources being initialized */
	File_io.init();
	HW_pres.probe();
	Event_handler.init();

	/* Test Code Begin */

	/* Test Code End */



	LOG_INFO(TAG, "Initialization completed");
	/* Turn on green LED to signify Initialization complete */
	HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, GPIO_PIN_SET);
}

/*
 * Default task loop
 */
void Top_default_task(void) {
	System_console.loop();

}


/*
 * Uart interrupt handler
 */
void Top_uart_handler(UART_HandleTypeDef *uart_handle) {

	/* Console RX */
	if(uart_handle == &huart5) {
		char c;
		HAL_UART_Receive(uart_handle, (uint8_t *) &c, 1, 0);
		Console_uart.rx_int(c);
	}
}


/*
 * ADC DMA Half buffer full interrupt
 */
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc) {
	MF_decoder.handle_buffer(hadc, 0);

}


/*
 * ADC DMA buffer full interrupt
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
	MF_decoder.handle_buffer(hadc, 1);
}


/*
 * SAI DMA half buffer completed buffer callback
 */

void HAL_SAI_TxHalfCpltCallback(SAI_HandleTypeDef *hsai) {
	Tone_plant.handle_buffer(hsai, 0);

}

/*
 * SAI DMA buffer completed buffer callback
 */

void HAL_SAI_TxCpltCallback(SAI_HandleTypeDef *hsai) {
	Tone_plant.handle_buffer(hsai, 1);

}

/*
 * SAI Error callback
 */

void HAL_SAI_ErrorCallback(SAI_HandleTypeDef *hsai) {
	Tone_plant.handle_error(hsai);
}


/*
 * I2C interrupt handlers
 */

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c) {
	I2c.handler(hi2c, I2C_Engine::MSG_I2C_TX);
}

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c) {
	I2c.handler(hi2c, I2C_Engine::MSG_I2C_RX);
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c) {
	I2c.handler(hi2c, I2C_Engine::MSG_I2C_ERR);

}




