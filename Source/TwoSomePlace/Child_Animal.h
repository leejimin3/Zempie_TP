// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Child_Animal.generated.h"

UCLASS()
class TWOSOMEPLACE_API AChild_Animal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChild_Animal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimalState")
	TArray<int32> head;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimalState")
	TArray<int32> body;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimalState")
	TArray<int32> leg;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimalState")
	TArray<int32> tail;
};
