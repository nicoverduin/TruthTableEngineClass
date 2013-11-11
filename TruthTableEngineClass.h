/**
 * TruthTableEngineClass.h
 *
 *  Created on	: 7 nov. 2013
 *  Author		: Nico Verduin
 *	Email		: info@verelec.com
 *  Website		: www.verelec.nl
 *
 * Revision Control
 * 
 * Latest Revsion
 * ____________________
 *
 * Revision	: $Revision: 3 $
 * Date		: $Date: 2013-11-11 14:08:57 +0100 (Mon, 11 Nov 2013) $
 * Author	: $Author: Nico $
 *
 */

#ifndef TRUTHTABLEENGINECLASS_H_
#define TRUTHTABLEENGINECLASS_H_

#include <Arduino.h>
//
// structure for Engine Array entries. Current setup can handle maximum of 8 inputs mapping to 8 outputs
//
#ifndef STRUCT_CONDITION
#define STRUCT_CONDITION
struct condition {
	uint32_t inputs;         // input conditions
	uint32_t outputs;        // output results
};
#endif
//
// complete set we are working with
//
struct EngineData {
	uint8_t *inputArray; 			// pointer to digital input pin array
	uint8_t *analogArray; 			// pointer to analog input pin array
	uint8_t *activeInputArray;		// pointer to active input levels (for digital inputs)
	uint8_t *digitalInputArray;		// pointer to digital input array (read values)
	unsigned int *analogInputArray;	// pointer to analog input array (read values)
	uint8_t *outputArray;			// pointer to output pin array
	uint8_t *activeOutputArray;		// pointer to active output levels
	uint8_t *digitalOutputArray;  	// pointer to digital output array (values to write)
	unsigned int *bandwidthArray;	// pointer to analog bandwidths
	condition *engineArray;			// pointer to conditions sets
	uint8_t	numberOfDigitalPins;	// number of digital pins
	uint8_t numberOfAnalogPins;		// number of analog pins
	uint8_t numberOfOutputPins;		// number of output pins
	unsigned int numberOfConditions;// number of conditions to test
	uint32_t testByte;				// 4 byte value that will be tested in Engine
	uint32_t outputByte;			// 4 byte result value from engine
};


class TruthTableEngine {
	public:
		TruthTableEngine();						// constructor
		void setup(EngineData *inp);			// sets the input and output ports
		void readInputs(EngineData *inp);		// reads the inputs from the digital pins
		void preProcess(EngineData *inp);		// processes all inputs
		void process(EngineData *inp);			// searches a valid combination
		void postProcess(EngineData *inp);		// processes all outputs
		void writeOutputs(EngineData *inp);		// writes the outputs to the digital pins
		void processAutomatic(EngineData *inp);	// processes the above in sequence
};

#endif /* TRUTHTABLEENGINECLASS_H_ */
