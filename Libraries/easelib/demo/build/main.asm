; program start section
  call __global_scope_initialization
  call __function_main
  hlt

; location of global variables
  %define global_malloc_start_address 0
  %define global_malloc_end_address 1
  %define global_malloc_first_block 2
  %define global_FontUbuntuMono_B_30 3
  %define global_FontRetro_Gaming_11 266
  %define global_effect 529
  %define global_timer 530
  %define global_clear_color 531
  %define global_is_intro_over 532
  %define global_show_controls 533
  %define global_intro_timer 534
  %define global_intro_color_from_black 535
  %define global_info_offset 536
  %define global_title_timer 537
  %define global_info_size 538
  %define global_info_open 539
  %define global_button_timer 540

__global_scope_initialization:
  push BP
  mov BP, SP
  mov R0, 1048576
  mov [global_malloc_start_address], R0
  mov R0, 3145727
  mov [global_malloc_end_address], R0
  mov R0, -1
  mov [global_malloc_first_block], R0
  mov R0, -1
  mov [global_effect], R0
  mov R0, 0.000000
  mov [global_timer], R0
  mov R0, -367324911
  mov [global_clear_color], R0
  mov R0, 0
  mov [global_is_intro_over], R0
  mov R0, 1
  mov [global_show_controls], R0
  mov R0, 0.000000
  mov [global_intro_timer], R0
  mov R0, 0.000000
  mov [global_intro_color_from_black], R0
  mov R0, 0.000000
  mov [global_info_offset], R0
  mov R0, 0.000000
  mov [global_title_timer], R0
  mov R0, 0
  mov [global_info_open], R0
  mov R0, 0.000000
  mov [global_button_timer], R0
  mov SP, BP
  pop BP
  ret

__function_make_gray:
  push BP
  mov BP, SP
  push R1
  mov R0, [BP+2]
  shl R0, 16
  or R0, -16777216
  mov R1, [BP+2]
  shl R1, 8
  or R0, R1
  mov R1, [BP+2]
  or R0, R1
__function_make_gray_return:
  pop R1
  mov SP, BP
  pop BP
  ret

__function_make_color_rgb:
  push BP
  mov BP, SP
  push R1
  mov R0, [BP+4]
  shl R0, 16
  or R0, -16777216
  mov R1, [BP+3]
  shl R1, 8
  or R0, R1
  mov R1, [BP+2]
  or R0, R1
__function_make_color_rgb_return:
  pop R1
  mov SP, BP
  pop BP
  ret

__function_make_color_rgba:
  push BP
  mov BP, SP
  push R1
  mov R0, [BP+5]
  shl R0, 24
  mov R1, [BP+4]
  shl R1, 16
  or R0, R1
  mov R1, [BP+3]
  shl R1, 8
  or R0, R1
  mov R1, [BP+2]
  or R0, R1
__function_make_color_rgba_return:
  pop R1
  mov SP, BP
  pop BP
  ret

__function_get_color_red:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  and R0, 255
__function_get_color_red_return:
  mov SP, BP
  pop BP
  ret

__function_get_color_green:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  shl R0, -8
  and R0, 255
__function_get_color_green_return:
  mov SP, BP
  pop BP
  ret

__function_get_color_blue:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  shl R0, -16
  and R0, 255
__function_get_color_blue_return:
  mov SP, BP
  pop BP
  ret

__function_get_color_alpha:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  shl R0, -24
  and R0, 255
__function_get_color_alpha_return:
  mov SP, BP
  pop BP
  ret

__function_select_texture:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out GPU_SelectedTexture, R0
__function_select_texture_return:
  mov SP, BP
  pop BP
  ret

__function_get_selected_texture:
  push BP
  mov BP, SP
  in R0, GPU_SelectedTexture
__function_get_selected_texture_return:
  mov SP, BP
  pop BP
  ret

__function_select_region:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out GPU_SelectedRegion, R0
__function_select_region_return:
  mov SP, BP
  pop BP
  ret

__function_get_selected_region:
  push BP
  mov BP, SP
  in R0, GPU_SelectedRegion
__function_get_selected_region_return:
  mov SP, BP
  pop BP
  ret

__function_define_region:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out GPU_RegionMinX, R0
  mov R0, [BP+3]
  out GPU_RegionMinY, R0
  mov R0, [BP+4]
  out GPU_RegionMaxX, R0
  mov R0, [BP+5]
  out GPU_RegionMaxY, R0
  mov R0, [BP+6]
  out GPU_RegionHotSpotX, R0
  mov R0, [BP+7]
  out GPU_RegionHotSpotY, R0
__function_define_region_return:
  mov SP, BP
  pop BP
  ret

__function_define_region_topleft:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out GPU_RegionMinX, R0
  out GPU_RegionHotSpotX, R0
  mov R0, [BP+3]
  out GPU_RegionMinY, R0
  out GPU_RegionHotSpotY, R0
  mov R0, [BP+4]
  out GPU_RegionMaxX, R0
  mov R0, [BP+5]
  out GPU_RegionMaxY, R0
__function_define_region_topleft_return:
  mov SP, BP
  pop BP
  ret

__function_define_region_center:
  push BP
  mov BP, SP
  isub SP, 2
  mov R0, [BP+2]
  mov R1, [BP+4]
  iadd R0, R1
  idiv R0, 2
  mov [BP-1], R0
  mov R0, [BP+3]
  mov R1, [BP+5]
  iadd R0, R1
  idiv R0, 2
  mov [BP-2], R0
  mov R0, [BP+2]
  out GPU_RegionMinX, R0
  mov R0, [BP+3]
  out GPU_RegionMinY, R0
  mov R0, [BP+4]
  out GPU_RegionMaxX, R0
  mov R0, [BP+5]
  out GPU_RegionMaxY, R0
  mov R0, [BP-1]
  out GPU_RegionHotSpotX, R0
  mov R0, [BP-2]
  out GPU_RegionHotSpotY, R0
__function_define_region_center_return:
  mov SP, BP
  pop BP
  ret

__function_define_region_matrix:
  push BP
  mov BP, SP
  isub SP, 17
  mov R0, [BP+2]
  mov [BP-1], R0
  mov R0, [BP+3]
  mov [BP-2], R0
  mov R0, [BP+4]
  mov [BP-3], R0
  mov R0, [BP+5]
  mov [BP-4], R0
  mov R0, [BP+6]
  mov [BP-5], R0
  mov R0, [BP+7]
  mov [BP-6], R0
  mov R0, [BP+8]
  mov [BP-7], R0
  mov R0, [BP-4]
  mov R1, [BP-2]
  isub R0, R1
  iadd R0, 1
  mov R1, [BP+11]
  iadd R0, R1
  mov [BP-8], R0
  mov R0, [BP-5]
  mov R1, [BP-3]
  isub R0, R1
  iadd R0, 1
  mov R1, [BP+11]
  iadd R0, R1
  mov [BP-9], R0
  mov R0, 0
  mov [BP-10], R0
__for_206_start:
  mov R0, [BP-10]
  mov R1, [BP+10]
  ilt R0, R1
  jf R0, __for_206_end
  mov R0, 0
  mov [BP-11], R0
__for_216_start:
  mov R0, [BP-11]
  mov R1, [BP+9]
  ilt R0, R1
  jf R0, __for_216_end
  mov R1, [BP-1]
  mov [SP], R1
  call __function_select_region
  mov R1, [BP-2]
  mov [SP], R1
  mov R1, [BP-3]
  mov [SP+1], R1
  mov R1, [BP-4]
  mov [SP+2], R1
  mov R1, [BP-5]
  mov [SP+3], R1
  mov R1, [BP-6]
  mov [SP+4], R1
  mov R1, [BP-7]
  mov [SP+5], R1
  call __function_define_region
  mov R0, [BP-1]
  mov R1, R0
  iadd R1, 1
  mov [BP-1], R1
  mov R0, [BP-2]
  mov R1, [BP-8]
  iadd R0, R1
  mov [BP-2], R0
  mov R0, [BP-4]
  mov R1, [BP-8]
  iadd R0, R1
  mov [BP-4], R0
  mov R0, [BP-6]
  mov R1, [BP-8]
  iadd R0, R1
  mov [BP-6], R0
__for_216_continue:
  mov R0, [BP-11]
  iadd R0, 1
  mov [BP-11], R0
  jmp __for_216_start
__for_216_end:
  mov R0, [BP-3]
  mov R1, [BP-9]
  iadd R0, R1
  mov [BP-3], R0
  mov R0, [BP-5]
  mov R1, [BP-9]
  iadd R0, R1
  mov [BP-5], R0
  mov R0, [BP-7]
  mov R1, [BP-9]
  iadd R0, R1
  mov [BP-7], R0
  mov R0, [BP+3]
  mov [BP-2], R0
  mov R0, [BP+5]
  mov [BP-4], R0
  mov R0, [BP+7]
  mov [BP-6], R0
__for_206_continue:
  mov R0, [BP-10]
  iadd R0, 1
  mov [BP-10], R0
  jmp __for_206_start
__for_206_end:
__function_define_region_matrix_return:
  mov SP, BP
  pop BP
  ret

__function_set_region_hotspot:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out GPU_RegionHotSpotX, R0
  mov R0, [BP+3]
  out GPU_RegionHotSpotY, R0
__function_set_region_hotspot_return:
  mov SP, BP
  pop BP
  ret

__function_set_multiply_color:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out GPU_MultiplyColor, R0
__function_set_multiply_color_return:
  mov SP, BP
  pop BP
  ret

__function_set_drawing_point:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out GPU_DrawingPointX, R0
  mov R0, [BP+3]
  out GPU_DrawingPointY, R0
__function_set_drawing_point_return:
  mov SP, BP
  pop BP
  ret

__function_set_drawing_scale:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out GPU_DrawingScaleX, R0
  mov R0, [BP+3]
  out GPU_DrawingScaleY, R0
__function_set_drawing_scale_return:
  mov SP, BP
  pop BP
  ret

__function_set_drawing_angle:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out GPU_DrawingAngle, R0
__function_set_drawing_angle_return:
  mov SP, BP
  pop BP
  ret

__function_set_blending_mode:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out GPU_ActiveBlending, R0
__function_set_blending_mode_return:
  mov SP, BP
  pop BP
  ret

__function_get_multiply_color:
  push BP
  mov BP, SP
  in R0, GPU_MultiplyColor
__function_get_multiply_color_return:
  mov SP, BP
  pop BP
  ret

__function_get_drawing_point:
  push BP
  mov BP, SP
  push R1
  in R0, GPU_DrawingPointX
  mov R1, [BP+2]
  mov [R1], R0
  in R0, GPU_DrawingPointY
  mov R1, [BP+3]
  mov [R1], R0
__function_get_drawing_point_return:
  mov SP, BP
  pop BP
  ret

__function_get_drawing_scale:
  push BP
  mov BP, SP
  push R1
  in R0, GPU_DrawingScaleX
  mov R1, [BP+2]
  mov [R1], R0
  in R0, GPU_DrawingScaleY
  mov R1, [BP+3]
  mov [R1], R0
__function_get_drawing_scale_return:
  mov SP, BP
  pop BP
  ret

__function_get_drawing_angle:
  push BP
  mov BP, SP
  in R0, GPU_DrawingAngle
__function_get_drawing_angle_return:
  mov SP, BP
  pop BP
  ret

__function_get_blending_mode:
  push BP
  mov BP, SP
  in R0, GPU_ActiveBlending
__function_get_blending_mode_return:
  mov SP, BP
  pop BP
  ret

__function_clear_screen:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out GPU_ClearColor, R0
  out GPU_Command, GPUCommand_ClearScreen
__function_clear_screen_return:
  mov SP, BP
  pop BP
  ret

__function_draw_region:
  push BP
  mov BP, SP
  out GPU_Command, GPUCommand_DrawRegion
__function_draw_region_return:
  mov SP, BP
  pop BP
  ret

__function_draw_region_at:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out GPU_DrawingPointX, R0
  mov R0, [BP+3]
  out GPU_DrawingPointY, R0
  out GPU_Command, GPUCommand_DrawRegion
__function_draw_region_at_return:
  mov SP, BP
  pop BP
  ret

__function_draw_region_zoomed:
  push BP
  mov BP, SP
  out GPU_Command, GPUCommand_DrawRegionZoomed
__function_draw_region_zoomed_return:
  mov SP, BP
  pop BP
  ret

__function_draw_region_zoomed_at:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out GPU_DrawingPointX, R0
  mov R0, [BP+3]
  out GPU_DrawingPointY, R0
  out GPU_Command, GPUCommand_DrawRegionZoomed
__function_draw_region_zoomed_at_return:
  mov SP, BP
  pop BP
  ret

__function_draw_region_rotated:
  push BP
  mov BP, SP
  out GPU_Command, GPUCommand_DrawRegionRotated
__function_draw_region_rotated_return:
  mov SP, BP
  pop BP
  ret

__function_draw_region_rotated_at:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out GPU_DrawingPointX, R0
  mov R0, [BP+3]
  out GPU_DrawingPointY, R0
  out GPU_Command, GPUCommand_DrawRegionRotated
__function_draw_region_rotated_at_return:
  mov SP, BP
  pop BP
  ret

__function_draw_region_rotozoomed:
  push BP
  mov BP, SP
  out GPU_Command, GPUCommand_DrawRegionRotozoomed
__function_draw_region_rotozoomed_return:
  mov SP, BP
  pop BP
  ret

__function_draw_region_rotozoomed_at:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out GPU_DrawingPointX, R0
  mov R0, [BP+3]
  out GPU_DrawingPointY, R0
  out GPU_Command, GPUCommand_DrawRegionRotozoomed
__function_draw_region_rotozoomed_at_return:
  mov SP, BP
  pop BP
  ret

__function_print_at:
  push BP
  mov BP, SP
  isub SP, 4
  call __function_get_selected_texture
  mov [BP-1], R0
  mov R1, -1
  mov [SP], R1
  call __function_select_texture
  mov R0, [BP+2]
  mov [BP-2], R0
__while_361_start:
__while_361_continue:
  mov R0, [BP+4]
  mov R0, [R0]
  cib R0
  jf R0, __while_361_end
  mov R1, [BP+4]
  mov R1, [R1]
  mov [SP], R1
  call __function_select_region
  mov R1, [BP+2]
  mov [SP], R1
  mov R1, [BP+3]
  mov [SP+1], R1
  call __function_draw_region_at
  mov R0, [BP+2]
  iadd R0, 10
  mov [BP+2], R0
__if_374_start:
  mov R0, [BP+4]
  mov R0, [R0]
  ieq R0, 10
  jf R0, __if_374_end
  mov R0, [BP-2]
  mov [BP+2], R0
  mov R0, [BP+3]
  iadd R0, 20
  mov [BP+3], R0
__if_374_end:
  mov R0, [BP+4]
  iadd R0, 1
  mov [BP+4], R0
  jmp __while_361_start
__while_361_end:
  mov R1, [BP-1]
  mov [SP], R1
  call __function_select_texture
__function_print_at_return:
  mov SP, BP
  pop BP
  ret

__function_print:
  push BP
  mov BP, SP
  isub SP, 5
  lea R1, [BP-1]
  mov [SP], R1
  lea R1, [BP-2]
  mov [SP+1], R1
  call __function_get_drawing_point
  mov R1, [BP-1]
  mov [SP], R1
  mov R1, [BP-2]
  mov [SP+1], R1
  mov R1, [BP+2]
  mov [SP+2], R1
  call __function_print_at
__function_print_return:
  mov SP, BP
  pop BP
  ret

__function_select_sound:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out SPU_SelectedSound, R0
__function_select_sound_return:
  mov SP, BP
  pop BP
  ret

__function_get_selected_sound:
  push BP
  mov BP, SP
  in R0, SPU_SelectedSound
__function_get_selected_sound_return:
  mov SP, BP
  pop BP
  ret

__function_select_channel:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out SPU_SelectedChannel, R0
__function_select_channel_return:
  mov SP, BP
  pop BP
  ret

__function_get_selected_channel:
  push BP
  mov BP, SP
  in R0, SPU_SelectedChannel
__function_get_selected_channel_return:
  mov SP, BP
  pop BP
  ret

__function_set_sound_loop:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out SPU_SoundPlayWithLoop, R0
__function_set_sound_loop_return:
  mov SP, BP
  pop BP
  ret

__function_set_sound_loop_start:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out SPU_SoundLoopStart, R0
__function_set_sound_loop_start_return:
  mov SP, BP
  pop BP
  ret

__function_set_sound_loop_end:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out SPU_SoundLoopEnd, R0
__function_set_sound_loop_end_return:
  mov SP, BP
  pop BP
  ret

__function_set_channel_volume:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out SPU_ChannelVolume, R0
__function_set_channel_volume_return:
  mov SP, BP
  pop BP
  ret

__function_set_channel_speed:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out SPU_ChannelSpeed, R0
__function_set_channel_speed_return:
  mov SP, BP
  pop BP
  ret

__function_set_channel_position:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out SPU_ChannelPosition, R0
__function_set_channel_position_return:
  mov SP, BP
  pop BP
  ret

__function_set_channel_loop:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out SPU_ChannelLoopEnabled, R0
__function_set_channel_loop_return:
  mov SP, BP
  pop BP
  ret

__function_assign_channel_sound:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out SPU_SelectedChannel, R0
  mov R0, [BP+3]
  out SPU_ChannelAssignedSound, R0
__function_assign_channel_sound_return:
  mov SP, BP
  pop BP
  ret

__function_get_channel_speed:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out SPU_SelectedChannel, R0
  in R0, SPU_ChannelSpeed
__function_get_channel_speed_return:
  mov SP, BP
  pop BP
  ret

__function_get_channel_position:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out SPU_SelectedChannel, R0
  in R0, SPU_ChannelPosition
__function_get_channel_position_return:
  mov SP, BP
  pop BP
  ret

__function_get_channel_state:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out SPU_SelectedChannel, R0
  in R0, SPU_ChannelState
__function_get_channel_state_return:
  mov SP, BP
  pop BP
  ret

__function_set_global_volume:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out SPU_GlobalVolume, R0
__function_set_global_volume_return:
  mov SP, BP
  pop BP
  ret

__function_get_global_volume:
  push BP
  mov BP, SP
  in R0, SPU_GlobalVolume
__function_get_global_volume_return:
  mov SP, BP
  pop BP
  ret

__function_play_channel:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out SPU_SelectedChannel, R0
  out SPU_Command, SPUCommand_PlaySelectedChannel
__function_play_channel_return:
  mov SP, BP
  pop BP
  ret

__function_pause_channel:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out SPU_SelectedChannel, R0
  out SPU_Command, SPUCommand_PauseSelectedChannel
__function_pause_channel_return:
  mov SP, BP
  pop BP
  ret

__function_stop_channel:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out SPU_SelectedChannel, R0
  out SPU_Command, SPUCommand_StopSelectedChannel
__function_stop_channel_return:
  mov SP, BP
  pop BP
  ret

__function_pause_all_channels:
  push BP
  mov BP, SP
  out SPU_Command, SPUCommand_PauseAllChannels
__function_pause_all_channels_return:
  mov SP, BP
  pop BP
  ret

__function_stop_all_channels:
  push BP
  mov BP, SP
  out SPU_Command, SPUCommand_StopAllChannels
__function_stop_all_channels_return:
  mov SP, BP
  pop BP
  ret

__function_resume_all_channels:
  push BP
  mov BP, SP
  out SPU_Command, SPUCommand_ResumeAllChannels
__function_resume_all_channels_return:
  mov SP, BP
  pop BP
  ret

__function_play_sound_in_channel:
  push BP
  mov BP, SP
  mov R0, [BP+3]
  out SPU_SelectedChannel, R0
  mov R0, [BP+2]
  out SPU_ChannelAssignedSound, R0
  out SPU_Command, SPUCommand_PlaySelectedChannel
__function_play_sound_in_channel_return:
  mov SP, BP
  pop BP
  ret

__function_play_sound:
  push BP
  mov BP, SP
  push R1
  mov R0, 0
__play_sound_begin_loop:
  out SPU_SelectedChannel, R0
  in R1, SPU_ChannelState
  ieq R1, 0x40
  jt R1, __play_sound_channel_found
  iadd R0, 1
  mov R1, R0
  ige R1, 16
  jf R1, __play_sound_begin_loop
  mov R0, -1
  jmp __play_sound_exit
__play_sound_channel_found:
  mov R1, [BP+2]
  out SPU_ChannelAssignedSound, R1
  out SPU_Command, SPUCommand_PlaySelectedChannel
__play_sound_exit:
  pop R1
__function_play_sound_return:
  mov SP, BP
  pop BP
  ret

__function_select_gamepad:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out INP_SelectedGamepad, R0
__function_select_gamepad_return:
  mov SP, BP
  pop BP
  ret

__function_get_selected_gamepad:
  push BP
  mov BP, SP
  in R0, INP_SelectedGamepad
__function_get_selected_gamepad_return:
  mov SP, BP
  pop BP
  ret

__function_gamepad_is_connected:
  push BP
  mov BP, SP
  in R0, INP_GamepadConnected
__function_gamepad_is_connected_return:
  mov SP, BP
  pop BP
  ret

__function_gamepad_left:
  push BP
  mov BP, SP
  in R0, INP_GamepadLeft
__function_gamepad_left_return:
  mov SP, BP
  pop BP
  ret

__function_gamepad_right:
  push BP
  mov BP, SP
  in R0, INP_GamepadRight
__function_gamepad_right_return:
  mov SP, BP
  pop BP
  ret

__function_gamepad_up:
  push BP
  mov BP, SP
  in R0, INP_GamepadUp
__function_gamepad_up_return:
  mov SP, BP
  pop BP
  ret

__function_gamepad_down:
  push BP
  mov BP, SP
  in R0, INP_GamepadDown
__function_gamepad_down_return:
  mov SP, BP
  pop BP
  ret

__function_gamepad_direction:
  push BP
  mov BP, SP
__if_515_start:
  call __function_gamepad_left
  mov R1, R0
  igt R1, 0
  mov R0, R1
  jf R0, __if_515_else
  mov R0, -1
  lea R1, [BP+2]
  mov R1, [R1]
  mov [R1], R0
  jmp __if_515_end
__if_515_else:
__if_524_start:
  call __function_gamepad_right
  mov R1, R0
  igt R1, 0
  mov R0, R1
  jf R0, __if_524_else
  mov R0, 1
  lea R1, [BP+2]
  mov R1, [R1]
  mov [R1], R0
  jmp __if_524_end
__if_524_else:
  mov R0, 0
  lea R1, [BP+2]
  mov R1, [R1]
  mov [R1], R0
__if_524_end:
__if_515_end:
__if_536_start:
  call __function_gamepad_up
  mov R1, R0
  igt R1, 0
  mov R0, R1
  jf R0, __if_536_else
  mov R0, -1
  lea R1, [BP+3]
  mov R1, [R1]
  mov [R1], R0
  jmp __if_536_end
__if_536_else:
__if_545_start:
  call __function_gamepad_down
  mov R1, R0
  igt R1, 0
  mov R0, R1
  jf R0, __if_545_else
  mov R0, 1
  lea R1, [BP+3]
  mov R1, [R1]
  mov [R1], R0
  jmp __if_545_end
__if_545_else:
  mov R0, 0
  lea R1, [BP+3]
  mov R1, [R1]
  mov [R1], R0
__if_545_end:
__if_536_end:
__function_gamepad_direction_return:
  mov SP, BP
  pop BP
  ret

__function_gamepad_direction_normalized:
  push BP
  mov BP, SP
__if_560_start:
  call __function_gamepad_left
  mov R1, R0
  igt R1, 0
  mov R0, R1
  jf R0, __if_560_else
  mov R0, -1.000000
  lea R1, [BP+2]
  mov R1, [R1]
  mov [R1], R0
  jmp __if_560_end
__if_560_else:
__if_569_start:
  call __function_gamepad_right
  mov R1, R0
  igt R1, 0
  mov R0, R1
  jf R0, __if_569_else
  mov R0, 1.000000
  lea R1, [BP+2]
  mov R1, [R1]
  mov [R1], R0
  jmp __if_569_end
__if_569_else:
  mov R0, 0.000000
  lea R1, [BP+2]
  mov R1, [R1]
  mov [R1], R0
__if_569_end:
__if_560_end:
__if_581_start:
  call __function_gamepad_up
  mov R1, R0
  igt R1, 0
  mov R0, R1
  jf R0, __if_581_else
  mov R0, -1.000000
  lea R1, [BP+3]
  mov R1, [R1]
  mov [R1], R0
  jmp __if_581_end
__if_581_else:
__if_590_start:
  call __function_gamepad_down
  mov R1, R0
  igt R1, 0
  mov R0, R1
  jf R0, __if_590_else
  mov R0, 1.000000
  lea R1, [BP+3]
  mov R1, [R1]
  mov [R1], R0
  jmp __if_590_end
__if_590_else:
  mov R0, 0.000000
  lea R1, [BP+3]
  mov R1, [R1]
  mov [R1], R0
__if_590_end:
__if_581_end:
__if_602_start:
  mov R0, [BP+2]
  mov R0, [R0]
  cfb R0
  jf R0, __LogicalAnd_ShortCircuit_605
  mov R1, [BP+3]
  mov R1, [R1]
  cfb R1
  and R0, R1
__LogicalAnd_ShortCircuit_605:
  jf R0, __if_602_end
  mov R0, [BP+2]
  mov R0, [R0]
  fmul R0, 0.707107
  lea R1, [BP+2]
  mov R1, [R1]
  mov [R1], R0
  mov R0, [BP+3]
  mov R0, [R0]
  fmul R0, 0.707107
  lea R1, [BP+3]
  mov R1, [R1]
  mov [R1], R0
__if_602_end:
__function_gamepad_direction_normalized_return:
  mov SP, BP
  pop BP
  ret

__function_gamepad_button_a:
  push BP
  mov BP, SP
  in R0, INP_GamepadButtonA
__function_gamepad_button_a_return:
  mov SP, BP
  pop BP
  ret

__function_gamepad_button_b:
  push BP
  mov BP, SP
  in R0, INP_GamepadButtonB
__function_gamepad_button_b_return:
  mov SP, BP
  pop BP
  ret

__function_gamepad_button_x:
  push BP
  mov BP, SP
  in R0, INP_GamepadButtonX
__function_gamepad_button_x_return:
  mov SP, BP
  pop BP
  ret

__function_gamepad_button_y:
  push BP
  mov BP, SP
  in R0, INP_GamepadButtonY
__function_gamepad_button_y_return:
  mov SP, BP
  pop BP
  ret

__function_gamepad_button_l:
  push BP
  mov BP, SP
  in R0, INP_GamepadButtonL
__function_gamepad_button_l_return:
  mov SP, BP
  pop BP
  ret

__function_gamepad_button_r:
  push BP
  mov BP, SP
  in R0, INP_GamepadButtonR
__function_gamepad_button_r_return:
  mov SP, BP
  pop BP
  ret

__function_gamepad_button_start:
  push BP
  mov BP, SP
  in R0, INP_GamepadButtonStart
__function_gamepad_button_start_return:
  mov SP, BP
  pop BP
  ret

__function_fmod:
  push BP
  mov BP, SP
  push R1
  mov R0, [BP+2]
  mov R1, [BP+3]
  fmod R0, R1
  pop R1
__function_fmod_return:
  mov SP, BP
  pop BP
  ret

__function_min:
  push BP
  mov BP, SP
  push R1
  mov R0, [BP+2]
  mov R1, [BP+3]
  imin R0, R1
  pop R1
__function_min_return:
  mov SP, BP
  pop BP
  ret

__function_max:
  push BP
  mov BP, SP
  push R1
  mov R0, [BP+2]
  mov R1, [BP+3]
  imax R0, R1
  pop R1
__function_max_return:
  mov SP, BP
  pop BP
  ret

__function_abs:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  iabs R0
__function_abs_return:
  mov SP, BP
  pop BP
  ret

__function_fmin:
  push BP
  mov BP, SP
  push R1
  mov R0, [BP+2]
  mov R1, [BP+3]
  fmin R0, R1
  pop R1
__function_fmin_return:
  mov SP, BP
  pop BP
  ret

__function_fmax:
  push BP
  mov BP, SP
  push R1
  mov R0, [BP+2]
  mov R1, [BP+3]
  fmax R0, R1
  pop R1
__function_fmax_return:
  mov SP, BP
  pop BP
  ret

__function_fabs:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  fabs R0
__function_fabs_return:
  mov SP, BP
  pop BP
  ret

__function_floor:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  flr R0
__function_floor_return:
  mov SP, BP
  pop BP
  ret

__function_ceil:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  ceil R0
__function_ceil_return:
  mov SP, BP
  pop BP
  ret

__function_round:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  round R0
__function_round_return:
  mov SP, BP
  pop BP
  ret

__function_sin:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  sin R0
__function_sin_return:
  mov SP, BP
  pop BP
  ret

__function_cos:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  fadd R0, 1.570796
  sin R0
__function_cos_return:
  mov SP, BP
  pop BP
  ret

__function_tan:
  push BP
  mov BP, SP
  push R1
  mov R1, [BP+2]
  mov R0, R1
  sin R0
  fadd R1, 1.570796
  sin R1
  fdiv R0, R1
  pop R1
__function_tan_return:
  mov SP, BP
  pop BP
  ret

__function_asin:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  acos R0
  fsgn R0
  fadd R0, 1.570796
__function_asin_return:
  mov SP, BP
  pop BP
  ret

__function_acos:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  acos R0
__function_acos_return:
  mov SP, BP
  pop BP
  ret

__function_atan2:
  push BP
  mov BP, SP
  push R1
  mov R0, [BP+2]
  mov R1, [BP+3]
  atan2 R0, R1
  pop R1
__function_atan2_return:
  mov SP, BP
  pop BP
  ret

__function_sqrt:
  push BP
  mov BP, SP
  push R1
  mov R0, [BP+2]
  mov R1, 0.5
  pow R0, R1
  pop R1
__function_sqrt_return:
  mov SP, BP
  pop BP
  ret

__function_pow:
  push BP
  mov BP, SP
  push R1
  mov R0, [BP+2]
  mov R1, [BP+3]
  pow R0, R1
  pop R1
__function_pow_return:
  mov SP, BP
  pop BP
  ret

