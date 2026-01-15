// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOTDDREMAKE_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) float damage = 1.0f;
	UPROPERTY(EditAnywhere) float range =100.0f;
	UPROPERTY(EditAnywhere) TArray<TEnumAsByte<EObjectTypeQuery>> objectToAttack;

	UPROPERTY(EditAnywhere) float fireRate =1.0f;
	UPROPERTY(EditAnywhere) float currentfireRate =1.0f;

	UPROPERTY(EditAnywhere) float timeWaitAnimation =0.3f;
	UPROPERTY(EditAnywhere) FTimerHandle timerAttack;

	UPROPERTY(EditAnywhere) TObjectPtr<USoundBase> attackSound = nullptr;

public:	
	// Sets default values for this component's properties
	UAttackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void Attack();
	void AttackWithanimation();
	void UpdateFireRate(float _deltattime);
};
