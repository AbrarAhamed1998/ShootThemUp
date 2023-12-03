// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShootThemUpGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API AKillEmAllGameMode : public AShootThemUpGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void OnPawnKilled(APawn* KilledPawn) override;
	void EndGame(bool bIsPlayerWinner);
};