__function_exp:
  push BP
  mov BP, SP
  push R1
  mov R0, 2.718282
  mov R1, [BP+2]
  pow R0, R1
  pop R1
__function_exp_return:
  mov SP, BP
  pop BP
  ret

__function_log:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  log R0
__function_log_return:
  mov SP, BP
  pop BP
  ret

__function_isdigit:
  push BP
  mov BP, SP
  push R1
  mov R0, [BP+2]
  ige R0, 48
  jf R0, __LogicalAnd_ShortCircuit_733
  mov R1, [BP+2]
  ile R1, 57
  and R0, R1
__LogicalAnd_ShortCircuit_733:
__function_isdigit_return:
  pop R1
  mov SP, BP
  pop BP
  ret

__function_isxdigit:
  push BP
  mov BP, SP
  push R1
__if_738_start:
  mov R0, [BP+2]
  ige R0, 48
  jf R0, __LogicalAnd_ShortCircuit_743
  mov R1, [BP+2]
  ile R1, 57
  and R0, R1
__LogicalAnd_ShortCircuit_743:
  jf R0, __if_738_end
  mov R0, 1
  jmp __function_isxdigit_return
__if_738_end:
__if_748_start:
  mov R0, [BP+2]
  ige R0, 97
  jf R0, __LogicalAnd_ShortCircuit_753
  mov R1, [BP+2]
  ile R1, 102
  and R0, R1
__LogicalAnd_ShortCircuit_753:
  jf R0, __if_748_end
  mov R0, 1
  jmp __function_isxdigit_return
__if_748_end:
  mov R0, [BP+2]
  ige R0, 65
  jf R0, __LogicalAnd_ShortCircuit_764
  mov R1, [BP+2]
  ile R1, 70
  and R0, R1
__LogicalAnd_ShortCircuit_764:
__function_isxdigit_return:
  pop R1
  mov SP, BP
  pop BP
  ret

__function_isalpha:
  push BP
  mov BP, SP
  push R1
__if_769_start:
  mov R0, [BP+2]
  ige R0, 97
  jf R0, __LogicalAnd_ShortCircuit_774
  mov R1, [BP+2]
  ile R1, 122
  and R0, R1
__LogicalAnd_ShortCircuit_774:
  jf R0, __if_769_end
  mov R0, 1
  jmp __function_isalpha_return
__if_769_end:
  mov R0, [BP+2]
  ige R0, 65
  jf R0, __LogicalAnd_ShortCircuit_785
  mov R1, [BP+2]
  ile R1, 90
  and R0, R1
__LogicalAnd_ShortCircuit_785:
__function_isalpha_return:
  pop R1
  mov SP, BP
  pop BP
  ret

__function_isascii:
  push BP
  mov BP, SP
  push R1
  mov R0, [BP+2]
  ige R0, 0
  jf R0, __LogicalAnd_ShortCircuit_796
  mov R1, [BP+2]
  ile R1, 127
  and R0, R1
__LogicalAnd_ShortCircuit_796:
__function_isascii_return:
  pop R1
  mov SP, BP
  pop BP
  ret

__function_isalphanum:
  push BP
  mov BP, SP
  push R1
__if_801_start:
  mov R0, [BP+2]
  ige R0, 48
  jf R0, __LogicalAnd_ShortCircuit_806
  mov R1, [BP+2]
  ile R1, 57
  and R0, R1
__LogicalAnd_ShortCircuit_806:
  jf R0, __if_801_end
  mov R0, 1
  jmp __function_isalphanum_return
__if_801_end:
__if_811_start:
  mov R0, [BP+2]
  ige R0, 97
  jf R0, __LogicalAnd_ShortCircuit_816
  mov R1, [BP+2]
  ile R1, 122
  and R0, R1
__LogicalAnd_ShortCircuit_816:
  jf R0, __if_811_end
  mov R0, 1
  jmp __function_isalphanum_return
__if_811_end:
  mov R0, [BP+2]
  ige R0, 65
  jf R0, __LogicalAnd_ShortCircuit_827
  mov R1, [BP+2]
  ile R1, 90
  and R0, R1
__LogicalAnd_ShortCircuit_827:
__function_isalphanum_return:
  pop R1
  mov SP, BP
  pop BP
  ret

__function_islower:
  push BP
  mov BP, SP
  push R1
__if_832_start:
  mov R0, [BP+2]
  ige R0, 97
  jf R0, __LogicalAnd_ShortCircuit_837
  mov R1, [BP+2]
  ile R1, 122
  and R0, R1
__LogicalAnd_ShortCircuit_837:
  jf R0, __if_832_end
  mov R0, 1
  jmp __function_islower_return
__if_832_end:
  mov R0, [BP+2]
  ige R0, 224
  jf R0, __LogicalAnd_ShortCircuit_848
  mov R1, [BP+2]
  ile R1, 254
  and R0, R1
__LogicalAnd_ShortCircuit_848:
  jf R0, __LogicalAnd_ShortCircuit_852
  mov R1, [BP+2]
  ine R1, 247
  and R0, R1
__LogicalAnd_ShortCircuit_852:
__function_islower_return:
  pop R1
  mov SP, BP
  pop BP
  ret

__function_isupper:
  push BP
  mov BP, SP
  push R1
__if_857_start:
  mov R0, [BP+2]
  ige R0, 65
  jf R0, __LogicalAnd_ShortCircuit_862
  mov R1, [BP+2]
  ile R1, 90
  and R0, R1
__LogicalAnd_ShortCircuit_862:
  jf R0, __if_857_end
  mov R0, 1
  jmp __function_isupper_return
__if_857_end:
  mov R0, [BP+2]
  ige R0, 192
  jf R0, __LogicalAnd_ShortCircuit_873
  mov R1, [BP+2]
  ile R1, 222
  and R0, R1
__LogicalAnd_ShortCircuit_873:
  jf R0, __LogicalAnd_ShortCircuit_877
  mov R1, [BP+2]
  ine R1, 215
  and R0, R1
__LogicalAnd_ShortCircuit_877:
__function_isupper_return:
  pop R1
  mov SP, BP
  pop BP
  ret

__function_isspace:
  push BP
  mov BP, SP
  push R1
  mov R0, [BP+2]
  ieq R0, 32
  jt R0, __LogicalOr_ShortCircuit_888
  mov R1, [BP+2]
  ieq R1, 10
  or R0, R1
__LogicalOr_ShortCircuit_888:
  jt R0, __LogicalOr_ShortCircuit_892
  mov R1, [BP+2]
  ieq R1, 13
  or R0, R1
__LogicalOr_ShortCircuit_892:
  jt R0, __LogicalOr_ShortCircuit_896
  mov R1, [BP+2]
  ieq R1, 9
  or R0, R1
__LogicalOr_ShortCircuit_896:
__function_isspace_return:
  pop R1
  mov SP, BP
  pop BP
  ret

__function_tolower:
  push BP
  mov BP, SP
  push R1
  push R2
  isub SP, 1
__if_901_start:
  mov R2, [BP+2]
  mov [SP], R2
  call __function_isupper
  mov R1, R0
  bnot R1
  mov R0, R1
  jf R0, __if_901_end
  mov R0, [BP+2]
  jmp __function_tolower_return
__if_901_end:
  mov R0, [BP+2]
  iadd R0, 32
__function_tolower_return:
  iadd SP, 1
  pop R2
  pop R1
  mov SP, BP
  pop BP
  ret

__function_toupper:
  push BP
  mov BP, SP
  push R1
  push R2
  isub SP, 1
__if_913_start:
  mov R2, [BP+2]
  mov [SP], R2
  call __function_islower
  mov R1, R0
  bnot R1
  mov R0, R1
  jf R0, __if_913_end
  mov R0, [BP+2]
  jmp __function_toupper_return
__if_913_end:
  mov R0, [BP+2]
  isub R0, 32
__function_toupper_return:
  iadd SP, 1
  pop R2
  pop R1
  mov SP, BP
  pop BP
  ret

__function_strlen:
  push BP
  mov BP, SP
  isub SP, 1
  push R1
  mov R0, [BP+2]
  mov [BP-1], R0
__while_928_start:
__while_928_continue:
  mov R0, [BP+2]
  mov R0, [R0]
  cib R0
  jf R0, __while_928_end
  mov R0, [BP+2]
  iadd R0, 1
  mov [BP+2], R0
  jmp __while_928_start
__while_928_end:
  mov R0, [BP+2]
  mov R1, [BP-1]
  isub R0, R1
__function_strlen_return:
  pop R1
  mov SP, BP
  pop BP
  ret

__function_strcmp:
  push BP
  mov BP, SP
  push R1
__while_940_start:
__while_940_continue:
  mov R0, [BP+2]
  mov R0, [R0]
  cib R0
  jf R0, __LogicalAnd_ShortCircuit_943
  mov R1, [BP+3]
  mov R1, [R1]
  cib R1
  and R0, R1
__LogicalAnd_ShortCircuit_943:
  jf R0, __while_940_end
__if_947_start:
  mov R0, [BP+2]
  mov R0, [R0]
  mov R1, [BP+3]
  mov R1, [R1]
  ine R0, R1
  jf R0, __if_947_end
  jmp __while_940_end
__if_947_end:
  mov R0, [BP+2]
  iadd R0, 1
  mov [BP+2], R0
  mov R0, [BP+3]
  iadd R0, 1
  mov [BP+3], R0
  jmp __while_940_start
__while_940_end:
  mov R0, [BP+2]
  mov R0, [R0]
  mov R1, [BP+3]
  mov R1, [R1]
  isub R0, R1
__function_strcmp_return:
  pop R1
  mov SP, BP
  pop BP
  ret

__function_strncmp:
  push BP
  mov BP, SP
  push R1
__if_968_start:
  mov R0, [BP+4]
  ilt R0, 1
  jf R0, __if_968_end
  mov R0, 0
  jmp __function_strncmp_return
__if_968_end:
__while_974_start:
__while_974_continue:
  mov R0, [BP+2]
  mov R0, [R0]
  cib R0
  jf R0, __LogicalAnd_ShortCircuit_977
  mov R1, [BP+3]
  mov R1, [R1]
  cib R1
  and R0, R1
__LogicalAnd_ShortCircuit_977:
  jf R0, __while_974_end
  mov R0, [BP+4]
  isub R0, 1
  mov [BP+4], R0
__if_983_start:
  mov R0, [BP+4]
  ile R0, 0
  jf R0, __if_983_end
  jmp __while_974_end
__if_983_end:
__if_988_start:
  mov R0, [BP+2]
  mov R0, [R0]
  mov R1, [BP+3]
  mov R1, [R1]
  ine R0, R1
  jf R0, __if_988_end
  jmp __while_974_end
__if_988_end:
  mov R0, [BP+2]
  iadd R0, 1
  mov [BP+2], R0
  mov R0, [BP+3]
  iadd R0, 1
  mov [BP+3], R0
  jmp __while_974_start
__while_974_end:
  mov R0, [BP+2]
  mov R0, [R0]
  mov R1, [BP+3]
  mov R1, [R1]
  isub R0, R1
__function_strncmp_return:
  pop R1
  mov SP, BP
  pop BP
  ret

__function_strcpy:
  push BP
  mov BP, SP
__while_1008_start:
__while_1008_continue:
  mov R0, [BP+3]
  mov R0, [R0]
  cib R0
  jf R0, __while_1008_end
  mov R0, [BP+3]
  mov R0, [R0]
  lea R1, [BP+2]
  mov R1, [R1]
  mov [R1], R0
  mov R0, [BP+2]
  iadd R0, 1
  mov [BP+2], R0
  mov R0, [BP+3]
  iadd R0, 1
  mov [BP+3], R0
  jmp __while_1008_start
__while_1008_end:
  mov R0, 0
  lea R1, [BP+2]
  mov R1, [R1]
  mov [R1], R0
__function_strcpy_return:
  mov SP, BP
  pop BP
  ret

__function_strncpy:
  push BP
  mov BP, SP
__if_1029_start:
  mov R0, [BP+4]
  ilt R0, 1
  jf R0, __if_1029_end
  jmp __function_strncpy_return
__if_1029_end:
__while_1034_start:
__while_1034_continue:
  mov R0, [BP+3]
  mov R0, [R0]
  cib R0
  jf R0, __while_1034_end
  mov R0, [BP+3]
  mov R0, [R0]
  lea R1, [BP+2]
  mov R1, [R1]
  mov [R1], R0
  mov R0, [BP+2]
  iadd R0, 1
  mov [BP+2], R0
  mov R0, [BP+3]
  iadd R0, 1
  mov [BP+3], R0
  mov R0, [BP+4]
  isub R0, 1
  mov [BP+4], R0
__if_1049_start:
  mov R0, [BP+4]
  ile R0, 0
  jf R0, __if_1049_end
  jmp __while_1034_end
__if_1049_end:
  jmp __while_1034_start
__while_1034_end:
  mov R0, 0
  lea R1, [BP+2]
  mov R1, [R1]
  mov [R1], R0
__function_strncpy_return:
  mov SP, BP
  pop BP
  ret

__function_strcat:
  push BP
  mov BP, SP
__while_1061_start:
__while_1061_continue:
  mov R0, [BP+2]
  mov R0, [R0]
  cib R0
  jf R0, __while_1061_end
  mov R0, [BP+2]
  iadd R0, 1
  mov [BP+2], R0
  jmp __while_1061_start
__while_1061_end:
__while_1066_start:
__while_1066_continue:
  mov R0, [BP+3]
  mov R0, [R0]
  cib R0
  jf R0, __while_1066_end
  mov R0, [BP+3]
  mov R0, [R0]
  lea R1, [BP+2]
  mov R1, [R1]
  mov [R1], R0
  mov R0, [BP+2]
  iadd R0, 1
  mov [BP+2], R0
  mov R0, [BP+3]
  iadd R0, 1
  mov [BP+3], R0
  jmp __while_1066_start
__while_1066_end:
  mov R0, 0
  lea R1, [BP+2]
  mov R1, [R1]
  mov [R1], R0
__function_strcat_return:
  mov SP, BP
  pop BP
  ret

__function_strncat:
  push BP
  mov BP, SP
__if_1087_start:
  mov R0, [BP+4]
  ilt R0, 1
  jf R0, __if_1087_end
  jmp __function_strncat_return
__if_1087_end:
__while_1092_start:
__while_1092_continue:
  mov R0, [BP+2]
  mov R0, [R0]
  cib R0
  jf R0, __while_1092_end
  mov R0, [BP+2]
  iadd R0, 1
  mov [BP+2], R0
  jmp __while_1092_start
__while_1092_end:
__while_1097_start:
__while_1097_continue:
  mov R0, [BP+3]
  mov R0, [R0]
  cib R0
  jf R0, __while_1097_end
  mov R0, [BP+3]
  mov R0, [R0]
  lea R1, [BP+2]
  mov R1, [R1]
  mov [R1], R0
  mov R0, [BP+2]
  iadd R0, 1
  mov [BP+2], R0
  mov R0, [BP+3]
  iadd R0, 1
  mov [BP+3], R0
  mov R0, [BP+4]
  isub R0, 1
  mov [BP+4], R0
__if_1112_start:
  mov R0, [BP+4]
  ile R0, 0
  jf R0, __if_1112_end
  jmp __while_1097_end
__if_1112_end:
  jmp __while_1097_start
__while_1097_end:
  mov R0, 0
  lea R1, [BP+2]
  mov R1, [R1]
  mov [R1], R0
__function_strncat_return:
  mov SP, BP
  pop BP
  ret

__function_itoa:
  push BP
  mov BP, SP
  isub SP, 65
  lea DR, [BP-17]
  mov SR, __literal_string_1130
  mov CR, 17
  movs
  lea R0, [BP-50]
  mov [BP-51], R0
__if_1139_start:
  mov R0, [BP+4]
  ilt R0, 2
  jt R0, __LogicalOr_ShortCircuit_1144
  mov R1, [BP+4]
  igt R1, 16
  or R0, R1
__LogicalOr_ShortCircuit_1144:
  jf R0, __if_1139_end
  jmp __function_itoa_return
__if_1139_end:
__if_1148_start:
  mov R0, [BP+4]
  ieq R0, 10
  jf R0, __LogicalAnd_ShortCircuit_1153
  mov R1, [BP+2]
  ilt R1, 0
  and R0, R1
__LogicalAnd_ShortCircuit_1153:
  jf R0, __if_1148_else
__if_1157_start:
  mov R0, [BP+2]
  ieq R0, 0x80000000
  jf R0, __if_1157_end
  lea DR, [BP-63]
  mov SR, __literal_string_1167
  mov CR, 12
  movs
  mov R1, [BP+3]
  mov [SP], R1
  lea R1, [BP-63]
  mov [SP+1], R1
  call __function_strcpy
  jmp __function_itoa_return
__if_1157_end:
  mov R0, 45
  lea R1, [BP+3]
  mov R1, [R1]
  mov [R1], R0
  mov R0, [BP+3]
  iadd R0, 1
  mov [BP+3], R0
  mov R0, [BP+2]
  isgn R0
  mov [BP+2], R0
  jmp __if_1148_end
__if_1148_else:
__if_1182_start:
  mov R0, [BP+2]
  ilt R0, 0
  jf R0, __if_1182_end
  mov R0, [BP+2]
  and R0, 2147483647
  mov [BP+2], R0
  mov R0, 1073741824
  mov [BP-52], R0
  mov R0, 1073741824
  mov R1, [BP+4]
  imod R0, R1
  mov [BP-53], R0
  mov R0, [BP-53]
  imul R0, 2
  mov R1, [BP+2]
  mov R2, [BP+4]
  imod R1, R2
  iadd R0, R1
  mov [BP-54], R0
  mov R0, [BP-54]
  mov R1, [BP+4]
  imod R0, R1
  mov [BP-55], R0
  lea R0, [BP-17]
  mov R1, [BP-55]
  iadd R0, R1
  mov R0, [R0]
  lea R1, [BP-51]
  mov R1, [R1]
  mov [R1], R0
  mov R0, [BP-51]
  iadd R0, 1
  mov [BP-51], R0
  mov R0, [BP-52]
  mov R1, [BP+4]
  idiv R0, R1
  imul R0, 2
  mov R1, [BP+2]
  mov R2, [BP+4]
  idiv R1, R2
  iadd R0, R1
  mov R1, [BP-54]
  mov R2, [BP+4]
  idiv R1, R2
  iadd R0, R1
  mov [BP+2], R0
__if_1238_start:
  mov R0, [BP+2]
  bnot R0
  jf R0, __if_1238_end
  jmp __label_1258_digits_stored
__if_1238_end:
__if_1182_end:
__if_1148_end:
__do_1242_start:
  lea R0, [BP-17]
  mov R1, [BP+2]
  mov R2, [BP+4]
  imod R1, R2
  iadd R0, R1
  mov R0, [R0]
  lea R1, [BP-51]
  mov R1, [R1]
  mov [R1], R0
  mov R0, [BP-51]
  iadd R0, 1
  mov [BP-51], R0
  mov R0, [BP+2]
  mov R1, [BP+4]
  idiv R0, R1
  mov [BP+2], R0
__do_1242_continue:
  mov R0, [BP+2]
  cib R0
  jt R0, __do_1242_start
__do_1242_end:
__label_1258_digits_stored:
__do_1259_start:
  mov R0, [BP-51]
  isub R0, 1
  mov [BP-51], R0
  mov R0, [BP-51]
  mov R0, [R0]
  lea R1, [BP+3]
  mov R1, [R1]
  mov [R1], R0
  mov R0, [BP+3]
  iadd R0, 1
  mov [BP+3], R0
__do_1259_continue:
  mov R0, [BP-51]
  lea R1, [BP-50]
  ine R0, R1
  jt R0, __do_1259_start
__do_1259_end:
  mov R0, 0
  lea R1, [BP+3]
  mov R1, [R1]
  mov [R1], R0
__function_itoa_return:
  mov SP, BP
  pop BP
  ret

__function_ftoa:
  push BP
  mov BP, SP
  isub SP, 14
__if_1283_start:
  mov R0, [BP+2]
  flt R0, 0.000000
  jf R0, __if_1283_end
  mov R0, 45
  lea R1, [BP+3]
  mov R1, [R1]
  mov [R1], R0
  mov R0, [BP+3]
  iadd R0, 1
  mov [BP+3], R0
  mov R0, [BP+2]
  fsgn R0
  mov [BP+2], R0
__if_1283_end:
  mov R0, [BP+2]
  flr R0
  cfi R0
  mov [BP-1], R0
  push R1
  mov R0, [BP+2]
  mov R1, [BP-1]
  cif R1
  fsub R0, R1
  fmul R0, 100000.0
  round R0
  cfi R0
  mov [BP-2], R0
  pop R1
  mov R1, [BP-1]
  mov [SP], R1
  mov R1, [BP+3]
  mov [SP+1], R1
  mov R1, 10
  mov [SP+2], R1
  call __function_itoa
__if_1312_start:
  mov R0, [BP-2]
  bnot R0
  jf R0, __if_1312_end
  jmp __function_ftoa_return
__if_1312_end:
  mov R1, [BP+3]
  mov [SP], R1
  mov R1, __literal_string_1318
  mov [SP+1], R1
  call __function_strcat
  mov R0, [BP-2]
  mov [BP-3], R0
__while_1322_start:
__while_1322_continue:
  mov R0, [BP-3]
  ilt R0, 10000
  jf R0, __while_1322_end
  mov R1, [BP+3]
  mov [SP], R1
  mov R1, __literal_string_1329
  mov [SP+1], R1
  call __function_strcat
  mov R0, [BP-3]
  imul R0, 10
  mov [BP-3], R0
  jmp __while_1322_start
__while_1322_end:
__while_1333_start:
__while_1333_continue:
  mov R0, [BP-2]
  imod R0, 10
  bnot R0
  jf R0, __while_1333_end
  mov R0, [BP-2]
  idiv R0, 10
  mov [BP-2], R0
  jmp __while_1333_start
__while_1333_end:
  mov R1, [BP-2]
  mov [SP], R1
  lea R1, [BP-11]
  mov [SP+1], R1
  mov R1, 10
  mov [SP+2], R1
  call __function_itoa
  mov R1, [BP+3]
  mov [SP], R1
  lea R1, [BP-11]
  mov [SP+1], R1
  call __function_strcat
__function_ftoa_return:
  mov SP, BP
  pop BP
  ret

__function_get_cycle_counter:
  push BP
  mov BP, SP
  in R0, TIM_CycleCounter
__function_get_cycle_counter_return:
  mov SP, BP
  pop BP
  ret

__function_get_frame_counter:
  push BP
  mov BP, SP
  in R0, TIM_FrameCounter
__function_get_frame_counter_return:
  mov SP, BP
  pop BP
  ret

__function_get_date:
  push BP
  mov BP, SP
  in R0, TIM_CurrentDate
__function_get_date_return:
  mov SP, BP
  pop BP
  ret

__function_get_time:
  push BP
  mov BP, SP
  in R0, TIM_CurrentTime
__function_get_time_return:
  mov SP, BP
  pop BP
  ret

__function_translate_date:
  push BP
  mov BP, SP
  isub SP, 15
  mov R0, [BP+2]
  shl R0, -16
  mov R1, [BP+3]
  mov [R1], R0
  mov R0, [BP+2]
  and R0, 65535
  mov [BP-1], R0
  mov R0, 31
  mov [BP-13], R0
  mov R0, 28
  mov [BP-12], R0
  mov R0, 31
  mov [BP-11], R0
  mov R0, 30
  mov [BP-10], R0
  mov R0, 31
  mov [BP-9], R0
  mov R0, 30
  mov [BP-8], R0
  mov R0, 31
  mov [BP-7], R0
  mov R0, 31
  mov [BP-6], R0
  mov R0, 30
  mov [BP-5], R0
  mov R0, 31
  mov [BP-4], R0
  mov R0, 30
  mov [BP-3], R0
  mov R0, 31
  mov [BP-2], R0
  mov R1, [BP+3]
  mov R0, [R1]
  imod R0, 4
  ieq R0, 0
  jf R0, __LogicalAnd_ShortCircuit_1407
  mov R2, [BP+3]
  mov R1, [R2]
  imod R1, 100
  ine R1, 0
  and R0, R1
__LogicalAnd_ShortCircuit_1407:
  mov [BP-14], R0
__if_1416_start:
  mov R0, [BP-14]
  jf R0, __if_1416_end
  mov R0, 29
  mov [BP-12], R0
__if_1416_end:
  mov R0, 1
  mov R1, [BP+3]
  iadd R1, 1
  mov [R1], R0
  mov R0, 0
  mov [BP-15], R0
__for_1427_start:
  mov R0, [BP-15]
  ilt R0, 11
  jf R0, __for_1427_end
__if_1437_start:
  mov R0, [BP-1]
  lea R1, [BP-13]
  mov R2, [BP-15]
  iadd R1, R2
  mov R1, [R1]
  ilt R0, R1
  jf R0, __if_1437_end
  mov R0, [BP-1]
  iadd R0, 1
  mov R1, [BP+3]
  iadd R1, 2
  mov [R1], R0
  jmp __function_translate_date_return
__if_1437_end:
  mov R0, [BP-1]
  lea R1, [BP-13]
  mov R2, [BP-15]
  iadd R1, R2
  mov R1, [R1]
  isub R0, R1
  mov [BP-1], R0
  mov R2, [BP+3]
  iadd R2, 1
  mov R0, [R2]
  mov R1, R0
  iadd R1, 1
  mov [R2], R1
__for_1427_continue:
  mov R0, [BP-15]
  iadd R0, 1
  mov [BP-15], R0
  jmp __for_1427_start
__for_1427_end:
  mov R0, 12
  mov R1, [BP+3]
  iadd R1, 1
  mov [R1], R0
  mov R0, [BP-1]
  iadd R0, 1
  mov R1, [BP+3]
  iadd R1, 2
  mov [R1], R0
__function_translate_date_return:
  mov SP, BP
  pop BP
  ret

__function_translate_time:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  idiv R0, 3600
  mov R1, [BP+3]
  mov [R1], R0
  mov R0, [BP+2]
  imod R0, 3600
  idiv R0, 60
  mov R1, [BP+3]
  iadd R1, 1
  mov [R1], R0
  mov R0, [BP+2]
  imod R0, 60
  mov R1, [BP+3]
  iadd R1, 2
  mov [R1], R0
__function_translate_time_return:
  mov SP, BP
  pop BP
  ret

__function_end_frame:
  push BP
  mov BP, SP
  wait
__function_end_frame_return:
  mov SP, BP
  pop BP
  ret

__function_sleep:
  push BP
  mov BP, SP
  isub SP, 2
  call __function_get_frame_counter
  mov [BP-1], R0
  mov R0, [BP-1]
  mov R1, [BP+2]
  iadd R0, R1
  mov [BP-2], R0
__while_1512_start:
__while_1512_continue:
  call __function_get_frame_counter
  mov R1, R0
  mov R2, [BP-2]
  ilt R1, R2
  mov R0, R1
  jf R0, __while_1512_end
  call __function_end_frame
  jmp __while_1512_start
__while_1512_end:
__function_sleep_return:
  mov SP, BP
  pop BP
  ret

__function_memset:
  push BP
  mov BP, SP
  mov CR, [BP+4]
  mov DR, [BP+2]
  mov SR, [BP+3]
  sets
__function_memset_return:
  mov SP, BP
  pop BP
  ret

__function_memcpy:
  push BP
  mov BP, SP
  mov CR, [BP+4]
  mov DR, [BP+2]
  mov SR, [BP+3]
  movs
__function_memcpy_return:
  mov SP, BP
  pop BP
  ret

__function_memcmp:
  push BP
  mov BP, SP
  mov CR, [BP+4]
  mov DR, [BP+2]
  mov SR, [BP+3]
  cmps R0
__function_memcmp_return:
  mov SP, BP
  pop BP
  ret

__function_merge_free_malloc_blocks:
  push BP
  mov BP, SP
  isub SP, 2
  mov R1, [BP+2]
  mov R0, [R1]
  mov [BP-1], R0
  mov R1, [BP+2]
  iadd R1, 1
  mov R0, [R1]
  mov [BP-2], R0
__if_1583_start:
  mov R0, [BP-2]
  ine R0, -1
  jf R0, __LogicalAnd_ShortCircuit_1585
  mov R2, [BP-2]
  iadd R2, 3
  mov R1, [R2]
  and R0, R1
__LogicalAnd_ShortCircuit_1585:
  jf R0, __if_1583_end
  mov R1, [BP-2]
  iadd R1, 1
  mov R0, [R1]
  mov R1, [BP+2]
  iadd R1, 1
  mov [R1], R0
__if_1594_start:
  mov R1, [BP-2]
  iadd R1, 1
  mov R0, [R1]
  ine R0, -1
  jf R0, __if_1594_end
  mov R0, [BP+2]
  mov R2, [BP-2]
  iadd R2, 1
  mov R1, [R2]
  mov [R1], R0
__if_1594_end:
  mov R1, [BP+2]
  iadd R1, 2
  mov R0, [R1]
  mov R2, [BP-2]
  iadd R2, 2
  mov R1, [R2]
  iadd R1, 4
  iadd R0, R1
  mov R1, [BP+2]
  iadd R1, 2
  mov [R1], R0
  mov R1, [BP+2]
  iadd R1, 1
  mov R0, [R1]
  mov [BP-2], R0
__if_1583_end:
__if_1613_start:
  mov R0, [BP-1]
  ine R0, -1
  jf R0, __LogicalAnd_ShortCircuit_1615
  mov R2, [BP-1]
  iadd R2, 3
  mov R1, [R2]
  and R0, R1
__LogicalAnd_ShortCircuit_1615:
  jf R0, __if_1613_end
  mov R0, [BP-2]
  mov R1, [BP-1]
  iadd R1, 1
  mov [R1], R0
__if_1623_start:
  mov R0, [BP-2]
  ine R0, -1
  jf R0, __if_1623_end
  mov R0, [BP-1]
  mov R1, [BP-2]
  mov [R1], R0
__if_1623_end:
  mov R1, [BP-1]
  iadd R1, 2
  mov R0, [R1]
  mov R2, [BP+2]
  iadd R2, 2
  mov R1, [R2]
  iadd R1, 4
  iadd R0, R1
  mov R1, [BP-1]
  iadd R1, 2
  mov [R1], R0
