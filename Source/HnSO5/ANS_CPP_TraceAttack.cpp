// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_CPP_TraceAttack.h"
#include "Components/SkeletalMeshComponent.h"
#include "HnSO5/BPC_CPP_HealthComponent.h"
#include "GameFramework/Actor.h"

UANS_CPP_TraceAttack::UANS_CPP_TraceAttack()
{

}

void UANS_CPP_TraceAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

    if (MeshComp && MeshComp->GetOwner())
    {
        TraceAttack(MeshComp);
    }
}


void UANS_CPP_TraceAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyBegin(MeshComp, Animation, FrameDeltaTime, EventReference);

    if (MeshComp && MeshComp->GetOwner())
    {
        LoadAndUse();
        ActorsToIgnore.Empty();
    }
}

void UANS_CPP_TraceAttack::LoadAndUse() {
    UPrimaryDataAsset* LoadedAsset = SoftAttackDataAsset.LoadSynchronous();
    if (LoadedAsset)
    {
        // Find the Damage property
        FProperty* DamageProp = LoadedAsset->GetClass()->FindPropertyByName("Damage");
        if (DamageProp)
        {
            if (FFloatProperty* FloatProp = CastField<FFloatProperty>(DamageProp))
            {
                DamageValue = FloatProp->GetPropertyValue_InContainer(LoadedAsset);
            }
            else if (FDoubleProperty* DoubleProp = CastField<FDoubleProperty>(DamageProp))
            {
                DamageValue = (float)DoubleProp->GetPropertyValue_InContainer(LoadedAsset);
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Damage property not found in data asset"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load attack data asset!"));
    }
}


void UANS_CPP_TraceAttack::TraceAttack(USkeletalMeshComponent* MeshComponent) 
{
    FVector Startloc = MeshComponent->GetSocketLocation(BeginingSocket);
    FVector EndLoc = MeshComponent->GetSocketLocation(EndSocket);

    TArray<TEnumAsByte<EObjectTypeQuery>> DetectableObjects;
    DetectableObjects.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
    DetectableObjects.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

    bool bTraceComplex = false;
    TArray<FHitResult> OutHits;
  
    if (bIgnoreSelf)
    {
        ActorsToIgnore.Add(MeshComponent->GetOwner());

        // Ignore all skeletal mesh components of owner
        TArray<USkeletalMeshComponent*> SkeletalComps;
        MeshComponent->GetOwner()->GetComponents(SkeletalComps);
        for (USkeletalMeshComponent* SkelComp : SkeletalComps)
        {
            ActorsToIgnore.AddUnique(SkelComp->GetOwner());
        }
    }
    
    UKismetSystemLibrary::SphereTraceMultiForObjects(
        MeshComponent->GetWorld(),
        Startloc,
        EndLoc,
        SphereRadius,
        DetectableObjects,
        bTraceComplex,
        ActorsToIgnore,
        DebugDraw,
        OutHits,
        bIgnoreSelf
    );

    for (const FHitResult& Hit : OutHits) {
        AActor* HitActor = Hit.GetActor();
        
        if (HitActor) {
            UBPC_CPP_HealthComponent* HealthComp = HitActor->FindComponentByClass<UBPC_CPP_HealthComponent>();

            if (HealthComp) {
                HealthComp->TakeDamage(DamageValue);
                ActorsToIgnore.Add(HitActor);
            }
        }
    }

    return;
}