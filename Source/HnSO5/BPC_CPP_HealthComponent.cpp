// Fill out your copyright notice in the Description page of Project Settings.


#include "BPC_CPP_HealthComponent.h"

// Sets default values for this component's properties
UBPC_CPP_HealthComponent::UBPC_CPP_HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBPC_CPP_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBPC_CPP_HealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UBPC_CPP_HealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

float UBPC_CPP_HealthComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}

bool UBPC_CPP_HealthComponent::IsDead() const
{
	return CurrentHealth < 0.0f ? true : false;
}

void UBPC_CPP_HealthComponent::SetMaxHealth(float NewMaxHealth)
{
	MaxHealth = FMath::Max(1.0f, NewMaxHealth);
}

void UBPC_CPP_HealthComponent::InitializeHealth(float InitialHealth, float InitialMaxHealth) {
	MaxHealth = FMath::Max(1.0f, InitialMaxHealth);
	CurrentHealth = FMath::Clamp(InitialHealth, 1.0f, MaxHealth);
}

void UBPC_CPP_HealthComponent::TakeDamage(float DmgRecieved)
{
	if (IsDead() || DmgRecieved < 0.0f) {
		return;
	}

	CurrentHealth -= DmgRecieved;
	OnHealthChangedSignature.Broadcast(DmgRecieved);
}

void UBPC_CPP_HealthComponent::Heal(float HealRecieved)
{
	if (IsDead() || HealRecieved < 0.0f) {
		return;
	}

	CurrentHealth = FMath::Clamp(CurrentHealth + HealRecieved, 1.0f, MaxHealth);
	OnHealthChangedSignature.Broadcast(HealRecieved);
}