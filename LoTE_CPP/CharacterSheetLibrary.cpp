// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSheetLibrary.h"

void UCharacterSheetLibrary::ChangeSkill(bool positive, UTextBlock* text, UTextBlock* PD)
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
			if (tmp < 3)
			{
				PDint = PDint + 5 * (tmp + 1);
				text->SetText(FText::FromString(FString::FromInt(tmp + 1)));
			}
			else if (tmp < 5)
			{
				PDint = PDint + 15 + 10 * (tmp - 2);
				text->SetText(FText::FromString(FString::FromInt(tmp + 1)));
			}
			else if (tmp < 9)
			{
				PDint = PDint + 45 + 20 * (tmp - 5);
				text->SetText(FText::FromString(FString::FromInt(tmp + 1)));
			}
			else if (tmp == 9)
			{
				PDint = PDint + 145;
				text->SetText(FText::FromString(FString::FromInt(tmp + 1)));
			}

			PD->SetText(FText::FromString(FString::FromInt(PDint)));

		}
		else if (tmp > 0)
		{
			if (tmp < 4)
			{
				PDint = PDint - 5 * (tmp);
				text->SetText(FText::FromString(FString::FromInt(tmp - 1)));
			}
			else if (tmp < 6)
			{
				PDint = PDint - 15 - 10 * (tmp - 3);
				text->SetText(FText::FromString(FString::FromInt(tmp - 1)));
			}
			else if (tmp < 10)
			{
				PDint = PDint - 45 - 20 * (tmp - 6);
				text->SetText(FText::FromString(FString::FromInt(tmp - 1)));
			}
			else if (tmp == 10)
			{
				PDint = PDint - 145;
				text->SetText(FText::FromString(FString::FromInt(tmp - 1)));
			}
			PD->SetText(FText::FromString(FString::FromInt(PDint)));
		}
	}
}

bool UCharacterSheetLibrary::SaveToFile(FString SaveDirectory, FString FileName, TArray<FString>SaveText, bool AllowOverWriting)
{
	SaveDirectory = SaveDirectory + "\\" + FileName+".txt";

	if (AllowOverWriting == false)
	{
		if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*SaveDirectory))
		{
			return false;
		}
	}

	FString FinalString = "";
	for (FString& Each : SaveText)
	{
		FinalString = FinalString + Each;
		FinalString = FinalString + LINE_TERMINATOR;
	}
	
	return FFileHelper::SaveStringToFile(FinalString, *SaveDirectory);

}

FString UCharacterSheetLibrary::GetTextValue(UTextBlock* text)
{
	return text->GetText().ToString();
}

FString UCharacterSheetLibrary::GetEditableTextValue(UEditableText* text)
{
	return text->GetText().ToString();
}

bool UCharacterSheetLibrary::SaveLineToFile(FString SaveDirectory, FString FileName, FString SaveText, bool AllowOverWriting)
{
	SaveDirectory = SaveDirectory + "\\" + FileName + ".txt";

	if (AllowOverWriting == false)
	{
		if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*SaveDirectory))
		{
			return false;
		}
	}

	FString FinalString = SaveText + LINE_TERMINATOR;

	return FFileHelper::SaveStringToFile(FinalString, *SaveDirectory);
}

TArray<FString> UCharacterSheetLibrary::LoadFileToStringArray(FString Filename, FString SaveDirectory)
{
	
	TArray<FString> result;
	IPlatformFile& file = FPlatformFileManager::Get().GetPlatformFile();

	if (file.CreateDirectory(*SaveDirectory))
	{
		Filename.TrimEndInline();
		//Filename.RemoveSpacesInline();
		FString myFile = SaveDirectory + Filename+".txt";
		FFileHelper::LoadFileToStringArray(result, *myFile);
		FString* tmp = result.GetData();
		FString tmp2 = tmp[138];    
		UE_LOG(LogTemp, Warning, TEXT("shit2 is %s"), *tmp2);
	}
	else
	{
	 //   UE_LOG(LogTemp, Warning, TEXT("Wyjebao sie na tworzeniu arraya"));
	}
	return result;
}

FString UCharacterSheetLibrary::LoadFileToString(FString Filename, FString SaveDirectory)
{
	FString result;
	IPlatformFile& file = FPlatformFileManager::Get().GetPlatformFile();

	if (file.CreateDirectory(*SaveDirectory))
	{
		
		FString myFile = SaveDirectory + Filename+".txt";
		UE_LOG(LogTemp, Warning, TEXT("shit1 is %s"), *myFile);
		FFileHelper::LoadFileToString(result, *myFile);
	}
	UE_LOG(LogTemp, Warning, TEXT("return from shit1 is %s"), *result);
	return result;
}

int UCharacterSheetLibrary::SubstractInt(int randomInt, int minus)
{
	return randomInt-minus;
}

int UCharacterSheetLibrary::AddInt(int randomInt, int plus)
{
	return randomInt+plus;
}

bool UCharacterSheetLibrary::IsThereEnoughGold(int currentGold, int price)
{
	if (currentGold - price >= 0)
	{
		return true;
	}
	else return false;
}

void UCharacterSheetLibrary::ChangeText(FString text, UTextBlock* changedText)
{
	changedText->SetText(FText::FromString(text));
}

int UCharacterSheetLibrary::SafeFStringToInt(FString text)
{
	int tmp = 0;
	if (text.IsNumeric())
	{
		tmp = FCString::Atoi(*text);
	}
	return tmp;
}

bool UCharacterSheetLibrary::BuySellItem(UButton* Button, UTextBlock* gold, bool condition, int price)
{
	FString tmp = gold->GetText().ToString();
	int calculatableGold = SafeFStringToInt(tmp);

	bool bul = condition;

	if (bul == false)
	{
		if (IsThereEnoughGold(calculatableGold, price))
		{
			
	  
			Button->SetColorAndOpacity(FColor::Red);
			calculatableGold = calculatableGold - price;
			gold->SetText(FText::FromString(FString::FromInt(calculatableGold)));
			bul = true;
			return bul;
	   }
	}
	else {
		Button->SetColorAndOpacity(FColor::White);
		calculatableGold = calculatableGold + price;
		gold->SetText(FText::FromString(FString::FromInt(calculatableGold)));
		bul = false;
		return bul;

	}
	return bul;
}



FString UCharacterSheetLibrary::ReadLineFromFile(FString SaveDirectory, FString FileName)
{
	SaveDirectory = SaveDirectory + "\\" + FileName + ".txt";
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*SaveDirectory))
	{
		FString name;
		FFileHelper::LoadFileToString(name, *SaveDirectory);
		return name;
	}
	else {
		return FString("fk");
	}
	
}

TArray<FString> UCharacterSheetLibrary::MakeAnArray(FString SaveDirectory, FString FileName)
{
	SaveDirectory = SaveDirectory + "\\" + FileName + ".txt";

	TArray<FString>Array;

	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*SaveDirectory))
	{
		
		FFileHelper::LoadANSITextFileToStrings(*SaveDirectory, NULL, Array);
		UE_LOG(LogTemp, Warning, TEXT("Nie wyebao"));
		return Array;
	}
	else {

		UE_LOG(LogTemp, Warning, TEXT("Wyjebao sie na tworzeniu arraya"));
		return TArray<FString>();

	}
  
	
}


