
float dist=0;

void bg(int sep, int reg){
	
	dist+=0.05;
	
	select_texture(maintex);
	select_region(reg);

	set_drawing_angle(sin(dist*0.9)*0.4);


	for(int x=0; x<18; x++){

		for(int y=0; y<18; y++){

			set_multiply_color(make_color_rgba(x*x, 14, y*y, (y*y)+20 ));
			
			draw_region_rotated_at(((x*sep/10)+sin(dist/2)*10) , ((y*sep/10)+cos(dist/2)*10) );

		}



	}


}