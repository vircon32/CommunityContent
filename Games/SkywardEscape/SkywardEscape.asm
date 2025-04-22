;
; Skyward Escape- This  is a missile dodging game where  the player tries
; to  stay alive  for as  long as  possible while  missiles go  after the
; player.
;

%define playerX         0x00100000 ; defining variables
%define playerY         0x00100001
%define points          0x00100004
%define rotation        0x00100005
%define speed           0x00100006
%define objects         0x00100007
%define frame_s         0x00100008
%define frame_e         0x00100009
%define High_score      0x00100010
%define offset_x        0x00100011
%define offset_y        0x00100012
%define stored_x        0x00100013
%define stored_y        0x00100014
%define stored_a        0x00100015
%define score           0x00100016
%define object_x        0x00100100
%define object_y        0x00100200
%define object_r        0x00100300
%define object_a        0x00100400

    mov   R0, object_x
    push  R0
    call  _initialize_mem
    pop   R0
    mov   R0, object_y
    push  R0
    call  _initialize_mem
    pop   R0
    mov   R0, object_r
    push  R0
    call  _initialize_mem
    pop   R0
    mov   R0, object_a
    push  R0
    call  _initialize_mem
    pop   R0

    in    R0, TIM_CurrentTime
    out   RNG_CurrentValue, R0

    mov   R0, 0
    mov   [High_score], R0

    ; Defining textures
    mov   R0, 0.600000
    out   GPU_DrawingScaleX, R0
    out   GPU_DrawingScaleY, R0

    out   GPU_SelectedTexture, 0 ; red texture
    out   GPU_SelectedRegion, 0

    out   GPU_RegionMinX, 0     ; creating the region bounds
    out   GPU_RegionMinY, 0
    out   GPU_RegionMaxX, 200
    out   GPU_RegionMaxY, 200
    out   GPU_RegionHotSpotX, 100
    out   GPU_RegionHotSpotY, 100

    out   GPU_SelectedTexture, 1
    out   GPU_SelectedRegion, 1

    out   GPU_RegionMinX, 0
    out   GPU_RegionMinY, 0
    out   GPU_RegionMaxX, 100
    out   GPU_RegionMaxY, 100
    out   GPU_RegionHotSpotX, 50
    out   GPU_RegionHotSpotY, 50

    out   GPU_SelectedTexture, 2 ; Background Texture
    out   GPU_SelectedRegion, 2

    out   GPU_RegionMinX, 0     ; creating the region bounds
    out   GPU_RegionMinY, 0
    out   GPU_RegionMaxX, 640
    out   GPU_RegionMaxY, 360
    out   GPU_RegionHotSpotX, 320
    out   GPU_RegionHotSpotY, 180

    out   GPU_SelectedTexture, 2 ; Missile Texture
    out   GPU_SelectedRegion, 3

    out   GPU_RegionMinX, 0     ; creating the region bounds
    out   GPU_RegionMinY, 360
    out   GPU_RegionMaxX, 110
    out   GPU_RegionMaxY, 610
    out   GPU_RegionHotSpotX, 55
    out   GPU_RegionHotSpotY, 465

    out   GPU_SelectedTexture, 2 ; Coin Texture
    out   GPU_SelectedRegion, 4

    out   GPU_RegionMinX, 0     ; creating the region bounds
    out   GPU_RegionMinY, 360
    out   GPU_RegionMaxX, 110
    out   GPU_RegionMaxY, 610
    out   GPU_RegionHotSpotX, 320
    out   GPU_RegionHotSpotY, 180

    out   SPU_SelectedSound, 0
    out   SPU_SelectedChannel, 1
    out   SPU_ChannelAssignedSound, 0
    out   SPU_Command, SPUCommand_PlaySelectedChannel
    out   SPU_ChannelLoopEnabled, 1

    mov   R11, 16
    mov   R12, 9
    mov   [playerX], R11
    mov   [playerY], R12

    mov   R0, 5
    mov   [speed], R0

    mov   R1, 0  ; R1 contains our gamepad ID
    out   INP_SelectedGamepad, R1

