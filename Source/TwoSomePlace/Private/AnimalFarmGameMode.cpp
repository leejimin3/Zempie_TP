// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimalFarmGameMode.h"
#include "../Parent_Animal.h"
#include "../Child_Animal.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Misc/DefaultValueHelper.h"

void AAnimalFarmGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	
	LoadAnimalDatas();
}

TArray<FAnimalRawData> AAnimalFarmGameMode::GetAnimalRawDatas()
{
	return AnimalDatas;
}

void AAnimalFarmGameMode::SpawnAnimals(int animalSpawnCount)
{
	//check(GetWorld() != nullptr);

	// upper player		
	for (int i = 0; i < animalSpawnCount; ++i)
	{
		AParent_Animal* animal = GetWorld()->SpawnActor<AParent_Animal>(AnimalClass, SpawnOrigin, { 0.0f,0.0f,0.0f });
		Animals.Push(animal);

		animal->Set_LeftDownFarmAria(FarmLeftDown);
		animal->Set_RightUpFarmAria(FarmRightUp);
	}

	// lower player
	for (int i = 0; i < animalSpawnCount; ++i)
	{
		AParent_Animal* animal = GetWorld()->SpawnActor<AParent_Animal>(AnimalClass, SpawnOrigin, { 0.0f,0.0f,0.0f });
		Animals.Push(animal);

		animal->Set_LeftDownFarmAria(FarmLeftDown);
		animal->Set_RightUpFarmAria(FarmRightUp);
	}
}

AChild_Animal* AAnimalFarmGameMode::MakeChildAnimal(const AParent_Animal* parent1, const AParent_Animal* parent2)
{
	AChild_Animal* childAnimal = nullptr;
	childAnimal = NewObject<AChild_Animal>();

	// 반복문으로 일괄 처리하기 위한 처리
	const TArray<int32>* parentsPartsInfo[4][2] =
	{
		{&parent1->head, &parent2->head},
		{&parent1->body, &parent2->body},
		{&parent1->leg, &parent2->leg},
		{&parent1->tail, &parent2->tail},
	};

	TArray<int32>* childPartsInfo[4] =
	{
		&childAnimal->head,
		&childAnimal->body,
		&childAnimal->leg,
		&childAnimal->tail
	};

	// parent1, parent2의 특성을 random하게 child에게 물려주는 로직
	unsigned int selector = 0;
	for (int i = 0; i < 4; ++i)
	{
		selector = UKismetMathLibrary::RandomInteger(1);
		const TArray<int32>* selectedPartsInfo = parentsPartsInfo[i][selector];

		childPartsInfo[i]->SetNum(selectedPartsInfo->Num());

		for (int j = 0; j < selectedPartsInfo->Num(); ++j)
		{
			(*childPartsInfo[i])[j] = (*selectedPartsInfo)[j];
		}
	}

	return childAnimal;
}

void AAnimalFarmGameMode::LoadAnimalDatas()
{
	FString csvRawData;
	
	const TCHAR* delims = {TEXT(",")};
	if (FFileHelper::LoadFileToString(csvRawData, *(FPaths::ProjectConfigDir() + AnimalDataCSVFileName)))
	{
		TArray<FString> columns;
		csvRawData.ParseIntoArrayLines(columns);

		for (const FString& column : columns)
		{
			if (column[0] != 'a')
			{
				continue;
			}
			else
			{
				int32 arraySize = 0;
				TArray<FString> rows;
				
				if ((arraySize = column.ParseIntoArray(rows, delims)) > 0)
				{
					FAnimalRawData animalRawData;
					animalRawData.AnimalCode = rows[0];
					animalRawData.AnimalName = rows[1];

					for (int i = 2; i < arraySize; ++i)
					{
						float data = 0.0f;
						
						check(FDefaultValueHelper::ParseFloat(rows[i], data));
						
						animalRawData.States.Push(data);
					}

					

					AnimalDatas.Push(animalRawData);
				}
			}
		}

	}
	else
	{
		UKismetSystemLibrary::PrintString(GetWorld(), *(AnimalDataCSVFileName + TEXT(" file not found, check config folder")));
		UKismetSystemLibrary::PrintString(GetWorld(), *(FPaths::ProjectConfigDir() + AnimalDataCSVFileName));

		return;
	}

	//// debugging Code
	for (const FAnimalRawData& rawData : AnimalDatas)
	{
		UKismetSystemLibrary::PrintString(GetWorld(), rawData.AnimalCode);
		UKismetSystemLibrary::PrintString(GetWorld(), rawData.AnimalName);

		for (const float& state : rawData.States)
		{
			UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%f"), state));
		}
	}
}
