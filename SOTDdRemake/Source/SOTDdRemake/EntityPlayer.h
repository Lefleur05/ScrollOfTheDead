// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EntityBase.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EntityPlayer.generated.h"

UCLASS()
class SOTDDREMAKE_API AEntityPlayer : public AEntityBase
{
	GENERATED_BODY()
	//Input
	UPROPERTY(EditAnywhere) TObjectPtr<UInputMappingContext> mapping = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> moveAction = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> jumpAction = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> attackAction = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> pauseAction = nullptr;

	//Camera
	UPROPERTY(EditAnywhere) TObjectPtr<USpringArmComponent> springArm = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UCameraComponent> camera = nullptr;

	//Inventory
	UPROPERTY(EditAnywhere) float countMoney = 0.0f;
	UPROPERTY(EditAnywhere) float countBook = 0.0f;
	UPROPERTY(EditAnywhere) float countRune = 0.0f;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdateInventory);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTogglePauseMenu, const bool , _isPaused);
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable) FOnDeath onDeath;
	UPROPERTY(BlueprintAssignable, BlueprintCallable) FOnUpdateInventory onUpdateInventory;
	UPROPERTY(BlueprintAssignable, BlueprintCallable) FOnTogglePauseMenu onTogglePauseMenu;

	UFUNCTION(BlueprintCallable) float GetCountMoney() { return countMoney; }
	UFUNCTION(BlueprintCallable) float GetCountBook() { return countBook; }
	UFUNCTION(BlueprintCallable) float GetCountRune() { return countRune; }
	UFUNCTION(BlueprintCallable) bool GetIsDead() { return isDead; }

	FORCEINLINE void SetCountMoney(float _value) { countMoney = _value; onUpdateInventory.Broadcast(); }
	FORCEINLINE void SetCountBook(float _value) { countBook = _value; onUpdateInventory.Broadcast(); }
	FORCEINLINE void SetCountRune(float _value) { countRune = _value; onUpdateInventory.Broadcast(); }


	//TSoftObjectPtr<AActor> test = nullptr; // LevelEncours/MyActor.MyActor -> *
	//TObjectPtr<AActor> testActor = nullptr // List -> AActorpresent dans la scene -> 0x0000 ?
public:
	AEntityPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	virtual bool Death() override;
	void TogglePauseMenu(const FInputActionValue& _value);


};
