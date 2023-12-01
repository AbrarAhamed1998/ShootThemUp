// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SetRootComponent(Root);

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	MeshComponent->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, MeshComponent, TEXT("MuzzleFlashSocket"));

	APawn* GunOwner = Cast<APawn>(GetOwner());
	if (GunOwner == nullptr) return;

	AController* OwnerController = GunOwner->GetController();
	if (OwnerController == nullptr) return;

	FVector CamLocation;
	FRotator CamRotation;

	OwnerController->GetPlayerViewPoint(CamLocation, CamRotation);

	FVector EndPoint = CamLocation + CamRotation.Vector() * MaxRange;

	FHitResult hitResult;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(GetOwner());

	bool bHasHitObjectInChannel = GetWorld()->LineTraceSingleByChannel(hitResult,CamLocation, EndPoint, ECollisionChannel::ECC_GameTraceChannel1, params);

	if (bHasHitObjectInChannel)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactHitVFX, hitResult.Location, hitResult.ImpactNormal.Rotation());
		AActor* shotActor = hitResult.GetActor();
		if (shotActor == nullptr) return;
		FPointDamageEvent DamageActorEvent(BulletDamage,hitResult, hitResult.ImpactNormal, nullptr);;
		shotActor->TakeDamage(BulletDamage, DamageActorEvent, OwnerController, this);
	}

	//DrawDebugCamera(GetWorld(), CamLocation, CamRotation, 90, 2, FColor::Blue, true);
}

