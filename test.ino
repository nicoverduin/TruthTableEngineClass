/**
 * test.cpp
 *
 *  Created on	: 9 nov. 2013
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
#include <Arduino.h>
#include "TruthTableEngineClass.h"	// truth table engine class
#include "Test_Set.h"				// generated test set

TruthTableEngine engine;			// we only need one engine

void setup(){
	Test_Set_buildModelStructure();	// function itself is generated in test set
	engine.setup(Test_Set_ptr);		// setup IO ports. TestSet_ptr is generated
}

void loop(){
	//
	// process all at once
	//
	engine.processAutomatic(Test_Set_ptr);
	//
	// or each individual step
	//
	engine.readInputs(Test_Set_ptr);	// reads the inputs from the digital pins
	engine.preProcess(Test_Set_ptr);	// processes all inputs
	engine.process(Test_Set_ptr);		// searches a valid combination
	engine.postProcess(Test_Set_ptr);	// processes all outputs
	engine.writeOutputs(Test_Set_ptr);	// writes the outputs to the digital pins
}
