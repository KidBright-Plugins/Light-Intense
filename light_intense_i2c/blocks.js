Blockly.Blocks["light_intense_i2c.getRawValue"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.LIGHT_INTENSE_TITLE);
		// i2c channel 0 to 64
		var channel_array = [];
		for (var i = 0;i <= 0; i++) {
			channel_array.push([String(i), String(i)]);
		}
		this.appendDummyInput()
			.appendField(Blockly.Msg.CHANNEL)
			.appendField(new Blockly.FieldDropdown(channel_array), 'CHANNEL');

		// device addess
		this.appendDummyInput()
			.appendField(Blockly.Msg.ADDRESS)
			.appendField(new Blockly.FieldDropdown([
				["0x23", "35"]
			]), 'ADDRESS');

		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(58);
		this.setTooltip(Blockly.Msg.LIGHT_INTENSE_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.LIGHT_INTENSE_HELPURL);
	}
};