#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Parent_Animal.generated.h"

UCLASS()
class TWOSOMEPLACE_API AParent_Animal : public AActor
{
	GENERATED_BODY()
	
public:	
	AParent_Animal();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AnimalState")
	TArray<FString> animalCodes;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AnimalState")
	TArray<float> head;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AnimalState")
	TArray<float> body;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AnimalState")
	TArray<float> leg;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AnimalState")
	TArray<float> tail;

	UPROPERTY(EditAnywhere)
	FVector LeftDownFarmAria;

	UFUNCTION()
	void Set_LeftDownFarmAria(FVector _leftdownfarmaria);

	UPROPERTY(EditAnywhere)
	FVector RightUpFarmAria;

	UFUNCTION()
	void Set_RightUpFarmAria(FVector _rightupfarmaria);

	UPROPERTY(EditAnywhere)
	FVector RandomFarmAria;

	bool barrive;
};
