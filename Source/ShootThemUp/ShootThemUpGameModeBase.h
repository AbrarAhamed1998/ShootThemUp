// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootThemUpGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API AShootThemUpGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void OnPawnKilled(APawn* KilledPawn);
};
