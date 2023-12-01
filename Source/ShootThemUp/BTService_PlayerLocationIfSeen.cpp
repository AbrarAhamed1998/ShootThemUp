// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "AIController.h"
#include "ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
		return;
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (PlayerPawn == nullptr)
		return;

	if (AIController->LineOfSightTo(PlayerPawn))
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, PlayerPawn->GetActorLocation());
	else
		OwnerComp.GetBlackboardComponent()->ClearValue(BlackboardKey.SelectedKeyName);
}
