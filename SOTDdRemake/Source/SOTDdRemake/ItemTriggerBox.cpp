// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemTriggerBox.h"
#include "EntityPlayer.h"
#include <Kismet/KismetSystemLibrary.h>
#include "Components/AudioComponent.h"

AItemTriggerBox::AItemTriggerBox()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>("flipbook");
	collision = CreateDefaultSubobject<UBoxComponent>("collision");
	audio = CreateDefaultSubobject<UAudioComponent>("audio");

	flipbook->SetupAttachment(RootComponent);
	collision->SetupAttachment(RootComponent);
	audio->SetupAttachment(RootComponent);
}

void AItemTriggerBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	TObjectPtr<AEntityPlayer> _player = Cast<AEntityPlayer>(OtherActor);
	if (!_player)return;

	switch (type)
	{
	case ItemType::Money:
		_player->SetCountMoney(_player->GetCountMoney() + 1);
		break;
	case ItemType::Book:
		_player->SetCountBook(_player->GetCountBook() + 1);
		break;
	case ItemType::Rune:
		_player->SetCountRune(_player->GetCountRune() + 1);
		break;
	default:
		break;
	}

	audio->SetSound(pickUpSound);
	audio->Play();

	UKismetSystemLibrary::PrintString(GetWorld(), "NotifyActorBeginOverlap");
	SetActorEnableCollision(false);
	SetLifeSpan(1.0f);
	flipbook->SetVisibility(false);
	//Destroy();

}
