#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <cstring>
#include <cstdlib>

int MaxCharWidth = 0;
int MaxCharHeight = 0;
int CharWidths[8][16];
void findMaxFontSizes(TTF_Font* font)
{
	char test[2];
	test[1] = 0;
	MaxCharHeight = TTF_FontHeight(font);
	for (int y = 0; y < 8; y++)
		for(int x = 0; x < 16; x++)
		{
			switch(y*16 +x)
			{
				case 1:
					test[0] = 'M';
					break;
				case 3:
					test[0] = 'W';
					break;
				case 5:
					test[0] = 'I';
					break;
				default:
					test[0] = y*16 +x;
					break;
			}
			
			TTF_SizeText(font, test, &CharWidths[y][x], NULL);
			if(CharWidths[y][x] > MaxCharWidth)
				MaxCharWidth = CharWidths[y][x]; 
		}
}

char *gnu_basename(char *path)
{
	char *base = strrchr(path, '\\');
    if (base)
		return base+1;
	else
	{
		char *base = strrchr(path, '/');
    	return base ? base+1 : path;
	}
}

void sanitize(char *fontName)
{
	char bad[8] = "-$ +*,.";
	for (size_t i = 0; i < strlen(bad); i++)
	{
		char* tmp = strchr(fontName, bad[i]);
		while(tmp)
		{
			*tmp = '_';
			tmp = strchr(fontName, bad[i]);
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("use %s <path/to/font.ttf> <fontsize>\n", gnu_basename(argv[0]));
		return 1;
	}
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		 if( IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG)
		 {
			if( TTF_Init() == 0)
			{
				Uint32 rmask, gmask, bmask, amask;
				#if SDL_BYTEORDER == SDL_BIG_ENDIAN
					rmask = 0xff000000;
					gmask = 0x00ff0000;
					bmask = 0x0000ff00;
					amask = 0x000000ff;
				#else
					rmask = 0x000000ff;
					gmask = 0x0000ff00;
					bmask = 0x00ff0000;
					amask = 0xff000000;
				#endif
				SDL_Surface *RendererSurface = SDL_CreateRGBSurface(0,2048,2048, 32, rmask, gmask, bmask, amask);
				SDL_Renderer* Renderer = SDL_CreateSoftwareRenderer(RendererSurface);
				if (Renderer)
				{
					SDL_RendererInfo rendererInfo;
					SDL_GetRendererInfo(Renderer, &rendererInfo);
					SDL_Log("Using Renderer:%s\n", rendererInfo.name);

					int FontSize = atoi(argv[2]);
					
					TTF_Font* Font = TTF_OpenFont(argv[1], FontSize);
					if(Font)
					{
						findMaxFontSizes(Font);		

						SDL_Surface* TextSurface = SDL_CreateRGBSurface(0, MaxCharWidth * 16, MaxCharHeight * 8, 32, rmask, gmask, bmask, amask);
						SDL_Renderer* TextRenderer = SDL_CreateSoftwareRenderer(TextSurface);
						SDL_SetRenderDrawColor(TextRenderer, 0, 0, 0, 0);
						SDL_RenderClear(TextRenderer);
				
						char FontName[1000];
						char* base = gnu_basename(argv[1]);
						strcpy(FontName, base);
						char* ext = strrchr(FontName,'.');
						if(ext)
							*ext = 0;
						strcat(FontName, "_");
						strcat(FontName, argv[2]);
						
						sanitize(FontName);

						char Code[20000];
						char Nr[20];
						char Char[2];
						Char[1] = 0;
						strcpy(Code, "#ifndef ");
						strcat(Code, FontName);
						strcat(Code, "_H\n");
						strcat(Code, "#define ");
						strcat(Code, FontName);
						strcat(Code, "_H\n\n");

						strcat(Code, "#include \"video.h\"\n");
						strcat(Code, "#include \"libs/TextFonts/textfont.h\"\n\n");
						strcat(Code, "#define ");
						strcat(Code, FontName);
						strcat(Code, "_texture_id 0\n");
						strcat(Code, "#define ");
						strcat(Code, FontName);
						strcat(Code, "_region_id 0\n\n");
						strcat(Code, "textfont Font");
						strcat(Code, FontName);
						strcat(Code, ";\n\n");
						strcat(Code, "void setupFont");
						strcat(Code, FontName);
						strcat(Code, "()\n{\n");
						strcat(Code, "select_texture(");
						strcat(Code, FontName);
						strcat(Code, "_texture_id);\n");
    					//strcat(Code, "define_region_matrix(0,  0,0,  ");
						//sprintf(Nr,"%d",MaxCharWidth-1);
						//strcat(Code, Nr);
						//strcat(Code, ",");
						//sprintf(Nr,"%d",MaxCharHeight-1);
						//strcat(Code, Nr);
						//strcat(Code, ",  0,");
						//strcat(Code, Nr);
						//strcat(Code, ",  16,8,  0);\n");

						for (int y = 0; y < 8; y++)
							for(int x = 0; x < 16; x++)
							{								
								switch(y*16 +x)
								{
									case 1:
										Char[0] = 'M';
										break;
									case 3:
										Char[0] = 'W';
										break;
									case 5:
										Char[0] = 'I';	
										break;
									default:
										Char[0] = y*16 +x;
										break;
								}
							    // then we redefine some characters to have different widths
							    // (note that, for this font, upper and lowercase letters are the same)
    							strcat(Code, "select_region(");
								strcat(Code, FontName);
								strcat(Code, "_region_id + ");
								sprintf(Nr,"%d", y*16 + x);
								strcat(Code, Nr);
								strcat(Code, ");");
								strcat(Code, " //");
								if((y*16 +x >= 32) && (y*16 +x < 127) && (y*16 +x != 92))
								{
									strcat(Code, Char);
								}
								strcat(Code, " ");
								sprintf(Nr,"%d",CharWidths[y][x]);
								strcat(Code, Nr);
								strcat(Code, "\n");
    							strcat(Code, "define_region(");
								sprintf(Nr,"%d",x * MaxCharWidth);
								strcat(Code,  Nr);
								strcat(Code, ",");
								sprintf(Nr,"%d",y * MaxCharHeight);
								strcat(Code,  Nr);
								strcat(Code, ",  ");
								sprintf(Nr,"%d",(x * MaxCharWidth) + CharWidths[y][x]-1);
								strcat(Code, Nr);
								strcat(Code, ",");
								sprintf(Nr,"%d",((y+1) * MaxCharHeight)-1);	
								strcat(Code,  Nr);
								strcat(Code, ",  ");
								sprintf(Nr,"%d",x * MaxCharWidth);
								strcat(Code,  Nr);
								strcat(Code, ",");
								sprintf(Nr,"%d",y * MaxCharHeight);
								strcat(Code,  Nr);
								strcat(Code, ");\n");
								
								SDL_Color white = {255, 255, 255, 255};
								SDL_Surface* Tmp = TTF_RenderText_Blended(Font, Char, white);
								if(Tmp)
								{
									SDL_Texture* TmpTexture = SDL_CreateTextureFromSurface(TextRenderer, Tmp);
									SDL_Rect rect; 
									rect.x = x * MaxCharWidth;  
									rect.y = y * MaxCharHeight;
									rect.w = Tmp->w;
									rect.h = Tmp->h;
									SDL_RenderCopy(TextRenderer, TmpTexture, NULL, &rect);
									SDL_DestroyTexture(TmpTexture);
									SDL_FreeSurface(Tmp);
								}
							}
						
						char FontVar[1000];
						strcpy(FontVar, "Font");
						strcat(FontVar, FontName);
						strcat(Code,"\n");
						strcat(Code, FontVar);
						strcat(Code, ".character_height = ");
						sprintf(Nr,"%d",MaxCharHeight);
						strcat(Code, Nr);
						strcat(Code, ";\n");

						strcat(Code, FontVar);
						strcat(Code, ".use_variable_width = true;\n");
						
						strcat(Code, FontVar);
						strcat(Code, ".character_separation = 0;\n");
						strcat(Code, FontVar);
						strcat(Code, ".line_separation = 0;\n\n");

						strcat(Code, FontVar);
						strcat(Code, ".texture_id = ");
						strcat(Code, FontName);
						strcat(Code, "_texture_id;\n");

						strcat(Code, FontVar);
						strcat(Code, ".character_zero_region_id = ");
						strcat(Code, FontName);
						strcat(Code, "_region_id;\n");

						strcat(Code,"textfont_read_region_widths(&");
						strcat(Code, FontVar);
						strcat(Code, ");\n\n");

						strcat(Code, "}\n");
						strcat(Code, "#endif\n");
						
						char FileNamePng[1000];
						strcpy(FileNamePng, FontName);
						strcat(FileNamePng, ".png");
						IMG_SavePNG(TextSurface, FileNamePng);
						SDL_DestroyRenderer(TextRenderer);
						SDL_FreeSurface(TextSurface);
						SDL_DestroyRenderer(Renderer);
						SDL_FreeSurface(RendererSurface);
						
						char FileNameHeader[1000];
						strcpy(FileNameHeader, FontName);
						strcat(FileNameHeader, ".h");
						FILE *Fp = fopen(FileNameHeader, "w+");
						if(Fp)
						{
							fwrite(Code, sizeof(char), strlen(Code), Fp);
							fclose(Fp);
						}
						SDL_Log("Created Font with size per char: %dx%d", MaxCharWidth, MaxCharHeight);
					}
					else
					{
						SDL_Log("failed opening font '%s': %s", argv[1], SDL_GetError());
					}
					
				}
				else
				{
					SDL_Log("Failed to create renderer: %s\n", SDL_GetError());
				}
				TTF_Quit();	
			}
			else
			{
				SDL_Log("Failed to initialise SDL_TTF: %s\n", SDL_GetError());
			}
			IMG_Quit();	
		}
		else
		{
			SDL_Log("Failed to initialise SDL_Image: %s\n", SDL_GetError());
		}
		SDL_Quit();
	}
	else
		SDL_Log("Failed to initialise SDL: %s\n", SDL_GetError());
	return 1;
}