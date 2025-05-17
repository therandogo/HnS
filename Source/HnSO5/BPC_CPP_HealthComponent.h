// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BPC_CPP_HealthComponent.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HNSO5_API UBPC_CPP_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBPC_CPP_HealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HealthParameters")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HealthParameters")
	float CurrentHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ChangeHealthParameters")
	float TotalDamageRecieved;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ChangeHealthParameters")
	float TotalHealRecieved;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintPure, Category = "HealthFunctions")
	float GetCurrentHealth() const;

	UFUNCTION(BlueprintPure, Category = "HealthFunctions")
	bool IsDead() const;

	UFUNCTION(BlueprintCallable, Category = "ChangeHealthFunctions")
	void SetMaxHealth(float NewMaxHealth);

	UFUNCTION(BlueprintCallable, Category = "ChangeHealthFunctions")
	void InitializeHealth(float InitialHealth, float InitialMaxHealth);

	UFUNCTION(BlueprintCallable, Category = "ChangeHealthFunctions")
	void TakeDamage(float DmgRecieved);

	UFUNCTION(BlueprintCallable, Category = "ChangeHealthFunctions")
	void Heal(float HealRecieved);

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedSignature OnHealthChangedSignature;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedSignature OnDeathSignature;
};