_game_menu:
    ; Prints the main menu
    mov   R0, 5
    mov   [speed], R0
    mov   R1, 335 ; hanger X
    mov   R2, 150 ; hanger Y
    mov   R3, 10.000000 ; hanger scale
    mov   R4, 0.600000  ; plane scale

    mov   R6, 0xFFE8A200
    out   GPU_ClearColor, R6
    out   GPU_Command, GPUCommand_ClearScreen

    mov   R0, R3
    out   GPU_DrawingScaleX, R0
    out   GPU_DrawingScaleY, R0

    mov   R0, R4
    out   GPU_DrawingScaleX, R0
    out   GPU_DrawingScaleY, R0
    out   GPU_SelectedTexture, 2 ; plane texture
    out   GPU_SelectedRegion, 2

    out   GPU_DrawingPointX, 320 ; set X coordinate
    out   GPU_DrawingPointY, 180 ; set Y coordinate
    out   GPU_Command, GPUCommand_DrawRegion

    out   GPU_DrawingScaleX, R0
    out   GPU_DrawingScaleY, R0
    out   GPU_SelectedTexture, 0 ; plane texture
    out   GPU_SelectedRegion, 0

    out   GPU_DrawingPointX, 320 ; set X coordinate
    out   GPU_DrawingPointY, 180 ; set Y coordinate
    out   GPU_Command, GPUCommand_DrawRegionRotozoomed

    mov   R0, [High_score]
    push  R0
    mov   R0, 315
    push  R0
    mov   R0, 60
    push  R0
    call  _print_Num
    pop   R0
    pop   R0
    pop   R0

    wait
    in    R10, INP_GamepadButtonStart ; Press enter to start the game
    ieq   R10, 1
    jf    R10, _game_menu

_game_start:
    ; makes it look like the plane is taking off
    wait
    mov   R6, 0xFFE8A200
    out   GPU_ClearColor, R6
    out   GPU_Command, GPUCommand_ClearScreen

    mov   R0, R3
    out   GPU_DrawingScaleX, R0
    out   GPU_DrawingScaleY, R0

    ; Make buttons go transparent
    out   GPU_SelectedTexture, 1 ; land texture
    out   GPU_SelectedRegion, 1

    out   GPU_DrawingPointX, R1 ; set X coordinate
    out   GPU_DrawingPointY, R2 ; set Y coordinate
    out   GPU_Command, GPUCommand_DrawRegionRotozoomed

    mov   R0, R4
    out   GPU_DrawingScaleX, R0
    out   GPU_DrawingScaleY, R0
    out   GPU_SelectedTexture, 0 ; plane texture
    out   GPU_SelectedRegion, 0

    out   GPU_DrawingPointX, 320 ; set X coordinate
    out   GPU_DrawingPointY, 180 ; set Y coordinate
    out   GPU_Command, GPUCommand_DrawRegionRotozoomed

    iadd  R2,2
    mov   R5, R2
    igt   R5, 300
    jf    R5, _game_start_shrink
    fsub  R3,0.02

_game_start_shrink:
    mov   R5, R2
    ilt   R5, 650
    jt    R5, _game_start

    ; spawn a missile at the start so the player isnt lonely
    call  _spawn_missile
    in    R0, TIM_CurrentTime
    mov   [frame_s], R0

__while_loop:                   ; main game loop
    wait
    mov   R6, 0xFFE8A200
    out   GPU_ClearColor, R6
    out   GPU_Command, GPUCommand_ClearScreen

__inner_loop:
    out   GPU_SelectedTexture, 1 ; land texture
    out   GPU_SelectedRegion, 1

    out   GPU_SelectedTexture, 0 ; plane texture
    out   GPU_SelectedRegion, 0

    mov   R13, [rotation]
    out   GPU_DrawingAngle, R13
    ;;;;;;;;;;;;;;;;;
    ;;; Always print player at front of screen
    out   GPU_DrawingPointX, 320 ; set X coordinate
    out   GPU_DrawingPointY, 180 ; set Y coordinate
    out   GPU_Command, GPUCommand_DrawRegionRotozoomed

    ; Getting offsets based on player position
    mov   R0, [object_x]
    mov   R1, [object_y]
    mov   R2, [speed]
    mov   R3, [rotation]
    cif   R2
    sin   R3
    fmul  R2, R3
    cfi   R2
    imul  R2, -1
    mov   R6, R2 ; storing X value

    mov   R2, [speed]
    cif   R2
    mov   R3, [rotation]
    sin   R3
    mov   R4, 2.0
    pow   R3, R4
    mov   R5, 1.0
    fsub  R5, R3
    mov   R4, 0.5
    pow   R5, R4
    fmul  R2, R5

    cfi   R2
    mov   R3, [rotation]
    mov   R4, R3
    fabs  R4
    fgt   R4, 1.625
    mov   R5, R3
    fabs  R5
    flt   R5, 4.875
    and   R4,R5
    jf    R4, _spin_float_stuff
    imul  R2, -1

_spin_float_stuff:
    imul  R2, 1

    mov   [offset_x], R6
    mov   [offset_y], R2

    ; Printing the missiles then checking the collisions
    call  _print_missiles
    call  _missiles_missile_col
    call  _check_collisions_player

    mov   R2, R0
    igt   R2, 640
    jf    R2, _screen_width_max
    mov   R0, 640

