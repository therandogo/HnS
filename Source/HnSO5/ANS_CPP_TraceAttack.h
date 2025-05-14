// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/EngineTypes.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_CPP_TraceAttack.generated.h"

/**
 * 
 */
UCLASS()
class HNSO5_API UANS_CPP_TraceAttack : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	UANS_CPP_TraceAttack();

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName BeginingSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName EndSocket;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UPrimaryDataAsset> SoftAttackDataAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SphereRadius = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIgnoreSelf = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EDrawDebugTrace::Type> DebugDraw = EDrawDebugTrace::ForOneFrame;


	UFUNCTION(BlueprintCallable)
	void TraceAttack(USkeletalMeshComponent* MeshComponent);

	UFUNCTION()
	void LoadAndUse();
	

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DamageValue = 0.0f;

	UPROPERTY()
	TArray<AActor*> ActorsToIgnore;

};
