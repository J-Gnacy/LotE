// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InitiativeComponent.h"
#include "LoTEHUD.h"
#include "LoTECharacter.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStats
{
	GENERATED_BODY()

	FCharacterStats()
	{
	}
	UPROPERTY(BlueprintReadWrite)
	int strength;
	UPROPERTY(BlueprintReadWrite)
	int dexterity;
	UPROPERTY(BlueprintReadWrite)
	int speed;
	UPROPERTY(BlueprintReadWrite)
	int endurance;
	UPROPERTY(BlueprintReadWrite)
	int smarts;
	UPROPERTY(BlueprintReadWrite)
	int psyche;
	UPROPERTY(BlueprintReadWrite)
	int senses;

	

};

USTRUCT(BlueprintType)
struct FCombatSkills
{
	GENERATED_BODY()

		FCombatSkills()
	{
	}

	UPROPERTY(BlueprintReadWrite)
		int wpolearm;
	UPROPERTY(BlueprintReadWrite)
		int w2handed;
	UPROPERTY(BlueprintReadWrite)
		int w1handed;
	UPROPERTY(BlueprintReadWrite)
		int wlight;
	UPROPERTY(BlueprintReadWrite)
		int wthrowing;
	UPROPERTY(BlueprintReadWrite)
		int wshooting;
	UPROPERTY(BlueprintReadWrite)
		int dodging;
	UPROPERTY(BlueprintReadWrite)
		int brawling;


};


USTRUCT(BlueprintType)
struct FBaseSkills
{
	GENERATED_BODY()

		FBaseSkills()
	{
	}
	UPROPERTY(BlueprintReadWrite)
		int acrobatics;
	UPROPERTY(BlueprintReadWrite)
		int riding;
	UPROPERTY(BlueprintReadWrite)
		int healing;
	UPROPERTY(BlueprintReadWrite)
		int navigation;
	UPROPERTY(BlueprintReadWrite)
		int swimming;
	UPROPERTY(BlueprintReadWrite)
		int investigation;
	UPROPERTY(BlueprintReadWrite)
		int perception;
	UPROPERTY(BlueprintReadWrite)
		int climbing;
	UPROPERTY(BlueprintReadWrite)
		int boating;
};

USTRUCT(BlueprintType)
struct FCriminalSkills
{
	GENERATED_BODY()

		FCriminalSkills()
	{
	}


	UPROPERTY(BlueprintReadWrite)
		int forgery;
	UPROPERTY(BlueprintReadWrite)
		int thievery;
	UPROPERTY(BlueprintReadWrite)
		int lockpicking;
	UPROPERTY(BlueprintReadWrite)
		int disguise;
	UPROPERTY(BlueprintReadWrite)
		int stealth;

};

USTRUCT(BlueprintType)
struct FSocialSkills
{
	GENERATED_BODY()

		FSocialSkills()
	{
	}


	UPROPERTY(BlueprintReadWrite)
		int bluff;
	UPROPERTY(BlueprintReadWrite)
		int leadership;
	UPROPERTY(BlueprintReadWrite)
		int etiquette;
	UPROPERTY(BlueprintReadWrite)
		int persuasion;
	UPROPERTY(BlueprintReadWrite)
		int performance;
	UPROPERTY(BlueprintReadWrite)
		int intimidation;
};

USTRUCT(BlueprintType)
struct FHuntingSkills
{
	GENERATED_BODY()

		FHuntingSkills()
	{
	}


	UPROPERTY(BlueprintReadWrite)
		int survival;
	UPROPERTY(BlueprintReadWrite)
		int traps;
	UPROPERTY(BlueprintReadWrite)
		int tracking;
};

USTRUCT(BlueprintType)
struct FMagicSkills
{
	GENERATED_BODY()

		FMagicSkills()
	{
	}