_screen_width_max:
    mov   R2, R0
    ilt   R2, 0
    jf    R2, _screen_width_min
    mov   R0, 0

_screen_width_min:
    mov   R2, R1
    igt   R2, 360
    jf    R2, _screen_height_max
    mov   R1, 360

_screen_height_max:
    mov   R2, R1
    ilt   R2, 0
    jf    R2, _screen_height_min
    mov   R1, 0

_screen_height_min:

_conditionals:
    mov   R12, [speed]
    mov   R13, [rotation]

    ; spawns a new missile every second
    mov   R0, [frame_s]
    in    R1, TIM_CurrentTime
    isub  R1, R0
    idiv  R1, 3

    ; Spawning missiles based on how long player has lived
    mov   R2, [objects]
    igt   R1, R2
    jf    R1, _left
    ; checking if max number of missiles is sent out
    mov   R2, [objects]
    igt   R2, 99
    jt    R2, _left

    call  _spawn_missile

_left:
    in    R10, INP_GamepadLeft ; state is loaded into R10
    mov   R4,  0               ; put a 0 in R4
    ilt   R4,  R10             ; if R4(0) < R10, R4 has a 1
    jf    R4,  _right          ; if R4 is 0, goto _right

    fsub  R13, 0.10              ; decrement R2 (X value)
    jt    R4,  _movement_done

_right:
    in    R10, INP_GamepadRight
    mov   R4,  0
    ilt   R4,  R10
    jf    R4,  _movement_done
    fadd  R13, 0.10             ; if right, add 1 to X (R2)

_movement_done:
    fmod  R13, 6.5
    mov   [rotation], R13
    jmp   __while_loop

__end_while_loop:
    hlt

_print_Num:
    ; prints number
    push  BP
    mov   BP, SP
    push  R0
    in    R0, GPU_SelectedTexture
    push  R0
    in    R0, GPU_SelectedRegion
    push  R0
    push  R1
    push  R2
    push  R3
    push  R4
    push  R5
    push  R6
    push  R7
    push  R8
    push  R9
    push  R10
    push  R11
    push  R12
    push  R13
    ; Prints the number inputted at the x/y with a buffer so it can be re-used
    ; figures out how many digits in num
    out   GPU_SelectedTexture, -1

    mov   R7, 0
    mov   R5, [BP+4]

_digit_loop_1024:
    mov   R6, R5
    igt   R6, 0
    jf    R6, _digit_loop_1024e
    idiv  R5, 10
    iadd  R7, 1
    jmp   _digit_loop_1024

_digit_loop_1024e:
    mov   R5, [BP+4]
    mov   R4, [BP+3]
    mov   R3, [BP+2]

    mov   R6, R7
    isub  R6, 1
    imul  R6, 10
    iadd  R4, R6
    mov   R6, 20 ; buffer
    iadd  R4, R6
    mov   [BP+4], R4

_print_num_1024: ; printing that number of digits at the spot
    mov   R6, R5
    imod  R6, 10
    iadd  R6, 48

    out   GPU_SelectedRegion, R6
    out   GPU_DrawingPointX, R4
    out   GPU_DrawingPointY, R3
    out   GPU_Command, GPUCommand_DrawRegion

    idiv  R5, 10
    isub  R7, 1
    isub  R4, 10
    mov   R8, R7
    ilt   R8, 1
    jf    R8, _print_num_1024

    pop   R13
    pop   R12
    pop   R11
    pop   R10
    pop   R9
    pop   R8
    pop   R7
    pop   R6
    pop   R5
    pop   R4
    pop   R3
    pop   R2
    pop   R1
    pop   R0
    out   GPU_SelectedRegion, R0
    pop   R0
    out   GPU_SelectedTexture, R0
    pop   R0
    mov   SP, BP
    pop   BP
    ret

_print_missiles:
    ; changes missiles x/y then prints it out
    push  BP
    mov   BP, SP
    push  R0
    in    R0, GPU_SelectedTexture
    push  R0
    in    R0, GPU_SelectedRegion
    push  R0
    in    R0, GPU_DrawingScaleX
    push  R0
    in    R0, GPU_DrawingScaleY
    push  R0
    push  R1
    push  R2
    push  R3
    push  R4
    push  R5
    push  R6
    push  R7
    push  R8
    push  R9
    push  R10
    push  R11
    push  R12
    push  R13
    mov   R2, 0.15
    out   GPU_DrawingScaleX, R2
    out   GPU_DrawingScaleY, R2
    out   GPU_SelectedTexture, 2 ; Missile texture
    out   GPU_SelectedRegion, 3

    mov   R4, object_x
    mov   R5, object_y
    mov   R9, object_r
    mov   R6, [objects]
    mov   R7, object_a
    iadd  R9, R6
    iadd  R4, R6
    iadd  R5, R6

    ; add to  rotation aswell

    ; player x 320
    ; player y 180

