#ifndef __light_intense_i2c_H__
#define __light_intense_i2c_H__

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"

#define light_intense_i2c_POLLING_MS					1000

class light_intense_i2c : public Device {
	private:
		enum {
			 s_detect, s_read, s_error, s_wait , s_idle , s_copyvalue
		} state;
		TickType_t tickcnt, polling_tickcnt;
		int result;

	public:
		// constructor
		light_intense_i2c(int bus_ch, int dev_addr);
		// override
		void init(void);
		void process(Driver *drv);
		int prop_count(void);
		bool prop_name(int index, char *name);
		bool prop_unit(int index, char *unit);
		bool prop_attr(int index, char *attr);
		bool prop_read(int index, char *value);
		bool prop_write(int index, char *value);
		// method
		double getRawValue(void);
};

#endif
