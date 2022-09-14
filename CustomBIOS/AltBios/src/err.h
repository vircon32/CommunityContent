#ifndef ERR_H
#define ERR_H
// ---------------------------------------------------------
//     HARDWARE ERROR CODES
// ---------------------------------------------------------


#define error_memory_read       0
#define error_memory_write      1
#define error_port_read         2
#define error_port_write        3
#define error_stack_overflow    4
#define error_stack_underflow   5
#define error_division          6
#define error_arc_cosine        7
#define error_arc_tangent_2     8
#define error_logarithm         9
#define error_power            10
#define error_unknown          11

void request_cartridge()
{
	int[64] bltx; //dots x
	int[64] blty; //dots y
	int bstart=0;
	
	int ha;
	while(true){
		ha++;
		clear_screen(make_color_rgb(4,0,1));
		
		if (ha>75){
		
		//cloning the particles function	
			for(int i=0;i<64;i++){
			
				if(bstart<64){
				
					blty[i]=rand_betw(0,360);
					bltx[i]=rand_betw(0,640);
					bstart+=1;
				}
			
				if(blty[i]>360){
				
					bltx[i]=rand_betw(1,640);
					blty[i]=-7;
				}

				blty[i]+=7;
				select_region(region_blt);
			
				set_drawing_scale(3,2);
				draw_region_zoomed_at(bltx[i], blty[i] );
			}
			
			select_region(region_grad_alt);
			set_drawing_scale(700,2);
			draw_region_zoomed_at(0,0);
		
			select_region(region_cart);		//draw cart image
			draw_region_at(640/2, 340/2);

			select_region(region_cart_plz);		//draw cart please
			draw_region_at(640/2, 340/2-50);

			select_region(region_cart_rez);		//please reset
			draw_region_at(640/2, 340/2+50);

		}

    end_frame();
	}
}

// ---------------------------------------------------------
//     ERROR HANDLER FUNCTION
// ---------------------------------------------------------


void error_handler()
{
    // do not initialize these!
    // or else R0 will be overwritten
 	
	int error_code;
    int instruction_pointer;
    int instruction;
    int immediate_value;
    
    // save registers to variables
    asm
    {
        "mov {error_code}, R0"
        "mov {instruction_pointer}, R1"
        "mov {instruction}, R2"
        "mov {immediate_value}, R3"
    }
	end_frame();
	
    if( error_code == error_memory_read )
    {
	print_at(10,10,"memory read error");
    }
    
    else if( error_code == error_memory_write )
    {
	print_at(10,10,"memory write error");
    }
    
    else if( error_code == error_port_read )
    {
	print_at(10,10,"port read error");
    }
    
    else if( error_code == error_port_write )
    {
	print_at(10,10,"port read error");
    }
    
    else if( error_code == error_stack_overflow )
    {
	print_at(10,10,"stoverflow error");
    }
    
    else if( error_code == error_stack_underflow )
    {
	print_at(10,10,"stunderflow error");
    }
    
    else if( error_code == error_division )
    {
	print_at(10,10,"div error");
    }
    
    else if( error_code == error_arc_cosine )
    {
 	print_at(10,10,"arc consine error");
    }
    
    else if( error_code == error_arc_tangent_2 )
    {
	print_at(10,10,"arc tan 2 error");
    }
    
    else if( error_code == error_logarithm )
    {
	print_at(10,10,"logar error");
    }
    
    else if( error_code == error_power )
    {
	print_at(10,10,"power error");
    }
    else
    {
	print_at(10,10,"wtfff with that error");
    }

    // stop any sound
    stop_all_channels();
}

#endif