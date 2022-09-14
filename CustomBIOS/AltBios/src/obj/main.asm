; hardware error vector
  call __function_error_handler
  wait
  hlt

; program start section
  call __global_scope_initialization
  call __function_main
  hlt

; location of global variables
  define global_ever 0
  define global_evera 1
  define global_ha 2

__global_scope_initialization:
  push BP
  mov BP, SP
  mov R0, 1
  mov [global_ever], R0
  mov R0, 0
  mov [global_evera], R0
  mov R0, 0
  mov [global_ha], R0
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
__for_286_start:
  mov R0, [BP-10]
  mov R1, [BP+10]
  ilt R0, R1
  jf R0, __for_286_end
  mov R0, 0
  mov [BP-11], R0
__for_296_start:
  mov R0, [BP-11]
  mov R1, [BP+9]
  ilt R0, R1
  jf R0, __for_296_end
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
__for_296_continue:
  mov R0, [BP-11]
  iadd R0, 1
  mov [BP-11], R0
  jmp __for_296_start
__for_296_end:
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
__for_286_continue:
  mov R0, [BP-10]
  iadd R0, 1
  mov [BP-10], R0
  jmp __for_286_start
__for_286_end:
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
__while_441_start:
__while_441_continue:
  mov R0, [BP+4]
  mov R0, [R0]
  cib R0
  jf R0, __while_441_end
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
__if_454_start:
  mov R0, [BP+4]
  mov R0, [R0]
  ieq R0, 10
  jf R0, __if_454_end
  mov R0, [BP-2]
  mov [BP+2], R0
  mov R0, [BP+3]
  iadd R0, 20
  mov [BP+3], R0
__if_454_end:
  mov R0, [BP+4]
  iadd R0, 1
  mov [BP+4], R0
  jmp __while_441_start
__while_441_end:
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
  jf R0, __LogicalAnd_ShortCircuit_539
  mov R2, [BP+3]
  mov R1, [R2]
  imod R1, 100
  ine R1, 0
  and R0, R1
__LogicalAnd_ShortCircuit_539:
  mov [BP-14], R0
__if_548_start:
  mov R0, [BP-14]
  jf R0, __if_548_end
  mov R0, 29
  mov [BP-12], R0
__if_548_end:
  mov R0, 1
  mov R1, [BP+3]
  iadd R1, 1
  mov [R1], R0
  mov R0, 0
  mov [BP-15], R0
__for_559_start:
  mov R0, [BP-15]
  ilt R0, 11
  jf R0, __for_559_end
__if_569_start:
  mov R0, [BP-1]
  lea R1, [BP-13]
  mov R2, [BP-15]
  iadd R1, R2
  mov R1, [R1]
  ilt R0, R1
  jf R0, __if_569_end
  mov R0, [BP-1]
  iadd R0, 1
  mov R1, [BP+3]
  iadd R1, 2
  mov [R1], R0
  jmp __function_translate_date_return
__if_569_end:
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
__for_559_continue:
  mov R0, [BP-15]
  iadd R0, 1
  mov [BP-15], R0
  jmp __for_559_start
__for_559_end:
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
__while_644_start:
__while_644_continue:
  call __function_get_frame_counter
  mov R1, R0
  mov R2, [BP-2]
  ilt R1, R2
  mov R0, R1
  jf R0, __while_644_end
  call __function_end_frame
  jmp __while_644_start
__while_644_end:
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

__function_cartridge_connected:
  push BP
  mov BP, SP
  in R0, CAR_Connected
__function_cartridge_connected_return:
  mov SP, BP
  pop BP
  ret

__function_run_cartridge:
  push BP
  mov BP, SP
  isub SP, 1
  mov R1, 0
  mov [SP], R1
  call __function_stop_channel
  jmp 0x20000000
__function_run_cartridge_return:
  mov SP, BP
  pop BP
  ret

__function_rand_betw:
  push BP
  mov BP, SP
  isub SP, 1
  push R1
  push R2
  call __function_rand
  mov R1, R0
  mov R2, [BP+3]
  imod R1, R2
  mov R2, [BP+2]
  isub R1, R2
  iadd R1, 1
  mov R2, [BP+2]
  iadd R1, R2
  mov R0, R1
  mov [BP-1], R0
  mov R0, [BP-1]
