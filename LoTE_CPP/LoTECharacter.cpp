// Copyright Epic Games, Inc. All Rights Reserved.

#include "LoTECharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"

ALoTECharacter::ALoTECharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ALoTECharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = TopDownCameraComponent->GetComponentLocation();
				FVector EndLocation = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}

FCharacterStats ALoTECharacter::SetStats(int nStrength, int nDexterity, int nSpeed, int nEndurance, int nSmarts, int nPsyche, int nSenses)
{
	Stats.strength = nStrength;
	Stats.dexterity = nDexterity;
	Stats.speed = nSpeed;
	Stats.endurance = nEndurance;
	Stats.smarts = nSmarts;
	Stats.psyche = nPsyche;
	Stats.senses = nSenses;

	RefreshStats();

	return Stats;
}


void ALoTECharacter::SetStatsStruct(FCharacterStats Nstats)
{
	Stats=Nstats;
	RefreshStats();
}

void ALoTECharacter::SetSkillsStruct(FSkills Nskills)
{
	Skills=Nskills;
}

FCharacterStats ALoTECharacter::GetStatsStruct()
{
	return Stats;
}

FSkills ALoTECharacter::GetSkillsStruct()
{
	return Skills;
}

FSkills ALoTECharacter::SetSkills(int nWpolearm, int nW2handed, int nW1handed, int nWlight, int nWthrowing, int nWshooting, int nDodging, int nBrawling, int nAntimagic, int nWhiteMagic, int nIllusions, int nKriomancy, int nNecromancy, int nPiromancy, int nTelekinesis, int nTransmutation, int nDivination, int nSurvival, int nTraps, int nTracking, int nAcrobatics, int nRiding, int nHealing, int nNavigation, int nSwimming, int nInvestigation, int nPerception, int nClimbing, int nBoating, int nBluff, int nLeadership, int nEtiquette, int nPersuasion, int nPerformance, int nIntimidation, int nForgery, int nThievery, int nLockpicking, int nDisguise, int nStealth, int nHistory, int nEngineering, int nLinguistics, int nMagic, int nOccultism, int nLaw, int nNature, int nTactics, int nEnchanting, int nAlchemy, int nArtistic, int nCooking, int nSmithing, int nTailoring, int nTrading, int nFurriery)
{
	Skills.CombatSkills.wpolearm = nWpolearm;
	Skills.CombatSkills.w2handed = nW2handed;
	Skills.CombatSkills.w1handed = nW1handed;
	Skills.CombatSkills.wlight = nWlight;
	Skills.CombatSkills.wthrowing = nWthrowing;
	Skills.CombatSkills.wshooting = nWshooting;
	Skills.CombatSkills.dodging = nDodging;
	Skills.CombatSkills.brawling = nBrawling;
	Skills.MagicSkills.antimagic = nAntimagic;
	Skills.MagicSkills.whiteMagic = nWhiteMagic;
	Skills.MagicSkills.illusions = nIllusions;
	Skills.MagicSkills.kriomancy = nKriomancy;
	Skills.MagicSkills.necromancy = nNecromancy;
	Skills.MagicSkills.piromancy = nPiromancy;
	Skills.MagicSkills.telekinesis = nTelekinesis;
	Skills.MagicSkills.transmutation = nTransmutation;
	Skills.MagicSkills.divination = nDivination;
	Skills.HuntingSkills.survival = nSurvival;
	Skills.HuntingSkills.traps = nTraps;
	Skills.HuntingSkills.tracking = nTracking;
	Skills.BaseSkills.acrobatics = nAcrobatics;
	Skills.BaseSkills.riding = nRiding;
	Skills.BaseSkills.healing = nHealing;
	Skills.BaseSkills.navigation = nNavigation;
	Skills.BaseSkills.swimming = nSwimming;
	Skills.BaseSkills.investigation = nInvestigation;
	Skills.BaseSkills.perception = nPerception;
	Skills.BaseSkills.climbing = nClimbing;
	Skills.BaseSkills.boating = nBoating;
	Skills.SocialSkills.bluff = nBluff;
	Skills.SocialSkills.leadership = nLeadership;
	Skills.SocialSkills.etiquette = nEtiquette;
	Skills.SocialSkills.persuasion = nPersuasion;
	Skills.SocialSkills.performance = nPerformance;
	Skills.SocialSkills.intimidation = nIntimidation;
	Skills.CriminalSkills.forgery = nForgery;
	Skills.CriminalSkills.thievery = nThievery;
	Skills.CriminalSkills.lockpicking = nLockpicking;
	Skills.CriminalSkills.disguise = nDisguise;
	Skills.CriminalSkills.stealth = nStealth;
	Skills.BookSmartsSkills.history = nHistory;
	Skills.BookSmartsSkills.engineering = nEngineering;
	Skills.BookSmartsSkills.linguistics = nLinguistics;
	Skills.BookSmartsSkills.magic = nMagic;
	Skills.BookSmartsSkills.occultism = nOccultism;
	Skills.BookSmartsSkills.law = nLaw;
	Skills.BookSmartsSkills.nature = nNature;
	Skills.BookSmartsSkills.tactics = nTactics;
	Skills.BookSmartsSkills.enchanting = nEnchanting;
	Skills.BookSmartsSkills.alchemy = nAlchemy;
	Skills.ProfessionalSkills.artistic = nArtistic;
	Skills.ProfessionalSkills.cooking = nCooking;
	Skills.ProfessionalSkills.smithing = nSmithing;
	Skills.ProfessionalSkills.tailoring = nTailoring;
	Skills.ProfessionalSkills.trading = nTrading;
	Skills.ProfessionalSkills.furriery = nFurriery;

	return Skills;
}

