// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include "EntityBase.h"
#include "Components/AudioComponent.h"
#include "EntityPlayer.h"

// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateFireRate(DeltaTime);
	// ...
}

void UAttackComponent::Attack()
{
	TObjectPtr<AEntityPlayer> _entityPlayer = Cast<AEntityPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (_entityPlayer->GetIsDead())
		return;


	if (currentfireRate < fireRate)
		return;
	currentfireRate = 0.0f;

	
	TObjectPtr<AEntityBase> _entityOwner = Cast<AEntityBase>(GetOwner());
	if (_entityOwner)
	{
		if (_entityOwner->GetIsDead())
			return;

		_entityOwner->DoAttackAnimation();
		if (attackSound)
		{
			_entityOwner->GetAudio()->SetSound(attackSound);
			_entityOwner->GetAudio()->Play();
		}
	}

	if (timeWaitAnimation <= 0.0f)
	{
		AttackWithanimation();
		return;
	}
	GetWorld()->GetTimerManager().SetTimer(timerAttack, this, &UAttackComponent::AttackWithanimation, timeWaitAnimation, false);
}

void UAttackComponent::AttackWithanimation()
{
	GetWorld()->GetTimerManager().ClearTimer(timerAttack);

	TObjectPtr<AActor> _owner = GetOwner();
	FVector _start = _owner->GetActorLocation();
	FVector _end = _owner->GetActorLocation() + _owner->GetActorForwardVector() * range;

	FHitResult _result;
	UKismetSystemLibrary::BoxTraceSingleForObjects(GetWorld(),
		_start,
		_end,
		FVector(25.0f, 25.0f, 50.0f),
		FRotator(0.0f),
		objectToAttack,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::ForOneFrame,
		_result,
		true);


	TObjectPtr<AEntityBase> _entity = Cast<AEntityBase>(_result.GetActor());
	if (_entity)
	{
		_entity->AddLife(-damage);
		UKismetSystemLibrary::PrintString(GetWorld(), "Hit");
	}
}

void UAttackComponent::UpdateFireRate(float _deltatime)
{
	if (currentfireRate <= fireRate)
	{
		currentfireRate += _deltatime;
	}
}

