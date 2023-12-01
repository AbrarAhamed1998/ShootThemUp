// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"


void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	
	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);

		PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}


void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//MoveToActor(PlayerPawn, 300, false, true);

	//if (LineOfSightTo(PlayerPawn))
	//{
	//	// Setting current player location
	//	GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
	//	//SetFocus(PlayerPawn);
	//	
	//	// Setting last known location
	//	GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownLocation"), PlayerPawn->GetActorLocation());
	//}
	//else
	//{
	//	GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	//}
}