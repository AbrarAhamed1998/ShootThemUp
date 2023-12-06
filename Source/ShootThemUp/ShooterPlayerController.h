// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

	void HandleGameEndUI(bool bIsWinner);

protected:
	virtual void BeginPlayingState() override;
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> LoseScreenWidget;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> WinScreenWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> HUDScreenWidget;

	UPROPERTY(EditDefaultsOnly)
	float RestartDelay = 3.0f;

	FTimerHandle RestartTimerHandle;

	UPROPERTY()
	UUserWidget* HUDUIObject;
	/// <summary>
	/// Handles the Lose condition on Game End.
	/// </summary>
	void HandleLoseCondition();

	/// <summary>
	/// Handles the Win condition on Game End.
	/// </summary>
	void HandleWinCondition();

	void RemoveHUDFromViewport();
};