__if_1613_end:
__function_merge_free_malloc_blocks_return:
  mov SP, BP
  pop BP
  ret

__function_reduce_malloc_block:
  push BP
  mov BP, SP
  isub SP, 3
  mov R1, [BP+2]
  iadd R1, 2
  mov R0, [R1]
  mov R1, [BP+3]
  isub R0, R1
  mov [BP-1], R0
__if_1645_start:
  mov R0, [BP-1]
  ile R0, 4
  jf R0, __if_1645_end
  jmp __function_reduce_malloc_block_return
__if_1645_end:
  mov R0, [BP+2]
  iadd R0, 4
  mov R1, [BP+3]
  iadd R0, R1
  mov [BP-2], R0
  mov R0, [BP+2]
  mov R1, [BP-2]
  mov [R1], R0
  mov R1, [BP+2]
  iadd R1, 1
  mov R0, [R1]
  mov R1, [BP-2]
  iadd R1, 1
  mov [R1], R0
  mov R0, 1
  mov R1, [BP-2]
  iadd R1, 3
  mov [R1], R0
  mov R0, [BP-1]
  isub R0, 4
  mov R1, [BP-2]
  iadd R1, 2
  mov [R1], R0
  mov R0, [BP+3]
  mov R1, [BP+2]
  iadd R1, 2
  mov [R1], R0
  mov R0, [BP-2]
  mov R1, [BP+2]
  iadd R1, 1
  mov [R1], R0
__if_1688_start:
  mov R1, [BP-2]
  iadd R1, 1
  mov R0, [R1]
  ine R0, -1
  jf R0, __if_1688_end
  mov R0, [BP-2]
  mov R2, [BP-2]
  iadd R2, 1
  mov R1, [R2]
  mov [R1], R0
__if_1688_end:
  mov R1, [BP-2]
  mov [SP], R1
  call __function_merge_free_malloc_blocks
__function_reduce_malloc_block_return:
  mov SP, BP
  pop BP
  ret

__function_expand_malloc_block:
  push BP
  mov BP, SP
  isub SP, 3
  push R1
  push R2
  isub SP, 2
  mov R0, [BP+3]
  mov R2, [BP+2]
  iadd R2, 2
  mov R1, [R2]
  isub R0, R1
  mov [BP-1], R0
__if_1707_start:
  mov R0, [BP-1]
  ile R0, 0
  jf R0, __if_1707_end
  mov R0, 1
  jmp __function_expand_malloc_block_return
__if_1707_end:
  mov R1, [BP+2]
  iadd R1, 1
  mov R0, [R1]
  mov [BP-2], R0
__if_1717_start:
  mov R0, [BP-2]
  ine R0, -1
  bnot R0
  jt R0, __LogicalOr_ShortCircuit_1720
  mov R2, [BP-2]
  iadd R2, 3
  mov R1, [R2]
  bnot R1
  or R0, R1
__LogicalOr_ShortCircuit_1720:
  jf R0, __if_1717_end
  mov R0, 0
  jmp __function_expand_malloc_block_return
__if_1717_end:
  mov R1, [BP-2]
  iadd R1, 2
  mov R0, [R1]
  iadd R0, 4
  mov [BP-3], R0
__if_1732_start:
  mov R0, [BP-3]
  mov R1, [BP-1]
  ilt R0, R1
  jf R0, __if_1732_end
  mov R0, 0
  jmp __function_expand_malloc_block_return
__if_1732_end:
  mov R1, [BP+2]
  iadd R1, 2
  mov R0, [R1]
  mov R1, [BP-3]
  iadd R0, R1
  mov R1, [BP+2]
  iadd R1, 2
  mov [R1], R0
  mov R1, [BP-2]
  iadd R1, 1
  mov R0, [R1]
  mov R1, [BP+2]
  iadd R1, 1
  mov [R1], R0
__if_1747_start:
  mov R1, [BP-2]
  iadd R1, 1
  mov R0, [R1]
  ine R0, -1
  jf R0, __if_1747_end
  mov R0, [BP+2]
  mov R2, [BP-2]
  iadd R2, 1
  mov R1, [R2]
  mov [R1], R0
__if_1747_end:
  mov R1, [BP+2]
  mov [SP], R1
  mov R1, [BP+3]
  mov [SP+1], R1
  call __function_reduce_malloc_block
  mov R0, 1
__function_expand_malloc_block_return:
  iadd SP, 2
  pop R2
  pop R1
  mov SP, BP
  pop BP
  ret

__function_malloc:
  push BP
  mov BP, SP
  isub SP, 3
  push R1
  push R2
__if_1762_start:
  mov R0, [global_malloc_first_block]
  ine R0, -1
  bnot R0
  jf R0, __if_1762_end
  mov R0, [global_malloc_start_address]
  mov [global_malloc_first_block], R0
  mov R0, [global_malloc_end_address]
  mov R1, [global_malloc_start_address]
  isub R0, R1
  iadd R0, 1
  mov R1, [global_malloc_first_block]
  iadd R1, 2
  mov [R1], R0
  mov R1, [global_malloc_first_block]
  iadd R1, 2
  mov R0, [R1]
  isub R0, 4
  mov R1, [global_malloc_first_block]
  iadd R1, 2
  mov [R1], R0
  mov R0, -1
  mov R1, [global_malloc_first_block]
  mov [R1], R0
  mov R0, -1
  mov R1, [global_malloc_first_block]
  iadd R1, 1
  mov [R1], R0
  mov R0, 1
  mov R1, [global_malloc_first_block]
  iadd R1, 3
  mov [R1], R0
__if_1762_end:
__if_1797_start:
  mov R0, [BP+2]
  ile R0, 0
  jf R0, __if_1797_end
  mov R0, -1
  jmp __function_malloc_return
__if_1797_end:
  mov R0, [global_malloc_first_block]
  mov [BP-1], R0
__while_1806_start:
__while_1806_continue:
  mov R0, [BP-1]
  ine R0, -1
  jf R0, __while_1806_end
__if_1809_start:
  mov R1, [BP-1]
  iadd R1, 3
  mov R0, [R1]
  jf R0, __LogicalAnd_ShortCircuit_1812
  mov R2, [BP-1]
  iadd R2, 2
  mov R1, [R2]
  mov R2, [BP+2]
  ige R1, R2
  and R0, R1
__LogicalAnd_ShortCircuit_1812:
  jf R0, __if_1809_end
  jmp __while_1806_end
__if_1809_end:
  mov R1, [BP-1]
  iadd R1, 1
  mov R0, [R1]
  mov [BP-1], R0
  jmp __while_1806_start
__while_1806_end:
__if_1822_start:
  mov R0, [BP-1]
  ine R0, -1
  bnot R0
  jf R0, __if_1822_end
  mov R0, -1
  jmp __function_malloc_return
__if_1822_end:
  mov R0, [BP+2]
  iadd R0, 4
  mov [BP-2], R0
__if_1832_start:
  mov R1, [BP-1]
  iadd R1, 2
  mov R0, [R1]
  mov R1, [BP-2]
  igt R0, R1
  jf R0, __if_1832_else
  mov R0, [BP-1]
  iadd R0, 4
  mov R2, [BP-1]
  iadd R2, 2
  mov R1, [R2]
  iadd R0, R1
  mov R1, [BP-2]
  isub R0, R1
  mov [BP-3], R0
  mov R0, [BP+2]
  mov R1, [BP-3]
  iadd R1, 2
  mov [R1], R0
  mov R0, 0
  mov R1, [BP-3]
  iadd R1, 3
  mov [R1], R0
  mov R0, [BP-1]
  mov R1, [BP-3]
  mov [R1], R0
  mov R1, [BP-1]
  iadd R1, 1
  mov R0, [R1]
  mov R1, [BP-3]
  iadd R1, 1
  mov [R1], R0
  mov R1, [BP-1]
  iadd R1, 2
  mov R0, [R1]
  mov R1, [BP-2]
  isub R0, R1
  mov R1, [BP-1]
  iadd R1, 2
  mov [R1], R0
  mov R0, [BP-3]
  mov R1, [BP-1]
  iadd R1, 1
  mov [R1], R0
__if_1877_start:
  mov R1, [BP-3]
  iadd R1, 1
  mov R0, [R1]
  ine R0, -1
  jf R0, __if_1877_end
  mov R0, [BP-3]
  mov R2, [BP-3]
  iadd R2, 1
  mov R1, [R2]
  mov [R1], R0
__if_1877_end:
  mov R0, [BP-3]
  iadd R0, 4
  jmp __function_malloc_return
  jmp __if_1832_end
__if_1832_else:
  mov R0, 0
  mov R1, [BP-1]
  iadd R1, 3
  mov [R1], R0
  mov R0, [BP-1]
  iadd R0, 4
  jmp __function_malloc_return
__if_1832_end:
__function_malloc_return:
  pop R2
  pop R1
  mov SP, BP
  pop BP
  ret

__function_free:
  push BP
  mov BP, SP
  isub SP, 2
__if_1902_start:
  mov R0, [BP+2]
  ine R0, -1
  bnot R0
  jf R0, __if_1902_end
  jmp __function_free_return
__if_1902_end:
  mov R0, [BP+2]
  isub R0, 4
  mov [BP-1], R0
  mov R0, 1
  mov R1, [BP-1]
  iadd R1, 3
  mov [R1], R0
  mov R1, [BP-1]
  mov [SP], R1
  call __function_merge_free_malloc_blocks
__function_free_return:
  mov SP, BP
  pop BP
  ret

__function_calloc:
  push BP
  mov BP, SP
  isub SP, 2
  push R1
  isub SP, 3
  mov R0, [BP+2]
  mov R1, [BP+3]
  imul R0, R1
  mov [BP-1], R0
  mov R1, [BP-1]
  mov [SP], R1
  call __function_malloc
  mov [BP-2], R0
__if_1930_start:
  mov R0, [BP-2]
  ine R0, -1
  bnot R0
  jf R0, __if_1930_end
  mov R0, -1
  jmp __function_calloc_return
__if_1930_end:
  mov R1, [BP-2]
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, [BP-1]
  mov [SP+2], R1
  call __function_memset
  mov R0, [BP-2]
__function_calloc_return:
  iadd SP, 3
  pop R1
  mov SP, BP
  pop BP
  ret

__function_realloc:
  push BP
  mov BP, SP
  isub SP, 3
  push R1
  isub SP, 3
__if_1944_start:
  mov R0, [BP+2]
  ine R0, -1
  bnot R0
  jf R0, __if_1944_end
  mov R1, [BP+3]
  mov [SP], R1
  call __function_malloc
  jmp __function_realloc_return
__if_1944_end:
__if_1950_start:
  mov R0, [BP+3]
  ile R0, 0
  jf R0, __if_1950_end
  mov R1, [BP+2]
  mov [SP], R1
  call __function_free
  mov R0, -1
  jmp __function_realloc_return
__if_1950_end:
  mov R0, [BP+2]
  isub R0, 4
  mov [BP-1], R0
  mov R1, [BP-1]
  iadd R1, 2
  mov R0, [R1]
  mov [BP-2], R0
__if_1969_start:
  mov R0, [BP+3]
  mov R1, [BP-2]
  ieq R0, R1
  jf R0, __if_1969_end
  mov R0, [BP+2]
  jmp __function_realloc_return
__if_1969_end:
__if_1975_start:
  mov R0, [BP+3]
  mov R1, [BP-2]
  ilt R0, R1
  jf R0, __if_1975_else
  mov R1, [BP-1]
  mov [SP], R1
  mov R1, [BP+3]
  mov [SP+1], R1
  call __function_reduce_malloc_block
  mov R0, [BP+2]
  jmp __function_realloc_return
  jmp __if_1975_end
__if_1975_else:
__if_1986_start:
  mov R1, [BP-1]
  mov [SP], R1
  mov R1, [BP+3]
  mov [SP+1], R1
  call __function_expand_malloc_block
  jf R0, __if_1986_else
  mov R0, [BP+2]
  jmp __function_realloc_return
  jmp __if_1986_end
__if_1986_else:
  mov R1, [BP+3]
  mov [SP], R1
  call __function_malloc
  mov [BP-3], R0
__if_1997_start:
  mov R0, [BP-3]
  ine R0, -1
  bnot R0
  jf R0, __if_1997_end
  mov R0, -1
  jmp __function_realloc_return
__if_1997_end:
  mov R1, [BP-3]
  mov [SP], R1
  mov R1, [BP+2]
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  call __function_memcpy
  mov R1, [BP+2]
  mov [SP], R1
  call __function_free
  mov R0, [BP-3]
  jmp __function_realloc_return
__if_1986_end:
__if_1975_end:
__function_realloc_return:
  iadd SP, 3
  pop R1
  mov SP, BP
  pop BP
  ret

__function_rand:
  push BP
  mov BP, SP
  in R0, RNG_CurrentValue
__function_rand_return:
  mov SP, BP
  pop BP
  ret

__function_srand:
  push BP
  mov BP, SP
  mov R0, [BP+2]
  out RNG_CurrentValue, R0
__function_srand_return:
  mov SP, BP
  pop BP
  ret

__function_exit:
  push BP
  mov BP, SP
  hlt
__function_exit_return:
  mov SP, BP
  pop BP
  ret

__function_ease:
  push BP
  mov BP, SP
  isub SP, 3
  push R1
  push R2
  push R3
  isub SP, 1
__if_2025_start:
  mov R0, [BP+2]
  fle R0, 0.000000
  jf R0, __if_2025_else
  mov R0, 0.000000
  jmp __function_ease_return
  jmp __if_2025_end
__if_2025_else:
__if_2031_start:
  mov R0, [BP+2]
  fge R0, 1.000000
  jf R0, __if_2031_end
  mov R0, 1.000000
  jmp __function_ease_return
__if_2031_end:
__if_2025_end:
__if_2037_start:
  mov R0, [BP+2]
  flt R0, 0.500000
  jt R0, __LogicalOr_ShortCircuit_2042
  mov R1, [BP+4]
  ieq R1, 0
  or R0, R1
__LogicalOr_ShortCircuit_2042:
  jf R0, __if_2037_end
__if_2046_start:
  mov R0, [BP+4]
  ieq R0, 0
  jf R0, __if_2046_else
  mov R0, [BP+2]
  mov [BP-1], R0
  jmp __if_2046_end
__if_2046_else:
  mov R0, [BP+2]
  fmul R0, 2.000000
  mov [BP-1], R0
__if_2046_end:
__if_2058_start:
  mov R0, [BP+3]
  ieq R0, 1
  jf R0, __if_2058_else
  mov R0, [BP-1]
  mov [BP-2], R0
__if_2066_start:
  mov R0, [BP+4]
  ieq R0, 0
  jf R0, __if_2066_else
  mov R0, [BP-2]
  jmp __function_ease_return
  jmp __if_2066_end
__if_2066_else:
  mov R0, [BP-2]
  fmul R0, 0.500000
  jmp __function_ease_return
__if_2066_end:
  jmp __if_2058_end
__if_2058_else:
__if_2076_start:
  mov R0, [BP+3]
  ine R0, 0
  jf R0, __if_2076_end
  mov R0, [BP+3]
  mov R1, 2
  ieq R1, R0
  jt R1, __switch_2081_case_2
  mov R1, 3
  ieq R1, R0
  jt R1, __switch_2081_case_3
  mov R1, 4
  ieq R1, R0
  jt R1, __switch_2081_case_4
  mov R1, 5
  ieq R1, R0
  jt R1, __switch_2081_case_5
  mov R1, 6
  ieq R1, R0
  jt R1, __switch_2081_case_6
  jmp __switch_2081_end
__switch_2081_case_2:
  mov R2, [BP-1]
  fmul R2, 3.141593
  fdiv R2, 2.000000
  mov [SP], R2
  call __function_cos
  mov R1, R0
  fsgn R1
  fadd R1, 1.000000
  mov [BP-2], R1
  mov R0, R1
  jmp __switch_2081_end
__switch_2081_case_3:
  mov R0, [BP-1]
  mov R1, [BP-1]
  fmul R0, R1
  mov R1, [BP-1]
  fmul R0, R1
  mov [BP-2], R0
  jmp __switch_2081_end
__switch_2081_case_4:
  mov R0, [BP-1]
  mov R1, [BP-1]
  fmul R0, R1
  mov R1, [BP-1]
  fmul R0, R1
  mov R1, [BP-1]
  fmul R0, R1
  mov R1, [BP-1]
  fmul R0, R1
  mov [BP-2], R0
  jmp __switch_2081_end
__switch_2081_case_5:
  mov R2, [BP-1]
  mov R3, [BP-1]
  fmul R2, R3
  fsgn R2
  fadd R2, 1.000000
  mov [SP], R2
  call __function_sqrt
  mov R1, R0
  fsgn R1
  fadd R1, 1.000000
  mov [BP-2], R1
  mov R0, R1
  jmp __switch_2081_end
__switch_2081_case_6:
  mov R0, [BP-1]
  fmul R0, 2.701580
  mov R1, [BP-1]
  fmul R0, R1
  mov R1, [BP-1]
  fmul R0, R1
  mov R1, [BP-1]
  fmul R1, 1.701580
  mov R2, [BP-1]
  fmul R1, R2
  fsub R0, R1
  mov [BP-2], R0
__switch_2081_end:
__if_2152_start:
  mov R0, [BP+4]
  ieq R0, 0
  jf R0, __if_2152_else
  mov R0, [BP-2]
  jmp __function_ease_return
  jmp __if_2152_end
__if_2152_else:
  mov R0, [BP-2]
  fmul R0, 0.500000
  jmp __function_ease_return
__if_2152_end:
__if_2076_end:
__if_2058_end:
__if_2037_end:
__if_2162_start:
  mov R0, [BP+2]
  fge R0, 0.500000
  jt R0, __LogicalOr_ShortCircuit_2167
  mov R1, [BP+3]
  ieq R1, 0
  or R0, R1
__LogicalOr_ShortCircuit_2167:
  jf R0, __if_2162_end
__if_2171_start:
  mov R0, [BP+3]
  ieq R0, 0
  jf R0, __if_2171_else
  mov R0, [BP+2]
  mov [BP-1], R0
  jmp __if_2171_end
__if_2171_else:
  mov R0, [BP+2]
  fsub R0, 0.500000
  fmul R0, 2.000000
  mov [BP-1], R0
__if_2171_end:
__if_2186_start:
  mov R0, [BP+4]
  ieq R0, 1
  jf R0, __if_2186_else
  mov R0, [BP-1]
  mov [BP-2], R0
__if_2194_start:
  mov R0, [BP+3]
  ieq R0, 0
  jf R0, __if_2194_else
  mov R0, [BP-2]
  jmp __function_ease_return
  jmp __if_2194_end
__if_2194_else:
  mov R0, [BP-2]
  fmul R0, 0.500000
  fadd R0, 0.500000
  jmp __function_ease_return
__if_2194_end:
  jmp __if_2186_end
__if_2186_else:
__if_2206_start:
  mov R0, [BP+4]
  ine R0, 0
  jf R0, __if_2206_end
  mov R0, [BP-1]
  fsgn R0
  fadd R0, 1.000000
  mov [BP-3], R0
  mov R0, [BP+4]
  mov R1, 2
  ieq R1, R0
  jt R1, __switch_2217_case_2
  mov R1, 3
  ieq R1, R0
  jt R1, __switch_2217_case_3
  mov R1, 4
  ieq R1, R0
  jt R1, __switch_2217_case_4
  mov R1, 5
  ieq R1, R0
  jt R1, __switch_2217_case_5
  mov R1, 6
  ieq R1, R0
  jt R1, __switch_2217_case_6
  jmp __switch_2217_end
__switch_2217_case_2:
  mov R2, [BP-1]
  fmul R2, 3.141593
  fdiv R2, 2.000000
  mov [SP], R2
  call __function_sin
  mov R1, R0
  mov [BP-2], R1
  mov R0, R1
  jmp __switch_2217_end
__switch_2217_case_3:
  mov R0, [BP-3]
  mov R1, [BP-3]
  fmul R0, R1
  mov R1, [BP-3]
  fmul R0, R1
  fsgn R0
  fadd R0, 1.000000
  mov [BP-2], R0
  jmp __switch_2217_end
__switch_2217_case_4:
  mov R0, [BP-3]
  mov R1, [BP-3]
  fmul R0, R1
  mov R1, [BP-3]
  fmul R0, R1
  mov R1, [BP-3]
  fmul R0, R1
  mov R1, [BP-3]
  fmul R0, R1
  fsgn R0
  fadd R0, 1.000000
  mov [BP-2], R0
  jmp __switch_2217_end
__switch_2217_case_5:
  mov R2, [BP-3]
  mov R3, [BP-3]
  fmul R2, R3
  fsgn R2
  fadd R2, 1.000000
  mov [SP], R2
  call __function_sqrt
  mov R1, R0
  mov [BP-2], R1
  mov R0, R1
  jmp __switch_2217_end
__switch_2217_case_6:
  mov R0, [BP-1]
  fsub R0, 1.000000
  fmul R0, 2.701580
  mov R1, [BP-1]
  fsub R1, 1.000000
  fmul R0, R1
  mov R1, [BP-1]
  fsub R1, 1.000000
  fmul R0, R1
  fadd R0, 1.000000
  mov R1, [BP-1]
  fsub R1, 1.000000
  fmul R1, 1.701580
  mov R2, [BP-1]
  fsub R2, 1.000000
  fmul R1, R2
  fadd R0, R1
  mov [BP-2], R0
__switch_2217_end:
__if_2305_start:
  mov R0, [BP+3]
  ieq R0, 0
  jf R0, __if_2305_else
  mov R0, [BP-2]
  jmp __function_ease_return
  jmp __if_2305_end
__if_2305_else:
  mov R0, [BP-2]
  fmul R0, 0.500000
  fadd R0, 0.500000
  jmp __function_ease_return
__if_2305_end:
__if_2206_end:
__if_2186_end:
__if_2162_end:
__function_ease_return:
  iadd SP, 1
  pop R3
  pop R2
  pop R1
  mov SP, BP
  pop BP
  ret

__function_textfont_get_character_width:
  push BP
  mov BP, SP
  push R1
__if_2337_start:
  mov R1, [BP+2]
  iadd R1, 4
  mov R0, [R1]
  jf R0, __if_2337_end
  mov R0, [BP+2]
  iadd R0, 5
  mov R1, [BP+3]
  iadd R0, R1
  mov R0, [R0]
  jmp __function_textfont_get_character_width_return
__if_2337_end:
  mov R1, [BP+2]
  iadd R1, 2
  mov R0, [R1]
__function_textfont_get_character_width_return:
  pop R1
  mov SP, BP
  pop BP
  ret

__function_textfont_get_line_width:
  push BP
  mov BP, SP
  isub SP, 1
  push R1
  push R2
  push R3
  isub SP, 2
  mov R0, 0
  mov [BP-1], R0
__while_2354_start:
__while_2354_continue:
  mov R0, [BP+3]
  mov R0, [R0]
  cib R0
  jf R0, __LogicalAnd_ShortCircuit_2358
  mov R1, [BP+3]
  mov R1, [R1]
  ine R1, 10
  and R0, R1
__LogicalAnd_ShortCircuit_2358:
  jf R0, __while_2354_end
__if_2365_start:
  mov R0, [BP-1]
  ine R0, 0
  jf R0, __if_2365_end
  mov R0, [BP-1]
  mov R2, [BP+2]
  iadd R2, 261
  mov R1, [R2]
  iadd R0, R1
  mov [BP-1], R0
__if_2365_end:
  mov R1, [BP-1]
  mov R3, [BP+2]
  mov [SP], R3
  mov R3, [BP+3]
  mov R3, [R3]
  mov [SP+1], R3
  call __function_textfont_get_character_width
  mov R2, R0
  iadd R1, R2
  mov [BP-1], R1
  mov R0, R1
  mov R0, [BP+3]
  mov R1, R0
  iadd R1, 1
  mov [BP+3], R1
  jmp __while_2354_start
__while_2354_end:
  mov R0, [BP-1]
__function_textfont_get_line_width_return:
  iadd SP, 2
  pop R3
  pop R2
  pop R1
  mov SP, BP
  pop BP
  ret

__function_textfont_print_line_from_left:
  push BP
  mov BP, SP
  isub SP, 1
  push R1
  push R2
  push R3
  push R4
  isub SP, 2
  mov R0, 0
  mov [BP-1], R0
__while_2391_start:
__while_2391_continue:
  mov R0, [BP+5]
  mov R0, [R0]
  cib R0
  jf R0, __LogicalAnd_ShortCircuit_2395
  mov R1, [BP+5]
  mov R1, [R1]
  ine R1, 10
  and R0, R1
__LogicalAnd_ShortCircuit_2395:
  jf R0, __while_2391_end
  mov R2, [BP+2]
  iadd R2, 1
  mov R1, [R2]
  mov R2, [BP+5]
  mov R2, [R2]
  iadd R1, R2
  mov [SP], R1
  call __function_select_region
  mov R1, [BP+3]
  mov [SP], R1
  mov R1, [BP+4]
  mov [SP+1], R1
  call __function_draw_region_at
  mov R1, [BP+3]
  mov R3, [BP+2]
  mov [SP], R3
  mov R3, [BP+5]
  mov R3, [R3]
  mov [SP+1], R3
  call __function_textfont_get_character_width
  mov R2, R0
  mov R4, [BP+2]
  iadd R4, 261
  mov R3, [R4]
  iadd R2, R3
  iadd R1, R2
  mov [BP+3], R1
  mov R0, R1
  mov R0, [BP+5]
  mov R1, R0
  iadd R1, 1
  mov [BP+5], R1
  mov R0, [BP-1]
  mov R1, R0
  iadd R1, 1
  mov [BP-1], R1
  jmp __while_2391_start
__while_2391_end:
  mov R0, [BP-1]
__function_textfont_print_line_from_left_return:
  iadd SP, 2
  pop R4
  pop R3
  pop R2
  pop R1
  mov SP, BP
  pop BP
  ret

__function_textfont_print_from_left:
  push BP
  mov BP, SP
  isub SP, 5
  mov R2, [BP+2]
  mov R1, [R2]
  mov [SP], R1
  call __function_select_texture
__while_2434_start:
__while_2434_continue:
  mov R0, [BP+5]
  mov R0, [R0]
  cib R0
  jf R0, __while_2434_end
  mov R1, [BP+2]
  mov [SP], R1
  mov R1, [BP+3]
  mov [SP+1], R1
  mov R1, [BP+4]
  mov [SP+2], R1
  mov R1, [BP+5]
  mov [SP+3], R1
  call __function_textfont_print_line_from_left
  mov [BP-1], R0
  mov R0, [BP+5]
  mov R1, [BP-1]
  iadd R0, R1
  mov [BP+5], R0
  mov R0, [BP+4]
  mov R2, [BP+2]
  iadd R2, 3
  mov R1, [R2]
  mov R3, [BP+2]
  iadd R3, 262
  mov R2, [R3]
  iadd R1, R2
  iadd R0, R1
  mov [BP+4], R0
__if_2455_start:
  mov R0, [BP+5]
  mov R0, [R0]
  ieq R0, 10
  jf R0, __if_2455_end
  mov R0, [BP+5]
  mov R1, R0
  iadd R1, 1
  mov [BP+5], R1
__if_2455_end:
  jmp __while_2434_start
__while_2434_end:
__function_textfont_print_from_left_return:
  mov SP, BP
  pop BP
  ret

__function_textfont_print_from_right:
  push BP
  mov BP, SP
  isub SP, 7
  mov R2, [BP+2]
  mov R1, [R2]
  mov [SP], R1
  call __function_select_texture
__while_2470_start:
__while_2470_continue:
  mov R0, [BP+5]
  mov R0, [R0]
  cib R0
  jf R0, __while_2470_end
  mov R1, [BP+2]
  mov [SP], R1
  mov R1, [BP+5]
  mov [SP+1], R1
  call __function_textfont_get_line_width
  mov [BP-1], R0
  mov R0, [BP+3]
  mov R1, [BP-1]
  isub R0, R1
  iadd R0, 1
  mov [BP-2], R0
  mov R1, [BP+2]
  mov [SP], R1
  mov R1, [BP-2]
  mov [SP+1], R1
  mov R1, [BP+4]
  mov [SP+2], R1
  mov R1, [BP+5]
  mov [SP+3], R1
  call __function_textfont_print_line_from_left
  mov [BP-3], R0
  mov R0, [BP+5]
  mov R1, [BP-3]
  iadd R0, R1
  mov [BP+5], R0
  mov R0, [BP+4]
  mov R2, [BP+2]
  iadd R2, 3
  mov R1, [R2]
  mov R3, [BP+2]
  iadd R3, 262
  mov R2, [R3]
  iadd R1, R2
  iadd R0, R1
  mov [BP+4], R0
__if_2503_start:
  mov R0, [BP+5]
  mov R0, [R0]
  ieq R0, 10
  jf R0, __if_2503_end
  mov R0, [BP+5]
  mov R1, R0
  iadd R1, 1
  mov [BP+5], R1
__if_2503_end:
  jmp __while_2470_start
__while_2470_end:
__function_textfont_print_from_right_return:
  mov SP, BP
  pop BP
  ret

__function_textfont_print_centered:
  push BP
  mov BP, SP
  isub SP, 7
  mov R2, [BP+2]
  mov R1, [R2]
  mov [SP], R1
  call __function_select_texture
__while_2518_start:
__while_2518_continue:
  mov R0, [BP+5]
  mov R0, [R0]
  cib R0
  jf R0, __while_2518_end
  mov R1, [BP+2]
  mov [SP], R1
  mov R1, [BP+5]
  mov [SP+1], R1
  call __function_textfont_get_line_width
  mov [BP-1], R0
  mov R0, [BP+3]
  mov R1, [BP-1]
  idiv R1, 2
  isub R0, R1
  mov [BP-2], R0
  mov R1, [BP+2]
  mov [SP], R1
  mov R1, [BP-2]
  mov [SP+1], R1
  mov R1, [BP+4]
  mov [SP+2], R1
  mov R1, [BP+5]
  mov [SP+3], R1
  call __function_textfont_print_line_from_left
  mov [BP-3], R0
  mov R0, [BP+5]
  mov R1, [BP-3]
  iadd R0, R1
  mov [BP+5], R0
  mov R0, [BP+4]
  mov R2, [BP+2]
  iadd R2, 3
  mov R1, [R2]
  mov R3, [BP+2]
  iadd R3, 262
  mov R2, [R3]
  iadd R1, R2
  iadd R0, R1
  mov [BP+4], R0
