=============================================================================
CUSTOM BIOS: BiosWithoutLogoDebug FOR VIRCON32 CONSOLE
=============================================================================

What is this?

    This is a custom BIOS program for the Vircon32 console. Its functions
    are the same as  the standard BIOS but at the start  it shows no logo
    and plays no sound. Instead it begins execution right away. This BIOS
    is  not meant  for regular  console use.  It is  instead directed  to
    developers, who will  often do frequent changes and  tests. This BIOS
    will save  them the time  of waiting for  the logo every  single time
    they do a new test.
    
    This BIOS is a modified version of the 'BiosWithoutLogo' BIOS in  the
    ConsoleSoftware Vircon32 repository. It essentially just adds in some
    support functions (for instruction decoding) and modifies the data to
    be ultimately displayed to the error message screen.

    The intent is for it to be more useful in ASM debugging endeavours- a
    fair bit easier to see the source of the problem versus constantly in
    need of decoding the instruction data you are provided in hex.

-----------------------------------------------------------------------------

Additions

    The following is an overview of the changes made to `BiosWithoutLogo`
    for any deeper investigations:

    *  added  a  struct  called `instruction_opcode`  to  store  assembly
    instruction mneumonics that  are displayed. Also used  to display the
    memory section of the error.

    *   due   to  an   issue   with   the  Vircon32   `itoa()`   function
    (see https://github.com/vircon32/ComputerSoftware/issues/16), a fixed
    version called `itoa2()`  is present in the file that  will allow the
    display of ALL valid hexadecimal values.

    * `decode_instruction()`  takes the  instruction hex  value, provided
    immediate value, and the desired  y position and renders the assembly
    instruction. This is the main value-added workhorse of this BIOS.

-----------------------------------------------------------------------------

Modifications / Changes

    *  The  bulk  of  changes   to  existing  functions  takes  place  in
    `error_handler()`,  where we  determine not  only the  instruction at
    issue, but  we display  the previous  two leading up  to it,  and the
    following two  after it, for  a nice contextual display  of debugging
    information.

    The offset of  each instruction is also displayed, which  can be used
    with the assembler's `-g` argument.

-----------------------------------------------------------------------------

To-Do / Limitations

    * bounds  checking is  not complete  in the  current version.  If the
    prior instructions fall below the  current memory region, or the next
    instructions  are beyond  it, no  restriction is  currently performed
    (such scenarios would likely cause  invalid output or throw a machine
    access error).

    * port name  translations are not performed. You'll just  get the hex
    value of the port. Which if you  have a good reference handy won't be
    as big of a  problem. No reason this hasn't yet  been done aside from
    time. Is not a difficult task to implement.

    * obviously our decoding will not know about any of your  established
    labels. You will just see raw hex offsets. No way around this.

    * no decoding  will be done for BIOS-originating  errors, for obvious
    reasons.

    * the formatting pedant in me would love to column-align the  decoded
    output of assembly instructions, parameters.
 
-----------------------------------------------------------------------------

Embedding BIOS debug subroutines for ready access

    If you  had your own  custom debug subroutine, to  facilitate access,
    it  could  be   added  to  the  BIOS  data.  This   will  be  a  very
    implementation-specific use case, but here is what we have settled on
    doing for our purposes:

    * 3 debug subroutines (located in a file called `debug.asm`:
      * _debug: display of a word of data (in hex) at a given x and y
      * _debugmemory: display of a range of memory addresses
      * _debugregs: display of the register array
    
    * After compiling, but before  assembling, append the contents of the
    `debug.asm` to the compiler-generated assembly output:
      * `cat ../debug/debug.asm >> obj/BiosWithoutLogoDebug.asm`

    * When  assembling, add the  `-g` argument to generate  the debugging
    output file:
      * `assemble obj/BiosWithoutLogoDebug.asm -o obj/BiosWithoutLogoDebug.vbin -b -g || abort_build`
      * simple addition to make to the existing logic in `Make.sh`

    * Continue build  process as usual. Upon completion,  we can generate
    some  assembly-style defines  automatically with  the following  bash
    snippet (assumes that all the  debug routines start with `_debug` and
    there are no additional references):

        ```
        declare -a NAME
        NAME[0]=
        NAME[1]="MEM"
        NAME[2]="REGS"
        index=0
        for entry in `cat obj/BiosWithoutLogoDebug.vbin.debug | grep '\<_debug' | cut -d',' -f1,4`;
        do
			offset=$(echo "${entry}" | cut -d',' -f1)
			echo "%define DEBUG${NAME[${index}]} ${offset}"
			let index=index+1
        done
        ```
    
      * This `%define` output can be added to your own assembly files, to be
      used to call upon easily by the symbolic names:
        * `call DEBUG`
        * `call DEBUGMEM`
        * `call DEBUGREGS`

    *  If using  C, with  assembly  debug routines  (again, our  specific
    situation), writing some C wrapper functions can be done. In the case
    of our DEBUG (which takes 3  parameters- the value to display, the x,
    and the y; the updated X coordinate is returned):

        ```
        int debug (int value, int x, int y)
        {
            asm
            {
                "mov R5, {value}" // pick some high register
                "push R5"
                "mov R5, {x}"
                "push R5"
                "mov R5, {y}"
                "push R5"
                "call 0x10001D54" // the output offset from the bash snippet
                "pop R5"
                "mov {x}, R5"
            }
            return (x);
        }
        ```

-----------------------------------------------------------------------------

Credits

    All  existing credits  for the  `BiosWithoutLogo` BIOS,  with further
    modifications from:

    * Matthew Haas (@wedge1020)
    * Thomas Kastner (@t0mmyka)
    * Connor Grant (@Cgrant2)
    * Brandon Dildine (@BDildine)

    ... as part  of our spring2025 semester explorations  in our Computer
    Organization class at SUNY Corning Community College.

-----------------------------------------------------------------------------

License

    This program is free and open source. It is offered under
    the 3-Clause BSD License, which full text is the following:
    
    Copyright 2023-2024 Carra.
    All rights reserved.
    
    Redistribution and use in source and binary forms, with or
    without modification, are permitted provided that the
    following conditions are met:
    
    1. Redistributions of source code must retain the above
    copyright notice, this list of conditions and the following
    disclaimer.
    
    2. Redistributions in binary form must reproduce the above
    copyright notice, this list of conditions and the following
    disclaimer in the documentation and/or other materials
    provided with the distribution.
    
    3. Neither the name of the copyright holder nor the names of
    its contributors may be used to endorse or promote products
    derived from this software without specific prior written
    permission.
    
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
    CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
    INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
    MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
    NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
    HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
    OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
    EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
