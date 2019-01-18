#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "light_intense_i2c.h"

#undef __DEBUG__

#ifdef __DEBUG__
#include "esp_log.h"
static const char *TAG = "light_intense_i2c";
#endif

// light_intense_i2c registers
#define light_intense_i2c_MEAS_HIGHREP         0x2400

light_intense_i2c::light_intense_i2c(int bus_ch, int dev_addr) {
	channel = bus_ch;
	address = dev_addr;
	polling_ms = light_intense_i2c_POLLING_MS;
}

void light_intense_i2c::init(void) {
	state = s_detect;
}

int light_intense_i2c::prop_count(void) {
	return 1;
}

bool light_intense_i2c::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool light_intense_i2c::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool light_intense_i2c::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool light_intense_i2c::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool light_intense_i2c::prop_write(int index, char *value) {
	// not supported
	return false;
}

void light_intense_i2c::process(Driver *drv) {

	//printf("process\n");

	I2CDev *i2c = (I2CDev *)drv;
	uint8_t data[6];

	switch (state) {
		case s_detect:
			// stamp polling tickcnt
			polling_tickcnt = get_tickcnt();
			// detect i2c device
			if (i2c->detect(channel, address) == ESP_OK) {
				//printf("detected\n");
				state = s_read;// change state
			}
			else {
				state = s_error;
			}
			break;
		case s_read:
			//printf("start reading\n");
			data[0] = address;
			if (i2c->write(channel, address, data, 1) == ESP_OK){
				//printf("starting sensor\n");
			}
			data[0] = 0x13;
			if (i2c->write(channel, address, data, 1) == ESP_OK){
				//printf("set mode\n");
			}
			state = s_copyvalue;
		case s_copyvalue:
			data[0] = address;
			if (i2c->write(channel, address, data, 1) == ESP_OK){
				if (i2c->read(channel, address, NULL, 0, data, 6) == ESP_OK) {	
					uint16_t newresult = (data[0]<<8) | data[1];
					result = newresult;
					//printf("LIGHT INTENSITY %d\n", result);
					//or
					//memcpy(result, newresult, 8);
					initialized = true;
					// load polling tickcnt
					tickcnt = polling_tickcnt;
					// goto wait and retry with detect state
					state = s_wait;
				}
			}
			//state = s_idle;
			//printf(getRawValue());
			break;
		case s_idle:
			break;
		case s_error:
			// set error flag
			error = true;
			// clear initialized flag
			initialized = false;
			// get current tickcnt
			tickcnt = get_tickcnt();
			// goto wait and retry with detect state
			state = s_wait;
			break;
		case s_wait:
			// wait polling_ms timeout
			if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
				state = s_detect;
			}
			break;
	}
}

double light_intense_i2c::getRawValue(void) {
	//printf("getValue\n");
	return result;
}

