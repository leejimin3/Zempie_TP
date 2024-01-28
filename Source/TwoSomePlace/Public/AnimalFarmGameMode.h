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
	csv ���˰� ���� ����ü �����Դϴ�.
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
		csv���� ������ Row ������
		csv���Ͽ� �̻��� �ִ��� �˻��ϴµ� ����մϴ�.
	*/
	UPROPERTY(EditAnywhere, Category = "InGame")
	int AnimalDataCSVRowCount = 14;

	/*
		*.csv ������ ���� �̸��� �Է��ϸ�, /confing ������ ��ġ�մϴ�.
	*/
	UPROPERTY(EditAnywhere, Category = "AnimalState | CSV Data")
	FString AnimalDataCSVFileName;

	/*
		AnimalDataCSVFileName�� �ش��ϴ� CSV���Ͽ��� �о�� �����͸�
		��ȯ�մϴ�.
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
		animalSpawnCount��ŭ ������ �����մϴ�.
		�̹� ���忡 ������ �����Ѵٸ�, ������ ��� �����ѵ� �ٽ� �����մϴ�. (����)
	*/
	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void SpawnAnimals(int animalSpawnCount);

	/*
		parent1�� parent2�� Ư���� ���� child animal�� �����մϴ�.
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
