// Fill out your copyright notice in the Description page of Project Settings.


#include "SSPlayerState.h"

ASSPlayerState::ASSPlayerState()
{

}

void ASSPlayerState::OnRep_TeamScores()
{
	UE_LOG(LogTemp, Warning, TEXT("Player State Get Replicated TemScored!"));
}
