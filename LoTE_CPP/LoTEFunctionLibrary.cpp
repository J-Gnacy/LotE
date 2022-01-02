// Fill out your copyright notice in the Description page of Project Settings.


#include "LoTEFunctionLibrary.h"

void ULoTEFunctionLibrary::ChangeStat(bool positive, UTextBlock* text, UTextBlock* PD)
{
	FString TheString = text->GetText().ToString();
	FString ValueOfPD = PD->GetText().ToString();
	int PDint = 0;

	int tmp = 0;

	if (TheString.IsNumeric() || ValueOfPD.IsNumeric())
	{
		tmp = FCString::Atoi(*TheString);
		PDint = FCString::Atoi(*ValueOfPD);

		if (positive == true)
		{
			if (tmp == 1)
			{
				PDint = PDint + 10;
			}
			else if (tmp == 2)
			{
				PDint = PDint + 20;
			}
			else if (tmp == 3)
			{
				PDint = PDint + 40;
			}
			else if (tmp == 4)
			{
				PDint = PDint + 60;
			}
			else if (tmp == 5)
			{
				PDint = PDint + 80;
			}
			else if (tmp == 6)
			{
				PDint = PDint + 120;
			}
			else if (tmp == 7)
			{
				PDint = PDint + 160;
			}
			else if (tmp == 8)
			{
				PDint = PDint + 200;
			}
			else if (tmp > 8)
			{
				int tmp2 = tmp - 8;
				PDint = PDint + 200 + tmp2 * 100;
			}
			text->SetText(FText::FromString(FString::FromInt(tmp + 1)));
		}
		else {
			if (tmp == 2)
			{
				PDint = PDint - 10;
				text->SetText(FText::FromString(FString::FromInt(tmp - 1)));
			}
			else if (tmp == 3)
			{
				PDint = PDint - 20;
				text->SetText(FText::FromString(FString::FromInt(tmp - 1)));
			}
			else if (tmp == 4)
			{
				PDint = PDint - 40;
				text->SetText(FText::FromString(FString::FromInt(tmp - 1)));
			}
			else if (tmp == 5)
			{
				PDint = PDint - 60;
				text->SetText(FText::FromString(FString::FromInt(tmp - 1)));
			}
			else if (tmp == 6)
			{
				PDint = PDint - 80;
				text->SetText(FText::FromString(FString::FromInt(tmp - 1)));
			}
			else if (tmp == 7)
			{
				PDint = PDint - 120;
				text->SetText(FText::FromString(FString::FromInt(tmp - 1)));
			}
			else if (tmp == 8)
			{
				PDint = PDint - 160;
				text->SetText(FText::FromString(FString::FromInt(tmp - 1)));
			}
			else if (tmp == 8)
			{
				PDint = PDint - 200;
				text->SetText(FText::FromString(FString::FromInt(tmp - 1)));
			}
			else if (tmp > 8)
			{
				int tmp2 = tmp - 9;
				PDint = PDint - 200 - tmp2 * 100;
				text->SetText(FText::FromString(FString::FromInt(tmp - 1)));
			}
		}

		PD->SetText(FText::FromString(FString::FromInt(PDint)));



	}
	
}

void ULoTEFunctionLibrary::SetValue(UTextBlock* changedText, UTextBlock* mainStat, EResource Resource) //option 1 = mainStat+3, option 2 = mainStat*2, option 3 = mainStat/2, option 4= 3+mainStat*5,
{
	FString tmp = mainStat->GetText().ToString();
	int result=0;

		if (tmp.IsNumeric())
		{
			int tmpInt = FCString::Atoi(*tmp);

			if (Resource == EResource::PA)
			{
				result = tmpInt + 3;
			}
			else if (Resource == EResource::MANA)
			{
				result = tmpInt * 2;
			}
			else if (Resource == EResource::RESISTANCE)
			{
				result = tmpInt / 2;
			}
			else if (Resource == EResource::SANITY)
			{
				result = 3 + tmpInt * 5;
			}
			else if (Resource==EResource::MOVE)
			{
				result = (3 + tmpInt) * 2;
			};

			changedText->SetText(FText::FromString(FString::FromInt(result)));

		}

}

void ULoTEFunctionLibrary::SetSmartsyThings(UTextBlock* changedText, UTextBlock* mainStat, UTextBlock* secondStat, bool useBoth)
{
	FString tmp = mainStat->GetText().ToString();
	int result = 0;

	
		if (tmp.IsNumeric())
		{
			int tmpInt = FCString::Atoi(*tmp);
			if (useBoth == true)
			{
				FString tmp2 = secondStat->GetText().ToString();
				if (tmp2.IsNumeric())
				{
					int tmp2Int = FCString::Atoi(*tmp2);
					result = tmp2Int + tmpInt;
				}
			}
			else
			{
				result = (tmpInt * 70);
			}
			changedText->SetText(FText::FromString(FString::FromInt(result)));
		}

	
}

float ULoTEFunctionLibrary::SetXDistance(float enemyX, float playerX)
{
	float resultX;
	if (enemyX > playerX)
	{
		resultX = abs((playerX - enemyX));
	}
	else
	{
		resultX = abs((enemyX - playerX));
	}
	return resultX;
}

float ULoTEFunctionLibrary::SetYDistance(float enemyY, float playerY)
{
	float resultY;
	if (enemyY > playerY)
	{
		resultY = abs((playerY - enemyY));
	}
	else
	{
		resultY = abs((enemyY - playerY));
	}
	return resultY;
}

