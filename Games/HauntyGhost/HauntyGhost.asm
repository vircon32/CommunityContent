%define BIOS             -1
%define CLEAR            GPUCommand_ClearScreen
%define TEXTURE          GPU_SelectedTexture
%define REGION           GPU_selectedRegion
%define DRAWX            GPU_DrawingPointX
%define DRAWY            GPU_DrawingPointY
%define DRAWREG          GPUCommand_DrawRegion
%define HIGH_SCORE       0x00101111
%define PILLAR_REG_ARR   0x00100000
%define PILLARX_ARR      0x00110000
%define BACKGROUNDX_ARR  0x00111000
%define BORDER_ARR       0x00111100
%define ANTI_HOLD        R0             ; 1 for hold, 0 for release
%define PLAYERY          R1
%define TEMP_A           R2
%define TEMP_B           R3
%define JUMP_TO          R4
%define FALL_SPEED       R5
%define COUNTER          R6
%define ARR_CYCLER       R7
%define MENU_BOOL        R11
%define ARR_CYCLER2      R8
%define COLLISION_TOP    R9
%define COLLISION_BOTTOM R10
%define CURRENT_SCORE    R12
%define X                R13

    out   INP_SelectedGamepad, 0

    in    TEMP_A, TIM_CurrentTime
    out   RNG_CurrentValue, TEMP_A

    mov   ARR_CYCLER, HIGH_SCORE
    mov   TEMP_A, 0
    mov   [ARR_CYCLER], TEMP_A

;defining bottom border

    out   TEXTURE, 5
    out   REGION, 25
    out   GPU_RegionMinX, 0
    out   GPU_RegionMinY, 0
    out   GPU_RegionMaxX, 640
    out   GPU_RegionMaxY, 360
    out   GPU_RegionHotSpotX, 0
    out   GPU_RegionHotSpotY, 0

    out   TEXTURE, 6
    out   REGION, 26
    out   GPU_RegionMinX, 0
    out   GPU_RegionMinY, 0
    out   GPU_RegionMaxX, 640
    out   GPU_RegionMaxY, 360
    out   GPU_RegionHotSpotX, 0
    out   GPU_RegionHotSpotY, 0

    out   TEXTURE, 7
    out   REGION, 27
    out   GPU_RegionMinX, 0
    out   GPU_RegionMinY, 0
    out   GPU_RegionMaxX, 640
    out   GPU_RegionMaxY, 360
    out   GPU_RegionHotSpotX, 0
    out   GPU_RegionHotSpotY, 0

;defining bottom border

    out   TEXTURE, 4
    out   REGION, 21
    out   GPU_RegionMinX, 0
    out   GPU_RegionMinY, 320
    out   GPU_RegionMaxX, 640
    out   GPU_RegionMaxY, 360
    out   GPU_RegionHotSpotX, 0
    out   GPU_RegionHotSpotY, 320

;defining background and background animations

    out   TEXTURE, 1
    out   REGION, 18
    out   GPU_RegionMinX, 0
    out   GPU_RegionMinY, 0
    out   GPU_RegionMaxX, 640
    out   GPU_RegionMaxY, 319
    out   GPU_RegionHotSpotX, 0
    out   GPU_RegionHotSpotY, 0

    out   TEXTURE, 2
    out   REGION, 19
    out   GPU_RegionMinX, 0
    out   GPU_RegionMinY, 0
    out   GPU_RegionMaxX, 640
    out   GPU_RegionMaxY, 319
    out   GPU_RegionHotSpotX, 0
    out   GPU_RegionHotSpotY, 0

    out   TEXTURE, 3
    out   REGION, 20
    out   GPU_RegionMinX, 0
    out   GPU_RegionMinY, 0
    out   GPU_RegionMaxX, 640
    out   GPU_RegionMaxY, 319
    out   GPU_RegionHotSpotX, 0
    out   GPU_RegionHotSpotY, 0