	UPROPERTY(BlueprintReadWrite)
		int antimagic;
	UPROPERTY(BlueprintReadWrite)
		int whiteMagic;
	UPROPERTY(BlueprintReadWrite)
		int illusions;
	UPROPERTY(BlueprintReadWrite)
		int kriomancy;
	UPROPERTY(BlueprintReadWrite)
		int necromancy;
	UPROPERTY(BlueprintReadWrite)
		int piromancy;
	UPROPERTY(BlueprintReadWrite)
		int telekinesis;
	UPROPERTY(BlueprintReadWrite)
		int transmutation;
	UPROPERTY(BlueprintReadWrite)
		int divination;

};

USTRUCT(BlueprintType)
struct FBookSmartsSkills
{
	GENERATED_BODY()

		FBookSmartsSkills()
	{
	}


	UPROPERTY(BlueprintReadWrite)
		int history;
	UPROPERTY(BlueprintReadWrite)
		int engineering;
	UPROPERTY(BlueprintReadWrite)
		int linguistics;
	UPROPERTY(BlueprintReadWrite)
		int magic;
	UPROPERTY(BlueprintReadWrite)
		int occultism;
	UPROPERTY(BlueprintReadWrite)
		int law;
	UPROPERTY(BlueprintReadWrite)
		int nature;
	UPROPERTY(BlueprintReadWrite)
		int tactics;
	UPROPERTY(BlueprintReadWrite)
		int enchanting;
	UPROPERTY(BlueprintReadWrite)
		int alchemy;

};

USTRUCT(BlueprintType)
struct FProfessionalSkills
{
	GENERATED_BODY()

		FProfessionalSkills()
	{
	}


	UPROPERTY(BlueprintReadWrite)
		int artistic;
	UPROPERTY(BlueprintReadWrite)
		int cooking;
	UPROPERTY(BlueprintReadWrite)
		int smithing;
	UPROPERTY(BlueprintReadWrite)
		int tailoring;
	UPROPERTY(BlueprintReadWrite)
		int trading;
	UPROPERTY(BlueprintReadWrite)
		int furriery;
	UPROPERTY(BlueprintReadWrite)
		int professionalOther;

};


USTRUCT(BlueprintType)
struct FSkills
{
	GENERATED_BODY()

		FSkills()
	{
	}
	UPROPERTY(BlueprintReadWrite)
	FCombatSkills CombatSkills;
	UPROPERTY(BlueprintReadWrite)
	FBaseSkills BaseSkills;
	UPROPERTY(BlueprintReadWrite)
	FCriminalSkills CriminalSkills;
	UPROPERTY(BlueprintReadWrite)
	FSocialSkills SocialSkills;
	UPROPERTY(BlueprintReadWrite)
	FHuntingSkills HuntingSkills;
	UPROPERTY(BlueprintReadWrite)
	FMagicSkills MagicSkills;
	UPROPERTY(BlueprintReadWrite)
	FBookSmartsSkills BookSmartsSkills;
	UPROPERTY(BlueprintReadWrite)
	FProfessionalSkills ProfessionalSkills;

};

UENUM(BlueprintType)
enum class WType : uint8 {
	SHORT			UMETA(DisplayName = "Short"),
	ONEHANDED		UMETA(DisplayName = "OneHanded"),
	THROWING		UMETA(DisplayName = "Throwing"),
	TWOHANDED		UMETA(DisplayName = "TwoHanded"),
	POLEARM			UMETA(DisplayName = "Polearm"),
	SHOOTING		UMETA(DisplayName = "Shooting"),
	BRAWLING		UMETA(DisplayName = "Brawling"),

};

