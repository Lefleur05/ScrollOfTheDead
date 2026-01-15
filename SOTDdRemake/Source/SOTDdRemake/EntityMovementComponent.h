// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "InputAction.h"
#include "EntityMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOTDDREMAKE_API UEntityMovementComponent : public UFloatingPawnMovement //UActorComponent //
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) bool canMove = true;
	UPROPERTY(EditAnywhere) float speed = 100.0f;

public:
	FORCEINLINE void SetCanMove(bool _canMove) { canMove = _canMove; }
	FORCEINLINE bool GetCanMove() { return canMove; }
public:	
	// Sets default values for this component's properties
	UEntityMovementComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void MovementPlayer(const FInputActionValue& _value);
	void Movement(FVector _targetLoc);
	void Jumping(const FInputActionValue& _value);

	void RotateToMoveDirection(FVector _targetLoc, bool useController);
	bool IsTheSameDirection(FVector _targetDir);
};
