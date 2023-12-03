// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	
	UUserWidget* LoseScreenObject = CreateWidget(this, LoseScreenWidget);

	if (LoseScreenObject != nullptr)
	{
		LoseScreenObject->AddToViewport();
	}

	GetWorldTimerManager().SetTimer(RestartTimerHandle, this, &APlayerController::RestartLevel, RestartDelay); 
}
