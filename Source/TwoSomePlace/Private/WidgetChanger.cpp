// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetChanger.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AWidgetChanger::AWidgetChanger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWidgetChanger::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AWidgetChanger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

