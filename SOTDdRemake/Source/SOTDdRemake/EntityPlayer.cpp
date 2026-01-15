// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityPlayer.h"
#include <EnhancedInputSubsystems.h>
#include "EnhancedInputComponent.h"
#include <Kismet/KismetSystemLibrary.h>
//#include "EntityMovementComponent.h"
//#include "Components/CapsuleComponent.h"


// Sets default values
AEntityPlayer::AEntityPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	springArm = CreateDefaultSubobject<USpringArmComponent>("springArm");
	camera = CreateDefaultSubobject<UCameraComponent>("camera");
	
	springArm->SetupAttachment(RootComponent);
	camera->SetupAttachment(springArm);
}

// Called when the game starts or when spawned
void AEntityPlayer::BeginPlay()
{
	Super::BeginPlay();
	SetActorLocation(FVector(GetActorLocation().X, 0.0f, GetActorLocation().Z));

	//mapping = GetWorld()->GetFirstPlayerController()->GetSubsystem<UInputMappingContext>();

	//if (ULocalPlayer* _localPlayer = Cast<ULocalPlayer>(GetController()))
	
	if (ULocalPlayer* _localPlayer = Cast<ULocalPlayer>(GetWorld()->GetFirstLocalPlayerFromController()))
	{
		UKismetSystemLibrary::PrintString(GetWorld(), "AEntityPlayer::BeginPlay");
		if (UEnhancedInputLocalPlayerSubsystem* _inputSystem = _localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			_inputSystem->AddMappingContext(mapping, 10);
		}
	}
}

// Called every frame
void AEntityPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEntityPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* _input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	_input->BindAction(moveAction, ETriggerEvent::Triggered, entityMovement.Get(),&UEntityMovementComponent::MovementPlayer);
	_input->BindAction(jumpAction, ETriggerEvent::Triggered, entityMovement.Get(),&UEntityMovementComponent::Jumping);
	_input->BindAction(attackAction, ETriggerEvent::Triggered, attack.Get(),&UAttackComponent::Attack);
	_input->BindAction(pauseAction, ETriggerEvent::Started, this,&AEntityPlayer::TogglePauseMenu);

	UKismetSystemLibrary::PrintString(GetWorld(), "AEntityPlayer::SetupPlayerInputComponent");

}

bool AEntityPlayer::Death()
{
	entityMovement->SetCanMove(false);
	onDeath.Broadcast();
	//Collision change in BP
	UKismetSystemLibrary::PrintString(GetWorld(), "Death Player");
	return Super::Death();
}

void AEntityPlayer::TogglePauseMenu(const FInputActionValue& _value)
{
	bool _isPaused = GetWorld()->IsPaused();
	GetWorld()->GetFirstPlayerController()->SetPause(!_isPaused);
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = !_isPaused;
	onTogglePauseMenu.Broadcast(!_isPaused);

}