_print_missiles_loop:
    mov   R8, R6
    ilt   R8, 1
    jt    R8, _print_missiles_loop_end
    isub  R4, 1
    isub  R5, 1
    isub  R9, 1
    mov   R0, [R4]
    mov   R1, [offset_x]
    iadd  R0, R1
    mov   [R4], R0
    mov   R2, [R5]
    mov   R3, [offset_y]
    iadd  R2, R3
    mov   [R5], R2
    mov   R1, R0 ; object x
    mov   R3, R2 ; object y
    cif   R1
    cif   R3

    mov   R11, 320.0 ; moving the position of the players x to R9
    mov   R10, 180.0 ; moving the position of the players y to R10

    fsub  R11, R1
    fsub  R10, R3

    mov   R3, R11
    feq   R3, 0.0
    jf    R3, _atan2
    mov   R11, 1

_atan2:
    mov   R3, R10
    feq   R3, 0.0
    jf    R3, _atan3
    mov   R10, 1

_atan3:
    atan2 R10, R11
    mov   R1, R10
    flt   R1, 0
    jf    R1, _not_neg
    fadd  R10, 6.2832

_not_neg:
    fadd  R10, 1.625


    fmod  R10, 6.5
    mov   R11, [R9] ; previous arctan value
    fmod  R11, 6.5

    ; tween arctan value
    mov   R12, R10
    flt   R12, R11
    jt    R12, _smaller_rot
    fadd  R11, 0.03
    jmp   _end_rot

_smaller_rot:
    mov   R12, R11
    push  R12
    mov   R12, 100
    push  R12
    push  R12
    ; call _print_float
    pop   R12
    pop   R12
    pop   R12
    fsub  R11, 0.03

_end_rot:
    mov   [R9], R11
    mov   R10, R11

    mov   R11, 0
    push  R11
    push  R11
    mov   R11, R10
    push  R11
    call  _change_position_m
    pop   R11
    pop   R11; Y Change
    pop   R12; X Change

    isub  R0, R12
    isub  R2, R11
    mov   [R4], R0
    mov   [R5], R2
    out   GPU_DrawingAngle , R10

    out   GPU_DrawingPointX, R0 ; set X coordinate
    out   GPU_DrawingPointY, R2 ; set Y coordinate
    out   GPU_Command, GPUCommand_DrawRegionRotozoomed

_print_missiles_conditional:
    isub  R6, 1
    jmp   _print_missiles_loop

_print_missiles_loop_end:
    pop   R13
    pop   R12
    pop   R11
    pop   R10
    pop   R9
    pop   R8
    pop   R7
    pop   R6
    pop   R5
    pop   R4
    pop   R3
    pop   R2
    pop   R1
    pop   R0
    out   GPU_DrawingScaleY, R0
    pop   R0
    out   GPU_DrawingScaleX, R0
    pop   R0
    out   GPU_SelectedRegion, R0
    pop   R0
    out   GPU_SelectedTexture, R0
    pop   R0
    mov   SP, BP
    pop   BP
    ret

_change_position_m:
    ; changes missiles position
    push  BP
    mov   BP, SP
    push  R0
    push  R1
    push  R2
    push  R3
    push  R4
    push  R5
    push  R6

    mov   R2, 4
    mov   R3, [BP+2] ; rotation
    cif   R2
    sin   R3
    fmul  R2, R3
    cfi   R2
    imul  R2, -1
    mov   R6, R2 ; storing X value

    mov   R2, 4
    cif   R2
    mov   R3, [BP+2]; rotation
    sin   R3
    mov   R4, 2.0
    pow   R3, R4
    mov   R5, 1.0
    fsub  R5, R3
    mov   R4, 0.5
    pow   R5, R4
    fmul  R2, R5
    cfi   R2

    mov   R4, [BP+2]
    fgt   R4, 1.625
    mov   R5, [BP+2]
    fabs  R5
    flt   R5, 4.875
    and   R4,R5
    jf    R4, _spin_float_stuff1
    imul  R2, -1

_spin_float_stuff1:
    mov   [BP+4], R6
    mov   [BP+3], R2

    pop   R6
    pop   R5
    pop   R4
    pop   R3
    pop   R2
    pop   R1
    pop   R0
    mov   SP, BP
    pop   BP
    ret