UCLASS(Blueprintable)
class ALoTECharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALoTECharacter();


	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACharacter* Enemy;
	UInitiativeComponent* CharInitiative=CreateDefaultSubobject<UInitiativeComponent>(TEXT("Initiative Component"));
	FString characterName;
	TArray<int>CStats;
	FCharacterStats Stats;
	FSkills Skills;


	int PD;
	int gold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isTripped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isGrabbed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isExhausted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isStunned;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isFrightened;

	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		FCharacterStats SetStats(int nStrength, int nDexterity, int nSpeed, int nEndurance, int nSmarts, int nPsyche, int nSenses);

	int move;
	int actionPoints;
	int healthPoints;
	int resistance;
	int talentsLimit;
	int sanity;
	int mana;
	int fortuneCards;



	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetStatsStruct(FCharacterStats Nstats);


	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetSkillsStruct(FSkills Nskills);

	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		FCharacterStats GetStatsStruct();

	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		FSkills GetSkillsStruct();








	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		FSkills SetSkills(int nwpolearm, int nw2handed,
			int nw1handed,
			int nwlight,
			int nwthrowing,
			int nwshooting,
			int ndodging,
			int nbrawling,
			int nantimagic,
			int nwhiteMagic,
			int nillusions,
			int nkriomancy,
			int nnecromancy,
			int npiromancy,
			int ntelekinesis,
			int ntransmutation,
			int ndivination,
			int nsurvival,
			int ntraps,
			int ntracking,
			int nacrobatics,
			int nriding,
			int nhealing,
			int nnavigation,
			int nswimming,
			int ninvestigation,
			int nperception,
			int nclimbing,
			int nboating,
			int nbluff,
			int nleadership,
			int netiquette,
			int npersuasion,
			int nperformance,
			int nintimidation,
			int nforgery,
			int nthievery,
			int nlockpicking,
			int ndisguise,
			int nstealth,
			int nhistory,
			int nengineering,
			int nlinguistics,
			int nmagic,
			int noccultism,
			int nlaw,
			int nnature,
			int ntactics,
			int nenchanting,
			int nalchemy,
			int nartistic,
			int ncooking,
			int nsmithing,
			int ntailoring,
			int ntrading,
			int nfurriery);


	int dmgNegation;

	int currentHP;
	int currentMove;
	int currentActionPoints;
	int currentSanity;
	int currentMana;
	int currentFortuneCards;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int minWeaponDmg;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int maxWeaponDmg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int attackBonus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int tempAttackBonus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int damageBonus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int tempDamageBonus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int damageRolled;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int attackRolled;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int currentMoveBonus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int maxMoveBonus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int currentDefenseBonus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int maxDefenseBonus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int currentRollBonus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int maxRollBonus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		WType WUsed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int dmgRolled;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int attRolled;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int currentActions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int maxActions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool attackUsed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool catchUsed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool tripUsed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool pushUsed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool disarmUsed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool aimUsed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool spellcastingUsed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool moveUsed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool runUsed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int maxPurchasableActions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int currentPurchasableActions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimSequenceBase* AttackAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimSequenceBase* GetHitAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimSequenceBase* CombatIdleAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimSequenceBase* DodgeAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimSequenceBase* DeathAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimSequenceBase* CatchAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimSequenceBase* TripAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimSequenceBase* BullrushAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimSequenceBase* KnockeddownAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimSequenceBase* CurrentAttackAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimSequenceBase* LyingAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimSequenceBase* PushedAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float attackRange;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//int initiative;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//int initiativeBonus;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	bool roundAvailable;


	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void InitializeStats(TArray<FString>Stats);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		static FString statIntToString(int stat);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetMaxHP();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetCurrentHP();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetCurrentMove();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetCurrentActionPoints();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetCurrentSanity();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetCurrentMana();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetCurrentFortuneCards();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetMaxMove();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetMaxActionPoints();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetMaxSanity();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetMaxMana();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetMaxFortuneCards();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void RefreshStats();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetPD();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetStrength();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetDexterity();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetSpeed();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetEndurance();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetSmarts();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetPsyche();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetSenses();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetGold();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetResistance();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetDmgNegation();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetTalentsLimit();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetWPolearm();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetW2Handed();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetW1Handed();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetWLight();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetWThrowing();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetWShooting();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetDodging();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetBrawling();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetAntimagic();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetWhiteMagic();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetIllusions();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetKriomancy();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetNecromancy();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetPiromancy();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetTelekinesis();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetTransmutation();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetDivination();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetSurvival();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetTraps();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetTracking();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetRiding();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetHealing();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetNavigation();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetSwimming();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetInvestigation();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetPerception();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetClimbing();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetBoating();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetBluff();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetLeadership();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetEtiquette();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetPersuasion();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetPerformance();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetIntimidation();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetForgery();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetThievery();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetLockpicking();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetDisguise();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetStealth();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetHistory();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetEngineering();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetLinguistics();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetMagic();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetOccultism();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetLaw();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetNature();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetTactics();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetEnchanting();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetAlchemy();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetArtistic();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetCooking();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetSmithing();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetTailoring();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetTrading();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetFurriery();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetProfessionalOther();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		FString GetCharacterName();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetMaxHP(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetCurrentHP(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetCurrentMove(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetCurrentActionPoints(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetCurrentSanity(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetCurrentMana(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetCurrentFortuneCards(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetMaxMove(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetMaxActionPoints(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetMaxSanity(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetMaxMana(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetMaxFortuneCards(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetPD(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetStrength(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetDexterity(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetSpeed(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetEndurance(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetSmarts(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetPsyche(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetSenses(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetGold(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetResistance(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetDmgNegation(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetTalentsLimit(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetWPolearm(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetW2Handed(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetW1Handed(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetWLight(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetWThrowing(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetWShooting(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetDodging(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetBrawling(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetAntimagic(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetWhiteMagic(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetIllusions(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetKriomancy(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetNecromancy(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetPiromancy(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetTelekinesis(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetTransmutation(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetDivination(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetSurvival(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetTraps(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetTracking(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetRiding(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetHealing(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetNavigation(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetSwimming(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetInvestigation(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetPerception(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetClimbing(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetBoating(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetBluff(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetLeadership(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetEtiquette(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetPersuasion(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetPerformance(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetIntimidation(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetForgery(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetThievery(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetLockpicking(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetDisguise(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetStealth(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetHistory(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetEngineering(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetLinguistics(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetMagic(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetOccultism(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetLaw(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetNature(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetTactics(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetEnchanting(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetAlchemy(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetArtistic(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetCooking(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetSmithing(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetTailoring(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetTrading(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetFurriery(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetProfessionalOther(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int GetAcrobatics();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetAcrobatics(int tmp);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void ReloadStats(TArray<UTextBlock*>Textblocks);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void StatsIntoArrayAlphabetically();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollSkill(int skillLevel, int statLevel);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollStat(int statLevel);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int Roll(int minNumber, int maxNumber);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollWPolearm();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollW2Handed();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollW1Handed();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollWLight();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollWThrowing();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollWShooting();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollDodging();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollBrawling();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollAntimagic();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollWhiteMagic();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollIllusions();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollKriomancy();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollNecromancy();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollPiromancy();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollTelekinesis();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollTransmutation();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollDivination();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollSurvival();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollTraps();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollTracking();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollRiding();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollHealing();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollNavigation();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollSwimming();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollInvestigation();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollPerception();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollClimbing();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollBoating();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollBluff();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollLeadership();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollEtiquette();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollPersuasion();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollPerformance();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollIntimidation();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollForgery();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollThievery();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollLockpicking();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollDisguise();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollStealth();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollHistory();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollEngineering();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollLinguistics();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollMagic();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollOccultism();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollLaw();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollNature();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollTactics();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollEnchanting();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollAlchemy();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollArtistic();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollCooking();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollSmithing();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollTailoring();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollTrading();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollFurriery();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollProfessionalOther();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollAcrobatics();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int Attack();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollStrength();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollDexterity();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollSpeed();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollEndurance();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollSmarts();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollPsyche();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollSenses();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		void SetCharacterName(FString name);
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollDamage();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		int RollParry();
	UFUNCTION(BlueprintCallable, Category = "LoTECollection")
		bool CheckIfDead();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LoTENative")
		void DoYourTurn();
		void DoYourTurn_Implementation();


private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;
};

