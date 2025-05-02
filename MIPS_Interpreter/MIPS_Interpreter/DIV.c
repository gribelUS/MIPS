/*
* Author: Tiago Breunig
* Date: 04/03/2025
* Team1
* MIPS_Interpreter
*/

#include "Instruction.h"

void div_reg_assm(void) {
	// Checking that the op code matches
	// strcmp(string1, string2) returns 0 if they match
	if (strcmp(OP_CODE, "DIV") != 0) {
		// If the op code doesn't match, this isn't the correct command
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of parameters
	*/

	// The first parameter should always be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// The second parameter needs to be a register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Rs should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rt should be 31 or less
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	/*
		Putting binary together
	*/

	// Set opcode for R-type instruction
	setBits_str(31, "000000");

	// Set rs
	setBits_num(25, PARAM1.value, 5);

	// Set rt
	setBits_num(20, PARAM2.value, 5);

	// Set function code
	setBits_str(5, "011010");

	// Set rd and shamt to 0
	setBits_num(15, 0, 10);
	
	// Indicate that encoding is complete
	state = COMPLETE_ENCODE;
}

void div_reg_bin(void) {
	// Check if the instruction matches the binary pattern for DIV
	// Opcode should be 000000 and funct should be 011010
	if (checkBits(31, "000000") != 0 || checkBits(5, "011010") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Finding values in the binary
	*/

	// Extract rs from bits 25-21
	uint32_t Rs = getBits(25, 5);

	// Extract rt from bits 20-16
	uint32_t Rt = getBits(20, 5);

	// Set operation name to DIV
	setOp("DIV");

	// Store extracted register values in parameters
	setParam(1, REGISTER, Rs);
	setParam(2, REGISTER, Rt);

	// Tell the system the decoding is done
	state = COMPLETE_DECODE;
}


