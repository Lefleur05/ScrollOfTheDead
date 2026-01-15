// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EntityBase.h"
#include "EntityEnnemy.generated.h"

UCLASS()
class SOTDDREMAKE_API AEntityEnnemy : public AEntityBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) FVector targetLoc = FVector(0.0f);
	UPROPERTY(EditAnywhere) float maxRangeTargetLoc = 500.0f;
	UPROPERTY(EditAnywhere) float timeBeforeMoveAgain = 2.0f;
	UPROPERTY(EditAnywhere) float currenttimeBeforeMoveAgain = 5.0f;

	UPROPERTY(EditAnywhere) bool followPlayer = false;
	UPROPERTY(EditAnywhere) float rangeOfView =250;
	UPROPERTY(EditAnywhere) float rangeOfViewBehind = 100.0f;
	UPROPERTY(EditAnywhere) TArray<TEnumAsByte<EObjectTypeQuery>> playerToFollow; // Player
	UPROPERTY(EditAnywhere) TArray<TEnumAsByte<EObjectTypeQuery>> objectOnThePath; // WorldStatic, WorldDynamic, PhysicsBody, Ennemy

public:	
	AEntityEnnemy();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void Update(float _deltatime);

public:

	void RandomTargetLocation();
	bool OnTheTargetLoc();
	void WaitForMove(float _deltatime);

	void DetectePlayer();

	virtual bool Death() override;


};