;defining player and player animation

    out   TEXTURE, 0
    out   REGION, 14
    out   GPU_RegionMinX, 592
    out   GPU_RegionMinY, 15
    out   GPU_RegionMaxX, 624
    out   GPU_RegionMaxY, 46
    out   GPU_RegionHotSpotX, 608
    out   GPU_RegionHotSpotY, 30

    out   TEXTURE, 0
    out   REGION, 15
    out   GPU_RegionMinX, 592
    out   GPU_RegionMinY, 63
    out   GPU_RegionMaxX, 624
    out   GPU_RegionMaxY, 94
    out   GPU_RegionHotSpotX, 608
    out   GPU_RegionHotSpotY, 78

    out   TEXTURE, 0
    out   REGION, 16
    out   GPU_RegionMinX, 592
    out   GPU_RegionMinY, 111
    out   GPU_RegionMaxX, 624
    out   GPU_RegionMaxY, 142
    out   GPU_RegionHotSpotX, 608
    out   GPU_RegionHotSpotY, 126

;defining pillars

    mov   R0, 1
    mov   R1, 12
    mov   R2, 51

_define_pillars:
    out   TEXTURE, 0
    out   REGION, R0
    out   GPU_RegionMinX, R1
    out   GPU_RegionMinY, 0
    out   GPU_RegionMaxX, R2
    out   GPU_RegionMaxY, 319
    out   GPU_RegionHotSpotX, R1
    out   GPU_RegionHotSpotY, 0

    iadd  R0, 1
    iadd  R1, 48
    iadd  R2, 48

    mov   R3, R0
    ieq   R3, 13
    jt    R3, _define_pillars_end
    jmp   _define_pillars

_define_pillars_end:
    call  _fresh_start
    mov   MENU_BOOL, 1

    mov   ARR_CYCLER, BACKGROUNDX_ARR
    mov   TEMP_A, 0
    mov   [ARR_CYCLER], TEMP_A
    iadd  ARR_CYCLER, 1
    mov   TEMP_A, 640
    mov   [ARR_CYCLER], TEMP_A
    isub  ARR_CYCLER, 1

    mov   ARR_CYCLER, BORDER_ARR
    mov   TEMP_A, 0
    mov   [ARR_CYCLER], TEMP_A
    iadd  ARR_CYCLER, 1
    mov   TEMP_A, 640
    mov   [ARR_CYCLER], TEMP_A

_main_loop:
    in    TEMP_A, INP_GamepadLeft
    mov   TEMP_B, 0
    ilt   TEMP_B, TEMP_A
    jf    TEMP_B, _menu_unchanged
    mov   MENU_BOOL, 1
    mov   PLAYERY, 150

_menu_unchanged:
    in    TEMP_A, INP_GamepadRight
    mov   TEMP_B, 0
    ilt   TEMP_B, TEMP_A
    jf    TEMP_B, _X_not_pressed
    mov   MENU_BOOL, 2
    call  _fresh_start

_X_not_pressed:
    mov   TEMP_A, MENU_BOOL
    ieq   TEMP_A, 1
    jt    TEMP_A, _drawmenu

; obtain texture and region of backround

    in    TEMP_A, TIM_FrameCounter
    imod  TEMP_A, 21
    mov   TEMP_B, TEMP_A
    ilt   TEMP_B, 7
    jt    TEMP_B, _background_animation_1

    mov   TEMP_B, TEMP_A
    igt   TEMP_B, 6
    jt    TEMP_B, _background_animation_2

_background_animation_1:
    out   TEXTURE, 1
    out   REGION, 18
    jmp   _finish_background_animation

_background_animation_2:
    mov   TEMP_B, TEMP_A
    ilt   TEMP_B, 13
    jf    TEMP_B, _background_animation_3

    out   TEXTURE, 2
    out   REGION, 19
    jmp   _finish_background_animation

_background_animation_3:
    out   TEXTURE, 3
    out   REGION, 20
    jmp   _finish_background_animation

_finish_background_animation:
;    mov TEMP_A, MENU_BOOL
;    ieq TEMP_A, 2
;    jt TEMP_A, _draw_background

; change background coordinates every n frames

_move_background:
    mov   ARR_CYCLER, BACKGROUNDX_ARR

    mov   TEMP_A, [ARR_CYCLER]
    isub  TEMP_A, 1
    mov   [ARR_CYCLER], TEMP_A
    iadd  ARR_CYCLER, 1

    mov   TEMP_A, [ARR_CYCLER]
    isub  TEMP_A, 1
    mov   [ARR_CYCLER], TEMP_A
    isub  ARR_CYCLER, 1