_check_collisions_player: ; Itterates through all missiles to check for collisions with player
    ; if collisions are found, end game/go to start screen, reset all memory
    push  BP
    mov   BP, SP
    push  R0
    push  R1
    push  R2
    push  R3
    push  R4
    push  R5
    push  R6
    push  R7
    push  R8
    push  R9
    push  R10
    push  R11
    push  R12
    push  R13

    mov   R13, [objects]
    mov   R4, object_x
    mov   R5, object_y
    mov   R7, object_a
    mov   R6, [objects]
    ; player x 320
    ; player y 180

    mov   R12, 360 ; player is only 80 pixels wide/tall
    mov   R11, 280 ;
    mov   R2, 220 ; player max Y
    mov   R10, 140 ; player min Y

_col_missiles_loop:
    mov   R8, R6
    ilt   R8, 1
    jt    R8, _col_missiles_loop_end

    ; Checking if the missile is alive
    mov   R9, [R7]
    jf    R9, _col_missiles_conditional
    isub  R6, 1 ; subtract from the amound of missiles left to find

    ;;;;;;;;;;;;;;;;;;;;;
    ;; Checking player X
    mov   R0, [R4]
    ilt   R0, R12
    jf    R0, _col_missiles_conditional
    mov   R0, [R4]
    igt   R0, R11
    jf    R0, _col_missiles_conditional
    ;;;;;;;;;;;;;;;;;;;;
    ;; Checking player Y
    mov   R0, [R5]
    ilt   R0, R2
    jf    R0, _col_missiles_conditional
    mov   R0, [R5]
    igt   R0, R10
    jf    R0, _col_missiles_conditional

    jmp   _game_over

_col_missiles_conditional:
    iadd  R4, 1
    iadd  R5, 1
    iadd  R7, 1
    jmp   _col_missiles_loop

_col_missiles_loop_end:
    pop   R13
    pop   R12
    pop   R11
    pop   R10
    pop   R9
    pop   R8
    pop   R7
    pop   R6
    pop   R5
    pop   R4
    pop   R3
    pop   R2
    pop   R1
    pop   R0
    mov   SP, BP
    pop   BP
    ret

_initialize_mem:
    ; sets 100 mem addresses to 0
    push  BP
    mov   BP, SP
    push  R0
    push  R1
    push  R2
    push  R3

    mov   R0, [BP+2] ; memory address
    mov   R1, 99
    mov   R3, 0

_start_init_mem_loop:
    mov   R2, R1
    ige   R2, 1
    jf    R2, _end_init_mem_loop
    mov   [R0], R3
    iadd  R0, 1
    isub  R1, 1
    jmp   _start_init_mem_loop

_end_init_mem_loop:
    pop   R3
    pop   R2
    pop   R1
    pop   R0
    mov   SP, BP
    pop   BP
    ret

_spawn_missile: ; Creates a missile outside the players view
    push  BP
    mov   BP, SP
    push  R0
    push  R1
    push  R2
    push  R3
    push  R4
    push  R5
    push  R6
    push  R7
    push  R8
    push  R9
    push  R10
    push  R11

    mov   R0, [objects]
    iadd  R0, 1
    mov   [objects], R0
    mov   R0, 0
    mov   R3, object_a

_start_spawn_loop:
    mov   R4, [R3]
    jt    R4, _spawn_loop_conditional
    ; Jumps if object_a =1 aka the object is alive

    ; setting the object to alive
    mov   R4, 1
    mov   [R3], R4

    mov   R1, object_x
    mov   R2, object_y
    mov   R5, object_r
    iadd  R1, R0
    iadd  R2, R0
    iadd  R5, R0
    mov   R3, 0 ; spawn x
    mov   R4, 0 ; spawn y

    ; chooses random side to spawn missiles on

    mov   R4, -50
    ; check if top/bot
    in    R0, RNG_CurrentValue
    imod  R0, 4
    mov   R6, R0
    ieq   R6, 0
    jt    R6, _set_bot
    mov   R6, R0
    ieq   R6, 1
    jt    R6, _set_top
    mov   R6, R0
    ieq   R6, 2
    jt    R6, _set_left
    mov   R6, R0
    ieq   R6, 3
    jt    R6, _set_right
    ; RANDOMIZING THE SPAWN

_set_top:
    mov   R4, -120
    in    R0, RNG_CurrentValue
    imod  R0, 600
    mov   R3, R0
    jmp   _set_end

_set_bot:
    mov   R4, 400
    in    R0, RNG_CurrentValue
    imod  R0, 600
    mov   R3, R0
    jmp   _set_end