__function_rand_betw_return:
  pop R2
  pop R1
  mov SP, BP
  pop BP
  ret

__function_request_cartridge:
  push BP
  mov BP, SP
  isub SP, 135
  mov R0, 0
  mov [BP-129], R0
__while_716_start:
__while_716_continue:
  mov R0, 1
  jf R0, __while_716_end
  mov R0, [BP-130]
  mov R1, R0
  iadd R1, 1
  mov [BP-130], R1
  mov R2, 4
  mov [SP], R2
  mov R2, 0
  mov [SP+1], R2
  mov R2, 1
  mov [SP+2], R2
  call __function_make_color_rgb
  mov [BP-132], R0
  mov R1, [BP-132]
  mov [SP], R1
  call __function_clear_screen
__if_726_start:
  mov R0, [BP-130]
  igt R0, 75
  jf R0, __if_726_end
  mov R0, 0
  mov [BP-131], R0
__for_731_start:
  mov R0, [BP-131]
  ilt R0, 64
  jf R0, __for_731_end
__if_741_start:
  mov R0, [BP-129]
  ilt R0, 64
  jf R0, __if_741_end
  mov R2, 0
  mov [SP], R2
  mov R2, 360
  mov [SP+1], R2
  call __function_rand_betw
  mov R1, R0
  lea R2, [BP-128]
  mov R3, [BP-131]
  iadd R2, R3
  mov [R2], R1
  mov R0, R1
  mov R2, 0
  mov [SP], R2
  mov R2, 640
  mov [SP+1], R2
  call __function_rand_betw
  mov R1, R0
  lea R2, [BP-64]
  mov R3, [BP-131]
  iadd R2, R3
  mov [R2], R1
  mov R0, R1
  mov R0, [BP-129]
  iadd R0, 1
  mov [BP-129], R0
__if_741_end:
__if_763_start:
  lea R0, [BP-128]
  mov R1, [BP-131]
  iadd R0, R1
  mov R0, [R0]
  igt R0, 360
  jf R0, __if_763_end
  mov R2, 1
  mov [SP], R2
  mov R2, 640
  mov [SP+1], R2
  call __function_rand_betw
  mov R1, R0
  lea R2, [BP-64]
  mov R3, [BP-131]
  iadd R2, R3
  mov [R2], R1
  mov R0, R1
  mov R0, -7
  lea R1, [BP-128]
  mov R2, [BP-131]
  iadd R1, R2
  mov [R1], R0
__if_763_end:
  lea R0, [BP-128]
  mov R1, [BP-131]
  iadd R0, R1
  mov R0, [R0]
  iadd R0, 7
  lea R1, [BP-128]
  mov R2, [BP-131]
  iadd R1, R2
  mov [R1], R0
  mov R1, 261
  mov [SP], R1
  call __function_select_region
  mov R1, 3
  cif R1
  mov [SP], R1
  mov R1, 2
  cif R1
  mov [SP+1], R1
  call __function_set_drawing_scale
  lea R1, [BP-64]
  mov R2, [BP-131]
  iadd R1, R2
  mov R1, [R1]
  mov [SP], R1
  lea R1, [BP-128]
  mov R2, [BP-131]
  iadd R1, R2
  mov R1, [R1]
  mov [SP+1], R1
  call __function_draw_region_zoomed_at
__for_731_continue:
  mov R0, [BP-131]
  mov R1, R0
  iadd R1, 1
  mov [BP-131], R1
  jmp __for_731_start
__for_731_end:
  mov R1, 262
  mov [SP], R1
  call __function_select_region
  mov R1, 700
  cif R1
  mov [SP], R1
  mov R1, 2
  cif R1
  mov [SP+1], R1
  call __function_set_drawing_scale
  mov R1, 0
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  call __function_draw_region_zoomed_at
  mov R1, 265
  mov [SP], R1
  call __function_select_region
  mov R1, 320
  mov [SP], R1
  mov R1, 170
  mov [SP+1], R1
  call __function_draw_region_at
  mov R1, 263
  mov [SP], R1
  call __function_select_region
  mov R1, 320
  mov [SP], R1
  mov R1, 120
  mov [SP+1], R1
  call __function_draw_region_at
  mov R1, 264
  mov [SP], R1
  call __function_select_region
  mov R1, 320
  mov [SP], R1
  mov R1, 220
  mov [SP+1], R1
  call __function_draw_region_at
