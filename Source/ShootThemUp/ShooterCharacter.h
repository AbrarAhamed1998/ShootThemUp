// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SHOOTTHEMUP_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForwardCharacter(float axisValue);
	void MoveRightCharacter(float axisValue);
	void JumpCharacter();
	void LookUpRate(float axisValue);
	void LookRightRate(float axisValue);
	void Shoot();

	UPROPERTY(EditAnywhere)
	float RotationRate = 10.f;


	UPROPERTY(VisibleAnywhere)
	class AGun* SpawnedGun;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;


};
