// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/TextBlock.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "LoTEFunctionLibrary.generated.h"



UENUM(BlueprintType)
enum class EResource : uint8 {
	MANA			UMETA(DisplayName = "Mana"),
	MOVE			UMETA(DisplayName = "Move"),
	PA				UMETA(DisplayName = "PA"),
	SANITY			UMETA(DisplayName = "Sanity"),
	RESISTANCE		UMETA(DisplayName = "Resistance"),

};
/**
 * 
 */
UCLASS()
class LOTE_API ULoTEFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		static void ChangeStat(bool positive, UTextBlock* text, UTextBlock* PD);

		UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		static void SetValue(UTextBlock* changedText, UTextBlock* mainStat, EResource Resource);

		UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		static void SetSmartsyThings(UTextBlock* changedText, UTextBlock* mainStat, UTextBlock* secondStat, bool useBoth);

		UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		static float SetXDistance(float enemyX, float playerX);

		UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		static float SetYDistance(float enemyY, float playerY);



};
