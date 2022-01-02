// articy Software GmbH & Co. KG
/** This code file was generated by ArticyImporter. Changes to this file will get lost once the code is regenerated. */

#pragma once

#include "CoreUObject.h"
#include "Lote_OmateInterfaces.generated.h"


/** UNINTERFACE generated from Articy Podstawowe własności bohatera Feature */
UINTERFACE(MinimalAPI, BlueprintType, Category="Lote_Omate Feature Interfaces", meta=(CannotImplementInterfaceInBlueprint))
class ULote_OmateObjectWithDefaultBasicCharacterFeatureFeature : public UInterface { GENERATED_BODY() };
class ILote_OmateObjectWithDefaultBasicCharacterFeatureFeature
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable)
	virtual class ULote_OmateDefaultBasicCharacterFeatureFeature* GetFeatureDefaultBasicCharacterFeature() const
	{
		return nullptr;
	}
};

/** UNINTERFACE generated from Articy Rozszerzone własności bohatera Feature */
UINTERFACE(MinimalAPI, BlueprintType, Category="Lote_Omate Feature Interfaces", meta=(CannotImplementInterfaceInBlueprint))
class ULote_OmateObjectWithDefaultExtendedCharacterFeatureFeature : public UInterface { GENERATED_BODY() };
class ILote_OmateObjectWithDefaultExtendedCharacterFeatureFeature
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable)
	virtual class ULote_OmateDefaultExtendedCharacterFeatureFeature* GetFeatureDefaultExtendedCharacterFeature() const
	{
		return nullptr;
	}
};