_draw_background:
    mov   TEMP_A, [ARR_CYCLER]

    out   DRAWX, TEMP_A
    out   DRAWY, 0
    out   GPU_Command, DRAWREG

    iadd  ARR_CYCLER, 1
    mov   TEMP_A, [ARR_CYCLER]

    out   DRAWX, TEMP_A
    out   DRAWY, 0
    out   GPU_Command, DRAWREG

    isub  ARR_CYCLER, 1

; check in need to rotate background positions

    mov   TEMP_A, [ARR_CYCLER]
    ieq   TEMP_A, -640
    jf    TEMP_A, _skip_background_change

    iadd  ARR_CYCLER, 1
    mov   TEMP_A, 640
    mov   [ARR_CYCLER], TEMP_A
    isub  ARR_CYCLER, 1
    mov   TEMP_A, 0
    mov   [ARR_CYCLER], TEMP_A

_skip_background_change:
;;;;;;;;;;;;;;;;;;;;;;;;;

;    mov TEMP_A, MENU_BOOL
;    ieq TEMP_A, 2
;    jt TEMP_A, _finish_ghost_animation

_move_bottom:
    out   TEXTURE, 4
    out   REGION, 21

    mov   ARR_CYCLER, BORDER_ARR
    mov   TEMP_A, [ARR_CYCLER]
    isub  TEMP_A, 2
    mov   [ARR_CYCLER], TEMP_A
    iadd  ARR_CYCLER, 1

    mov   TEMP_A, [ARR_CYCLER]
    isub  TEMP_A, 2
    mov   [ARR_CYCLER], TEMP_A
    isub  ARR_CYCLER, 1

_draw_bottom:
    mov   TEMP_A, [ARR_CYCLER]

    out   DRAWX, TEMP_A
    out   DRAWY, 320
    out   GPU_Command, DRAWREG

    iadd  ARR_CYCLER, 1
    mov   TEMP_A, [ARR_CYCLER]

    out   DRAWX, TEMP_A
    out   DRAWY, 320
    out   GPU_Command, DRAWREG

    isub  ARR_CYCLER, 1

; check if need to rotate background positions

    mov   TEMP_A, [ARR_CYCLER]
    ieq   TEMP_A, -640
    jf    TEMP_A, _skip_bottom_change

    iadd  ARR_CYCLER, 1
    mov   TEMP_A, 640
    mov   [ARR_CYCLER], TEMP_A
    isub  ARR_CYCLER, 1
    mov   TEMP_A, 0
    mov   [ARR_CYCLER], TEMP_A
    mov   ARR_CYCLER, BACKGROUNDX_ARR

_skip_bottom_change:
    in    TEMP_A, TIM_FrameCounter
    imod  TEMP_A, 21
    mov   TEMP_B, TEMP_A
    ilt   TEMP_B, 7
    jt    TEMP_B, _ghost_animation_1

    mov   TEMP_B, TEMP_A
    igt   TEMP_B, 6
    jt    TEMP_B, _ghost_animation_2

_ghost_animation_1:
    out   TEXTURE, 0
    out   REGION, 14
    out   DRAWX, 191
    out   DRAWY, PLAYERY
    out   GPU_Command, DRAWREG
    jmp   _finish_ghost_animation

_ghost_animation_2:
    mov   TEMP_B, TEMP_A
    ilt   TEMP_B, 13
    jf    TEMP_B, _ghost_animation_3

    out   TEXTURE, 0
    out   REGION, 15
    out   DRAWX, 191
    out   DRAWY, PLAYERY
    out   GPU_Command, DRAWREG
    jmp   _finish_ghost_animation

_ghost_animation_3:
    out   TEXTURE, 0
    out   REGION, 16
    out   DRAWX, 191
    out   DRAWY, PLAYERY
    out   GPU_Command, DRAWREG
    jmp   _finish_ghost_animation

_finish_ghost_animation:
    mov   TEMP_A, MENU_BOOL
    ieq   TEMP_A, 2
    jf    TEMP_A, _no_wait


;    out TEXTURE, 0
;    out REGION, 14
;    out DRAWX, 191
;    out DRAWY, PLAYERY
;    out GPU_Command, DRAWREG

