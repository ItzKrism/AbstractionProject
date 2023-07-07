// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbstractionPlayerCharacter.generated.h"

class UHealthComponent;
class UPatricleSystemComponent;

DECLARE_MULTICAST_DELEGATE(FOnInteractionStart);
DECLARE_MULTICAST_DELEGATE(FOnInteractionCancel);

UCLASS()
class ABSTRACTIONPROJECT_API AAbstractionPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAbstractionPlayerCharacter();

	FOnInteractionStart OnInteractionStart;
	FOnInteractionCancel OnInteractionCancel;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnDeath(bool IsFellOut);

	UPROPERTY(EditAnywhere)
		UHealthComponent* HealthComponent;

	//Input Bindings
	void StartInteraction();
	void StopInteraction();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* Called when the actor falls out of the world 'safely' (below KillZ and such)*/
	virtual void FellOutOfWorld(const class UDamageType& dmgType);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable)
	const bool IsAlive() const;

	UFUNCTION(BlueprintCallable)
	const float	GetCurrentHealth() const;
};