__if_2551_start:
  mov R0, [BP+5]
  mov R0, [R0]
  ieq R0, 10
  jf R0, __if_2551_end
  mov R0, [BP+5]
  mov R1, R0
  iadd R1, 1
  mov [BP+5], R1
__if_2551_end:
  jmp __while_2518_start
__while_2518_end:
__function_textfont_print_centered_return:
  mov SP, BP
  pop BP
  ret

__function_textfont_read_region_widths:
  push BP
  mov BP, SP
  isub SP, 4
  mov R2, [BP+2]
  mov R1, [R2]
  mov [SP], R1
  call __function_select_texture
  mov R0, 0
  mov [BP-1], R0
__for_2563_start:
  mov R0, [BP-1]
  ilt R0, 256
  jf R0, __for_2563_end
  mov R2, [BP+2]
  iadd R2, 1
  mov R1, [R2]
  mov R2, [BP-1]
  iadd R1, R2
  mov [SP], R1
  call __function_select_region
  in R0, GPU_RegionMinX
  mov [BP-2], R0
  in R0, GPU_RegionMaxX
  mov [BP-3], R0
  mov R2, [BP-3]
  mov R3, [BP-2]
  isub R2, R3
  iadd R2, 1
  mov [SP], R2
  call __function_abs
  mov R1, R0
  mov R2, [BP+2]
  iadd R2, 5
  mov R3, [BP-1]
  iadd R2, R3
  mov [R2], R1
  mov R0, R1
__for_2563_continue:
  mov R0, [BP-1]
  iadd R0, 1
  mov [BP-1], R0
  jmp __for_2563_start
__for_2563_end:
__function_textfont_read_region_widths_return:
  mov SP, BP
  pop BP
  ret

__function_textfont_print_int_from_left:
  push BP
  mov BP, SP
  isub SP, 24
  mov R1, [BP+5]
  mov [SP], R1
  lea R1, [BP-20]
  mov [SP+1], R1
  mov R1, 10
  mov [SP+2], R1
  call __function_itoa
  mov R1, [BP+2]
  mov [SP], R1
  mov R1, [BP+3]
  mov [SP+1], R1
  mov R1, [BP+4]
  mov [SP+2], R1
  lea R1, [BP-20]
  mov [SP+3], R1
  call __function_textfont_print_line_from_left
__function_textfont_print_int_from_left_return:
  mov SP, BP
  pop BP
  ret

__function_textfont_print_float_from_left:
  push BP
  mov BP, SP
  isub SP, 34
  mov R1, [BP+5]
  mov [SP], R1
  lea R1, [BP-30]
  mov [SP+1], R1
  call __function_ftoa
  mov R1, [BP+2]
  mov [SP], R1
  mov R1, [BP+3]
  mov [SP+1], R1
  mov R1, [BP+4]
  mov [SP+2], R1
  lea R1, [BP-30]
  mov [SP+3], R1
  call __function_textfont_print_line_from_left
__function_textfont_print_float_from_left_return:
  mov SP, BP
  pop BP
  ret

__function_setupFontUbuntuMono_B_30:
  push BP
  mov BP, SP
  isub SP, 6
  mov R1, 1
  mov [SP], R1
  call __function_select_texture
  mov R1, 0
  mov [SP], R1
  call __function_select_region
  mov R1, 0
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, -1
  mov [SP+2], R1
  mov R1, 29
  mov [SP+3], R1
  mov R1, 0
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 1
  mov [SP], R1
  call __function_select_region
  mov R1, 15
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 29
  mov [SP+2], R1
  mov R1, 29
  mov [SP+3], R1
  mov R1, 15
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 2
  mov [SP], R1
  call __function_select_region
  mov R1, 30
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 44
  mov [SP+2], R1
  mov R1, 29
  mov [SP+3], R1
  mov R1, 30
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 3
  mov [SP], R1
  call __function_select_region
  mov R1, 45
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 59
  mov [SP+2], R1
  mov R1, 29
  mov [SP+3], R1
  mov R1, 45
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 4
  mov [SP], R1
  call __function_select_region
  mov R1, 60
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 74
  mov [SP+2], R1
  mov R1, 29
  mov [SP+3], R1
  mov R1, 60
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 5
  mov [SP], R1
  call __function_select_region
  mov R1, 75
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 89
  mov [SP+2], R1
  mov R1, 29
  mov [SP+3], R1
  mov R1, 75
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 6
  mov [SP], R1
  call __function_select_region
  mov R1, 90
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 104
  mov [SP+2], R1
  mov R1, 29
  mov [SP+3], R1
  mov R1, 90
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 7
  mov [SP], R1
  call __function_select_region
  mov R1, 105
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 119
  mov [SP+2], R1
  mov R1, 29
  mov [SP+3], R1
  mov R1, 105
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 8
  mov [SP], R1
  call __function_select_region
  mov R1, 120
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 134
  mov [SP+2], R1
  mov R1, 29
  mov [SP+3], R1
  mov R1, 120
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 9
  mov [SP], R1
  call __function_select_region
  mov R1, 135
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 149
  mov [SP+2], R1
  mov R1, 29
  mov [SP+3], R1
  mov R1, 135
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 10
  mov [SP], R1
  call __function_select_region
  mov R1, 150
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 164
  mov [SP+2], R1
  mov R1, 29
  mov [SP+3], R1
  mov R1, 150
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 11
  mov [SP], R1
  call __function_select_region
  mov R1, 165
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 179
  mov [SP+2], R1
  mov R1, 29
  mov [SP+3], R1
  mov R1, 165
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 12
  mov [SP], R1
  call __function_select_region
  mov R1, 180
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 194
  mov [SP+2], R1
  mov R1, 29
  mov [SP+3], R1
  mov R1, 180
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 13
  mov [SP], R1
  call __function_select_region
  mov R1, 195
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 209
  mov [SP+2], R1
  mov R1, 29
  mov [SP+3], R1
  mov R1, 195
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 14
  mov [SP], R1
  call __function_select_region
  mov R1, 210
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 224
  mov [SP+2], R1
  mov R1, 29
  mov [SP+3], R1
  mov R1, 210
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 15
  mov [SP], R1
  call __function_select_region
  mov R1, 225
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 239
  mov [SP+2], R1
  mov R1, 29
  mov [SP+3], R1
  mov R1, 225
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 16
  mov [SP], R1
  call __function_select_region
  mov R1, 0
  mov [SP], R1
  mov R1, 30
  mov [SP+1], R1
  mov R1, 14
  mov [SP+2], R1
  mov R1, 59
  mov [SP+3], R1
  mov R1, 0
  mov [SP+4], R1
  mov R1, 30
  mov [SP+5], R1
  call __function_define_region
  mov R1, 17
  mov [SP], R1
  call __function_select_region
  mov R1, 15
  mov [SP], R1
  mov R1, 30
  mov [SP+1], R1
  mov R1, 29
  mov [SP+2], R1
  mov R1, 59
  mov [SP+3], R1
  mov R1, 15
  mov [SP+4], R1
  mov R1, 30
  mov [SP+5], R1
  call __function_define_region
  mov R1, 18
  mov [SP], R1
  call __function_select_region
  mov R1, 30
  mov [SP], R1
  mov R1, 30
  mov [SP+1], R1
  mov R1, 44
  mov [SP+2], R1
  mov R1, 59
  mov [SP+3], R1
  mov R1, 30
  mov [SP+4], R1
  mov R1, 30
  mov [SP+5], R1
  call __function_define_region
  mov R1, 19
  mov [SP], R1
  call __function_select_region
  mov R1, 45
  mov [SP], R1
  mov R1, 30
  mov [SP+1], R1
  mov R1, 59
  mov [SP+2], R1
  mov R1, 59
  mov [SP+3], R1
  mov R1, 45
  mov [SP+4], R1
  mov R1, 30
  mov [SP+5], R1
  call __function_define_region
  mov R1, 20
  mov [SP], R1
  call __function_select_region
  mov R1, 60
  mov [SP], R1
  mov R1, 30
  mov [SP+1], R1
  mov R1, 74
  mov [SP+2], R1
  mov R1, 59
  mov [SP+3], R1
  mov R1, 60
  mov [SP+4], R1
  mov R1, 30
  mov [SP+5], R1
  call __function_define_region
  mov R1, 21
  mov [SP], R1
  call __function_select_region
  mov R1, 75
  mov [SP], R1
  mov R1, 30
  mov [SP+1], R1
  mov R1, 89
  mov [SP+2], R1
  mov R1, 59
  mov [SP+3], R1
  mov R1, 75
  mov [SP+4], R1
  mov R1, 30
  mov [SP+5], R1
  call __function_define_region
  mov R1, 22
  mov [SP], R1
  call __function_select_region
  mov R1, 90
  mov [SP], R1
  mov R1, 30
  mov [SP+1], R1
  mov R1, 104
  mov [SP+2], R1
  mov R1, 59
  mov [SP+3], R1
  mov R1, 90
  mov [SP+4], R1
  mov R1, 30
  mov [SP+5], R1
  call __function_define_region
  mov R1, 23
  mov [SP], R1
  call __function_select_region
  mov R1, 105
  mov [SP], R1
  mov R1, 30
  mov [SP+1], R1
  mov R1, 119
  mov [SP+2], R1
  mov R1, 59
  mov [SP+3], R1
  mov R1, 105
  mov [SP+4], R1
  mov R1, 30
  mov [SP+5], R1
  call __function_define_region
  mov R1, 24
  mov [SP], R1
  call __function_select_region
  mov R1, 120
  mov [SP], R1
  mov R1, 30
  mov [SP+1], R1
  mov R1, 134
  mov [SP+2], R1
  mov R1, 59
  mov [SP+3], R1
  mov R1, 120
  mov [SP+4], R1
  mov R1, 30
  mov [SP+5], R1
  call __function_define_region
  mov R1, 25
  mov [SP], R1
  call __function_select_region
  mov R1, 135
  mov [SP], R1
  mov R1, 30
  mov [SP+1], R1
  mov R1, 149
  mov [SP+2], R1
  mov R1, 59
  mov [SP+3], R1
  mov R1, 135
  mov [SP+4], R1
  mov R1, 30
  mov [SP+5], R1
  call __function_define_region
  mov R1, 26
  mov [SP], R1
  call __function_select_region
  mov R1, 150
  mov [SP], R1
  mov R1, 30
  mov [SP+1], R1
  mov R1, 164
  mov [SP+2], R1
  mov R1, 59
  mov [SP+3], R1
  mov R1, 150
  mov [SP+4], R1
  mov R1, 30
  mov [SP+5], R1
  call __function_define_region
  mov R1, 27
  mov [SP], R1
  call __function_select_region
  mov R1, 165
  mov [SP], R1
  mov R1, 30
  mov [SP+1], R1
  mov R1, 179
  mov [SP+2], R1
  mov R1, 59
  mov [SP+3], R1
  mov R1, 165
  mov [SP+4], R1
  mov R1, 30
  mov [SP+5], R1
  call __function_define_region
  mov R1, 28
  mov [SP], R1
  call __function_select_region
  mov R1, 180
  mov [SP], R1
  mov R1, 30
  mov [SP+1], R1
  mov R1, 194
  mov [SP+2], R1
  mov R1, 59
  mov [SP+3], R1
  mov R1, 180
  mov [SP+4], R1
  mov R1, 30
  mov [SP+5], R1
  call __function_define_region
  mov R1, 29
  mov [SP], R1
  call __function_select_region
  mov R1, 195
  mov [SP], R1
  mov R1, 30
  mov [SP+1], R1
  mov R1, 209
  mov [SP+2], R1
  mov R1, 59
  mov [SP+3], R1
  mov R1, 195
  mov [SP+4], R1
  mov R1, 30
  mov [SP+5], R1
  call __function_define_region
  mov R1, 30
  mov [SP], R1
  call __function_select_region
  mov R1, 210
  mov [SP], R1
  mov R1, 30
  mov [SP+1], R1
  mov R1, 224
  mov [SP+2], R1
  mov R1, 59
  mov [SP+3], R1
  mov R1, 210
  mov [SP+4], R1
  mov R1, 30
  mov [SP+5], R1
  call __function_define_region
  mov R1, 31
  mov [SP], R1
  call __function_select_region
  mov R1, 225
  mov [SP], R1
  mov R1, 30
  mov [SP+1], R1
  mov R1, 239
  mov [SP+2], R1
  mov R1, 59
  mov [SP+3], R1
  mov R1, 225
  mov [SP+4], R1
  mov R1, 30
  mov [SP+5], R1
  call __function_define_region
  mov R1, 32
  mov [SP], R1
  call __function_select_region
  mov R1, 0
  mov [SP], R1
  mov R1, 60
  mov [SP+1], R1
  mov R1, 14
  mov [SP+2], R1
  mov R1, 89
  mov [SP+3], R1
  mov R1, 0
  mov [SP+4], R1
  mov R1, 60
  mov [SP+5], R1
  call __function_define_region
  mov R1, 33
  mov [SP], R1
  call __function_select_region
  mov R1, 15
  mov [SP], R1
  mov R1, 60
  mov [SP+1], R1
  mov R1, 29
  mov [SP+2], R1
  mov R1, 89
  mov [SP+3], R1
  mov R1, 15
  mov [SP+4], R1
  mov R1, 60
  mov [SP+5], R1
  call __function_define_region
  mov R1, 34
  mov [SP], R1
  call __function_select_region
  mov R1, 30
  mov [SP], R1
  mov R1, 60
  mov [SP+1], R1
  mov R1, 44
  mov [SP+2], R1
  mov R1, 89
  mov [SP+3], R1
  mov R1, 30
  mov [SP+4], R1
  mov R1, 60
  mov [SP+5], R1
  call __function_define_region
  mov R1, 35
  mov [SP], R1
  call __function_select_region
  mov R1, 45
  mov [SP], R1
  mov R1, 60
  mov [SP+1], R1
  mov R1, 59
  mov [SP+2], R1
  mov R1, 89
  mov [SP+3], R1
  mov R1, 45
  mov [SP+4], R1
  mov R1, 60
  mov [SP+5], R1
  call __function_define_region
  mov R1, 36
  mov [SP], R1
  call __function_select_region
  mov R1, 60
  mov [SP], R1
  mov R1, 60
  mov [SP+1], R1
  mov R1, 74
  mov [SP+2], R1
  mov R1, 89
  mov [SP+3], R1
  mov R1, 60
  mov [SP+4], R1
  mov R1, 60
  mov [SP+5], R1
  call __function_define_region
  mov R1, 37
  mov [SP], R1
  call __function_select_region
  mov R1, 75
  mov [SP], R1
  mov R1, 60
  mov [SP+1], R1
  mov R1, 89
  mov [SP+2], R1
  mov R1, 89
  mov [SP+3], R1
  mov R1, 75
  mov [SP+4], R1
  mov R1, 60
  mov [SP+5], R1
  call __function_define_region
  mov R1, 38
  mov [SP], R1
  call __function_select_region
  mov R1, 90
  mov [SP], R1
  mov R1, 60
  mov [SP+1], R1
  mov R1, 104
  mov [SP+2], R1
  mov R1, 89
  mov [SP+3], R1
  mov R1, 90
  mov [SP+4], R1
  mov R1, 60
  mov [SP+5], R1
  call __function_define_region
  mov R1, 39
  mov [SP], R1
  call __function_select_region
  mov R1, 105
  mov [SP], R1
  mov R1, 60
  mov [SP+1], R1
  mov R1, 119
  mov [SP+2], R1
  mov R1, 89
  mov [SP+3], R1
  mov R1, 105
  mov [SP+4], R1
  mov R1, 60
  mov [SP+5], R1
  call __function_define_region
  mov R1, 40
  mov [SP], R1
  call __function_select_region
  mov R1, 120
  mov [SP], R1
  mov R1, 60
  mov [SP+1], R1
  mov R1, 134
  mov [SP+2], R1
  mov R1, 89
  mov [SP+3], R1
  mov R1, 120
  mov [SP+4], R1
  mov R1, 60
  mov [SP+5], R1
  call __function_define_region
  mov R1, 41
  mov [SP], R1
  call __function_select_region
  mov R1, 135
  mov [SP], R1
  mov R1, 60
  mov [SP+1], R1
  mov R1, 149
  mov [SP+2], R1
  mov R1, 89
  mov [SP+3], R1
  mov R1, 135
  mov [SP+4], R1
  mov R1, 60
  mov [SP+5], R1
  call __function_define_region
  mov R1, 42
  mov [SP], R1
  call __function_select_region
  mov R1, 150
  mov [SP], R1
  mov R1, 60
  mov [SP+1], R1
  mov R1, 164
  mov [SP+2], R1
  mov R1, 89
  mov [SP+3], R1
  mov R1, 150
  mov [SP+4], R1
  mov R1, 60
  mov [SP+5], R1
  call __function_define_region
  mov R1, 43
  mov [SP], R1
  call __function_select_region
  mov R1, 165
  mov [SP], R1
  mov R1, 60
  mov [SP+1], R1
  mov R1, 179
  mov [SP+2], R1
  mov R1, 89
  mov [SP+3], R1
  mov R1, 165
  mov [SP+4], R1
  mov R1, 60
  mov [SP+5], R1
  call __function_define_region
  mov R1, 44
  mov [SP], R1
  call __function_select_region
  mov R1, 180
  mov [SP], R1
  mov R1, 60
  mov [SP+1], R1
  mov R1, 194
  mov [SP+2], R1
  mov R1, 89
  mov [SP+3], R1
  mov R1, 180
  mov [SP+4], R1
  mov R1, 60
  mov [SP+5], R1
  call __function_define_region
  mov R1, 45
  mov [SP], R1
  call __function_select_region
  mov R1, 195
  mov [SP], R1
  mov R1, 60
  mov [SP+1], R1
  mov R1, 209
  mov [SP+2], R1
  mov R1, 89
  mov [SP+3], R1
  mov R1, 195
  mov [SP+4], R1
  mov R1, 60
  mov [SP+5], R1
  call __function_define_region
  mov R1, 46
  mov [SP], R1
  call __function_select_region
  mov R1, 210
  mov [SP], R1
  mov R1, 60
  mov [SP+1], R1
  mov R1, 224
  mov [SP+2], R1
  mov R1, 89
  mov [SP+3], R1
  mov R1, 210
  mov [SP+4], R1
  mov R1, 60
  mov [SP+5], R1
  call __function_define_region
  mov R1, 47
  mov [SP], R1
  call __function_select_region
  mov R1, 225
  mov [SP], R1
  mov R1, 60
  mov [SP+1], R1
  mov R1, 239
  mov [SP+2], R1
  mov R1, 89
  mov [SP+3], R1
  mov R1, 225
  mov [SP+4], R1
  mov R1, 60
  mov [SP+5], R1
  call __function_define_region
  mov R1, 48
  mov [SP], R1
  call __function_select_region
  mov R1, 0
  mov [SP], R1
  mov R1, 90
  mov [SP+1], R1
  mov R1, 14
  mov [SP+2], R1
  mov R1, 119
  mov [SP+3], R1
  mov R1, 0
  mov [SP+4], R1
  mov R1, 90
  mov [SP+5], R1
  call __function_define_region
  mov R1, 49
  mov [SP], R1
  call __function_select_region
  mov R1, 15
  mov [SP], R1
  mov R1, 90
  mov [SP+1], R1
  mov R1, 29
  mov [SP+2], R1
  mov R1, 119
  mov [SP+3], R1
  mov R1, 15
  mov [SP+4], R1
  mov R1, 90
  mov [SP+5], R1
  call __function_define_region
  mov R1, 50
  mov [SP], R1
  call __function_select_region
  mov R1, 30
  mov [SP], R1
  mov R1, 90
  mov [SP+1], R1
  mov R1, 44
  mov [SP+2], R1
  mov R1, 119
  mov [SP+3], R1
  mov R1, 30
  mov [SP+4], R1
  mov R1, 90
  mov [SP+5], R1
  call __function_define_region
  mov R1, 51
  mov [SP], R1
  call __function_select_region
  mov R1, 45
  mov [SP], R1
  mov R1, 90
  mov [SP+1], R1
  mov R1, 59
  mov [SP+2], R1
  mov R1, 119
  mov [SP+3], R1
  mov R1, 45
  mov [SP+4], R1
  mov R1, 90
  mov [SP+5], R1
  call __function_define_region
  mov R1, 52
  mov [SP], R1
  call __function_select_region
  mov R1, 60
  mov [SP], R1
  mov R1, 90
  mov [SP+1], R1
  mov R1, 74
  mov [SP+2], R1
  mov R1, 119
  mov [SP+3], R1
  mov R1, 60
  mov [SP+4], R1
  mov R1, 90
  mov [SP+5], R1
  call __function_define_region
  mov R1, 53
  mov [SP], R1
  call __function_select_region
  mov R1, 75
  mov [SP], R1
  mov R1, 90
  mov [SP+1], R1
  mov R1, 89
  mov [SP+2], R1
  mov R1, 119
  mov [SP+3], R1
  mov R1, 75
  mov [SP+4], R1
  mov R1, 90
  mov [SP+5], R1
  call __function_define_region
  mov R1, 54
  mov [SP], R1
  call __function_select_region
  mov R1, 90
  mov [SP], R1
  mov R1, 90
  mov [SP+1], R1
  mov R1, 104
  mov [SP+2], R1
  mov R1, 119
  mov [SP+3], R1
  mov R1, 90
  mov [SP+4], R1
  mov R1, 90
  mov [SP+5], R1
  call __function_define_region
  mov R1, 55
  mov [SP], R1
  call __function_select_region
  mov R1, 105
  mov [SP], R1
  mov R1, 90
  mov [SP+1], R1
  mov R1, 119
  mov [SP+2], R1
  mov R1, 119
  mov [SP+3], R1
  mov R1, 105
  mov [SP+4], R1
  mov R1, 90
  mov [SP+5], R1
  call __function_define_region
  mov R1, 56
  mov [SP], R1
  call __function_select_region
  mov R1, 120
  mov [SP], R1
  mov R1, 90
  mov [SP+1], R1
  mov R1, 134
  mov [SP+2], R1
  mov R1, 119
  mov [SP+3], R1
  mov R1, 120
  mov [SP+4], R1
  mov R1, 90
  mov [SP+5], R1
  call __function_define_region
  mov R1, 57
  mov [SP], R1
  call __function_select_region
  mov R1, 135
  mov [SP], R1
  mov R1, 90
  mov [SP+1], R1
  mov R1, 149
  mov [SP+2], R1
  mov R1, 119
  mov [SP+3], R1
  mov R1, 135
  mov [SP+4], R1
  mov R1, 90
  mov [SP+5], R1
  call __function_define_region
  mov R1, 58
  mov [SP], R1
  call __function_select_region
  mov R1, 150
  mov [SP], R1
  mov R1, 90
  mov [SP+1], R1
  mov R1, 164
  mov [SP+2], R1
  mov R1, 119
  mov [SP+3], R1
  mov R1, 150
  mov [SP+4], R1
  mov R1, 90
  mov [SP+5], R1
  call __function_define_region
  mov R1, 59
  mov [SP], R1
  call __function_select_region
  mov R1, 165
  mov [SP], R1
  mov R1, 90
  mov [SP+1], R1
  mov R1, 179
  mov [SP+2], R1
  mov R1, 119
  mov [SP+3], R1
  mov R1, 165
  mov [SP+4], R1
  mov R1, 90
  mov [SP+5], R1
  call __function_define_region
  mov R1, 60
  mov [SP], R1
  call __function_select_region
  mov R1, 180
  mov [SP], R1
  mov R1, 90
  mov [SP+1], R1
  mov R1, 194
  mov [SP+2], R1
  mov R1, 119
  mov [SP+3], R1
  mov R1, 180
  mov [SP+4], R1
  mov R1, 90
  mov [SP+5], R1
  call __function_define_region
  mov R1, 61
  mov [SP], R1
  call __function_select_region
  mov R1, 195
  mov [SP], R1
  mov R1, 90
  mov [SP+1], R1
  mov R1, 209
  mov [SP+2], R1
  mov R1, 119
  mov [SP+3], R1
  mov R1, 195
  mov [SP+4], R1
  mov R1, 90
  mov [SP+5], R1
  call __function_define_region
  mov R1, 62
  mov [SP], R1
  call __function_select_region
  mov R1, 210
  mov [SP], R1
  mov R1, 90
  mov [SP+1], R1
  mov R1, 224
  mov [SP+2], R1
  mov R1, 119
  mov [SP+3], R1
  mov R1, 210
  mov [SP+4], R1
  mov R1, 90
  mov [SP+5], R1
  call __function_define_region
  mov R1, 63
  mov [SP], R1
  call __function_select_region
  mov R1, 225
  mov [SP], R1
  mov R1, 90
  mov [SP+1], R1
  mov R1, 239
  mov [SP+2], R1
  mov R1, 119
  mov [SP+3], R1
  mov R1, 225
  mov [SP+4], R1
  mov R1, 90
  mov [SP+5], R1
  call __function_define_region
  mov R1, 64
  mov [SP], R1
  call __function_select_region
  mov R1, 0
  mov [SP], R1
  mov R1, 120
  mov [SP+1], R1
  mov R1, 14
  mov [SP+2], R1
  mov R1, 149
  mov [SP+3], R1
  mov R1, 0
  mov [SP+4], R1
  mov R1, 120
  mov [SP+5], R1
  call __function_define_region
  mov R1, 65
  mov [SP], R1
  call __function_select_region
  mov R1, 15
  mov [SP], R1
  mov R1, 120
  mov [SP+1], R1
  mov R1, 29
  mov [SP+2], R1
  mov R1, 149
  mov [SP+3], R1
  mov R1, 15
  mov [SP+4], R1
  mov R1, 120
  mov [SP+5], R1
  call __function_define_region
  mov R1, 66
  mov [SP], R1
  call __function_select_region
  mov R1, 30
  mov [SP], R1
  mov R1, 120
  mov [SP+1], R1
  mov R1, 44
  mov [SP+2], R1
  mov R1, 149
  mov [SP+3], R1
  mov R1, 30
  mov [SP+4], R1
  mov R1, 120
  mov [SP+5], R1
  call __function_define_region
  mov R1, 67
  mov [SP], R1
  call __function_select_region
  mov R1, 45
  mov [SP], R1
  mov R1, 120
  mov [SP+1], R1
  mov R1, 59
  mov [SP+2], R1
  mov R1, 149
  mov [SP+3], R1
  mov R1, 45
  mov [SP+4], R1
  mov R1, 120
  mov [SP+5], R1
  call __function_define_region
  mov R1, 68
  mov [SP], R1
  call __function_select_region
  mov R1, 60
  mov [SP], R1
  mov R1, 120
  mov [SP+1], R1
  mov R1, 74
  mov [SP+2], R1
  mov R1, 149
  mov [SP+3], R1
  mov R1, 60
  mov [SP+4], R1
  mov R1, 120
  mov [SP+5], R1
  call __function_define_region
  mov R1, 69
  mov [SP], R1
  call __function_select_region
  mov R1, 75
  mov [SP], R1
  mov R1, 120
  mov [SP+1], R1
  mov R1, 89
  mov [SP+2], R1
  mov R1, 149
  mov [SP+3], R1
  mov R1, 75
  mov [SP+4], R1
  mov R1, 120
  mov [SP+5], R1
  call __function_define_region
  mov R1, 70
  mov [SP], R1
  call __function_select_region
  mov R1, 90
  mov [SP], R1
  mov R1, 120
  mov [SP+1], R1
  mov R1, 104
  mov [SP+2], R1
  mov R1, 149
  mov [SP+3], R1
  mov R1, 90
  mov [SP+4], R1
  mov R1, 120
  mov [SP+5], R1
  call __function_define_region
  mov R1, 71
  mov [SP], R1
  call __function_select_region
  mov R1, 105
  mov [SP], R1
  mov R1, 120
  mov [SP+1], R1
  mov R1, 119
  mov [SP+2], R1
  mov R1, 149
  mov [SP+3], R1
  mov R1, 105
  mov [SP+4], R1
  mov R1, 120
  mov [SP+5], R1
  call __function_define_region
  mov R1, 72
  mov [SP], R1
  call __function_select_region
  mov R1, 120
  mov [SP], R1
  mov R1, 120
  mov [SP+1], R1
  mov R1, 134
  mov [SP+2], R1
  mov R1, 149
  mov [SP+3], R1
  mov R1, 120
  mov [SP+4], R1
  mov R1, 120
  mov [SP+5], R1
  call __function_define_region
  mov R1, 73
  mov [SP], R1
  call __function_select_region
  mov R1, 135
  mov [SP], R1
  mov R1, 120
  mov [SP+1], R1
  mov R1, 149
  mov [SP+2], R1
  mov R1, 149
  mov [SP+3], R1
  mov R1, 135
  mov [SP+4], R1
  mov R1, 120
  mov [SP+5], R1
  call __function_define_region
  mov R1, 74
  mov [SP], R1
  call __function_select_region
  mov R1, 150
  mov [SP], R1
  mov R1, 120
  mov [SP+1], R1
  mov R1, 164
  mov [SP+2], R1
  mov R1, 149
  mov [SP+3], R1
  mov R1, 150
  mov [SP+4], R1
  mov R1, 120
  mov [SP+5], R1
  call __function_define_region
  mov R1, 75
  mov [SP], R1
  call __function_select_region
  mov R1, 165
  mov [SP], R1
  mov R1, 120
  mov [SP+1], R1
  mov R1, 179
  mov [SP+2], R1
  mov R1, 149
  mov [SP+3], R1
  mov R1, 165
  mov [SP+4], R1
  mov R1, 120
  mov [SP+5], R1
  call __function_define_region
  mov R1, 76
  mov [SP], R1
  call __function_select_region
  mov R1, 180
  mov [SP], R1
  mov R1, 120
  mov [SP+1], R1
  mov R1, 194
  mov [SP+2], R1
  mov R1, 149
  mov [SP+3], R1
  mov R1, 180
  mov [SP+4], R1
  mov R1, 120
  mov [SP+5], R1
  call __function_define_region
  mov R1, 77
  mov [SP], R1
  call __function_select_region
  mov R1, 195
  mov [SP], R1
  mov R1, 120
  mov [SP+1], R1
  mov R1, 209
  mov [SP+2], R1
  mov R1, 149
  mov [SP+3], R1
  mov R1, 195
  mov [SP+4], R1
  mov R1, 120
  mov [SP+5], R1
  call __function_define_region
  mov R1, 78
  mov [SP], R1
  call __function_select_region
  mov R1, 210
  mov [SP], R1
  mov R1, 120
  mov [SP+1], R1
  mov R1, 224
  mov [SP+2], R1
  mov R1, 149
  mov [SP+3], R1
  mov R1, 210
  mov [SP+4], R1
  mov R1, 120
  mov [SP+5], R1
  call __function_define_region
  mov R1, 79
  mov [SP], R1
  call __function_select_region
  mov R1, 225
  mov [SP], R1
  mov R1, 120
  mov [SP+1], R1
  mov R1, 239
  mov [SP+2], R1
  mov R1, 149
  mov [SP+3], R1
  mov R1, 225
  mov [SP+4], R1
  mov R1, 120
  mov [SP+5], R1
  call __function_define_region
  mov R1, 80
  mov [SP], R1
  call __function_select_region
  mov R1, 0
  mov [SP], R1
  mov R1, 150
  mov [SP+1], R1
  mov R1, 14
  mov [SP+2], R1
  mov R1, 179
  mov [SP+3], R1
  mov R1, 0
  mov [SP+4], R1
  mov R1, 150
  mov [SP+5], R1
  call __function_define_region
  mov R1, 81
  mov [SP], R1
  call __function_select_region
  mov R1, 15
  mov [SP], R1
  mov R1, 150
  mov [SP+1], R1
  mov R1, 29
  mov [SP+2], R1
  mov R1, 179
  mov [SP+3], R1
  mov R1, 15
  mov [SP+4], R1
  mov R1, 150
  mov [SP+5], R1
  call __function_define_region
  mov R1, 82
  mov [SP], R1
  call __function_select_region
  mov R1, 30
  mov [SP], R1
  mov R1, 150
  mov [SP+1], R1
  mov R1, 44
  mov [SP+2], R1
  mov R1, 179
  mov [SP+3], R1
  mov R1, 30
  mov [SP+4], R1
  mov R1, 150
  mov [SP+5], R1
  call __function_define_region
  mov R1, 83
  mov [SP], R1
  call __function_select_region
  mov R1, 45
  mov [SP], R1
  mov R1, 150
  mov [SP+1], R1
  mov R1, 59
  mov [SP+2], R1
  mov R1, 179
  mov [SP+3], R1
  mov R1, 45
  mov [SP+4], R1
  mov R1, 150
  mov [SP+5], R1
  call __function_define_region
  mov R1, 84
  mov [SP], R1
  call __function_select_region
  mov R1, 60
  mov [SP], R1
  mov R1, 150
  mov [SP+1], R1
  mov R1, 74
  mov [SP+2], R1
  mov R1, 179
  mov [SP+3], R1
  mov R1, 60
  mov [SP+4], R1
  mov R1, 150
  mov [SP+5], R1
  call __function_define_region
  mov R1, 85
  mov [SP], R1
  call __function_select_region
  mov R1, 75
  mov [SP], R1
  mov R1, 150
  mov [SP+1], R1
  mov R1, 89
  mov [SP+2], R1
  mov R1, 179
  mov [SP+3], R1
  mov R1, 75
  mov [SP+4], R1
  mov R1, 150
  mov [SP+5], R1
  call __function_define_region
  mov R1, 86
  mov [SP], R1
  call __function_select_region
  mov R1, 90
  mov [SP], R1
  mov R1, 150
  mov [SP+1], R1
  mov R1, 104
  mov [SP+2], R1
  mov R1, 179
  mov [SP+3], R1
  mov R1, 90
  mov [SP+4], R1
  mov R1, 150
  mov [SP+5], R1
  call __function_define_region
  mov R1, 87
  mov [SP], R1
  call __function_select_region
  mov R1, 105
  mov [SP], R1
  mov R1, 150
  mov [SP+1], R1
  mov R1, 119
  mov [SP+2], R1
  mov R1, 179
  mov [SP+3], R1
  mov R1, 105
  mov [SP+4], R1
  mov R1, 150
  mov [SP+5], R1
  call __function_define_region
  mov R1, 88
  mov [SP], R1
  call __function_select_region
  mov R1, 120
  mov [SP], R1
  mov R1, 150
  mov [SP+1], R1
  mov R1, 134
  mov [SP+2], R1
  mov R1, 179
  mov [SP+3], R1
  mov R1, 120
  mov [SP+4], R1
  mov R1, 150
  mov [SP+5], R1
  call __function_define_region
  mov R1, 89
  mov [SP], R1
  call __function_select_region
  mov R1, 135
  mov [SP], R1
  mov R1, 150
  mov [SP+1], R1
  mov R1, 149
  mov [SP+2], R1
  mov R1, 179
  mov [SP+3], R1
  mov R1, 135
  mov [SP+4], R1
  mov R1, 150
  mov [SP+5], R1
  call __function_define_region
  mov R1, 90
  mov [SP], R1
  call __function_select_region
  mov R1, 150
  mov [SP], R1
  mov R1, 150
  mov [SP+1], R1
  mov R1, 164
  mov [SP+2], R1
  mov R1, 179
  mov [SP+3], R1
  mov R1, 150
  mov [SP+4], R1
  mov R1, 150
  mov [SP+5], R1
  call __function_define_region
  mov R1, 91
  mov [SP], R1
  call __function_select_region
  mov R1, 165
  mov [SP], R1
  mov R1, 150
  mov [SP+1], R1
  mov R1, 179
  mov [SP+2], R1
  mov R1, 179
  mov [SP+3], R1
  mov R1, 165
  mov [SP+4], R1
  mov R1, 150
  mov [SP+5], R1
  call __function_define_region
  mov R1, 92
  mov [SP], R1
  call __function_select_region
  mov R1, 180
  mov [SP], R1
  mov R1, 150
  mov [SP+1], R1
  mov R1, 194
  mov [SP+2], R1
  mov R1, 179
  mov [SP+3], R1
  mov R1, 180
  mov [SP+4], R1
  mov R1, 150
  mov [SP+5], R1
  call __function_define_region
  mov R1, 93
  mov [SP], R1
  call __function_select_region
  mov R1, 195
  mov [SP], R1
  mov R1, 150
  mov [SP+1], R1
  mov R1, 209
  mov [SP+2], R1
  mov R1, 179
  mov [SP+3], R1
  mov R1, 195
  mov [SP+4], R1
  mov R1, 150
  mov [SP+5], R1
  call __function_define_region
  mov R1, 94
  mov [SP], R1
  call __function_select_region
  mov R1, 210
  mov [SP], R1
  mov R1, 150
  mov [SP+1], R1
  mov R1, 224
  mov [SP+2], R1
  mov R1, 179
  mov [SP+3], R1
  mov R1, 210
  mov [SP+4], R1
  mov R1, 150
  mov [SP+5], R1
  call __function_define_region
  mov R1, 95
  mov [SP], R1
  call __function_select_region
  mov R1, 225
  mov [SP], R1
  mov R1, 150
  mov [SP+1], R1
  mov R1, 239
  mov [SP+2], R1
  mov R1, 179
  mov [SP+3], R1
  mov R1, 225
  mov [SP+4], R1
  mov R1, 150
  mov [SP+5], R1
  call __function_define_region
  mov R1, 96
  mov [SP], R1
  call __function_select_region
  mov R1, 0
  mov [SP], R1
  mov R1, 180
  mov [SP+1], R1
  mov R1, 14
  mov [SP+2], R1
  mov R1, 209
  mov [SP+3], R1
  mov R1, 0
  mov [SP+4], R1
  mov R1, 180
  mov [SP+5], R1
  call __function_define_region
  mov R1, 97
  mov [SP], R1
  call __function_select_region
  mov R1, 15
  mov [SP], R1
  mov R1, 180
  mov [SP+1], R1
  mov R1, 29
  mov [SP+2], R1
  mov R1, 209
  mov [SP+3], R1
  mov R1, 15
  mov [SP+4], R1
  mov R1, 180
  mov [SP+5], R1
  call __function_define_region
  mov R1, 98
  mov [SP], R1
  call __function_select_region
  mov R1, 30
  mov [SP], R1
  mov R1, 180
  mov [SP+1], R1
  mov R1, 44
  mov [SP+2], R1
  mov R1, 209
  mov [SP+3], R1
  mov R1, 30
  mov [SP+4], R1
  mov R1, 180
  mov [SP+5], R1
  call __function_define_region
  mov R1, 99
  mov [SP], R1
  call __function_select_region
  mov R1, 45
  mov [SP], R1
  mov R1, 180
  mov [SP+1], R1
  mov R1, 59
  mov [SP+2], R1
  mov R1, 209
  mov [SP+3], R1
  mov R1, 45
  mov [SP+4], R1
  mov R1, 180
  mov [SP+5], R1
  call __function_define_region
  mov R1, 100
  mov [SP], R1
  call __function_select_region
  mov R1, 60
  mov [SP], R1
  mov R1, 180
  mov [SP+1], R1
  mov R1, 74
  mov [SP+2], R1
  mov R1, 209
  mov [SP+3], R1
  mov R1, 60
  mov [SP+4], R1
  mov R1, 180
  mov [SP+5], R1
  call __function_define_region
  mov R1, 101
  mov [SP], R1
  call __function_select_region
  mov R1, 75
  mov [SP], R1
  mov R1, 180
  mov [SP+1], R1
  mov R1, 89
  mov [SP+2], R1
  mov R1, 209
  mov [SP+3], R1
  mov R1, 75
  mov [SP+4], R1
  mov R1, 180
  mov [SP+5], R1
  call __function_define_region
  mov R1, 102
  mov [SP], R1
  call __function_select_region
  mov R1, 90
  mov [SP], R1
  mov R1, 180
  mov [SP+1], R1
  mov R1, 104
  mov [SP+2], R1
  mov R1, 209
  mov [SP+3], R1
  mov R1, 90
  mov [SP+4], R1
  mov R1, 180
  mov [SP+5], R1
  call __function_define_region
  mov R1, 103
  mov [SP], R1
  call __function_select_region
  mov R1, 105
  mov [SP], R1
  mov R1, 180
  mov [SP+1], R1
  mov R1, 119
  mov [SP+2], R1
  mov R1, 209
  mov [SP+3], R1
  mov R1, 105
  mov [SP+4], R1
  mov R1, 180
  mov [SP+5], R1
  call __function_define_region
  mov R1, 104
  mov [SP], R1
  call __function_select_region
  mov R1, 120
  mov [SP], R1
  mov R1, 180
  mov [SP+1], R1
  mov R1, 134
  mov [SP+2], R1
  mov R1, 209
  mov [SP+3], R1
  mov R1, 120
  mov [SP+4], R1
  mov R1, 180
  mov [SP+5], R1
  call __function_define_region
  mov R1, 105
  mov [SP], R1
  call __function_select_region
  mov R1, 135
  mov [SP], R1
  mov R1, 180
  mov [SP+1], R1
  mov R1, 149
  mov [SP+2], R1
  mov R1, 209
  mov [SP+3], R1
  mov R1, 135
  mov [SP+4], R1
  mov R1, 180
  mov [SP+5], R1
  call __function_define_region
  mov R1, 106
  mov [SP], R1
  call __function_select_region
  mov R1, 150
  mov [SP], R1
  mov R1, 180
  mov [SP+1], R1
  mov R1, 164
  mov [SP+2], R1
  mov R1, 209
  mov [SP+3], R1
  mov R1, 150
  mov [SP+4], R1
  mov R1, 180
  mov [SP+5], R1
  call __function_define_region
  mov R1, 107
  mov [SP], R1
  call __function_select_region
  mov R1, 165
  mov [SP], R1
  mov R1, 180
  mov [SP+1], R1
  mov R1, 179
  mov [SP+2], R1
  mov R1, 209
  mov [SP+3], R1
  mov R1, 165
  mov [SP+4], R1
  mov R1, 180
  mov [SP+5], R1
  call __function_define_region
  mov R1, 108
  mov [SP], R1
  call __function_select_region
  mov R1, 180
  mov [SP], R1
  mov R1, 180
  mov [SP+1], R1
  mov R1, 194
  mov [SP+2], R1
  mov R1, 209
  mov [SP+3], R1
  mov R1, 180
  mov [SP+4], R1
  mov R1, 180
  mov [SP+5], R1
  call __function_define_region
  mov R1, 109
  mov [SP], R1
  call __function_select_region
  mov R1, 195
  mov [SP], R1
  mov R1, 180
  mov [SP+1], R1
  mov R1, 209
  mov [SP+2], R1
  mov R1, 209
  mov [SP+3], R1
  mov R1, 195
  mov [SP+4], R1
  mov R1, 180
  mov [SP+5], R1
  call __function_define_region
  mov R1, 110
  mov [SP], R1
  call __function_select_region
  mov R1, 210
  mov [SP], R1
  mov R1, 180
  mov [SP+1], R1
  mov R1, 224
  mov [SP+2], R1
  mov R1, 209
  mov [SP+3], R1
  mov R1, 210
  mov [SP+4], R1
  mov R1, 180
  mov [SP+5], R1
  call __function_define_region
  mov R1, 111
  mov [SP], R1
  call __function_select_region
  mov R1, 225
  mov [SP], R1
  mov R1, 180
  mov [SP+1], R1
  mov R1, 239
  mov [SP+2], R1
  mov R1, 209
  mov [SP+3], R1
  mov R1, 225
  mov [SP+4], R1
  mov R1, 180
  mov [SP+5], R1
  call __function_define_region
  mov R1, 112
  mov [SP], R1
  call __function_select_region
  mov R1, 0
  mov [SP], R1
  mov R1, 210
  mov [SP+1], R1
  mov R1, 14
  mov [SP+2], R1
  mov R1, 239
  mov [SP+3], R1
  mov R1, 0
  mov [SP+4], R1
  mov R1, 210
  mov [SP+5], R1
  call __function_define_region
  mov R1, 113
  mov [SP], R1
  call __function_select_region
  mov R1, 15
  mov [SP], R1
  mov R1, 210
  mov [SP+1], R1
  mov R1, 29
  mov [SP+2], R1
  mov R1, 239
  mov [SP+3], R1
  mov R1, 15
  mov [SP+4], R1
  mov R1, 210
  mov [SP+5], R1
  call __function_define_region
  mov R1, 114
  mov [SP], R1
  call __function_select_region
  mov R1, 30
  mov [SP], R1
  mov R1, 210
  mov [SP+1], R1
  mov R1, 44
  mov [SP+2], R1
  mov R1, 239
  mov [SP+3], R1
  mov R1, 30
  mov [SP+4], R1
  mov R1, 210
  mov [SP+5], R1
  call __function_define_region
  mov R1, 115
  mov [SP], R1
  call __function_select_region
  mov R1, 45
  mov [SP], R1
  mov R1, 210
  mov [SP+1], R1
  mov R1, 59
  mov [SP+2], R1
  mov R1, 239
  mov [SP+3], R1
  mov R1, 45
  mov [SP+4], R1
  mov R1, 210
  mov [SP+5], R1
  call __function_define_region
  mov R1, 116
  mov [SP], R1
  call __function_select_region
  mov R1, 60
  mov [SP], R1
  mov R1, 210
  mov [SP+1], R1
  mov R1, 74
  mov [SP+2], R1
  mov R1, 239
  mov [SP+3], R1
  mov R1, 60
  mov [SP+4], R1
  mov R1, 210
  mov [SP+5], R1
  call __function_define_region
  mov R1, 117
  mov [SP], R1
  call __function_select_region
  mov R1, 75
  mov [SP], R1
  mov R1, 210
  mov [SP+1], R1
  mov R1, 89
  mov [SP+2], R1
  mov R1, 239
  mov [SP+3], R1
  mov R1, 75
  mov [SP+4], R1
  mov R1, 210
  mov [SP+5], R1
  call __function_define_region
  mov R1, 118
  mov [SP], R1
  call __function_select_region
  mov R1, 90
  mov [SP], R1
  mov R1, 210
  mov [SP+1], R1
  mov R1, 104
  mov [SP+2], R1
  mov R1, 239
  mov [SP+3], R1
  mov R1, 90
  mov [SP+4], R1
  mov R1, 210
  mov [SP+5], R1
  call __function_define_region
  mov R1, 119
  mov [SP], R1
  call __function_select_region
  mov R1, 105
  mov [SP], R1
  mov R1, 210
  mov [SP+1], R1
  mov R1, 119
  mov [SP+2], R1
  mov R1, 239
  mov [SP+3], R1
  mov R1, 105
  mov [SP+4], R1
  mov R1, 210
  mov [SP+5], R1
  call __function_define_region
  mov R1, 120
  mov [SP], R1
  call __function_select_region
  mov R1, 120
  mov [SP], R1
  mov R1, 210
  mov [SP+1], R1
  mov R1, 134
  mov [SP+2], R1
  mov R1, 239
  mov [SP+3], R1
  mov R1, 120
  mov [SP+4], R1
  mov R1, 210
  mov [SP+5], R1
  call __function_define_region
  mov R1, 121
  mov [SP], R1
  call __function_select_region
  mov R1, 135
  mov [SP], R1
  mov R1, 210
  mov [SP+1], R1
  mov R1, 149
  mov [SP+2], R1
  mov R1, 239
  mov [SP+3], R1
  mov R1, 135
  mov [SP+4], R1
  mov R1, 210
  mov [SP+5], R1
  call __function_define_region
  mov R1, 122
  mov [SP], R1
  call __function_select_region
  mov R1, 150
  mov [SP], R1
  mov R1, 210
  mov [SP+1], R1
  mov R1, 164
  mov [SP+2], R1
  mov R1, 239
  mov [SP+3], R1
  mov R1, 150
  mov [SP+4], R1
  mov R1, 210
  mov [SP+5], R1
  call __function_define_region
  mov R1, 123
  mov [SP], R1
  call __function_select_region
  mov R1, 165
  mov [SP], R1
  mov R1, 210
  mov [SP+1], R1
  mov R1, 179
  mov [SP+2], R1
  mov R1, 239
  mov [SP+3], R1
  mov R1, 165
  mov [SP+4], R1
  mov R1, 210
  mov [SP+5], R1
  call __function_define_region
  mov R1, 124
  mov [SP], R1
  call __function_select_region
  mov R1, 180
  mov [SP], R1
  mov R1, 210
  mov [SP+1], R1
  mov R1, 194
  mov [SP+2], R1
  mov R1, 239
  mov [SP+3], R1
  mov R1, 180
  mov [SP+4], R1
  mov R1, 210
  mov [SP+5], R1
  call __function_define_region
  mov R1, 125
  mov [SP], R1
  call __function_select_region
  mov R1, 195
  mov [SP], R1
  mov R1, 210
  mov [SP+1], R1
  mov R1, 209
  mov [SP+2], R1
  mov R1, 239
  mov [SP+3], R1
  mov R1, 195
  mov [SP+4], R1
  mov R1, 210
  mov [SP+5], R1
  call __function_define_region
  mov R1, 126
  mov [SP], R1
  call __function_select_region
  mov R1, 210
  mov [SP], R1
  mov R1, 210
  mov [SP+1], R1
  mov R1, 224
  mov [SP+2], R1
  mov R1, 239
  mov [SP+3], R1
  mov R1, 210
  mov [SP+4], R1
  mov R1, 210
  mov [SP+5], R1
  call __function_define_region
  mov R1, 127
  mov [SP], R1
  call __function_select_region
  mov R1, 225
  mov [SP], R1
  mov R1, 210
  mov [SP+1], R1
  mov R1, 239
  mov [SP+2], R1
  mov R1, 239
  mov [SP+3], R1
  mov R1, 225
  mov [SP+4], R1
  mov R1, 210
  mov [SP+5], R1
  call __function_define_region
  mov R0, 30
  mov [6], R0
  mov R0, 1
  mov [7], R0
  mov R0, 0
  mov [264], R0
  mov R0, 0
  mov [265], R0
  mov R0, 1
  mov [global_FontUbuntuMono_B_30], R0
  mov R0, 0
  mov [4], R0
  mov R1, global_FontUbuntuMono_B_30
  mov [SP], R1
  call __function_textfont_read_region_widths