;    out TEXTURE, 4
;    out REGION, 21
;    out DRAWX, 0
;    out DRAWY, 320
;    out GPU_Command, DRAWREG

    out   TEXTURE, BIOS
    mov   TEMP_A, _fly_message
    mov   TEMP_B, [TEMP_A]
    out   REGION, TEMP_B
    mov   R4, 250
    out   DRAWX, R4
    out   DRAWY, 336
    out   GPU_Command, DRAWREG

_format_print_fly_start:
    iadd  R4, 10
    iadd  TEMP_A, 1
    mov   TEMP_B, [TEMP_A]
    mov   R0, TEMP_B
    ieq   R0, 0
    jt    R0, _format_print_fly_end
    out   REGION, TEMP_B
    out   DRAWX, R4
    out   GPU_Command, DRAWREG
    jmp   _format_print_fly_start

_format_print_fly_end:
    in    TEMP_A, INP_GamepadUp
    mov   TEMP_B, 0
    ilt   TEMP_B, TEMP_A
	wait
    jf    TEMP_B, _main_loop

    mov   MENU_BOOL, 0
    call  _fresh_start
    jmp   _main_loop

_no_wait:

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; jump handling
;;

    mov   TEMP_A, ANTI_HOLD
    ieq   TEMP_A, 1
    jt    TEMP_A, _no_jump

_check_jump:
    in    TEMP_A, INP_GamepadUp
    mov   TEMP_B, 0
    ilt   TEMP_B, TEMP_A
    jf    TEMP_B, _no_jump

    mov   FALL_SPEED, 1
    mov   ANTI_HOLD, 1
    mov   JUMP_TO, PLAYERY
    isub  JUMP_TO, 50

_no_jump:
    in    TEMP_A, INP_GamepadUp
    mov   TEMP_B, 0
    ilt   TEMP_B, TEMP_A
    jt    TEMP_B, _check_rise
    mov   ANTI_HOLD, 0

_check_rise:
    mov   TEMP_A, PLAYERY
    igt   TEMP_A, JUMP_TO
    jf    TEMP_A, _is_down
    isub  PLAYERY, 5
    jmp   _is_not_down

_is_down:
    mov   JUMP_TO, 360

    in    TEMP_A, TIM_FrameCounter
    imod  TEMP_A, 10
    mov   TEMP_B, 0
    ieq   TEMP_B, TEMP_A
    jf    TEMP_B, _do_not_add_fall
    iadd  FALL_SPEED, 1

_do_not_add_fall:
    iadd  PLAYERY, FALL_SPEED

_is_not_down:

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; draw pillars
;;
    mov   COUNTER, 0
    mov   ARR_CYCLER, PILLAR_REG_ARR
    mov   ARR_CYCLER2, PILLARX_ARR

_draw_pillars:
    mov   TEMP_A, [ARR_CYCLER]
    mov   TEMP_B, [ARR_CYCLER2]

    out   TEXTURE, 0
    out   REGION, TEMP_A
    out   DRAWX, TEMP_B
    out   DRAWY, 0
    out   GPU_Command, DRAWREG

    iadd  ARR_CYCLER, 1
    iadd  ARR_CYCLER2, 1

    iadd  COUNTER, 1
    mov   TEMP_A, COUNTER
    ieq   TEMP_A, 6
    jf    TEMP_A, _draw_pillars

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; move pillars
;;
    mov   ARR_CYCLER, PILLAR_REG_ARR
    mov   ARR_CYCLER2, PILLARX_ARR
    mov   COUNTER, 0

_move_pillars:
    mov   TEMP_A, [ARR_CYCLER2]
    isub  TEMP_A, 2
    mov   [ARR_CYCLER2], TEMP_A
    iadd  ARR_CYCLER2, 1
    iadd  COUNTER, 1

    mov   TEMP_A, COUNTER
    ieq   TEMP_A, 6
    jf    TEMP_A, _move_pillars

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; add/remove pillar
;;

    mov   ARR_CYCLER, PILLAR_REG_ARR
    mov   ARR_CYCLER2, PILLARX_ARR

    mov   TEMP_A, [ARR_CYCLER2]
    ilt   TEMP_A, -60
    jf    TEMP_A, _do_not_add_pillar

    mov   COUNTER, 0
    mov   TEMP_A, 150

