//
// debuggerBIOS.c - custom Vircon32 BIOS to provide an in-environment, interactive
//                  via the configured gamepad,  single-step debugger  and various
//                  other debugging goodies to aid in troubleshooting or exploring
//                  CARTs at the assembly/machine code level.
//
// The debuggerBIOS maintains persistent control over the runtime experience, in a
// manner where it carefully runs each CART instruction, one at a time,  emulating
// various instructions for finer control or to prevent jailbreaking.
//
// It provides a selection of resource views, allowing the user to see what is the
// current state of various system attributes (like registers, memory,  the stack,
// various IOPorts).
//
// It also features a (performance impacted) CONTINUATION mode,  which momentarily
// suspends the single-step mode while still retaining debugging control  (toggled
// via the START button), and an ESCAPE mode, which will exit debuggerBIOS (the  X
// button on the gamepage).
//
// Starts in single-step mode, waiting for confirmation on the first CART  offset-
// 0x20000000. Press DOWN to single-step, UP to cycle resource views.  LEFT/RIGHT,
// L/R can control content window adjustment in various views (see instructions at
// the top center of the debuggerBIOS screen).
//
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor: include indicated standard Vircon32 libraries
//
#include "audio.h"
#include "input.h"
#include "video.h"
#include "time.h"
#include "string.h"

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor: boolean
//
#define  TRUE                    1
#define  FALSE                   0

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor: opcode defines
//
#define  OPCODE_HLT              0x00
#define  OPCODE_WAIT             0x01
#define  OPCODE_JMP              0x02
#define  OPCODE_CALL             0x03
#define  OPCODE_RET              0x04
#define  OPCODE_JT               0x05
#define  OPCODE_JF               0x06
#define  OPCODE_IEQ              0x07
#define  OPCODE_INE              0x08
#define  OPCODE_IGT              0x09
#define  OPCODE_IGE              0x0A
#define  OPCODE_ILT              0x0B
#define  OPCODE_ILE              0x0C
#define  OPCODE_FEQ              0x0D
#define  OPCODE_FNE              0x0E
#define  OPCODE_FGT              0x0F
#define  OPCODE_FGE              0x10
#define  OPCODE_FLT              0x11
#define  OPCODE_FLE              0x12
#define  OPCODE_MOV              0x13
#define  OPCODE_LEA              0x14
#define  OPCODE_PUSH             0x15
#define  OPCODE_POP              0x16
#define  OPCODE_IN               0x17
#define  OPCODE_OUT              0x18
#define  OPCODE_MOVS             0x19
#define  OPCODE_SETS             0x1A
#define  OPCODE_CMPS             0x1B
#define  OPCODE_CIF              0x1C
#define  OPCODE_CFI              0x1D
#define  OPCODE_CIB              0x1E
#define  OPCODE_CFB              0x1F
#define  OPCODE_NOT              0x20
#define  OPCODE_AND              0x21
#define  OPCODE_OR               0x22
#define  OPCODE_XOR              0x23
#define  OPCODE_BNOT             0x24
#define  OPCODE_SHL              0x25
#define  OPCODE_IADD             0x26
#define  OPCODE_ISUB             0x27
#define  OPCODE_IMUL             0x28
#define  OPCODE_IDIV             0x29
#define  OPCODE_IMOD             0x2A
#define  OPCODE_ISGN             0x2B
#define  OPCODE_IMIN             0x2C
#define  OPCODE_IMAX             0x2D
#define  OPCODE_IABS             0x2E
#define  OPCODE_FADD             0x2F
#define  OPCODE_FSUB             0x30
#define  OPCODE_FMUL             0x31
#define  OPCODE_FDIV             0x32
#define  OPCODE_FMOD             0x33
#define  OPCODE_FSGN             0x34
#define  OPCODE_FMIN             0x35
#define  OPCODE_FMAX             0x36
#define  OPCODE_FABS             0x37
#define  OPCODE_FLR              0x38
#define  OPCODE_CEIL             0x39
#define  OPCODE_ROUND            0x3A
#define  OPCODE_SIN              0x3B
#define  OPCODE_ACOS             0x3C
#define  OPCODE_ATAN2            0x3D
#define  OPCODE_LOG              0x3E
#define  OPCODE_POW              0x3F

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor: IOPort aliases
//
#define  TIM_FRAMECOUNTER        0x002
#define  TIM_CYCLECOUNTER        0x003
#define  RNG_CURRENTVALUE        0x100
#define  GPU_COMMAND             0x200
#define  GPU_CLEAR               0x202
#define  GPU_MULTIPLY            0x203
#define  GPU_BLEND               0x204
#define  GPU_TEXTURE             0x205
#define  GPU_REGION              0x206
#define  GPU_DRAWX               0x207
#define  GPU_DRAWY               0x208
#define  GPU_SCALEX              0x209
#define  GPU_SCALEY              0x20A
#define  GPU_ANGLE               0x20B

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor: IOPort GPUCOMMAND aliases
//
#define  GPUCMD_CLEAR            0x10
#define  GPUCMD_DRAW             0x11
#define  GPUCMD_DRAWZOOM         0x12
#define  GPUCMD_DRAWROTO         0x13
#define  GPUCMD_DRAWROTOZOOM     0x14

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor: memory map aliases
//
#define  ADDR_CART_REGISTERS     0x003FFBA0
#define  ADDR_CUSTOM_ROUTINE     0x003FFFB0
#define  ADDR_CART_OFFSET        0x003FFFEE
#define  ADDR_CUSTOM_RETURN      0x003FFFEF
#define  ADDR_BIOS_REGISTERS     0x003FFFF0
#define  ADDR_PORT_TIMFRAME      0x003FFFDF
#define  ADDR_PORT_TIMCYCLE      0x003FFFE0
#define  ADDR_PORT_RNGVALUE      0x003FFFE1

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor: gamepad button press easy read symbols
//
#define  BUTTON_NOT_PRESSED      -1
#define  BUTTON_IS_PRESSED       1

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor: continue mode settings
//
#define  CONTINUE_NONE           0
#define  CONTINUE_ENTRIGGER      1
#define  CONTINUE_ENABLED        2
#define  CONTINUE_DETRIGGER      3

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor: debugger view modes
//
#define  MODE_NONE               0
#define  MODE_REG                1
#define  MODE_RAM                2
#define  MODE_STA                3
#define  MODE_BTR                4
#define  MODE_TIM                5
#define  MODE_RNG                6
#define  MODE_GPU                7
#define  MODE_SPU                8
#define  MODE_INP                9
#define  MODE_CAR                10
#define  MODE_MEM                11
#define  NUM_MODES               12

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor: data formats
//
#define  FORMAT_HEX              0
#define  FORMAT_INTEGER          1
#define  FORMAT_FLOAT            2
#define  NUM_FORMATS             3

////////////////////////////////////////////////////////////////////////////////////////
//
// BIOS-required regions; these
// may safely be used by programs
//
#define first_region_font        0
#define region_white_pixel       256

////////////////////////////////////////////////////////////////////////////////////////
//
// other non-required regions, used
// to draw the logo and error screens
//
#define region_logo_letters      300
#define region_logo_line         301
#define region_subtitle          302
#define region_console           303
#define region_gamepad           304
#define region_cartridge         305
#define region_memory_card       306
#define region_large_arrow       307
#define region_small_arrow       308
#define region_white_square      309
#define region_logo_v            310 // 1-58, 
#define region_logo_32           311 // 200+
#define region_divider_v         312
#define region_divider_h         313

////////////////////////////////////////////////////////////////////////////////////////
//
// an auxiliary region that will keep
// being redefined for logo animation
//
#define region_logo_temp         400

////////////////////////////////////////////////////////////////////////////////////////
//
// colors for error screens
//
#define error_colors_background  0xFF8D4130
#define error_colors_title       color_yellow
#define error_colors_message     color_white
#define error_colors_values      0xFF8080FF

////////////////////////////////////////////////////////////////////////////////////////
//
// hardware error codes
//
#define  ERROR_MEMORY_READ       0
#define  ERROR_MEMORY_WRITE      1
#define  ERROR_PORT_READ         2
#define  ERROR_PORT_WRITE        3
#define  ERROR_STACK_OVERFLOW    4
#define  ERROR_STACK_UNDERFLOW   5
#define  ERROR_DIVISION          6
#define  ERROR_ARC_COSINE        7
#define  ERROR_ARC_TANGENT_2     8
#define  ERROR_LOGARITHM         9
#define  ERROR_POWER             10
#define  ERROR_UNKNOWN           11

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor: debugger-specific resources
//
#define  DEBUG_GAMEPAD           0 // use this gamepad id for debuggerBIOS actions

////////////////////////////////////////////////////////////////////////////////////////
//
// Pre-processor: error codes
//
enum error_codes
{
    error_memory_read      = 0,
    error_memory_write,
    error_port_read,
    error_port_write,
    error_stack_overflow,
    error_stack_underflow,
    error_division,
    error_arc_cosine,
    error_arc_tangent_2,
    error_logarithm,
    error_power,
    error_unknown
};

////////////////////////////////////////////////////////////////////////////////////////
//
// error_message struct: storing the name and description of each error
//
struct error_message
{
    int [50]  title;
    int [150] description;
};

////////////////////////////////////////////////////////////////////////////////////////
//
// string_data: to simplify opcode display
//
struct string_data
{
    int [40] name;
    int      lower;
    int      upper;
};

////////////////////////////////////////////////////////////////////////////////////////
//
// opcode_t: The base unit of the array that stores the strings of each
// instruction opcode
//
struct opcode_t
{
    int [7] name;
};

////////////////////////////////////////////////////////////////////////////////////////
//
// function prototypes
//
void  draw_message_screen (int *title, int *msg);
void  decode              (int  x,     int  y,    int  instruction, int    immediate);
void  hexit_zoomed        (int  x,     int  y,    int  value,       float  factor);
void  hexit               (int  x,     int  y,    int  value);
void  portit              (int  x,     int  y,    int  value);
void  print_hex_value     (int  x,     int  y,    int *name,        int    value);
void  print_zoomed_at     (int  x,     int  y,    int *text,        float  factor);
void  init_regions        (void);
void  views               (int  mode,  int *addr, int *flags,       int   *backtrace);
bool  cartridge_connected ();
void  draw_logo           (int  mode);
void  request_cartridge   ();