void ALoTECharacter::InitializeStats(TArray<FString> StatsArray)
{


	FString tmp;
	characterName = StatsArray[1];
	tmp = StatsArray[3];
	if (tmp.IsNumeric())
	{
		gold = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[5];
	if (tmp.IsNumeric())
	{
		Stats.strength = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[7];
	if (tmp.IsNumeric())
	{
		Stats.dexterity = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[9];
	if (tmp.IsNumeric())
	{
		Stats.speed = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[11];
	if (tmp.IsNumeric())
	{
		Stats.endurance = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[13];
	if (tmp.IsNumeric())
	{
		Stats.smarts = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[15];
	if (tmp.IsNumeric())
	{
		Stats.psyche = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[17];
	if (tmp.IsNumeric())
	{
		Stats.senses = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[19];
	if (tmp.IsNumeric())
	{
		move = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[21];
	if (tmp.IsNumeric())
	{
		actionPoints = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[23];
	if (tmp.IsNumeric())
	{
		healthPoints = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[25];
	if (tmp.IsNumeric())
	{
		resistance = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[27];
	if (tmp.IsNumeric())
	{
		talentsLimit = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[29];
	if (tmp.IsNumeric())
	{
		sanity = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[31];
	if (tmp.IsNumeric())
	{
		fortuneCards = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[33];
	if (tmp.IsNumeric())
	{
		Skills.CombatSkills.wpolearm = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[35];
	if (tmp.IsNumeric())
	{
		Skills.CombatSkills.w2handed = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[37];
	if (tmp.IsNumeric())
	{
		Skills.CombatSkills.w1handed = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[39];
	if (tmp.IsNumeric())
	{
		Skills.CombatSkills.wlight = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[41];
	if (tmp.IsNumeric())
	{
		Skills.CombatSkills.wthrowing = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[43];
	if (tmp.IsNumeric())
	{
		Skills.CombatSkills.wshooting = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[45];
	if (tmp.IsNumeric())
	{
		Skills.CombatSkills.dodging = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[47];
	if (tmp.IsNumeric())
	{
		Skills.CombatSkills.brawling = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[49];
	if (tmp.IsNumeric())
	{
		Skills.MagicSkills.antimagic = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[51];
	if (tmp.IsNumeric())
	{
		Skills.MagicSkills.whiteMagic = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[53];
	if (tmp.IsNumeric())
	{
		Skills.MagicSkills.illusions = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[55];
	if (tmp.IsNumeric())
	{
		Skills.MagicSkills.kriomancy = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[57];
	if (tmp.IsNumeric())
	{
		Skills.MagicSkills.necromancy = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[59];
	if (tmp.IsNumeric())
	{
		Skills.MagicSkills.piromancy = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[61];
	if (tmp.IsNumeric())
	{
		Skills.MagicSkills.telekinesis = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[63];
	if (tmp.IsNumeric())
	{
		Skills.MagicSkills.transmutation = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[65];
	if (tmp.IsNumeric())
	{
		Skills.MagicSkills.divination = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[67];
	if (tmp.IsNumeric())
	{
		Skills.HuntingSkills.survival = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[69];
	if (tmp.IsNumeric())
	{
		Skills.HuntingSkills.traps = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[71];
	if (tmp.IsNumeric())
	{
		Skills.HuntingSkills.tracking = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[73];
	if (tmp.IsNumeric())
	{
		Skills.BaseSkills.acrobatics = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[75];
	if (tmp.IsNumeric())
	{
		Skills.BaseSkills.riding = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[77];
	if (tmp.IsNumeric())
	{
		Skills.BaseSkills.healing = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[79];
	if (tmp.IsNumeric())
	{
		Skills.BaseSkills.navigation = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[81];
	if (tmp.IsNumeric())
	{
		Skills.BaseSkills.swimming = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[83];
	if (tmp.IsNumeric())
	{
		Skills.BaseSkills.investigation = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[85];
	if (tmp.IsNumeric())
	{
		Skills.BaseSkills.perception = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[87];
	if (tmp.IsNumeric())
	{
		Skills.BaseSkills.climbing = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[89];
	if (tmp.IsNumeric())
	{
		Skills.BaseSkills.boating = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[91];
	if (tmp.IsNumeric())
	{
		Skills.SocialSkills.bluff = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[93];
	if (tmp.IsNumeric())
	{
		Skills.SocialSkills.leadership = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[95];
	if (tmp.IsNumeric())
	{
		Skills.SocialSkills.etiquette = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[97];
	if (tmp.IsNumeric())
	{
		Skills.SocialSkills.persuasion = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[99];
	if (tmp.IsNumeric())
	{
		Skills.SocialSkills.performance = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[101];
	if (tmp.IsNumeric())
	{
		Skills.SocialSkills.intimidation = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[103];
	if (tmp.IsNumeric())
	{
		Skills.CriminalSkills.forgery = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[105];
	if (tmp.IsNumeric())
	{
		Skills.CriminalSkills.thievery = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[107];
	if (tmp.IsNumeric())
	{
		Skills.CriminalSkills.lockpicking = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[109];
	if (tmp.IsNumeric())
	{
		Skills.CriminalSkills.disguise = FCString::Atoi(*tmp);
	}


	tmp = StatsArray[113];
	if (tmp.IsNumeric())
	{
		Skills.CriminalSkills.stealth = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[115];
	if (tmp.IsNumeric())
	{
		Skills.BookSmartsSkills.history = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[117];
	if (tmp.IsNumeric())
	{
		Skills.BookSmartsSkills.engineering = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[119];
	if (tmp.IsNumeric())
	{
		Skills.BookSmartsSkills.linguistics = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[121];
	if (tmp.IsNumeric())
	{
		Skills.BookSmartsSkills.magic = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[123];
	if (tmp.IsNumeric())
	{
		Skills.BookSmartsSkills.occultism = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[125];
	if (tmp.IsNumeric())
	{
		Skills.BookSmartsSkills.law = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[127];
	if (tmp.IsNumeric())
	{
		Skills.BookSmartsSkills.nature = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[129];
	if (tmp.IsNumeric())
	{
		Skills.BookSmartsSkills.tactics = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[131];
	if (tmp.IsNumeric())
	{
		Skills.BookSmartsSkills.enchanting = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[133];
	if (tmp.IsNumeric())
	{
		Skills.BookSmartsSkills.alchemy = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[135];
	if (tmp.IsNumeric())
	{
		Skills.ProfessionalSkills.artistic = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[137];
	if (tmp.IsNumeric())
	{
		Skills.ProfessionalSkills.cooking = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[139];
	if (tmp.IsNumeric())
	{
		Skills.ProfessionalSkills.smithing = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[141];
	if (tmp.IsNumeric())
	{
		Skills.ProfessionalSkills.tailoring = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[143];
	if (tmp.IsNumeric())
	{
		Skills.ProfessionalSkills.trading = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[145];
	if (tmp.IsNumeric())
	{
		Skills.ProfessionalSkills.furriery = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[147];
	if (tmp.IsNumeric())
	{
		Skills.ProfessionalSkills.professionalOther = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[149];
	if (tmp.IsNumeric())
	{
		PD = FCString::Atoi(*tmp);
	}

	tmp = StatsArray[151];
	if (tmp.IsNumeric())
	{
		mana = FCString::Atoi(*tmp);
	}

	WUsed = WType::BRAWLING;
	RefreshStats();
}

FString ALoTECharacter::statIntToString(int stat)
{

	return FString::FromInt(stat);
}

int ALoTECharacter::GetMaxHP()
{
	return healthPoints;
}

int ALoTECharacter::GetCurrentHP()
{
	return currentHP;
}

int ALoTECharacter::GetMaxActionPoints()
{
	return actionPoints;
}

int ALoTECharacter::GetCurrentActionPoints()
{
	return currentActionPoints;
}

int ALoTECharacter::GetMaxMove()
{
	return move;
}

int ALoTECharacter::GetCurrentMove()
{
	return currentMove;
}

int ALoTECharacter::GetMaxSanity()
{
	return sanity;
}

int ALoTECharacter::GetCurrentSanity()
{
	return currentSanity;
}

int ALoTECharacter::GetMaxMana()
{
	return mana;
}

int ALoTECharacter::GetCurrentMana()
{
	return currentMana;
}

int ALoTECharacter::GetMaxFortuneCards()
{
	return fortuneCards;
}

void ALoTECharacter::RefreshStats()
{

	move = 3 + Stats.speed;
	actionPoints = 3 + Stats.speed;
	healthPoints = 3 + 5 * Stats.endurance;
	resistance = Stats.endurance / 2;
	talentsLimit = 70 * Stats.smarts;
	sanity = 3 + 5 * Stats.psyche;
	mana = 2 * Stats.psyche;
	fortuneCards = (Stats.senses + Stats.smarts) / 2;

	currentMove = move;
	currentActionPoints = actionPoints;
	currentHP = healthPoints;
	currentSanity = sanity;
	currentMana = mana;
	currentFortuneCards = fortuneCards;

	tempAttackBonus = 0;
	attackBonus = 0;
	tempDamageBonus = 0;
	damageBonus = 0;
	damageRolled = 0;
	attackRolled = 0;

	currentMoveBonus = 0;
	maxMoveBonus = 0;
	currentDefenseBonus = 0;
	maxDefenseBonus = 0;
	currentRollBonus = 0;
	maxRollBonus = 0;
	//initiative = 0;
	//initiativeBonus = 0;

	minWeaponDmg = 1 + Stats.strength;
	maxWeaponDmg = 1 + Stats.strength;
	attRolled = 0;
	dmgRolled = 0;
	maxActions = 2;
	maxPurchasableActions = 2;
	currentPurchasableActions = maxPurchasableActions;
	currentActions = maxActions;
	attackUsed = false;
	catchUsed = false;
	tripUsed = false;
	pushUsed = false;
	disarmUsed = false;
	aimUsed = false;
	spellcastingUsed = false;
	moveUsed = false;
	runUsed = false;

}

int ALoTECharacter::GetCurrentFortuneCards()
{
	return currentFortuneCards;
}

int ALoTECharacter::GetPD()
{

	return PD;
}

int ALoTECharacter::GetStrength()
{
	return Stats.strength;
}

int ALoTECharacter::GetDexterity()
{
	return Stats.dexterity;
}

int ALoTECharacter::GetSpeed()
{
	return Stats.speed;
}

int ALoTECharacter::GetEndurance()
{
	return Stats.endurance;
}

int ALoTECharacter::GetSmarts()
{
	return Stats.smarts;
}

int ALoTECharacter::GetPsyche()
{
	return Stats.psyche;
}

int ALoTECharacter::GetSenses()
{
	return Stats.senses;
}

int ALoTECharacter::GetGold()
{
	return gold;
}

int ALoTECharacter::GetResistance()
{
	return resistance;
}

int ALoTECharacter::GetDmgNegation()
{
	return dmgNegation;
}

int ALoTECharacter::GetTalentsLimit()
{
	return talentsLimit;
}

int ALoTECharacter::GetWPolearm()
{
	return Skills.CombatSkills.wpolearm;
}

int ALoTECharacter::GetW2Handed()
{
	return Skills.CombatSkills.w2handed;
}

int ALoTECharacter::GetW1Handed()
{
	return Skills.CombatSkills.w1handed;
}

int ALoTECharacter::GetWLight()
{
	return Skills.CombatSkills.wlight;
}

int ALoTECharacter::GetWThrowing()
{
	return Skills.CombatSkills.wthrowing;
}

int ALoTECharacter::GetWShooting()
{
	return Skills.CombatSkills.wshooting;
}

int ALoTECharacter::GetDodging()
{
	return Skills.CombatSkills.dodging;
}

int ALoTECharacter::GetBrawling()
{
	return Skills.CombatSkills.brawling;
}

int ALoTECharacter::GetAntimagic()
{
	return Skills.MagicSkills.antimagic;
}

int ALoTECharacter::GetWhiteMagic()
{
	return Skills.MagicSkills.whiteMagic;
}

int ALoTECharacter::GetIllusions()
{
	return Skills.MagicSkills.illusions;
}

int ALoTECharacter::GetKriomancy()
{
	return Skills.MagicSkills.kriomancy;
}

int ALoTECharacter::GetNecromancy()
{
	return Skills.MagicSkills.necromancy;
}

int ALoTECharacter::GetPiromancy()
{
	return Skills.MagicSkills.piromancy;
}

int ALoTECharacter::GetTelekinesis()
{
	return Skills.MagicSkills.telekinesis;
}

int ALoTECharacter::GetTransmutation()
{
	return Skills.MagicSkills.transmutation;
}

int ALoTECharacter::GetDivination()
{
	return Skills.MagicSkills.divination;
}

int ALoTECharacter::GetSurvival()
{
	return Skills.HuntingSkills.survival;
}

int ALoTECharacter::GetTraps()
{
	return Skills.HuntingSkills.traps;
}

int ALoTECharacter::GetTracking()
{
	return Skills.HuntingSkills.tracking;
}

int ALoTECharacter::GetRiding()
{
	return Skills.BaseSkills.riding;
}

int ALoTECharacter::GetHealing()
{
	return Skills.BaseSkills.healing;
}

int ALoTECharacter::GetNavigation()
{
	return Skills.BaseSkills.navigation;
}

int ALoTECharacter::GetSwimming()
{
	return Skills.BaseSkills.swimming;
}

int ALoTECharacter::GetInvestigation()
{
	return Skills.BaseSkills.investigation;
}

int ALoTECharacter::GetPerception()
{
	return Skills.BaseSkills.perception;
}

int ALoTECharacter::GetClimbing()
{
	return Skills.BaseSkills.climbing;
}

int ALoTECharacter::GetBoating()
{
	return Skills.BaseSkills.boating;
}

int ALoTECharacter::GetBluff()
{
	return Skills.SocialSkills.bluff;
}

int ALoTECharacter::GetLeadership()
{
	return Skills.SocialSkills.leadership;
}

int ALoTECharacter::GetEtiquette()
{
	return Skills.SocialSkills.etiquette;
}

int ALoTECharacter::GetPersuasion()
{
	return Skills.SocialSkills.persuasion;
}

int ALoTECharacter::GetPerformance()
{
	return Skills.SocialSkills.performance;
}

int ALoTECharacter::GetIntimidation()
{
	return Skills.SocialSkills.intimidation;
}

int ALoTECharacter::GetForgery()
{
	return Skills.CriminalSkills.forgery;
}

int ALoTECharacter::GetThievery()
{
	return Skills.CriminalSkills.thievery;
}

int ALoTECharacter::GetLockpicking()
{
	return Skills.CriminalSkills.lockpicking;
}

int ALoTECharacter::GetDisguise()
{
	return Skills.CriminalSkills.disguise;
}

int ALoTECharacter::GetStealth()
{
	return Skills.CriminalSkills.stealth;
}

int ALoTECharacter::GetHistory()
{
	return Skills.BookSmartsSkills.history;
}

int ALoTECharacter::GetEngineering()
{
	return Skills.BookSmartsSkills.engineering;
}

int ALoTECharacter::GetLinguistics()
{
	return Skills.BookSmartsSkills.linguistics;
}

int ALoTECharacter::GetMagic()
{
	return Skills.BookSmartsSkills.magic;
}

int ALoTECharacter::GetOccultism()
{
	return Skills.BookSmartsSkills.occultism;
}

int ALoTECharacter::GetLaw()
{
	return Skills.BookSmartsSkills.law;
}

int ALoTECharacter::GetNature()
{
	return Skills.BookSmartsSkills.nature;
}

int ALoTECharacter::GetTactics()
{
	return Skills.BookSmartsSkills.tactics;
}

int ALoTECharacter::GetEnchanting()
{
	return Skills.BookSmartsSkills.enchanting;
}

int ALoTECharacter::GetAlchemy()
{
	return Skills.BookSmartsSkills.alchemy;
}

int ALoTECharacter::GetArtistic()
{
	return Skills.ProfessionalSkills.artistic;
}

int ALoTECharacter::GetCooking()
{
	return Skills.ProfessionalSkills.cooking;
}

int ALoTECharacter::GetSmithing()
{
	return Skills.ProfessionalSkills.smithing;
}

int ALoTECharacter::GetTailoring()
{
	return Skills.ProfessionalSkills.tailoring;
}

int ALoTECharacter::GetTrading()
{
	return Skills.ProfessionalSkills.trading;
}

int ALoTECharacter::GetFurriery()
{
	return Skills.ProfessionalSkills.furriery;
}

int ALoTECharacter::GetProfessionalOther()
{
	return Skills.ProfessionalSkills.professionalOther;
}

FString ALoTECharacter::GetCharacterName()
{
	return characterName;
}

void ALoTECharacter::SetMaxHP(int tmp)
{
	healthPoints = tmp;
}

void ALoTECharacter::SetCurrentHP(int tmp)
{
	if (tmp > healthPoints)
	{
		currentHP = healthPoints;
	}
	else { currentHP = tmp; }

}

void ALoTECharacter::SetMaxActionPoints(int tmp)
{
	actionPoints = tmp;
}

void ALoTECharacter::SetCurrentActionPoints(int tmp)
{
	if (tmp > actionPoints)
	{
		currentActionPoints = actionPoints;
	}
	else { currentActionPoints = tmp; }

}

void ALoTECharacter::SetMaxMove(int tmp)
{
	move = tmp;
}

void ALoTECharacter::SetCurrentMove(int tmp)
{
	currentMove = tmp;
}

void ALoTECharacter::SetMaxSanity(int tmp)
{
	sanity = tmp;
}

void ALoTECharacter::SetCurrentSanity(int tmp)
{
	if (tmp > sanity)
	{
		currentHP = sanity;
	}
	else { currentSanity = tmp; }

}

void ALoTECharacter::SetMaxMana(int tmp)
{
	mana = tmp;
}

void ALoTECharacter::SetCurrentMana(int tmp)
{
	if (tmp > mana)
	{
		currentMana = mana;
	}
	else {
		currentMana = tmp;
	}

}

void ALoTECharacter::SetMaxFortuneCards(int tmp)
{
	fortuneCards = tmp;
}

void ALoTECharacter::SetCurrentFortuneCards(int tmp)
{
	currentFortuneCards = tmp;
}

void ALoTECharacter::SetPD(int tmp)
{
	PD = tmp;
}

void ALoTECharacter::SetStrength(int tmp)
{
	Stats.strength = tmp;
}

void ALoTECharacter::SetDexterity(int tmp)
{
	Stats.dexterity = tmp;
}

void ALoTECharacter::SetSpeed(int tmp)
{
	Stats.speed = tmp;
}

void ALoTECharacter::SetEndurance(int tmp)
{
	Stats.endurance = tmp;
}

void ALoTECharacter::SetSmarts(int tmp)
{
	Stats.smarts = tmp;
}

void ALoTECharacter::SetPsyche(int tmp)
{
	Stats.psyche = tmp;
}

void ALoTECharacter::SetSenses(int tmp)
{
	Stats.senses = tmp;
}

void ALoTECharacter::SetGold(int tmp)
{
	gold = tmp;
}

void ALoTECharacter::SetResistance(int tmp)
{
	resistance = tmp;
}

void ALoTECharacter::SetDmgNegation(int tmp)
{
	dmgNegation = tmp;
}

void ALoTECharacter::SetTalentsLimit(int tmp)
{
	talentsLimit = tmp;
}

void ALoTECharacter::SetWPolearm(int tmp)
{
	Skills.CombatSkills.wpolearm = tmp;
}

void ALoTECharacter::SetW2Handed(int tmp)
{
	Skills.CombatSkills.w2handed = tmp;
}

void ALoTECharacter::SetW1Handed(int tmp)
{
	Skills.CombatSkills.w1handed = tmp;
}

void ALoTECharacter::SetWLight(int tmp)
{
	Skills.CombatSkills.wlight = tmp;
}

void ALoTECharacter::SetWThrowing(int tmp)
{
	Skills.CombatSkills.wthrowing = tmp;
}

void ALoTECharacter::SetWShooting(int tmp)
{
	Skills.CombatSkills.wshooting = tmp;
}

void ALoTECharacter::SetDodging(int tmp)
{
	Skills.CombatSkills.dodging = tmp;
}

void ALoTECharacter::SetBrawling(int tmp)
{
	Skills.CombatSkills.brawling = tmp;
}

void ALoTECharacter::SetAntimagic(int tmp)
{
	Skills.MagicSkills.antimagic = tmp;
}

void ALoTECharacter::SetWhiteMagic(int tmp)
{
	Skills.MagicSkills.whiteMagic = tmp;
}

void ALoTECharacter::SetIllusions(int tmp)
{
	Skills.MagicSkills.illusions = tmp;
}

void ALoTECharacter::SetKriomancy(int tmp)
{
	Skills.MagicSkills.kriomancy = tmp;
}

void ALoTECharacter::SetNecromancy(int tmp)
{
	Skills.MagicSkills.necromancy = tmp;
}

void ALoTECharacter::SetPiromancy(int tmp)
{
	Skills.MagicSkills.piromancy = tmp;
}

void ALoTECharacter::SetTelekinesis(int tmp)
{
	Skills.MagicSkills.telekinesis = tmp;
}

void ALoTECharacter::SetTransmutation(int tmp)
{
	Skills.MagicSkills.transmutation = tmp;
}

void ALoTECharacter::SetDivination(int tmp)
{
	Skills.MagicSkills.divination = tmp;
}

void ALoTECharacter::SetSurvival(int tmp)
{
	Skills.HuntingSkills.survival = tmp;
}

void ALoTECharacter::SetTraps(int tmp)
{
	Skills.HuntingSkills.traps = tmp;
}

void ALoTECharacter::SetTracking(int tmp)
{
	Skills.HuntingSkills.tracking = tmp;
}

void ALoTECharacter::SetRiding(int tmp)
{
	Skills.BaseSkills.riding = tmp;
}

void ALoTECharacter::SetHealing(int tmp)
{
	Skills.BaseSkills.healing = tmp;
}

void ALoTECharacter::SetNavigation(int tmp)
{
	Skills.BaseSkills.navigation = tmp;
}

void ALoTECharacter::SetSwimming(int tmp)
{
	Skills.BaseSkills.swimming = tmp;
}

void ALoTECharacter::SetInvestigation(int tmp)
{
	Skills.BaseSkills.investigation = tmp;
}

void ALoTECharacter::SetPerception(int tmp)
{
	Skills.BaseSkills.perception = tmp;
}

void ALoTECharacter::SetClimbing(int tmp)
{
	Skills.BaseSkills.climbing = tmp;
}

void ALoTECharacter::SetBoating(int tmp)
{
	Skills.BaseSkills.boating = tmp;
}

void ALoTECharacter::SetBluff(int tmp)
{
	Skills.SocialSkills.bluff = tmp;
}

void ALoTECharacter::SetLeadership(int tmp)
{
	Skills.SocialSkills.leadership = tmp;
}

void ALoTECharacter::SetEtiquette(int tmp)
{
	Skills.SocialSkills.etiquette = tmp;
}

void ALoTECharacter::SetPersuasion(int tmp)
{
	Skills.SocialSkills.persuasion = tmp;
}

void ALoTECharacter::SetPerformance(int tmp)
{
	Skills.SocialSkills.performance = tmp;
}

void ALoTECharacter::SetIntimidation(int tmp)
{
	Skills.SocialSkills.intimidation = tmp;
}

void ALoTECharacter::SetForgery(int tmp)
{
	Skills.CriminalSkills.forgery = tmp;
}

void ALoTECharacter::SetThievery(int tmp)
{
	Skills.CriminalSkills.thievery = tmp;
}

void ALoTECharacter::SetLockpicking(int tmp)
{
	Skills.CriminalSkills.lockpicking = tmp;
}

void ALoTECharacter::SetDisguise(int tmp)
{
	Skills.CriminalSkills.disguise = tmp;
}

void ALoTECharacter::SetStealth(int tmp)
{
	Skills.CriminalSkills.stealth = tmp;
}

void ALoTECharacter::SetHistory(int tmp)
{
	Skills.BookSmartsSkills.history = tmp;
}

void ALoTECharacter::SetEngineering(int tmp)
{
	Skills.BookSmartsSkills.engineering = tmp;
}

void ALoTECharacter::SetLinguistics(int tmp)
{
	Skills.BookSmartsSkills.linguistics = tmp;
}

void ALoTECharacter::SetMagic(int tmp)
{
	Skills.BookSmartsSkills.magic = tmp;
}

void ALoTECharacter::SetOccultism(int tmp)
{
	Skills.BookSmartsSkills.occultism = tmp;
}

void ALoTECharacter::SetLaw(int tmp)
{
	Skills.BookSmartsSkills.law = tmp;
}

void ALoTECharacter::SetNature(int tmp)
{
	Skills.BookSmartsSkills.nature = tmp;
}

void ALoTECharacter::SetTactics(int tmp)
{
	Skills.BookSmartsSkills.tactics = tmp;
}

void ALoTECharacter::SetEnchanting(int tmp)
{
	Skills.BookSmartsSkills.enchanting = tmp;
}

void ALoTECharacter::SetAlchemy(int tmp)
{
	Skills.BookSmartsSkills.alchemy = tmp;
}

void ALoTECharacter::SetArtistic(int tmp)
{
	Skills.ProfessionalSkills.artistic = tmp;
}

void ALoTECharacter::SetCooking(int tmp)
{
	Skills.ProfessionalSkills.cooking = tmp;
}

void ALoTECharacter::SetSmithing(int tmp)
{
	Skills.ProfessionalSkills.smithing = tmp;
}

void ALoTECharacter::SetTailoring(int tmp)
{
	Skills.ProfessionalSkills.tailoring = tmp;
}

void ALoTECharacter::SetTrading(int tmp)
{
	Skills.ProfessionalSkills.trading = tmp;
}

void ALoTECharacter::SetFurriery(int tmp)
{
	Skills.ProfessionalSkills.furriery = tmp;
}

void ALoTECharacter::SetProfessionalOther(int tmp)
{
	Skills.ProfessionalSkills.professionalOther = tmp;
}

int ALoTECharacter::GetAcrobatics()
{
	return Skills.BaseSkills.acrobatics;
}

void ALoTECharacter::SetAcrobatics(int tmp)
{
	Skills.BaseSkills.acrobatics = tmp;
}


void ALoTECharacter::ReloadStats(TArray<UTextBlock*> Textblocks)
{
	StatsIntoArrayAlphabetically();
	//	FString tmp;
	//	int tmp2;
	for (int i = 0; i < 65; i++)
	{
		//tmp2 = CStats[i];
		//tmp = FString::FromInt(tmp2);
		//UE_LOG(LogTemp, Warning, TEXT("shit2 is %s"), *tmp);
		//Textblocks[i]->SetText(FText::FromString(FString::FromInt(CStats[i])));
	}
	//Textblocks[0]->SetText(FText::FromString(FString::FromInt(Skills.BaseSkills.acrobatics)));


}

void ALoTECharacter::StatsIntoArrayAlphabetically()
{
	int elka = 7;
	CStats.Add(5);
	CStats.Add(elka);
	CStats[0] = Skills.BaseSkills.acrobatics;
	CStats.Add(Skills.BookSmartsSkills.alchemy);
	CStats.Add(Skills.MagicSkills.antimagic);
	CStats.Add(Skills.ProfessionalSkills.artistic);
	CStats.Add(Skills.SocialSkills.bluff);
	CStats.Add(Skills.BaseSkills.boating);
	CStats.Add(Skills.CombatSkills.brawling);
	CStats.Add(Skills.BaseSkills.climbing);
	CStats.Add(Skills.ProfessionalSkills.cooking);
	CStats.Add(Stats.dexterity);
	CStats.Add(Skills.CriminalSkills.disguise);
	CStats.Add(Skills.MagicSkills.divination);
	CStats.Add(Skills.CombatSkills.dodging);
	CStats.Add(Skills.BookSmartsSkills.enchanting);
	CStats.Add(Stats.endurance);
	CStats.Add(Skills.BookSmartsSkills.engineering);
	CStats.Add(Skills.SocialSkills.etiquette);
	CStats.Add(Skills.CriminalSkills.forgery);
	CStats.Add(Skills.ProfessionalSkills.furriery);
	CStats.Add(Skills.BaseSkills.healing);
	CStats.Add(Skills.BookSmartsSkills.history);
	CStats.Add(Skills.MagicSkills.illusions);
	CStats.Add(Skills.SocialSkills.intimidation);
	CStats.Add(Skills.BaseSkills.investigation);
	CStats.Add(Skills.MagicSkills.kriomancy);
	CStats.Add(Skills.BookSmartsSkills.law);
	CStats.Add(Skills.SocialSkills.leadership);
	CStats.Add(Skills.BookSmartsSkills.linguistics);
	CStats.Add(Skills.CriminalSkills.lockpicking);
	CStats.Add(Skills.BookSmartsSkills.magic);
	CStats.Add(Skills.BookSmartsSkills.nature);
	CStats.Add(Skills.BaseSkills.navigation);
	CStats.Add(Skills.MagicSkills.necromancy);
	CStats.Add(Skills.BookSmartsSkills.occultism);
	CStats.Add(PD);
	CStats.Add(Skills.BaseSkills.perception);
	CStats.Add(Skills.SocialSkills.performance);
	CStats.Add(Skills.SocialSkills.persuasion);
	CStats.Add(Skills.MagicSkills.piromancy);
	CStats.Add(Skills.ProfessionalSkills.professionalOther);
	CStats.Add(Stats.psyche);
	CStats.Add(Skills.BaseSkills.riding);
	CStats.Add(Stats.senses);
	CStats.Add(Stats.smarts);
	CStats.Add(Skills.ProfessionalSkills.smithing);
	CStats.Add(Stats.speed);
	CStats.Add(Skills.CriminalSkills.stealth);
	CStats.Add(Stats.strength);
	CStats.Add(Skills.HuntingSkills.survival);
	CStats.Add(Skills.BaseSkills.swimming);
	CStats.Add(Skills.BookSmartsSkills.tactics);
	CStats.Add(Skills.ProfessionalSkills.tailoring);
	CStats.Add(Skills.MagicSkills.telekinesis);
	CStats.Add(Skills.CriminalSkills.thievery);
	CStats.Add(Skills.HuntingSkills.tracking);
	CStats.Add(Skills.ProfessionalSkills.trading);
	CStats.Add(Skills.MagicSkills.transmutation);
	CStats.Add(Skills.HuntingSkills.traps);
	CStats.Add(Skills.CombatSkills.w1handed);
	CStats.Add(Skills.CombatSkills.w2handed);
	CStats.Add(Skills.MagicSkills.whiteMagic);
	CStats.Add(Skills.CombatSkills.wlight);
	CStats.Add(Skills.CombatSkills.wpolearm);
	CStats.Add(Skills.CombatSkills.wshooting);
	CStats.Add(Skills.CombatSkills.wthrowing);
	CStats.Add(gold);
	CStats[0] = Skills.BaseSkills.acrobatics;
	CStats[1] = Skills.BookSmartsSkills.alchemy;
	CStats[2] = Skills.MagicSkills.antimagic;
	CStats[3] = Skills.ProfessionalSkills.artistic;
	CStats[4] = Skills.SocialSkills.bluff;
	CStats[5] = Skills.BaseSkills.boating;
	CStats[6] = Skills.CombatSkills.brawling;
	CStats[7] = Skills.BaseSkills.climbing;
	CStats[8] = Skills.ProfessionalSkills.cooking;
	CStats[9] = Stats.dexterity;
	CStats[10] = Skills.CriminalSkills.disguise;
	CStats[11] = Skills.MagicSkills.divination;
	CStats[12] = Skills.CombatSkills.dodging;
	CStats[13] = Skills.BookSmartsSkills.enchanting;
	CStats[14] = Stats.endurance;
	CStats[15] = Skills.BookSmartsSkills.engineering;
	CStats[16] = Skills.SocialSkills.etiquette;
	CStats[17] = Skills.CriminalSkills.forgery;
	CStats[18] = Skills.ProfessionalSkills.furriery;
	CStats[19] = Skills.BaseSkills.healing;
	CStats[20] = Skills.BookSmartsSkills.history;
	CStats[21] = Skills.MagicSkills.illusions;
	CStats[22] = Skills.SocialSkills.intimidation;
	CStats[23] = Skills.BaseSkills.investigation;
	CStats[24] = Skills.MagicSkills.kriomancy;
	CStats[25] = Skills.BookSmartsSkills.law;
	CStats[26] = Skills.SocialSkills.leadership;
	CStats[27] = Skills.BookSmartsSkills.linguistics;
	CStats[28] = Skills.CriminalSkills.lockpicking;
	CStats[29] = Skills.BookSmartsSkills.magic;
	CStats[30] = Skills.BookSmartsSkills.nature;
	CStats[31] = Skills.BaseSkills.navigation;
	CStats[32] = Skills.MagicSkills.necromancy;
	CStats[33] = Skills.BookSmartsSkills.occultism;
	CStats[34] = PD;
	CStats[35] = Skills.BaseSkills.perception;
	CStats[36] = Skills.SocialSkills.performance;
	CStats[37] = Skills.SocialSkills.persuasion;
	CStats[38] = Skills.MagicSkills.piromancy;
	CStats[39] = Skills.ProfessionalSkills.professionalOther;
	CStats[40] = Stats.psyche;
	CStats[41] = Skills.BaseSkills.riding;
	CStats[42] = Stats.senses;
	CStats[43] = Stats.smarts;
	CStats[44] = Skills.ProfessionalSkills.smithing;
	CStats[45] = Stats.speed;
	CStats[46] = Skills.CriminalSkills.stealth;
	CStats[47] = Stats.strength;
	CStats[48] = Skills.HuntingSkills.survival;
	CStats[49] = Skills.BaseSkills.swimming;
	CStats[50] = Skills.BookSmartsSkills.tactics;
	CStats[51] = Skills.ProfessionalSkills.tailoring;
	CStats[52] = Skills.MagicSkills.telekinesis;
	CStats[53] = Skills.CriminalSkills.thievery;
	CStats[54] = Skills.HuntingSkills.tracking;
	CStats[55] = Skills.ProfessionalSkills.trading;
	CStats[56] = Skills.MagicSkills.transmutation;
	CStats[57] = Skills.HuntingSkills.traps;
	CStats[58] = Skills.CombatSkills.w1handed;
	CStats[59] = Skills.CombatSkills.w2handed;
	CStats[60] = Skills.MagicSkills.whiteMagic;
	CStats[61] = Skills.CombatSkills.wlight;
	CStats[62] = Skills.CombatSkills.wpolearm;
	CStats[63] = Skills.CombatSkills.wshooting;
	CStats[64] = Skills.CombatSkills.wthrowing;
	CStats[65] = gold;
}
int ALoTECharacter::RollSkill(int skillLevel, int statLevel)
{
	int minValue, maxValue;
	minValue = skillLevel + statLevel;
	maxValue = minValue;
	int rollBonuses;
	rollBonuses = skillLevel + statLevel + currentRollBonus;

	if (skillLevel == 1)
	{
		minValue = rollBonuses + 2;
		maxValue = rollBonuses + 8;
	}
	else if (skillLevel == 2)
	{
		minValue = rollBonuses + 2;
		maxValue = rollBonuses + 10;
	}
	else if (skillLevel == 3)
	{
		minValue = rollBonuses + 2;
		maxValue = rollBonuses + 12;
	}
	else if (skillLevel == 4)
	{
		minValue = rollBonuses + 2;
		maxValue = rollBonuses + 14;
	}
	else if (skillLevel == 5)
	{
		minValue = rollBonuses + 2;
		maxValue = rollBonuses + 16;
	}
	else if (skillLevel == 6)
	{
		minValue = rollBonuses + 2;
		maxValue = rollBonuses + 18;
	}
	else if (skillLevel == 7)
	{
		minValue = rollBonuses + 2;
		maxValue = rollBonuses + 20;
	}
	else if (skillLevel == 8)
	{
		minValue = rollBonuses + 2;
		maxValue = rollBonuses + 22;
	}
	else if (skillLevel == 9)
	{
		minValue = rollBonuses + 2;
		maxValue = rollBonuses + 24;
	}
	else if (skillLevel == 10)
	{
		minValue = rollBonuses + 3;
		maxValue = rollBonuses + 28;
	}
	else
	{
		minValue = rollBonuses + 1;
		maxValue = rollBonuses + 4;
	}
	return FMath::RandRange(minValue, maxValue);
}

int ALoTECharacter::RollStat(int statLevel)
{
	return FMath::RandRange(statLevel + 2, statLevel + 12);

}

int ALoTECharacter::Roll(int minNumber, int maxNumber)
{
	return FMath::RandRange(minNumber, maxNumber);;
}

int ALoTECharacter::RollWPolearm()
{
	return RollSkill(Skills.CombatSkills.wpolearm, Stats.dexterity);
}

int ALoTECharacter::RollW2Handed()
{
	return RollSkill(Skills.CombatSkills.w2handed, Stats.dexterity);
}

int ALoTECharacter::RollW1Handed()
{
	return RollSkill(Skills.CombatSkills.w1handed, Stats.dexterity);
}

int ALoTECharacter::RollWLight()
{
	return RollSkill(Skills.CombatSkills.wlight, Stats.dexterity);
}

int ALoTECharacter::RollWThrowing()
{
	return RollSkill(Skills.CombatSkills.wthrowing, Stats.dexterity);
}

int ALoTECharacter::RollWShooting()
{
	return RollSkill(Skills.CombatSkills.wshooting, Stats.dexterity);
}

int ALoTECharacter::RollDodging()
{
	return RollSkill(Skills.CombatSkills.dodging, Stats.dexterity);
}

int ALoTECharacter::RollBrawling()
{
	return RollSkill(Skills.CombatSkills.brawling, Stats.dexterity);
}

int ALoTECharacter::RollAntimagic()
{
	return RollSkill(Skills.MagicSkills.antimagic, Stats.senses);
}

int ALoTECharacter::RollWhiteMagic()
{
	return RollSkill(Skills.MagicSkills.whiteMagic, Stats.senses);
}

int ALoTECharacter::RollIllusions()
{
	return RollSkill(Skills.MagicSkills.illusions, Stats.senses);
}

int ALoTECharacter::RollKriomancy()
{
	return RollSkill(Skills.MagicSkills.kriomancy, Stats.senses);
}

int ALoTECharacter::RollNecromancy()
{
	return RollSkill(Skills.MagicSkills.necromancy, Stats.senses);
}

int ALoTECharacter::RollPiromancy()
{
	return RollSkill(Skills.MagicSkills.piromancy, Stats.senses);
}

int ALoTECharacter::RollTelekinesis()
{
	return RollSkill(Skills.MagicSkills.telekinesis, Stats.senses);
}

int ALoTECharacter::RollTransmutation()
{
	return RollSkill(Skills.MagicSkills.transmutation, Stats.senses);
}

int ALoTECharacter::RollDivination()
{
	return RollSkill(Skills.MagicSkills.divination, Stats.senses);
}

int ALoTECharacter::RollSurvival()
{
	return RollSkill(Skills.HuntingSkills.survival, Stats.senses);
}

int ALoTECharacter::RollTraps()
{
	return RollSkill(Skills.HuntingSkills.traps, Stats.smarts);
}

int ALoTECharacter::RollTracking()
{
	return RollSkill(Skills.HuntingSkills.tracking, Stats.senses);
}

int ALoTECharacter::RollRiding()
{
	return RollSkill(Skills.BaseSkills.riding, Stats.dexterity);
}

int ALoTECharacter::RollHealing()
{
	return RollSkill(Skills.BaseSkills.healing, Stats.dexterity);
}

int ALoTECharacter::RollNavigation()
{
	return RollSkill(Skills.BaseSkills.navigation, Stats.smarts);
}

int ALoTECharacter::RollSwimming()
{
	return RollSkill(Skills.BaseSkills.swimming, Stats.strength);
}

int ALoTECharacter::RollInvestigation()
{
	return RollSkill(Skills.BaseSkills.investigation, Stats.smarts);
}

int ALoTECharacter::RollPerception()
{
	return RollSkill(Skills.BaseSkills.perception, Stats.senses);
}

int ALoTECharacter::RollClimbing()
{
	return RollSkill(Skills.BaseSkills.climbing, Stats.strength);
}

int ALoTECharacter::RollBoating()
{
	return RollSkill(Skills.BaseSkills.boating, Stats.dexterity);
}

int ALoTECharacter::RollBluff()
{
	return RollSkill(Skills.SocialSkills.bluff, Stats.senses);
}

int ALoTECharacter::RollLeadership()
{
	return RollSkill(Skills.SocialSkills.leadership, Stats.senses);
}

int ALoTECharacter::RollEtiquette()
{
	return RollSkill(Skills.SocialSkills.etiquette, Stats.senses);
}

int ALoTECharacter::RollPersuasion()
{
	return RollSkill(Skills.SocialSkills.persuasion, Stats.senses);
}

int ALoTECharacter::RollPerformance()
{
	return RollSkill(Skills.SocialSkills.performance, Stats.senses);
}

int ALoTECharacter::RollIntimidation()
{
	return RollSkill(Skills.SocialSkills.intimidation, Stats.senses);
}

int ALoTECharacter::RollForgery()
{
	return RollSkill(Skills.CriminalSkills.forgery, Stats.dexterity);
}

int ALoTECharacter::RollThievery()
{
	return RollSkill(Skills.CriminalSkills.thievery, Stats.dexterity);
}

int ALoTECharacter::RollLockpicking()
{
	return RollSkill(Skills.CriminalSkills.lockpicking, Stats.dexterity);
}

int ALoTECharacter::RollDisguise()
{
	return RollSkill(Skills.CriminalSkills.disguise, Stats.smarts);
}

int ALoTECharacter::RollStealth()
{
	return RollSkill(Skills.CriminalSkills.stealth, Stats.dexterity);
}

int ALoTECharacter::RollHistory()
{
	return RollSkill(Skills.BookSmartsSkills.history, Stats.smarts);
}

int ALoTECharacter::RollEngineering()
{
	return RollSkill(Skills.BookSmartsSkills.engineering, Stats.smarts);
}

int ALoTECharacter::RollLinguistics()
{
	return RollSkill(Skills.BookSmartsSkills.linguistics, Stats.smarts);
}

int ALoTECharacter::RollMagic()
{
	return RollSkill(Skills.BookSmartsSkills.magic, Stats.smarts);
}

int ALoTECharacter::RollOccultism()
{
	return RollSkill(Skills.BookSmartsSkills.occultism, Stats.smarts);
}

int ALoTECharacter::RollLaw()
{
	return RollSkill(Skills.BookSmartsSkills.law, Stats.smarts);
}

int ALoTECharacter::RollNature()
{
	return RollSkill(Skills.BookSmartsSkills.nature, Stats.smarts);
}

int ALoTECharacter::RollTactics()
{
	return RollSkill(Skills.BookSmartsSkills.tactics, Stats.smarts);
}

int ALoTECharacter::RollEnchanting()
{
	return RollSkill(Skills.BookSmartsSkills.enchanting, Stats.smarts);
}

int ALoTECharacter::RollAlchemy()
{
	return RollSkill(Skills.BookSmartsSkills.alchemy, Stats.smarts);
}

int ALoTECharacter::RollArtistic()
{
	return RollSkill(Skills.ProfessionalSkills.artistic, Stats.senses);
}

int ALoTECharacter::RollCooking()
{
	return RollSkill(Skills.ProfessionalSkills.cooking, Stats.smarts);
}

int ALoTECharacter::RollSmithing()
{
	return RollSkill(Skills.ProfessionalSkills.smithing, Stats.dexterity);
}

int ALoTECharacter::RollTailoring()
{
	return RollSkill(Skills.ProfessionalSkills.tailoring, Stats.dexterity);
}

int ALoTECharacter::RollTrading()
{
	return RollSkill(Skills.ProfessionalSkills.trading, Stats.smarts);
}

int ALoTECharacter::RollFurriery()
{
	return RollSkill(Skills.ProfessionalSkills.furriery, Stats.dexterity);
}

int ALoTECharacter::RollProfessionalOther()
{
	return RollSkill(Skills.ProfessionalSkills.professionalOther, Stats.smarts);
}

int ALoTECharacter::RollAcrobatics()
{
	return RollSkill(Skills.BaseSkills.acrobatics, Stats.dexterity);
}

int ALoTECharacter::Attack()
{
	if (WUsed == WType::BRAWLING)
	{
		attRolled = RollBrawling();
	}
	else if (WUsed == WType::ONEHANDED)
	{
		attRolled = RollW1Handed();
	}
	else if (WUsed == WType::POLEARM)
	{
		attRolled = RollWPolearm();
	}
	else if (WUsed == WType::SHOOTING)
	{
		attRolled = RollWShooting();
	}
	else if (WUsed == WType::SHORT)
	{
		attRolled = RollWLight();
	}
	else if (WUsed == WType::THROWING)
	{
		attRolled = RollWThrowing();
	}
	else if (WUsed == WType::TWOHANDED)
	{
		attRolled = RollW2Handed();
	}


	return attRolled;
}

int ALoTECharacter::RollStrength()
{
	return RollStat(Stats.strength);
}

int ALoTECharacter::RollDexterity()
{
	return RollStat(Stats.dexterity);
}

int ALoTECharacter::RollSpeed()
{
	return RollStat(Stats.speed);
}

int ALoTECharacter::RollEndurance()
{
	return RollStat(Stats.endurance);
}

int ALoTECharacter::RollSmarts()
{
	return RollStat(Stats.smarts);
}

int ALoTECharacter::RollPsyche()
{
	return RollStat(Stats.psyche);
}

int ALoTECharacter::RollSenses()
{
	return RollStat(Stats.senses);
}

void ALoTECharacter::SetCharacterName(FString name)
{
	characterName = name;
}

int ALoTECharacter::RollDamage()
{
	dmgRolled = Roll(minWeaponDmg, maxWeaponDmg);
	return dmgRolled;
}

int ALoTECharacter::RollParry()
{
	return Attack();
}

bool ALoTECharacter::CheckIfDead()
{
	int hp = GetCurrentHP();
	if (hp < 1)
		return true;
	return false;
}

void ALoTECharacter::DoYourTurn_Implementation()
{
}
