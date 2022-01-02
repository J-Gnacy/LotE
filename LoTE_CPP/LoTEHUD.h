// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LoTEHUD.generated.h"

/**
 * 
 */
UCLASS()
class LOTE_API ALoTEHUD : public AHUD
{
	GENERATED_BODY()

			public:
	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
};
