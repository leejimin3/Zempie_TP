// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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
	AActor* ClickActor2;

	void HandleClick();
	void Init();

	FVector FirstPos;
	FVector SecondPos;

	int state;

	bool bcanclick;
	void SetClick();

	void ShowResult();

protected:
	virtual void BeginPlay() override;
};
