// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LoTECharacter.h"
#include "InteractableInterface.h"
#include "MonsterCharacter.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EMood : uint8 {
	HOSTILE			UMETA(DisplayName = "Hostile"),
	FRIENDLY		UMETA(DisplayName = "Friendly"),

};

UCLASS()
class LOTE_API AMonsterCharacter : public ALoTECharacter, public IInteractableInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMood CurrentMood;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "LoTENative")
		void ForceDialogue();
		void ForceDialogue_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "LoTENative")
		void LastBreathEvent();
		void LastBreathEvent_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "LoTENative")
		void CheckDialogueLine();
		void CheckDialogueLine_Implementation();
	
};
