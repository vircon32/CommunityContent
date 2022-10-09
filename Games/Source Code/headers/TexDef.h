#define TexPlayer 0
#define TexFish 1
#define TexBackg 2
#define TexLives 3
#define Sfont 4
#define TexVig 5
#define TexDefeat 6
#define TexTurtle 7
#define TexTinyFuskingFish 8
#define TexShark 9
#define TexIntro 10
#define TexMem 11


#define FRegPlayer 0
#define FRegFish 0
#define FRegLives 0
#define FRegSfont 0
#define FRegTurtle 0
// no Freg to sharks


#define RegDead 0
#define RegNew 1
#define RegS 2

#define SndBgs 0
#define SndBubbles 1
#define SndHit 2
#define SndShark 3
#define SndIntro 4


void TexDefine(){
		
	select_texture(TexPlayer);
	define_region_matrix(FRegPlayer, 1,1, 69,111, 34,20, 6,2, 1);
	select_region(13);
	define_region_topleft(1,1,2,2);

	select_texture(TexFish);
	define_region_matrix(FRegFish,1,1,118,38,1,1,3,1,1);

	select_texture(TexBackg);
	select_region(0);
	define_region_topleft(0,0,640,360);

	select_texture(TexLives);
	define_region_matrix(FRegLives,1,1,63,37,1,1,1,3,0);
	
	select_texture(Sfont);
	define_region_matrix(FRegSfont,1,1,20,28,1,1,10,1,1);
	
	select_texture(TexVig);
	select_region(0);
	define_region_topleft(0,0,640,360);
	
		select_region(1);
	define_region_topleft(0,0,1,1);
	
	
		select_texture(TexDefeat);
	select_region(RegDead);
	define_region_center(8,0,430,224);
	
		select_region(RegNew);
	define_region_topleft(1,240,68,260);

		select_region(RegS);
	define_region_center(274,233,432,267);
	
		select_texture(TexTurtle);
	define_region_matrix(FRegTurtle,1,1,181,76,1,1,2,2,1);
	
	select_texture(TexTinyFuskingFish);
	select_region(0);
	define_region_topleft(1,1,52,29);
	
			select_texture(TexShark);
	define_region_matrix(0 ,1,1,258,86,1,1,3,2,1);
	
		select_texture(TexIntro);
	select_region(0);
	define_region_center(0,0,341,94);
	
	select_region(1);
	define_region_center(0,96,98,256);
	
	select_region(2);
	define_region_center(100,96,268,119);

	
		select_texture(TexMem);
	select_region(0);
	define_region_center(0,0,389,36);

	select_region(1);
	define_region(0,38,106,117,0,57);
	
	select_region(2);
	define_region_center(0,119,556,141);

}