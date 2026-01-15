// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "ItemTriggerBox.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ItemType : uint8
{
	Money UMETA(DisplayName = "Money"),
	Book UMETA(DisplayName = "Book"),
	Rune UMETA(DisplayName = "Rune")

};

UCLASS()
class SOTDDREMAKE_API AItemTriggerBox : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) ItemType type = ItemType::Money;
	UPROPERTY(EditAnywhere)TObjectPtr<UPaperFlipbookComponent> flipbook = nullptr;
	UPROPERTY(EditAnywhere)TObjectPtr <UBoxComponent> collision = nullptr;
	//Audio
	UPROPERTY(EditAnywhere)TObjectPtr<UAudioComponent> audio = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<USoundBase> pickUpSound = nullptr;

	AItemTriggerBox();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
};