__function_setupFontUbuntuMono_B_30_return:
  mov SP, BP
  pop BP
  ret

__function_setupFontRetro_Gaming_11:
  push BP
  mov BP, SP
  isub SP, 6
  mov R1, 2
  mov [SP], R1
  call __function_select_texture
  mov R1, 0
  mov [SP], R1
  call __function_select_region
  mov R1, 0
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, -1
  mov [SP+2], R1
  mov R1, 13
  mov [SP+3], R1
  mov R1, 0
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 1
  mov [SP], R1
  call __function_select_region
  mov R1, 12
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 20
  mov [SP+2], R1
  mov R1, 13
  mov [SP+3], R1
  mov R1, 12
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 2
  mov [SP], R1
  call __function_select_region
  mov R1, 24
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 30
  mov [SP+2], R1
  mov R1, 13
  mov [SP+3], R1
  mov R1, 24
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 3
  mov [SP], R1
  call __function_select_region
  mov R1, 36
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 45
  mov [SP+2], R1
  mov R1, 13
  mov [SP+3], R1
  mov R1, 36
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 4
  mov [SP], R1
  call __function_select_region
  mov R1, 48
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 54
  mov [SP+2], R1
  mov R1, 13
  mov [SP+3], R1
  mov R1, 48
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 5
  mov [SP], R1
  call __function_select_region
  mov R1, 60
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 67
  mov [SP+2], R1
  mov R1, 13
  mov [SP+3], R1
  mov R1, 60
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 6
  mov [SP], R1
  call __function_select_region
  mov R1, 72
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 78
  mov [SP+2], R1
  mov R1, 13
  mov [SP+3], R1
  mov R1, 72
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 7
  mov [SP], R1
  call __function_select_region
  mov R1, 84
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 90
  mov [SP+2], R1
  mov R1, 13
  mov [SP+3], R1
  mov R1, 84
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 8
  mov [SP], R1
  call __function_select_region
  mov R1, 96
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 102
  mov [SP+2], R1
  mov R1, 13
  mov [SP+3], R1
  mov R1, 96
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 9
  mov [SP], R1
  call __function_select_region
  mov R1, 108
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 114
  mov [SP+2], R1
  mov R1, 13
  mov [SP+3], R1
  mov R1, 108
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 10
  mov [SP], R1
  call __function_select_region
  mov R1, 120
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 126
  mov [SP+2], R1
  mov R1, 13
  mov [SP+3], R1
  mov R1, 120
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 11
  mov [SP], R1
  call __function_select_region
  mov R1, 132
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 138
  mov [SP+2], R1
  mov R1, 13
  mov [SP+3], R1
  mov R1, 132
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 12
  mov [SP], R1
  call __function_select_region
  mov R1, 144
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 150
  mov [SP+2], R1
  mov R1, 13
  mov [SP+3], R1
  mov R1, 144
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 13
  mov [SP], R1
  call __function_select_region
  mov R1, 156
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 162
  mov [SP+2], R1
  mov R1, 13
  mov [SP+3], R1
  mov R1, 156
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 14
  mov [SP], R1
  call __function_select_region
  mov R1, 168
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 174
  mov [SP+2], R1
  mov R1, 13
  mov [SP+3], R1
  mov R1, 168
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 15
  mov [SP], R1
  call __function_select_region
  mov R1, 180
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 186
  mov [SP+2], R1
  mov R1, 13
  mov [SP+3], R1
  mov R1, 180
  mov [SP+4], R1
  mov R1, 0
  mov [SP+5], R1
  call __function_define_region
  mov R1, 16
  mov [SP], R1
  call __function_select_region
  mov R1, 0
  mov [SP], R1
  mov R1, 14
  mov [SP+1], R1
  mov R1, 6
  mov [SP+2], R1
  mov R1, 27
  mov [SP+3], R1
  mov R1, 0
  mov [SP+4], R1
  mov R1, 14
  mov [SP+5], R1
  call __function_define_region
  mov R1, 17
  mov [SP], R1
  call __function_select_region
  mov R1, 12
  mov [SP], R1
  mov R1, 14
  mov [SP+1], R1
  mov R1, 18
  mov [SP+2], R1
  mov R1, 27
  mov [SP+3], R1
  mov R1, 12
  mov [SP+4], R1
  mov R1, 14
  mov [SP+5], R1
  call __function_define_region
  mov R1, 18
  mov [SP], R1
  call __function_select_region
  mov R1, 24
  mov [SP], R1
  mov R1, 14
  mov [SP+1], R1
  mov R1, 30
  mov [SP+2], R1
  mov R1, 27
  mov [SP+3], R1
  mov R1, 24
  mov [SP+4], R1
  mov R1, 14
  mov [SP+5], R1
  call __function_define_region
  mov R1, 19
  mov [SP], R1
  call __function_select_region
  mov R1, 36
  mov [SP], R1
  mov R1, 14
  mov [SP+1], R1
  mov R1, 42
  mov [SP+2], R1
  mov R1, 27
  mov [SP+3], R1
  mov R1, 36
  mov [SP+4], R1
  mov R1, 14
  mov [SP+5], R1
  call __function_define_region
  mov R1, 20
  mov [SP], R1
  call __function_select_region
  mov R1, 48
  mov [SP], R1
  mov R1, 14
  mov [SP+1], R1
  mov R1, 54
  mov [SP+2], R1
  mov R1, 27
  mov [SP+3], R1
  mov R1, 48
  mov [SP+4], R1
  mov R1, 14
  mov [SP+5], R1
  call __function_define_region
  mov R1, 21
  mov [SP], R1
  call __function_select_region
  mov R1, 60
  mov [SP], R1
  mov R1, 14
  mov [SP+1], R1
  mov R1, 66
  mov [SP+2], R1
  mov R1, 27
  mov [SP+3], R1
  mov R1, 60
  mov [SP+4], R1
  mov R1, 14
  mov [SP+5], R1
  call __function_define_region
  mov R1, 22
  mov [SP], R1
  call __function_select_region
  mov R1, 72
  mov [SP], R1
  mov R1, 14
  mov [SP+1], R1
  mov R1, 78
  mov [SP+2], R1
  mov R1, 27
  mov [SP+3], R1
  mov R1, 72
  mov [SP+4], R1
  mov R1, 14
  mov [SP+5], R1
  call __function_define_region
  mov R1, 23
  mov [SP], R1
  call __function_select_region
  mov R1, 84
  mov [SP], R1
  mov R1, 14
  mov [SP+1], R1
  mov R1, 90
  mov [SP+2], R1
  mov R1, 27
  mov [SP+3], R1
  mov R1, 84
  mov [SP+4], R1
  mov R1, 14
  mov [SP+5], R1
  call __function_define_region
  mov R1, 24
  mov [SP], R1
  call __function_select_region
  mov R1, 96
  mov [SP], R1
  mov R1, 14
  mov [SP+1], R1
  mov R1, 102
  mov [SP+2], R1
  mov R1, 27
  mov [SP+3], R1
  mov R1, 96
  mov [SP+4], R1
  mov R1, 14
  mov [SP+5], R1
  call __function_define_region
  mov R1, 25
  mov [SP], R1
  call __function_select_region
  mov R1, 108
  mov [SP], R1
  mov R1, 14
  mov [SP+1], R1
  mov R1, 114
  mov [SP+2], R1
  mov R1, 27
  mov [SP+3], R1
  mov R1, 108
  mov [SP+4], R1
  mov R1, 14
  mov [SP+5], R1
  call __function_define_region
  mov R1, 26
  mov [SP], R1
  call __function_select_region
  mov R1, 120
  mov [SP], R1
  mov R1, 14
  mov [SP+1], R1
  mov R1, 126
  mov [SP+2], R1
  mov R1, 27
  mov [SP+3], R1
  mov R1, 120
  mov [SP+4], R1
  mov R1, 14
  mov [SP+5], R1
  call __function_define_region
  mov R1, 27
  mov [SP], R1
  call __function_select_region
  mov R1, 132
  mov [SP], R1
  mov R1, 14
  mov [SP+1], R1
  mov R1, 138
  mov [SP+2], R1
  mov R1, 27
  mov [SP+3], R1
  mov R1, 132
  mov [SP+4], R1
  mov R1, 14
  mov [SP+5], R1
  call __function_define_region
  mov R1, 28
  mov [SP], R1
  call __function_select_region
  mov R1, 144
  mov [SP], R1
  mov R1, 14
  mov [SP+1], R1
  mov R1, 150
  mov [SP+2], R1
  mov R1, 27
  mov [SP+3], R1
  mov R1, 144
  mov [SP+4], R1
  mov R1, 14
  mov [SP+5], R1
  call __function_define_region
  mov R1, 29
  mov [SP], R1
  call __function_select_region
  mov R1, 156
  mov [SP], R1
  mov R1, 14
  mov [SP+1], R1
  mov R1, 162
  mov [SP+2], R1
  mov R1, 27
  mov [SP+3], R1
  mov R1, 156
  mov [SP+4], R1
  mov R1, 14
  mov [SP+5], R1
  call __function_define_region
  mov R1, 30
  mov [SP], R1
  call __function_select_region
  mov R1, 168
  mov [SP], R1
  mov R1, 14
  mov [SP+1], R1
  mov R1, 174
  mov [SP+2], R1
  mov R1, 27
  mov [SP+3], R1
  mov R1, 168
  mov [SP+4], R1
  mov R1, 14
  mov [SP+5], R1
  call __function_define_region
  mov R1, 31
  mov [SP], R1
  call __function_select_region
  mov R1, 180
  mov [SP], R1
  mov R1, 14
  mov [SP+1], R1
  mov R1, 186
  mov [SP+2], R1
  mov R1, 27
  mov [SP+3], R1
  mov R1, 180
  mov [SP+4], R1
  mov R1, 14
  mov [SP+5], R1
  call __function_define_region
  mov R1, 32
  mov [SP], R1
  call __function_select_region
  mov R1, 0
  mov [SP], R1
  mov R1, 28
  mov [SP+1], R1
  mov R1, 3
  mov [SP+2], R1
  mov R1, 41
  mov [SP+3], R1
  mov R1, 0
  mov [SP+4], R1
  mov R1, 28
  mov [SP+5], R1
  call __function_define_region
  mov R1, 33
  mov [SP], R1
  call __function_select_region
  mov R1, 12
  mov [SP], R1
  mov R1, 28
  mov [SP+1], R1
  mov R1, 15
  mov [SP+2], R1
  mov R1, 41
  mov [SP+3], R1
  mov R1, 12
  mov [SP+4], R1
  mov R1, 28
  mov [SP+5], R1
  call __function_define_region
  mov R1, 34
  mov [SP], R1
  call __function_select_region
  mov R1, 24
  mov [SP], R1
  mov R1, 28
  mov [SP+1], R1
  mov R1, 30
  mov [SP+2], R1
  mov R1, 41
  mov [SP+3], R1
  mov R1, 24
  mov [SP+4], R1
  mov R1, 28
  mov [SP+5], R1
  call __function_define_region
  mov R1, 35
  mov [SP], R1
  call __function_select_region
  mov R1, 36
  mov [SP], R1
  mov R1, 28
  mov [SP+1], R1
  mov R1, 47
  mov [SP+2], R1
  mov R1, 41
  mov [SP+3], R1
  mov R1, 36
  mov [SP+4], R1
  mov R1, 28
  mov [SP+5], R1
  call __function_define_region
  mov R1, 36
  mov [SP], R1
  call __function_select_region
  mov R1, 48
  mov [SP], R1
  mov R1, 28
  mov [SP+1], R1
  mov R1, 56
  mov [SP+2], R1
  mov R1, 41
  mov [SP+3], R1
  mov R1, 48
  mov [SP+4], R1
  mov R1, 28
  mov [SP+5], R1
  call __function_define_region
  mov R1, 37
  mov [SP], R1
  call __function_select_region
  mov R1, 60
  mov [SP], R1
  mov R1, 28
  mov [SP+1], R1
  mov R1, 68
  mov [SP+2], R1
  mov R1, 41
  mov [SP+3], R1
  mov R1, 60
  mov [SP+4], R1
  mov R1, 28
  mov [SP+5], R1
  call __function_define_region
  mov R1, 38
  mov [SP], R1
  call __function_select_region
  mov R1, 72
  mov [SP], R1
  mov R1, 28
  mov [SP+1], R1
  mov R1, 81
  mov [SP+2], R1
  mov R1, 41
  mov [SP+3], R1
  mov R1, 72
  mov [SP+4], R1
  mov R1, 28
  mov [SP+5], R1
  call __function_define_region
  mov R1, 39
  mov [SP], R1
  call __function_select_region
  mov R1, 84
  mov [SP], R1
  mov R1, 28
  mov [SP+1], R1
  mov R1, 87
  mov [SP+2], R1
  mov R1, 41
  mov [SP+3], R1
  mov R1, 84
  mov [SP+4], R1
  mov R1, 28
  mov [SP+5], R1
  call __function_define_region
  mov R1, 40
  mov [SP], R1
  call __function_select_region
  mov R1, 96
  mov [SP], R1
  mov R1, 28
  mov [SP+1], R1
  mov R1, 101
  mov [SP+2], R1
  mov R1, 41
  mov [SP+3], R1
  mov R1, 96
  mov [SP+4], R1
  mov R1, 28
  mov [SP+5], R1
  call __function_define_region
  mov R1, 41
  mov [SP], R1
  call __function_select_region
  mov R1, 108
  mov [SP], R1
  mov R1, 28
  mov [SP+1], R1
  mov R1, 113
  mov [SP+2], R1
  mov R1, 41
  mov [SP+3], R1
  mov R1, 108
  mov [SP+4], R1
  mov R1, 28
  mov [SP+5], R1
  call __function_define_region
  mov R1, 42
  mov [SP], R1
  call __function_select_region
  mov R1, 120
  mov [SP], R1
  mov R1, 28
  mov [SP+1], R1
  mov R1, 129
  mov [SP+2], R1
  mov R1, 41
  mov [SP+3], R1
  mov R1, 120
  mov [SP+4], R1
  mov R1, 28
  mov [SP+5], R1
  call __function_define_region
  mov R1, 43
  mov [SP], R1
  call __function_select_region
  mov R1, 132
  mov [SP], R1
  mov R1, 28
  mov [SP+1], R1
  mov R1, 139
  mov [SP+2], R1
  mov R1, 41
  mov [SP+3], R1
  mov R1, 132
  mov [SP+4], R1
  mov R1, 28
  mov [SP+5], R1
  call __function_define_region
  mov R1, 44
  mov [SP], R1
  call __function_select_region
  mov R1, 144
  mov [SP], R1
  mov R1, 28
  mov [SP+1], R1
  mov R1, 147
  mov [SP+2], R1
  mov R1, 41
  mov [SP+3], R1
  mov R1, 144
  mov [SP+4], R1
  mov R1, 28
  mov [SP+5], R1
  call __function_define_region
  mov R1, 45
  mov [SP], R1
  call __function_select_region
  mov R1, 156
  mov [SP], R1
  mov R1, 28
  mov [SP+1], R1
  mov R1, 161
  mov [SP+2], R1
  mov R1, 41
  mov [SP+3], R1
  mov R1, 156
  mov [SP+4], R1
  mov R1, 28
  mov [SP+5], R1
  call __function_define_region
  mov R1, 46
  mov [SP], R1
  call __function_select_region
  mov R1, 168
  mov [SP], R1
  mov R1, 28
  mov [SP+1], R1
  mov R1, 171
  mov [SP+2], R1
  mov R1, 41
  mov [SP+3], R1
  mov R1, 168
  mov [SP+4], R1
  mov R1, 28
  mov [SP+5], R1
  call __function_define_region
  mov R1, 47
  mov [SP], R1
  call __function_select_region
  mov R1, 180
  mov [SP], R1
  mov R1, 28
  mov [SP+1], R1
  mov R1, 188
  mov [SP+2], R1
  mov R1, 41
  mov [SP+3], R1
  mov R1, 180
  mov [SP+4], R1
  mov R1, 28
  mov [SP+5], R1
  call __function_define_region
  mov R1, 48
  mov [SP], R1
  call __function_select_region
  mov R1, 0
  mov [SP], R1
  mov R1, 42
  mov [SP+1], R1
  mov R1, 8
  mov [SP+2], R1
  mov R1, 55
  mov [SP+3], R1
  mov R1, 0
  mov [SP+4], R1
  mov R1, 42
  mov [SP+5], R1
  call __function_define_region
  mov R1, 49
  mov [SP], R1
  call __function_select_region
  mov R1, 12
  mov [SP], R1
  mov R1, 42
  mov [SP+1], R1
  mov R1, 17
  mov [SP+2], R1
  mov R1, 55
  mov [SP+3], R1
  mov R1, 12
  mov [SP+4], R1
  mov R1, 42
  mov [SP+5], R1
  call __function_define_region
  mov R1, 50
  mov [SP], R1
  call __function_select_region
  mov R1, 24
  mov [SP], R1
  mov R1, 42
  mov [SP+1], R1
  mov R1, 32
  mov [SP+2], R1
  mov R1, 55
  mov [SP+3], R1
  mov R1, 24
  mov [SP+4], R1
  mov R1, 42
  mov [SP+5], R1
  call __function_define_region
  mov R1, 51
  mov [SP], R1
  call __function_select_region
  mov R1, 36
  mov [SP], R1
  mov R1, 42
  mov [SP+1], R1
  mov R1, 44
  mov [SP+2], R1
  mov R1, 55
  mov [SP+3], R1
  mov R1, 36
  mov [SP+4], R1
  mov R1, 42
  mov [SP+5], R1
  call __function_define_region
  mov R1, 52
  mov [SP], R1
  call __function_select_region
  mov R1, 48
  mov [SP], R1
  mov R1, 42
  mov [SP+1], R1
  mov R1, 56
  mov [SP+2], R1
  mov R1, 55
  mov [SP+3], R1
  mov R1, 48
  mov [SP+4], R1
  mov R1, 42
  mov [SP+5], R1
  call __function_define_region
  mov R1, 53
  mov [SP], R1
  call __function_select_region
  mov R1, 60
  mov [SP], R1
  mov R1, 42
  mov [SP+1], R1
  mov R1, 68
  mov [SP+2], R1
  mov R1, 55
  mov [SP+3], R1
  mov R1, 60
  mov [SP+4], R1
  mov R1, 42
  mov [SP+5], R1
  call __function_define_region
  mov R1, 54
  mov [SP], R1
  call __function_select_region
  mov R1, 72
  mov [SP], R1
  mov R1, 42
  mov [SP+1], R1
  mov R1, 80
  mov [SP+2], R1
  mov R1, 55
  mov [SP+3], R1
  mov R1, 72
  mov [SP+4], R1
  mov R1, 42
  mov [SP+5], R1
  call __function_define_region
  mov R1, 55
  mov [SP], R1
  call __function_select_region
  mov R1, 84
  mov [SP], R1
  mov R1, 42
  mov [SP+1], R1
  mov R1, 92
  mov [SP+2], R1
  mov R1, 55
  mov [SP+3], R1
  mov R1, 84
  mov [SP+4], R1
  mov R1, 42
  mov [SP+5], R1
  call __function_define_region
  mov R1, 56
  mov [SP], R1
  call __function_select_region
  mov R1, 96
  mov [SP], R1
  mov R1, 42
  mov [SP+1], R1
  mov R1, 104
  mov [SP+2], R1
  mov R1, 55
  mov [SP+3], R1
  mov R1, 96
  mov [SP+4], R1
  mov R1, 42
  mov [SP+5], R1
  call __function_define_region
  mov R1, 57
  mov [SP], R1
  call __function_select_region
  mov R1, 108
  mov [SP], R1
  mov R1, 42
  mov [SP+1], R1
  mov R1, 116
  mov [SP+2], R1
  mov R1, 55
  mov [SP+3], R1
  mov R1, 108
  mov [SP+4], R1
  mov R1, 42
  mov [SP+5], R1
  call __function_define_region
  mov R1, 58
  mov [SP], R1
  call __function_select_region
  mov R1, 120
  mov [SP], R1
  mov R1, 42
  mov [SP+1], R1
  mov R1, 123
  mov [SP+2], R1
  mov R1, 55
  mov [SP+3], R1
  mov R1, 120
  mov [SP+4], R1
  mov R1, 42
  mov [SP+5], R1
  call __function_define_region
  mov R1, 59
  mov [SP], R1
  call __function_select_region
  mov R1, 132
  mov [SP], R1
  mov R1, 42
  mov [SP+1], R1
  mov R1, 135
  mov [SP+2], R1
  mov R1, 55
  mov [SP+3], R1
  mov R1, 132
  mov [SP+4], R1
  mov R1, 42
  mov [SP+5], R1
  call __function_define_region
  mov R1, 60
  mov [SP], R1
  call __function_select_region
  mov R1, 144
  mov [SP], R1
  mov R1, 42
  mov [SP+1], R1
  mov R1, 150
  mov [SP+2], R1
  mov R1, 55
  mov [SP+3], R1
  mov R1, 144
  mov [SP+4], R1
  mov R1, 42
  mov [SP+5], R1
  call __function_define_region
  mov R1, 61
  mov [SP], R1
  call __function_select_region
  mov R1, 156
  mov [SP], R1
  mov R1, 42
  mov [SP+1], R1
  mov R1, 162
  mov [SP+2], R1
  mov R1, 55
  mov [SP+3], R1
  mov R1, 156
  mov [SP+4], R1
  mov R1, 42
  mov [SP+5], R1
  call __function_define_region
  mov R1, 62
  mov [SP], R1
  call __function_select_region
  mov R1, 168
  mov [SP], R1
  mov R1, 42
  mov [SP+1], R1
  mov R1, 174
  mov [SP+2], R1
  mov R1, 55
  mov [SP+3], R1
  mov R1, 168
  mov [SP+4], R1
  mov R1, 42
  mov [SP+5], R1
  call __function_define_region
  mov R1, 63
  mov [SP], R1
  call __function_select_region
  mov R1, 180
  mov [SP], R1
  mov R1, 42
  mov [SP+1], R1
  mov R1, 188
  mov [SP+2], R1
  mov R1, 55
  mov [SP+3], R1
  mov R1, 180
  mov [SP+4], R1
  mov R1, 42
  mov [SP+5], R1
  call __function_define_region
  mov R1, 64
  mov [SP], R1
  call __function_select_region
  mov R1, 0
  mov [SP], R1
  mov R1, 56
  mov [SP+1], R1
  mov R1, 8
  mov [SP+2], R1
  mov R1, 69
  mov [SP+3], R1
  mov R1, 0
  mov [SP+4], R1
  mov R1, 56
  mov [SP+5], R1
  call __function_define_region
  mov R1, 65
  mov [SP], R1
  call __function_select_region
  mov R1, 12
  mov [SP], R1
  mov R1, 56
  mov [SP+1], R1
  mov R1, 20
  mov [SP+2], R1
  mov R1, 69
  mov [SP+3], R1
  mov R1, 12
  mov [SP+4], R1
  mov R1, 56
  mov [SP+5], R1
  call __function_define_region
  mov R1, 66
  mov [SP], R1
  call __function_select_region
  mov R1, 24
  mov [SP], R1
  mov R1, 56
  mov [SP+1], R1
  mov R1, 32
  mov [SP+2], R1
  mov R1, 69
  mov [SP+3], R1
  mov R1, 24
  mov [SP+4], R1
  mov R1, 56
  mov [SP+5], R1
  call __function_define_region
  mov R1, 67
  mov [SP], R1
  call __function_select_region
  mov R1, 36
  mov [SP], R1
  mov R1, 56
  mov [SP+1], R1
  mov R1, 44
  mov [SP+2], R1
  mov R1, 69
  mov [SP+3], R1
  mov R1, 36
  mov [SP+4], R1
  mov R1, 56
  mov [SP+5], R1
  call __function_define_region
  mov R1, 68
  mov [SP], R1
  call __function_select_region
  mov R1, 48
  mov [SP], R1
  mov R1, 56
  mov [SP+1], R1
  mov R1, 56
  mov [SP+2], R1
  mov R1, 69
  mov [SP+3], R1
  mov R1, 48
  mov [SP+4], R1
  mov R1, 56
  mov [SP+5], R1
  call __function_define_region
  mov R1, 69
  mov [SP], R1
  call __function_select_region
  mov R1, 60
  mov [SP], R1
  mov R1, 56
  mov [SP+1], R1
  mov R1, 68
  mov [SP+2], R1
  mov R1, 69
  mov [SP+3], R1
  mov R1, 60
  mov [SP+4], R1
  mov R1, 56
  mov [SP+5], R1
  call __function_define_region
  mov R1, 70
  mov [SP], R1
  call __function_select_region
  mov R1, 72
  mov [SP], R1
  mov R1, 56
  mov [SP+1], R1
  mov R1, 80
  mov [SP+2], R1
  mov R1, 69
  mov [SP+3], R1
  mov R1, 72
  mov [SP+4], R1
  mov R1, 56
  mov [SP+5], R1
  call __function_define_region
  mov R1, 71
  mov [SP], R1
  call __function_select_region
  mov R1, 84
  mov [SP], R1
  mov R1, 56
  mov [SP+1], R1
  mov R1, 92
  mov [SP+2], R1
  mov R1, 69
  mov [SP+3], R1
  mov R1, 84
  mov [SP+4], R1
  mov R1, 56
  mov [SP+5], R1
  call __function_define_region
  mov R1, 72
  mov [SP], R1
  call __function_select_region
  mov R1, 96
  mov [SP], R1
  mov R1, 56
  mov [SP+1], R1
  mov R1, 104
  mov [SP+2], R1
  mov R1, 69
  mov [SP+3], R1
  mov R1, 96
  mov [SP+4], R1
  mov R1, 56
  mov [SP+5], R1
  call __function_define_region
  mov R1, 73
  mov [SP], R1
  call __function_select_region
  mov R1, 108
  mov [SP], R1
  mov R1, 56
  mov [SP+1], R1
  mov R1, 115
  mov [SP+2], R1
  mov R1, 69
  mov [SP+3], R1
  mov R1, 108
  mov [SP+4], R1
  mov R1, 56
  mov [SP+5], R1
  call __function_define_region
  mov R1, 74
  mov [SP], R1
  call __function_select_region
  mov R1, 120
  mov [SP], R1
  mov R1, 56
  mov [SP+1], R1
  mov R1, 128
  mov [SP+2], R1
  mov R1, 69
  mov [SP+3], R1
  mov R1, 120
  mov [SP+4], R1
  mov R1, 56
  mov [SP+5], R1
  call __function_define_region
  mov R1, 75
  mov [SP], R1
  call __function_select_region
  mov R1, 132
  mov [SP], R1
  mov R1, 56
  mov [SP+1], R1
  mov R1, 140
  mov [SP+2], R1
  mov R1, 69
  mov [SP+3], R1
  mov R1, 132
  mov [SP+4], R1
  mov R1, 56
  mov [SP+5], R1
  call __function_define_region
  mov R1, 76
  mov [SP], R1
  call __function_select_region
  mov R1, 144
  mov [SP], R1
  mov R1, 56
  mov [SP+1], R1
  mov R1, 151
  mov [SP+2], R1
  mov R1, 69
  mov [SP+3], R1
  mov R1, 144
  mov [SP+4], R1
  mov R1, 56
  mov [SP+5], R1
  call __function_define_region
  mov R1, 77
  mov [SP], R1
  call __function_select_region
  mov R1, 156
  mov [SP], R1
  mov R1, 56
  mov [SP+1], R1
  mov R1, 164
  mov [SP+2], R1
  mov R1, 69
  mov [SP+3], R1
  mov R1, 156
  mov [SP+4], R1
  mov R1, 56
  mov [SP+5], R1
  call __function_define_region
  mov R1, 78
  mov [SP], R1
  call __function_select_region
  mov R1, 168
  mov [SP], R1
  mov R1, 56
  mov [SP+1], R1
  mov R1, 176
  mov [SP+2], R1
  mov R1, 69
  mov [SP+3], R1
  mov R1, 168
  mov [SP+4], R1
  mov R1, 56
  mov [SP+5], R1
  call __function_define_region
  mov R1, 79
  mov [SP], R1
  call __function_select_region
  mov R1, 180
  mov [SP], R1
  mov R1, 56
  mov [SP+1], R1
  mov R1, 188
  mov [SP+2], R1
  mov R1, 69
  mov [SP+3], R1
  mov R1, 180
  mov [SP+4], R1
  mov R1, 56
  mov [SP+5], R1
  call __function_define_region
  mov R1, 80
  mov [SP], R1
  call __function_select_region
  mov R1, 0
  mov [SP], R1
  mov R1, 70
  mov [SP+1], R1
  mov R1, 8
  mov [SP+2], R1
  mov R1, 83
  mov [SP+3], R1
  mov R1, 0
  mov [SP+4], R1
  mov R1, 70
  mov [SP+5], R1
  call __function_define_region
  mov R1, 81
  mov [SP], R1
  call __function_select_region
  mov R1, 12
  mov [SP], R1
  mov R1, 70
  mov [SP+1], R1
  mov R1, 20
  mov [SP+2], R1
  mov R1, 83
  mov [SP+3], R1
  mov R1, 12
  mov [SP+4], R1
  mov R1, 70
  mov [SP+5], R1
  call __function_define_region
  mov R1, 82
  mov [SP], R1
  call __function_select_region
  mov R1, 24
  mov [SP], R1
  mov R1, 70
  mov [SP+1], R1
  mov R1, 32
  mov [SP+2], R1
  mov R1, 83
  mov [SP+3], R1
  mov R1, 24
  mov [SP+4], R1
  mov R1, 70
  mov [SP+5], R1
  call __function_define_region
  mov R1, 83
  mov [SP], R1
  call __function_select_region
  mov R1, 36
  mov [SP], R1
  mov R1, 70
  mov [SP+1], R1
  mov R1, 44
  mov [SP+2], R1
  mov R1, 83
  mov [SP+3], R1
  mov R1, 36
  mov [SP+4], R1
  mov R1, 70
  mov [SP+5], R1
  call __function_define_region
  mov R1, 84
  mov [SP], R1
  call __function_select_region
  mov R1, 48
  mov [SP], R1
  mov R1, 70
  mov [SP+1], R1
  mov R1, 56
  mov [SP+2], R1
  mov R1, 83
  mov [SP+3], R1
  mov R1, 48
  mov [SP+4], R1
  mov R1, 70
  mov [SP+5], R1
  call __function_define_region
  mov R1, 85
  mov [SP], R1
  call __function_select_region
  mov R1, 60
  mov [SP], R1
  mov R1, 70
  mov [SP+1], R1
  mov R1, 68
  mov [SP+2], R1
  mov R1, 83
  mov [SP+3], R1
  mov R1, 60
  mov [SP+4], R1
  mov R1, 70
  mov [SP+5], R1
  call __function_define_region
  mov R1, 86
  mov [SP], R1
  call __function_select_region
  mov R1, 72
  mov [SP], R1
  mov R1, 70
  mov [SP+1], R1
  mov R1, 80
  mov [SP+2], R1
  mov R1, 83
  mov [SP+3], R1
  mov R1, 72
  mov [SP+4], R1
  mov R1, 70
  mov [SP+5], R1
  call __function_define_region
  mov R1, 87
  mov [SP], R1
  call __function_select_region
  mov R1, 84
  mov [SP], R1
  mov R1, 70
  mov [SP+1], R1
  mov R1, 93
  mov [SP+2], R1
  mov R1, 83
  mov [SP+3], R1
  mov R1, 84
  mov [SP+4], R1
  mov R1, 70
  mov [SP+5], R1
  call __function_define_region
  mov R1, 88
  mov [SP], R1
  call __function_select_region
  mov R1, 96
  mov [SP], R1
  mov R1, 70
  mov [SP+1], R1
  mov R1, 104
  mov [SP+2], R1
  mov R1, 83
  mov [SP+3], R1
  mov R1, 96
  mov [SP+4], R1
  mov R1, 70
  mov [SP+5], R1
  call __function_define_region
  mov R1, 89
  mov [SP], R1
  call __function_select_region
  mov R1, 108
  mov [SP], R1
  mov R1, 70
  mov [SP+1], R1
  mov R1, 116
  mov [SP+2], R1
  mov R1, 83
  mov [SP+3], R1
  mov R1, 108
  mov [SP+4], R1
  mov R1, 70
  mov [SP+5], R1
  call __function_define_region
  mov R1, 90
  mov [SP], R1
  call __function_select_region
  mov R1, 120
  mov [SP], R1
  mov R1, 70
  mov [SP+1], R1
  mov R1, 128
  mov [SP+2], R1
  mov R1, 83
  mov [SP+3], R1
  mov R1, 120
  mov [SP+4], R1
  mov R1, 70
  mov [SP+5], R1
  call __function_define_region
  mov R1, 91
  mov [SP], R1
  call __function_select_region
  mov R1, 132
  mov [SP], R1
  mov R1, 70
  mov [SP+1], R1
  mov R1, 137
  mov [SP+2], R1
  mov R1, 83
  mov [SP+3], R1
  mov R1, 132
  mov [SP+4], R1
  mov R1, 70
  mov [SP+5], R1
  call __function_define_region
  mov R1, 92
  mov [SP], R1
  call __function_select_region
  mov R1, 144
  mov [SP], R1
  mov R1, 70
  mov [SP+1], R1
  mov R1, 152
  mov [SP+2], R1
  mov R1, 83
  mov [SP+3], R1
  mov R1, 144
  mov [SP+4], R1
  mov R1, 70
  mov [SP+5], R1
  call __function_define_region
  mov R1, 93
  mov [SP], R1
  call __function_select_region
  mov R1, 156
  mov [SP], R1
  mov R1, 70
  mov [SP+1], R1
  mov R1, 161
  mov [SP+2], R1
  mov R1, 83
  mov [SP+3], R1
  mov R1, 156
  mov [SP+4], R1
  mov R1, 70
  mov [SP+5], R1
  call __function_define_region
  mov R1, 94
  mov [SP], R1
  call __function_select_region
  mov R1, 168
  mov [SP], R1
  mov R1, 70
  mov [SP+1], R1
  mov R1, 176
  mov [SP+2], R1
  mov R1, 83
  mov [SP+3], R1
  mov R1, 168
  mov [SP+4], R1
  mov R1, 70
  mov [SP+5], R1
  call __function_define_region
  mov R1, 95
  mov [SP], R1
  call __function_select_region
  mov R1, 180
  mov [SP], R1
  mov R1, 70
  mov [SP+1], R1
  mov R1, 186
  mov [SP+2], R1
  mov R1, 83
  mov [SP+3], R1
  mov R1, 180
  mov [SP+4], R1
  mov R1, 70
  mov [SP+5], R1
  call __function_define_region
  mov R1, 96
  mov [SP], R1
  call __function_select_region
  mov R1, 0
  mov [SP], R1
  mov R1, 84
  mov [SP+1], R1
  mov R1, 5
  mov [SP+2], R1
  mov R1, 97
  mov [SP+3], R1
  mov R1, 0
  mov [SP+4], R1
  mov R1, 84
  mov [SP+5], R1
  call __function_define_region
  mov R1, 97
  mov [SP], R1
  call __function_select_region
  mov R1, 12
  mov [SP], R1
  mov R1, 84
  mov [SP+1], R1
  mov R1, 20
  mov [SP+2], R1
  mov R1, 97
  mov [SP+3], R1
  mov R1, 12
  mov [SP+4], R1
  mov R1, 84
  mov [SP+5], R1
  call __function_define_region
  mov R1, 98
  mov [SP], R1
  call __function_select_region
  mov R1, 24
  mov [SP], R1
  mov R1, 84
  mov [SP+1], R1
  mov R1, 32
  mov [SP+2], R1
  mov R1, 97
  mov [SP+3], R1
  mov R1, 24
  mov [SP+4], R1
  mov R1, 84
  mov [SP+5], R1
  call __function_define_region
  mov R1, 99
  mov [SP], R1
  call __function_select_region
  mov R1, 36
  mov [SP], R1
  mov R1, 84
  mov [SP+1], R1
  mov R1, 44
  mov [SP+2], R1
  mov R1, 97
  mov [SP+3], R1
  mov R1, 36
  mov [SP+4], R1
  mov R1, 84
  mov [SP+5], R1
  call __function_define_region
  mov R1, 100
  mov [SP], R1
  call __function_select_region
  mov R1, 48
  mov [SP], R1
  mov R1, 84
  mov [SP+1], R1
  mov R1, 56
  mov [SP+2], R1
  mov R1, 97
  mov [SP+3], R1
  mov R1, 48
  mov [SP+4], R1
  mov R1, 84
  mov [SP+5], R1
  call __function_define_region
  mov R1, 101
  mov [SP], R1
  call __function_select_region
  mov R1, 60
  mov [SP], R1
  mov R1, 84
  mov [SP+1], R1
  mov R1, 68
  mov [SP+2], R1
  mov R1, 97
  mov [SP+3], R1
  mov R1, 60
  mov [SP+4], R1
  mov R1, 84
  mov [SP+5], R1
  call __function_define_region
  mov R1, 102
  mov [SP], R1
  call __function_select_region
  mov R1, 72
  mov [SP], R1
  mov R1, 84
  mov [SP+1], R1
  mov R1, 78
  mov [SP+2], R1
  mov R1, 97
  mov [SP+3], R1
  mov R1, 72
  mov [SP+4], R1
  mov R1, 84
  mov [SP+5], R1
  call __function_define_region
  mov R1, 103
  mov [SP], R1
  call __function_select_region
  mov R1, 84
  mov [SP], R1
  mov R1, 84
  mov [SP+1], R1
  mov R1, 92
  mov [SP+2], R1
  mov R1, 97
  mov [SP+3], R1
  mov R1, 84
  mov [SP+4], R1
  mov R1, 84
  mov [SP+5], R1
  call __function_define_region
  mov R1, 104
  mov [SP], R1
  call __function_select_region
  mov R1, 96
  mov [SP], R1
  mov R1, 84
  mov [SP+1], R1
  mov R1, 104
  mov [SP+2], R1
  mov R1, 97
  mov [SP+3], R1
  mov R1, 96
  mov [SP+4], R1
  mov R1, 84
  mov [SP+5], R1
  call __function_define_region
  mov R1, 105
  mov [SP], R1
  call __function_select_region
  mov R1, 108
  mov [SP], R1
  mov R1, 84
  mov [SP+1], R1
  mov R1, 111
  mov [SP+2], R1
  mov R1, 97
  mov [SP+3], R1
  mov R1, 108
  mov [SP+4], R1
  mov R1, 84
  mov [SP+5], R1
  call __function_define_region
  mov R1, 106
  mov [SP], R1
  call __function_select_region
  mov R1, 120
  mov [SP], R1
  mov R1, 84
  mov [SP+1], R1
  mov R1, 126
  mov [SP+2], R1
  mov R1, 97
  mov [SP+3], R1
  mov R1, 120
  mov [SP+4], R1
  mov R1, 84
  mov [SP+5], R1
  call __function_define_region
  mov R1, 107
  mov [SP], R1
  call __function_select_region
  mov R1, 132
  mov [SP], R1
  mov R1, 84
  mov [SP+1], R1
  mov R1, 139
  mov [SP+2], R1
  mov R1, 97
  mov [SP+3], R1
  mov R1, 132
  mov [SP+4], R1
  mov R1, 84
  mov [SP+5], R1
  call __function_define_region
  mov R1, 108
  mov [SP], R1
  call __function_select_region
  mov R1, 144
  mov [SP], R1
  mov R1, 84
  mov [SP+1], R1
  mov R1, 148
  mov [SP+2], R1
  mov R1, 97
  mov [SP+3], R1
  mov R1, 144
  mov [SP+4], R1
  mov R1, 84
  mov [SP+5], R1
  call __function_define_region
  mov R1, 109
  mov [SP], R1
  call __function_select_region
  mov R1, 156
  mov [SP], R1
  mov R1, 84
  mov [SP+1], R1
  mov R1, 164
  mov [SP+2], R1
  mov R1, 97
  mov [SP+3], R1
  mov R1, 156
  mov [SP+4], R1
  mov R1, 84
  mov [SP+5], R1
  call __function_define_region
  mov R1, 110
  mov [SP], R1
  call __function_select_region
  mov R1, 168
  mov [SP], R1
  mov R1, 84
  mov [SP+1], R1
  mov R1, 176
  mov [SP+2], R1
  mov R1, 97
  mov [SP+3], R1
  mov R1, 168
  mov [SP+4], R1
  mov R1, 84
  mov [SP+5], R1
  call __function_define_region
  mov R1, 111
  mov [SP], R1
  call __function_select_region
  mov R1, 180
  mov [SP], R1
  mov R1, 84
  mov [SP+1], R1
  mov R1, 188
  mov [SP+2], R1
  mov R1, 97
  mov [SP+3], R1
  mov R1, 180
  mov [SP+4], R1
  mov R1, 84
  mov [SP+5], R1
  call __function_define_region
  mov R1, 112
  mov [SP], R1
  call __function_select_region
  mov R1, 0
  mov [SP], R1
  mov R1, 98
  mov [SP+1], R1
  mov R1, 8
  mov [SP+2], R1
  mov R1, 111
  mov [SP+3], R1
  mov R1, 0
  mov [SP+4], R1
  mov R1, 98
  mov [SP+5], R1
  call __function_define_region
  mov R1, 113
  mov [SP], R1
  call __function_select_region
  mov R1, 12
  mov [SP], R1
  mov R1, 98
  mov [SP+1], R1
  mov R1, 20
  mov [SP+2], R1
  mov R1, 111
  mov [SP+3], R1
  mov R1, 12
  mov [SP+4], R1
  mov R1, 98
  mov [SP+5], R1
  call __function_define_region
  mov R1, 114
  mov [SP], R1
  call __function_select_region
  mov R1, 24
  mov [SP], R1
  mov R1, 98
  mov [SP+1], R1
  mov R1, 31
  mov [SP+2], R1
  mov R1, 111
  mov [SP+3], R1
  mov R1, 24
  mov [SP+4], R1
  mov R1, 98
  mov [SP+5], R1
  call __function_define_region
  mov R1, 115
  mov [SP], R1
  call __function_select_region
  mov R1, 36
  mov [SP], R1
  mov R1, 98
  mov [SP+1], R1
  mov R1, 44
  mov [SP+2], R1
  mov R1, 111
  mov [SP+3], R1
  mov R1, 36
  mov [SP+4], R1
  mov R1, 98
  mov [SP+5], R1
  call __function_define_region
  mov R1, 116
  mov [SP], R1
  call __function_select_region
  mov R1, 48
  mov [SP], R1
  mov R1, 98
  mov [SP+1], R1
  mov R1, 54
  mov [SP+2], R1
  mov R1, 111
  mov [SP+3], R1
  mov R1, 48
  mov [SP+4], R1
  mov R1, 98
  mov [SP+5], R1
  call __function_define_region
  mov R1, 117
  mov [SP], R1
  call __function_select_region
  mov R1, 60
  mov [SP], R1
  mov R1, 98
  mov [SP+1], R1
  mov R1, 68
  mov [SP+2], R1
  mov R1, 111
  mov [SP+3], R1
  mov R1, 60
  mov [SP+4], R1
  mov R1, 98
  mov [SP+5], R1
  call __function_define_region
  mov R1, 118
  mov [SP], R1
  call __function_select_region
  mov R1, 72
  mov [SP], R1
  mov R1, 98
  mov [SP+1], R1
  mov R1, 80
  mov [SP+2], R1
  mov R1, 111
  mov [SP+3], R1
  mov R1, 72
  mov [SP+4], R1
  mov R1, 98
  mov [SP+5], R1
  call __function_define_region
  mov R1, 119
  mov [SP], R1
  call __function_select_region
  mov R1, 84
  mov [SP], R1
  mov R1, 98
  mov [SP+1], R1
  mov R1, 92
  mov [SP+2], R1
  mov R1, 111
  mov [SP+3], R1
  mov R1, 84
  mov [SP+4], R1
  mov R1, 98
  mov [SP+5], R1
  call __function_define_region
  mov R1, 120
  mov [SP], R1
  call __function_select_region
  mov R1, 96
  mov [SP], R1
  mov R1, 98
  mov [SP+1], R1
  mov R1, 104
  mov [SP+2], R1
  mov R1, 111
  mov [SP+3], R1
  mov R1, 96
  mov [SP+4], R1
  mov R1, 98
  mov [SP+5], R1
  call __function_define_region
  mov R1, 121
  mov [SP], R1
  call __function_select_region
  mov R1, 108
  mov [SP], R1
  mov R1, 98
  mov [SP+1], R1
  mov R1, 116
  mov [SP+2], R1
  mov R1, 111
  mov [SP+3], R1
  mov R1, 108
  mov [SP+4], R1
  mov R1, 98
  mov [SP+5], R1
  call __function_define_region
  mov R1, 122
  mov [SP], R1
  call __function_select_region
  mov R1, 120
  mov [SP], R1
  mov R1, 98
  mov [SP+1], R1
  mov R1, 128
  mov [SP+2], R1
  mov R1, 111
  mov [SP+3], R1
  mov R1, 120
  mov [SP+4], R1
  mov R1, 98
  mov [SP+5], R1
  call __function_define_region
  mov R1, 123
  mov [SP], R1
  call __function_select_region
  mov R1, 132
  mov [SP], R1
  mov R1, 98
  mov [SP+1], R1
  mov R1, 137
  mov [SP+2], R1
  mov R1, 111
  mov [SP+3], R1
  mov R1, 132
  mov [SP+4], R1
  mov R1, 98
  mov [SP+5], R1
  call __function_define_region
  mov R1, 124
  mov [SP], R1
  call __function_select_region
  mov R1, 144
  mov [SP], R1
  mov R1, 98
  mov [SP+1], R1
  mov R1, 147
  mov [SP+2], R1
  mov R1, 111
  mov [SP+3], R1
  mov R1, 144
  mov [SP+4], R1
  mov R1, 98
  mov [SP+5], R1
  call __function_define_region
  mov R1, 125
  mov [SP], R1
  call __function_select_region
  mov R1, 156
  mov [SP], R1
  mov R1, 98
  mov [SP+1], R1
  mov R1, 161
  mov [SP+2], R1
  mov R1, 111
  mov [SP+3], R1
  mov R1, 156
  mov [SP+4], R1
  mov R1, 98
  mov [SP+5], R1
  call __function_define_region
  mov R1, 126
  mov [SP], R1
  call __function_select_region
  mov R1, 168
  mov [SP], R1
  mov R1, 98
  mov [SP+1], R1
  mov R1, 175
  mov [SP+2], R1
  mov R1, 111
  mov [SP+3], R1
  mov R1, 168
  mov [SP+4], R1
  mov R1, 98
  mov [SP+5], R1
  call __function_define_region
  mov R1, 127
  mov [SP], R1
  call __function_select_region
  mov R1, 180
  mov [SP], R1
  mov R1, 98
  mov [SP+1], R1
  mov R1, 186
  mov [SP+2], R1
  mov R1, 111
  mov [SP+3], R1
  mov R1, 180
  mov [SP+4], R1
  mov R1, 98
  mov [SP+5], R1
  call __function_define_region
  mov R0, 14
  mov [269], R0
  mov R0, 1
  mov [270], R0
  mov R0, 0
  mov [527], R0
  mov R0, 0
  mov [528], R0
  mov R0, 2
  mov [global_FontRetro_Gaming_11], R0
  mov R0, 0
  mov [267], R0
  mov R1, global_FontRetro_Gaming_11
  mov [SP], R1
  call __function_textfont_read_region_widths
