// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EntityMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "AttackComponent.h"
#include "EntityBase.generated.h"


UENUM(BlueprintType)
enum class EntityType : uint8
{
	Base UMETA(DisplayName = "Base"),
	Enemy UMETA(DisplayName = "Enemy"),
	Player UMETA(DisplayName = "Player")

};

UENUM(BlueprintType)
enum class EntityState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Walking UMETA(DisplayName = "Walking"),
	Jumping UMETA(DisplayName = "Jumping"),
	Attacking UMETA(DisplayName = "Attacking"),
	Hurt UMETA(DisplayName = "Hurt"),
	Dying UMETA(DisplayName = "Dying")
};

UCLASS()
class SOTDDREMAKE_API AEntityBase : public ACharacter
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) FString name = "Entity";
	UPROPERTY(EditAnywhere) EntityType type = EntityType::Base;
	UPROPERTY(EditAnywhere)EntityState state = EntityState::Idle;

protected:
	//Movement
	UPROPERTY(EditAnywhere)TObjectPtr<UEntityMovementComponent> entityMovement = nullptr;
	UPROPERTY(EditAnywhere)TObjectPtr<UAttackComponent> attack = nullptr;
	
	//Animation
	UPROPERTY(EditAnywhere)TObjectPtr<UPaperFlipbookComponent> flipbook = nullptr;
	UPROPERTY(editanywhere)TObjectPtr< UPaperFlipbook> flipbookIdle = nullptr;
	UPROPERTY(editanywhere)TObjectPtr< UPaperFlipbook> flipbookWalk = nullptr;
	UPROPERTY(editanywhere)TObjectPtr< UPaperFlipbook> flipbookJump = nullptr;
	UPROPERTY(editanywhere)TObjectPtr< UPaperFlipbook> flipbookAttack = nullptr;
	UPROPERTY(editanywhere)TObjectPtr< UPaperFlipbook> flipbookDamage = nullptr;
	UPROPERTY(editanywhere)TObjectPtr< UPaperFlipbook> flipbookDeath = nullptr;
	UPROPERTY(editanywhere)bool autoChangeAnimation = true;
	UPROPERTY() FTimerHandle timerWaitAnimation;

	//Audio
	UPROPERTY(EditAnywhere)TObjectPtr<UAudioComponent> audio = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<USoundBase> damageSound = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<USoundBase> deathSound = nullptr;


	//Life
	UPROPERTY(EditAnywhere) float currentLife = 3.0f;
	UPROPERTY(EditAnywhere) float maxLife = 3.0f;
	UPROPERTY(EditAnywhere) bool isDead = false;

	//Event
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddLife, const float&, _life);
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable) FOnAddLife onAddLife;

	FORCEINLINE float GetCurrentLife() { return currentLife; }
	FORCEINLINE bool GetIsDead() { return isDead; }
	FORCEINLINE TObjectPtr<UAudioComponent> GetAudio() { return audio; }

public:
	// Sets default values for this character's properties
	AEntityBase();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void UpdateAnimationMovement();
public:

	void AddLife(float _lifeToAdd);
	void DoDamageAnimation();
	void DoAttackAnimation();
	void WaitAnimationAutoChange();
	void EndWaitAnimationAutoChange();
	virtual bool Death();


};
