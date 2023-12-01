// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "ShootThemUpGameModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnedGun = GetWorld()->SpawnActor<AGun>(GunClass);

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	SpawnedGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));

	SpawnedGun->SetOwner(this);

	CurrentHealth = MaxHealth;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForwardCharacter);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRightCharacter);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"),EInputEvent::IE_Pressed,this, &ACharacter::Jump);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed ,this, &AShooterCharacter::Shoot);
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (IsDead()) return 0;
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageApplied = FMath::Min(CurrentHealth, DamageApplied);
	CurrentHealth -= DamageApplied;
	//UE_LOG(LogTemp, Warning, TEXT("CurrentHealth : %f"), CurrentHealth);

	if (IsDead())
	{
		AShootThemUpGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AShootThemUpGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->OnPawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageApplied;
}

bool AShooterCharacter::IsDead() const
{
	return CurrentHealth<=0;
}

void AShooterCharacter::MoveForwardCharacter(float val)
{
	AddMovementInput(GetActorForwardVector() * val);
}

void AShooterCharacter::MoveRightCharacter(float axisValue)
{
	AddMovementInput(GetActorRightVector() * axisValue);
}

void AShooterCharacter::JumpCharacter()
{
	//AddMovementInput(GetActorUpVector() * 5.0f);
}

void AShooterCharacter::LookUpRate(float axisValue)
{
	AddControllerPitchInput(axisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightRate(float axisValue)
{
	AddControllerYawInput(axisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::Shoot()
{
	SpawnedGun->PullTrigger();
}



