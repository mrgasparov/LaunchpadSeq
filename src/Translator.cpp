//
//  Translator.cpp
//  exampleInput
//
//  Created by Pedro Mendes on 11/06/14.
//
//

#include "Translator.h"

// Global static pointer used to ensure a single instance of the class.
Translator* Translator::m_pInstance = NULL;

/** This function is called to create an instance of the class.
 Calling the constructor publicly is not allowed. The constructor
 is private and is only called by this Instance function.
 */

Translator* Translator::Instance()
{
    if (!m_pInstance)   // Only allow one instance of class to be generated.
        m_pInstance = new Translator;
    
    return m_pInstance;
}

// VELOCITY STATE --> PAD COLOR

void Translator::init_v_to_pc_map() {
    
    //v_to_pc_map = TRMap();
    
    v_to_pc_map[VEL_OFF] = OFF;
    v_to_pc_map[VEL_MIN] = GREEN_DIM;
    v_to_pc_map[VEL_MED] = GREEN_MED;
    v_to_pc_map[VEL_MAX] = GREEN_FULL;
}

pad_colors_t Translator::v_to_pc(velocity_states_t _vel) {
    
    pad_colors_t pc = (pad_colors_t) v_to_pc_map[_vel];
    
    return pc;
}