_set_left:
    mov   R3, -30 ; moving 0 to x value
    in    R0, RNG_CurrentValue
    imod  R0, 360
    mov   R4, R0
    jmp   _set_end

_set_right:
    mov   R3, 680 ; moving 0 to x value
    in    R0, RNG_CurrentValue
    imod  R0, 360
    mov   R4, R0
    jmp   _set_end

_set_end:
    cif   R3
    cif   R4

    mov   R11, 320.0 ; moving the position of the players x to R9
    mov   R10, 180.0 ; moving the position of the players y to R10

    fsub  R11, R3
    fsub  R10, R4

    atan2 R10, R11
    mov   R11, R10
    flt   R11, 0
    jf    R11, _not_neg_s
    fadd  R10, 6.2832

_not_neg_s:
    fadd  R10, 1.625

    mov   [R5], R10

    cfi   R3
    cfi   R4
    mov   [R1], R3    ; setting X to start value
    mov   [R2], R4    ; setting Y to new value
    jmp   _end_spawn_loop

_spawn_loop_conditional:
    iadd  R3, 1
    iadd  R0, 1
    jmp   _start_spawn_loop

_end_spawn_loop:
    pop   R11
    pop   R10
    pop   R9
    pop   R8
    pop   R7
    pop   R6
    pop   R5
    pop   R4
    pop   R3
    pop   R2
    pop   R1
    pop   R0
    mov   SP, BP
    pop   BP
    ret

_missiles_missile_col:
    ; Checks the collisions between missiles
    push  BP
    mov   BP, SP
    push  R0
    push  R1
    push  R2
    push  R3
    push  R4
    push  R5
    push  R6
    push  R7
    push  R8
    push  R9
    push  R10
    push  R11
    push  R12
    push  R13

    mov   R13, [objects]
    mov   R12, object_a
    mov   R11, object_x
    mov   R10, object_y
    mov   R8, object_r
    mov   R9, 0 ; found objects count

_col_mxm_loop:
    mov   R0, [R12]
    jf    R0, _col_mxm_loop_cond ; missile is not alive, go to next

    iadd  R9, 1 ; add to the found object counter
    mov   R3, R9
    mov   R5, [object_x]
    mov   R4, [object_y]

    ; storing the registers for later use
    mov   [stored_a],R12
    mov   [stored_x],R11
    mov   [stored_y],R10

    iadd  R12, 1 ; getting the next objects stats
    iadd  R11, 1
    iadd  R10, 1

    mov   R0, 70
    push  R0
    mov   R0, [R8]
    fmod  R8, 1.5708
    push  R0
    call  _cos_int
    pop   R0
    pop   R6

    mov   R0, 70
    push  R0
    mov   R0, [R8]
    fmod  R8, 1.5708
    push  R0
    call  _sin_int
    pop   R0
    pop   R7

_inner_mxm_loop:
    mov   R0, [R12]
    jf    R0, _inner_mxm_loop_c ; missile is not alive, go to next
    iadd  R3, 1

    mov   R2, R5
    isub  R2, 55
    isub  R2, R6
    mov   R1, [R11] ; object_x
    igt   R1, R2
    jf    R1, _inner_mxm_loop_c

    mov   R2, R5
    iadd  R2, 55
    iadd  R2, R6
    mov   R1, [R11] ; object_x
    ilt   R1, R2
    jf    R1, _inner_mxm_loop_c

    mov   R2, R4
    isub  R2, 65
    isub  R2, R7
    mov   R1, [R10] ; object_y
    igt   R1, R2
    jf    R1, _inner_mxm_loop_c

    mov   R2, R4
    iadd  R2, 65
    iadd  R2, R7
    mov   R1, [R10] ; object_y
    ilt   R1, R2
    jf    R1, _inner_mxm_loop_c


    mov   R0, 0
    mov   [R12], R0
    mov   R12,[stored_a]
    mov   [R12], R0
    isub  R13, 2
    mov   [objects],R13
    mov   R11,[stored_x]
    mov   R10,[stored_y]
    jmp   _col_mxm_loop_cond

_inner_mxm_loop_c:
    iadd  R12, 1
    iadd  R11, 1
    iadd  R10, 1
    mov   R1, R3
    ige   R1, R13
    jf    R1, _inner_mxm_loop

_inner_mxm_loop_e:
    mov   R12,[stored_a]
    mov   R11,[stored_x]
    mov   R10,[stored_y]

_col_mxm_loop_cond:
    iadd  R12, 1
    iadd  R11, 1
    iadd  R10, 1
    iadd  R8, 1
    mov   R1, R9
    ige   R1, R13
    jf    R1, _col_mxm_loop

