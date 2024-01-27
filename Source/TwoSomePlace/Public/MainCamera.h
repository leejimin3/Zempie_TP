// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "MainCamera.generated.h"

UCLASS()
class TWOSOMEPLACE_API AMainCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMainCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* MainCameraComponent;

	UPROPERTY(EditAnyWhere)
	FVector TargetVector;

	UFUNCTION()
	void MovingCamera();

	UFUNCTION(BlueprintCallable)
	void FadeOutCamera(APlayerController* playercontroller);

	UFUNCTION(BlueprintCallable)
	void FadeInCamera(APlayerController* playercontroller);

	FTimerHandle FadeTImerHandle;

	UPROPERTY(EditAnyWhere)
	bool bMoving;
};