////////////////////////////////////////////////////////////////////////////////////////
//
// main(): normal BIOS routine run on system startup
//
void main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare variables - note their position relative to BP
    //
    int             *code;        // [BP-1]: pointer to our dynamic code
    int             *offset;      // [BP-2]: address of instruction to process
    int              instruction; // [BP-3]: raw data of instruction
    int              immediate;   // [BP-4]: immediate value of instruction
    int              immflag;     // [BP-5]: immediate flag of instruction
    int              index;       // [BP-6]: index for loops and sequences
    int              y;
    int [8]          history;     // previous instructions to display
    int              count;       // tracking history array content quantity
    int              pos;         // another index variable
    int             *address;
    int             *memaddr;
    int              value;
    int              framestop;
    int              stepflag;
    int              modeflag;
    int              yflag;
    int              continueflag;
    int              exitflag;
    int              upflag;
    int              incflag;
    int              decflag;
    int              clearflag;
    int              emuflag;
    int              color;
    int              srcreg;
    int              dstreg;
    int              port;
    int            **mem;
    int [64]         backtrace;
    int              btrace;
    int [NUM_MODES]  vflag;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // init_regions(): Move  all general BIOS actions  (defining regions,
    // checking for cartridge, etc.) to its own subroutine, to facilitate
    // debugger debugging
    //
    init_regions ();

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // debuggerBIOS memory map:
    //
    // 0x003FFB9F base of cartridge stack (initial CART BP/SP)
    // 0x003FFBA0    (R0)  value from the context of the CART ROM
    // 0x003FFBA1    (R1)  value from the context of the CART ROM
    // 0x003FFBA2    (R2)  value from the context of the CART ROM
    // 0x003FFBA3    (R3)  value from the context of the CART ROM
    // 0x003FFBA4    (R4)  value from the context of the CART ROM
    // 0x003FFBA5    (R5)  value from the context of the CART ROM
    // 0x003FFBA6    (R6)  value from the context of the CART ROM
    // 0x003FFBA7    (R7)  value from the context of the CART ROM
    // 0x003FFBA8    (R8)  value from the context of the CART ROM
    // 0x003FFBA9    (R9)  value from the context of the CART ROM
    // 0x003FFBAA    (R10) value from the context of the CART ROM
    // 0x003FFBAB CR (R11) value from the context of the CART ROM
    // 0x003FFBAC SR (R12) value from the context of the CART ROM
    // 0x003FFBAD DR (R13) value from the context of the CART ROM
    // 0x003FFBAE BP (R14) value from the context of the CART ROM
    // 0x003FFBAF SP (R15) value from the context of the CART ROM
    // 0x003FFBB0 top of debugger stack (1023 total words)
    //   . . .
    // 0x003FFFAF base of debugger/BIOS stack
    // 0x003FFFB0 start of dynamic subroutine (46 total words)
    //   . . .
    // 0x003FFFDE end of dynamic subroutine
    // 0x003FFFDF CART TIM_FrameCounter value
    // 0x003FFFE0 CART TIM_CycleCounter value
    // 0x003FFFE1 CART RNG_CurrentValue value
    // 0x003FFFE2 CART GPUCommand value
    // 0x003FFFE3 CART GPU_ClearColor value
    // 0x003FFFE4 CART GPU_MultiplyColor value
    // 0x003FFFE5 CART GPU_ActiveBlending value
    // 0x003FFFE6 CART texture id
    // 0x003FFFE7 CART region id
    // 0x003FFFE8 CART GPU_DrawingPointX
    // 0x003FFFE9 CART GPU_DrawingPointY
    // 0x003FFFEA CART scaleX
    // 0x003FFFEB CART scaleY
    // 0x003FFFEC CART angle
    // 0x003FFFED CART gamepad id
    // 0x003FFFEE offset of current CART instruction
    // 0x003FFFEF address of where our jumped-to routine will "return"
    // 0x003FFFF0    (R0)  value from the context of the BIOS ROM
    // 0x003FFFF1    (R1)  value from the context of the BIOS ROM
    // 0x003FFFF2    (R2)  value from the context of the BIOS ROM
    // 0x003FFFF3    (R3)  value from the context of the BIOS ROM
    // 0x003FFFF4    (R4)  value from the context of the BIOS ROM
    // 0x003FFFF5    (R5)  value from the context of the BIOS ROM
    // 0x003FFFF6    (R6)  value from the context of the BIOS ROM
    // 0x003FFFF7    (R7)  value from the context of the BIOS ROM
    // 0x003FFFF8    (R8)  value from the context of the BIOS ROM
    // 0x003FFFF9    (R9)  value from the context of the BIOS ROM
    // 0x003FFFFA    (R10) value from the context of the BIOS ROM
    // 0x003FFFFB CR (R11) value from the context of the BIOS ROM
    // 0x003FFFFC SR (R12) value from the context of the BIOS ROM
    // 0x003FFFFD DR (R13) value from the context of the BIOS ROM
    // 0x003FFFFE BP (R14) value from the context of the BIOS ROM
    // 0x003FFFFF SP (R15) value from the context of the BIOS ROM
    //
    // This will allow the debugger  to maintain important data, separate
    // whatever the  CART ROM ends up  doing (provided it plays  nice and
    // just uses BP/SP as presented).
    //
    // We should be able  to scale this as needed, but  the aim should be
    // to allocate  as little memory  as possible, to reduce  issues with
    // the CART ROM, which will have no idea what is going on.
    //
    // As heavier functions like decode() add close to 500 words onto the
    // stack, so some further memory map adjustments had to be done. BIOS
    // stack was  upgraded from 160 words  to just shy of  1024 words (at
    // 1023 words). This hopefully will be more than enough.
    //
    ////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Set up desired stack configuration  - we want nothing initially on
    // the stack, so we'll discard that return address.
    //
    // Since the point  is to never return from main(),  before any local
    // variables are declared,  let us do some  rearranging to facilitate
    // our operations here, in accordance with the memory map above:
    //
    // Process: determine the  difference between the old BP  and our new
    // one; then just subtract that difference from the SP (which will be
    // at the  correct value  based on variables  declared), so  it'll be
    // adjusted into the  new stack space at the  appropriate offset from
    // BP,  eliminating any  future issues  when declaring  (or removing)
    // variables at the start of main().
    //
    asm
    {
        "PUSH R10"                       // back up R10 (arbitrary register)
        "MOV  R10,          R14"         // copy base pointer into R10
        "MOV  R14,          0x003FFFAF"  // new stack base
        "MOV  [0x003FFFFE], R14"         // back up debug/BIOS BP
        "ISUB R10,          R14"         // subtract new BP from old BP
        "ISUB R15,          R10"         // adjust SP to new offset
        "MOV  [0x003FFFFF], R15"         // back up debug/BIOS SP
        "MOV  R10,          0x003FFB9F"  // CART initial BP
        "MOV  [0x003FFBAE], R10"         // store initial CART BP
        "MOV  R10,          0x003FFB9F"  // CART initial SP (offset for variables)
        "MOV  [0x003FFBAF], R10"         // store initial CART SP
        "POP  R10"                       // restore R10
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // initialize CART port values
    //
    asm
    {
        "PUSH  R0"
        "IN    R0,           GPU_ClearColor"
        "MOV   [0x003FFFE3], R0"
        "IN    R0,           GPU_MultiplyColor"
        "MOV   [0x003FFFE4], R0"
        "IN    R0,           GPU_ActiveBlending"
        "MOV   [0x003FFFE5], R0"
        "IN    R0,           GPU_SelectedTexture"
        "MOV   [0x003FFFE6], R0"
        "IN    R0,           GPU_SelectedRegion"
        "MOV   [0x003FFFE7], R0"
        "IN    R0,           GPU_DrawingPointX"
        "MOV   [0x003FFFE8], R0"
        "IN    R0,           GPU_DrawingPointY"
        "MOV   [0x003FFFE9], R0"
        "IN    R0,           GPU_DrawingScaleX"
        "MOV   [0x003FFFEA], R0"
        "IN    R0,           GPU_DrawingScaleY"
        "MOV   [0x003FFFEB], R0"
        "IN    R0,           GPU_DrawingAngle"
        "MOV   [0x003FFFEC], R0"
        "POP   R0"
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // DEBUGGER: instead of directly passing control off to the CART ROM,
    // we will retain  control here in the BIOS,  providing the debugging
    // interface, allowing for finer instruction-by-instruction analysis.
    //
    ////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // We will need a variable, an  integer pointer (offset) to track our
    // current position in  CART ROM execution (our  program data). Think
    // of it like our own program counter.
    //
    // ... in an earlier commit, this was done in assembly like so:
    //
    // asm
    // {
    //     "mov   R0,       0x20000000"
    //     "mov   {offset}, R0"
    // }
    //
    offset                               = (int *) 0x20000000; // first CART word

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // debugging  loop.  This  is  an   infinite  while  loop  that  will
    // continually take us from instruction to instruction.
    //
    count                                = 0;
    modeflag                             = MODE_NONE; // no content view by default
    vflag[MODE_RAM]                      = ADDR_BIOS_REGISTERS;
    vflag[MODE_REG]                      = FORMAT_HEX;
    vflag[MODE_STA]                      = 9;
    vflag[MODE_MEM]                      = 0x30000000;
    exitflag                             = FALSE;
    continueflag                         = CONTINUE_NONE;
    clearflag                            = FALSE;
    emuflag                              = FALSE;
    for (index                           = 0;
         index                          <  64;
         index                           = index + 1)
    {
        backtrace[index]                 = -1;
    }
    btrace                               = 0;
    vflag[MODE_BTR]                      = 0;

    while (1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // For error_handler() enhancement:  back up the next CART offset
        // to be processed.  In the event of an  error, this value can be
        // be read and used to display CART-context instructions
        //
        // 0x003FFFEE offset of current CART instruction
        //
        // This  was  originally done  in  ASM,  but  then redone  in  C.
        // Provided here  is that original  inline ASM (after  setting up
        // code to store the address of the next instruction to execute):
        //
        // asm
        // {
        //     "push  R0"
        //     "mov   R0,           {code}" // doing an implied dereference?
        //     "mov   [0x003FFFEE], R0"
        //     "pop   R0"
        // }
        //
        instruction                      = *offset;
        immflag                          = instruction & 0x02000000;
        code                             = (int *) ADDR_CART_OFFSET;
        *code                            = (int) offset + 1;
        if (immflag                     >  0)
        {
            *code                        = (int) offset + 2;
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // continue  mode view  refresh: only  render once  the CART  has
        // issued  a  clearing  of  the  screen  (via  `out  GPU_Command,
        // GPUCommand_ClearScreen`)
        //
        // Attempted performance tweak:  only traipse through the views() 
        // function if a view is currently selected
        //
        if ((modeflag                   != MODE_NONE)        &&
            (continueflag               == CONTINUE_ENABLED) &&
            (clearflag                  == TRUE))
        {
            views (modeflag, offset, vflag, backtrace);
            clearflag                    = FALSE;
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // START: remain  in debugger,  but continue normal  execution of
        // CART instructions (occurs on release after press)
        //
        value                            = gamepad_button_start ();
        if ((value                      >= BUTTON_IS_PRESSED) &&
            (continueflag               == CONTINUE_ENABLED))
        {
            continueflag                 = CONTINUE_DETRIGGER;
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // START: recognize key release  after being pressed (the setting
        // of continueflag to 2 allows framestop to continually be set to
        // 0, prevently a re-entry of  the single-step prompt). Note that
        // with  this, we  are still  in the  debugging monitor,  and can
        // break back to the single-step prompt by pressing START again.
        //
        // Revert back to previously establish debugging mode.
        //
        else if ((value                 <= BUTTON_NOT_PRESSED) &&
                 (continueflag          == CONTINUE_DETRIGGER))
        {
            continueflag                 = CONTINUE_NONE;
            framestop                    = -1;
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // continue mode: prevent single-step interaction
        //
        if (continueflag                == CONTINUE_ENABLED)
        {
            framestop                    = 0;
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // single step: debugger interactive interface
        //
        else
        {
            framestop                    = -1;
            stepflag                     = FALSE;
            upflag                       = FALSE;
            yflag                        = FALSE;
            incflag                      = FALSE;
            decflag                      = FALSE;
            exitflag                     = FALSE;
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // update the history array, cycling out the old, bringing in the
        // new as needed
        //
        if (count                       == 8) // buffer the previous 7 instructions,
        {                                     // cycling off the ones as needed
            for (index                   = 1;
                 index                  <  8;
                 index                   = index + 1)
            {
                history[index-1]         = history[index]; // oldest one goes away
            }
            count                        = count - 1; // allow new instruction
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // obtain the next instruction from our CART offset
        //
        history[count]                   = (int) offset;
        count                            = count + 1;

        ////////////////////////////////////////////////////////////////////////////////
        //
        // single-step loop
        //
        while (framestop                != 0) // single step loop
        {
            ////////////////////////////////////////////////////////////////////////////
            //
            // draw "debuggerBIOS" logo in top left, with instructions
            //
            draw_logo (modeflag);

            ////////////////////////////////////////////////////////////////////////////
            //
            // display   the   instruction,  highlighting   the   current
            // one  yellow;   past  instructions   are  displayed   in  a
            // fading-from-white gradient
            //
            y                            = 50;
            for (index                   = 0;
                 index                  <  count;
                 index                   = index + 1)
            {
                ////////////////////////////////////////////////////////////////////////
                //
                // obtain address and dereference the instruction that is
                // to be decoded and displayed
                //
                address                  = (int *) history[index];
                instruction              = *address;

                ////////////////////////////////////////////////////////////////////////
                //
                // as some instructions may  have immediate data, we need
                // to check  if the  current instruction  has it,  and to
                // obtain  it if  so (if  not, set  'immediate' to  0 and
                // otherwise ignore it).
                //
                // We do this by masking  out all bits in the instruction
                // save for the immediate flag. If the resulting value is
                // greater than 0,  that bit is set, that  means there is
                // immediate data.
                //
                // This is what  we came up with initially  in class, but
                // then I later  realized we can do this in  C, as we did
                // above for instruction:
                //
                // asm
                // {
                //    "mov   R0,          {offset}"
                //    "mov   R1,          [R0]"
                //    "mov   {immediate}, R1"
                // }
                //
                immflag                  = instruction & 0x02000000;
                if (immflag             >  0)                         // immediate bit
                {
                    immediate            = *(address+1);              // deref offset
                }

                else
                {
                    immediate            = 0;                         // no immediate
                }

                if (index               == (count - 1))
                {
                    set_multiply_color (color_yellow);
                }

                else
                {
                    ////////////////////////////////////////////////////////////////////
                    //
                    // calculate white  fade to black: as  we are dealing
                    // with raw binary  data store on the  machine, it is
                    // encoded in the machine's  little endian format, so
                    // the word  representing the RGBA value  is actually
                    // of the form ABGR (note the shifts below)
                    //
                    value                = 0x3F + (8 * index);
                    color                = (((value + (index * 24))));       // RED
                    color               |= (((value + (index * 24))) << 8);  // GREEN
                    color               |= (((value + (index * 24))) << 16); // BLUE
                    color               |= (((0xFF))                 << 24); // ALPHA
                    set_multiply_color (color);
                }

                ////////////////////////////////////////////////////////////////////////
                //
                // display the instruction offset and hex
                //
                hexit_zoomed (0,  y, (int) address, 0.75); // instruction addr
                hexit_zoomed (88, y, instruction,   0.75); // instruction hex

                ////////////////////////////////////////////////////////////////////////
                //
                // if there is immediate data, display that on the next line
                //
                if (immflag             >  0)
                {
                    address              = address + 1;
                    hexit_zoomed (0,  (y + 18), (int) address, 0.75);
                    hexit_zoomed (88, (y + 18), immediate,     0.75);
                }

                decode (176, y, instruction, immediate);
                if (index               == (count - 1))
                {
                    set_multiply_color (color_white);
                }

                y                        = y + 18;
                if (immflag             >  0)
                {
                    y                    = y + 18;
                }
            }

            ////////////////////////////////////////////////////////////////////////////
            //
            // resource view logic
            //
            views (modeflag, offset, vflag, backtrace);

            ////////////////////////////////////////////////////////////////////////////
            //
            // UP: cycle content display
            //
            value                        = gamepad_up ();
            if ((value                  >= BUTTON_IS_PRESSED) &&
                (upflag                 == FALSE))
            {
                modeflag                 = (modeflag + 1) % NUM_MODES;
                upflag                   = TRUE;
            }

            ////////////////////////////////////////////////////////////////////////////
            //
            // UP: recognize key release after being pressed
            //
            else if ((value             <= BUTTON_NOT_PRESSED) &&
                (upflag                 == TRUE))
            {
                upflag                   = FALSE;
            }

            ////////////////////////////////////////////////////////////////////////////
            //
            // LEFT: decrement content by 16
            //
            value                        = gamepad_left ();
            if ((value                  >= BUTTON_IS_PRESSED) &&
                (decflag                == FALSE))
            {
                decflag                  = TRUE;
                if (modeflag            == MODE_RAM)
                {
                    vflag[MODE_RAM]         = vflag[MODE_RAM] - 16;
                    if (vflag[MODE_RAM] <  0x00000000)
                    {
                        vflag[MODE_RAM]  = ADDR_BIOS_REGISTERS;
                    }
                }

                else if (modeflag       == MODE_REG)
                {
                    vflag[MODE_REG]      = vflag[MODE_REG] - 1;
                    if (vflag[MODE_REG] <  0)
                    {
                        vflag[MODE_REG]  = NUM_FORMATS - 1;
                    }
                }

                else if (modeflag       == MODE_STA)
                {
                    vflag[MODE_STA]      = vflag[MODE_STA] - 1;
                    if (vflag[MODE_STA] <  1)
                    {
                        vflag[MODE_STA]  = 1;
                    }
                }

                else if (modeflag       == MODE_BTR)
                {
                    vflag[MODE_BTR]      = vflag[MODE_BTR] - 16;
                    if (vflag[MODE_BTR] <  0)
                    {
                        vflag[MODE_BTR]  = 48;
                    }
                }

                else if (modeflag       == MODE_INP)
                {
                    vflag[MODE_INP]      = (vflag[MODE_INP] - 1) % 4;
                    if (vflag[MODE_INP] <  0)
                    {
                        vflag[MODE_INP]  = 3;
                    }
                }

                else if (modeflag       == MODE_MEM)
                {
                    vflag[MODE_MEM]      = vflag[MODE_MEM] - 16;
                    if (vflag[MODE_MEM] <  0x30000000)
                    {
                        vflag[MODE_MEM]  = 0x3003FFF0;
                    }
                }

                else if (modeflag       == MODE_RNG)
                {
                    memaddr              = (int *) ADDR_PORT_RNGVALUE;
                    *memaddr             = *memaddr - 1;
                }
            }

            ////////////////////////////////////////////////////////////////////////////
            //
            // LEFT: recognize key release after being pressed
            //
            else if ((value             <= BUTTON_NOT_PRESSED) &&
                (decflag                == TRUE))
            {
                decflag                  = FALSE;
            }

            ////////////////////////////////////////////////////////////////////////////
            //
            // L: decrement content by 256
            //
            value                        = gamepad_button_l ();
            if ((value                  >= BUTTON_IS_PRESSED) &&
                (decflag                == FALSE))
            {
                decflag                  = 2;
                if (modeflag            == MODE_RAM)
                {
                    vflag[MODE_RAM]      = vflag[MODE_RAM] - 256;
                    if (vflag[MODE_RAM] <  0x00000000)
                    {
                        vflag[MODE_RAM]  = 0x003FFF00;
                    }
                }

                else if (modeflag       == MODE_REG)
                {
                    vflag[MODE_REG]      = FORMAT_HEX;
                }

                else if (modeflag       == MODE_STA)
                {
                    vflag[MODE_STA]      = vflag[MODE_STA] - 3;
                    if (vflag[MODE_STA] <  1)
                    {
                        vflag[MODE_STA]  = 1;
                    }
                }

                else if (modeflag       == MODE_BTR)
                {
                    vflag[MODE_BTR]      = 0;
                }

                else if (modeflag       == MODE_INP)
                {
                    vflag[MODE_INP]      = 0;
                }

                else if (modeflag       == MODE_MEM)
                {
                    vflag[MODE_MEM]      = vflag[MODE_MEM] - 256;
                    if (vflag[MODE_MEM] <  0x30000000)
                    {
                        vflag[MODE_MEM]  = 0x3003FF00;
                    }
                }

                else if (modeflag       == MODE_RNG)
                {
                    memaddr              = (int *) ADDR_PORT_RNGVALUE;
                    *memaddr             = *memaddr - 100;
                }
            }

            ////////////////////////////////////////////////////////////////////////////
            //
            // L: recognize key release after being pressed
            //
            else if ((value             <= BUTTON_NOT_PRESSED) &&
                (decflag                == 2))
            {
                decflag                  = FALSE;
            }

            ////////////////////////////////////////////////////////////////////////////
            //
            // RIGHT: increment content by 16
            //
            value                        = gamepad_right ();
            if ((value                  >= BUTTON_IS_PRESSED) &&
                (incflag                == FALSE))
            {
                incflag                  = 2;
                if (modeflag            == MODE_RAM)
                {
                    vflag[MODE_RAM]      = vflag[MODE_RAM] + 16;
                    if (vflag[MODE_RAM] >  ADDR_BIOS_REGISTERS)
                    {
                        vflag[MODE_RAM]  = 0x00000000;
                    }
                }

                else if (modeflag       == MODE_REG)
                {
                    vflag[MODE_REG]      = (vflag[MODE_REG] + 1) % NUM_FORMATS;
                }

                else if (modeflag       == MODE_STA)
                {
                    vflag[MODE_STA]      = vflag[MODE_STA] + 1;
                    if (vflag[MODE_STA] >  18)
                    {
                        vflag[MODE_STA]  = 18;
                    }
                }

                else if (modeflag       == MODE_BTR)
                {
                    vflag[MODE_BTR]      = vflag[MODE_BTR]  + 16;
                    if (vflag[MODE_BTR] >  63)
                    {
                        vflag[MODE_BTR]  = 0;
                    }
                }

                else if (modeflag       == MODE_INP)
                {
                    vflag[MODE_INP]      = (vflag[MODE_INP] + 1) % 4;
                }

                else if (modeflag       == MODE_MEM)
                {
                    vflag[MODE_MEM]      = vflag[MODE_MEM] + 16;
                    if (vflag[MODE_MEM] >  0x3003FFFF)
                    {
                        vflag[MODE_MEM]  = 0x30000000;
                    }
                }

                else if (modeflag       == MODE_RNG)
                {
                    memaddr              = (int *) ADDR_PORT_RNGVALUE;
                    *memaddr             = *memaddr + 1;
                }
            }

            ////////////////////////////////////////////////////////////////////////////
            //
            // RIGHT: recognize key release after being pressed
            //
            else if ((value             <= BUTTON_NOT_PRESSED) &&
                (incflag                == 2))
            {
                incflag                  = FALSE;
            }

            ////////////////////////////////////////////////////////////////////////////
            //
            // R: increment content by 256
            //
            value                        = gamepad_button_r ();
            if ((value                  >= BUTTON_IS_PRESSED) &&
                (incflag                == FALSE))
            {
                incflag                  = TRUE;
                if (modeflag            == MODE_RAM)
                {
                    vflag[MODE_RAM]      = vflag[MODE_RAM] + 256;
                    if (vflag[MODE_RAM] >  0x003FFF00)
                    {
                        vflag[MODE_RAM]  = 0x00000000;
                    }
                }

                else if (modeflag       == MODE_REG)
                {
                    vflag[MODE_REG]      = NUM_FORMATS - 1;
                }

                else if (modeflag       == MODE_STA)
                {
                    vflag[MODE_STA]      = vflag[MODE_STA] + 3;
                    if (vflag[MODE_STA] >  18)
                    {
                        vflag[MODE_STA]  = 18;
                    }
                }

                else if (modeflag       == MODE_BTR)
                {
                    vflag[MODE_BTR]      = 48;
                }

                else if (modeflag       == MODE_INP)
                {
                    vflag[MODE_INP]      = 3;
                }

                else if (modeflag       == MODE_MEM)
                {
                    vflag[MODE_MEM]      = vflag[MODE_MEM] + 256;
                    if (vflag[MODE_MEM] >  0x3003FF00)
                    {
                        vflag[MODE_MEM]  = 0x30000000;
                    }
                }

                else if (modeflag       == MODE_RNG)
                {
                    address              = (int *) ADDR_PORT_RNGVALUE;
                    *address             = *address + 100;
                }
            }

            ////////////////////////////////////////////////////////////////////////////
            //
            // R: recognize key release after being pressed
            //
            else if ((value             <= BUTTON_NOT_PRESSED) &&
                (incflag                == TRUE))
            {
                incflag                  = FALSE;
            }

            ////////////////////////////////////////////////////////////////////////////
            //
            // DOWN: perform single step execution of current instruction
            //
            value                        = gamepad_down ();
            if (value                   >= BUTTON_IS_PRESSED)
            {
                stepflag                 = TRUE;
            }

            ////////////////////////////////////////////////////////////////////////////
            //
            // DOWN: recognize key release after being pressed (framestop
            // is  what  gets   us  out  of  the  loop   to  execute  the
            // instruction).
            //
            else if ((value             <= BUTTON_NOT_PRESSED) &&
                     (stepflag          == TRUE))
            {
                framestop                = 0; // actually perform single step
            }                                 // (by releasing down once pressed)

            ////////////////////////////////////////////////////////////////////////////
            //
            // START: remain  in debugger, but continue  normal execution
            // of CART instructions (occurs on release after press)
            //
            value                        = gamepad_button_start ();
            if ((value                  >= BUTTON_IS_PRESSED) &&
                (continueflag           == CONTINUE_NONE))
            {
                continueflag             = CONTINUE_ENTRIGGER;
            }

            ////////////////////////////////////////////////////////////////////////////
            //
            // START:  recognize key  release  after  being pressed  (the
            // setting  of   continueflag  to   2  allows   framestop  to
            // continually  be set  to  0, prevently  a  re-entry of  the
            // single-step  prompt). Note  that with  this, we  are still
            // in  the  debugging monitor,  and  can  break back  to  the
            // single-step prompt by pressing START again.
            //
            else if ((value             <= BUTTON_NOT_PRESSED) &&
                     (continueflag      == CONTINUE_ENTRIGGER))
            {
                continueflag             = CONTINUE_ENABLED;
                framestop                = 0;
            }

            ////////////////////////////////////////////////////////////////////////////
            //
            // X:  exit from  the debugger,  resuming normal  unmonitored
            // execution of instructions (occurs on release after press)
            //
            value                        = gamepad_button_x ();
            if ((value                  >= BUTTON_IS_PRESSED) &&
                (exitflag               == FALSE))
            {
                exitflag                 = TRUE;
            }

            ////////////////////////////////////////////////////////////////////////////
            //
            // X: recognize key release  after being pressed (the jumping
            // to offset  will break us  out of the  debugger environment
            // for the remainder of the session).
            //
            else if ((value             <= BUTTON_NOT_PRESSED) &&
                     (exitflag          == TRUE))
            {
                ////////////////////////////////////////////////////////////////////////
                //
                // Since  we are  escaping the  debugger, set  our stored
                // offset value  to some unique, impossible  value so any
                // error_handler()  call to  service system  errors won't
                // rewrite the value of the provided InstructionPointer:
                //
                code                     = (int *) ADDR_CART_OFFSET;
                *code                    = 0xDEADBEEF;         // why not?

                ////////////////////////////////////////////////////////////////////////
                //
                // generate ideal custom subroutine  to handle the escape
                // from the BIOS/debugger:
                //
                index                    = 0;
                code                     = (int *) ADDR_CUSTOM_ROUTINE;
                *(code+index++)          = 0x0A000000;         // JMP to immediate
                *(code+index++)          = (int) offset;       // immediate value
                *(code+index++)          = 0x00000000;         // HLT for safety

                ////////////////////////////////////////////////////////////////////////
                //
                // switch to CART context; no need to back up BIOS, since
                // the debugger is being exit
                //
                asm
                {
                    /*
                    "MOV R0,                  [0x003FFFE3]"
                    "OUT GPU_ClearColor,      R0"
                    "MOV R0,                  [0x003FFFE4]"
                    "OUT GPU_MultiplyColor,   R0"
                    "MOV R0,                  [0x003FFFE5]"
                    "OUT GPU_ActiveBlending,  R0"
                    "MOV R0,                  [0x003FFFE6]"
                    "OUT GPU_SelectedTexture, R0"
                    "MOV R0,                  [0x003FFFE7]"
                    "OUT GPU_SelectedRegion,  R0"
                    "MOV R0,                  [0x003FFFE8]"
                    "OUT GPU_DrawingPointX,   R0"
                    "MOV R0,                  [0x003FFFE9]"
                    "OUT GPU_DrawingPointY,   R0"
                    "MOV R0,                  [0x003FFFEA]"
                    "OUT GPU_DrawingScaleX,   R0"
                    "MOV R0,                  [0x003FFFEB]"
                    "OUT GPU_DrawingScaleY,   R0"
                    "MOV R0,                  [0x003FFFEC]"
                    "OUT GPU_DrawingAngle,    R0"
                    "MOV R0,                  [0x003FFFED]" */
                    "OUT INP_SelectedGamepad, R0"
                    "MOV R0,                  [0x003FFBA0]" // restore CART register
                    "MOV R1,                  [0x003FFBA1]" // restore CART register
                    "MOV R2,                  [0x003FFBA2]" // restore CART register
                    "MOV R3,                  [0x003FFBA3]" // restore CART register
                    "MOV R4,                  [0x003FFBA4]" // restore CART register
                    "MOV R5,                  [0x003FFBA5]" // restore CART register
                    "MOV R6,                  [0x003FFBA6]" // restore CART register
                    "MOV R7,                  [0x003FFBA7]" // restore CART register
                    "MOV R8,                  [0x003FFBA8]" // restore CART register
                    "MOV R9,                  [0x003FFBA9]" // restore CART register
                    "MOV R10,                 [0x003FFBAA]" // restore CART register
                    "MOV R11,                 [0x003FFBAB]" // restore CART register
                    "MOV R12,                 [0x003FFBAC]" // restore CART register
                    "MOV R13,                 [0x003FFBAD]" // restore CART register
                    "MOV R14,                 [0x003FFBAE]" // restore CART stack BP
                    "MOV R15,                 [0x003FFBAF]" // restore CART stack SP
                    "JMP 0x003FFFB0"                        // jump to custom routine
                }
            }

            end_frame ();
        } // end of single step loop

        ////////////////////////////////////////////////////////////////////////////////
        //
        // refresh instruction component variables
        //
        instruction                      = *offset;
        immflag                          = instruction  & 0x02000000;
        dstreg                           = (instruction & 0x01E00000) >> 21;
        srcreg                           = (instruction & 0x001E0000) >> 17;
        port                             = instruction  & 0x00003FFF;
        if (immflag                     >  0)
        {
            immediate                    = *(offset+1);
        }
        else
        {
            immediate                    = 0;
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // SANDBOXING:  to  preserve  debugger  monitoring  control,  any
        // branch instruction must be  intercepted and emulated. They are
        // never run in the custom routine, as branching would escape the
        // BIOS.
        //
        emuflag                          = FALSE;
        switch ((instruction & 0xFC000000) >> 26)
        {
            ////////////////////////////////////////////////////////////////////////////
            //
            // implement JMP emulation
            //
            case OPCODE_JMP:
                if (immflag             >  0)                 // if immediate bit is set
                {
                    offset               = (int *) immediate; // addr of first CART word
                }
                else
                {
                    pos                  = (instruction & 0x01E00000) >> 21;
                    code                 = (int *) (ADDR_CART_REGISTERS + pos);
                    offset               = (int *) *code;
                }

                ////////////////////////////////////////////////////////////////////////
                //
                // update CART cyclecounter
                //
                memaddr                  = (int *) ADDR_PORT_TIMCYCLE;
                *memaddr                 = *memaddr + 1;
                emuflag                  = TRUE;

                ////////////////////////////////////////////////////////////////////////
                //
                // instruction processing done: proceed to next instruction
                //
                continue;

            ////////////////////////////////////////////////////////////////////////////
            //
            // implement CALL  emulation: among the more  detailed of the
            // branch instructions  to emulate; since it  PUSHes onto the
            // stack, THAT  functionality also needs to  be performed, in
            // lieu of actually executing the native instruction
            //
            // Take note of the exceptional pointer scheme utilized
            //
            case OPCODE_CALL:

                ////////////////////////////////////////////////////////////////////////
                //
                // CART SP, stored in RAM
                //
                code                     = (int *) (ADDR_CART_REGISTERS + 15);
                *code                    = *code - 1; // CART SP = CART SP - 1 (push)

                ////////////////////////////////////////////////////////////////////////
                //
                // The trickiest,  most indirect part: to  accomplish the
                // PUSH, the address  needs to be placed  onto the stack-
                // but specifically the CART memory backup of SP.
                //
                mem                      = (int **) &(*code);
                **mem                    = (int) offset; // **mem is actual data

                if (immflag             >  0)
                {
                    offset               = (int *) immediate; // addr of CART word
                }
                else
                {
                    pos                  = (instruction & 0x01E00000) >> 21;
                    code                 = (int *) (ADDR_CART_REGISTERS + pos);
                    offset               = (int *) *code;
                }
                backtrace[btrace]        = (int) offset;
                btrace                   = btrace + 1;

                ////////////////////////////////////////////////////////////////////////
                //
                // update CART cyclecounter
                //
                memaddr                  = (int *) ADDR_PORT_TIMCYCLE;
                *memaddr                 = *memaddr + 1;
                emuflag                  = TRUE;

                ////////////////////////////////////////////////////////////////////////
                //
                // instruction processing done: proceed to next instruction
                //
                continue;

            ////////////////////////////////////////////////////////////////////////////
            //
            // implement RET  emulation: among  the more detailed  of the
            // branch instructions  to emulate.  Like CALL, which  has to
            // perform a  stack operation (PUSH),  here a POP is  what is
            // needing to be done.
            //
            case OPCODE_RET:

                ////////////////////////////////////////////////////////////////////////
                //
                // CART SP, stored in RAM
                //
                btrace                   = btrace - 1;
                backtrace[btrace]        = -1;
                code                     = (int *) (ADDR_CART_REGISTERS + 15);
                mem                      = (int **) &(*code);
                offset                   = (int *) **mem;
                *code                    = *code + 1; // CART SP = CART SP + 1 (pop)
                immflag                  = (*offset) & 0x02000000;
                offset                   = offset + 1;
                if (immflag             >  0)
                {
                    offset               = offset + 1;
                }

                ////////////////////////////////////////////////////////////////////////
                //
                // update CART cyclecounter
                //
                memaddr                  = (int *) ADDR_PORT_TIMCYCLE;
                *memaddr                 = *memaddr + 1;
                emuflag                  = TRUE;

                ////////////////////////////////////////////////////////////////////////
                //
                // instruction processing done: proceed to next instruction
                //
                continue;

            case OPCODE_JT:
                emuflag                  = TRUE;
                code                     = (int *) (ADDR_CART_REGISTERS + dstreg);
                if (*code               == FALSE) // false
                {
                    break;
                }
                else // true (we're jumping)
                {
                    if (immflag         >  0)
                    {
                        offset           = (int *) immediate;
                    }
                    else
                    {
                        code             = (int *) (ADDR_CART_REGISTERS + srcreg);
                        offset           = (int *) *code;
                    }
                }

                ////////////////////////////////////////////////////////////////////////
                //
                // update CART cyclecounter
                //
                memaddr                  = (int *) ADDR_PORT_TIMCYCLE;
                *memaddr                 = *memaddr + 1;

                ////////////////////////////////////////////////////////////////////////
                //
                // instruction processing done: proceed to next instruction
                //
                continue;

            case OPCODE_JF:
                emuflag                  = TRUE;
                code                     = (int *) (ADDR_CART_REGISTERS + dstreg);
                if (*code               != FALSE) // true (we're not jumping)
                {
                    break;
                }
                else // false (we're jumping)
                {
                    if (immflag         >  0)
                    {
                        offset           = (int *) immediate;
                    }
                    else
                    {
                        code             = (int *) (ADDR_CART_REGISTERS + srcreg);
                        offset           = (int *) *code;
                    }
                }

                ////////////////////////////////////////////////////////////////////////
                //
                // update CART cyclecounter
                //
                memaddr                  = (int *) ADDR_PORT_TIMCYCLE;
                *memaddr                 = *memaddr + 1;

                ////////////////////////////////////////////////////////////////////////
                //
                // instruction processing done: proceed to next instruction
                //
                continue;

            ////////////////////////////////////////////////////////////////////////////
            //
            // WAIT: in general, the expectation is after a WAIT there is
            // a decent chance of a clear screen and then various  redraw
            // events, so if we look out for a WAIT, we can set a flag to
            // use with tracking drawing events
            //
            case OPCODE_WAIT:

                ////////////////////////////////////////////////////////////////////////
                //
                // increment CART framecounter
                //
                memaddr                  = (int *) ADDR_PORT_TIMFRAME;
                *memaddr                 = *memaddr + 1;

                ////////////////////////////////////////////////////////////////////////
                //
                // reset CART cyclecounter
                //
                memaddr                  = (int *) ADDR_PORT_TIMCYCLE;
                *memaddr                 = 0;

                emuflag                  = FALSE;
                break;

            ////////////////////////////////////////////////////////////////////////////
            //
            // IN: be on  the lookout for RNG port reads in the CART, and
            // provide it our in-memory value instead; then refresh whats
            // in memory
            //
            case OPCODE_IN:

                emuflag                  = TRUE;
                switch (port)
                {
                    ////////////////////////////////////////////////////////////////////
                    //
                    // For attempted accuracy, we manage our own FrameCounter
                    // for the CART
                    //
                    case TIM_FRAMECOUNTER:
                        memaddr          = (int *) ADDR_PORT_TIMFRAME;
                        address          = (int *) (ADDR_CART_REGISTERS + dstreg);
                        *address         = *memaddr;
                        break;

                    ////////////////////////////////////////////////////////////////////
                    //
                    // For attempted accuracy, we manage our own CycleCounter
                    // for the CART
                    //
                    case TIM_CYCLECOUNTER:
                        memaddr          = (int *) ADDR_PORT_TIMCYCLE;
                        address          = (int *) (ADDR_CART_REGISTERS + dstreg);
                        *address         = *memaddr;
                        break;

                    ////////////////////////////////////////////////////////////////////
                    //
                    // If getting a random number, emulate the IN instruction
                    // as we want to be able to exert control over it via the
                    // debugger (note that if RNG, it completely handles this
                    // instruction; if not, it lets it process)
                    //
                    case RNG_CURRENTVALUE:
                        memaddr          = (int *) ADDR_PORT_RNGVALUE;
                        address          = (int *) (ADDR_CART_REGISTERS + dstreg);
                        *address         = *memaddr;
                        asm
                        {
                            "PUSH  R0"
                            "IN    R0,           RNG_CurrentValue"
                            "MOV   [0x003FFFE1], R0"
                            "POP   R0"
                        }
                        break;

                    default:
                        emuflag          = FALSE;
                        break;
                }
                break;

            ////////////////////////////////////////////////////////////////////////////
            //
            // The OUT instruction  will be performed as  normal, we just
            // make  a quick  pit stop  here  to check  for the  specific
            // transaction, set the flag, then be back on our way.
            //
            case OPCODE_OUT:

                ////////////////////////////////////////////////////////////////////////
                //
                // obtain the value being transacted by the OUT, regardless
                // of form
                //
                if (immflag             >  0)
                {
                    value                = immediate;
                }
                else
                {
                    address              = (int *) (ADDR_CART_REGISTERS + srcreg);
                    value                = *address;
                }

                emuflag                  = TRUE;
                switch (port)
                {
                    case GPU_COMMAND:

                        ////////////////////////////////////////////////////////////////
                        //
                        // OUT: be on  the lookout for clear  screen instances, which
                        // will be  tied to  `clearflag` and  the continue  mode view
                        // rendering.
                        //
                        if (value       == GPUCMD_CLEAR)
                        {
                            clearflag    = TRUE;
                        }
                        emuflag          = FALSE;
                        break;

                    case GPU_CLEAR:
                        asm
                        {
                            "PUSH  R0"
                            "MOV   R0,           {value}"
                            "MOV   [0x003FFFE3], R0"
                            "POP   R0"
                        }
                        emuflag          = FALSE;
                        break;

                    case GPU_MULTIPLY:
                        asm
                        {
                            "PUSH  R0"
                            "MOV   R0,           {value}"
                            "MOV   [0x003FFFE4], R0"
                            "POP   R0"
                        }
                        emuflag          = FALSE;
                        break;

                    case GPU_BLEND:
                        asm
                        {
                            "PUSH  R0"
                            "MOV   R0,           {value}"
                            "MOV   [0x003FFFE5], R0"
                            "POP   R0"
                        }
                        emuflag          = FALSE;
                        break;

                    case GPU_TEXTURE:
                        asm
                        {
                            "PUSH  R0"
                            "MOV   R0,           {value}"
                            "MOV   [0x003FFFE6], R0"
                            "POP   R0"
                        }
                        emuflag          = FALSE;
                        break;

                    case GPU_REGION:
                        asm
                        {
                            "PUSH  R0"
                            "MOV   R0,           {value}"
                            "MOV   [0x003FFFE7], R0"
                            "POP   R0"
                        }
                        emuflag          = FALSE;
                        break;

                    case GPU_DRAWX:
                        asm
                        {
                            "PUSH  R0"
                            "MOV   R0,           {value}"
                            "MOV   [0x003FFFE8], R0"
                            "POP   R0"
                        }
                        emuflag          = FALSE;
                        break;

                    case GPU_DRAWY:
                        asm
                        {
                            "PUSH  R0"
                            "MOV   R0,           {value}"
                            "MOV   [0x003FFFE9], R0"
                            "POP   R0"
                        }
                        emuflag          = FALSE;
                        break;

                    case GPU_SCALEX:
                        asm
                        {
                            "PUSH  R0"
                            "MOV   R0,           {value}"
                            "MOV   [0x003FFFEA], R0"
                            "POP   R0"
                        }
                        emuflag          = FALSE;
                        break;

                    case GPU_SCALEY:
                        asm
                        {
                            "PUSH  R0"
                            "MOV   R0,           {value}"
                            "MOV   [0x003FFFEB], R0"
                            "POP   R0"
                        }
                        emuflag          = FALSE;
                        break;

                    case GPU_ANGLE:
                        asm
                        {
                            "PUSH  R0"
                            "MOV   R0,           {value}"
                            "MOV   [0x003FFFEC], R0"
                            "POP   R0"
                        }
                        emuflag          = FALSE;
                        break;

                    default:
                        emuflag          = FALSE;
                        break;
                }
                break;

            default:
                emuflag                  = FALSE;
                break;
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // if instruction emulation is triggered, do the deed
        //
        if (emuflag                     == TRUE)
        {
            emuflag                      = FALSE;
            offset                       = offset + 1;
            if (immflag                 >  0)
            {
                offset                   = offset + 1;
            }

            ////////////////////////////////////////////////////////////////////////////
            //
            // update TIM_CycleCounter
            //
            memaddr                      = (int *) ADDR_PORT_TIMCYCLE;
            *memaddr                     = *memaddr + 1;

            ////////////////////////////////////////////////////////////////////////////
            //
            // skip the rest of this loop and proceed to the next
            // instruction
            //
            continue;
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // point  the  'code' pointer  at  the  starting address  of  our
        // dynamic subroutine
        //
        // For reference:
        //
        //   0x003FFFB0 start of dynamic subroutine (48 total words)
        //     . . .
        //   0x003FFFE0 end of dynamic subroutine
        //
        // The idea is to pack  the instructions into a specific location
        // in memory (RAM), in known  consecutive locations, then to CALL
        // it like  a subroutine, run  the desired instruction,  then RET
        // from it.
        //
        // 0x003FFFB0 start of dynamic subroutine (64 total words)
        //
        code                             = (int *) ADDR_CUSTOM_ROUTINE;  // (BP+1)

        ////////////////////////////////////////////////////////////////////////////////
        //
        // GENERATE THE  IDEAL SUBROUTINE:  knowing that the  compiler is
        // very stack- centric, it will generally use as few registers as
        // possible.
        //
        // We will  make use of  R10 (after backing  it up onto  the CART
        // stack) to  obtain the needed  "return" value, collected  in an
        // earlier assembly  sequence, as essentially a  "hack" giving us
        // access to the InstructionPointer.
        //
        // If  we keep  everything  stack and  memory-bound, that  should
        // mitigate  data hazards.  As  the debugger,  we  don't want  to
        // interfere with the normal execution of code.
        //
        // That  said, we  need  to  be mindful  we  are maintaining  TWO
        // different  stacks: the  DEBUGGER  stack, and  the CART  stack.
        // Whenever we  hop into this  custom subroutine, we'll  swap out
        // BP/SP with the CART stack values, execute the instruction then
        // store the CART register changes, revert back to BIOS mode, and
        // that is exactly what happens below (see SWITCHING CONTEXTS)
        //
        index                            = 0;
        *(code+index++)                  = instruction; // instruction to process
        if (immflag                     >  0)
        {
            *(code+index++)              = immediate;   // immediate value
        }
        *(code+index++)                  = 0x55400000;  // PUSH R10
        *(code+index++)                  = 0x4F408000;  // MOV R10, [0x003FFFEF]
        *(code+index++)                  = 0x003FFFEF;  // immediate data (retaddr)
        *(code+index++)                  = 0x09400000;  // JMP R10
        *(code+index++)                  = 0x00000000;  // HLT

        ////////////////////////////////////////////////////////////////////////////////
        //
        // SWITCHING CONTEXTS: BIOS -> CART
        //
        // pre-custom routine, back up BIOS environment
        //
        asm
        {
            "MOV  [0x003FFFF0],        R0"  // back up BIOS to RAM
            "MOV  [0x003FFFF1],        R1"  // back up BIOS to RAM
            "MOV  [0x003FFFF2],        R2"  // back up BIOS to RAM
            "MOV  [0x003FFFF3],        R3"  // back up BIOS to RAM
            "MOV  [0x003FFFF4],        R4"  // back up BIOS to RAM
            "MOV  [0x003FFFF5],        R5"  // back up BIOS to RAM
            "MOV  [0x003FFFF6],        R6"  // back up BIOS to RAM
            "MOV  [0x003FFFF7],        R7"  // back up BIOS to RAM
            "MOV  [0x003FFFF8],        R8"  // back up BIOS to RAM
            "MOV  [0x003FFFF9],        R9"  // back up BIOS to RAM
            "MOV  [0x003FFFFA],        R10" // back up BIOS to RAM
            "MOV  [0x003FFFFB],        R11" // back up BIOS to RAM
            "MOV  [0x003FFFFC],        R12" // back up BIOS to RAM
            "MOV  [0x003FFFFD],        R13" // back up BIOS to RAM
            "MOV  [0x003FFFFE],        R14" // back up BIOS to RAM
            "MOV  [0x003FFFFF],        R15" // back up BIOS to RAM
            "MOV  R0,                  _CUSTOM_RET"  // grab returning offset
            "MOV  [0x003FFFEF],        R0"           // place it in memory
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Restore CART GPU IOPorts and CART gamepad
        //
        asm
        {
            "MOV  R0,                  [0x003FFFE3]" // restore CART GPU ports
            "OUT  GPU_ClearColor,      R0"
            "MOV  R0,                  [0x003FFFE4]"
            "OUT  GPU_MultiplyColor,   R0"
            "MOV  R0,                  [0x003FFFE5]"
            "OUT  GPU_ActiveBlending,  R0"
            "MOV  R0,                  [0x003FFFE6]"
            "OUT  GPU_SelectedTexture, R0"
            "MOV  R0,                  [0x003FFFE7]"
            "OUT  GPU_SelectedRegion,  R0"
            "MOV  R0,                  [0x003FFFE8]"
            "OUT  GPU_DrawingPointX,   R0"
            "MOV  R0,                  [0x003FFFE9]"
            "OUT  GPU_DrawingPointY,   R0"
            "MOV  R0,                  [0x003FFFEA]"
            "OUT  GPU_DrawingScaleX,   R0"
            "MOV  R0,                  [0x003FFFEB]"
            "OUT  GPU_DrawingScaleY,   R0"
            "MOV  R0,                  [0x003FFFEC]"
            "OUT  GPU_DrawingAngle,    R0"
            "MOV  R0,                  [0x003FFFED]"  // grab CART gamepad
            "OUT  INP_SelectedGamepad, R0"            // restore CART gamepad
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Restore CART registers
        //
        asm
        {
            "MOV  R13,                 [0x003FFBAD]"  // restore CART register
            "MOV  R12,                 [0x003FFBAC]"  // restore CART register
            "MOV  R11,                 [0x003FFBAB]"  // restore CART register
            "MOV  R10,                 [0x003FFBAA]"  // restore CART register
            "MOV  R9,                  [0x003FFBA9]"  // restore CART register
            "MOV  R8,                  [0x003FFBA8]"  // restore CART register
            "MOV  R7,                  [0x003FFBA7]"  // restore CART register
            "MOV  R6,                  [0x003FFBA6]"  // restore CART register
            "MOV  R5,                  [0x003FFBA5]"  // restore CART register
            "MOV  R4,                  [0x003FFBA4]"  // restore CART register
            "MOV  R3,                  [0x003FFBA3]"  // restore CART register
            "MOV  R2,                  [0x003FFBA2]"  // restore CART register
            "MOV  R1,                  [0x003FFBA1]"  // restore CART register
            "MOV  R0,                  [0x003FFBA0]"  // restore CART register
            "MOV  R14,                 [0x003FFBAE]"  // restore CART stack BP
            "MOV  R15,                 [0x003FFBAF]"  // restore CART stack SP
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Thinking  on this  situation some  more,  with the  help of  a
        // well-placed label,  we can  have the  assembler solve  all our
        // offset  problems: we'll  let it  translate the  offset of  our
        // label, allowing  us to  simply place  the desired  offset into
        // memory at the intended location for our custom routine to grab
        // it, no finangling on our part necessary. Here is the old code,
        // preserved due to  the awesome hack employed to  give us access
        // to the InstructionPointer (IP) register:
        //
        //  "CALL _GET_IP_REG"      // offset jujitsu being  done at  the
        //  "JMP  _AFTER_GETTING"   // last moment we are  still in  BIOS
        //  "_GET_IP_REG:"          // mode, before switching to the CART
        //  "MOV R0, [SP]"          // grab our current location (IP)  in
        //  "MOV [0x003FFFEF], R0"  // stack, save it to RAM  in a  known
        //  "RET"                   // location to grab later
        //  "_AFTER_GETTING:"
        //
        ////////////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////////////
        //
        // "CALL" IDEAL ROUTINE: With our subroutine generated in memory,
        // we can now CALL it to run it through.
        //
        // As subroutine  instruction processing is  sequential, starting
        // at  the very  first address  and proceeding  downward (barring
        // any  branching),  it will  "just  work",  and  we can  do  any
        // post-processing as needed.
        //
        // We don't actually want do a CALL, since it would impact what's
        // on the stack, and being a BIOS element, would pollute the CART
        // stack. So instead, we JMP to it, and finangle the ability  for
        // getting back via some label hackery.
        //
        // The  start of  the subroutine  is  the address  stored in  the
        // 'code' integer pointer. So, JMP to it:
        //
        asm
        {
            "JMP   0x003FFFB0"
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // SWITCHING CONTEXTS: CART -> BIOS
        //
        // post-custom  routine,  back  up  CART  and  restore  the  BIOS
        // environment
        //
        asm
        {
            "_CUSTOM_RET:"
            "POP  R10"              // R10 back to last legit CART state
            "MOV [0x003FFBAD], R13" // back up CART to RAM
            "MOV [0x003FFBAC], R12" // back up CART to RAM
            "MOV [0x003FFBAB], R11" // back up CART to RAM
            "MOV [0x003FFBAA], R10" // back up CART to RAM
            "MOV [0x003FFBA9], R9"  // back up CART to RAM
            "MOV [0x003FFBA8], R8"  // back up CART to RAM
            "MOV [0x003FFBA7], R7"  // back up CART to RAM
            "MOV [0x003FFBA6], R6"  // back up CART to RAM
            "MOV [0x003FFBA5], R5"  // back up CART to RAM
            "MOV [0x003FFBA4], R4"  // back up CART to RAM
            "MOV [0x003FFBA3], R3"  // back up CART to RAM
            "MOV [0x003FFBA2], R2"  // back up CART to RAM
            "MOV [0x003FFBA1], R1"  // back up CART to RAM
            "MOV [0x003FFBA0], R0"  // dummy back up CART to RAM
            "MOV [0x003FFBAE], R14" // back up CART to RAM
            "MOV [0x003FFBAF], R15" // back up CART to RAM
            "IN  R0,           GPU_ClearColor" // back up CART GPU ports
            "MOV [0x003FFFE3], R0"
            "IN  R0,           GPU_MultiplyColor"
            "MOV [0x003FFFE4], R0"
            "IN  R0,           GPU_ActiveBlending"
            "MOV [0x003FFFE5], R0"
            "IN  R0,           GPU_SelectedTexture"
            "MOV [0x003FFFE6], R0"
            "IN  R0,           GPU_SelectedRegion"
            "MOV [0x003FFFE7], R0"
            "IN  R0,           GPU_DrawingPointX"
            "MOV [0x003FFFE8], R0"
            "IN  R0,           GPU_DrawingPointY"
            "MOV [0x003FFFE9], R0"
            "IN  R0,           GPU_DrawingScaleX"
            "MOV [0x003FFFEA], R0"
            "IN  R0,           GPU_DrawingScaleY"
            "MOV [0x003FFFEB], R0"
            "IN  R0,           GPU_DrawingAngle"
            "MOV [0x003FFFEC], R0"
            "IN  R0,           INP_SelectedGamepad" // back up current CART gamepad
            "MOV [0x003FFFED], R0"           // back up current CART gamepad
            "MOV R0,           [0x003FFFF0]" // restore BIOS register
            "MOV R1,           [0x003FFFF1]" // restore BIOS register
            "MOV R2,           [0x003FFFF2]" // restore BIOS register
            "MOV R3,           [0x003FFFF3]" // restore BIOS register
            "MOV R4,           [0x003FFFF4]" // restore BIOS register
            "MOV R5,           [0x003FFFF5]" // restore BIOS register
            "MOV R6,           [0x003FFFF6]" // restore BIOS register
            "MOV R7,           [0x003FFFF7]" // restore BIOS register
            "MOV R8,           [0x003FFFF8]" // restore BIOS register
            "MOV R9,           [0x003FFFF9]" // restore BIOS register
            "MOV R10,          [0x003FFFFA]" // restore BIOS register
            "MOV R11,          [0x003FFFFB]" // restore BIOS register
            "MOV R12,          [0x003FFFFC]" // restore BIOS register
            "MOV R13,          [0x003FFFFD]" // restore BIOS register
            "MOV R14,          [0x003FFFFE]" // restore BIOS stack BP
            "MOV R15,          [0x003FFFFF]" // restore BIOS stack SP
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // restore BIOS gamepad
        //
        select_gamepad (DEBUG_GAMEPAD);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // advance CART "program counter"` by 1 (+ another 1 if immediate
        // data is present)
        //
        offset                           = offset + 1;
        if (immflag                     >  0)
        {
            offset                       = offset + 1;
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // increment the CART cycle counter
        //
        memaddr                          = (int *) ADDR_PORT_TIMCYCLE;
        *memaddr                         = *memaddr + 1;
    }

    asm { "hlt" }
}
void  draw_message_screen (int *title, int *message)
{
    int previous_texture  = get_selected_texture ();
    int previous_region   = get_selected_region ();

    clear_screen          (error_colors_background);
    set_multiply_color    (color_white);
    select_texture        (-1);

    // write title
    set_multiply_color    (error_colors_title);
    print_at              (49, 37, title);

    // draw horizontal line
    select_region         (region_white_square);
    set_drawing_scale     (640/2, 1);
    draw_region_zoomed_at (0, 60);
    set_drawing_scale     (1, 1);

    // write message
    set_multiply_color    (error_colors_message);
    print_at              (49, 95, message);

    select_texture        (previous_texture);
    select_region         (previous_region);
}

void  hexit  (int x, int y, int value)
{
    int [9] data;
    int     mask          = 0xF0000000;
    int     shift         = 28;
    int     index         = 0;
    int     byte          = 0;
    int     adjust        = 10;
    float   sx            = 0.0;
    float   sy            = 0.0;

    int     prev_vtex     = get_selected_texture ();
    int     prev_region   = get_selected_region  ();

    select_texture     (-1);
    get_drawing_scale  (&sx, &sy);
    adjust                = (float) adjust * sx;
    if (sx               != 1.0)
    {
        adjust            = adjust + 1;
    }

    strcpy             (data, "0x");
    print_zoomed_at    (x, y, data, sx);
    x                     = x + (adjust * 2);

    for (index            = 0;
         index           <  8;
         index            = index + 1)
    {
        byte              = (value & mask)    >> shift;
        if (byte         >  9)
            byte          = byte + 0x7;
        byte              = byte + 0x30;

        select_region  (byte);
        draw_region_at (x, y);

        x                 = x + adjust;
        shift             = shift - 4;
        mask              = mask >> 4;
    }
    select_texture (prev_vtex);
    select_region  (prev_region);
}

void  hexit_zoomed (int x, int y, int value, float factor)
{
    set_drawing_scale (factor, (factor * 2));
    hexit (x, y, value);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// portit(): display 3 digit IOPort hex value
//
void portit  (int x, int y, int value)
{
    int [4] data;
    int     mask              = 0xF00;
    int     shift             = 8;
    int     index             = 0;
    int     byte              = 0;
    int     previous_texture  = get_selected_texture ();
    int     previous_region   = get_selected_region ();

    select_texture (-1);

    strcpy (data, "0x");
    print_at (x, y, data);
    x                         = x + 20;

    for (index                = 0;
         index               <  3;
         index                = index + 1)
    {
        byte                  = (value & mask)    >> shift;
        if (byte             >  9)
            byte              = byte + 0x7;
        byte                  = byte + 0x30;

        select_region  (byte);
        draw_region_at (x, y);

        x                     = x + 10;
        shift                 = shift - 4;
        mask                  = mask >> 4;
    }
    select_texture (previous_texture);
    select_region  (previous_region);
}

void  print_hex_value (int  x, int  y, int *name, int  value)
{
    // convert the number to hex, always
    // showing the full 8 hex digits
    int [16+1] hex_characters  = "0123456789ABCDEF";
    int [8+1 ] hex_string;

    for (int Digit            = 7;
         Digit               >= 0;
         Digit--)
    {
        hex_string[ Digit ]   = hex_characters[value & 15];
        value               >>= 4;
    }

    hex_string[8]             = 0;

    // join all text parts
    int [60]   text;
    strcpy (text, name);
    strcat (text, " = 0x");
    strcat (text, hex_string);

    // print the text
    print_at (x, y, text);
}

bool  cartridge_connected ()
{
    asm
    {
        "in R0, CAR_Connected"
    }
}

void  request_cartridge ()
{
    int  previous_region   = get_selected_region ();

    draw_message_screen
    (
        "NO CARTRIDGE FOUND",
        "To play a game, please power off\n"
        "your console and insert a game\n"
        "cartridge compatible with Vircon32."
    );

    // draw console diagram
    set_multiply_color (color_white);
    select_region (region_console);
    draw_region_at (400, 207);

    select_region (region_cartridge );
    draw_region_at (469, 76 );

    select_region (region_large_arrow );
    draw_region_at (497, 149 );

    // ensure everything gets drawn
    end_frame ();

    select_region (previous_region);
}

void init_regions (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // define all texture regions in bios texture
    //
    select_texture (-1);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // all the characters of the text font
    //
    define_region_matrix (first_region_font, 1, 22, 10, 41, 1, 22, 32, 8, 0);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // white pixel
    //
    select_region (region_white_pixel);
    define_region_topleft (469, 29, 469, 29);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // logo letters
    //
    select_region (region_logo_letters);
    define_region (1, 183, 278, 238, 140, 238);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // logo V
    //
    select_region (region_logo_v);
    define_region_topleft (1, 183, 54,  238);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // logo 32
    //
    select_region (region_logo_32);
    define_region_topleft (190, 183, 278, 238);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // divider_v
    //
    select_region (region_divider_v);
    define_region_topleft (0, 0, 0, 50);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // divider_h
    //
    select_region (region_divider_h);
    define_region_topleft (0, 0, 80, 0);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // logo line
    //
    select_region (region_logo_line);
    define_region (1, 240, 278, 247, 140, 232);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // subtitle
    //
    select_region (region_subtitle);
    define_region (1, 1, 440, 20, 221, 20 );

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // console
    //
    select_region (region_console);
    define_region_topleft (280, 191, 478, 326);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // cartridge
    //
    select_region (region_cartridge);
    define_region_topleft (322, 116, 403, 189);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // large arrow
    //
    select_region (region_large_arrow);
    define_region_topleft (444, 26, 467, 85);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // white square
    //
    select_region (region_white_square);
    define_region_topleft (469, 26, 470, 27);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // clear the screen
    //
    clear_screen (color_black);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // CHECK FOR CARTRIDGE
    //
    if (!cartridge_connected ())
    {
        request_cartridge ();
        asm { "hlt" }
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // sanitize screen: ensure that any video parameters that might have
    // been used are restored to expected defaults
    //
    set_multiply_color (color_white);
    set_drawing_point (0, 0);
    select_region (0);

    select_gamepad (DEBUG_GAMEPAD);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// print_zoomed_at(): print "text" at given coordinates, X scale influenced
// by provided factor (1.0 for normal size)
//
void print_zoomed_at (int  drawing_x, int  drawing_y, int *text, float  factor)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // preserve previous texture selection
    //
    int  previous_texture   = get_selected_texture ();
    int  previous_region    = get_selected_region  ();

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // select the BIOS texture
    //
    select_texture (-1);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // begin drawing characters at the given position
    //
    int  initial_drawing_x  = drawing_x;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // until we encounter the null terminator at the end of the string...
    //
    while (*text)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // print this character (character value is region id)
        //
        select_region         (*text);
        set_drawing_scale     (factor,    1.0);
        draw_region_zoomed_at (drawing_x, drawing_y);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // advance in x, influenced by any scaling factor
        //
        if (factor         == 1.0)
        {
            drawing_x      += bios_character_width;
        }
        else
        {
            drawing_x      += (bios_character_width * factor) + 1;
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // execute line breaks
        //
        if (*text          == '\n')
        {
            ////////////////////////////////////////////////////////////////////////////
            //
            // y advances, x is reset
            //
            drawing_x       = initial_drawing_x;
            drawing_y      += bios_character_height;
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // advance to next character
        //
        ++text;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // restore previous texture and region selection
    //
    select_texture (previous_texture);
    select_region  (previous_region);
}

void draw_logo (int  modeflag)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // preserve previous texture selection
    //
    int  previous_texture   = get_selected_texture ();
    int  previous_region    = get_selected_region  ();

    set_blending_mode (blending_alpha);
    set_multiply_color (0xFFFFFFFF);
    clear_screen (color_black);
    select_texture (-1);
    select_region (region_divider_v);
    draw_region_at (0, 0);
    draw_region_at (80, 0);
    select_region (region_divider_h);
    draw_region_at (0, 0);
    draw_region_at (0, 50);
    select_region (region_logo_v);
    set_drawing_scale (0.5, 0.5);
    draw_region_zoomed_at (0, 0);
    select_region (region_logo_32);
    draw_region_zoomed_at (20,0);
    print_zoomed_at (0, 30, "d e b u g g e r", 0.50);
    set_drawing_scale (0.75, 1.5);
    set_drawing_angle (4.712389);
    select_region (66);
    draw_region_rotozoomed_at (64, 30);
    select_region (73);
    draw_region_rotozoomed_at (64, 24);
    select_region (79);
    draw_region_rotozoomed_at (64, 16);
    select_region (83);
    draw_region_rotozoomed_at (64, 8);
    set_multiply_color (color_yellow);
    print_zoomed_at (100, 0,
                     "DOWN single steps, START to continue, X to escape", 0.50);
    print_zoomed_at (100, 16,
                     "UP for content view (REGS, MEM, STACK, IOPORTS, none)", 0.50);

    switch (modeflag)
    {
        case MODE_REG:
            print_zoomed_at (100, 32,
                             "LEFT/RIGHT cycle formats (hex, int, float)", 0.50);
            break;

        case MODE_RNG:
            print_zoomed_at (100, 32,
                             "LEFT/RIGHT adjusts RNG value by 1, L/R by 100", 0.50);
            break;

        case MODE_STA:
            print_zoomed_at (100, 32, "LEFT/RIGHT adjust BP/SP view", 0.50);
            break;

        case MODE_BTR:
            print_zoomed_at (100, 32, "LEFT/RIGHT adjust backtrace view by 16", 0.50);
            break;

        case MODE_RAM:
        case MODE_MEM:
            print_zoomed_at (100, 32,
                             "LEFT/RIGHT adjust by 16, L/R adjust by 256", 0.50);
            break;
    }

    set_multiply_color (color_white);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // restore previous texture and region selection
    //
    select_texture (previous_texture);
    select_region  (previous_region);
}

////////////////////////////////////////////////////////////////////////////////////////
//
// error_handler(): process and report the system error
//
// NOTE:  this is  the  error_handler() developed  during the  spring2025
// offering of  the CSCS2650  Computer Organization  course at  SUNY CCC;
// ported over to add to the rich functionality of debuggerBIOS. 
//
void  error_handler ()
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare but NOT INITIALIZED  variables: default compiler action is
    // use R0  for transactions,  which will  override the  critical data
    // that the system placed in R0 for reporting here.
    //
    int   error_code;
    int   instruction_pointer;
    int   instruction;
    int   immediate_value;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // save registers to variables
    //
    asm
    {
        "mov   {error_code},          R0"
        "mov   {instruction_pointer}, R1"
        "mov   {instruction},         R2"
        "mov   {immediate_value},     R3"
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // ensure everything gets drawn
    //
    end_frame ();

    ////////////////////////////////////////////////////////////////////////////////////
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
    int      *offset;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // initialize memory type array with their identified names
    //
    string_data [4] memtype            =
    {
        { "[RAM] " }, { "[BIOS]" }, { "[CART]" }, { "[CARD]" }
    };
    memtype[0].lower                   = 0x00000000;
    memtype[0].upper                   = 0x003FFFFF;
    memtype[1].lower                   = 0x10000000;
    memtype[1].upper                   = 0x100FFFFF;
    memtype[2].lower                   = 0x20000000;
    memtype[2].upper                   = 0x27FFFFFF;
    memtype[3].lower                   = 0x30000000;
    memtype[3].upper                   = 0x30003FFF;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // determine messages for this error code
    //
    int  *error_title                  = NULL;
    int  *error_message                = NULL;

    switch (error_code)
    {
        case ERROR_MEMORY_READ:
            error_title                = "ERROR: INVALID MEMORY READ";
            error_message              = "Program attempted to read from a memory "
                                         "address\nthat does not exist or is in a "
                                         "write-only device.";
            break;

        case ERROR_MEMORY_WRITE:
            error_title                = "ERROR: INVALID MEMORY WRITE";
            error_message              = "Program attempted to write on a memory "
                                         "address\nthat does not exist or is in a "
                                         "read-only device.";
            break;

        case ERROR_PORT_READ:
            error_title                = "ERROR: INVALID PORT READ";
            error_message              = "Program attempted to read from a port "
                                         "number\nthat does not exist or is set "
                                         "as write-only.";
            break;

        case ERROR_PORT_WRITE:
            error_title                = "ERROR: INVALID PORT WRITE";
            error_message              = "Program attempted to write on a port "
                                         "number\nthat does not exist or is set "
                                         "as read-only.";
            break;

        case ERROR_STACK_OVERFLOW:
            error_title                = "ERROR: STACK OVERFLOW";
            error_message              = "Program pushed too many values in the "
                                         "stack\nand available RAM memory was "
                                         "exhausted.";
            break;

        case ERROR_STACK_UNDERFLOW:
            error_title                = "ERROR: STACK UNDERFLOW";
            error_message              = "Program popped too many values from the "
                                         "stack\nand all data stored in stack was "
                                         "exhausted.";
            break;

        case ERROR_DIVISION:
            error_title                = "ERROR: DIVISION BY ZERO";
            error_message              = "Program attempted to perform a division "
                                         "or\nmodulus operation where the divisor "
                                         "was zero.";
            break;

        case ERROR_ARC_COSINE:
            error_title                = "ERROR: ARC COSINE OUT OF RANGE";
            error_message              = "Program attempted to perform an arc "
                                         "cosine\noperation when the argument was "
                                         "not in [-1,+1].";
            break;

        case ERROR_ARC_TANGENT_2:
            error_title                = "ERROR: ARC TANGENT NOT DEFINED";
            error_message              = "Program attempted to perform an arc "
                                         "tangent\noperation when both of the "
                                         "arguments were 0.";
            break;

        case ERROR_LOGARITHM:
            error_title                = "ERROR: LOGARITHM OUT OF RANGE";
            error_message              = "Program attempted to perform a logarithm\n"
                                         "operation when the argument is not "
                                         "positive.";
            break;

        case ERROR_POWER:
            error_title                = "ERROR: POWER HAS NO REAL SOLUTION";
            error_message              = "Program attempted to perform a power "
                                         "operation\nwhen base was negative and "
                                         "exponent non integer.";
            break;

        case ERROR_UNKNOWN:
            error_title                = "UNKNOWN ERROR";
            error_message              = "Program caused a hardware error with an "
                                         "error\ncode that was not recognized by "
                                         "the BIOS.";
            break;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // draw the basic screen
    //
    set_drawing_scale (1.0, 1.0);
    draw_message_screen (error_title, error_message);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // CART context: when debugging, the offending CART instruction will be
    // the first instruction in the custom routine. To make the output more
    // valuable, adjust instruction_pointer to point to the actual location
    // in CART memory
    //
    offset                             = (int *) ADDR_CART_OFFSET;
    if (*offset                       != 0xDEADBEEF)
    {
        instruction_pointer            = (int) *offset;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // ID  memory page  of error:  ascertain and  display type  of memory
    // where error condition occurred
    //
    section                            = (instruction_pointer & 0x30000000) >> 28;
    print_at (579, 0, memtype[section].name);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // now print the related hex values
    //
    x                                  = 49;
    set_multiply_color (error_colors_values);
    print_hex_value (x, 160, "Instruction Pointer", instruction_pointer);
    print_hex_value (x, 180, "Instruction        ", instruction);
    print_hex_value (x, 200, "Immediate Value    ", immediate_value);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // REPORTING: do not do instruction dump for BIOS errors
    //
    if (section                       != 1)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // lookahead instruction logic: decode up to error instruction + 2
        // for display on screen
        //
        addr                           = (int *)(instruction_pointer);
        pos                            = 9;
        max                            = 5;
        while (pos                    <  (max * 3))
        {
            list[pos]                  = (int)(addr); // addr of +N instruction
            list[pos+1]                = *(addr);     // actual hex of +N instruction
            immflag                    = (*(addr) & 0x02000000) >> 25;
            if (immflag               == 1)
            {
                addr                   = addr + 1;
                list[pos+2]            = *(addr); // immediate value to +N instruction
            }
            else
            {
                list[pos+2]            = 0;
            }

            ////////////////////////////////////////////////////////////////////////////
            //
            // lookahead upper bound check
            //
            if ((int)addr             == memtype[section].upper)
            {
                max                    = (pos + 3) / 3;
                break;
            }

            addr                       = addr + 1;
            pos                        = pos  + 3;
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // look back, get to instruction (ensure instruction/immediate
        // alignment is correct)
        //
        pos                            = 6;
        addr                           = (int *) 0x20000000;
        if (instruction_pointer       >  0x20000000)
        {
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
        }

        ////////////////////////////////////////////////////////////////////////////////
        //
        // lower bound check
        //
        if ((int)addr                 == memtype[section].lower)
        {
            min                        = pos;
        }
        else
        {
            min                        = 0;
            for (index                 = 3;
                 index                >= min;
                 index                 = index - 3)
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
                    addr               = addr - 1; // check prior for immediate flag
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

                ////////////////////////////////////////////////////////////////////////
                //
                // lower bound check
                //
                if ((int)addr         == memtype[section].lower)
                {
                    min                = index;
                    break;
                }
            }
        }

        y                              = 240;
        for (index                     = 0;
             index                    <  max;
             index                     = index + 1)
        {
            ////////////////////////////////////////////////////////////////////////////
            //
            // Lower bound check for memory access
            //
            if (list[(index*3)+0]     <  memtype[section].lower)
            {
                continue;
            }

            ////////////////////////////////////////////////////////////////////////////
            //
            // highlight the current (error) instruction red, others in white
            //
            if (list[(index*3)+1]     == instruction)
            {
                set_multiply_color (color_red);
            }
            else
            {
                set_multiply_color (color_white);
            }

            x                          = 49;
            hexit (x, y, list[(index*3)]);
            x                          = x    + (strlen (data) * 10);
            print_at (x, y, ":");
            x                          = x    + 20;

            word                       = list[(index*3)+1];
            value                      = list[(index*3)+2];
            decode (169, y, word, value);

            y                          = y    + 20;

            ////////////////////////////////////////////////////////////////////////////
            //
            // Upper bound check for memory access
            //
            if (list[(index*3)+0]     == memtype[section].upper)
            {
                break;
            }
        }
    }

    print_at (579, 339, "[HALT]");

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // stop any sound
    //
    stop_all_channels ();
}

////////////////////////////////////////////////////////////////////////////////////////
//
// decode(): take machine code instruction w/ immediate data and decode
// into assembly instruction
//
void decode (int x, int y, int instruction, int immediate)
{
    int [18] data;
    int      opcode          = (instruction & 0xFC000000) >> 26; // bits 31-26
    int      immflag         = (instruction & 0x02000000) >> 25; // bit  25
    int      dstreg          = (instruction & 0x01E00000) >> 21; // bits 24-21
    int      srcreg          = (instruction & 0x001E0000) >> 17; // bits 20-17
    int      addr            = (instruction & 0x0001C000) >> 14; // bits 16-14
    int      port            = (instruction & 0x00003FFF);       // bits 13-0

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // initialize our opcodes array with the available instructions
    //
    opcode_t [64] mneumonic  =
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

    strcpy (data, mneumonic[opcode].name);
    print_at (x, y, data);
    x                        = x + 60;

    switch (opcode)
    {
        case OPCODE_HLT:  // zero operand instructions
        case OPCODE_WAIT:
        case OPCODE_RET:
        case OPCODE_MOVS:
        case OPCODE_SETS:
            break;

        case OPCODE_JMP:   // one operand instructions
        case OPCODE_CALL:
        case OPCODE_PUSH:
        case OPCODE_POP:
        case OPCODE_CMPS:
        case OPCODE_CIF:
        case OPCODE_CFI:
        case OPCODE_CIB:
        case OPCODE_CFB:
        case OPCODE_NOT:
        case OPCODE_BNOT:
        case OPCODE_ISGN:
        case OPCODE_IABS:
        case OPCODE_FSGN:
        case OPCODE_FABS:
        case OPCODE_FLR:
        case OPCODE_CEIL:
        case OPCODE_ROUND:
        case OPCODE_SIN:
        case OPCODE_ACOS:
        case OPCODE_LOG:
            if (immflag     == 1)
            {
                hexit (x, y, immediate);
            }
            else
            {
                strcpy (data, "R");
                print_at (x, y, data);
                x            = x + 10;
                itoa (dstreg, data, 10);
                print_at (x, y, data);
            }
            break;

        case OPCODE_JT: // two-operand integer instructions
        case OPCODE_JF:
        case OPCODE_IEQ:
        case OPCODE_INE:
        case OPCODE_IGT:
        case OPCODE_IGE:
        case OPCODE_ILT:
        case OPCODE_ILE:
        case OPCODE_AND:
        case OPCODE_OR:
        case OPCODE_XOR:
        case OPCODE_SHL:
        case OPCODE_IADD:
        case OPCODE_ISUB:
        case OPCODE_IMUL:
        case OPCODE_IDIV:
        case OPCODE_IMOD:
        case OPCODE_IMIN:
        case OPCODE_IMAX:
            strcpy (data, "R");
            print_at (x, y, data);
            x                = x + 10;
            itoa (dstreg, data, 10);
            print_at (x, y, data);

            if (dstreg      >  9) // calibrate for register name length (R# vs R##)
            {
                x            = x + 10;
            }
            x                = x + 10;

            strcpy (data, ", ");
            print_at (x, y, data);
            x                = x + 20;

            if (immflag     == 1)
            {
                hexit (x, y, immediate);
            }
            else
            {
                strcpy (data, "R");
                print_at (x, y, data);
                x            = x + 10;
                itoa (srcreg, data, 10);
                print_at (x, y, data);
            }
            break;

        case OPCODE_FEQ: // two-operand float instructions
        case OPCODE_FNE:
        case OPCODE_FGT:
        case OPCODE_FGE:
        case OPCODE_FLT:
        case OPCODE_FLE:
        case OPCODE_FADD:
        case OPCODE_FSUB:
        case OPCODE_FMUL:
        case OPCODE_FDIV:
        case OPCODE_FMOD:
        case OPCODE_FMIN:
        case OPCODE_FMAX:
        case OPCODE_ATAN2:
        case OPCODE_POW:
            strcpy (data, "R");
            print_at (x, y, data);
            x                = x + 10;
            itoa (dstreg, data, 10);
            print_at (x, y, data);

            if (dstreg      >  9) // calibrate for register name length (R# vs R##)
            {
                x            = x + 10;
            }
            x                = x + 10;

            strcpy (data, ", ");
            print_at (x, y, data);

            if (dstreg      <= 9)
            {
                x            = x + 10;
            }
            x                = x + 150;

            if (immflag     == 1)
            {
                ftoa (immediate, data);
            }
            else
            {
                strcpy (data, "R");
                print_at (x, y, data);
                x            = x + 10;
                itoa (srcreg, data, 10);
            }
            print_at (x, y, data);
            break;

        case OPCODE_MOV:
            switch (addr)
            {
                case 00:
                    strcpy (data, "R");
                    print_at (x, y, data);
                    x        = x + 10;
                    itoa (dstreg, data, 10);
                    print_at (x, y, data);
                    if (dstreg >  9)
                    {
                        x    = x + 10;
                    }
                    x        = x + 10;
                    strcpy (data, ",");
                    print_at (x, y, data);
                    x        = x + 20;
                    hexit (x, y, immediate);
                    break;

                case 01:
                    strcpy (data, "R");
                    print_at (x, y, data);
                    x        = x + 10;
                    itoa (dstreg, data, 10);
                    print_at (x, y, data);
                    if (dstreg >  9)
                    {
                        x    = x + 10;
                    }
                    x        = x + 10;
                    strcpy (data, ", R");
                    print_at (x, y, data);
                    x        = x + 30;
                    itoa (srcreg, data, 10);
                    print_at (x, y, data);
                    break;

                case 02:
                    strcpy (data, "R");
                    print_at (x, y, data);
                    x        = x + 10;
                    itoa (dstreg, data, 10);
                    print_at (x, y, data);
                    if (dstreg >  9)
                    {
                        x    = x + 10;
                    }
                    x        = x + 10;
                    strcpy (data, ", [");
                    print_at (x, y, data);
                    x        = x + 30;
                    hexit (x, y, immediate);
                    x        = x + 100;
                    strcpy (data, "]");
                    print_at (x, y, data);
                    break;

                case 03:
                    strcpy (data, "R");
                    print_at (x, y, data);
                    x        = x + 10;
                    itoa (dstreg, data, 10);
                    print_at (x, y, data);
                    if (dstreg >  9)
                    {
                        x    = x + 10;
                    }
                    x        = x + 10;
                    strcpy (data, ", [R");
                    print_at (x, y, data);
                    x        = x + 40;
                    itoa (srcreg, data, 10);
                    print_at (x, y, data);
                    if (srcreg >  9)
                    {
                        x    = x + 10;
                    }
                    x        = x + 10;
                    strcpy (data, "]");
                    print_at (x, y, data);
                    break;

                case 04:
                    strcpy (data, "R");
                    print_at (x, y, data);
                    x        = x + 10;
                    itoa (dstreg, data, 10);
                    print_at (x, y, data);
                    if (dstreg >  9)
                    {
                        x    = x + 10;
                    }
                    x        = x + 10;
                    strcpy (data, ", [R");
                    print_at (x, y, data);
                    x        = x + 40;
                    itoa (srcreg, data, 10);
                    print_at (x, y, data);
                    if (srcreg >  9)
                    {
                        x    = x + 10;
                    }
                    x        = x + 10;
                    strcpy (data, "+");
                    print_at (x, y, data);
                    x        = x + 10;
                    hexit (x, y, immediate);
                    x        = x + 100;
                    strcpy (data, "]");
                    print_at (x, y, data);
                    break;

                case 05:
                    strcpy (data, "[");
                    print_at (x, y, data);
                    x        = x + 10;
                    hexit (x, y, immediate);
                    x        = x + 100;
                    strcpy (data, "],");
                    print_at (x, y, data);
                    x        = x + 30;
                    strcpy (data, "R");
                    print_at (x, y, data);
                    x        = x + 10;
                    itoa (srcreg, data, 10);
                    print_at (x, y, data);
                    break;

                case 06:
                    strcpy (data, "[R");
                    print_at (x, y, data);
                    x         = x + 20;
                    itoa (dstreg, data, 10);
                    print_at (x, y, data);
                    if (dstreg >  9)
                    {
                        x    = x + 10;
                    }
                    x        = x + 10;
                    strcpy (data, "],");
                    print_at (x, y, data);
                    x        = x + 30;
                    strcpy (data, "R");
                    print_at (x, y, data);
                    x        = x + 10;
                    itoa (srcreg, data, 10);
                    print_at (x, y, data);
                    break;

                case 07:
                    strcpy (data, "[R");
                    print_at (x, y, data);
                    x        = x + 20;
                    itoa (dstreg, data, 10);
                    print_at (x, y, data);
                    if (dstreg >  9)
                    {
                        x    = x + 10;
                    }
                    x        = x + 10;
                    strcpy (data, "+");
                    print_at (x, y, data);
                    x        = x + 10;
                    hexit (x, y, immediate);
                    x        = x + 100;
                    strcpy (data, "],");
                    print_at (x, y, data);
                    x        = x + 30;
                    strcpy (data, "R");
                    print_at (x, y, data);
                    x        = x + 10;
                    itoa (srcreg, data, 10);
                    print_at (x, y, data);
                    break;
            }
            break;

        case OPCODE_LEA:
            strcpy (data, "R");
            print_at (x, y, data);
            x                = x + 10;
            itoa (dstreg, data, 10);
            print_at (x, y, data);
            if (dstreg      >  9)
            {
                x            = x + 10;
            }
            x                = x + 10;
            strcpy (data, ", [R");
            print_at (x, y, data);
            x                = x + 40;
            itoa (srcreg, data, 10);
            print_at (x, y, data);
            if (srcreg      >  9)
            {
                x            = x + 10;
            }
            x                = x + 10;

            if (immflag     == 1)
            {
                strcpy (data, "+");
                print_at (x, y, data);
                x            = x + 10;
                hexit (x, y, immediate);
                x            = x + 100;
            }
            strcpy (data, "]");
            print_at (x, y, data);
            break;

        case OPCODE_IN:
            strcpy (data, "R");
            print_at (x, y, data);
            x                = x + 10;
            itoa (dstreg, data, 10);
            print_at (x, y, data);
            if (dstreg      >  9)
            {
                x            = x + 10;
            }
            x                = x + 10;
            strcpy (data, ",");
            print_at (x, y, data);
            x                = x + 20;
            portit (x, y, port);
            break;

        case OPCODE_OUT:
            portit (x, y, port);
            x                = x + 50;
            if (immflag     == 1) // we have an immediate value
            {
                strcpy (data, ",");
                print_at (x, y, data);
                x            = x + 20;
                hexit (x, y, immediate);
            }
            else
            {
                strcpy (data, ", R");
                print_at (x, y, data);
                x            = x + 30;
                itoa (srcreg, data, 10);
                print_at (x, y, data);
            }
            break;
    }
}
////////////////////////////////////////////////////////////////////////////////////////
//
// views(): process the individual resource views
//
void  views (int  modeflag, int *offset, int *viewflags, int *backtrace)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Declare and initialize variables
    //
    int [33]  data;
    int      *address              = NULL;
    int      *stack                = NULL;
    int       index                = 0;
    int       pos                  = 0;
    int       value                = 0;
    int       viewval              = 0;
    float     fvalue               = 0.0;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // preserve previous texture selection
    //
    int  previous_texture          = get_selected_texture ();
    int  previous_region           = get_selected_region  ();

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // switch to the BIOS texture
    //
    select_texture (-1);

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Ensure the data array is cleared
    //
    for (index                     = 0;
         index                    <  16;
         index                     = index + 1)
    {
        data[index]                = 0;         // clear the data array
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // obtain the mode-specific view value
    //
    if ((modeflag                 >= MODE_NONE) &&
        (modeflag                 <  NUM_MODES))
    {
        viewval                    = *(viewflags+modeflag);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Process for the selected mode
    //
    switch (modeflag)
    {
        ////////////////////////////////////////////////////////////////////////////////
        //
        // register display: if enabled, the
        // CART register values will be displayed off to the right
        //
        case MODE_REG:
            print_zoomed_at (490, 0, "register view", 1.0);
            select_region   (region_divider_h);
            draw_region_at  (490, 20);
            draw_region_at  (540, 20);

            for (index             = 0;
                 index            <  16;        // for all registers
                 index             = index + 1)
            {
                itoa (index, &data[1], 10);
                data[0]            = 'R';
                if (index         <  10)
                {
                    data[2]        = ':';
                    data[3]        = 0;
                }
                else
                {
                    data[3]        = ':';
                    data[4]        = 0;
                }
                print_at (490, 18 + (index * 18), data); 

                ////////////////////////////////////////////////////////////////////
                //
                // display CART register value (backed up in memory)
                //
                address            = (int *) ADDR_CART_REGISTERS;
                value              = *(address+index);
                switch (viewval)
                {
                    case FORMAT_HEX:
                        hexit_zoomed (540, 18 + (index * 18), value, 0.75);
                        break;

                    case FORMAT_INTEGER:
                        itoa (value, data, 10);
                        print_at (540, 18 + (index * 18), data);
                        break;

                    case FORMAT_FLOAT:
                        fvalue     = (float) *(address+index);
                        ftoa (fvalue, data);
                        print_at (540, 18 + (index * 18), data);
                        break;
                }
            }

            print_at (490, 18 + (index * 18), "IP:");
            hexit_zoomed (540, 18 + (index * 18), (int) offset, 0.75);
            print_at (490, 18 + ((index+1) * 18), "IR:");
            value                  = *offset;
            hexit_zoomed (540, 18 + ((index+1) * 18), value, 0.75);
            if ((value & 0x02000000) >  0)
            {
                value                 = *(offset+1);
                print_at (490, 18 + ((index+2) * 18), "IV:");
                hexit_zoomed (540, 18 + ((index+2) * 18), value, 0.75);
            }
            break;

        ////////////////////////////////////////////////////////////////////////////////
        //
        // backtrace view: if selected, and the backtrace array populated,
        // display the current function call stack
        //
        case MODE_BTR:
            print_zoomed_at (464, 0, "backtrace", 1.0);
            select_region   (region_divider_h);
            draw_region_at  (464, 20);
            draw_region_at  (540, 20);

            pos                    = 20;
            for (index             = 15;
                 index            >= 0;
                 index             = index - 1)
            {
                if (-1            == *(backtrace+(viewval+index)))
                {
                    continue;
                }
                print_zoomed_at (464, pos, "[", 0.75);
                itoa            ((index + viewval), data, 10);
                print_zoomed_at (474, pos, data, 0.75);
                print_zoomed_at (494, pos, "]:", 0.75);
                hexit_zoomed    (524, pos, *(backtrace+(viewval+index)), 0.75);
                pos                = pos + 20;
            }
            break;

        ////////////////////////////////////////////////////////////////////////////////
        //
        // memory display: if selected, the CART memory values will be
        // displayed off to the right
        //
        case MODE_RAM:
            print_zoomed_at (464, 0, "memaddr   value", 1.0);
            select_region   (region_divider_h);
            draw_region_at  (464, 20);
            draw_region_at  (560, 20);

            for (index             = 0;
                 index            <  16;        // run from 0 to 15, for all registers
                 index             = index + 1)
            {
                ////////////////////////////////////////////////////////////////////////
                //
                // display address
                //
                hexit_zoomed    (464, (20+(index * 20)), (viewval+index), 0.75);
                print_zoomed_at (544, (20+(index * 20)), ":", 0.75); 

                ////////////////////////////////////////////////////////////////////////
                //
                // display value at address
                //
                address            = (int *) (value+index);
                hexit_zoomed (560, (20+(index * 20)), *(address), 0.75);
            }
            break;

        ////////////////////////////////////////////////////////////////////////////////
        //
        // MODE_STA: if selected, the stack registers and memory that
        // immediate surrounds the stack will be displayed
        //
        case MODE_STA:
            print_zoomed_at (464, 0, "stack     value", 1.0);
            select_region   (region_divider_h);
            draw_region_at  (464, 20);
            draw_region_at  (560, 20);

            ////////////////////////////////////////////////////////////////////////////
            //
            // obtain the CART stack pointer
            //
            print_at (464, 20, "SP:"); 
            asm
            {
                "PUSH R0"
                "MOV  R0,        [0x003FFBAF]"
                "MOV  {address}, R0"
                "POP  R0"
            }
            hexit_zoomed (560, 20, (int) address, 0.75);

            ////////////////////////////////////////////////////////////////////////////
            //
            // obtain the CART base pointer
            //
            asm
            {
                "PUSH R0"
                "MOV  R0,        [0x003FFBAE]"
                "MOV  {stack}, R0"
                "POP  R0"
            }

            pos                    = 20;
            for (index             = 0;
                 index            <= viewval;
                 index             = index + 1)
            {
                if ((0            <= (int) (address+index)) &&
                    (0x003FFFFF   >= (int) (address+index)) &&
                    (stack        >= (address+index)))
                {
                    pos            = pos + 16;
                    print_at     (464, pos, "[SP+"); 
                    itoa         (index, data, 10);
                    print_at     (504, pos, data);
                    print_at     (524, pos, "]:");
                    hexit_zoomed (560, pos, *(address+index), 0.75);
                }
                else
                {
                    break;
                }

                if (stack         == (address+index))
                {
                    break;
                }
            }

            pos                    = pos + 16;
            print_at     (464, pos, "BP:"); 
            hexit_zoomed (560, pos, (int) stack, 0.75);

            for (index             = 0;
                 index            <  18 - viewval;
                 index             = index + 1)
            {
                if ((0            <= (int) (stack+index)) &&
                    (0x003FFFFF   >= (int) (stack+index)) &&
                    (stack        >= (address+index)))
                {
                    pos            = pos + 16;
                    print_at     (464, pos, "[BP+"); 
                    itoa         (index, data, 10);
                    print_at     (504, pos, data);
                    print_at     (524, pos, "]:");
                    hexit_zoomed (560, pos, *(stack+index), 0.75);
                }
                else
                {
                    break;
                }
            }
            break;

        ////////////////////////////////////////////////////////////////////////////////
        //
        // MODE_TIMPORTS: if selected, TIM ports and their values will be
        // displayed
        //
        case MODE_TIM:

            print_zoomed_at (464, 0, "TIM port value", 1.0);
            select_region   (region_divider_h);
            draw_region_at  (464, 20);
            draw_region_at  (560, 20);

            print_at (464, 20, "Date:");
            asm
            {
                "PUSH R0"
                "IN   R0,      TIM_CurrentDate"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 16);
            print_at (560, 20, data);

            print_at (464, 40, "Time:");
            asm
            {
                "PUSH R0"
                "IN   R0,      TIM_CurrentTime"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 16);
            print_at (560, 40, data);

            print_at (464, 60, "Frame #:");
            asm
            {
                "PUSH R0"
                "MOV  R0,      [0x003FFFDF]"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 60, data);

            print_at (464, 80, "Cycles:");
            asm
            {
                "PUSH R0"
                "MOV  R0,      [0x003FFFE0]"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 80, data);
            break;

        ////////////////////////////////////////////////////////////////////////////////
        //
        // MODE_RNGPORTS: if selected, RNG port and its value will be
        // displayed
        //
        case MODE_RNG:

            print_zoomed_at (464, 0, "RNG port value", 1.0);
            select_region   (region_divider_h);
            draw_region_at  (464, 20);
            draw_region_at  (560, 20);

            print_at (464, 20, "RAND:");
            asm
            {
                "PUSH R0"
                "MOV  R0,      [0x003FFFE1]"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 20, data);
            break;

        ////////////////////////////////////////////////////////////////////////////////
        //
        // MODE_GPU: if selected, GPU ports and their values will be
        // displayed
        //
        case MODE_GPU:

            print_zoomed_at (464, 0, "GPU port value", 1.0);
            select_region   (region_divider_h);
            draw_region_at  (464, 20);
            draw_region_at  (560, 20);

            print_at (464, 20, "Clear:");
            asm
            {
                "PUSH R0"
                "MOV  R0,      [0x003FFFE3]"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 16);
            print_at (560, 20, data);

            print_at (464, 40, "Multiply:");
            asm
            {
                "PUSH R0"
                "MOV  R0,      [0x003FFFE4]"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 16);
            print_at (560, 40, data);

            print_at (464, 60, "Blending:");
            asm
            {
                "PUSH R0"
                "MOV  R0,      [0x003FFFE5]"
                "MOV  {value}, R0"
                "POP  R0"
            }

            if (value       == 0x20)
            {
                print_at (560, 60, "alpha");
            }
            else if (value  == 0x21)
            {
                print_at (560, 60, "add");
            }
            else
            {
                print_at (560, 60, "subtract");
            }

            print_at (464, 80, "Texture:");
            asm
            {
                "PUSH R0"
                "MOV  R0,      [0x003FFFE6]"
                "OUT  GPU_SelectedTexture, R0"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 80, data);

            print_at (464, 100, "Region:");
            asm
            {
                "PUSH R0"
                "MOV  R0,      [0x003FFFE7]"
                "OUT  GPU_SelectedRegion, R0"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 100, data);

            print_at (464, 120, "DrawX:");
            asm
            {
                "PUSH R0"
                "MOV  R0,      [0x003FFFE8]"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 120, data);

            print_at (464, 140, "DrawY:");
            asm
            {
                "PUSH R0"
                "MOV  R0,      [0x003FFFE9]"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 140, data);

            print_at (464, 160, "ScaleX:");
            asm
            {
                "PUSH R0"
                "MOV  R0,       [0x003FFFEA]"
                "MOV  {fvalue}, R0"
                "POP  R0"
            }
            ftoa (fvalue, data);
            print_at (560, 160, data);

            print_at (464, 180, "ScaleY:");
            asm
            {
                "PUSH R0"
                "MOV  R0,       [0x003FFFEB]"
                "MOV  {fvalue}, R0"
                "POP  R0"
            }
            ftoa (fvalue, data);
            print_at (560, 180, data);

            print_at (464, 200, "Angle:");
            asm
            {
                "PUSH R0"
                "MOV  R0,       [0x003FFFEC]"
                "MOV  {fvalue}, R0"
                "POP  R0"
            }
            ftoa (fvalue, data);
            print_at (560, 200, data);

            print_at (464, 220, "MinX:");
            asm
            {
                "PUSH R0"
                "MOV  R0,      [0x003FFFE6]"
                "OUT  GPU_SelectedTexture, R0"
                "MOV  R0,      [0x003FFFE7]"
                "OUT  GPU_SelectedRegion, R0"
                "IN   R0,      GPU_RegionMinX"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 220, data);

            print_at (464, 240, "MinY:");
            asm
            {
                "PUSH R0"
                "MOV  R0,      [0x003FFFE6]"
                "OUT  GPU_SelectedTexture, R0"
                "MOV  R0,      [0x003FFFE7]"
                "OUT  GPU_SelectedRegion, R0"
                "IN   R0,      GPU_RegionMinY"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 240, data);

            print_at (464, 260, "MaxX:");
            asm
            {
                "PUSH R0"
                "MOV  R0,      [0x003FFFE6]"
                "OUT  GPU_SelectedTexture, R0"
                "MOV  R0,      [0x003FFFE7]"
                "OUT  GPU_SelectedRegion, R0"
                "IN   R0,      GPU_RegionMaxX"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 260, data);

            print_at (464, 280, "MaxY:");
            asm
            {
                "PUSH R0"
                "MOV  R0,      [0x003FFFE6]"
                "OUT  GPU_SelectedTexture, R0"
                "MOV  R0,      [0x003FFFE7]"
                "OUT  GPU_SelectedRegion, R0"
                "IN   R0,      GPU_RegionMaxY"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 280, data);

            print_at (464, 300, "HotspotX:");
            asm
            {
                "PUSH R0"
                "MOV  R0,      [0x003FFFE6]"
                "OUT  GPU_SelectedTexture, R0"
                "MOV  R0,      [0x003FFFE7]"
                "OUT  GPU_SelectedRegion, R0"
                "IN   R0,      GPU_RegionHotSpotX"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 300, data);

            print_at (464, 320, "HotspotY:");
            asm
            {
                "PUSH R0"
                "MOV  R0,      [0x003FFFE6]"
                "OUT  GPU_SelectedTexture, R0"
                "MOV  R0,      [0x003FFFE7]"
                "OUT  GPU_SelectedRegion, R0"
                "IN   R0,      GPU_RegionHotspotY"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 320, data);
            break;

        ////////////////////////////////////////////////////////////////////////////////
        //
        // MODE_SPU: if selected, SPU ports and their values will be
        // displayed
        //
        case MODE_SPU:
            print_zoomed_at (464, 0, "SPU port value", 1.0);
            select_region   (region_divider_h);
            draw_region_at  (464, 20);
            draw_region_at  (560, 20);

            print_at (464, 20, "Volume:");
            asm
            {
                "PUSH R0"
                "IN   R0,                  SPU_GlobalVolume"
                "MOV  {fvalue},            R0"
                "POP  R0"
            }
            ftoa (fvalue, data);
            print_at (560, 20, data);

            print_at (464, 40, "Sound #:");
            asm
            {
                "PUSH R0"
                "IN   R0,                  SPU_SelectedSound"
                "MOV  {value},             R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 40, data);

            print_at (464, 60, "Channel#:");
            asm
            {
                "PUSH R0"
                "IN   R0,                  SPU_SelectedChannel"
                "MOV  {value},             R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 60, data);

            print_at (464, 80, "SoundLen:");
            asm
            {
                "PUSH R0"
                "IN   R0,                  SPU_SoundLength"
                "MOV  {value},             R0"
                "POP  R0"
            }
            hexit_zoomed (560, 80, value, 0.75);

            print_at (464, 100, "PlayLoop:");
            asm
            {
                "PUSH R0"
                "IN   R0,                  SPU_SoundPlayWithLoop"
                "MOV  {value},             R0"
                "POP  R0"
            }

            if (value             == 0)
            {
                print_at (560, 100, "false");
            }
            else
            {
                print_at (560, 100, "true");
            }

            print_at (464, 120, "LoopStrt:");
            asm
            {
                "PUSH R0"
                "IN   R0,                  SPU_SoundLoopStart"
                "MOV  {value},             R0"
                "POP  R0"
            }
            hexit_zoomed (560, 120, value, 0.75);

            print_at (464, 140, "LoopEnd:");
            asm
            {
                "PUSH R0"
                "IN   R0,                  SPU_SoundLoopEnd"
                "MOV  {value},             R0"
                "POP  R0"
            }
            hexit_zoomed (560, 140, value, 0.75);

            print_at (464, 160, "ChanStat:");
            asm
            {
                "PUSH R0"
                "IN   R0,                  SPU_ChannelState"
                "MOV  {value},             R0"
                "POP  R0"
            }

            switch (value)
            {
                case 0x40: // SPUChannelState_Stopped
                    print_at (560, 160, "stopped");
                    break;

                case 0x41: // SPUChannelState_Paused
                    print_at (560, 160, "paused");
                    break;

                case 0x42: // SPUChannelState_Playing
                    print_at (560, 160, "playing");
                    break;
            }

            print_at (464, 180, "ChnSet:");
            asm
            {
                "PUSH R0"
                "IN   R0,                  SPU_ChannelAssignedSound"
                "MOV  {value},             R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 180, data);

            print_at (464, 200, "ChanVol:");
            asm
            {
                "PUSH R0"
                "IN   R0,                  SPU_ChannelVolume"
                "MOV  {fvalue},            R0"
                "POP  R0"
            }
            ftoa (fvalue, data);
            print_at (560, 200, data);

            print_at (464, 220, "ChanSpd:");
            asm
            {
                "PUSH R0"
                "IN   R0,                  SPU_ChannelSpeed"
                "MOV  {fvalue},            R0"
                "POP  R0"
            }
            ftoa (fvalue, data);
            print_at (560, 220, data);

            print_at (464, 240, "ChanLoop:");
            asm
            {
                "PUSH R0"
                "IN   R0,                  SPU_ChannelLoopEnabled"
                "MOV  {value},             R0"
                "POP  R0"
            }

            if (value             == 0)
            {
                print_at (560, 240, "false");
            }
            else
            {
                print_at (560, 240, "true");
            }

            print_at (464, 260, "ChanPos:");
            asm
            {
                "PUSH R0"
                "IN   R0,                  SPU_ChannelPosition"
                "MOV  {fvalue},            R0"
                "POP  R0"
            }
            ftoa (fvalue, data);
            print_at (560, 260, data);
            break;

        ////////////////////////////////////////////////////////////////////////////////
        //
        // MODE_INP: if selected, INP ports and their values will be
        // displayed
        //
        case MODE_INP:
            print_zoomed_at (464, 0, "INP port value", 1.0);
            select_region   (region_divider_h);
            draw_region_at  (464, 20);
            draw_region_at  (560, 20);

            print_at (464, 20, "Gamepad:");
            select_gamepad (viewval);
            itoa (viewval, data, 10);
            print_at (560, 20, data);

            print_zoomed_at (464, 40, "Connected:", 0.75);
            asm
            {
                "PUSH R0"
                "IN   R0,      INP_GamepadConnected"
                "MOV  {value}, R0"
                "POP  R0"
            }

            if (value             == 1)
            {
                print_at (560, 40, "true");
            }
            else
            {
                print_at (560, 40, "false");
            }

            print_at (464, 60, "Left:");
            asm
            {
                "PUSH R0"
                "IN   R0,      INP_GamepadLeft"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 60, data);

            print_at (464, 80, "Right:");
            asm
            {
                "PUSH R0"
                "IN   R0,      INP_GamepadRight"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 80, data);

            print_at (464, 100, "Up:");
            asm
            {
                "PUSH R0"
                "IN   R0,      INP_GamepadUp"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 100, data);

            print_at (464, 120, "Down:");
            asm
            {
                "PUSH R0"
                "IN   R0,      INP_GamepadDown"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 120, data);

            print_at (464, 140, "Start:");
            asm
            {
                "PUSH R0"
                "IN   R0,      INP_GamepadButtonStart"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 140, data);

            print_at (464, 160, "A:");
            asm
            {
                "PUSH R0"
                "IN   R0,      INP_GamepadButtonA"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 160, data);

            print_at (464, 180, "B:");
            asm
            {
                "PUSH R0"
                "IN   R0,      INP_GamepadButtonB"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 180, data);

            print_at (464, 200, "X:");
            asm
            {
                "PUSH R0"
                "IN   R0,      INP_GamepadButtonX"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 200, data);

            print_at (464, 220, "Y:");
            asm
            {
                "PUSH R0"
                "IN   R0,      INP_GamepadButtonY"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 220, data);

            print_at (464, 240, "L:");
            asm
            {
                "PUSH R0"
                "IN   R0,      INP_GamepadButtonL"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 240, data);

            print_at (464, 260, "R:");
            asm
            {
                "PUSH R0"
                "IN   R0,      INP_GamepadButtonR"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 260, data);

            select_gamepad (DEBUG_GAMEPAD);
            break;

        ////////////////////////////////////////////////////////////////////////////////
        //
        // MODE_CAR: if selected, CAR ports and their values will be
        // displayed
        //
        case MODE_CAR:
            print_zoomed_at (464, 0, "CAR port value", 1.0);
            select_region   (region_divider_h);
            draw_region_at  (464, 20);
            draw_region_at  (560, 20);

            print_at (464, 20, "Connect:");
            asm
            {
                "PUSH R0"
                "IN   R0,      CAR_Connected"
                "MOV  {value}, R0"
                "POP  R0"
            }

            if (value        == 0)
            {
                print_at (560, 20, "false");
            }
            else
            {
                print_at (560, 20, "true");
            }

            print_at (464, 40, "ROMSize:");
            asm
            {
                "PUSH R0"
                "IN   R0,      CAR_ProgramROMSize"
                "MOV  {value}, R0"
                "POP  R0"
            }
            hexit_zoomed (560, 40, value, 0.75);

            print_at (464, 60, "#VTEX:");
            asm
            {
                "PUSH R0"
                "IN   R0,      CAR_NumberOfTextures"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 60, data);

            print_at (464, 80, "#VSND:");
            asm
            {
                "PUSH R0"
                "IN   R0,      CAR_NumberOfSounds"
                "MOV  {value}, R0"
                "POP  R0"
            }
            itoa (value, data, 10);
            print_at (560, 80, data);
            break;

        ////////////////////////////////////////////////////////////////////////////////
        //
        // MODE_MEM: if selected, the MEM port and connected MEMCard data
        // will be displayed, with similar memory-adjustment controls available
        //
        case MODE_MEM:
            print_zoomed_at (464, 0, "MEM port value", 1.0);
            select_region   (region_divider_h);
            draw_region_at  (464, 20);
            draw_region_at  (560, 20);

            asm
            {
                "PUSH R0"
                "IN   R0,      MEM_Connected"
                "MOV  {value}, R0"
                "POP  R0"
            }

            if (value             == 0)
            {
                print_at (464, 20, "Connect:");
                print_at (560, 20, "false");
            }
            else
            {
                address            = (int *) 0x30000000;
                print_at (464, 20, address); // display MEMC title

                for (index         = 0;
                     index        <  16;
                     index         = index + 1)
                {
                    ////////////////////////////////////////////////////////////////////
                    //
                    // display address
                    //
                    hexit_zoomed    (464, (40+(index * 20)), (viewval+index), 0.75);
                    print_zoomed_at (544, (40+(index * 20)), ":", 0.75); 

                    ////////////////////////////////////////////////////////////////////
                    //
                    // display value at address
                    //
                    address        = (int *) (viewval+index);
                    hexit_zoomed (560, (40+(index * 20)), *(address), 0.75);
                }
            }
            break;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // restore previous texture and region selection
    //
    select_texture (previous_texture);
    select_region  (previous_region);
}
