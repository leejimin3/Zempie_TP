// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameMode.h"
#include "AnimalFarmGameMode.generated.h"

USTRUCT(BlueprintType)
struct TWOSOMEPLACE_API FAnimalData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimalState")
	FName animalName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimalState")
	TArray<FName> animalTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimalState")
	TArray<float> head;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimalState")
	TArray<float> body;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimalState")
	TArray<float> leg;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimalState")
	TArray<float> tail;
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

	UPROPERTY(EditAnywhere, Category = "AnimalState")
	UDataTable* AnimalDataTable;

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

	UPROPERTY(BlueprintReadWrite, Category = "Animal")
	TArray<AParent_Animal*> Animals;

protected:

	TMap<FName, FAnimalData> AnimalDatas;

	void LoadAnimalDatas();
};
