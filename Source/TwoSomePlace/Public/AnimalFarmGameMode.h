// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameMode.h"
#include "AnimalFarmGameMode.generated.h"

USTRUCT(BlueprintType)
struct TWOSOMEPLACE_API FVector2Ds
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector2D> Vector2Ds;
};


USTRUCT(BlueprintType)
struct TWOSOMEPLACE_API FAnimalImageData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimalState")
	FString AnimalCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimalState")
	TArray<FString> AnimalImageFileNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimalState")
	TMap<FString, FVector2Ds> ImageVector2DDatas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimalState")
	TMap<FString,FString> TextureNames;
};

/*
	csv 포맷과 맞춘 구조체 형태입니다.
*/
USTRUCT(BlueprintType)
struct TWOSOMEPLACE_API FAnimalRawData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FAnimalRawData() {}
	FAnimalRawData(const FAnimalRawData& rawData)
		:AnimalCode(rawData.AnimalCode), AnimalName(rawData.AnimalName)
	{
		for (const float& state : rawData.States)
		{
			this->States.Push(state);
		}
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimalState")
	UClass ChildType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimalState")
	FString AnimalCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimalState")
	FString AnimalName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimalState")
	TArray<float> States;

	void CopyRange(TArray<float>& outArray, const int startNum, int endNum)
	{
		for (int i = startNum; i <= endNum && i < States.Num(); ++i)
		{
			outArray.Push(States[i]);
		}
	}
};

/**
 * 
 */
class AParent_Animal;
class AChild_Animal;

UCLASS()
class TWOSOMEPLACE_API AAnimalFarmGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	
	UFUNCTION()
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
public:

	/*
		csv파일 포맷의 Row 갯수로
		csv파일에 이상이 있는지 검사하는데 사용합니다.
	*/
	UPROPERTY(EditAnywhere, Category = "InGame")
	int AnimalDataCSVRowCount = 14;

	/*
		*.csv 형태의 파일 이름을 입력하며, /confing 폴더에 위치합니다.
	*/
	UPROPERTY(EditAnywhere, Category = "AnimalState | CSV Data")
	FString AnimalDataCSVFileName;

	/*
		AnimalDataCSVFileName에 해당하는 CSV파일에서 읽어온 데이터를
		반환합니다.
	*/
	UFUNCTION(BlueprintCallable, Category = "AnimalState")
	TArray<FAnimalRawData> GetAnimalRawDatas();

	UPROPERTY(EditAnywhere, Category = "Spawn")
	FVector SpawnOrigin;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	UClass* AnimalClass;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	FVector FarmLeftDown;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	FVector FarmRightUp;

	/*
		animalSpawnCount만큼 동물을 생성합니다.
		이미 월드에 동물이 존재한다면, 동물을 모두 삭제한뒤 다시 생성합니다. (리롤)
	*/
	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void SpawnAnimals(int animalSpawnCount);

	/*
		parent1과 parent2의 특성을 섞은 child animal을 생성합니다.
	*/
	UFUNCTION(BlueprintCallable, Category = "InGame")
	AParent_Animal* MakeChildAnimal(const AParent_Animal* parent1, const AParent_Animal* parent2);

	UPROPERTY(EditAnywhere, Category = "InGame")
	FVector ParentLeftPos;

	UPROPERTY(EditAnywhere, Category = "InGame")
	FVector ParentRightPos;

	UFUNCTION(BlueprintCallable, Category = "AnimalState | CSV Data")
	FAnimalImageData GetAnimalImageData(FString animalCode);

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Animal")
	TArray<AParent_Animal*> Animals;

	UPROPERTY(VisibleAnywhere, Category = "Animal");
	TArray<FAnimalRawData> AnimalDatas;

	void LoadAnimalDatas();

	UPROPERTY(EditAnywhere, Category = "Animal Image")
	int ImagePartsNum = 4;

	UPROPERTY(VisibleAnywhere, Category = "Animal Image")
	TMap<FString, FAnimalImageData> AnimalImageDatas;

	void LoadAnimalImageDatas(FString fileName);

	UPROPERTY(VisibleAnywhere, Category = "Animal");
	AParent_Animal* ChildAnimal = nullptr;
};
