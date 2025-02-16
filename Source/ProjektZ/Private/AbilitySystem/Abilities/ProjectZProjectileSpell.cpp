#include "AbilitySystem/Abilities/ProjectZProjectileSpell.h"

#include "Kismet/KismetSystemLibrary.h"
#include "AbilitySystemComponent.h"
#include <Interaction/CombatInterface.h>
#include "AbilitySystemBlueprintLibrary.h"
#include "Actor/Projectile.h"
#include "ProjektZ/Public/ProjektZGameplayTags.h"
#include "GameFramework/ProjectileMovementComponent.h"



void UProjectZProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UProjectZProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag)
{
	// Check if the function is running on the server
	if (!GetAvatarActorFromActorInfo()->HasAuthority()) return;

		const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocetLocation(GetAvatarActorFromActorInfo(),SocketTag);
		const FRotator SocketRotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		const FVector ForwardVector = SocketRotation.Vector();  // Get forward vector from rotation

		// Adjust the spawn location to be a little in front of the socket
		const float DistanceInFrontOfSocket = 50.0f;  // Distance to move forward from the socket location
		const FVector AdjustedLocation = SocketLocation + (ForwardVector * DistanceInFrontOfSocket);

		FRotator Rotation = (ProjectileTargetLocation - AdjustedLocation).Rotation();
		//Rotation.Pitch = 0.0f;

		// Create a transform for the spawn location and rotation
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(AdjustedLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());

		// Spawn the projectile using deferred spawning method
		AProjectile* CurrProjectile = GetWorld()->SpawnActorDeferred<AProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		CurrProjectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
		CurrProjectile->EffectParams = EffectParams;

		CurrProjectile->IsPiercing = IsPiercing;
		CurrProjectile->PiercingAmount = PiercingAmount;

		CurrProjectile->FinishSpawning(SpawnTransform);
		
}

void UProjectZProjectileSpell::SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, int AmountOfProjectiles, AActor* HomingTarget)
{
	if (!GetAvatarActorFromActorInfo()->HasAuthority()) return;

	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocetLocation(GetAvatarActorFromActorInfo(), SocketTag);
	const FRotator SocketRotation = (ProjectileTargetLocation - SocketLocation).Rotation();

	const FVector ForwardVector = SocketRotation.Vector();

	const float DistanceInFrontOfSocket = 50.0f;
	const FVector AdjustedLocation = SocketLocation + (ForwardVector * DistanceInFrontOfSocket);

	FRotator Rotation = (ProjectileTargetLocation - AdjustedLocation).Rotation();

	FVector LeftOfSpread = ForwardVector.RotateAngleAxis(-45.f, FVector::UpVector);

	if (AmountOfProjectiles > 1)
	{
		float DeltaSpread = 90 / AmountOfProjectiles - 1;
		for (int i = 0; i < AmountOfProjectiles; i++)
		{
			FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
			FTransform SpawnTransform;
			SpawnTransform.SetLocation(AdjustedLocation);
			SpawnTransform.SetRotation(Direction.Rotation().Quaternion());

			AProjectile* CurrProjectile = GetWorld()->SpawnActorDeferred<AProjectile>(
				ProjectileClass,
				SpawnTransform,
				GetOwningActorFromActorInfo(),
				Cast<APawn>(GetOwningActorFromActorInfo()), 
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

			CurrProjectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
			CurrProjectile->EffectParams = EffectParams;
			
			CurrProjectile->IsPiercing = IsPiercing;
			CurrProjectile->PiercingAmount = PiercingAmount;

			if (IsHomingProjectile) 
			{
				if (HomingTarget && HomingTarget->Implements<UCombatInterface>())
				{
					CurrProjectile->ProjectileMovement->HomingTargetComponent = HomingTarget->GetRootComponent();
				}
				else
				{
					CurrProjectile->HomingTargetSceneComponent = NewObject<USceneComponent>(USceneComponent::StaticClass());
					CurrProjectile->HomingTargetSceneComponent->AttachToComponent(CurrProjectile->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
					CurrProjectile->HomingTargetSceneComponent->SetWorldLocation(ProjectileTargetLocation);
					CurrProjectile->ProjectileMovement->HomingTargetComponent = CurrProjectile->HomingTargetSceneComponent;
				}

				CurrProjectile->ProjectileMovement->HomingAccelerationMagnitude = HomingAcceleration;
				CurrProjectile->ProjectileMovement->bIsHomingProjectile = IsHomingProjectile;
			}

			CurrProjectile->FinishSpawning(SpawnTransform);
		}
	}
	else
	{

	}
	
}

void UProjectZProjectileSpell::SpawnProjectileWithGivenLocation(const FVector& ProjectileTargetLocation, const FVector& ProjectileSpawnLocation, const FRotator& ProfectileSpawnRotation)
{
	// Check if the function is running on the server
	if (!GetAvatarActorFromActorInfo()->HasAuthority()) return;

	// Create a transform for the spawn location and rotation
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(ProjectileSpawnLocation);
	SpawnTransform.SetRotation(ProfectileSpawnRotation.Quaternion());

	// Spawn the projectile using deferred spawning method
	AProjectile* CurrProjectile = GetWorld()->SpawnActorDeferred<AProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	CurrProjectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
	CurrProjectile->EffectParams = EffectParams;

	CurrProjectile->IsPiercing = IsPiercing;
	CurrProjectile->PiercingAmount = PiercingAmount;

	CurrProjectile->FinishSpawning(SpawnTransform);

}
