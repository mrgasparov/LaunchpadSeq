//
//  edit_mode_t.h
//  exampleInput
//
//  Created by Pedro Mendes on 15/06/14.
//
//

#ifndef exampleInput_edit_mode_t_h
#define exampleInput_edit_mode_t_h

// define enum velocity states
enum edit_mode_t {
    
    //line
    LINE_DELETE,
    LINE_MUTE,
    LINE_COPY,
    
    //page
    PAGE_DELETE,
    PAGE_COPY,
    
    //pattern bank
    PATTERN_SELECT,
    PATTERN_DELETE,
    PATTERN_COPY
};

#endif
