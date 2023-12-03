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
	SetMuzzleFlash();

	FHitResult hitResult;
	AController* OwnerController = nullptr;
	bool bHasHitObjectInChannel = CheckIfHitObjectInChannel(hitResult);

	HandleHit(bHasHitObjectInChannel, hitResult);
}

void AGun::SetMuzzleFlash()
{
	if (MuzzleFlash == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("MuzzleFlash VFX not assiggned"));
		return;
	}
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, MeshComponent, TEXT("MuzzleFlashSocket"));
}

bool AGun::CheckIfHitObjectInChannel(FHitResult& hitResult)
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr) return false;

	FVector CamLocation;
	FRotator CamRotation;

	(OwnerController)->GetPlayerViewPoint(CamLocation, CamRotation);

	FVector EndPoint = CamLocation + CamRotation.Vector() * MaxRange;

	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(hitResult, CamLocation, EndPoint, ECollisionChannel::ECC_GameTraceChannel1, params);
}

void AGun::HandleHit(bool bHasHit, FHitResult hitResult)
{
	if (!bHasHit) return;
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactHitVFX, hitResult.Location, hitResult.ImpactNormal.Rotation());
	AActor* shotActor = hitResult.GetActor();
	if (shotActor == nullptr) return;
	FPointDamageEvent DamageActorEvent(BulletDamage, hitResult, hitResult.ImpactNormal, nullptr);;
	shotActor->TakeDamage(BulletDamage, DamageActorEvent, GetOwnerController(), this);
}

AController* AGun::GetOwnerController() const
{
	APawn* GunOwner = Cast<APawn>(GetOwner());
	if (GunOwner == nullptr) return nullptr;
	return GunOwner->GetController();
}

