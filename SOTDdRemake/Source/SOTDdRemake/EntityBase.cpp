// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityBase.h"
#include <Kismet/KismetSystemLibrary.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
AEntityBase::AEntityBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	entityMovement = CreateDefaultSubobject<UEntityMovementComponent>("movement");
	attack = CreateDefaultSubobject<UAttackComponent>("attack");
	flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>("flipbook");
	audio = CreateDefaultSubobject<UAudioComponent>("audio");
	flipbook->SetupAttachment(RootComponent);
	audio->SetupAttachment(RootComponent);
	AddOwnedComponent(entityMovement);
	AddOwnedComponent(attack);
}

// Called when the game starts or when spawned
void AEntityBase::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void AEntityBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!isDead)
		SetActorLocation(FVector(GetActorLocation().X, 0.0f, GetActorLocation().Z));
	UpdateAnimationMovement();
}

// Called to bind functionality to input
void AEntityBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEntityBase::UpdateAnimationMovement()
{
	if (!autoChangeAnimation)return;
	
	if (!CanJump())
	{
		if (flipbookJump)
			flipbook->SetFlipbook(flipbookJump);
	}
	else if (GetCharacterMovement()->Velocity.Length() > 0.0f)
	{
		if (flipbookWalk)
			flipbook->SetFlipbook(flipbookWalk);
	}
	else
	{
		if (flipbookIdle)
			flipbook->SetFlipbook(flipbookIdle);
	}

}


void AEntityBase::AddLife(float _lifeToAdd)
{
	currentLife += _lifeToAdd;
	currentLife = currentLife > maxLife ? maxLife : currentLife < 0.0f ? 0.0f : currentLife;

	onAddLife.Broadcast(currentLife);

	if (_lifeToAdd < 0.0f && currentLife > 0.0f)
	{
		DoDamageAnimation();
		if (damageSound)
		{
			audio->SetSound(damageSound);
			audio->Play();
		}
	}
	if (currentLife <= 0.0f)
		Death();

}

bool AEntityBase::Death()
{
	isDead = currentLife <= 0.0f;
	
	if (isDead)
	{
		if (deathSound)
		{
			audio->SetSound(deathSound);
			audio->Play();
		}

		entityMovement->SetCanMove(false);

		autoChangeAnimation = false;
		if (flipbookDeath)
		{
			flipbook->SetFlipbook(flipbookDeath);
			flipbook->SetLooping(false);
		}
		SetActorLocation(GetActorLocation() + FVector(0.0f, 5.0f, 0.0f));

	}
	return isDead;
}

void AEntityBase::DoDamageAnimation()
{
	if (flipbookDamage)
	{
		flipbook->SetFlipbook(flipbookDamage);
		WaitAnimationAutoChange();
	}
}

void AEntityBase::DoAttackAnimation()
{
	if (flipbookAttack)
	{
		flipbook->SetFlipbook(flipbookAttack);
		WaitAnimationAutoChange();
	}
}

void AEntityBase::WaitAnimationAutoChange()
{
	autoChangeAnimation = false;
	GetWorldTimerManager().SetTimer(timerWaitAnimation, this, &AEntityBase::EndWaitAnimationAutoChange, 0.5f, false);
}

void AEntityBase::EndWaitAnimationAutoChange()
{
	if(!isDead)
		autoChangeAnimation = true;
	UKismetSystemLibrary::PrintString(GetWorld(), "Animation damage2");
	GetWorldTimerManager().ClearTimer(timerWaitAnimation);
}

