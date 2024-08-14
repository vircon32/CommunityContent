#ifndef CSPRITES_H
#define CSPRITES_H

#include "string.h"
#include "libs/DrawPrimitives/draw_primitives.h"
#include "CImage.h"
#include "Vec2F.h"
#include "Common.h"
#include "SDL_HelperTypes.h"

#define TIMSORTRUN 128

enum ECollisionShape
{
	SHAPE_BOX,
	SHAPE_TRIANGLE,
	SHAPE_CIRCLE
};

struct CSprite {
		Texture *Img;
		int animInc;
		int animTimer;
		int index;
		int* imageID;
		float x;
		float y;
		float prevxscale;
		float prevyscale;
		float sxscale;
		float syscale;
		float xspeed;
		float yspeed;
		float xscale_speed;
		float yscale_speed;
		float rotation;
		int tileSizeX;
		int tileSizeY;
		int tilesX;
		int tilesY;
		int animTile;
		int animStartTile;
		int animEndTile;
		int animSpeed;
		ECollisionShape collisionShape;
		float collisionAngle;
		float collisionWidth;
		float collisionHeight;
		float collisionxoffset;
		float collisionyoffset;
		int depth;
		bool show;
		float r;
		float g;
		float b;
		float a;
		float rotation_speed;
		bool show_collision_shape;		
};


CSprite** CSprites_Sprites = NULL;
int CSprites_UpdateImageResets;
int CSprites_SpritesDrawn;
int CSprites_SpriteSlotsUsed = 0;
int CSprites_MaxSpriteSlotsUsed = 0;
bool CSprites_ForceShowCollisionShape;
bool CSprites_needSpriteSorting;
bool CSprites_notEnoughSpots = false;
int CSprites_spriteMax = 0;

void CSprites_SpritesDrawnReset()
{
	CSprites_SpritesDrawn = 0;
}


void CSprites_Init()
{
	CSprites_UpdateImageResets = 0;
	CSprites_SpriteSlotsUsed = 0;
	CSprites_ForceShowCollisionShape = false;
	CSprites_needSpriteSorting = false;
	CSprites_notEnoughSpots = false;
	CSprites_SpritesDrawnReset();
}


void CSprites_SetForceShowCollisionShape(bool val)
{
	CSprites_ForceShowCollisionShape = val;
}

int CSprites_UpdateImageResetsCount()
{
	return  CSprites_UpdateImageResets;
}


CSprite* CSprites_CreateSprite()
{
	for (int i= 0; i < CSprites_spriteMax; i++)
	{
		if(CSprites_Sprites[i] == NULL)
		{
			CSprites_SpriteSlotsUsed++;
			if(CSprites_MaxSpriteSlotsUsed < CSprites_SpriteSlotsUsed)
				CSprites_MaxSpriteSlotsUsed = CSprites_SpriteSlotsUsed;
			CSprite* Spr = (CSprite*) malloc(sizeof(CSprite));
			Spr->index = i;
			Spr->animInc = 0;
			Spr->animTimer = 0;
			Spr->rotation = 0;
			Spr->imageID = NULL;
			Spr->sxscale = 1;
			Spr->syscale = 1;
			Spr->prevxscale = -1;
			Spr->prevyscale = -1;
			Spr->xscale_speed = 0;
			Spr->yscale_speed = 0;
			Spr->xspeed = 0;
			Spr->yspeed = 0;
			Spr->tileSizeX = 0;
			Spr->tileSizeY = 0;
			Spr->animStartTile = 0;
			Spr->animEndTile = 0;
			Spr->animSpeed = 0;
			Spr->animTile = 0;
			Spr->collisionShape = SHAPE_BOX;
			Spr->collisionAngle = 0;
			Spr->collisionWidth = 0;
			Spr->collisionHeight = 0;
			Spr->collisionxoffset = 0;
			Spr->collisionyoffset = 0;
			Spr->depth = 0;
			Spr->show = true;
			Spr->r = 1.0;
			Spr->g = 1.0;
			Spr->b = 1.0;
			Spr->a = 1.0;
			Spr->tilesX = 1;
			Spr->tilesY = 1;
			Spr->rotation_speed = 0.0;
			Spr->Img = NULL;
			Spr->x = 0.0;
			Spr->y = 0.0;
			Spr->show_collision_shape = false;
			CSprites_Sprites[i] = Spr;

			return Spr;
		}
	}
	CSprites_notEnoughSpots = true;
	return NULL;
}




