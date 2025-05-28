// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	
	RemoveHUDFromViewport();

	HandleGameEndUI(bIsWinner);
}

void AShooterPlayerController::HandleGameEndUI(bool bIsWinner)
{
	if (bIsWinner)
		HandleWinCondition();
	else
		HandleLoseCondition();

	GetWorldTimerManager().SetTimer(RestartTimerHandle, this, &APlayerController::RestartLevel, RestartDelay);
}

void AShooterPlayerController::BeginPlayingState()
{
	Super::BeginPlayingState();
	// checking if the HUD UI Widget is null
	if (HUDScreenWidget == nullptr)
		return;

	HUDUIObject = CreateWidget(this, HUDScreenWidget);

	HUDUIObject->AddToViewport();
}

void AShooterPlayerController::HandleLoseCondition()
{
	UUserWidget* LoseScreenObject = CreateWidget(this, LoseScreenWidget);

	if (LoseScreenObject == nullptr)
		return;
	
	LoseScreenObject->AddToViewport();
}

void AShooterPlayerController::HandleWinCondition()
{
	UUserWidget* WinScreenObject = CreateWidget(this, WinScreenWidget);
	
	if (WinScreenObject == nullptr)
		return;

	WinScreenObject->AddToViewport();
}

void AShooterPlayerController::RemoveHUDFromViewport()
{
	if (HUDUIObject == nullptr)
		return;

	HUDUIObject->RemoveFromViewport();
}


