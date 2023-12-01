// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"

void AKillEmAllGameMode::OnPawnKilled(APawn* KilledPawn)
{
	Super::OnPawnKilled(KilledPawn);
	
	APlayerController* PlayerController = Cast<APlayerController>(KilledPawn->GetController());

	if (PlayerController != nullptr)
	{
		//UE_LOG(LogTemp, Log, TEXT("Player Killed!"));
		PlayerController->GameHasEnded(nullptr, false);
	}
}
