// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"

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

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
