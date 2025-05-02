/*
* Author: Ian Schiedenhelm
* Date: 04/3/2025
* Team1
* MIPS_Interpreter
*/

#include "Instruction.h"

void lui_immd_assm(void) {
    // Checking that the op code matches
	// strcmp(string1, string2) return 0 if they match
    if (strcmp(OP_CODE, "LUI") != 0) {
        state = WRONG_COMMAND;
        return;
    }

	/*
		Checking the type of parameters
	*/

    // Check if parameter 1 is a register
    if (PARAM1.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

	// Param 2 needs to be an immediate
    if (PARAM2.type != IMMEDIATE) {
        state = INVALID_PARAM;
        return;
    }

	/*
		Checking the value of parameters
	*/

    // Validate that register values is less than 31
    if (PARAM1.value > 31) {
        state = INVALID_REG;
        return;
    }

    // The offset value is limited to 16 bits
    if (PARAM2.value > 0xFFFF) {
        state = INVALID_IMMED;
        return;
    }

	/*
		Putting the binary together
	*/

    // Set opcode
    setBits_str(31, "001111");

    // Set bits for Rt
    setBits_num(20, PARAM1.value, 5);  

    // Set the immediate at less than 16
    setBits_num(15, PARAM3.value, 16);

    // Tell system encoding is complete
    state = COMPLETE_ENCODE;
}

// Function to decode the binary instruction
void lui_immd_bin(void) {
    // Check if the op code bits match
	// check_bits(start_bit, bit_string) returns 0 if the bit_string matches
	//  any x will be skipped
	// If the manual shows (0), then the value of that bit doesnt matter
    if (checkBits(31, "001111") != 0) {
        state = WRONG_COMMAND;
        return;
    }
	
	// If the op code bits match, then the rest can be read as correctly

	/*
		Finding values in the binary
	*/

    // getBits(start_bit, width)
    uint32_t Rt = getBits(20, 5);
    uint32_t imm16 = getBits(15, 16);  

    /*
		Setting Instruction values
	*/

    setOp("LUI");
	//setCond_num(cond);
	//setParam(param_num, param_type, param_value)
    setParam(1, REGISTER, Rt); //destination
    setParam(2, IMMEDIATE, imm16); //second source register operand

    // Tell system decoding is complete
    state = COMPLETE_DECODE;
}
