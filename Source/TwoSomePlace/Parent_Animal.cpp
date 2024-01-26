// Fill out your copyright notice in the Description page of Project Settings.


#include "Parent_Animal.h"

// Sets default values
AParent_Animal::AParent_Animal()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AParent_Animal::BeginPlay()
{
	Super::BeginPlay();

    RandomFarmAria = FVector(FMath::RandRange(LeftDownFarmAria.X, RightUpFarmAria.X),
        FMath::RandRange(LeftDownFarmAria.Y, RightUpFarmAria.Y),
        FMath::RandRange(LeftDownFarmAria.Z, RightUpFarmAria.Z));
}

// Called every frame
void AParent_Animal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (FVector::Distance(GetActorLocation(), RandomFarmAria) > 100.0f)
    {
        float MoveSpeed = FVector::Distance(GetActorLocation(), RandomFarmAria) / 2.0f;

        FVector MoveDirection = (RandomFarmAria - GetActorLocation()).GetSafeNormal();

        FVector NewLocation = GetActorLocation() + (MoveDirection * MoveSpeed * DeltaTime);
        SetActorLocation(NewLocation);
    }
}

void AParent_Animal::Set_LeftDownFarmAria(FVector _leftdownfarmaria)
{
    LeftDownFarmAria = _leftdownfarmaria;
}

void AParent_Animal::Set_RightUpFarmAria(FVector _rightupfarmaria)
{
    RightUpFarmAria = _rightupfarmaria;
}