// Function to merge two subarrays
void CSprites_merge(CSprite** array, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    CSprite** leftArray = (CSprite**)malloc(n1 * sizeof(CSprite*));
    CSprite** rightArray = (CSprite**)malloc(n2 * sizeof(CSprite*));

    // Copy data to temporary arrays leftArray[] and rightArray[]
    for (int i = 0; i < n1; i++)
        leftArray[i] = array[left + i];
    for (int j = 0; j < n2; j++)
        rightArray[j] = array[mid + 1 + j];

    // Merge the temporary arrays back into array[left..right]

    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = left; // Initial index of merged subarray

    while (i < n1 && j < n2) {
        int leftDepth;
		if(leftArray[i] == NULL) 
			leftDepth = CSprites_spriteMax;
		else
		  leftDepth = leftArray[i]->depth;
        int rightDepth;
		if (rightArray[j] == NULL) 
			rightDepth =  CSprites_spriteMax; 
		else
			rightDepth = rightArray[j]->depth;

        if (leftDepth <= rightDepth) {
            array[k] = leftArray[i];
            if (array[k]) array[k]->index = k;
            i++;
        } else {
            array[k] = rightArray[j];
            if (array[k]) array[k]->index = k;
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftArray[], if there are any
    while (i < n1) {
        array[k] = leftArray[i];
        if (array[k]) array[k]->index = k;
        i++;
        k++;
    }

    // Copy the remaining elements of rightArray[], if there are any
    while (j < n2) {
        array[k] = rightArray[j];
        if (array[k]) array[k]->index = k;
        j++;
        k++;
    }

    // Free the temporary arrays
    free(leftArray);
    free(rightArray);
}

// Function to implement merge sort
void CSprites_mergeSort(CSprite** array, int left, int right) {
    if (left < right) {
        // Find the middle point
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        CSprites_mergeSort(array, left, mid);
        CSprites_mergeSort(array, mid + 1, right);

        // Merge the sorted halves
        CSprites_merge(array, left, mid, right);
    }
}


// Utility function to perform insertion sort on the array
void insertionSort(CSprite** array, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        CSprite* temp = array[i];
        int depth;
        if (temp == NULL) {
            depth = INT_MAX;
        } else {
            depth = temp->depth;
        }

        int j = i - 1;

        while (j >= left) {
            int currentDepth;
            if (array[j] == NULL) {
                currentDepth = INT_MAX;
            } else {
                currentDepth = array[j]->depth;
            }

            if (currentDepth <= depth) {
                break;
            }

            array[j + 1] = array[j];
            if (array[j + 1] != NULL) {
                array[j + 1]->index = j + 1;
            }

            j--;
        }

        array[j + 1] = temp;
        if (array[j + 1] != NULL) {
            array[j + 1]->index = j + 1;
        }
    }
}

// Merge function merges the sorted runs
void merge(CSprite** array, int l, int m, int r) {
    int len1 = m - l + 1, len2 = r - m;
    CSprite** left = (CSprite**)malloc(len1 * sizeof(CSprite*));
    CSprite** right = (CSprite**)malloc(len2 * sizeof(CSprite*));

    for (int i = 0; i < len1; i++) {
        left[i] = array[l + i];
    }
    for (int i = 0; i < len2; i++) {
        right[i] = array[m + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = l;

    while (i < len1 && j < len2) {
        int leftDepth;
        if (left[i] == NULL) {
            leftDepth = INT_MAX;
        } else {
            leftDepth = left[i]->depth;
        }

        int rightDepth;
        if (right[j] == NULL) {
            rightDepth = INT_MAX;
        } else {
            rightDepth = right[j]->depth;
        }

        if (leftDepth <= rightDepth) {
            array[k] = left[i];
            if (array[k] != NULL) {
                array[k]->index = k;
            }
            i++;
        } else {
            array[k] = right[j];
            if (array[k] != NULL) {
                array[k]->index = k;
            }
            j++;
        }
        k++;
    }

    while (i < len1) {
        array[k] = left[i];
        if (array[k] != NULL) {
            array[k]->index = k;
        }
        i++;
        k++;
    }

    while (j < len2) {
        array[k] = right[j];
        if (array[k] != NULL) {
            array[k]->index = k;
        }
        j++;
        k++;
    }

    free(left);
    free(right);
}

// Iterative Timsort function to sort the array[0...n-1]
void timSort(CSprite** array, int n) {
    // Sort individual subarrays of size TIMSORTRUN
    for (int i = 0; i < n; i += TIMSORTRUN) {
        int right;
		if (i + TIMSORTRUN - 1 < n - 1) 
			right = (i + TIMSORTRUN - 1);
		else
			right = (n - 1);
        insertionSort(array, i, right);
    }

    // Start merging from size TIMSORTRUN (or 32). It will merge to form size 64, 128, 256 and so on...
    for (int size = TIMSORTRUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right;
			if (left + 2 * size - 1 < n - 1) 
				right = (left + 2 * size - 1); 
			else
				right = (n - 1);

            // Merge subarray array[left...mid] and array[mid+1...right]
            if (mid < right) {
                merge(array, left, mid, right);
            }
        }
    }
}


void CSprites_SortSprites()
{
	if (CSprites_needSpriteSorting)
	{
		timSort(CSprites_Sprites, CSprites_spriteMax - 1);
		CSprites_needSpriteSorting = false;
	}

}

void CSprites_UpdateSprites()
{
	CSprites_SortSprites();
	for (int i = 0; i < CSprites_spriteMax; i++)
	{
		if (CSprites_Sprites[i] == NULL)
			continue;

		if (CSprites_Sprites[i]->animSpeed != 0)
		{
			if (getCurrentTimeMilliseconds() > CSprites_Sprites[i]->animTimer)
			{
				CSprites_Sprites[i]->animTile += CSprites_Sprites[i]->animInc;
				if (CSprites_Sprites[i]->animInc > 0)
				{
					if(CSprites_Sprites[i]->animTile > CSprites_Sprites[i]->animEndTile)
						CSprites_Sprites[i]->animTile = CSprites_Sprites[i]->animStartTile;
				}
				else
				{
					if (CSprites_Sprites[i]->animInc < 0)
					{
						if(CSprites_Sprites[i]->animTile < CSprites_Sprites[i]->animEndTile)
							CSprites_Sprites[i]->animTile = CSprites_Sprites[i]->animStartTile;
					}
				}
				CSprites_Sprites[i]->animTimer = getCurrentTimeMilliseconds() + (int)floor(1000 / CSprites_Sprites[i]->animSpeed);
			}
		}

		CSprites_Sprites[i]->x += CSprites_Sprites[i]->xspeed;
		CSprites_Sprites[i]->y += CSprites_Sprites[i]->yspeed;
		CSprites_Sprites[i]->sxscale += CSprites_Sprites[i]->xscale_speed;
		CSprites_Sprites[i]->syscale += CSprites_Sprites[i]->yscale_speed;
		CSprites_Sprites[i]->rotation += CSprites_Sprites[i]->rotation_speed;
		CSprites_Sprites[i]->collisionAngle += CSprites_Sprites[i]->rotation_speed;
		CSprites_Sprites[i]->collisionWidth += CSprites_Sprites[i]->xscale_speed;
		CSprites_Sprites[i]->collisionHeight += CSprites_Sprites[i]->yscale_speed;
	}
}


void CSprites_DrawSprite(CSprite* Spr)
{
	if (Spr == NULL)
		return;
	
	CSprites_SortSprites();

	if (Spr->show && ((*Spr->imageID > -1) &&  (*Spr->imageID < GFX_Max)))
	{
		CSprites_SpritesDrawn++;
		//multiply is to get the sign
		//Vec2F scale = { 1.0 * (Spr->sxscale / fabs(Spr->sxscale)), 1.0 * (Spr->syscale / fabs(Spr->syscale))};
		//Vec2F scale = { Spr->sxscale, Spr->syscale};				
		CImage_DrawImageFuzeSrcRectTintFloat(*Spr->imageID, Spr->animTile, true, Spr->x, Spr->y, Spr->rotation, Spr->sxscale, Spr->syscale, Spr->r, Spr->g, Spr->b, Spr->a);
		

		if (Spr->show_collision_shape || CSprites_ForceShowCollisionShape)
		{
			set_multiply_color(make_color_rgb(255,0,255));
			switch(Spr->collisionShape)
			{
				case SHAPE_BOX:
				{
					draw_rectangle(Spr->x + Spr->collisionxoffset - (Spr->collisionWidth * fabs(Spr->sxscale) / 2), (int)(Spr->y + Spr->collisionyoffset - (Spr->collisionHeight * fabs(Spr->syscale) / 2)), Spr->x + Spr->collisionxoffset - (Spr->collisionWidth * fabs(Spr->sxscale) / 2) + (int)(Spr->collisionWidth * fabs(Spr->sxscale)), (int)(Spr->y + Spr->collisionyoffset - (Spr->collisionHeight * fabs(Spr->syscale) / 2)) + (int)(Spr->collisionHeight * fabs(Spr->syscale)));
					break;
				}
				case SHAPE_CIRCLE:
				{
					draw_circle(Spr->x + Spr->collisionxoffset ,Spr->y + Spr->collisionyoffset,Spr->collisionWidth * fabs(Spr->sxscale) / 2);
					break;
				}
				default:
					break;
			}
			set_multiply_color(color_white);
		}
	}
}


void CSprites_DrawSprites()
{
	CSprites_SpritesDrawn = 0;
	for (int i = 0; i < CSprites_spriteMax; i++)
	{
		if (CSprites_Sprites[i] != NULL)
			CSprites_DrawSprite(CSprites_Sprites[i]);
	}
}

void CSprites_SetSpriteRotationSpeed(CSprite* Spr, float rotationSpeed)
{
	Spr->rotation_speed = rotationSpeed;
}

void CSprites_SetSpriteColour (CSprite* Spr, float red, float green, float blue, float alpha)
{
	Spr->r = red;
	Spr->g = green;
	Spr->b = blue;
	Spr->a = alpha;
}

void CSprites_SetSpriteVisibility(CSprite* Spr, bool visibility)
{
	Spr->show = visibility;
}

Vec2F *CSprites_GetSpriteLocation(CSprite* Spr)
{
	Vec2F *Result = (Vec2F*) malloc(sizeof(Vec2F));
	Result->x =  Spr->x;
	Result->y = Spr->y;
	return Result;
}

void CSprites_SetSpriteImageTiles(CSprite* Spr, int *AImageID, int TilesX, int TilesY)
{
	Spr->imageID = AImageID;
	SDL_Point* Tz = CImage_ImageSize(*AImageID);
	
	Spr->tileSizeX = (int)floor(Tz->x / TilesX);
	Spr->tileSizeY = (int)floor(Tz->y / TilesY);
	Spr->tilesX = TilesX;
	Spr->tilesY = TilesY;
	if ((Spr->collisionHeight == 0) && (Spr->collisionWidth == 0))
	{
		Spr->collisionHeight = (float)Spr->tileSizeY;
		Spr->collisionWidth = (float)Spr->tileSizeX;
	}
	free(Tz);
}

void CSprites_SetSpriteImage(CSprite* Spr, int *AImageID)
{
	CSprites_SetSpriteImageTiles(Spr, AImageID, 1, 1);
}

void CSprites_SetSpriteScale(CSprite* Spr, Vec2F* AScale)
{
	Spr->sxscale = AScale->x;
	Spr->syscale = AScale->y;
}

void CSprites_SetSpriteRotation(CSprite* Spr, float AAngle)
{
	float diffAngle = AAngle - Spr->rotation;
	Spr->collisionAngle += diffAngle;
	Spr->rotation = AAngle;
}

void CSprites_SetSpriteAnimation(CSprite* Spr, int StartTile, int EndTile, int animSpeed)
{
	Spr->animStartTile = StartTile;
	Spr->animEndTile = EndTile;
	//small optimazation so i don't have to check the code
	if (StartTile == EndTile)
		Spr->animSpeed = 0;
	else
		Spr->animSpeed = animSpeed;
	Spr->animTile = StartTile;
	if (Spr->animSpeed != 0)
	{
		Spr->animTimer = getCurrentTimeMilliseconds() + (int)floor(1000 / animSpeed);

		if(EndTile < StartTile)
			Spr->animInc = -1;
		else
		{
			if(EndTile > StartTile)
				Spr->animInc = 1;
			else
				Spr->animInc = 0;
		}
	}
}

void CSprites_SetSpriteCollisionShape(CSprite* Spr, ECollisionShape shape, float width, float height, float rotation, float xoffset, float yoffset)
{
	Spr->collisionShape = shape;
	Spr->collisionWidth = width;
	Spr->collisionHeight = height;
	Spr->collisionAngle = rotation;
	Spr->collisionxoffset = xoffset;
	Spr->collisionyoffset = yoffset;
}

void CSprites_SetSpriteLocation(CSprite* Spr, Vec2F* pos )
{
	Spr->x = pos->x;
	Spr->y = pos->y;
}

void CSprites_SetSpriteDepth(CSprite* Spr, int depth)
{
	Spr->depth = depth;
	CSprites_needSpriteSorting = true;
}

int CSprites_GetSpriteAnimFrameCount(CSprite* Spr)
{
	if (Spr->animEndTile > Spr->animStartTile)
		return Spr->animEndTile - Spr->animStartTile + 1;
	else
		return Spr->animStartTile -  Spr->animEndTile + 1;
}

int CSprites_GetSpriteAnimFrame(CSprite* Spr)
{
	if (Spr->animEndTile < Spr->animStartTile)
		return Spr->animTile - Spr->animEndTile; 
	else
		return Spr->animTile - Spr->animStartTile;
}

SDL_Point* CSprites_TileSize(CSprite* Spr)
{
	SDL_Point *Result = (SDL_Point*) malloc(sizeof(SDL_Point));
	Result->x = Spr->tileSizeX;
	Result->y = Spr->tileSizeY;
	return Result;
}

//https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-Detection#
bool CSprites_DetectRectCircleCollsion(CSprite* SprRect, CSprite* SprCircle)
{
	Vec2F center = {SprCircle->x + SprCircle->collisionxoffset /2.0, SprCircle->y + SprCircle->collisionyoffset / 2.0};
	// calculate AABB info (center, half-extents)
	Vec2F aabb_half_extents = {fabs(SprRect->collisionWidth) * fabs(SprRect->sxscale) / 2.0, fabs(SprRect->collisionHeight) * fabs(SprRect->syscale) / 2.0};
	Vec2F aabb_center = {SprRect->x + SprRect->collisionxoffset / 2.0, SprRect->y + SprRect->collisionyoffset / 2.0};

	// get difference vector between both centers
	Vec2F difference;
	difference.x = center.x - aabb_center.x;
	difference.y = center.y - aabb_center.y;
	Vec2F neg_half_extends;
	neg_half_extends.x = -aabb_half_extents.x;
	neg_half_extends.y = -aabb_half_extents.y;
	Vec2F *clamped = clampVec2F(&difference, &neg_half_extends, &aabb_half_extents);
	// add clamped value to AABB_center and we get the value of box closest to circle
	Vec2F closest;
	closest.x = aabb_center.x + clamped->x;
	closest.y = aabb_center.y + clamped->y;
	// retrieve vector between center circle and closest point AABB and check if length <= radius
	difference.x = closest.x - center.x;
	difference.y = closest.y - center.y;
	free(clamped);
	return length(&difference) < (fabs(SprCircle->collisionWidth) * fabs(SprCircle->sxscale) / 2.0);
}

bool CSprites_DetectRectRectCollsion(CSprite* Spr, CSprite* SprOther)
{
	float widthA = (fabs(Spr->collisionWidth) * fabs(Spr->sxscale));
	float heightA = (fabs(Spr->collisionHeight) * fabs(Spr->syscale));
	float minAx = Spr->x + Spr->collisionxoffset - (fabs(Spr->collisionWidth) * fabs(Spr->sxscale) / 2);
	float minAy = Spr->y + Spr->collisionyoffset - (fabs(Spr->collisionHeight) * fabs(Spr->syscale) / 2);

	float widthB = (fabs(SprOther->collisionWidth) * fabs(SprOther->sxscale));
	float heightB = (fabs(SprOther->collisionHeight) * fabs(SprOther->syscale));
	float minBx = SprOther->x + SprOther->collisionxoffset - (fabs(SprOther->collisionWidth) * fabs(SprOther->sxscale) / 2);
	float minBy = SprOther->y + SprOther->collisionyoffset - (fabs(SprOther->collisionHeight) * fabs(SprOther->syscale) / 2);

	bool xOverlap = ((minAx >= minBx) && (minAx <= minBx + widthB)) ||
					((minBx >= minAx) && (minBx <= minAx + widthA));

	bool yOverlap = ((minAy >= minBy) && (minAy <= minBy + heightB)) ||
					((minBy >= minAy) && (minBy <= minAy + heightA));

	return xOverlap && yOverlap;
}

//takes no rotations into account !
bool CSprites_DetectSpriteCollision(CSprite* Spr, CSprite* SprOther)
{
	if((Spr == NULL) || (SprOther == NULL))
		return false;

	switch(Spr->collisionShape)
	{
		case SHAPE_BOX:
		{
			switch(SprOther->collisionShape)
			{
				case SHAPE_BOX:
					return CSprites_DetectRectRectCollsion(Spr, SprOther);
					break;
				case SHAPE_CIRCLE:
					//only works for true circles not ovals!
					if ((SprOther->collisionWidth == SprOther->collisionHeight) && (SprOther->sxscale == SprOther->syscale))
					{	// check normal rect first
						//if (CSprites_DetectRectRectCollsion(Spr, SprOther))
							return CSprites_DetectRectCircleCollsion(Spr, SprOther);
						//else
						//	return false;
					}
					else
						return false;
					break;
				default:
					return false;
			}
			break;
		}
		case SHAPE_CIRCLE:
		{
			switch(SprOther->collisionShape)
			{
				case SHAPE_BOX:
					//only works for true circles not ovals!
					if ((Spr->collisionWidth == Spr->collisionHeight) && (Spr->sxscale == Spr->syscale))
					{
						// check normal rect first
						//if (CSprites_DetectRectRectCollsion(Spr, SprOther))
							return CSprites_DetectRectCircleCollsion(SprOther, Spr);
						//else
						//	return false;
					}
					else
						return false;
					break;
				default:
					return false;
			}
			break;
		}
		default:
			return false;
	}
}


void CSprites_RemoveSprite(CSprite* Spr)
{
	if(Spr == NULL)
		return;

	if((Spr->index < 0) || (Spr->index >= CSprites_spriteMax))
		return;
	
	CSprites_Sprites[Spr->index] = NULL;	
	free(Spr);
	CSprites_SpriteSlotsUsed--;
}


void CSprites_RemoveAllSprites()
{
	for (int i=0; i < CSprites_spriteMax; i++)
	{
		CSprites_RemoveSprite(CSprites_Sprites[i]);
	}
}

void CSprites_SetSpriteMax(int val)
{
	if(CSprites_Sprites)
	{
		int tmp = CSprites_spriteMax;
		CSprites_spriteMax = val;
		for (int i = tmp-1; i > CSprites_spriteMax-1; i--)
		{
			CSprites_RemoveSprite(CSprites_Sprites[i]);
			CSprites_Sprites[i] = NULL;
		}
		
		realloc(CSprites_Sprites, sizeof(CSprite*) * CSprites_spriteMax);
		
		for (int i = tmp; i < CSprites_spriteMax; i++)
			CSprites_Sprites[i] = NULL;
		
		if (val == 0)
			CSprites_Sprites = NULL;
	}
	else
	{
		CSprites_spriteMax = val;
		CSprites_Sprites = (CSprite**) malloc(sizeof(CSprite*) * CSprites_spriteMax);
		for (int i=0; i < CSprites_spriteMax; i++)
			CSprites_Sprites[i] = NULL;
	}
}

void CSprites_DeInit()
{
	if(CSprites_Sprites)
	{
		CSprites_RemoveAllSprites();
		free(CSprites_Sprites);
	}
}

#endif