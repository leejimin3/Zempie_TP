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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimalState")
	TArray<int32> head;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimalState")
	TArray<int32> body;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimalState")
	TArray<int32> leg;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimalState")
	TArray<int32> tail;

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
