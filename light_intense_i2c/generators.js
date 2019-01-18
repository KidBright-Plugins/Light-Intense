Blockly.JavaScript['light_intense_i2c.getRawValue'] = function(block) {
	return ['DEV_I2C1.light_intense_i2c(' + block.getFieldValue('CHANNEL') + ', ' + block.getFieldValue('ADDRESS') + ').getRawValue()',Blockly.JavaScript.ORDER_ATOMIC];
};

