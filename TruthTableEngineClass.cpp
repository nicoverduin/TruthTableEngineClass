/**
 * TruthTableEngineClass.cpp
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
#include "TruthTableEngineClass.h"

/**
 * @name TruthTableEngine()
 * constructor
 */
TruthTableEngine::TruthTableEngine() {
}
/**
 * @name setup(EngineData *inp)
 * @parameter inp pointer to EngineData structure
 * sets the input and output ports
 */
void TruthTableEngine::setup(EngineData *inp) {
	//
	// setup digital input and output pins
	//
	for (uint8_t i = 0; i < inp->numberOfDigitalPins; i++) {
		pinMode(inp->inputArray[i], INPUT);
	}
	for (uint8_t i = 0; i < inp->numberOfOutputPins; i++) {
		pinMode(inp->outputArray[i], OUTPUT);
	}
}


/**
 * @name readInputs(EngineData *inp)
 * @parameter inp pointer to EngineData structure
 * reads the inputs from the digital and analog pins
 */
void TruthTableEngine::readInputs(EngineData *inp) {
	//
	// read the digital inputs
	//
	for (uint8_t i = 0; i < inp->numberOfDigitalPins; i++) {
		inp->digitalInputArray[i] = digitalRead(inp->inputArray[i]);
	}
	//
	// read the analog inputs
	//
	for (uint8_t i = 0; i < inp->numberOfAnalogPins; i++) {
		inp->analogInputArray[i] = analogRead(inp->analogArray[i]);
	}
}
/**
 * @name preProcess(EngineData *inp)
 * @param inp pointer to EngineData structure
 * preprocesses the data by validating the input pins against the active logic levels
 * and analog values if they fit within the bandwidth
 */
void TruthTableEngine::preProcess(EngineData *inp) {

	inp->testByte = 0;				// no inputs processed yet
    //
    // process digital inputs
    //
    for (uint8_t i = 0; i < inp->numberOfDigitalPins; i++) {
        //
        // shift the bits in testByte one bit left first and then add the digital reading of the pin
        //
        inp->testByte = inp->testByte << 1;               				// shift left one bit
        if(inp->digitalInputArray[i] == inp->activeInputArray[i]) {    // set right bit setting in test byte
            inp->testByte += 1;
        } else {
            inp->testByte += 0;
        }
    }

    //
    // preprocessing analog inputs
    //
    for (uint8_t i = 0; i < inp->numberOfAnalogPins; i++){
        //
        // check if within bandwidth
        //
        inp->testByte = inp->testByte << 1;                       		// shift one bit left
        uint8_t j = (i * 2 * sizeof(unsigned int));						// determine offsets
        if (inp->analogInputArray[i] >= inp->bandwidthArray[j]) {       // value larger/equal than minimum value
            if (inp->analogInputArray[i] <= inp->bandwidthArray[j+1]) { // value smaller/equal than maximum value
                //
                // fits in the bandwidth
                //
                inp->testByte = inp->testByte + 1;                		// set lowest bit to 1
            }
        }
    }

}
/**
 * @name process(EngineData *inp)
 * @param inp pointer to EngineData structure
 * searches the condition table for a valid (= equal) entry like testByte and
 * puts the result in output byte
 */
void TruthTableEngine::process(EngineData *inp) {
    //
    // Check if there is an entry with a corresponding match in the engine array
    //
	inp->outputByte = 0L;

    for (uint8_t i = 0; i < inp->numberOfConditions; i++){
        if (inp->engineArray[i].inputs == inp->testByte) {
            //
            // we found a corresponding entry
            //
            inp->outputByte = inp->engineArray[i].outputs;
            //
            // and we can break out of the loop
            //
            break;
        }
    }
}
/**
 * @name postProcess(EngineData *inp)
 * @param inp pointer to EngineData structure
 * Breaks the output byte into the individual array entries
 */
void TruthTableEngine::postProcess(EngineData *inp) {

	uint32_t wOutputByte;			// work value so outputByte stays intact

	wOutputByte = inp->outputByte;
    //
    // now the post processing. copy each bit value from outputByte into the output array
    //
    for (int i = inp->numberOfOutputPins - 1; i >=0; i--) {
        //
        // mask all but the least significant bit and set the digitalOutput Array
    	//
        if ((wOutputByte & 0x0001) == 1) {
        	inp->digitalOutputArray[i] = 1;
        } else {
        	inp->digitalOutputArray[i] = 0;
        }
        //
        // right shift outputByte one bit
        //
        wOutputByte = wOutputByte >> 1;
    }
}

/**
 * @name writeOutputs(EngineData *inp)
 * @param inp pointer to EngineData structure
 * copies the digital output array to the corresponding pin outputs
 */
void TruthTableEngine::writeOutputs(EngineData *inp) {
    //
    // now the post processing. copy each digital output to the correct pin and set the active level
    //
    for (uint8_t i = 0; i < inp->numberOfOutputPins; i++) {
        //
        // test each bit
        //
        if (inp->digitalOutputArray[i] == 1) {
            digitalWrite(inp->outputArray[i], inp->activeOutputArray[i]);
        } else {
            digitalWrite(inp->outputArray[i], !inp->activeOutputArray[i]);
        }
    }
}
/**
 * @name processAutomatic(EngineData *inp)
 * @param inp pointer to EngineData structure
 * processes the whole sequence from reading inputs to writing outputs
 */
void TruthTableEngine::processAutomatic(EngineData *inp) {
	readInputs(inp);		// read inputs
	preProcess(inp);		// pre process into testbyte
	process(inp);			// search for valid combination
	postProcess(inp);		// copy result to output array
	writeOutputs(inp);		// write digital pins based on active levels
}