__if_726_end:
  call __function_end_frame
  jmp __while_716_start
__while_716_end:
__function_request_cartridge_return:
  mov SP, BP
  pop BP
  ret

__function_error_handler:
  push BP
  mov BP, SP
  isub SP, 7
  mov [BP-1], R0
  mov [BP-2], R1
  mov [BP-3], R2
  mov [BP-4], R3
  call __function_end_frame
__if_855_start:
  mov R0, [BP-1]
  ieq R0, 0
  jf R0, __if_855_else
  mov R1, 10
  mov [SP], R1
  mov R1, 10
  mov [SP+1], R1
  mov R1, __literal_string_863
  mov [SP+2], R1
  call __function_print_at
  jmp __if_855_end
__if_855_else:
__if_864_start:
  mov R0, [BP-1]
  ieq R0, 1
  jf R0, __if_864_else
  mov R1, 10
  mov [SP], R1
  mov R1, 10
  mov [SP+1], R1
  mov R1, __literal_string_872
  mov [SP+2], R1
  call __function_print_at
  jmp __if_864_end
__if_864_else:
__if_873_start:
  mov R0, [BP-1]
  ieq R0, 2
  jf R0, __if_873_else
  mov R1, 10
  mov [SP], R1
  mov R1, 10
  mov [SP+1], R1
  mov R1, __literal_string_881
  mov [SP+2], R1
  call __function_print_at
  jmp __if_873_end
__if_873_else:
__if_882_start:
  mov R0, [BP-1]
  ieq R0, 3
  jf R0, __if_882_else
  mov R1, 10
  mov [SP], R1
  mov R1, 10
  mov [SP+1], R1
  mov R1, __literal_string_890
  mov [SP+2], R1
  call __function_print_at
  jmp __if_882_end
__if_882_else:
__if_891_start:
  mov R0, [BP-1]
  ieq R0, 4
  jf R0, __if_891_else
  mov R1, 10
  mov [SP], R1
  mov R1, 10
  mov [SP+1], R1
  mov R1, __literal_string_899
  mov [SP+2], R1
  call __function_print_at
  jmp __if_891_end
__if_891_else:
__if_900_start:
  mov R0, [BP-1]
  ieq R0, 5
  jf R0, __if_900_else
  mov R1, 10
  mov [SP], R1
  mov R1, 10
  mov [SP+1], R1
  mov R1, __literal_string_908
  mov [SP+2], R1
  call __function_print_at
  jmp __if_900_end
__if_900_else:
__if_909_start:
  mov R0, [BP-1]
  ieq R0, 6
  jf R0, __if_909_else
  mov R1, 10
  mov [SP], R1
  mov R1, 10
  mov [SP+1], R1
  mov R1, __literal_string_917
  mov [SP+2], R1
  call __function_print_at
  jmp __if_909_end
__if_909_else:
__if_918_start:
  mov R0, [BP-1]
  ieq R0, 7
  jf R0, __if_918_else
  mov R1, 10
  mov [SP], R1
  mov R1, 10
  mov [SP+1], R1
  mov R1, __literal_string_926
  mov [SP+2], R1
  call __function_print_at
  jmp __if_918_end
__if_918_else:
__if_927_start:
  mov R0, [BP-1]
  ieq R0, 8
  jf R0, __if_927_else
  mov R1, 10
  mov [SP], R1
  mov R1, 10
  mov [SP+1], R1
  mov R1, __literal_string_935
  mov [SP+2], R1
  call __function_print_at
  jmp __if_927_end
__if_927_else:
__if_936_start:
  mov R0, [BP-1]
  ieq R0, 9
  jf R0, __if_936_else
  mov R1, 10
  mov [SP], R1
  mov R1, 10
  mov [SP+1], R1
  mov R1, __literal_string_944
  mov [SP+2], R1
  call __function_print_at
  jmp __if_936_end
