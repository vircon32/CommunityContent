// include Vircon libraries
#include "audio.h"
#include "video.h"
#include "time.h"
#include "string.h"
#include "misc.h"

// include project libraries
#include "ErrorInfo.h"

// ---------------------------------------------------------
//     GENERAL DEFINITIONS
// ---------------------------------------------------------

// Simplify opcode display
struct string_data
{
    int [40] name;
    int      lower;
    int      upper;
};

// BIOS-required regions; these
// may safely be used by programs
#define first_region_font         0
#define region_white_pixel        256

// other non-required regions, used
// to draw the logo and error screens
#define region_console            300
#define region_cartridge          301
#define region_down_arrow         302
#define region_white_square       303

// colors for error screens
#define error_colors_background   0xFF8D4130
#define error_colors_title        color_yellow
#define error_colors_description  color_white
#define error_colors_values       0xFF8080FF

// ---------------------------------------------------------
//     SUPPORT FUNCTIONS
// ---------------------------------------------------------

// fixed itoa implementation (pending new DevTools release)
void itoa2 (int value, int *result_text, int base)
{
    int [16+1]  hex_values    = "0123456789ABCDEF";
    int [32+1]  rev_digits;
    int        *next_digit    = rev_digits;
    int         carry         = 0;
    int         signval       = 0;
    int         symbol        = 0;

    if ((base                <  2) ||
        (base                >  16))
    {
        return;
    }

    if (value                <  0)
    {
        if (base             == 10)
        {
            *result_text      = '-';
            ++result_text;
            value             = -value;
        }
        else
        {
            signval           = 0x40000000;
            value             = value   - 0x80000000;
        }    
    }

    do
    {
        symbol                = (value  % base)     + carry;
        symbol                = symbol  + ((signval % base) * 2);

        carry                 = 0;
        while (symbol        >= base)
        {
            symbol            = symbol  - base;
            carry             = carry   + 1;
        }

        *next_digit           = symbol;
        ++next_digit;

        value                 = value   / base;
        signval               = signval / base;
    }
    while ((value            != 0) ||
           (carry            >  0));

    do
    {
        --next_digit;
        *result_text          = hex_values[(int)(*next_digit)];
        ++result_text;
    }
    while (next_digit        != &rev_digits[0]);

    *result_text              = 0;
}

