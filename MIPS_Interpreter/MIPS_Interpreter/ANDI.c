/*
* Author: Tiago Breunig
* Date: 04/03/2025
* Team1
* MIPS_Interpreter
*/

#include "Instruction.h"

void andi_immd_assm(void) {
	// Checking that the op code matches
	// strcmp(string1, string2) return 0 if they match
	if (strcmp(OP_CODE, "ANDI") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of parameters
	*/

	// The first parameter should be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// The second parameter needs to be a register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// The third parameter needs to be an immediate
	if (PARAM3.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

	/*
		Checking the value of parameters
	*/

	//Rt should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rs should be 31 or less
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	// The immediate value is limited to 16 bits, this is 0xFFFF
	if (PARAM3.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}

	/*
		Putting the binary together
	*/

	// Set the opcode
	setBits_str(31, "001100");

	// Set Rt
	setBits_num(20, PARAM1.value, 5);

	// Set Rs
	setBits_num(25, PARAM2.value, 5);

	// Set immediate
	setBits_num(15, PARAM3.value, 16);

	// Tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void andi_immd_bin(void) {
	// Check if the opcode bits match
	// Check_bits(start_bit, bit_string) returns 0 if the bit_string matches
	// Any x will be skipped
	// If the manual shows (0), then the value of that bit doesn't matter
	if (checkBits(31, "001100") != 0 ) {
		state = WRONG_COMMAND;
		return;
	}

	// If the op code bits match, then the rest can be read as correctly

	/*
		Finding values in the binary
	*/
	
	// getBits(start_bit, width)
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t imm16 = getBits(15, 16);

	/*
		Setting Instruction values
	*/

	setOp("ANDI");
	//setCond_num(cond);
	//setParam(param_num, param_type, param_value)
	setParam(1, REGISTER, Rt); // Destination
	setParam(2, REGISTER, Rs); // First source register operand
	setParam(3, IMMEDIATE, imm16); // Immediate operand
	
	// Tell system the decoding is done
	state = COMPLETE_DECODE;
}