__if_936_else:
__if_945_start:
  mov R0, [BP-1]
  ieq R0, 10
  jf R0, __if_945_else
  mov R1, 10
  mov [SP], R1
  mov R1, 10
  mov [SP+1], R1
  mov R1, __literal_string_953
  mov [SP+2], R1
  call __function_print_at
  jmp __if_945_end
__if_945_else:
  mov R1, 10
  mov [SP], R1
  mov R1, 10
  mov [SP+1], R1
  mov R1, __literal_string_958
  mov [SP+2], R1
  call __function_print_at
__if_945_end:
__if_936_end:
__if_927_end:
__if_918_end:
__if_909_end:
__if_900_end:
__if_891_end:
__if_882_end:
__if_873_end:
__if_864_end:
__if_855_end:
  call __function_stop_all_channels
__function_error_handler_return:
  mov SP, BP
  pop BP
  ret

__function_magik:
  push BP
  mov BP, SP
  isub SP, 134
  mov R0, 0
  mov [BP-129], R0
  mov R1, -1
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  call __function_play_sound_in_channel
__while_983_start:
__while_983_continue:
  mov R0, 1
  jf R0, __while_983_end
  mov R0, [global_ha]
  mov R1, R0
  iadd R1, 1
  mov [global_ha], R1
__if_988_start:
  mov R0, [global_ha]
  igt R0, 150
  jf R0, __if_988_end
  mov R0, [global_ever]
  mov R1, [global_evera]
  iadd R0, R1
  mov [global_ever], R0
  mov R0, [global_evera]
  mov R1, R0
  iadd R1, 1
  mov [global_evera], R1
  mov R1, 260
  mov [SP], R1
  call __function_select_region
  mov R1, 326
  mov [SP], R1
  mov R1, 22
  mov [SP+1], R1
  mov R1, 326
  mov [SP+2], R1
  mov R1, 22
  mov [SP+3], R1
  call __function_define_region_topleft
__if_988_end:
__if_1005_start:
  mov R0, [global_ha]
  igt R0, 65
  jf R0, __if_1005_end
  mov R0, 0
  mov [BP-130], R0
__for_1010_start:
  mov R0, [BP-130]
  ilt R0, 64
  jf R0, __for_1010_end
__if_1020_start:
  mov R0, [BP-129]
  ilt R0, 64
  jf R0, __if_1020_end
  mov R2, 0
  mov [SP], R2
  mov R2, 360
  mov [SP+1], R2
  call __function_rand_betw
  mov R1, R0
  lea R2, [BP-128]
  mov R3, [BP-130]
  iadd R2, R3
  mov [R2], R1
  mov R0, R1
  mov R2, 0
  mov [SP], R2
  mov R2, 640
  mov [SP+1], R2
  call __function_rand_betw
  mov R1, R0
  lea R2, [BP-64]
  mov R3, [BP-130]
  iadd R2, R3
  mov [R2], R1
  mov R0, R1
  mov R0, [BP-129]
  iadd R0, 1
  mov [BP-129], R0
__if_1020_end:
__if_1042_start:
  mov R0, [global_ha]
  ilt R0, 120
  jf R0, __if_1042_end
__if_1047_start:
  lea R0, [BP-128]
  mov R1, [BP-130]
  iadd R0, R1
  mov R0, [R0]
  igt R0, 360
  jf R0, __if_1047_end
  mov R2, 1
  mov [SP], R2
  mov R2, 640
  mov [SP+1], R2
  call __function_rand_betw
  mov R1, R0
  lea R2, [BP-64]
  mov R3, [BP-130]
  iadd R2, R3
  mov [R2], R1
  mov R0, R1
  mov R0, -7
  lea R1, [BP-128]
  mov R2, [BP-130]
  iadd R1, R2
  mov [R1], R0
