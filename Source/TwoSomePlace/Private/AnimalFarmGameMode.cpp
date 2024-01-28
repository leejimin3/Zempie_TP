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
	LoadAnimalImageDatas(TEXT("ImageDataTest.csv"));

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

	//check(GetWorld() != nullptr);

	TArray<FAnimalRawData> animalDatas = AnimalDatas;

	FTransform defaultTransform({0.0f,0.0f,0.0f}, SpawnOrigin);
	// upper player		
	for (int i = 0; i < animalSpawnCount; ++i)
	{
		AParent_Animal* animal = GetWorld()->SpawnActorDeferred<AParent_Animal>(AnimalClass, defaultTransform);

		int animalTypeIndex = UKismetMathLibrary::RandomIntegerInRange(0, animalDatas.Num() - 1);
		
		FAnimalRawData animalData = animalDatas[animalTypeIndex];
		// 성능 안좋음 매번 크기 재설정
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
	// 임시 코드
	/*FTransform spawnTransform(FRotator(), SpawnOrigin);
	childAnimal = GetWorld()->SpawnActorDeferred<AParent_Animal>(AnimalClass, spawnTransform);
	childAnimal->Set_LeftDownFarmAria(FarmLeftDown);
	childAnimal->Set_RightUpFarmAria(FarmRightUp);
	childAnimal->FinishSpawning(spawnTransform);*/

	// 반복문으로 일괄 처리하기 위한 처리
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

	// parent1, parent2의 특성을 random하게 child에게 물려주는 로직
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
	FString path = TEXT("C:/") + AnimalDataCSVFileName;
	const TCHAR* delims = {TEXT(",")};
	if (FFileHelper::LoadFileToString(csvRawData, *(path)))
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
	/*for (const FAnimalRawData& rawData : AnimalDatas)
	{
		UKismetSystemLibrary::PrintString(GetWorld(), rawData.AnimalCode);
		UKismetSystemLibrary::PrintString(GetWorld(), rawData.AnimalName);

		for (const float& state : rawData.States)
		{
			UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%f"), state));
		}
	}*/
}

void AAnimalFarmGameMode::LoadAnimalImageDatas(FString fileName)
{
	const TArray<FString> partsNames = { TEXT("Body"), TEXT("Head") , TEXT("Leg") , TEXT("Tail") };
	const TCHAR* delims = { TEXT(",")};
	FString path = TEXT("C:/") + fileName;
	FString animalImageRawDatas;
	if (FFileHelper::LoadFileToString(animalImageRawDatas, *(path)))
	{
		TArray<FString> columns;
		int32 columnNum;
		columnNum = animalImageRawDatas.ParseIntoArrayLines(columns) - 1; // 첫 행 제외

		// code별로 구분 ImagePartsNum 만큼 잘라서 계산
		for (int i = 0; i < (columnNum / ImagePartsNum); ++i)
		{
			FAnimalImageData animationImageData;
			animationImageData.AnimalCode = columns[i * ImagePartsNum + 1].Left(4);

			for (int j = 0; j < ImagePartsNum; ++j)
			{
											// 첫 행 제외
				FString rawRows = columns[j + i * ImagePartsNum + 1];

				TArray<FString> rows;
				rawRows.ParseIntoArray(rows, delims);
				animationImageData.TextureNames.Add(partsNames[j], rows[0]);

				// 2d 좌표 데이터
				// Code 값이기 때문에 첫 행은 제외합니다.
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

		/*for (auto&[key, val] : AnimalImageDatas)
		{
			UKismetSystemLibrary::PrintString(GetWorld(), key);
			for (auto& [_key, _val] : val.ImageVector2DDatas)
			{
				UKismetSystemLibrary::PrintString(GetWorld(), _key);
				for (auto& __val : _val.Vector2Ds)
				{
					UKismetSystemLibrary::PrintString(GetWorld(), __val.ToString());
				}
			}
		}*/
	}
	else
	{
		UKismetSystemLibrary::PrintString(GetWorld(), *(FPaths::ProjectConfigDir() + fileName));
	}
}
