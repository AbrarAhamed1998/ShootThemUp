// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::OnPawnKilled(APawn* KilledPawn)
{
	Super::OnPawnKilled(KilledPawn);
	
	APlayerController* PlayerController = Cast<APlayerController>(KilledPawn->GetController());

	if (PlayerController != nullptr)
	{
		//UE_LOG(LogTemp, Log, TEXT("Player Killed!"));
		EndGame(false);
		return;
	}

	// For loop going through all AI controllers
	for (AShooterAIController* ShooterAI : TActorRange<AShooterAIController>(GetWorld()))
	{
		// If one of them not dead return out
		if (!ShooterAI->IsDead())
			return;
	}

	// Call Game end if all are dead
	EndGame(true);

}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