__function_setupFontRetro_Gaming_11_return:
  mov SP, BP
  pop BP
  ret

__function_effect_offset:
  push BP
  mov BP, SP
  isub SP, 2
  mov R1, [BP+2]
  fmul R1, 20.000000
  fadd R1, 100.000000
  cfi R1
  mov [SP], R1
  mov R1, 100
  mov [SP+1], R1
  call __function_draw_region_at
__function_effect_offset_return:
  mov SP, BP
  pop BP
  ret

__function_effect_simple_ease:
  push BP
  mov BP, SP
  isub SP, 4
  mov R2, [BP+2]
  mov [SP], R2
  mov R2, 2
  mov [SP+1], R2
  mov R2, 2
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 300.000000
  fadd R1, 100.000000
  cfi R1
  mov [BP-1], R1
  mov R1, [BP-1]
  mov [SP], R1
  mov R1, 100
  mov [SP+1], R1
  call __function_draw_region_at
__function_effect_simple_ease_return:
  mov SP, BP
  pop BP
  ret

__function_effect_different_ease:
  push BP
  mov BP, SP
  isub SP, 4
  mov R2, [BP+2]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 300.000000
  fadd R1, 100.000000
  cfi R1
  mov [BP-1], R1
  mov R1, [BP-1]
  mov [SP], R1
  mov R1, 100
  mov [SP+1], R1
  call __function_draw_region_at