_col_mxm_loop_end:
    pop   R13
    pop   R12
    pop   R11
    pop   R10
    pop   R9
    pop   R8
    pop   R7
    pop   R6
    pop   R5
    pop   R4
    pop   R3
    pop   R2
    pop   R1
    pop   R0
    mov   SP, BP
    pop   BP
    ret

_arctan:
    ; does the taylor expansion of arctan
    push  BP
    mov   BP, SP
    push  R0
    push  R1
    push  R2
    push  R3
    push  R4
    push  R5
    push  R6
    push  R7
    push  R8
    push  R9

    mov   R9, [BP+2] ; x
    mov   R5, R9
    feq   R5, 0

    mov   R8, R9     ; running total
    mov   R7, 3.0    ; has to be a float
    mov   R5, R9     ; moving x to new register
    pow   R5, R7     ; x^3
    fdiv  R5, 3.0    ; (x^3)/3
    fsub  R8, R5

    mov   R7, 5.0
    mov   R5, R9     ; moving x to new register
    pow   R5, R7     ; x^5
    fdiv  R5, 5.0    ; (x^5)/5
    fadd  R8, R5

    mov   R7, 7.0
    mov   R5, R9     ; moving x to new register
    pow   R5, R7     ; x^7
    fdiv  R5, 7.0    ; (x^7)/7
    fsub  R8, R5

    mov   [BP+2], R8
    pop   R9
    pop   R8
    pop   R7
    pop   R6
    pop   R5
    pop   R4
    pop   R3
    pop   R2
    pop   R1
    pop   R0
    mov   SP, BP
    pop   BP
    ret

_game_over:
    ; shows game over screen and resets memory before restarting
    push  BP
    mov   BP, SP
    push  R0
    push  R1
    push  R2

    call  _game_over_menu
    ; show end game screen

    mov   R0, 0.0
    mov   [rotation], R0
    out   GPU_DrawingAngle, R0
    call  _reset_mem
    mov   R0, 0
    mov   [objects], R0

    pop   R2
    pop   R1
    pop   R0
    mov   SP, BP
    pop   BP
    jmp   _game_menu

_game_over_menu:
    push  BP
    mov   BP, SP
    push  R0
    push  R1
    push  R2
    push  R3
    push  R4
    push  R5
    push  R6
    push  R7
    push  R8
    push  R9
    push  R10
    push  R11
    push  R12
    push  R13

    mov   R7, 320
    mov   R8, 520
    mov   R0, 3.0
    out   GPU_DrawingScaleX, R0
    out   GPU_DrawingScaleY, R0
    mov   R13, 0
    out   GPU_DrawingAngle, R13

    ; Change what it prints out based on if its a new high score or not
    in    R0, TIM_CurrentTime
    mov   R1, [frame_s]
    isub  R0, R1
    imul  R0, 13
    mov   R1, [High_score]
    mov   [score], R0
    mov   R2, R0
    mov   R12, _print_ts
    mov   R13, _print_score
    mov   R11, _print_sec
    mov   R9, _print_game_end
    ; Set new high score
    ilt   R2, R1
    jt    R2, _game_over_menu_loop
    mov   [High_score], R0
    mov   R13, _print_score_n

_game_over_menu_loop:
    wait
    mov   R6, 0xFFE8A200
    out   GPU_ClearColor, R6
    out   GPU_Command, GPUCommand_ClearScreen

    out   GPU_SelectedTexture, 0 ; plane texture
    out   GPU_SelectedRegion, 0

    out   GPU_DrawingPointX, R7 ; set X coordinate
    out   GPU_DrawingPointY, R8 ; set Y coordinate
    out   GPU_Command, GPUCommand_DrawRegionRotozoomed

    push  R9
    mov   R0, 275
    push  R0
    mov   R0, 100
    push  R0
    call  _print_lines
    pop   R0
    pop   R0
    pop   R0

    push  R13
    mov   R0, 200
    push  R0
    mov   R0, 170
    push  R0
    call  _print_lines
    pop   R0
    pop   R0
    pop   R0

    mov   R0, [score]
    push  R0
    mov   R0, 340
    push  R0
    mov   R0, 170
    push  R0
    call  _print_Num
    pop   R0
    pop   R0
    pop   R0

    ; Printing time survived
    push  R12
    mov   R0, 200
    push  R0
    mov   R0, 190
    push  R0
    call  _print_lines
    pop   R0
    pop   R0
    pop   R0

    mov   R1, [score]
    idiv  R1, 13
    push  R1
    mov   R0, 340
    push  R0
    mov   R0, 190
    push  R0
    call  _print_Num
    pop   R0
    pop   R0
    pop   R3

    ; Printing time survived
    push  R11
    iadd  R3, 20
    push  R3
    mov   R0, 190
    push  R0
    call  _print_lines
    pop   R0
    pop   R0
    pop   R0

    mov   R5, _print_enter
    push  R5
    mov   R0, 265
    push  R0
    mov   R0, 320
    push  R0
    call  _print_lines
    pop   R0
    pop   R0
    pop   R0

    isub  R8, 1
    in    R10, INP_GamepadButtonStart ; Press enter to start the game
    ieq   R10, 1
    jf    R10, _game_over_menu_loop

