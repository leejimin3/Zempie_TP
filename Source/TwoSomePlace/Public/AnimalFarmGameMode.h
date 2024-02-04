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

/*
	- 동물의 Parts 정보를 저장하는 구조체
	- csv파일로 부터 로딩 후, AnimalImageData에 저장합니다.
*/
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
	UClass* ChildType;

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
		자식을 생성할때 사용할 동물 클래스
	*/
	UPROPERTY(EditAnywhere, Category = "Spawn")
	UClass* ChildType;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	FVector ChildSpawnPosition;

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

	/*
		생성할 동물의 클래스
	*/
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

	/*
		코드에 해당하는 동물의 이미지 데이터를 반환
	*/
	UFUNCTION(BlueprintCallable, Category = "AnimalState | CSV Data")
	FAnimalImageData GetAnimalImageData(FString animalCode);

protected:

	/*
		생성된 동물들을 담는 컨테이너
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Animal")
	TArray<AParent_Animal*> Animals;

	/*
		LoadAnimalDatas()함수를 통해 읽어온 동물 데이터들
	*/
	UPROPERTY(VisibleAnywhere, Category = "Animal");
	TArray<FAnimalRawData> AnimalDatas;

	/*
		이미지 파츠 갯수로, 동물 종류가 담긴 .csv 파일에서 몇개의 파츠 데이터를 읽어올지 지정합니다.
	*/
	UPROPERTY(EditAnywhere, Category = "Animal Image")
	int ImagePartsNum = 4;

	/*
		동물 이미지 데이터를 동물 코드를 통해 찾을 수 있도록 저장합니다.
	*/
	UPROPERTY(VisibleAnywhere, Category = "Animal Image")
	TMap<FString, FAnimalImageData> AnimalImageDatas;

	/*
		현재 생성된 자식 동물
		MakeChildAnimal() 함수를 통해 생성됩니다.
	*/
	UPROPERTY(VisibleAnywhere, Category = "Animal");
	AParent_Animal* ChildAnimal = nullptr;

	/*
		csv 파일로부터 동물의 이미지 데이터를 로드합니다.
	*/
	UFUNCTION()
	void LoadAnimalImageDatas();

	/*
		csv 파일로부터 동물의 종류 데이터를 로드합니다.
	*/
	UFUNCTION()
	void LoadAnimalDatas();
};
