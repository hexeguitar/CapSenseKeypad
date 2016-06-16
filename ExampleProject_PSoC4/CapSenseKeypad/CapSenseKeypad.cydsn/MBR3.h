/* ========================================
 *
 * Cypress MBR3 Capsense controller driver
 * 
 * (c) 06.2016 Piotr Zapart
 * www.hexeguitar.com
 * 
 * ========================================
*/
#if !defined(MBR3_H)
#define MBR3_H

#include <cytypes.h>
    
/* CY8CMBR3116 Register Map Offset Address */
#define MBR3_REGMAP_ORIGIN			0x00
#define MBR3_SENSOR_PATTERN			0x00
#define MBR3_FSS_EN					0x02
#define MBR3_TOGGLE_EN				0x04
#define MBR3_LED_ON_EN				0x06
#define MBR3_SENSITIVITY0			0x08
#define MBR3_SENSITIVITY1			0x09
#define MBR3_SENSITIVITY2			0x0A
#define MBR3_SENSITIVITY3			0x0B
#define MBR3_BASE_THRESHOLD0    	0x0C
#define MBR3_BASE_THRESHOLD1		0x0D
#define MBR3_FINGER_THRESHOLD2		0x0E
#define MBR3_FINGER_THRESHOLD3		0x0F
#define MBR3_FINGER_THRESHOLD4		0x10
#define MBR3_FINGER_THRESHOLD5		0x11
#define MBR3_FINGER_THRESHOLD6		0x12
#define MBR3_FINGER_THRESHOLD7		0x13
#define MBR3_FINGER_THRESHOLD8		0x14
#define MBR3_FINGER_THRESHOLD9		0x15
#define MBR3_FINGER_THRESHOLD10		0x16
#define MBR3_FINGER_THRESHOLD11		0x17
#define MBR3_FINGER_THRESHOLD12		0x18
#define MBR3_FINGER_THRESHOLD13		0x19
#define MBR3_FINGER_THRESHOLD14		0x1A
#define MBR3_FINGER_THRESHOLD15		0x1B
#define MBR3_SENSOR_DEBOUNCE		0x1C
#define MBR3_BUTTON_HYS				0x1D
#define MBR3_BUTTON_BUT				0x1E
#define MBR3_BUTTON_LBR				0x1F
#define MBR3_BUTTON_NNT				0x20
#define MBR3_BUTTON_NT				0x21
#define MBR3_PROX_EN				0x26
#define MBR3_PROX_CFG				0x27
#define MBR3_PROX_CFG2				0x28
#define MBR3_PROX_TOUCH_TH0			0x2A
#define MBR3_PROX_TOUCH_TH1			0x2C
#define MBR3_PROX_HYS				0x30
#define MBR3_PROX_BUT				0x31
#define MBR3_PROX_LBR				0x32
#define MBR3_PROX_NNT				0x33
#define MBR3_PROX_NT				0x34
#define MBR3_PROX_POSITIVE_TH0		0x35
#define MBR3_PROX_POSITIVE_TH1		0x36
#define MBR3_PROX_NEGATIVE_TH0		0x39
#define MBR3_PROX_NEGATIVE_TH1		0x3A
#define MBR3_LED_ON_TIME			0x3D
#define MBR3_BUZZER_CFG				0x3E
#define MBR3_BUZZER_ON_TIME			0x3F
#define MBR3_GPO_CFG				0x40
#define MBR3_PWM_DUTYCYCLE_CFG0		0x41
#define MBR3_PWM_DUTYCYCLE_CFG1		0x42
#define MBR3_PWM_DUTYCYCLE_CFG2		0x43
#define MBR3_PWM_DUTYCYCLE_CFG3		0x44
#define MBR3_PWM_DUTYCYCLE_CFG4		0x45
#define MBR3_PWM_DUTYCYCLE_CFG5		0x46
#define MBR3_PWM_DUTYCYCLE_CFG6		0x47
#define MBR3_PWM_DUTYCYCLE_CFG7		0x48
#define MBR3_SPO_CFG				0x4C
#define MBR3_DEVICE_CFG0			0x4D
#define MBR3_DEVICE_CFG1			0x4E
#define MBR3_DEVICE_CFG2			0x4F
#define MBR3_I2C_ADDR				0x51
#define MBR3_REFRESH_CTRL			0x52
#define MBR3_STATE_TIMEOUT			0x55
#define MBR3_SLIDER_CFG				0x5D
#define MBR3_SLIDER1_CFG			0x61
#define MBR3_SLIDER1_RESOLUTION		0x62
#define MBR3_SLIDER1_THRESHOLD		0x63
#define MBR3_SLIDER2_CFG			0x67
#define MBR3_SLIDER2_RESOLUTION		0x68
#define MBR3_SLIDER2_THRESHOLD		0x69
#define MBR3_SLIDER_DEBOUNCE		0x6F
#define MBR3_SLIDER_BUT				0x70
#define MBR3_SLIDER_LBR				0x71
#define MBR3_SLIDER_NNT				0x72
#define MBR3_SLIDER_NT				0x73
#define MBR3_CONFIG_CRC				0x7E
#define MBR3_GPO_OUTPUT_STATE		0x80
#define MBR3_SENSOR_ID				0x82
#define MBR3_CTRL_CMD				0x86
#define MBR3_BUTTON_STATUS			0xAA
#define MBR3_PROX_STAT              0xAE

/* Command Codes */
#define MBR3_CMD_NULL			  	 0x00
#define MBR3_SAVE_CHECK_CRC          0x02
#define MBR3_CALC_CRC                0x03
#define MBR3_LOAD_FACTORY            0x04
#define MBR3_LOAD_PRIMARY            0x05
#define MBR3_LOAD_SECONDARY          0x06
#define MBR3_SLEEP                   0x07
#define MBR3_CLEAR_LATCHED_STATUS    0x08
#define MBR3_CMD_RESET_PROX0_FILTER	 0x09
#define MBR3_CMD_RESET_PROX1_FILTER	 0x0A
#define MBR3_ENTER_CONFIG_MODE       0x0B
#define MBR3_EXIT_CONTROL_RUN        0xFE
#define MBR3_SW_RESET                0xFF

/* Total number of configuration registers */
#define MBR3_TOTAL_CONFIG_REG_COUNT	 0x80

/* Length of Register Map */
#define MBR3_REG_MAP_LEN	256

/* Slave Address (Default) */
#define MBR3_SLAVE_ADDR	             0x37
	
#define MBR3_NO_OF_KIT_BUTTONS	     16

#define MBR3_BUZ_ON_1_33kHz          0x85
#define MBR3_BUZ_OFF_1_33kHz         0x05
#define MBR3_SPO_ENABLE              0x03
#define MBR3_SPO_DISABLE             0x00

#define I2C_WRITE                    0x00
#define I2C_READ                     0x01


// MBR3 chip initalization, uses a config table generated with EZ-Click software    
uint32_t MBR3_init(void);

// writes a buffer of data into the chip
uint32_t MBR3_writeBuf(uint8_t slaveAddr, uint8_t regAddr, uint8_t* buffer, uint8_t length);

// reads data from the chip into a buffer
uint32_t MBR3_readBuf(uint8_t slaveAddr, uint8_t regAddr, uint8_t* buffer, uint8_t length);


#endif
/* [] END OF FILE */
