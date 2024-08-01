#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "input.h"
#include "cworldparts.h"

bool StageDone(CWorldParts* WorldParts, CWorldPart* Player)
{
	//this works because player is on a higher group (it is handled & found last so the exit is found first if we are at that position)
	CWorldPart* Part = CWorldParts_PartAtPosition(WorldParts, Player->PlayFieldX, Player->PlayFieldY);
	if (Part)
	{
		if (Part->Type == IDExit)
		{
			return true;
		}
	}
	return false;
}


void GameInit(CWorldParts* WorldParts)
{
	FreeView = false;
	NeedRedraw = true;
	CWorldParts_FindPlayer(WorldParts);
	CWorldParts_LimitVPLevel(WorldParts);
}

void Game(CWorldParts* WorldParts)
{
	if (GameState == GSGameInit)
	{
		GameInit(WorldParts);
		GameState -= GSDiff;
	}
	if (!FreeView && !AskingQuestion && (gamepad_button_b() == 1))
	{
		playMenuBackSound();
		AskQuestion(qsQuitPlaying, "Do you want to quit playing the\ncurrent level and return to the level\nselector?\n\nPress (A) to quit, (B) to keep playing");
	}
	
	if(!AskingQuestion && (gamepad_button_r() == 1))
	{
		playMenuSelectSound();
		int i = skinSaveState();
		i++;
		if (i == MAXSKINS)
			i = 0;
		setSkinSaveState(i);
		NeedToReloadGraphics = true;
	}

	if(!FreeView && !AskingQuestion && (gamepad_button_y() == 1))
	{
		playMenuSelectSound();
		AskQuestion(qsRestartLevel, "Do you want to restart the\ncurrent level?\n\nPress (A) to restart, (B) to cancel");		
	}

	if (FreeView)
	{
		if (gamepad_button_x() == 1)
		{
			playMenuSelectSound();
			FreeView = false;
			CWorldParts_CenterVPOnPlayer(WorldParts);
			NeedRedraw = true;
		}
	}
	else
	{
		if(!AskingQuestion && (gamepad_button_x() == 1))
		{
			playMenuSelectSound();
			FreeView = true;
			NeedRedraw = true;
		}
		if (WorldParts->Player)
		{
			if (!AskingQuestion && !WorldParts->Player->IsMoving && !WorldParts->AttchedBoxQuedOrMoving)
			{
				//pickup 
				if ((gamepad_button_a() == 1) || (gamepad_up() == 1))
				{
					//dropping a block
					//if there is a block on top of the player and were facing left				
					if (WorldParts->NumBoxesAttachedToPlayer > 0)
					{
						CWorldPart* Part = CWorldParts_PartAtPosition(WorldParts, WorldParts->Player->PlayFieldX, WorldParts->Player->PlayFieldY - 1);
						if (Part)
						{
							if (Part->Group == GroupBox)
							{
								if (WorldParts->Player->AnimBase == AnimBaseLeft)
								{
									// and it can move to the left
									if ((CWorldPart_CanMoveTo(Part, Part->PlayFieldX - 1, Part->PlayFieldY)))
									{
										//move it to the left
										CWorldPart_AddToMoveQue(Part, Part->PlayFieldX - 1, Part->PlayFieldY);
										CWorldPart_AddToMoveQue(Part, Part->PlayFieldX - 1, Part->PlayFieldY + 1);
										//detaching is set automatically otherwise it would be set too early while the block is still detaching
										//CWorldPart_DeattachFromPlayer(WorldParts->Items[teller]);
										//NeedRedraw = true;
										playDropSound();
									}
								}
								else
								{
									// if there is block on top of theplayer were facing right
									if (WorldParts->Player->AnimBase == AnimBaseRight)
									{
										// and it can move to the left
										if ((CWorldPart_CanMoveTo(Part, Part->PlayFieldX + 1, Part->PlayFieldY)))
										{
											//move it to right
											CWorldPart_AddToMoveQue(Part, Part->PlayFieldX + 1, Part->PlayFieldY);
											CWorldPart_AddToMoveQue(Part, Part->PlayFieldX + 1, Part->PlayFieldY + 1);
											//detaching is set automatically otherwise it would be set too early while the block is still detaching
											//CWorldPart_DeattachFromPlayer(WorldParts->Items[teller]);
											//NeedRedraw = true;
											playDropSound();
										}

									}
								}
							}
						}
					}
					else
					{
						if (WorldParts->NumBoxesAttachedToPlayer == 0)
						{
							bool FloorFound = false;
							//picking up a block
							//if there is a block left to the player and were facing left
							if (WorldParts->Player->AnimBase == AnimBaseLeft)
							{
								CWorldPart* Part = CWorldParts_PartAtPosition(WorldParts, WorldParts->Player->PlayFieldX - 1, WorldParts->Player->PlayFieldY);
								if (Part)
								{
									if (Part->Group == GroupBox)
									{
										//see if there is a floor or block beneath the block
										CWorldPart* Part2 = CWorldParts_PartAtPosition(WorldParts, WorldParts->Player->PlayFieldX - 1, WorldParts->Player->PlayFieldY + 1);
										if (Part2)
										{
											if ((Part2->Group == GroupFloor) || (Part2->Group == GroupBox) || (Part2->Group == GroupExit))
											{
												FloorFound = true;
											}
										}

										if (Part->PlayFieldY == NrOfRows - 1)
										{
											FloorFound = true;
										}

										if (FloorFound)
										{
											//if there was see if there is space above the block and above the player
											if ((CWorldPart_CanMoveTo(Part, Part->PlayFieldX, Part->PlayFieldY - 1)) &&
												(CWorldPart_CanMoveTo(Part, Part->PlayFieldX + 1, Part->PlayFieldY - 1)))
											{
												//Attach the block to the player & move the block
												CWorldPart_AttachToPlayer(Part, WorldParts->Player);
												CWorldPart_AddToMoveQue(Part, Part->PlayFieldX, Part->PlayFieldY - 1);
												CWorldPart_AddToMoveQue(Part, Part->PlayFieldX + 1, Part->PlayFieldY - 1);
												//NeedRedraw = true;
												playPickupSound();
											}
										}
									}
								}
							}
							else
							{
								if (WorldParts->Player->AnimBase == AnimBaseRight)
								{
									CWorldPart* Part = CWorldParts_PartAtPosition(WorldParts, WorldParts->Player->PlayFieldX + 1, WorldParts->Player->PlayFieldY);
									if (Part)
									{
										if (Part->Group == GroupBox)
										{
											//see if there is a floor or block beneath the block
											CWorldPart* Part2 = CWorldParts_PartAtPosition(WorldParts, WorldParts->Player->PlayFieldX + 1, WorldParts->Player->PlayFieldY + 1);
											if (Part2)
											{
												if ((Part2->Group == GroupFloor) || (Part2->Group == GroupBox) || (Part2->Group == GroupExit))
												{
													FloorFound = true;
												}
											}


											if (Part->PlayFieldY == NrOfRows - 1)
											{
												FloorFound = true;
											}

											if (FloorFound)
											{
												//if there was see if there is space above the block and above the player
												if (CWorldPart_CanMoveTo(Part, Part->PlayFieldX, Part->PlayFieldY - 1) &&
													CWorldPart_CanMoveTo(Part, Part->PlayFieldX - 1, Part->PlayFieldY - 1))
												{
													//Attach the block to the player & move the block
													CWorldPart_AttachToPlayer(Part, WorldParts->Player);
													CWorldPart_AddToMoveQue(Part, Part->PlayFieldX, Part->PlayFieldY - 1);
													CWorldPart_AddToMoveQue(Part, Part->PlayFieldX - 1, Part->PlayFieldY - 1);
													//NeedRedraw = true;
													playPickupSound();
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	if (FreeView)
	{
		if (gamepad_left() % 2 == 1)
		{
			if (CViewPort_Move(WorldParts->ViewPort, -ViewportMove, 0))
			{
				NeedRedraw = true;
			}
		}
		if (gamepad_right() % 2 == 1)
		{
			if (CViewPort_Move(WorldParts->ViewPort, ViewportMove, 0))
			{
				NeedRedraw = true;
			}
		}
		if (gamepad_up() % 2 == 1)
		{
			if (CViewPort_Move(WorldParts->ViewPort, 0, -ViewportMove))
			{
				NeedRedraw = true;
			}
		}
		if (gamepad_down() % 2 == 1)
		{
			if (CViewPort_Move(WorldParts->ViewPort, 0, ViewportMove))
			{
				NeedRedraw = true;
			}
		}
	}
	else
	{		
		//need to have a input delay, its too taxing otherwise
		framecounter++;
		if (framecounter >= FrameDelayInput)
		{
			framecounter = 0;
			if (WorldParts->Player)
			{
				if (!AskingQuestion && !WorldParts->Player->IsMoving && !WorldParts->AttchedBoxQuedOrMoving)
				{
					if (gamepad_left() > 0)
					{
						if (CWorldPart_MoveTo(WorldParts->Player, WorldParts->Player->PlayFieldX - 1, WorldParts->Player->PlayFieldY))
						{
							NeedRedraw = true;
						}
						else
						{
							//move up
							NeedRedraw |= CWorldPart_MoveTo(WorldParts->Player, WorldParts->Player->PlayFieldX, WorldParts->Player->PlayFieldY - 1);
						}
					}

					if (gamepad_right() > 0)
					{
						if (CWorldPart_MoveTo(WorldParts->Player, WorldParts->Player->PlayFieldX + 1, WorldParts->Player->PlayFieldY))
						{
							NeedRedraw = true;
						}
						else
						{
							//move up
							NeedRedraw |= CWorldPart_MoveTo(WorldParts->Player, WorldParts->Player->PlayFieldX, WorldParts->Player->PlayFieldY - 1);
						}
					}
				}
			}
		}
	}
	
	
	if (!AskingQuestion)
	{
		NeedRedraw |= CWorldParts_Move(WorldParts) || NeedToReloadGraphics;
		if (NeedRedraw)
		{
			NeedRedraw = false;

			if (NeedToReloadGraphics)
			{
				LoadGraphics();
				CWorldParts_UpdateGraphics(WorldParts);
				NeedToReloadGraphics = false;
			}
			drawTexture(IMGBackground, 0, 0, 0);
			CWorldParts_Draw(WorldParts);
						
			if (FreeView)
			{
				set_multiply_color(Color1);
				draw_filled_rectangle(0, 0, WINDOW_WIDTH, 16);
				set_multiply_color(Color2);
				draw_rectangle(0, 16, WINDOW_WIDTH, 16);
				textfont_print_from_left(&FontRoboto_Bold_12,2,0, "Freeview - dpad: Move X: exit R: Next Skin");
				set_multiply_color(color_white);
			}
			else
			{
				if(gameHelpBarSaveState())
				{
					set_multiply_color(Color1);
					draw_filled_rectangle(0, 0, WINDOW_WIDTH, 16);
					set_multiply_color(Color2);
					draw_rectangle(0, 16, WINDOW_WIDTH, 16);
					textfont_print_from_left(&FontRoboto_Bold_12,2,0, "Game - dpad: Move A: pickup / drop B: Quit X: Freeview Mode Y: Restart Level R: Next Skin");
					set_multiply_color(color_white);
				}
			}
		}
	}

	if (WorldParts->Player)
	{
		if (!AskingQuestion && !WorldParts->Player->IsMoving && StageDone(WorldParts, WorldParts->Player))
		{
			//to one extra move & draw to make sure boxes are on final spot
			CWorldParts_Move(WorldParts);
			drawTexture(IMGBackground, 0, 0, 0);
			CWorldParts_Draw(WorldParts);
			
			playLevelDoneSound();
			
			int[200] Msg;
			int[10] Nr;
			
			if ((SelectedLevel == lastUnlockedLevel()))
			{
									
				if (lastUnlockedLevel() < MaxLevels[CurrentLevelPackIndex])
				{

					strcpy(Msg, "Congratulations !\n\nYou Succesfully Solved Level ");
					itoa(SelectedLevel, Nr, 10);
					strcat(Msg, Nr);
					strcat(Msg, "/");
					itoa(MaxLevels[CurrentLevelPackIndex], Nr, 10);
					strcat(Msg, Nr);
					strcat(Msg,"\nThe next level has now been unlocked!\n\nPress (A) to continue");
					AskQuestion(qsSolvedNotLastLevel, Msg);

				}
				else
				{
					strcpy(Msg, "Congratulations !\n\nYou Succesfully Solved Level ");
					itoa(SelectedLevel, Nr, 10);
					strcat(Msg, Nr);
					strcat(Msg, "/");
					itoa(MaxLevels[CurrentLevelPackIndex], Nr, 10);
					strcat(Msg, Nr);
					strcat(Msg,"\nAll levels are now finished!\n\nPress (A) to continue");
					AskQuestion(qsSolvedLastLevel, Msg);
				}
			}
			else
			{
				strcpy(Msg, "Congratulations !\n\nYou Succesfully Solved Level ");
				itoa(SelectedLevel, Nr, 10);
				strcat(Msg, Nr);
				strcat(Msg, "/");
				itoa(MaxLevels[CurrentLevelPackIndex], Nr, 10);
				strcat(Msg, Nr);
				strcat(Msg,"\n\nPress (A) to continue");
				AskQuestion(qsSolvedLevel, Msg);
			}
		}
	}

	int id;
	bool answer;
	//simple confirm messages
	if ((AskingQuestionID == qsSolvedNotLastLevel) || (AskingQuestionID == qsSolvedLastLevel) || (AskingQuestionID == qsSolvedLevel))
	{
		if (AskQuestionUpdate(&id, &answer, true))
		{
			if ((id == qsSolvedNotLastLevel) && answer)
			{
				SelectedLevel++;
				unlockLevel(SelectedLevel);
				GameState = GSStageSelectInit;
			}

			if ((id == qsSolvedLastLevel) && answer)
			{
				GameState = GSTitleScreenInit;
			}

			if ((id == qsSolvedLevel) && answer)
			{
					GameState = GSStageSelectInit;
			}
		}
	}

	//Yes / No Questions
	if (AskingQuestionID == qsQuitPlaying || AskingQuestionID == qsRestartLevel)
	{
		if (AskQuestionUpdate(&id, &answer, false))
		{
			if (id == qsRestartLevel)
			{
				if (answer)
				{
					LoadSelectedLevel(WorldParts);
					NeedRedraw = true;
				}
			}

			if (id == qsQuitPlaying)
			{
				if (answer)
				{
					GameState = GSStageSelectInit;
				}
			}
		}
	}
}

#endif