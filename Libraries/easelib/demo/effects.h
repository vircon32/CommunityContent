
void effect_offset(float t){

	draw_region_at( 100+t*20, 100 );

}


void effect_simple_ease(float t){

	draw_region_at( 100 + ease(t, SINE, SINE)*300, 100 );

}


void effect_different_ease(float t){

	draw_region_at( 100 + ease(t, QUINT, BACK)*300, 100 );

}


void effect_two_axis_ease(float t){

	draw_region_at( 100 + ease(t, BACK, BACK)*300, 100 + ease(t, SINE, SINE)*100 );

}


void effect_time_offset(float t){

	draw_region_at( 100 + ease(t-1, QUINT, QUINT)*300, 100 );

}

void effect_follow_by_offset(float t){

	draw_region_at( 100 + ease(t, QUINT, QUINT)*300, 60 );
	draw_region_at( 100 + ease(t-0.2, QUINT, QUINT)*300, 110 );
	draw_region_at( 100 + ease(t-0.4, QUINT, QUINT)*300, 160 );
	draw_region_at( 100 + ease(t-0.6, QUINT, QUINT)*300, 210 );

}

void effect_only_one_offset(float t){

	draw_region_at( 100, 100 + ease(t, QUINT, BACK)*50 - ease(t-1.2, BACK, QUINT)*50 );
	draw_region_at( 150, 100 + ease(t-1.2, QUINT, BACK)*50 - ease(t-2.4, BACK, QUINT)*50 );
	draw_region_at( 200, 100 + ease(t-2.4, QUINT, BACK)*50 - ease(t-3.6, BACK, QUINT)*50 );
	draw_region_at( 250, 100 + ease(t-3.6, QUINT, BACK)*50 - ease(t-4.8, BACK, QUINT)*50 );

}


void effect_concatenate(float t){
	draw_region_at( 100 + ease(t, QUINT, BACK)*100 + ease(t-1.5, SINE, SINE)*100 + ease(t-3, BACK, BACK)*100, 100 );

}


void effect_scale(float t){
	set_drawing_scale( ease(t,CIRC,BACK), ease(t,CIRC,BACK) );
	draw_region_zoomed_at( 200, 200 );

}

void effect_rotation(float t){
	set_drawing_angle( ease(t,CIRC,BACK));
	draw_region_rotated_at( 200, 200 );

}

void effect_rotozoomed(float t){

	set_drawing_scale( ease(t,CIRC,BACK), ease(t,CIRC,BACK) );
	set_drawing_angle( ease(t,BACK,BACK)*6.28319);
	draw_region_rotozoomed_at( 200, 200 );

}


void effect_none(float t){
		draw_region_at( 100 + ease(t, NONE, CUBIC)*300, 100 );

}


void effect_dual_none(float t){
	draw_region_at( 100 + ease(t, NONE, NONE)*300, 100 );

}


void effect_speed(float t){
	draw_region_at( 100 + ease(t/2, SINE, SINE)*300, 100 );

}


void effect_multiple_speed(float t){
	draw_region_at( 100 + ease(t/2, QUINT, QUINT)*300, 60 );
	draw_region_at( 100 + ease(t, QUINT, QUINT)*300, 110 );
	draw_region_at( 100 + ease(t*2, QUINT, QUINT)*300, 160 );
	draw_region_at( 100 + ease(t*3, QUINT, QUINT)*300, 210 );

}

void effect_repeat(float t){

	draw_region_at( 100 + ease( (asin(cos(t*2+pi))+1.5707963)/pi, QUINT, QUINT)*300, 100);
}