__if_1047_end:
__if_1042_end:
  lea R1, [BP-128]
  mov R2, [BP-130]
  iadd R1, R2
  mov R1, [R1]
  mov R3, 2
  mov [SP], R3
  mov R3, 12
  mov [SP+1], R3
  call __function_rand_betw
  mov R2, R0
  iadd R1, R2
  lea R2, [BP-128]
  mov R3, [BP-130]
  iadd R2, R3
  mov [R2], R1
  mov R0, R1
  mov R1, 261
  mov [SP], R1
  call __function_select_region
  mov R1, 3
  cif R1
  mov [SP], R1
  mov R1, 2
  cif R1
  mov [SP+1], R1
  call __function_set_drawing_scale
  lea R1, [BP-64]
  mov R2, [BP-130]
  iadd R1, R2
  mov R1, [R1]
  mov [SP], R1
  lea R1, [BP-128]
  mov R2, [BP-130]
  iadd R1, R2
  mov R1, [R1]
  mov [SP+1], R1
  call __function_draw_region_zoomed_at
__for_1010_continue:
  mov R0, [BP-130]
  mov R1, R0
  iadd R1, 1
  mov [BP-130], R1
  jmp __for_1010_start
__for_1010_end:
  mov R1, 259
  mov [SP], R1
  call __function_select_region
  mov R1, 700
  cif R1
  mov [SP], R1
  mov R1, 2
  cif R1
  mov [SP+1], R1
  call __function_set_drawing_scale
  mov R1, 0
  mov [SP], R1
  mov R1, [global_ever]
  isgn R1
  mov [SP+1], R1
  call __function_draw_region_zoomed_at
__if_1005_end:
  mov R1, 260
  mov [SP], R1
  call __function_select_region
  mov R1, 700
  cif R1
  mov [SP], R1
  mov R1, 400
  cif R1
  mov [SP+1], R1
  call __function_set_drawing_scale
  mov R1, 0
  mov [SP], R1
  mov R1, 0
  mov [SP+1], R1
  call __function_draw_region_zoomed_at
__if_1104_start:
  mov R0, [global_ha]
  igt R0, 35
  jf R0, __if_1104_end
  mov R1, 266
  mov [SP], R1
  call __function_select_region
  mov R1, 320
  mov [SP], R1
  mov R1, [global_ever]
  iadd R1, 180
  mov [SP+1], R1
  call __function_draw_region_at
__if_1104_end:
__if_1121_start:
  mov R0, [global_ha]
  igt R0, 45
  jf R0, __if_1121_end
  mov R1, 257
  mov [SP], R1
  call __function_select_region
  mov R1, 320
  mov [SP], R1
  mov R1, [global_ever]
  iadd R1, 180
  mov [SP+1], R1
  call __function_draw_region_at
__if_1121_end:
__if_1138_start:
  mov R0, [global_ha]
  igt R0, 55
  jf R0, __if_1138_end
  mov R1, 258
  mov [SP], R1
  call __function_select_region
  mov R1, 320
  mov [SP], R1
  mov R1, [global_ever]
  cif R1
  fadd R1, 240.000000
  cfi R1
  mov [SP+1], R1
  call __function_draw_region_at
__if_1138_end:
__if_1155_start:
  mov R0, [global_ha]
  igt R0, 230
  jf R0, __if_1155_end
__if_1160_start:
  call __function_cartridge_connected
  jf R0, __if_1160_else
  call __function_run_cartridge
  jmp __if_1160_end
__if_1160_else:
  call __function_request_cartridge
__if_1160_end:
__if_1155_end:
  call __function_end_frame
  jmp __while_983_start
__while_983_end:
__function_magik_return:
  mov SP, BP
  pop BP
  ret

