// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerController.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Misc/DefaultValueHelper.h"

#include "../Parent_Animal.h"

#include "AnimalFarmGameMode.h"

void ADefaultPlayerController::Init()
{
    FirstPos = FVector(-200.000016f, 310.000000f, -300.f);
    SecondPos = FVector(200.000016f, 310.000000f, -300.f);
    state = 0;
}

void ADefaultPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAction("Click", IE_Pressed, this, &ADefaultPlayerController::HandleClick);
}

void ADefaultPlayerController::BeginPlay()
{
    Super::BeginPlay();

    Init();
    SetShowMouseCursor(true);

    FTimerHandle timerhandle;
    GetWorldTimerManager().SetTimer(timerhandle, this, &ADefaultPlayerController::SetClick, 2.0f, false);
}

void ADefaultPlayerController::HandleClick()
{
    if (!bcanclick) return;

    FHitResult HitResult;
    GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, HitResult);

    if (HitResult.GetActor())
    {
        AActor* _ClickedActor = HitResult.GetActor();

        TArray<FName> ClickedObjectTags = _ClickedActor->Tags;

        for (auto TagName : ClickedObjectTags)
        {
            if (TagName == "Animal")
            {
                switch (state)
                {
                case 0:
                {
                    AAnimalFarmGameMode* gameMode = Cast<AAnimalFarmGameMode>(GetWorld()->GetAuthGameMode());

                    _ClickedActor->SetActorLocation(gameMode->ParentLeftPos);
                    ClickActor = _ClickedActor;
                    state++;
                    break;
                }
                case 1:
                {
                    AAnimalFarmGameMode* gameMode = Cast<AAnimalFarmGameMode>(GetWorld()->GetAuthGameMode());

                    _ClickedActor->SetActorLocation(gameMode->ParentRightPos);
                    ClickActor2 = _ClickedActor;

                    AParent_Animal* parentAnimal1 = Cast<AParent_Animal>(ClickActor);
                    AParent_Animal* parentAnimal2 = Cast<AParent_Animal>(ClickActor2);

                    check(gameMode != nullptr);

                    AParent_Animal* childAnimal = gameMode->MakeChildAnimal(parentAnimal1, parentAnimal2);
                    /*
                        child animal 생성됨

                        animalCodes[4] -> 각 부위가 누구로부터 왔는지를 의미
                        0 -> head
                        1 -> body
                        2 -> leg
                        3 -> tail
                    */

                    bcanclick = false;
                    ShowResult();
                    break;
                }
                }
            }
        }
    }
}

void ADefaultPlayerController::ShowResult()
{

}

void ADefaultPlayerController::SetClick()
{
    bcanclick = true;
}