// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjektZAbilityTypes.h"
#include "ReactiveActor.h"
#include "Projectile.generated.h"


class UNiagaraSystem;
class USphereComponent;
class UProjectileMovementComponent;
UCLASS()
class PROJEKTZ_API AProjectile : public AActor, public IReactiveInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsPiercing;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int PiercingAmount;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FDamageEffectParams DamageEffectParams;

	TArray<FEffectParams> EffectParams;

	UPROPERTY(EditAnywhere, Category = "Element")
	bool bHasReacted = false;

	UPROPERTY();
	TObjectPtr<USceneComponent> HomingTargetSceneComponent;

	FGameplayTag GetElementTag_Implementation();

	void SetReacted_Implementation(bool value);

	bool HasReacted_Implementation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	void OnHit();

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyindex, bool bFromSweep, const FHitResult& SweepResult);

private:

	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 15.f;

	bool bHit = false;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> LoopingSound;

	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingSoundComponent;

	UPROPERTY(EditAnywhere)
	bool bSpawnsActors = false;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AReactiveActor> ActorToSpawn;

	TArray<TObjectPtr<AActor>> ActorsHit;
};