_add_pillar:
    mov   TEMP_B, [ARR_CYCLER2]
    iadd  TEMP_B, TEMP_A
    mov   [ARR_CYCLER2], TEMP_B
    iadd  ARR_CYCLER2, 1
    iadd  COUNTER, 1

    mov   TEMP_B, COUNTER
    ieq   TEMP_B, 6
    jf    TEMP_B, _add_pillar

_adjust_pillar_reg:
    mov   ARR_CYCLER, PILLAR_REG_ARR

    iadd  ARR_CYCLER, 5
    mov   TEMP_A, [ARR_CYCLER]
    isub  ARR_CYCLER, 1
    mov   TEMP_B, [ARR_CYCLER]
    mov   [ARR_CYCLER], TEMP_A
    isub  ARR_CYCLER, 1
    mov   TEMP_A, [ARR_CYCLER]
    mov   [ARR_CYCLER], TEMP_B
    isub  ARR_CYCLER, 1
    mov   TEMP_B, [ARR_CYCLER]
    mov   [ARR_CYCLER], TEMP_A
    isub  ARR_CYCLER, 1
    mov   TEMP_A, [ARR_CYCLER]
    mov   [ARR_CYCLER], TEMP_B
    isub  ARR_CYCLER, 1
    mov   [ARR_CYCLER], TEMP_A
    iadd  ARR_CYCLER, 5

    in    TEMP_A, RNG_CurrentValue
    imod  TEMP_A, 12
    iadd  TEMP_A, 1

    mov   [ARR_CYCLER], TEMP_A

    mov   ARR_CYCLER, PILLAR_REG_ARR
    mov   ARR_CYCLER2, PILLARX_ARR

_do_not_add_pillar:

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; collision handling
;;

    mov   TEMP_A, PLAYERY
    igt   TEMP_A, 310
    jt    TEMP_A, _dead

    iadd  ARR_CYCLER2, 1
    mov   TEMP_A, [ARR_CYCLER2]
    ilt   TEMP_A, 201
    jf    TEMP_A, _skip_collision

    mov   TEMP_A, [ARR_CYCLER2]
    igt   TEMP_A, 151
    jf    TEMP_A, _skip_collision

    mov   ARR_CYCLER2, PILLARX_ARR

    iadd  ARR_CYCLER, 1
    mov   TEMP_A, [ARR_CYCLER]

    mov   COLLISION_TOP, 18
    mov   COLLISION_BOTTOM, 125
    mov   COUNTER, 1

_set_boundaries:
    mov   TEMP_B, TEMP_A
    ieq   TEMP_B, COUNTER
    jt    TEMP_B, _this_pillar

    iadd  COLLISION_TOP, 16
    iadd  COLLISION_BOTTOM, 16
    iadd  COUNTER, 1
    jmp   _set_boundaries

_this_pillar:
    iadd  COLLISION_TOP, 11
    isub  COLLISION_BOTTOM, 12

    mov   TEMP_A, PLAYERY
    igt   TEMP_A, COLLISION_TOP
    jf    TEMP_A, _end_main_loop

    mov   TEMP_A, PLAYERY
    ilt   TEMP_A, COLLISION_BOTTOM
    jf    TEMP_A, _end_main_loop

_skip_collision:
    mov   ARR_CYCLER2, PILLARX_ARR
    iadd  ARR_CYCLER2, 1
    mov   TEMP_A, [ARR_CYCLER2]
    ieq   TEMP_A, 148
    jf    TEMP_A, _no_score
    iadd  CURRENT_SCORE, 1

_no_score:
    call  _print_score             

	push  R4
	push  R0
    out   TEXTURE, BIOS
    mov   TEMP_A, _yourscore_message
    mov   TEMP_B, [TEMP_A]
    out   REGION, TEMP_B
    mov   R4, 220
    out   DRAWX, R4
    out   DRAWY, 336
    out   GPU_Command, DRAWREG

_format_print_score_start:
    iadd  R4, 10
    iadd  TEMP_A, 1
    mov   TEMP_B, [TEMP_A]
    mov   R0, TEMP_B
    ieq   R0, 0
    jt    R0, _format_print_score_end
    out   REGION, TEMP_B
    out   DRAWX, R4
    out   GPU_Command, DRAWREG
    jmp   _format_print_score_start