__function_effect_different_ease_return:
  mov SP, BP
  pop BP
  ret

__function_effect_two_axis_ease:
  push BP
  mov BP, SP
  isub SP, 5
  mov R2, [BP+2]
  mov [SP], R2
  mov R2, 2
  mov [SP+1], R2
  mov R2, 2
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 100.000000
  fadd R1, 100.000000
  cfi R1
  mov [BP-1], R1
  mov R2, [BP+2]
  mov [SP], R2
  mov R2, 6
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 300.000000
  fadd R1, 100.000000
  cfi R1
  mov [BP-2], R1
  mov R1, [BP-2]
  mov [SP], R1
  mov R1, [BP-1]
  mov [SP+1], R1
  call __function_draw_region_at
__function_effect_two_axis_ease_return:
  mov SP, BP
  pop BP
  ret

__function_effect_time_offset:
  push BP
  mov BP, SP
  isub SP, 4
  mov R2, [BP+2]
  fsub R2, 1.000000
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 4
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 300.000000
  fadd R1, 100.000000
  cfi R1
  mov [BP-1], R1
  mov R1, [BP-1]
  mov [SP], R1
  mov R1, 100
  mov [SP+1], R1
  call __function_draw_region_at
__function_effect_time_offset_return:
  mov SP, BP
  pop BP
  ret

__function_effect_follow_by_offset:
  push BP
  mov BP, SP
  isub SP, 4
  mov R2, [BP+2]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 4
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 300.000000
  fadd R1, 100.000000
  cfi R1
  mov [BP-1], R1
  mov R1, [BP-1]
  mov [SP], R1
  mov R1, 60
  mov [SP+1], R1
  call __function_draw_region_at
  mov R2, [BP+2]
  fsub R2, 0.200000
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 4
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 300.000000
  fadd R1, 100.000000
  cfi R1
  mov [BP-1], R1
  mov R1, [BP-1]
  mov [SP], R1
  mov R1, 110
  mov [SP+1], R1
  call __function_draw_region_at
  mov R2, [BP+2]
  fsub R2, 0.400000
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 4
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 300.000000
  fadd R1, 100.000000
  cfi R1
  mov [BP-1], R1
  mov R1, [BP-1]
  mov [SP], R1
  mov R1, 160
  mov [SP+1], R1
  call __function_draw_region_at
  mov R2, [BP+2]
  fsub R2, 0.600000
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 4
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 300.000000
  fadd R1, 100.000000
  cfi R1
  mov [BP-1], R1
  mov R1, [BP-1]
  mov [SP], R1
  mov R1, 210
  mov [SP+1], R1
  call __function_draw_region_at
__function_effect_follow_by_offset_return:
  mov SP, BP
  pop BP
  ret

__function_effect_only_one_offset:
  push BP
  mov BP, SP
  isub SP, 4
  mov R2, [BP+2]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 50.000000
  fadd R1, 100.000000
  mov R3, [BP+2]
  fsub R3, 1.200000
  mov [SP], R3
  mov R3, 6
  mov [SP+1], R3
  mov R3, 4
  mov [SP+2], R3
  call __function_ease
  mov R2, R0
  fmul R2, 50.000000
  fsub R1, R2
  cfi R1
  mov [BP-1], R1
  mov R1, 100
  mov [SP], R1
  mov R1, [BP-1]
  mov [SP+1], R1
  call __function_draw_region_at
  mov R2, [BP+2]
  fsub R2, 1.200000
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 50.000000
  fadd R1, 100.000000
  mov R3, [BP+2]
  fsub R3, 2.400000
  mov [SP], R3
  mov R3, 6
  mov [SP+1], R3
  mov R3, 4
  mov [SP+2], R3
  call __function_ease
  mov R2, R0
  fmul R2, 50.000000
  fsub R1, R2
  cfi R1
  mov [BP-1], R1
  mov R1, 150
  mov [SP], R1
  mov R1, [BP-1]
  mov [SP+1], R1
  call __function_draw_region_at
  mov R2, [BP+2]
  fsub R2, 2.400000
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 50.000000
  fadd R1, 100.000000
  mov R3, [BP+2]
  fsub R3, 3.600000
  mov [SP], R3
  mov R3, 6
  mov [SP+1], R3
  mov R3, 4
  mov [SP+2], R3
  call __function_ease
  mov R2, R0
  fmul R2, 50.000000
  fsub R1, R2
  cfi R1
  mov [BP-1], R1
  mov R1, 200
  mov [SP], R1
  mov R1, [BP-1]
  mov [SP+1], R1
  call __function_draw_region_at
  mov R2, [BP+2]
  fsub R2, 3.600000
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 50.000000
  fadd R1, 100.000000
  mov R3, [BP+2]
  fsub R3, 4.800000
  mov [SP], R3
  mov R3, 6
  mov [SP+1], R3
  mov R3, 4
  mov [SP+2], R3
  call __function_ease
  mov R2, R0
  fmul R2, 50.000000
  fsub R1, R2
  cfi R1
  mov [BP-1], R1
  mov R1, 250
  mov [SP], R1
  mov R1, [BP-1]
  mov [SP+1], R1
  call __function_draw_region_at
__function_effect_only_one_offset_return:
  mov SP, BP
  pop BP
  ret

__function_effect_concatenate:
  push BP
  mov BP, SP
  isub SP, 4
  mov R2, [BP+2]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 100.000000
  fadd R1, 100.000000
  mov R3, [BP+2]
  fsub R3, 1.500000
  mov [SP], R3
  mov R3, 2
  mov [SP+1], R3
  mov R3, 2
  mov [SP+2], R3
  call __function_ease
  mov R2, R0
  fmul R2, 100.000000
  fadd R1, R2
  mov R3, [BP+2]
  fsub R3, 3.000000
  mov [SP], R3
  mov R3, 6
  mov [SP+1], R3
  mov R3, 6
  mov [SP+2], R3
  call __function_ease
  mov R2, R0
  fmul R2, 100.000000
  fadd R1, R2
  cfi R1
  mov [BP-1], R1
  mov R1, [BP-1]
  mov [SP], R1
  mov R1, 100
  mov [SP+1], R1
  call __function_draw_region_at
__function_effect_concatenate_return:
  mov SP, BP
  pop BP
  ret

__function_effect_scale:
  push BP
  mov BP, SP
  isub SP, 5
  mov R2, [BP+2]
  mov [SP], R2
  mov R2, 5
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  mov [BP-1], R1
  mov R2, [BP+2]
  mov [SP], R2
  mov R2, 5
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  mov [BP-2], R1
  mov R1, [BP-2]
  mov [SP], R1
  mov R1, [BP-1]
  mov [SP+1], R1
  call __function_set_drawing_scale
  mov R1, 200
  mov [SP], R1
  mov R1, 200
  mov [SP+1], R1
  call __function_draw_region_zoomed_at
__function_effect_scale_return:
  mov SP, BP
  pop BP
  ret

__function_effect_rotation:
  push BP
  mov BP, SP
  isub SP, 4
  mov R2, [BP+2]
  mov [SP], R2
  mov R2, 5
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  mov [BP-1], R1
  mov R1, [BP-1]
  mov [SP], R1
  call __function_set_drawing_angle
  mov R1, 200
  mov [SP], R1
  mov R1, 200
  mov [SP+1], R1
  call __function_draw_region_rotated_at
__function_effect_rotation_return:
  mov SP, BP
  pop BP
  ret

__function_effect_rotozoomed:
  push BP
  mov BP, SP
  isub SP, 5
  mov R2, [BP+2]
  mov [SP], R2
  mov R2, 5
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  mov [BP-1], R1
  mov R2, [BP+2]
  mov [SP], R2
  mov R2, 5
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  mov [BP-2], R1
  mov R1, [BP-2]
  mov [SP], R1
  mov R1, [BP-1]
  mov [SP+1], R1
  call __function_set_drawing_scale
  mov R2, [BP+2]
  mov [SP], R2
  mov R2, 6
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 6.283190
  mov [BP-1], R1
  mov R1, [BP-1]
  mov [SP], R1
  call __function_set_drawing_angle
  mov R1, 200
  mov [SP], R1
  mov R1, 200
  mov [SP+1], R1
  call __function_draw_region_rotozoomed_at
__function_effect_rotozoomed_return:
  mov SP, BP
  pop BP
  ret

__function_effect_none:
  push BP
  mov BP, SP
  isub SP, 4
  mov R2, [BP+2]
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 3
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 300.000000
  fadd R1, 100.000000
  cfi R1
  mov [BP-1], R1
  mov R1, [BP-1]
  mov [SP], R1
  mov R1, 100
  mov [SP+1], R1
  call __function_draw_region_at
__function_effect_none_return:
  mov SP, BP
  pop BP
  ret

__function_effect_dual_none:
  push BP
  mov BP, SP
  isub SP, 4
  mov R2, [BP+2]
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 0
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 300.000000
  fadd R1, 100.000000
  cfi R1
  mov [BP-1], R1
  mov R1, [BP-1]
  mov [SP], R1
  mov R1, 100
  mov [SP+1], R1
  call __function_draw_region_at
__function_effect_dual_none_return:
  mov SP, BP
  pop BP
  ret

__function_effect_speed:
  push BP
  mov BP, SP
  isub SP, 4
  mov R2, [BP+2]
  fdiv R2, 2.000000
  mov [SP], R2
  mov R2, 2
  mov [SP+1], R2
  mov R2, 2
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 300.000000
  fadd R1, 100.000000
  cfi R1
  mov [BP-1], R1
  mov R1, [BP-1]
  mov [SP], R1
  mov R1, 100
  mov [SP+1], R1
  call __function_draw_region_at
__function_effect_speed_return:
  mov SP, BP
  pop BP
  ret

__function_effect_multiple_speed:
  push BP
  mov BP, SP
  isub SP, 4
  mov R2, [BP+2]
  fdiv R2, 2.000000
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 4
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 300.000000
  fadd R1, 100.000000
  cfi R1
  mov [BP-1], R1
  mov R1, [BP-1]
  mov [SP], R1
  mov R1, 60
  mov [SP+1], R1
  call __function_draw_region_at
  mov R2, [BP+2]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 4
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 300.000000
  fadd R1, 100.000000
  cfi R1
  mov [BP-1], R1
  mov R1, [BP-1]
  mov [SP], R1
  mov R1, 110
  mov [SP+1], R1
  call __function_draw_region_at
  mov R2, [BP+2]
  fmul R2, 2.000000
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 4
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 300.000000
  fadd R1, 100.000000
  cfi R1
  mov [BP-1], R1
  mov R1, [BP-1]
  mov [SP], R1
  mov R1, 160
  mov [SP+1], R1
  call __function_draw_region_at
  mov R2, [BP+2]
  fmul R2, 3.000000
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 4
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 300.000000
  fadd R1, 100.000000
  cfi R1
  mov [BP-1], R1
  mov R1, [BP-1]
  mov [SP], R1
  mov R1, 210
  mov [SP+1], R1
  call __function_draw_region_at
__function_effect_multiple_speed_return:
  mov SP, BP
  pop BP
  ret

__function_effect_repeat:
  push BP
  mov BP, SP
  isub SP, 4
  mov R4, [BP+2]
  fmul R4, 2.000000
  fadd R4, 3.141593
  mov [SP], R4
  call __function_cos
  mov R3, R0
  mov [BP-1], R3
  mov R3, [BP-1]
  mov [SP], R3
  call __function_asin
  mov R2, R0
  fadd R2, 1.570796
  fdiv R2, 3.141593
  mov [BP-1], R2
  mov R2, [BP-1]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 4
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 300.000000
  fadd R1, 100.000000
  cfi R1
  mov [BP-1], R1
  mov R1, [BP-1]
  mov [SP], R1
  mov R1, 100
  mov [SP+1], R1
  call __function_draw_region_at
__function_effect_repeat_return:
  mov SP, BP
  pop BP
  ret

__function_intro:
  push BP
  mov BP, SP
  isub SP, 5
  mov R1, 0
  mov [SP], R1
  call __function_select_texture
  mov R1, 0
  mov [SP], R1
  call __function_select_region
  mov R3, [global_intro_timer]
  fsub R3, 1.000000
  mov [SP], R3
  mov R3, 2
  mov [SP+1], R3
  mov R3, 2
  mov [SP+2], R3
  call __function_ease
  mov R2, R0
  fmul R2, 255.000000
  mov R4, [global_intro_timer]
  fsub R4, 5.000000
  mov [SP], R4
  mov R4, 2
  mov [SP+1], R4
  mov R4, 2
  mov [SP+2], R4
  call __function_ease
  mov R3, R0
  fmul R3, 255.000000
  fsub R2, R3
  cfi R2
  mov [BP-1], R2
  mov R2, 255
  mov [SP], R2
  mov R2, 255
  mov [SP+1], R2
  mov R2, 255
  mov [SP+2], R2
  mov R2, [BP-1]
  mov [SP+3], R2
  call __function_make_color_rgba
  mov R1, R0
  mov [BP-1], R1
  mov R1, [BP-1]
  mov [SP], R1
  call __function_set_multiply_color
  mov R2, [global_intro_color_from_black]
  fmul R2, 17.000000
  cfi R2
  mov [SP], R2
  mov R2, [global_intro_color_from_black]
  fmul R2, 17.000000
  cfi R2
  mov [SP+1], R2
  mov R2, [global_intro_color_from_black]
  fmul R2, 27.000000
  cfi R2
  mov [SP+2], R2
  call __function_make_color_rgb
  mov R1, R0
  mov [global_clear_color], R1
  mov R0, R1
__if_5953_start:
  mov R0, [global_intro_timer]
  fgt R0, 2.000000
  jf R0, __LogicalAnd_ShortCircuit_5958
  mov R1, [global_intro_color_from_black]
  flt R1, 1.000000
  and R0, R1
__LogicalAnd_ShortCircuit_5958:
  jf R0, __if_5953_end
  mov R0, [global_intro_color_from_black]
  fadd R0, 0.010000
  mov [global_intro_color_from_black], R0
__if_5953_end:
  mov R1, 320
  mov [SP], R1
  mov R1, 180
  mov [SP+1], R1
  call __function_draw_region_at
  mov R0, [global_intro_timer]
  fadd R0, 0.030000
  mov [global_intro_timer], R0
__if_5970_start:
  mov R0, [global_intro_timer]
  fgt R0, 7.000000
  jf R0, __if_5970_end
  mov R0, 0
  mov [global_effect], R0
  mov R1, -1
  mov [SP], R1
  call __function_set_multiply_color
  mov R0, 1
  mov [global_is_intro_over], R0
__if_5970_end:
__function_intro_return:
  mov SP, BP
  pop BP
  ret

__function_info:
  push BP
  mov BP, SP
  isub SP, 7
  mov R1, 0
  mov [SP], R1
  call __function_select_texture
  mov R1, 3
  mov [SP], R1
  call __function_select_region
  mov R0, 0.500000
  mov [BP-1], R0
__if_6005_start:
  mov R0, [global_info_offset]
  flt R0, 0.500000
  jf R0, __if_6005_end
  mov R2, [global_button_timer]
  fsub R2, 0.500000
  mov [SP], R2
  call __function_sin
  mov R1, R0
  fmul R1, 5.000000
  mov R3, [global_info_offset]
  mov [SP], R3
  mov R3, 4
  mov [SP+1], R3
  mov R3, 6
  mov [SP+2], R3
  call __function_ease
  mov R2, R0
  mov R3, [global_info_size]
  cif R3
  fmul R2, R3
  fsub R1, R2
  fadd R1, 300.000000
  cfi R1
  mov [BP-2], R1
  mov R1, 610
  mov [SP], R1
  mov R1, [BP-2]
  mov [SP+1], R1
  call __function_draw_region_at
__if_6005_end:
  mov R1, 2
  mov [SP], R1
  call __function_select_region
__if_6028_start:
  mov R0, [global_info_offset]
  flt R0, 0.500000
  jf R0, __if_6028_end
  mov R2, [global_button_timer]
  mov [SP], R2
  call __function_sin
  mov R1, R0
  fmul R1, 5.000000
  fadd R1, 335.000000
  mov R3, [global_info_offset]
  mov [SP], R3
  mov R3, 4
  mov [SP+1], R3
  mov R3, 6
  mov [SP+2], R3
  call __function_ease
  mov R2, R0
  mov R3, [global_info_size]
  cif R3
  fmul R2, R3
  fsub R1, R2
  cfi R1
  mov [BP-2], R1
  mov R1, 610
  mov [SP], R1
  mov R1, [BP-2]
  mov [SP+1], R1
  call __function_draw_region_at
__if_6028_end:
  mov R0, [global_button_timer]
  fadd R0, 0.040000
  mov [global_button_timer], R0
  mov R1, global_FontRetro_Gaming_11
  mov [SP], R1
  mov R1, 630
  mov [SP+1], R1
  mov R1, 10
  mov [SP+2], R1
  mov R1, __literal_string_6055
  mov [SP+3], R1
  call __function_textfont_print_from_right
__if_6056_start:
  mov R0, [global_info_open]
  jf R0, __LogicalAnd_ShortCircuit_6058
  mov R1, [global_info_offset]
  flt R1, 1.000000
  and R0, R1
__LogicalAnd_ShortCircuit_6058:
  jf R0, __if_6056_end
  mov R0, [global_info_offset]
  fadd R0, 0.020000
  mov [global_info_offset], R0
__if_6056_end:
__if_6065_start:
  mov R0, [global_info_open]
  bnot R0
  jf R0, __LogicalAnd_ShortCircuit_6068
  mov R1, [global_info_offset]
  fgt R1, 0.000000
  and R0, R1
__LogicalAnd_ShortCircuit_6068:
  jf R0, __if_6065_end
  mov R0, [global_info_offset]
  fsub R0, 0.020000
  mov [global_info_offset], R0
__if_6065_end:
__if_6075_start:
  mov R0, [global_title_timer]
  mov R1, [global_effect]
  cif R1
  flt R0, R1
  jf R0, __if_6075_end
  mov R0, [global_title_timer]
  fadd R0, 0.020000
  mov [global_title_timer], R0
__if_6075_end:
__if_6082_start:
  mov R0, [global_title_timer]
  mov R1, [global_effect]
  cif R1
  fgt R0, R1
  jf R0, __if_6082_end
  mov R0, [global_title_timer]
  fsub R0, 0.020000
  mov [global_title_timer], R0