__function_main:
  push BP
  mov BP, SP
  isub SP, 10
  mov R1, -1
  mov [SP], R1
  call __function_select_texture
  mov R1, 0
  mov [SP], R1
  mov R1, 1
  mov [SP+1], R1
  mov R1, 22
  mov [SP+2], R1
  mov R1, 10
  mov [SP+3], R1
  mov R1, 41
  mov [SP+4], R1
  mov R1, 1
  mov [SP+5], R1
  mov R1, 22
  mov [SP+6], R1
  mov R1, 32
  mov [SP+7], R1
  mov R1, 8
  mov [SP+8], R1
  mov R1, 0
  mov [SP+9], R1
  call __function_define_region_matrix
  mov R1, 256
  mov [SP], R1
  call __function_select_region
  mov R1, 316
  mov [SP], R1
  mov R1, 183
  mov [SP+1], R1
  mov R1, 316
  mov [SP+2], R1
  mov R1, 183
  mov [SP+3], R1
  call __function_define_region_topleft
  mov R1, 266
  mov [SP], R1
  call __function_select_region
  mov R1, 1
  mov [SP], R1
  mov R1, 183
  mov [SP+1], R1
  mov R1, 278
  mov [SP+2], R1
  mov R1, 238
  mov [SP+3], R1
  mov R1, 140
  mov [SP+4], R1
  mov R1, 238
  mov [SP+5], R1
  call __function_define_region
  mov R1, 257
  mov [SP], R1
  call __function_select_region
  mov R1, 1
  mov [SP], R1
  mov R1, 240
  mov [SP+1], R1
  mov R1, 278
  mov [SP+2], R1
  mov R1, 247
  mov [SP+3], R1
  mov R1, 140
  mov [SP+4], R1
  mov R1, 232
  mov [SP+5], R1
  call __function_define_region
  mov R1, 258
  mov [SP], R1
  call __function_select_region
  mov R1, 1
  mov [SP], R1
  mov R1, 1
  mov [SP+1], R1
  mov R1, 440
  mov [SP+2], R1
  mov R1, 20
  mov [SP+3], R1
  mov R1, 221
  mov [SP+4], R1
  mov R1, 20
  mov [SP+5], R1
  call __function_define_region
  mov R1, 259
  mov [SP], R1
  call __function_select_region
  mov R1, 322
  mov [SP], R1
  mov R1, 24
  mov [SP+1], R1
  mov R1, 322
  mov [SP+2], R1
  mov R1, 181
  mov [SP+3], R1
  call __function_define_region_topleft
  mov R1, 261
  mov [SP], R1
  call __function_select_region
  mov R1, 324
  mov [SP], R1
  mov R1, 22
  mov [SP+1], R1
  mov R1, 324
  mov [SP+2], R1
  mov R1, 27
  mov [SP+3], R1
  call __function_define_region_topleft
  mov R1, 260
  mov [SP], R1
  call __function_select_region
  mov R1, 322
  mov [SP], R1
  mov R1, 22
  mov [SP+1], R1
  mov R1, 322
  mov [SP+2], R1
  mov R1, 22
  mov [SP+3], R1
  call __function_define_region_topleft
  mov R1, 262
  mov [SP], R1
  call __function_select_region
  mov R1, 324
  mov [SP], R1
  mov R1, 29
  mov [SP+1], R1
  mov R1, 324
  mov [SP+2], R1
  mov R1, 186
  mov [SP+3], R1
  call __function_define_region_topleft
  mov R1, 263
  mov [SP], R1
  call __function_select_region
  mov R1, 1
  mov [SP], R1
  mov R1, 249
  mov [SP+1], R1
  mov R1, 225
  mov [SP+2], R1
  mov R1, 267
  mov [SP+3], R1
  call __function_define_region_center
  mov R1, 264
  mov [SP], R1
  call __function_select_region
  mov R1, 1
  mov [SP], R1
  mov R1, 269
  mov [SP+1], R1
  mov R1, 197
  mov [SP+2], R1
  mov R1, 283
  mov [SP+3], R1
  call __function_define_region_center
  mov R1, 265
  mov [SP], R1
  call __function_select_region
  mov R1, 280
  mov [SP], R1
  mov R1, 183
  mov [SP+1], R1
  mov R1, 314
  mov [SP+2], R1
  mov R1, 209
  mov [SP+3], R1
  call __function_define_region_center
  call __function_magik
__function_main_return:
  mov SP, BP
  pop BP
  ret

__literal_string_863:
  string "memory read error"
__literal_string_872:
  string "memory write error"
__literal_string_881:
  string "port read error"
__literal_string_890:
  string "port read error"
__literal_string_899:
  string "stoverflow error"
__literal_string_908:
  string "stunderflow error"
__literal_string_917:
  string "div error"
__literal_string_926:
  string "arc consine error"
__literal_string_935:
  string "arc tan 2 error"
__literal_string_944:
  string "logar error"
__literal_string_953:
  string "power error"
__literal_string_958:
  string "wtfff with that error"