_format_print_score_end:
	pop   R0
	pop   R4

    mov   TEMP_A, MENU_BOOL
    ieq   TEMP_A, 0
    jt    TEMP_A, _menu_skip_move_player
    mov   TEMP_A, MENU_BOOL
    ieq   TEMP_A, 2
    jt    TEMP_A, _menu_skip_move_player

_drawmenu:
    out   DRAWX, 0
    out   DRAWY, 0

; obtain texture and region of menu and draw it

    in    TEMP_A, TIM_FrameCounter
    imod  TEMP_A, 21
    mov   TEMP_B, TEMP_A
    ilt   TEMP_B, 7
    jt    TEMP_B, _menu_animation_1

    mov   TEMP_B, TEMP_A
    igt   TEMP_B, 6
    jt    TEMP_B, _menu_animation_2

_menu_animation_1:
    out   TEXTURE, 5
    out   REGION, 25
    out   GPU_Command, DRAWREG
    out   TEXTURE, 0
    out   REGION, 14
    out   DRAWX, 100
    out   DRAWY, PLAYERY
    out   GPU_Command, DRAWREG
    jmp   _finish_menu_animation

_menu_animation_2:
    mov   TEMP_B, TEMP_A
    ilt   TEMP_B, 13
    jf    TEMP_B, _menu_animation_3

    out   TEXTURE, 6
    out   REGION, 26
    out   GPU_Command, DRAWREG
    out   TEXTURE, 0
    out   REGION, 15
    out   DRAWX, 100
    out   DRAWY, PLAYERY
    out   GPU_Command, DRAWREG
    jmp   _finish_menu_animation

_menu_animation_3:
    out   TEXTURE, 7
    out   REGION, 27
    out   GPU_Command, DRAWREG
    out   TEXTURE, 0
    out   REGION, 16
    out   DRAWX, 100
    out   DRAWY, PLAYERY
    out   GPU_Command, DRAWREG
    jmp   _finish_menu_animation

_finish_menu_animation:
    mov   ARR_CYCLER, HIGH_SCORE
    mov   TEMP_A, [ARR_CYCLER]
    mov   CURRENT_SCORE, TEMP_A        
    call  _print_score

    out   TEXTURE, BIOS
    mov   TEMP_A, _play_message1
    mov   TEMP_B, [TEMP_A]
    out   REGION, TEMP_B
    mov   R4, 90
    out   DRAWX, R4
    out   DRAWY, 336
    out   GPU_Command, DRAWREG

_format_print_start_start:
    iadd  R4, 10
    iadd  TEMP_A, 1
    mov   TEMP_B, [TEMP_A]
    mov   R0, TEMP_B
    ieq   R0, 0
    jt    R0, _format_print_start_end
    out   REGION, TEMP_B
    out   DRAWX, R4
    out   GPU_Command, DRAWREG
    jmp   _format_print_start_start

_format_print_start_end:
    out   TEXTURE, BIOS
    mov   TEMP_A, _highscore_message
    mov   TEMP_B, [TEMP_A]
    out   REGION, TEMP_B
    mov   R4, 380
    out   DRAWX, R4
    out   DRAWY, 336
    out   GPU_Command, DRAWREG

_format_print_highscore_start:
    iadd  R4, 10
    iadd  TEMP_A, 1
    mov   TEMP_B, [TEMP_A]
    mov   R0, TEMP_B
    ieq   R0, 0
    jt    R0, _format_print_highscore_end
    out   REGION, TEMP_B
    out   DRAWX, R4
    out   GPU_Command, DRAWREG
    jmp   _format_print_highscore_start

_format_print_highscore_end:

_menu_move_player:
    mov   TEMP_A, PLAYERY
    ieq   TEMP_A, 195
    jt    TEMP_A, _menu_move_player_up
    mov   TEMP_A, PLAYERY
    ieq   TEMP_A, 125
    jt    TEMP_A, _menu_move_player_down
    jmp   _menu_move_player_upordown

_menu_move_player_up:
    mov   COUNTER, 1
    jmp   _menu_move_player_upordown

_menu_move_player_down:
    mov   COUNTER, 0

_menu_move_player_upordown:
    mov   TEMP_A, COUNTER
    ieq   TEMP_A, 1
    jt    TEMP_A, _goup
    iadd  PLAYERY, 1
    jmp   _menu_skip_move_player