////////////////////////////////////////////////////////////////////////////////////////
//
// decode and display instruction and associated data at provided address
//
void decode_instruction (int word, int y, int immediate_value)
{
    int      opcode;
    int      immflag;
    int      dstreg;
    int      srcreg;
    int      addrmode;
    int      portnum;
    int      size;
    int [11] data;
    int      x;
    int      flag;
    int      category;
    int      attribute;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // initialize our opcodes array with the available instructions
    //
    string_data [64] opcodes    =
    {
        { "HLT"  }, { "WAIT"  }, { "JMP"   }, { "CALL" },
        { "RET"  }, { "JT"    }, { "JF"    }, { "IEQ"  },
        { "INE"  }, { "IGT"   }, { "IGE"   }, { "ILT"  },
        { "ILE"  }, { "FEQ"   }, { "FNE"   }, { "FGT"  },
        { "FGE"  }, { "FLT"   }, { "FLE"   }, { "MOV"  },
        { "LEA"  }, { "PUSH"  }, { "POP"   }, { "IN"   },
        { "OUT"  }, { "MOVS"  }, { "SETS"  }, { "CMPS" },
        { "CIF"  }, { "CFI"   }, { "CIB"   }, { "CFB"  },
        { "NOT"  }, { "AND"   }, { "OR"    }, { "XOR"  },
        { "BNOT" }, { "SHL"   }, { "IADD"  }, { "ISUB" },
        { "IMUL" }, { "IDIV"  }, { "IMOD"  }, { "ISGN" },
        { "IMIN" }, { "IMAX"  }, { "IABS"  }, { "FADD" },
        { "FSUB" }, { "FMUL"  }, { "FDIV"  }, { "FMOD" },
        { "FSGN" }, { "FMIN"  }, { "FMAX"  }, { "FABS" },
        { "FLR"  }, { "CEIL"  }, { "ROUND" }, { "SIN"  },
        { "ACOS" }, { "ATAN2" }, { "LOG"   }, { "POW"  }
    };

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // initialize our port category arrays with the available port names
    //
    ////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // time port names
    //
    string_data [4] tim_ports   =
    {
        { "TIM_CurrentDate"          },
        { "TIM_CurrentTime"          },
        { "TIM_FrameCounter"         },
        { "TIM_CycleCounter"         }
    };

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // RNG port names
    //
    string_data [1] rng_ports   =
    {
        { "RNG_CurrentValue"         }
    };

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // GPU port names
    //
    string_data [18] gpu_ports  =
    {
        { "GPU_Command"              },
        { "GPU_RemainingPixels"      },
        { "GPU_ClearColor"           },
        { "GPU_MultiplyColor"        },
        { "GPU_ActiveBlending"       },
        { "GPU_SelectedTexture"      },
        { "GPU_SelectedRegion"       },
        { "GPU_DrawingPointX"        },
        { "GPU_DrawingPointY"        },
        { "GPU_DrawingScaleX"        },
        { "GPU_DrawingScaleY"        },
        { "GPU_DrawingAngle"         },
        { "GPU_RegionMinX"           },
        { "GPU_RegionMinY"           },
        { "GPU_RegionMaxX"           },
        { "GPU_RegionMaxY"           },
        { "GPU_RegionHotspotX"       },
        { "GPU_RegionHotspotY"       }
    };

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // SPU port names
    //
    string_data [14] spu_ports  =
    {
        { "SPU_Command"              },
        { "SPU_GlobalVolume"         },
        { "SPU_SelectedSound"        },
        { "SPU_SelectedChannel"      },
        { "SPU_SoundLength"          },
        { "SPU_SoundPlayWithLoop"    },
        { "SPU_SoundLoopStart"       },
        { "SPU_SoundLoopEnd"         },
        { "SPU_ChannelState"         },
        { "SPU_ChannelAssignedSound" },
        { "SPU_ChannelVolume"        },
        { "SPU_ChannelSpeed"         },
        { "SPU_ChannelLoopEnabled"   },
        { "SPU_ChannelPosition"      }
    };

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // INP port names
    //
    string_data [13] inp_ports  =
    {
        { "INP_SelectedGamepad"      },
        { "INP_GamepadConnected"     },
        { "INP_GamepadLeft"          },
        { "INP_GamepadRight"         },
        { "INP_GamepadUp"            },
        { "INP_GamepadDown"          },
        { "INP_GamepadButtonStart"   },
        { "INP_GamepadButtonA"       },
        { "INP_GamepadButtonB"       },
        { "INP_GamepadButtonX"       },
        { "INP_GamepadButtonY"       },
        { "INP_GamepadButtonL"       },
        { "INP_GamepadButtonR"       }
    };

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // CAR port names
    //
    string_data [4] car_ports   =
    {
        { "CAR_Connected"            },
        { "CAR_ProgramROMSize"       },
        { "CAR_NumberOfTextures"     },
        { "CAR_NumberOfSounds"       }
    };

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // MEM port names
    //
    string_data [1] mem_ports   =
    {
        { "MEM_Connected"            }
    };

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // connect all the categories together
    //
    size                        = sizeof (string_data *) * 7;
    string_data **port          = (string_data **) malloc (size);
    *(port+0)                   = tim_ports;
    *(port+1)                   = rng_ports;
    *(port+2)                   = gpu_ports;
    *(port+3)                   = spu_ports;
    *(port+4)                   = inp_ports;
    *(port+5)                   = car_ports;
    *(port+6)                   = mem_ports;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // mask out and obtain individual instruction elements
    //
    opcode                      = (word    & 0xFC000000) >> 26;
    immflag                     = (word    & 0x02000000) >> 25;
    dstreg                      = (word    & 0x01E00000) >> 21;
    srcreg                      = (word    & 0x001E0000) >> 17;
    addrmode                    = (word    & 0x0001C000) >> 14;
    portnum                     = (word    & 0x00003FFF);

    category                    = (portnum & 0x00000700) >> 8;
    attribute                   = (portnum & 0x000000FF);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // display the obtained instruction
    //
    x                           = 169;
    print_at (x, y, opcodes[opcode].name);
    x                           = x + ((strlen (opcodes[opcode].name)+1)*10);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // special case processing:
    //   * zero parameter instructions (we're done)
    //   * one parameter instruction (display the first parameter and return)
    //   * everything else is a two parameter instruction
    //
    switch (opcode)
    {
        // zero parameter instructions
        case 0x00: // HLT
        case 0x01: // WAIT
        case 0x04: // RET
        case 0x19: // MOVS
        case 0x1A: // SETS
            return;
            break;

        // one parameter instructions
        case 0x02: // JMP
        case 0x03: // CALL
        case 0x15: // PUSH
        case 0x16: // POP
        case 0x1B: // CMPS
        case 0x1C: // CIF
        case 0x1D: // CFI
        case 0x1E: // CIB
        case 0x1F: // CFB
        case 0x20: // NOT
        case 0x24: // BNOT
        case 0x2B: // ISGN
        case 0x2E: // IABS
        case 0x34: // FSGN
        case 0x37: // FABS
        case 0x38: // FLR
        case 0x39: // CEIL
        case 0x3A: // ROUND
        case 0x3B: // SIN
        case 0x3C: // ACOS
        case 0x3E: // LOG
            if (immflag        == 1)
            {
                print_at (x, y, "0x");
                x               = x + 20;
                itoa2 (immediate_value, data, 16);
                print_at (x, y, data);
            }
            else // register variant
            {
                print_at (x, y, "R");
                x               = x + 10;
                itoa2 (dstreg, data, 10); // dstreg is used by all, apparently
                print_at (x, y, data);
            }
            return;
            break;
    };

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // ALL the first parameter processing for two parameter
    // instructions (with special cases for MOV and OUT)
    //
    if (opcode                 == 0x13) // MOV
    {
        if (addrmode           >  4) // MOV addressing modes 5, 6, 7 we dereference
        {
            print_at (x, y, "[");
            x                   = x + 10;
        }

        if ((addrmode          == 5)  ||
            (addrmode          == 7))
        {
            if (addrmode       == 7)
            {
                print_at (x, y, "R");
                x               = x + 10;
                itoa2 (srcreg, data, 10);
                print_at (x, y, data);
                x               = x + (strlen (data) * 10);
                print_at (x, y, "+");
                x               = x + 10;
            }

            // print out `immediate_value`
            print_at (x, y, "0x");
            x                   = x + 20;
            itoa2 (immediate_value, data, 16);
            print_at (x, y, data);
            x                   = x + (strlen (data) * 10);
        }
        else // otherwise, a register reference is made
        {
            print_at (x, y, "R");
            x                   = x + 10;
            itoa2 (dstreg, data, 10);
            print_at (x, y, data);
            x                   = x + 10;
            if (dstreg         >  9)
                x               = x + 10;
        }

        if (addrmode           >  4)
        {
            print_at (x, y, "]");
            x                   = x + 10;
        }
    }
    else if (opcode            == 0x18) // OUT: first parameter is always a port number
    {
        print_at (x, y, (*(port+category)+attribute) -> name);
        size                    = strlen ((*(port+category)+attribute) -> name) * 10;
        x                       = x + size;
    }
    else // AVERAGE CASE: any other two parameter instruction; show dstreg
    {
        print_at (x, y, "R");
        x                       = x + 10;
        itoa2 (dstreg, data, 10);
        print_at (x, y, data);
        x                       = x + 10;
        if (dstreg             > 9)
            x                   = x + 10;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Display the parameter separating comma and space
    //
    print_at (x, y, ", ");
    x                           = x + 20;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Two parameter, second parameter display. Special cases for LEA, OUT
    //
    flag                        = 0;
    if (opcode                 == 0x14) // LEA
    {
        print_at (x, y, "[");
        x                       = x + 10;
        flag                    = 1;

        if (immflag            == 1)
        {
            print_at (x, y, "R");
            x                   = x + 10;
            itoa2 (srcreg, data, 10);
            print_at (x, y, data);
            x                   = x + (strlen (data) * 10);
            print_at (x, y, "+");
            x                   = x + 10;
        }
    }
    else if (opcode            == 0x13) // MOV
    {
        if ((addrmode          >= 2)  &&
            (addrmode          <= 4))
        {
            print_at (x, y, "[");
            x                   = x + 10;
            flag                = 1;

            if (addrmode       == 4)
            {
                print_at (x, y, "R");
                x               = x + 10;
                itoa2 (srcreg, data, 10);
                print_at (x, y, data);
                x               = x + (strlen (data) * 10);
                print_at (x, y, "+");
                x               = x + 10;
            }
        }
        else if (addrmode      >= 5)
        {
            flag                = 2;
        }
    }
    else if (opcode            == 0x18) // OUT special case (only if immflag is set)
    {
        if (immflag            == 1)
        {
            print_at (x, y, "[");
            x                   = x + 10;
            flag                = 1;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // AVERAGE CASE (not MOV)
    //
    if ((immflag               == 1) &&
        (flag                  != 2))   // immediate value variant
    {
        print_at (x, y, "0x");
        x                       = x + 20;
        itoa2 (immediate_value, data, 16);
        print_at (x, y, data);
        x                       = x + (strlen (data) * 10);
    }
    else if (opcode            == 0x17) // IN special case (port number)
    {
        print_at (x, y, (*(port+category)+attribute) -> name);
        size                    = strlen ((*(port+category)+attribute) -> name) * 10;
        x                       = x + size;
    }
    else // register variant
    {
        print_at (x, y, "R");
        x                       = x + 10;
        itoa2 (srcreg, data, 10);
        print_at (x, y, data);
        x                       = x + (strlen (data) * 10);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Wrapping up special case two parameter, second parameter edge cases
    //
    if (flag                   == 1)
    {
        print_at (x, y, "]");
    }
}

void draw_message_screen (error_message* message)
{
    clear_screen (error_colors_background);
    set_multiply_color (color_white);
    select_texture (-1);
    
    // write title
    set_multiply_color( error_colors_title );
    print_at( 49, 37, message->title );
    
    // draw horizontal line
    select_region( region_white_square );
    set_drawing_scale( 640/2, 1 );
    draw_region_zoomed_at( 0, 60 );
    set_drawing_scale( 1, 1 );
    
    // write description
    set_multiply_color( error_colors_description );
    print_at( 49, 95, message->description );
}

// ---------------------------------------------------------

void print_hex_value( int x, int y, int* name, int value )
{
    // convert the number to hex, always
    // showing the full 8 hex digits
    int[ 16+1 ] hex_characters = "0123456789ABCDEF";
    int[ 8+1 ] hex_string;
    
    for( int Digit = 7; Digit >= 0; Digit-- )
    {
        hex_string[ Digit ] = hex_characters[ value & 15 ];
        value >>= 4;
    }
    
    hex_string[ 8 ] = 0;
    
    // join all text parts
    int[ 60 ] text;
    strcpy( text, name );
    strcat( text, " = 0x" );
    strcat( text, hex_string );
    
    // print the text
    print_at( x, y, text );
}

// ---------------------------------------------------------

bool cartridge_connected()
{
    asm
    {
        "in R0, CAR_Connected"
    }
}

// ---------------------------------------------------------

void request_cartridge()
{
    // write a custom message as if it was an error
    error_message no_cartridge_message =
    {
        "NO CARTRIDGE FOUND",
        "To play a game, please power off\n"
        "your console and insert a game\n"
        "cartridge compatible with Vircon32."        
    };
    
    draw_message_screen( &no_cartridge_message );
    
    // draw console diagram
    set_multiply_color( color_white );
    select_region( region_console );
    draw_region_at( 400, 207 );
    
    select_region( region_cartridge );
    draw_region_at( 469, 76 );
    
    select_region( region_down_arrow );
    draw_region_at( 497, 149 );
    
    // ensure everything gets drawn
    end_frame();
}


// ---------------------------------------------------------
//     ERROR HANDLER FUNCTION
// ---------------------------------------------------------


void error_handler()
{
    // do not initialize these!
    // or else R0 will be overwritten
    int       error_code;
    int       instruction_pointer;
    int       instruction;
    int       immediate_value;
    
    // save registers to variables
    asm
    {
        "mov {error_code}, R0"
        "mov {instruction_pointer}, R1"
        "mov {instruction}, R2"
        "mov {immediate_value}, R3"
    }
    // we could also have done: `mov {addr}, R1` in the asm section

    //////////////////////////////////////////////////////////////////
    //
    // variables for instruction decoding
    //
    int      *addr;
    int [11]  data;
    int       immflag;
    int [15]  list;
    int       word;
    int       pos;
    int       index;
    int       value;
    int       x;
    int       y;
    int       min;
    int       max;
    int       section;
    
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // initialize memory type array with their identified names    
    //
    string_data [4] memtype     =
    {
        { "[RAM] " }, { "[BIOS]" }, { "[CART]" }, { "[CARD]" }
    };
    memtype[0].lower            = 0x00000000;
    memtype[0].upper            = 0x003FFFFF;
    memtype[1].lower            = 0x10000000;
    memtype[1].upper            = 0x100FFFFF;
    memtype[2].lower            = 0x20000000;
    memtype[2].upper            = 0x27FFFFFF;
    memtype[3].lower            = 0x30000000;
    memtype[3].upper            = 0x30003FFF;

    // ensure everything gets drawn
    end_frame ();
    
    // all possible error messages; do NOT store this as
    // global variables, since it may collide with globals
    // defined in the programs running from the cartridge
    error_message [12] error_messages =
    {
        {
            "ERROR: INVALID MEMORY READ",
            "Program attempted to read from a memory address\n"
            "that does not exist or is in a write-only device."
        },
        {
            "ERROR: INVALID MEMORY WRITE",
            "Program attempted to write on a memory address\n"
            "that does not exist or is in a read-only device."
        },
        {
            "ERROR: INVALID PORT READ",
            "Program attempted to read from a port number\n"
            "that does not exist or is set as write-only."
        },
        {
            "ERROR: INVALID PORT WRITE",
            "Program attempted to write on a port number\n"
            "that does not exist or is set as read-only."
        },
        {
            "ERROR: STACK OVERFLOW",
            "Program pushed too many values in the stack\n"
            "and available RAM memory was exhausted."
        },
        {
            "ERROR: STACK UNDERFLOW",
            "Program popped too many values from the stack\n"
            "and all data stored in stack was exhausted."
        },
        {
            "ERROR: DIVISION BY ZERO",
            "Program attempted to perform a division or\n"
            "modulus operation where the divisor was zero."
        },
        {
            "ERROR: ARC COSINE OUT OF RANGE",
            "Program attempted to perform an arc cosine\n"
            "operation when the argument was not in [-1,+1]."
        },
        {
            "ERROR: ARC TANGENT NOT DEFINED",
            "Program attempted to perform an arc tangent\n"
            "operation when both of the arguments were 0."
        },
        {
            "ERROR: LOGARITHM OUT OF RANGE",
            "Program attempted to perform a logarithm\n"
            "operation when the argument is not positive."
        },
        {
            "ERROR: POWER HAS NO REAL SOLUTION",
            "Program attempted to perform a power operation\n"
            "when base was negative and exponent non integer."
        },
        {
            "UNKNOWN ERROR",
            "Program caused a hardware error with an error\n"
            "code that was not recognized by the BIOS."
        }
    };
    
    // write the appropriate message for this error code
    if ((error_code               >= 0) &&
        (error_code               <  (int) error_unknown))
    {
        draw_message_screen (&error_messages[error_code]);
    }
    else
    {
        draw_message_screen (&error_messages[error_unknown]);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Ascertain and display type of memory where error condition occurred
    //
    section                        = (instruction_pointer & 0x30000000) >> 28;
    print_at (579, 0, memtype[section].name);
    
    // now print the related hex values
    x                              = 49;
    set_multiply_color (error_colors_values);
    print_hex_value (x, 160, "Instruction Pointer", instruction_pointer);
    print_hex_value (x, 180, "Instruction        ", instruction);
    print_hex_value (x, 200, "Immediate Value    ", immediate_value);

    // do not do instruction dump for BIOS errors
    //
    if (section                   != 1)
    {
        // lookahead instruction logic
        //
        addr                       = (int *)(instruction_pointer);
        pos                        = 9;
        max                        = 5;
        while (pos                <  (max * 3))
        {
            list[pos]              = (int)(addr); // addr of +N instruction
            list[pos+1]            = *(addr);     // actual hex of +N instruction
            immflag                = (*(addr) & 0x02000000) >> 25;
            if (immflag           == 1)
            {
                addr               = addr + 1;
                list[pos+2]        = *(addr);     // immediate value to +N instruction
            }
            else
            {
                list[pos+2]        = 0;
            }

            // lookahead upper bound check
            //
            if ((int)addr         == memtype[section].upper)
            {
                max                = (pos + 3) / 3;
                break;
            }

            addr                   = addr + 1;
            pos                    = pos  + 3;
        }

        // look back, get to instruction
        pos                        = 6;
        immflag                    = (instruction & 0x02000000) >> 25;

        if (immflag               == 1)
        {
            addr                   = (int *)(instruction_pointer-2);
            list[pos+2]            = *(addr+1);
        }
        else
        {
            addr                   = (int *)(instruction_pointer-1);
            list[pos+2]            = 0;
        }

        list[pos]                  = (int)(addr);
        list[pos+1]                = instruction;

        // lower bound check
        //
        if ((int)addr             == memtype[section].lower)
        {
            min                    = pos;
        }
        else
        {
            min                        = 0;
            for (index = 3; index >= min; index-=3)
            {
                addr                   = addr - 1;
                immflag                = (*(addr) & 0x02000000) >> 25;
                if (immflag           == 1) // definitely cannot be an instruction
                {
                    list[index+2]      = *(addr);     // immediate value
                    addr               = addr - 1;
                    list[index]        = (int)(addr); // addr of instruction
                    list[index+1]      = *(addr);     // actual hex of instruction
                }
                else // could be an instruction
                {
                    addr               = addr - 1; // check the previous for immediate flag
                    immflag            = (*(addr) & 0x02000000) >> 25;
                    if (immflag       == 1)
                    {
                        addr           = addr - 1; // if so, check the one before that
                        immflag        = (*(addr) & 0x02000000) >> 25;
                        if (immflag   == 1)
                        {
                            addr       = addr + 2;
                        }
                        else
                        {
                            addr       = addr + 1;
                        }
                        list[index]    = (int)(addr); // addr of instruction
                        list[index+1]  = *(addr);     // actual hex of instruction
                        list[index+2]  = *(addr+1);   // immediate value
                    }        
                    else
                    {
                        addr           = addr + 1;
                        list[index]    = (int)(addr); // addr of instruction
                        list[index+1]  = *(addr);     // actual hex of instruction
                        list[index+2]  = 0;           // immediate value
                    }
                }

                // lower bound check
                //
                if ((int)addr         == memtype[section].lower)
                {
                    min                = index;
                    break;
                }
            }
        }

        y                          = 240;
        for (index = min; index < max; index++)
        {
            if (list[(index*3)+1] == instruction)
            {
                set_multiply_color (color_red);
            }
            else
            {
                set_multiply_color (color_white);
            }

            x                      = 49;           
            print_at (49, y, "0x");
            x                      = x    + 20;
            itoa2 (list[(index*3)], data, 16);
            print_at (x, y, data);
            x                      = x    + (strlen (data) * 10);
            print_at (x, y, ":");
            x                      = x    + 20;

            word                   = list[(index*3)+1];
            value                  = list[(index*3)+2];
            decode_instruction (word, y, value);
        
            y                      = y    + 20;
        }
    }

    print_at (579, 339, "[HALT]");

    // stop any sound
    stop_all_channels();
}


// ---------------------------------------------------------
//     MAIN FUNCTION
// ---------------------------------------------------------

void main( void )
{
    // very small wait before starting,
    // to ensure a black screen is seen
    clear_screen( color_black );
    sleep( 15 );
    
    // ------------------------------------
    // PART 1: DEFINE ALL TEXTURE REGIONS
    // ------------------------------------
    
    select_texture( -1 );
    
    // all characters of the text font
    define_region_matrix( first_region_font,  1,1,  10,20,  1,1,  32,8,  0 );
    
    // white pixel
    select_region( region_white_pixel );
    define_region_topleft( 315,169,  315,169 );
    
    // console
    select_region( region_console );
    define_region_topleft( 1,164,  199,299 );
    
    // cartridge
    select_region( region_cartridge );
    define_region_topleft( 203,164,  284,237 );
    
    // down arrow
    select_region( region_down_arrow );
    define_region_topleft( 288,164,  311,223 );
    
    // white square
    select_region( region_white_square );
    define_region_topleft( 315,164,  316,165 );
    
    // ------------------------------------
    // PART 7: JUMP TO CARTRIDGE
    // ------------------------------------
    
    // if no cartrige is connected, show an alert screen and stop
    if( !cartridge_connected() )
    {
        request_cartridge();
        asm{ "hlt" }
    }
    
    // ensure that any video parameters we might have used
    // are restored to their expected defaults at startup
    set_multiply_color( color_white );
    select_region( 0 );
    
    // jump to first position in cartridge program rom
    asm{ "jmp 0x20000000" }
}
