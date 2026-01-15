// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityMovementComponent.h"
#include "GameFramework/Character.h"
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/KismetSystemLibrary.h>
#include "Components/CapsuleComponent.h"

// Sets default values for this component's properties
UEntityMovementComponent::UEntityMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEntityMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEntityMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEntityMovementComponent::MovementPlayer(const FInputActionValue& _value)
{
	//TODO Movement move only the capsule
	//UKismetSystemLibrary::PrintString(GetWorld(), "MovementPlayer");

	if (!canMove)return;
	TObjectPtr<APawn> _entity = Cast<APawn>(GetOwner());
	if (!_entity)return;

	float _input = _value.Get<float>();
	FVector _move = FVector::ForwardVector * speed * _input;
	_entity->AddMovementInput(_move);
	//UKismetSystemLibrary::PrintString(GetWorld(), "MovementPlayer "+ _move.ToString());
	RotateToMoveDirection(FVector::ForwardVector * speed * _input+ _entity->GetActorLocation(), true);
}

void UEntityMovementComponent::Movement(FVector _targetLoc)
{
	if (!canMove)return;
	//TODO movement with target pos
	TObjectPtr<APawn> _entity = Cast<APawn>(GetOwner());
	if (!_entity)return;
	FVector _direction = _targetLoc - _entity->GetActorLocation();
	_direction.Normalize();
	_entity->AddMovementInput(_direction * speed);
	RotateToMoveDirection(_targetLoc, false);
}

void UEntityMovementComponent::Jumping(const FInputActionValue& _value)
{
	if (!canMove)return;
	//UKismetSystemLibrary::PrintString(GetWorld(), "Jump");

	TObjectPtr<ACharacter> _entity = Cast<ACharacter>(GetOwner());
	if (!_entity)return;
	_entity->Jump();
}

void UEntityMovementComponent::RotateToMoveDirection(FVector _targetLoc, bool useController)
{
	TObjectPtr<APawn> _entity = Cast<APawn>(GetOwner());
	if (!_entity)return;

	FRotator _rot = UKismetMathLibrary::FindLookAtRotation(_entity->GetActorLocation(), _targetLoc) ;//+FRotator(0.0f, -90.0f, 0.0f)

	if (IsTheSameDirection(_targetLoc - _entity->GetActorLocation()))
		return;

	if (useController)
	{
		//_entity->AddControllerYawInput(180.0f);
		_entity->GetController()->SetControlRotation(_rot);

	}
	else
	{
		_entity->SetActorRotation(_rot);
	}
	//UKismetSystemLibrary::PrintString(GetWorld(), "RotateToMoveDirection "+ _rot.ToString());
}

bool UEntityMovementComponent::IsTheSameDirection(FVector _targetDir)
{
	float _dot = FVector::DotProduct(GetOwner()->GetActorForwardVector(), _targetDir);
	//UKismetSystemLibrary::PrintString(GetWorld(), "RotateToMoveDirection " + FString::SanitizeFloat(_dot));
	return _dot>= 99.0f;
}


