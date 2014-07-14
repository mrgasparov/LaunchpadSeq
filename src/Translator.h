//
//  Translator.h
//  exampleInput
//
//  Created by Pedro Mendes on 11/06/14.
//
//

#ifndef __exampleInput__Translator__
#define __exampleInput__Translator__

#include <iostream>

#include "ofMain.h"

#include "pad_colors_t.h"
#include "velocity_states_t.h"

class Translator{
    
public:
    
    static Translator* Instance();
    
    // global init
    void init();
    
    // init velocity to pad color map
    void init_v_to_pc_map();
    
    // translate velocity to pad color
    pad_colors_t v_to_pc(velocity_states_t _vel);
    
private:
    
    typedef std::map<int, int> TRMap;
    
    TRMap v_to_pc_map;
    
    Translator(){};  // Private so that it can  not be called
    Translator(Translator const&){};             // copy constructor is private
    Translator& operator=(Translator const&){};  // assignment operator is private
    static Translator* m_pInstance;
};


#endif /* defined(__exampleInput__Translator__) */
