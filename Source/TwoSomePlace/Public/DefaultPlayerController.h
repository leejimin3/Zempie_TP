// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainCamera.h"
#include "DefaultPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TWOSOMEPLACE_API ADefaultPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void SetupInputComponent() override;

	AActor* ClickActor;

	void HandleClick();
	void Init();
	
	UPROPERTY(EditAnywhere)
	FVector FirstPos;

	UPROPERTY(EditAnywhere)
	FVector SecondPos;

	int state;

	bool bcanclick;
	void SetClick();

	AMainCamera* maincamera;

protected:
	virtual void BeginPlay() override;
};
