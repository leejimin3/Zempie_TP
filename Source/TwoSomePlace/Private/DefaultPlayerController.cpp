// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerController.h"
#include "GameFramework/Actor.h"

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
        ClickActor = HitResult.GetActor();

        TArray<FName> ClickedObjectTags = ClickActor->Tags;

        for (auto TagName : ClickedObjectTags)
        {
            if (TagName == "Animal")
            {
                switch (state)
                {
                case 0:
                    ClickActor->SetActorLocation(FirstPos);
                    //GetWorld()->GetAuthGameMode()->//캐스팅
                    state++;
                    break;
                case 1:
                    ClickActor->SetActorLocation(SecondPos);
                    //GetWorld()->GetAuthGameMode()->//캐스팅
                    bcanclick = false;
                    ShowResult();
                    break;
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