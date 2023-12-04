// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SHOOTTHEMUP_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();


private:

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* MuzzleFlash;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* ShootAudio;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* ImpactHitVFX;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* ImpactHitSFX;

	UPROPERTY(EditDefaultsOnly)
	int MaxRange = 1000;

	UPROPERTY(EditDefaultsOnly)
	float BulletDamage = 10;

	void SetMuzzleFlash();

	void SetShootAudio();

	void SetImpactHitSFX(FVector Location);

	bool CheckIfHitObjectInChannel(FHitResult& hitResult);

	void HandleHit(bool bHasHit, FHitResult hitResult);

	AController* GetOwnerController() const;
};
