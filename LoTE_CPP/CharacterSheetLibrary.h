// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "Components/Button.h"
#include "Math/Color.h"
#include "HAL/PlatformFilemanager.h"
#include "HAL/FileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "CharacterSheetLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LOTE_API UCharacterSheetLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		static void ChangeSkill(bool positive, UTextBlock* text, UTextBlock* PD);
		UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		static bool SaveToFile(FString SaveDirectory, FString FileName, TArray<FString>SaveText, bool AllowOverWriting);
		UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		static FString GetTextValue(UTextBlock* text);
		UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		static FString GetEditableTextValue(UEditableText* text);
		UFUNCTION(BlueprintCallable, Category = "LoTECollection")	
		static FString ReadLineFromFile(FString SaveDirectory, FString FileName);
		UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		static TArray<FString> MakeAnArray(FString SaveDirectory, FString FileName);
		UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		static bool SaveLineToFile(FString SaveDirectory, FString FileName, FString SaveText, bool AllowOverWriting);
		UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		static TArray<FString> LoadFileToStringArray(FString Filename, FString SaveDirectory);
		UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		static FString LoadFileToString(FString Filename, FString SaveDirectory);
		UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		static int SubstractInt(int randomInt, int minus);
		UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		static int AddInt(int randomInt, int plus);
		UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		static bool IsThereEnoughGold(int currentGold, int price);
		UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		static void ChangeText(FString text, UTextBlock* changedText);
		UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		static int SafeFStringToInt(FString text);
		UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		static bool BuySellItem(UButton* Button, UTextBlock* gold, bool condition, int price);
};
