#include "AbilitySystem/Abilities/ProjectZProjectileSpell.h"

#include "Kismet/KismetSystemLibrary.h"
#include "AbilitySystemComponent.h"
#include <Interaction/CombatInterface.h>
#include "AbilitySystemBlueprintLibrary.h"
#include "Actor/Projectile.h"
#include "ProjektZ/Public/ProjektZGameplayTags.h"


void UProjectZProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UProjectZProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	// Check if the function is running on the server
	if (!GetAvatarActorFromActorInfo()->HasAuthority()) return;

	

		const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocetLocation(GetAvatarActorFromActorInfo());
		const FRotator SocketRotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		const FVector ForwardVector = SocketRotation.Vector();  // Get forward vector from rotation

		// Adjust the spawn location to be a little in front of the socket
		const float DistanceInFrontOfSocket = 100.0f;  // Distance to move forward from the socket location
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

		const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());

		FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
		EffectContextHandle.SetAbility(this);
		EffectContextHandle.AddSourceObject(CurrProjectile);

		TArray<TWeakObjectPtr<AActor>> Actors;
		Actors.Add(CurrProjectile);

		EffectContextHandle.AddActors(Actors);

		FHitResult HitResult;
		HitResult.Location = ProjectileTargetLocation;
		EffectContextHandle.AddHitResult(HitResult);


		const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), EffectContextHandle);

		const FProjektZGameplayTags GameplayTags = FProjektZGameplayTags::Get();

		for (auto& Pair : DamageTypes)
		{
			const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
			SpecHandle.Data.Get()->SetSetByCallerMagnitude(Pair.Key, ScaledDamage);
		}
		

		

		CurrProjectile->DamageEffectSpecHandle = SpecHandle;

		CurrProjectile->FinishSpawning(SpawnTransform);
	
}