__if_6082_end:
  mov R2, [global_title_timer]
  fadd R2, 1.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 50.000000
  fsub R1, 40.000000
  cfi R1
  mov [BP-2], R1
  mov R2, [global_title_timer]
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, -400.000000
  fadd R1, 10.000000
  cfi R1
  mov [BP-3], R1
  mov R1, global_FontUbuntuMono_B_30
  mov [SP], R1
  mov R1, [BP-3]
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6111
  mov [SP+3], R1
  call __function_textfont_print_from_left
  mov R2, [global_title_timer]
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 50.000000
  fsub R1, 40.000000
  cfi R1
  mov [BP-2], R1
  mov R2, [global_title_timer]
  fsub R2, 1.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, -400.000000
  fadd R1, 10.000000
  cfi R1
  mov [BP-3], R1
  mov R1, global_FontUbuntuMono_B_30
  mov [SP], R1
  mov R1, [BP-3]
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6134
  mov [SP+3], R1
  call __function_textfont_print_from_left
  mov R2, [global_title_timer]
  fsub R2, 1.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 50.000000
  fsub R1, 40.000000
  cfi R1
  mov [BP-2], R1
  mov R2, [global_title_timer]
  fsub R2, 2.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, -450.000000
  fadd R1, 10.000000
  cfi R1
  mov [BP-3], R1
  mov R1, global_FontUbuntuMono_B_30
  mov [SP], R1
  mov R1, [BP-3]
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6159
  mov [SP+3], R1
  call __function_textfont_print_from_left
  mov R2, [global_title_timer]
  fsub R2, 2.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 50.000000
  fsub R1, 40.000000
  cfi R1
  mov [BP-2], R1
  mov R2, [global_title_timer]
  fsub R2, 3.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, -450.000000
  fadd R1, 10.000000
  cfi R1
  mov [BP-3], R1
  mov R1, global_FontUbuntuMono_B_30
  mov [SP], R1
  mov R1, [BP-3]
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6184
  mov [SP+3], R1
  call __function_textfont_print_from_left
  mov R2, [global_title_timer]
  fsub R2, 3.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 50.000000
  fsub R1, 40.000000
  cfi R1
  mov [BP-2], R1
  mov R2, [global_title_timer]
  fsub R2, 4.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, -400.000000
  fadd R1, 10.000000
  cfi R1
  mov [BP-3], R1
  mov R1, global_FontUbuntuMono_B_30
  mov [SP], R1
  mov R1, [BP-3]
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6209
  mov [SP+3], R1
  call __function_textfont_print_from_left
  mov R2, [global_title_timer]
  fsub R2, 4.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 50.000000
  fsub R1, 40.000000
  cfi R1
  mov [BP-2], R1
  mov R2, [global_title_timer]
  fsub R2, 5.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, -400.000000
  fadd R1, 10.000000
  cfi R1
  mov [BP-3], R1
  mov R1, global_FontUbuntuMono_B_30
  mov [SP], R1
  mov R1, [BP-3]
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6234
  mov [SP+3], R1
  call __function_textfont_print_from_left
  mov R2, [global_title_timer]
  fsub R2, 5.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 50.000000
  fsub R1, 40.000000
  cfi R1
  mov [BP-2], R1
  mov R2, [global_title_timer]
  fsub R2, 6.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, -400.000000
  fadd R1, 10.000000
  cfi R1
  mov [BP-3], R1
  mov R1, global_FontUbuntuMono_B_30
  mov [SP], R1
  mov R1, [BP-3]
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6259
  mov [SP+3], R1
  call __function_textfont_print_from_left
  mov R2, [global_title_timer]
  fsub R2, 6.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 50.000000
  fsub R1, 40.000000
  cfi R1
  mov [BP-2], R1
  mov R2, [global_title_timer]
  fsub R2, 7.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, -500.000000
  fadd R1, 10.000000
  cfi R1
  mov [BP-3], R1
  mov R1, global_FontUbuntuMono_B_30
  mov [SP], R1
  mov R1, [BP-3]
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6284
  mov [SP+3], R1
  call __function_textfont_print_from_left
  mov R2, [global_title_timer]
  fsub R2, 7.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 50.000000
  fsub R1, 40.000000
  cfi R1
  mov [BP-2], R1
  mov R2, [global_title_timer]
  fsub R2, 8.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, -400.000000
  fadd R1, 10.000000
  cfi R1
  mov [BP-3], R1
  mov R1, global_FontUbuntuMono_B_30
  mov [SP], R1
  mov R1, [BP-3]
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6309
  mov [SP+3], R1
  call __function_textfont_print_from_left
  mov R2, [global_title_timer]
  fsub R2, 8.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 50.000000
  fsub R1, 40.000000
  cfi R1
  mov [BP-2], R1
  mov R2, [global_title_timer]
  fsub R2, 9.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, -400.000000
  fadd R1, 10.000000
  cfi R1
  mov [BP-3], R1
  mov R1, global_FontUbuntuMono_B_30
  mov [SP], R1
  mov R1, [BP-3]
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6334
  mov [SP+3], R1
  call __function_textfont_print_from_left
  mov R2, [global_title_timer]
  fsub R2, 9.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 50.000000
  fsub R1, 40.000000
  cfi R1
  mov [BP-2], R1
  mov R2, [global_title_timer]
  fsub R2, 10.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, -450.000000
  fadd R1, 10.000000
  cfi R1
  mov [BP-3], R1
  mov R1, global_FontUbuntuMono_B_30
  mov [SP], R1
  mov R1, [BP-3]
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6359
  mov [SP+3], R1
  call __function_textfont_print_from_left
  mov R2, [global_title_timer]
  fsub R2, 10.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 50.000000
  fsub R1, 40.000000
  cfi R1
  mov [BP-2], R1
  mov R2, [global_title_timer]
  fsub R2, 11.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, -400.000000
  fadd R1, 10.000000
  cfi R1
  mov [BP-3], R1
  mov R1, global_FontUbuntuMono_B_30
  mov [SP], R1
  mov R1, [BP-3]
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6384
  mov [SP+3], R1
  call __function_textfont_print_from_left
  mov R2, [global_title_timer]
  fsub R2, 11.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 50.000000
  fsub R1, 40.000000
  cfi R1
  mov [BP-2], R1
  mov R2, [global_title_timer]
  fsub R2, 12.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, -450.000000
  fadd R1, 10.000000
  cfi R1
  mov [BP-3], R1
  mov R1, global_FontUbuntuMono_B_30
  mov [SP], R1
  mov R1, [BP-3]
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6409
  mov [SP+3], R1
  call __function_textfont_print_from_left
  mov R2, [global_title_timer]
  fsub R2, 12.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 50.000000
  fsub R1, 40.000000
  cfi R1
  mov [BP-2], R1
  mov R2, [global_title_timer]
  fsub R2, 13.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, -400.000000
  fadd R1, 10.000000
  cfi R1
  mov [BP-3], R1
  mov R1, global_FontUbuntuMono_B_30
  mov [SP], R1
  mov R1, [BP-3]
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6434
  mov [SP+3], R1
  call __function_textfont_print_from_left
  mov R2, [global_title_timer]
  fsub R2, 13.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 50.000000
  fsub R1, 40.000000
  cfi R1
  mov [BP-2], R1
  mov R2, [global_title_timer]
  fsub R2, 14.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, -510.000000
  fadd R1, 10.000000
  cfi R1
  mov [BP-3], R1
  mov R1, global_FontUbuntuMono_B_30
  mov [SP], R1
  mov R1, [BP-3]
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6459
  mov [SP+3], R1
  call __function_textfont_print_from_left
  mov R2, [global_title_timer]
  fsub R2, 14.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, 50.000000
  fsub R1, 40.000000
  cfi R1
  mov [BP-2], R1
  mov R2, [global_title_timer]
  fsub R2, 15.000000
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fmul R1, -500.000000
  fadd R1, 10.000000
  cfi R1
  mov [BP-3], R1
  mov R1, global_FontUbuntuMono_B_30
  mov [SP], R1
  mov R1, [BP-3]
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6484
  mov [SP+3], R1
  call __function_textfont_print_from_left
  mov R0, [global_effect]
  mov R1, 0
  ieq R1, R0
  jt R1, __switch_6485_case_0
  mov R1, 1
  ieq R1, R0
  jt R1, __switch_6485_case_1
  mov R1, 2
  ieq R1, R0
  jt R1, __switch_6485_case_2
  mov R1, 3
  ieq R1, R0
  jt R1, __switch_6485_case_3
  mov R1, 4
  ieq R1, R0
  jt R1, __switch_6485_case_4
  mov R1, 5
  ieq R1, R0
  jt R1, __switch_6485_case_5
  mov R1, 6
  ieq R1, R0
  jt R1, __switch_6485_case_6
  mov R1, 7
  ieq R1, R0
  jt R1, __switch_6485_case_7
  mov R1, 8
  ieq R1, R0
  jt R1, __switch_6485_case_8
  mov R1, 9
  ieq R1, R0
  jt R1, __switch_6485_case_9
  mov R1, 10
  ieq R1, R0
  jt R1, __switch_6485_case_10
  mov R1, 11
  ieq R1, R0
  jt R1, __switch_6485_case_11
  mov R1, 12
  ieq R1, R0
  jt R1, __switch_6485_case_12
  mov R1, 13
  ieq R1, R0
  jt R1, __switch_6485_case_13
  mov R1, 14
  ieq R1, R0
  jt R1, __switch_6485_case_14
  mov R1, 15
  ieq R1, R0
  jt R1, __switch_6485_case_15
  jmp __switch_6485_end
__switch_6485_case_0:
  mov R0, 160
  mov [global_info_size], R0
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 435.000000
  cfi R1
  mov [BP-2], R1
  mov R1, 5
  mov [SP], R1
  mov R1, [BP-2]
  mov [SP+1], R1
  mov R1, __literal_string_6503
  mov [SP+2], R1
  call __function_print_at
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 495.000000
  cfi R1
  mov [BP-2], R1
  mov R1, global_FontRetro_Gaming_11
  mov [SP], R1
  mov R1, 5
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6517
  mov [SP+3], R1
  call __function_textfont_print_from_left
  jmp __switch_6485_end
__switch_6485_case_1:
  mov R0, 160
  mov [global_info_size], R0
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 435.000000
  cfi R1
  mov [BP-2], R1
  mov R1, 5
  mov [SP], R1
  mov R1, [BP-2]
  mov [SP+1], R1
  mov R1, __literal_string_6535
  mov [SP+2], R1
  call __function_print_at
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 495.000000
  cfi R1
  mov [BP-2], R1
  mov R1, global_FontRetro_Gaming_11
  mov [SP], R1
  mov R1, 5
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6549
  mov [SP+3], R1
  call __function_textfont_print_from_left
  jmp __switch_6485_end
__switch_6485_case_2:
  mov R0, 160
  mov [global_info_size], R0
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 435.000000
  cfi R1
  mov [BP-2], R1
  mov R1, 5
  mov [SP], R1
  mov R1, [BP-2]
  mov [SP+1], R1
  mov R1, __literal_string_6567
  mov [SP+2], R1
  call __function_print_at
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 495.000000
  cfi R1
  mov [BP-2], R1
  mov R1, global_FontRetro_Gaming_11
  mov [SP], R1
  mov R1, 5
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6581
  mov [SP+3], R1
  call __function_textfont_print_from_left
  jmp __switch_6485_end
__switch_6485_case_3:
  mov R0, 160
  mov [global_info_size], R0
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 435.000000
  cfi R1
  mov [BP-2], R1
  mov R1, 5
  mov [SP], R1
  mov R1, [BP-2]
  mov [SP+1], R1
  mov R1, __literal_string_6599
  mov [SP+2], R1
  call __function_print_at
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 495.000000
  cfi R1
  mov [BP-2], R1
  mov R1, global_FontRetro_Gaming_11
  mov [SP], R1
  mov R1, 5
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6613
  mov [SP+3], R1
  call __function_textfont_print_from_left
  jmp __switch_6485_end
__switch_6485_case_4:
  mov R0, 160
  mov [global_info_size], R0
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 435.000000
  cfi R1
  mov [BP-2], R1
  mov R1, 5
  mov [SP], R1
  mov R1, [BP-2]
  mov [SP+1], R1
  mov R1, __literal_string_6631
  mov [SP+2], R1
  call __function_print_at
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 495.000000
  cfi R1
  mov [BP-2], R1
  mov R1, global_FontRetro_Gaming_11
  mov [SP], R1
  mov R1, 5
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6645
  mov [SP+3], R1
  call __function_textfont_print_from_left
  jmp __switch_6485_end
__switch_6485_case_5:
  mov R0, 210
  mov [global_info_size], R0
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 440.000000
  cfi R1
  mov [BP-2], R1
  mov R1, 5
  mov [SP], R1
  mov R1, [BP-2]
  mov [SP+1], R1
  mov R1, __literal_string_6663
  mov [SP+2], R1
  call __function_print_at
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 495.000000
  cfi R1
  mov [BP-2], R1
  mov R1, global_FontRetro_Gaming_11
  mov [SP], R1
  mov R1, 5
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6677
  mov [SP+3], R1
  call __function_textfont_print_from_left
  jmp __switch_6485_end
__switch_6485_case_6:
  mov R0, 230
  mov [global_info_size], R0
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 440.000000
  cfi R1
  mov [BP-2], R1
  mov R1, 5
  mov [SP], R1
  mov R1, [BP-2]
  mov [SP+1], R1
  mov R1, __literal_string_6695
  mov [SP+2], R1
  call __function_print_at
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 515.000000
  cfi R1
  mov [BP-2], R1
  mov R1, global_FontRetro_Gaming_11
  mov [SP], R1
  mov R1, 5
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6709
  mov [SP+3], R1
  call __function_textfont_print_from_left
  jmp __switch_6485_end
__switch_6485_case_7:
  mov R0, 200
  mov [global_info_size], R0
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 440.000000
  cfi R1
  mov [BP-2], R1
  mov R1, 5
  mov [SP], R1
  mov R1, [BP-2]
  mov [SP+1], R1
  mov R1, __literal_string_6727
  mov [SP+2], R1
  call __function_print_at
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 495.000000
  cfi R1
  mov [BP-2], R1
  mov R1, global_FontRetro_Gaming_11
  mov [SP], R1
  mov R1, 5
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6741
  mov [SP+3], R1
  call __function_textfont_print_from_left
  jmp __switch_6485_end
__switch_6485_case_8:
  mov R0, 120
  mov [global_info_size], R0
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 440.000000
  cfi R1
  mov [BP-2], R1
  mov R1, 5
  mov [SP], R1
  mov R1, [BP-2]
  mov [SP+1], R1
  mov R1, __literal_string_6759
  mov [SP+2], R1
  call __function_print_at
  jmp __switch_6485_end
__switch_6485_case_9:
  mov R0, 120
  mov [global_info_size], R0
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 440.000000
  cfi R1
  mov [BP-2], R1
  mov R1, 5
  mov [SP], R1
  mov R1, [BP-2]
  mov [SP+1], R1
  mov R1, __literal_string_6777
  mov [SP+2], R1
  call __function_print_at
  jmp __switch_6485_end
__switch_6485_case_10:
  mov R0, 140
  mov [global_info_size], R0
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 440.000000
  cfi R1
  mov [BP-2], R1
  mov R1, 5
  mov [SP], R1
  mov R1, [BP-2]
  mov [SP+1], R1
  mov R1, __literal_string_6795
  mov [SP+2], R1
  call __function_print_at
  jmp __switch_6485_end
__switch_6485_case_11:
  mov R0, 160
  mov [global_info_size], R0
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 440.000000
  cfi R1
  mov [BP-2], R1
  mov R1, 5
  mov [SP], R1
  mov R1, [BP-2]
  mov [SP+1], R1
  mov R1, __literal_string_6813
  mov [SP+2], R1
  call __function_print_at
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 505.000000
  cfi R1
  mov [BP-2], R1
  mov R1, global_FontRetro_Gaming_11
  mov [SP], R1
  mov R1, 5
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6827
  mov [SP+3], R1
  call __function_textfont_print_from_left
  jmp __switch_6485_end
__switch_6485_case_12:
  mov R0, 150
  mov [global_info_size], R0
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 440.000000
  cfi R1
  mov [BP-2], R1
  mov R1, 5
  mov [SP], R1
  mov R1, [BP-2]
  mov [SP+1], R1
  mov R1, __literal_string_6845
  mov [SP+2], R1
  call __function_print_at
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 495.000000
  cfi R1
  mov [BP-2], R1
  mov R1, global_FontRetro_Gaming_11
  mov [SP], R1
  mov R1, 5
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6859
  mov [SP+3], R1
  call __function_textfont_print_from_left
  jmp __switch_6485_end
__switch_6485_case_13:
  mov R0, 160
  mov [global_info_size], R0
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 440.000000
  cfi R1
  mov [BP-2], R1
  mov R1, 5
  mov [SP], R1
  mov R1, [BP-2]
  mov [SP+1], R1
  mov R1, __literal_string_6877
  mov [SP+2], R1
  call __function_print_at
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 505.000000
  cfi R1
  mov [BP-2], R1
  mov R1, global_FontRetro_Gaming_11
  mov [SP], R1
  mov R1, 5
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6891
  mov [SP+3], R1
  call __function_textfont_print_from_left
  jmp __switch_6485_end
__switch_6485_case_14:
  mov R0, 200
  mov [global_info_size], R0
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 440.000000
  cfi R1
  mov [BP-2], R1
  mov R1, 5
  mov [SP], R1
  mov R1, [BP-2]
  mov [SP+1], R1
  mov R1, __literal_string_6909
  mov [SP+2], R1
  call __function_print_at
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 485.000000
  cfi R1
  mov [BP-2], R1
  mov R1, global_FontRetro_Gaming_11
  mov [SP], R1
  mov R1, 5
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6923
  mov [SP+3], R1
  call __function_textfont_print_from_left
  jmp __switch_6485_end
__switch_6485_case_15:
  mov R0, 160
  mov [global_info_size], R0
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 440.000000
  cfi R1
  mov [BP-2], R1
  mov R1, 5
  mov [SP], R1
  mov R1, [BP-2]
  mov [SP+1], R1
  mov R1, __literal_string_6941
  mov [SP+2], R1
  call __function_print_at
  mov R2, [global_info_offset]
  mov [SP], R2
  mov R2, 4
  mov [SP+1], R2
  mov R2, 6
  mov [SP+2], R2
  call __function_ease
  mov R1, R0
  fsgn R1
  mov R2, [global_info_size]
  cif R2
  fmul R1, R2
  fadd R1, 490.000000
  cfi R1
  mov [BP-2], R1
  mov R1, global_FontRetro_Gaming_11
  mov [SP], R1
  mov R1, 5
  mov [SP+1], R1
  mov R1, [BP-2]
  mov [SP+2], R1
  mov R1, __literal_string_6955
  mov [SP+3], R1
  call __function_textfont_print_from_left
__switch_6485_end:
__function_info_return:
  mov SP, BP
  pop BP
  ret

__function_main:
  push BP
  mov BP, SP
  isub SP, 5
  call __function_setupFontUbuntuMono_B_30
  call __function_setupFontRetro_Gaming_11
  mov R1, 0
  mov [SP], R1
  call __function_select_texture
  mov R1, 0
  mov [SP], R1
  call __function_select_region
  mov R1, 0
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 137
  mov [SP+2], R1
  mov R1, 93
  mov [SP+3], R1
  call __function_define_region_center
  mov R1, 1
  mov [SP], R1
  call __function_select_region
  mov R1, 139
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 186
  mov [SP+2], R1
  mov R1, 47
  mov [SP+3], R1
  call __function_define_region_center
  mov R1, 2
  mov [SP], R1
  call __function_select_region
  mov R1, 188
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 215
  mov [SP+2], R1
  mov R1, 27
  mov [SP+3], R1
  call __function_define_region_center
  mov R1, 3
  mov [SP], R1
  call __function_select_region
  mov R1, 139
  mov [SP], R1
  mov R1, 49
  mov [SP+1], R1
  mov R1, 177
  mov [SP+2], R1
  mov R1, 82
  mov [SP+3], R1
  call __function_define_region_center
  mov R1, 4
  mov [SP], R1
  call __function_select_region
  mov R1, 217
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  mov R1, 264
  mov [SP+2], R1
  mov R1, 47
  mov [SP+3], R1
  call __function_define_region_topleft
__while_6997_start:
__while_6997_continue:
  mov R0, 1
  cib R0
  jf R0, __while_6997_end
  mov R1, [global_clear_color]
  mov [SP], R1
  call __function_clear_screen
__if_7002_start:
  mov R0, [global_is_intro_over]
  bnot R0
  jf R0, __if_7002_else
  call __function_intro
  jmp __if_7002_end
__if_7002_else:
__if_7007_start:
  call __function_gamepad_button_start
  mov R1, R0
  ieq R1, 1
  mov R0, R1
  jf R0, __if_7007_end
  mov R0, 0.000000
  mov [global_timer], R0
__if_7007_end:
__if_7014_start:
  call __function_gamepad_button_a
  mov R1, R0
  ieq R1, 1
  jf R1, __LogicalAnd_ShortCircuit_7020
  mov R2, [global_info_open]
  bnot R2
  and R1, R2
__LogicalAnd_ShortCircuit_7020:
  mov R0, R1
  jf R0, __if_7014_else
  mov R0, 1
  mov [global_info_open], R0
  jmp __if_7014_end
__if_7014_else:
__if_7024_start:
  call __function_gamepad_button_a
  mov R1, R0
  ieq R1, 1
  jf R1, __LogicalAnd_ShortCircuit_7029
  mov R2, [global_info_open]
  and R1, R2
__LogicalAnd_ShortCircuit_7029:
  mov R0, R1
  jf R0, __if_7024_end
  mov R0, 0
  mov [global_info_open], R0
__if_7024_end:
__if_7014_end:
__if_7033_start:
  call __function_gamepad_left
  mov R1, R0
  ieq R1, 1
  jf R1, __LogicalAnd_ShortCircuit_7038
  mov R2, [global_effect]
  igt R2, 0
  and R1, R2
__LogicalAnd_ShortCircuit_7038:
  mov R0, R1
  jf R0, __if_7033_end
  mov R0, [global_effect]
  mov R1, R0
  isub R1, 1
  mov [global_effect], R1
  mov R0, 0.000000
  mov [global_timer], R0
__if_7033_end:
__if_7047_start:
  call __function_gamepad_right
  mov R1, R0
  ieq R1, 1
  jf R1, __LogicalAnd_ShortCircuit_7052
  mov R2, [global_effect]
  ilt R2, 15
  and R1, R2
__LogicalAnd_ShortCircuit_7052:
  mov R0, R1
  jf R0, __if_7047_end
  mov R0, [global_effect]
  mov R1, R0
  iadd R1, 1
  mov [global_effect], R1
  mov R0, 0.000000
  mov [global_timer], R0
  mov R0, 0
  mov [global_show_controls], R0
__if_7047_end:
__if_7064_start:
  mov R0, [global_show_controls]
  jf R0, __if_7064_end
  mov R1, 0
  mov [SP], R1
  call __function_select_texture
  mov R1, 4
  mov [SP], R1
  call __function_select_region
  mov R3, [global_timer]
  fmul R3, 3.000000
  mov [SP], R3
  call __function_sin
  mov R2, R0
  fmul R2, 64.000000
  fadd R2, 192.000000
  cfi R2
  mov [BP-1], R2
  mov R2, [BP-1]
  mov [SP], R2
  call __function_make_gray
  mov R1, R0
  mov [BP-1], R1
  mov R1, [BP-1]
  mov [SP], R1
  call __function_set_multiply_color
  mov R1, 10
  mov [SP], R1
  mov R1, 200
  mov [SP+1], R1
  call __function_draw_region_at
  mov R1, global_FontRetro_Gaming_11
  mov [SP], R1
  mov R1, 68
  mov [SP+1], R1
  mov R1, 210
  mov [SP+2], R1
  mov R1, __literal_string_7090
  mov [SP+3], R1
  call __function_textfont_print_from_left
  mov R1, -1
  mov [SP], R1
  call __function_set_multiply_color
__if_7064_end:
  mov R1, 0
  mov [SP], R1
  call __function_select_texture
  mov R1, 1
  mov [SP], R1
  call __function_select_region
  mov R0, [global_effect]
  mov R1, 0
  ieq R1, R0
  jt R1, __switch_7097_case_0
  mov R1, 1
  ieq R1, R0
  jt R1, __switch_7097_case_1
  mov R1, 2
  ieq R1, R0
  jt R1, __switch_7097_case_2
  mov R1, 3
  ieq R1, R0
  jt R1, __switch_7097_case_3
  mov R1, 4
  ieq R1, R0
  jt R1, __switch_7097_case_4
  mov R1, 5
  ieq R1, R0
  jt R1, __switch_7097_case_5
  mov R1, 6
  ieq R1, R0
  jt R1, __switch_7097_case_6
  mov R1, 7
  ieq R1, R0
  jt R1, __switch_7097_case_7
  mov R1, 8
  ieq R1, R0
  jt R1, __switch_7097_case_8
  mov R1, 9
  ieq R1, R0
  jt R1, __switch_7097_case_9
  mov R1, 10
  ieq R1, R0
  jt R1, __switch_7097_case_10
  mov R1, 11
  ieq R1, R0
  jt R1, __switch_7097_case_11
  mov R1, 12
  ieq R1, R0
  jt R1, __switch_7097_case_12
  mov R1, 13
  ieq R1, R0
  jt R1, __switch_7097_case_13
  mov R1, 14
  ieq R1, R0
  jt R1, __switch_7097_case_14
  mov R1, 15
  ieq R1, R0
  jt R1, __switch_7097_case_15
  jmp __switch_7097_end
__switch_7097_case_0:
  mov R1, [global_timer]
  mov [SP], R1
  call __function_effect_offset
  jmp __switch_7097_end
__switch_7097_case_1:
  mov R1, [global_timer]
  mov [SP], R1
  call __function_effect_simple_ease
  jmp __switch_7097_end
__switch_7097_case_2:
  mov R1, [global_timer]
  mov [SP], R1
  call __function_effect_different_ease
  jmp __switch_7097_end
__switch_7097_case_3:
  mov R1, [global_timer]
  mov [SP], R1
  call __function_effect_two_axis_ease
  jmp __switch_7097_end
__switch_7097_case_4:
  mov R1, [global_timer]
  mov [SP], R1
  call __function_effect_time_offset
  jmp __switch_7097_end
__switch_7097_case_5:
  mov R1, [global_timer]
  mov [SP], R1
  call __function_effect_follow_by_offset
  jmp __switch_7097_end
__switch_7097_case_6:
  mov R1, [global_timer]
  mov [SP], R1
  call __function_effect_only_one_offset
  jmp __switch_7097_end
__switch_7097_case_7:
  mov R1, [global_timer]
  mov [SP], R1
  call __function_effect_concatenate
  jmp __switch_7097_end
__switch_7097_case_8:
  mov R1, [global_timer]
  mov [SP], R1
  call __function_effect_scale
  jmp __switch_7097_end
__switch_7097_case_9:
  mov R1, [global_timer]
  mov [SP], R1
  call __function_effect_rotation
  jmp __switch_7097_end
__switch_7097_case_10:
  mov R1, [global_timer]
  mov [SP], R1
  call __function_effect_rotozoomed
  jmp __switch_7097_end
__switch_7097_case_11:
  mov R1, [global_timer]
  mov [SP], R1
  call __function_effect_none
  jmp __switch_7097_end
__switch_7097_case_12:
  mov R1, [global_timer]
  mov [SP], R1
  call __function_effect_dual_none
  jmp __switch_7097_end
__switch_7097_case_13:
  mov R1, [global_timer]
  mov [SP], R1
  call __function_effect_speed
  jmp __switch_7097_end
__switch_7097_case_14:
  mov R1, [global_timer]
  mov [SP], R1
  call __function_effect_multiple_speed
  jmp __switch_7097_end
__switch_7097_case_15:
  mov R1, [global_timer]
  mov [SP], R1
  call __function_effect_repeat
__switch_7097_end:
  call __function_info
  mov R0, [global_timer]
  fadd R0, 0.010000
  mov [global_timer], R0
__if_7002_end:
  call __function_end_frame
  jmp __while_6997_start
__while_6997_end:
__function_main_return:
  mov SP, BP
  pop BP
  ret

__literal_string_1130:
  string "0123456789ABCDEF"
__literal_string_1167:
  string "-2147483648"
__literal_string_1318:
  string "."
__literal_string_1329:
  string "0"
__literal_string_6055:
  string "PRESS START\nTO REPLAY"
__literal_string_6111:
  string "Effect 1: Offset."
__literal_string_6134:
  string "Effect 2: Simple ease."
__literal_string_6159:
  string "Effect 3: Different easing."
__literal_string_6184:
  string "Effect 4: Dual axis easing."
__literal_string_6209:
  string "Effect 5: Time offset"
__literal_string_6234:
  string "Effect 6: Follow by offset"
__literal_string_6259:
  string "Effect 7: Move only one"
__literal_string_6284:
  string "Effect 8: Concatenate easings"
__literal_string_6309:
  string "Effect 9: Scale"
__literal_string_6334:
  string "Effect 10: Rotate"
__literal_string_6359:
  string "Effect 11: Scale and rotate"
__literal_string_6384:
  string "Effect 12: NONE type"
__literal_string_6409:
  string "Effect 13: Two NONE types"
__literal_string_6434:
  string "Effect 14: Speed control"
__literal_string_6459:
  string "Effect 15: Multiple speed control"
__literal_string_6484:
  string "Effect 16: Looped"
__literal_string_6503:
  string "To offset any sprite, add a number to its position.\nMultiplying the number will make it move quicker."
__literal_string_6517:
  string "FORMULA: (100 + t*20, 100 )"
__literal_string_6535:
  string "The ease function enables us to simply create\npretty and smooth movements."
__literal_string_6549:
  string "FORMULA: (100 + ease(t, SINE, SINE)*300, 100 );"
__literal_string_6567:
  string "The ease function specifies two easing effects:\none for the first half and one for the second."
__literal_string_6581:
  string "FORMULA: (100 + ease(t, QUINT, BACK)*300, 100 );"
__literal_string_6599:
  string "The ease function can be used in both\nX and Y axis at the same time."
__literal_string_6613:
  string "FORMULA: (100 + ease(t, BACK, BACK)*300, 100 + ease(t, SINE, SINE)*100 );"
__literal_string_6631:
  string "By adding or subtracting t, the easing might\nbegin before or after a certain period."
__literal_string_6645:
  string "FORMULA: (100 + ease(t-1, QUINT, QUINT)*300, 100 );"
__literal_string_6663:
  string "You can use timing offset to make various objects\n\"follow\" each other."
__literal_string_6677:
  string "FORMULA:\n(100 + ease(t, QUINT, QUINT)*300, 60 );\n(100 + ease(t-0.2, QUINT, QUINT)*300, 110 );\n(100 + ease(t-0.4, QUINT, QUINT)*300, 160 );\n(100 + ease(t-0.6, QUINT, QUINT)*300, 210 );\n"
__literal_string_6695:
  string "If you subtract one easing to another with the same\namplitude, both will cancel.\napply it to various objects with different offsets."
__literal_string_6709:
  string "FORMULA:\n(100, 100 + ease(t, QUINT, BACK)*50 - ease(t-1, BACK, QUINT)*50);\n(150, 100 + ease(t-1, QUINT, BACK)*50 - ease(t-2, BACK, QUINT)*50);\n(200, 100 + ease(t-2, QUINT, BACK)*50 - ease(t-3, BACK, QUINT)*50);\n(250, 100 + ease(t-3, QUINT, BACK)*50 - ease(t-4, BACK, QUINT)*50);"
__literal_string_6727:
  string "Adding easings with temporal offset will result in\na variety of motions occurring one after the other."
__literal_string_6741:
  string "FORMULA:\n(100 + ease(t, QUINT, BACK)*100 +\n            ease(t-1.5, SINE, SINE)*100 +\n            ease(t-3, BACK, BACK)*100, 60);"
__literal_string_6759:
  string "Easings can be applied to scale property."
__literal_string_6777:
  string "Easings can be applied to rotation property."
__literal_string_6795:
  string "Easings can be applied to scale and roration\nproperties simultaneously."
__literal_string_6813:
  string "NONE type can be used if you don\'t need\neasing in or easing out effect."
__literal_string_6827:
  string "FORMULA: (ease(t, NONE, CUBIC), 100);"
__literal_string_6845:
  string "Using NONE on both parts will result in an abrupt return."
__literal_string_6859:
  string "FORMULA: (ease(t, NONE, NONE), 100);"
__literal_string_6877:
  string "Multiplying or dividing t will result in a\nspeed up or speed down."
__literal_string_6891:
  string "FORMULA: (100 + ease(t/2, SINE, SINE)*300, 100);"
__literal_string_6909:
  string "A better demonstration of speed control."
__literal_string_6923:
  string "FORMULA:\n(100 + ease(t/2, QUINT, QUINT)*300, 60);\n(100 + ease(t,     QUINT, QUINT)*300, 110);\n(100 + ease(t*2, QUINT, QUINT)*300, 160);\n(100 + ease(t*3, QUINT, QUINT)*300, 210);\n"
__literal_string_6941:
  string "A triangular wave can cause an\ninfinite back and forth movement."
__literal_string_6955:
  string "FORMULA:\n(100 + ease( (asin( cos( t*2+pi ) ) + 1.5707963) / pi, QUINT, QUINT)*300, 100);"
__literal_string_7090:
  string "Use left and right\nto navigate"
