#ifndef TEST_SET_H
#define TEST_SET_H
#include "TruthTableEngineClass.h" 
/**
 * @file     D:\workspace\TruthTableEngine\Test_Set.h
 * @author   TruthTable Testset generator
 * @date     10-11-2013
 * @version  1.0
 * @mainPage
 * test set generated for Truth table engine
 */

/**
 * SVN version control. do not remove
 * $Revision: 3 $
 * $Date: 2013-11-11 14:08:57 +0100 (Mon, 11 Nov 2013) $
 * $Author: Nico $
 */

#ifdef __IN_ECLIPSE__
    #ifdef __cplusplus
        extern "C" {
    #endif
    void loop();
    void setup();
    #ifdef __cplusplus
       } // extern "C"
    #endif
#endif
#include <Arduino.h>
//
// pin definitions
//

#define	SWITCH_NUMMER_1_PIN	14	// SWITCH NUMMER 1
#define	NUMMER_2_PIN	15	// NUMMER 2
#define	DRIE_PIN	16	// DRIE
#define	VIER_PIN	17	// VIER
#define	OUTPUT_1_PIN	8	// OUTPUT 1
#define	OUTPUT_2_PIN	9	// OUTPUT 2
#define	OUT3_PIN	10	// OUT3
//
// pin Array
//
uint8_t Test_Set_inputArray[] =          // this array contains all the digital input pins used
{	SWITCH_NUMMER_1_PIN	,	// Switch nummer 1
	NUMMER_2_PIN	,	// Nummer 2
	DRIE_PIN	,	// Drie
	VIER_PIN	,	// vier
};
//
// Active input level Array
//
uint8_t Test_Set_activeInputArray[] =          // this array contains the active input level per pin
{	LOW 	,	// Switch nummer 1
	LOW 	,	// Nummer 2
	LOW 	,	// Drie
	LOW 	,	// vier
};
//
// Analog pin Array
//
uint8_t Test_Set_analogArray[] =          // this array contains all the analog input pins used
{};
//
// Output pin Array
//
uint8_t Test_Set_outputArray[] =          // this array contains all the digital output pins used
{	OUTPUT_1_PIN	,	// output 1
	OUTPUT_2_PIN	,	// output 2
	OUT3_PIN	,	// out3
};
//
// Active output level Array
//
uint8_t Test_Set_activeOutputArray[] =          // this array contains the active output level per pin
{	HIGH	,	// output 1
	HIGH	,	// output 2
	HIGH	,	// out3
};
//
// Bandwidth array
//
unsigned int Test_Set_bandwidthArray[][2] =          // this array contains the active bandwidths
{};
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
// Conditions array
//
// instructions for use:
// - on the input side, a "1" indicates that that switch or input is SET. See it as an X on a truth table
// - On the output, a "1" indicates it will set the output pin.
//
// However, as inputs and outputs might be different set in practice. i.e. pull-up or pull-down on the inputs
// or a setting of output would mean a "0" while normally they would be high. This is resolved with the
// defines INPUT_ON and OUTPUT_ON at the beginning of the program
//
//
// Conditions array
//
 condition Test_Set_engineArray[] =          // this array contains the Truth table
{
	{ B1000,	 B100},	// Condition 1
	{ B0100,	 B010},	// Condition 2
	{ B0010,	 B110},	// Condition 3
	{ B0001,	 B001},	// Condition 4
};
uint8_t Test_Set_digitalInputArray[ 4];    // contains the digital values read from the pins 
unsigned int Test_Set_analogInputArray[ 0];       // contains the analog values read from the pins 
uint8_t Test_Set_digitalOutputArray[ 3];       // contains the output values read from the engine
//
// collections of all arrays belonging to Test_Set
//
EngineData Test_Set;                        // contains all the pointers to this testset
EngineData *Test_Set_ptr;                    // pointer to this testset

/**
* @name Test_Set_buildModelStructure()
* builds the model structure for this dataset ready to be handed over to the TruthTable Engine
*/
void Test_Set_buildModelStructure() {
    Test_Set_ptr                    = &Test_Set;  // get address of Engine test set
    //
    // get pointers to individual generated arrays
    //
    Test_Set_ptr->digitalInputArray  = Test_Set_digitalInputArray;    // inputs from digital ports
    Test_Set_ptr->analogInputArray   = Test_Set_analogInputArray;     // inputs from analog ports
    Test_Set_ptr->bandwidthArray     = &Test_Set_bandwidthArray[0][0];// bandwidths for analog ports
    Test_Set_ptr->activeInputArray   = Test_Set_activeInputArray;     // input levels when active
    Test_Set_ptr->inputArray         = Test_Set_inputArray;           // pin definitions digital input
    Test_Set_ptr->analogArray        = Test_Set_analogArray;          // pin definitions analog input
    Test_Set_ptr->outputArray        = Test_Set_outputArray;          // pin definitions digital outputs
    Test_Set_ptr->activeOutputArray  = Test_Set_activeOutputArray;    // output levels when active
    Test_Set_ptr->digitalOutputArray = Test_Set_digitalOutputArray;   // outputs to digital ports
    Test_Set_ptr->engineArray        = Test_Set_engineArray;          // conditions to engine
    Test_Set_ptr->numberOfDigitalPins =  4;
    Test_Set_ptr->numberOfAnalogPins =  0;
    Test_Set_ptr->numberOfOutputPins =  3;
    Test_Set_ptr->numberOfConditions =  4;
}
#endif
