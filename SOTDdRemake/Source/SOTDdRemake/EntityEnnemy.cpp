// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityEnnemy.h"
#include <Kismet/KismetSystemLibrary.h>

// Sets default values
AEntityEnnemy::AEntityEnnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEntityEnnemy::BeginPlay()
{
	Super::BeginPlay();
	targetLoc = GetActorLocation();
	RandomTargetLocation();


}

// Called every frame
void AEntityEnnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Update(DeltaTime);
	
}

void AEntityEnnemy::Update(float _deltatime)
{
	if (isDead)return;
	DetectePlayer();
	if (currenttimeBeforeMoveAgain >= timeBeforeMoveAgain)
		entityMovement->Movement(targetLoc);
	else
		WaitForMove(_deltatime);
	if (OnTheTargetLoc())
	{
		if (!followPlayer)
		{
			RandomTargetLocation();
			currenttimeBeforeMoveAgain = 0.0f;

		}
	}
	if (followPlayer)
		attack->Attack();

	SetActorRotation(FRotator(0.0f, GetActorRotation().Yaw, GetActorRotation().Roll));
}


void AEntityEnnemy::RandomTargetLocation()
{
	// TODO se bloque entre eux
	float _x = FMath::RandRange(-maxRangeTargetLoc, maxRangeTargetLoc);
	//UKismetSystemLibrary::PrintString(GetWorld(), "RandomTarget :" + FString::SanitizeFloat(_x));

	TArray<AActor*> _ignore;
	_ignore.Add(GetOwner());

	targetLoc = FVector(GetActorLocation().X + _x, GetActorLocation().Y, GetActorLocation().Z); 

	FHitResult _result;
	bool _somethingOnThePath = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(),
		GetActorLocation(),
		targetLoc,
		objectOnThePath,
		false,
		_ignore,
		EDrawDebugTrace::ForOneFrame,
		_result,
		true);

	if (_somethingOnThePath)
	{
		targetLoc = GetActorLocation();
		UKismetSystemLibrary::PrintString(GetWorld(), _result.GetActor()->GetName() + "new RandomTarget :" + targetLoc.ToString());

	}
}

bool AEntityEnnemy::OnTheTargetLoc()
{
	//float _dist = FVector::Dist(targetLoc, GetActorLocation());
	//return _dist < 5.0f;
	float _dist = targetLoc.X - GetActorLocation().X;
	return  _dist < 40.0f && _dist >-40.0f;
}

void AEntityEnnemy::WaitForMove(float _deltatime)
{
	if (currenttimeBeforeMoveAgain >= timeBeforeMoveAgain)return;
	currenttimeBeforeMoveAgain += _deltatime;
}

void AEntityEnnemy::DetectePlayer()
{

	FHitResult _result;
	followPlayer = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(),
		GetActorLocation() - GetActorForwardVector() * rangeOfViewBehind,
		GetActorLocation() + GetActorForwardVector() * rangeOfView,
		playerToFollow,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::ForOneFrame,
		_result,
		true);

	if (followPlayer)
	{
		//UKismetSystemLibrary::PrintString(GetWorld(), "I see you");
		targetLoc = _result.GetActor()->GetActorLocation();
	}
}

bool AEntityEnnemy::Death()
{
	SetActorEnableCollision(false);
	//UKismetSystemLibrary::PrintString(GetWorld(), "Death Ennemy");
	return Super::Death();;
}

