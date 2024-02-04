// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimalFarmGameMode.h"
#include "../Parent_Animal.h"
#include "../Child_Animal.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Misc/DefaultValueHelper.h"

void AAnimalFarmGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	LoadAnimalDatas();
	LoadAnimalImageDatas();

	Super::InitGame(MapName, Options, ErrorMessage);	
}

TArray<FAnimalRawData> AAnimalFarmGameMode::GetAnimalRawDatas()
{
	return AnimalDatas;
}

void AAnimalFarmGameMode::SpawnAnimals(int animalSpawnCount)
{
	if (!Animals.IsEmpty())
	{
		for (AParent_Animal* animal : Animals)
		{
			animal->Destroy();
		}

		Animals.Empty();
	}

	TArray<FAnimalRawData> animalDatas = AnimalDatas;

	FTransform defaultTransform({0.0f,0.0f,0.0f}, SpawnOrigin);
	// upper player		
	for (int i = 0; i < animalSpawnCount; ++i)
	{
		AParent_Animal* animal = GetWorld()->SpawnActorDeferred<AParent_Animal>(AnimalClass, defaultTransform);

		int animalTypeIndex = UKismetMathLibrary::RandomIntegerInRange(0, animalDatas.Num() - 1);
		
		FAnimalRawData animalData = animalDatas[animalTypeIndex];
		// ���� ������ �Ź� ũ�� �缳��
		animalDatas.RemoveAt(animalTypeIndex);

		for (int j = 0; j < 4; ++j)
		{
			animal->animalCodes.Push(animalData.AnimalCode);
		}

		animalData.CopyRange(animal->head, 0, 2);
		animalData.CopyRange(animal->body, 3, 5);
		animalData.CopyRange(animal->leg, 6, 8);
		animalData.CopyRange(animal->tail, 9, 11);

		animal->Set_LeftDownFarmAria(FarmLeftDown);
		animal->Set_RightUpFarmAria(FarmRightUp);

		animal->FinishSpawning(defaultTransform);

		Animals.Push(animal);
	}
}

AParent_Animal* AAnimalFarmGameMode::MakeChildAnimal(const AParent_Animal* parent1, const AParent_Animal* parent2)
{
	AParent_Animal* childAnimal = nullptr;

	FTransform transform(ChildSpawnPosition);
	
	childAnimal = GetWorld()->SpawnActorDeferred<AParent_Animal>(ChildType, transform);
	childAnimal->barrive = true;

	// �ݺ������� �ϰ� ó���ϱ� ���� ó��
	const TArray<float>* parentsPartsInfo[4][2] =
	{
		{&parent1->head, &parent2->head},
		{&parent1->body, &parent2->body},
		{&parent1->leg, &parent2->leg},
		{&parent1->tail, &parent2->tail},
	};

	TArray<float>* childPartsInfo[4] =
	{
		&childAnimal->head,
		&childAnimal->body,
		&childAnimal->leg,
		&childAnimal->tail
	};

	// parent1, parent2�� Ư���� random�ϰ� child���� �����ִ� ����
	unsigned int selector = 0;
	for (int i = 0; i < 4; ++i)
	{
		selector = UKismetMathLibrary::RandomInteger(2);
		const TArray<float>* selectedPartsInfo = parentsPartsInfo[i][selector];

		childPartsInfo[i]->SetNum(selectedPartsInfo->Num());

		for (int j = 0; j < selectedPartsInfo->Num(); ++j)
		{
			(*childPartsInfo[i])[j] = (*selectedPartsInfo)[j];
		}
		
		if (selector == 0)
		{
			childAnimal->animalCodes.Push(parent1->animalCodes[i]);
		}
		else
		{
			childAnimal->animalCodes.Push(parent2->animalCodes[i]);
		}
	}

	childAnimal->FinishSpawning(transform);

	return childAnimal;
}

FAnimalImageData AAnimalFarmGameMode::GetAnimalImageData(FString animalCode)
{
	return AnimalImageDatas[animalCode];
}

void AAnimalFarmGameMode::LoadAnimalDatas()
{
	FString csvRawData;
	FString filePath = FPaths::ProjectContentDir() + TEXT("Datas/") + TEXT("AnimalTypes.csv");
	UE_LOG(LogTemp, Warning, TEXT("path : %s"), *filePath);
	UKismetSystemLibrary::PrintString(GetWorld(), filePath);

	const TCHAR* delims = {TEXT(",")};
	if (FFileHelper::LoadFileToString(csvRawData, *(filePath)))
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
		UKismetSystemLibrary::PrintString(GetWorld(), *(filePath + TEXT(" file not found")));

		return;
	}
}

void AAnimalFarmGameMode::LoadAnimalImageDatas()
{
	const TArray<FString> partsNames = { TEXT("Body"), TEXT("Head") , TEXT("Leg") , TEXT("Tail") };
	const TCHAR* delims = { TEXT(",")};
	FString filePath = FPaths::ProjectContentDir() + TEXT("Datas/") + TEXT("AnimalImageDatas.csv");
	UE_LOG(LogTemp, Warning, TEXT("filePath : %s"), *filePath);
	UKismetSystemLibrary::PrintString(GetWorld(), filePath);

	FString animalImageRawDatas;
	if (FFileHelper::LoadFileToString(animalImageRawDatas, *(filePath)))
	{
		TArray<FString> columns;
		int32 columnNum;
		columnNum = animalImageRawDatas.ParseIntoArrayLines(columns) - 1; // ù �� ����

		// code���� ���� ImagePartsNum ��ŭ �߶� ���
		for (int i = 0; i < (columnNum / ImagePartsNum); ++i)
		{
			FAnimalImageData animationImageData;
			animationImageData.AnimalCode = columns[i * ImagePartsNum + 1].Left(4);

			for (int j = 0; j < ImagePartsNum; ++j)
			{
											// ù �� ����
				FString rawRows = columns[j + i * ImagePartsNum + 1];

				TArray<FString> rows;
				rawRows.ParseIntoArray(rows, delims);
				animationImageData.TextureNames.Add(partsNames[j], rows[0]);

				// 2d ��ǥ ������
				// Code ���̱� ������ ù ���� �����մϴ�.
				FVector2Ds vectors;
				for (int k = 1; k < rows.Num(); k+=2)
				{
					double x, y;
					FDefaultValueHelper::ParseDouble(rows[k], x);
					FDefaultValueHelper::ParseDouble(rows[k + 1], y);

					vectors.Vector2Ds.Push(FVector2D(x, y));
				}

				animationImageData.ImageVector2DDatas.Add(partsNames[j], vectors);
				AnimalImageDatas.Add(animationImageData.AnimalCode, animationImageData);
			}
		}
	}
	else
	{
		UKismetSystemLibrary::PrintString(GetWorld(), filePath);
	}
}
