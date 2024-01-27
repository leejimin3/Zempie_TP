// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCamera.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMainCamera::AMainCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCameraComponent"));
	SetRootComponent(MainCameraComponent);
}

// Called when the game starts or when spawned
void AMainCamera::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMainCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(bMoving)
    MovingCamera();
}

void AMainCamera::MovingCamera()
{
    if (FVector::Distance(GetActorLocation(), TargetVector) > 100.0f)
    {
        float MoveSpeed = FVector::Distance(GetActorLocation(), TargetVector) / 2.0f;

        FVector MoveDirection = (TargetVector - GetActorLocation()).GetSafeNormal();

        FVector NewLocation = GetActorLocation() + (MoveDirection * MoveSpeed * 0.03f);
        SetActorLocation(NewLocation);
    }

    else
    {
        bMoving = false;
    }
}

void AMainCamera::FadeInCamera(APlayerController* playercontroller)
{
    APlayerCameraManager* cameramanager =  playercontroller->PlayerCameraManager;
    cameramanager->StartCameraFade(0.f, 1.f, 3.f, FLinearColor::Black, false, true);
}

void AMainCamera::FadeOutCamera(APlayerController* playercontroller)
{
    APlayerCameraManager* cameramanager = playercontroller->PlayerCameraManager;
    cameramanager->StartCameraFade(1.f, 0.f, 3.f, FLinearColor::Black, false, true);
}