// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameMode.h"
#include "AnimalFarmGameMode.generated.h"

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
	FString AnimalCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimalState")
	FString AnimalName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimalState")
	TArray<float> States;
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
	UPROPERTY(EditAnywhere, Category = "AnimalState | CSV Data")
	int AnimalDataCSVRowCount = 14;

	/*
		*.csv ������ ���� �̸��� �Է��ϸ�, /confing ������ ��ġ�մϴ�.
	*/
	UPROPERTY(EditAnywhere, Category = "AnimalState | CSV Data")
	FString AnimalDataCSVFileName;

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

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void SpawnAnimals(int animalSpawnCount);

	UFUNCTION(BlueprintCallable, Category = "InGame")
	AChild_Animal* MakeChildAnimal(const AParent_Animal* parent1, const AParent_Animal* parent2);

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Animal")
	TArray<AParent_Animal*> Animals;

	UPROPERTY();
	TArray<FAnimalRawData> AnimalDatas;

	void LoadAnimalDatas();
};