_goup:
    isub  PLAYERY, 1

_menu_skip_move_player:
	wait
    jmp   _main_loop

_end_main_loop:

_dead:
    call  _print_score             

    mov   ARR_CYCLER, HIGH_SCORE
    mov   TEMP_A, [ARR_CYCLER]
    igt   TEMP_A, CURRENT_SCORE
    jt    TEMP_A, _not_a_highscore
    mov   [ARR_CYCLER], CURRENT_SCORE

_not_a_highscore:
    out   TEXTURE, BIOS
    mov   TEMP_A, _play_message2
    mov   TEMP_B, [TEMP_A]
    out   REGION, TEMP_B
    mov   R4, 25
    out   DRAWX, R4
    out   DRAWY, 336
    out   GPU_Command, DRAWREG

_format_print_respawn_start:
    iadd  R4, 10
    iadd  TEMP_A, 1
    mov   TEMP_B, [TEMP_A]
    mov   R0, TEMP_B
    ieq   R0, 0
    jt    R0, _format_print_respawn_end
    out   REGION, TEMP_B
    out   DRAWX, R4
    out   GPU_Command, DRAWREG
    jmp   _format_print_respawn_start

_format_print_respawn_end:
    out   TEXTURE, BIOS
    mov   TEMP_A, _menu_message
    mov   TEMP_B, [TEMP_A]
    out   REGION, TEMP_B
    mov   R4, 460
    out   DRAWX, R4
    out   DRAWY, 336
    out   GPU_Command, DRAWREG

_format_print_tomenu_start:
    iadd  R4, 10
    iadd  TEMP_A, 1
    mov   TEMP_B, [TEMP_A]
    mov   R0, TEMP_B
    ieq   R0, 0
    jt    R0, _format_print_tomenu_end
    out   REGION, TEMP_B
    out   DRAWX, R4
    out   GPU_Command, DRAWREG
    jmp   _format_print_tomenu_start

_format_print_tomenu_end:
    out   TEXTURE, BIOS
    mov   TEMP_A, _yourscore_message
    mov   TEMP_B, [TEMP_A]
    out   REGION, TEMP_B
    mov   R4, 220
    out   DRAWX, R4
    out   DRAWY, 336
    out   GPU_Command, DRAWREG

_format_print_finalscore_start:
    iadd  R4, 10
    iadd  TEMP_A, 1
    mov   TEMP_B, [TEMP_A]
    mov   R0, TEMP_B
    ieq   R0, 0
    jt    R0, _format_print_finalscore_end
    out   REGION, TEMP_B
    out   DRAWX, R4
    out   GPU_Command, DRAWREG
    jmp   _format_print_finalscore_start

_format_print_finalscore_end:
    in    TEMP_A, INP_GamepadRight
    mov   TEMP_B, 0
    ilt   TEMP_B, TEMP_A
    jf    TEMP_B, _respawn
    call  _fresh_start
    jmp   _main_loop

_respawn:
    in    TEMP_A, INP_GamepadLeft
    mov   TEMP_B, 0
    ilt   TEMP_B, TEMP_A
    jf    TEMP_B, _skip_menu
    mov   PLAYERY, 150
    mov   MENU_BOOL, 1
    jmp   _main_loop

_skip_menu:
	wait
    jmp   _format_print_finalscore_end
	hlt

_menu_message:
string "Main Menu [LEFT]"
_play_message1:
string "Press RIGHT to play..."
_play_message2:
string "Respawn [RIGHT]"
_highscore_message:
string "High Score:"
_yourscore_message:
string "Score:"
_fly_message:
string "Tap UP to fly"

_print_score:
    mov   ARR_CYCLER, BACKGROUNDX_ARR
    iadd  ARR_CYCLER, 4
    mov   [ARR_CYCLER], CURRENT_SCORE

    mov   TEMP_A, CURRENT_SCORE
    ilt   TEMP_A, 10
    jt    TEMP_A, _score_under10
    mov   TEMP_A, CURRENT_SCORE
    ilt   TEMP_A, 100
    jt    TEMP_A, _score_under100
    mov   X, 303
    jmp   _check_highscore

_score_under10:
    mov   X, 283
    jmp   _check_highscore