_game_over_menu_end_loop:
    pop   R13
    pop   R12
    pop   R11
    pop   R10
    pop   R9
    pop   R8
    pop   R7
    pop   R6
    pop   R5
    pop   R4
    pop   R3
    pop   R2
    pop   R1
    pop   R0
    mov   SP, BP
    pop   BP
    ret

_reset_mem:
    ; re-setting missile memory addresses
    push  BP
    mov   BP, SP
    push  R0
    mov   R0, object_x
    push  R0
    call  _initialize_mem
    pop   R0
    mov   R0, object_y
    push  R0
    call  _initialize_mem
    pop   R0
    mov   R0, object_r
    push  R0
    call  _initialize_mem
    pop   R0
    mov   R0, object_a
    push  R0
    call  _initialize_mem
    pop   R0
    pop   R0
    mov   SP, BP
    pop   BP
    ret

_cos_int:
    ; does the cos opperation for an inputted int
    push  BP
    mov   BP, SP
    push  R0
    push  R1
    push  R2
    push  R3
    push  R4
    push  R5
    push  R6
    push  R7
    push  R8
    push  R9

    mov   R2, [BP+3]
    cif   R2
    mov   R3, [BP+2] ; rotation
    sin   R3
    mov   R4, 2.0
    pow   R3, R4
    mov   R5, 1.0
    fsub  R5, R3
    mov   R4, 0.5
    pow   R5, R4
    fmul  R2, R5
    cfi   R2

    mov   R4, [BP+2]
    fgt   R4, 1.625
    mov   R5, [BP+2]
    fabs  R5
    flt   R5, 4.875
    and   R4,R5
    jf    R4, _spin_float_stuff2
    imul  R2, -1

_spin_float_stuff2:
    mov   [BP+3],R2
    pop   R9
    pop   R8
    pop   R7
    pop   R6
    pop   R5
    pop   R4
    pop   R3
    pop   R2
    pop   R1
    pop   R0
    mov   SP, BP
    pop   BP
    ret

_sin_int:
    ; does the sin opperation for an inputted int
    push  BP
    mov   BP, SP
    push  R2
    push  R3
    mov   R2, [BP+3]
    mov   R3, [BP+2]
    cif   R2
    sin   R3
    fmul  R2, R3
    cfi   R2
    imul  R2, -1
    mov   [BP+3], R2
    pop   R3
    pop   R2
    mov   SP, BP
    pop   BP
    ret

_print_lines:
    ; prints lines
    push  BP
    mov   BP, SP
    push  R0
    push  R1
    push  R2
    push  R3
    push  R4
    push  R5
    push  R6
    push  R7
    push  R8
    push  R9
    push  R10
    push  R11
    push  R12
    push  R13
    ; Prints the inputted string at the x and y
    out   GPU_SelectedTexture, -1
    mov   R5, [BP+4] ; string
    isub  R5, 1
    mov   R1, [BP+3]
    isub  R1, 10
    mov   R2, [BP+2]

_print_lines_top:
    iadd  R1, 10
    iadd  R5, 1
    mov   R6, [R5]

    mov   R7, R6
    ieq   R7, 0
    jt    R7, _print_lines_top_end

    out   GPU_SelectedRegion, R6
    out   GPU_DrawingPointX, R1
    out   GPU_DrawingPointY, R2
    out   GPU_Command, GPUCommand_DrawRegion

    jmp   _print_lines_top

_print_lines_top_end:
    pop   R13
    pop   R12
    pop   R11
    pop   R10
    pop   R9
    pop   R8
    pop   R7
    pop   R6
    pop   R5
    pop   R4
    pop   R3
    pop   R2
    pop   R1
    pop   R0
    mov   SP, BP
    pop   BP
    ret

_print_ts:
    string "Time survived:"

_print_score_n:
    string "New High Score!:"

_print_score:
    string "          Score:"

_print_sec:
    string "seconds"

_print_game_end:
    string "You Died!"

_print_enter:
    string "PRESS ENTER"