_score_under100:
    mov   X, 293
    jmp   _check_highscore

_check_highscore:
    mov   TEMP_A, MENU_BOOL
    ieq   TEMP_A, 1
    jf    TEMP_A, _not_menu
    call  _print_high_score
_not_menu:

_print_score_loop:
    out   TEXTURE, BIOS
    mov   TEMP_A, CURRENT_SCORE         ;check if prime count is less than 10
    ilt   TEMP_A, 10                    ;if not, recursively bring it down
    jt    TEMP_A, _lessthan10           ;to under 10 using imod and idiv
    mov   TEMP_A, CURRENT_SCORE
    imod  TEMP_A, 10
    mov   TEMP_B, TEMP_A
    iadd  TEMP_B, 48
    out   REGION, TEMP_B
    out   DRAWX, X
    out   DRAWY, 337
    out   GPU_Command, DRAWREG
    idiv  CURRENT_SCORE, 10
    isub  X, 10
    jmp   _print_score_loop

_lessthan10:
    mov   TEMP_A, CURRENT_SCORE         ;if less than 10, print ascii
    imod  TEMP_A, 10
    mov   TEMP_B, TEMP_A
    iadd  TEMP_B, 48
    out   REGION, TEMP_B
    out   DRAWX, X
    out   DRAWY, 337
    out   GPU_Command, DRAWREG

    mov   CURRENT_SCORE, [ARR_CYCLER]
    isub  ARR_CYCLER, 4
	ret

_print_high_score:
    iadd  X, 210
	ret

_fresh_start:
    mov   ARR_CYCLER, PILLAR_REG_ARR
    mov   TEMP_A, 2
    mov   [ARR_CYCLER], TEMP_A
    iadd  ARR_CYCLER, 1
    mov   TEMP_A, 5
    mov   [ARR_CYCLER], TEMP_A
    iadd  ARR_CYCLER, 1
    mov   TEMP_A, 3
    mov   [ARR_CYCLER], TEMP_A
    iadd  ARR_CYCLER, 1
    mov   TEMP_A, 7
    mov   [ARR_CYCLER], TEMP_A
    iadd  ARR_CYCLER, 1
    mov   TEMP_A, 10
    mov   [ARR_CYCLER], TEMP_A
    iadd  ARR_CYCLER, 1
    mov   TEMP_A, 1
    mov   [ARR_CYCLER], TEMP_A
    mov   ARR_CYCLER, PILLAR_REG_ARR

    mov   ARR_CYCLER, PILLARX_ARR
    mov   TEMP_A, 800
    mov   [ARR_CYCLER], TEMP_A
    iadd  ARR_CYCLER, 1
    iadd  TEMP_A, 150
    mov   [ARR_CYCLER], TEMP_A
    iadd  ARR_CYCLER, 1
    iadd  TEMP_A, 150
    mov   [ARR_CYCLER], TEMP_A
    iadd  ARR_CYCLER, 1
    iadd  TEMP_A, 150
    mov   [ARR_CYCLER], TEMP_A
    iadd  ARR_CYCLER, 1
    iadd  TEMP_A, 150
    mov   [ARR_CYCLER], TEMP_A
    iadd  ARR_CYCLER, 1
    iadd  TEMP_A, 150
    mov   [ARR_CYCLER], TEMP_A
    mov   ARR_CYCLER, PILLARX_ARR

;    mov ARR_CYCLER, BACKGROUNDX_ARR
;    mov TEMP_A, 0
;    mov [ARR_CYCLER], TEMP_A
;    iadd ARR_CYCLER, 1
;    mov TEMP_A, 640
;    mov [ARR_CYCLER], TEMP_A
;    isub ARR_CYCLER, 1

;    mov ARR_CYCLER, BORDER_ARR
;    mov TEMP_A, 0
;    mov [ARR_CYCLER], TEMP_A
;    iadd ARR_CYCLER, 1
;    mov TEMP_A, 640
;    mov [ARR_CYCLER], TEMP_A
;    mov ARR_CYCLER, BACKGROUNDX_ARR

    mov   CURRENT_SCORE, 0
    mov   PLAYERY, 150
    mov   JUMP_TO, 360
    mov   ANTI_HOLD, 0
    mov   FALL_SPEED, -1
	ret
