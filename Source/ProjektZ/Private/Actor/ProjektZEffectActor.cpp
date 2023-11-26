#include "Actor/ProjektZEffectActor.h"
#include "Components/SphereComponent.h"
#include <AbilitySystemComponent.h>
#include "AbilitySystem/ProjektZAttributeSet.h"
#include <AbilitySystemInterface.h>

AProjektZEffectActor::AProjektZEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AProjektZEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: Change this to apply GameplayEffect. For now using const_cast as a hack!
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UProjektZAttributeSet* ProjektZAttributeSet = Cast<UProjektZAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UProjektZAttributeSet::StaticClass()));
		UProjektZAttributeSet* MutableProjektZAttributeSet = const_cast<UProjektZAttributeSet*>(ProjektZAttributeSet);
		MutableProjektZAttributeSet->SetHealth(ProjektZAttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void AProjektZEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}


void AProjektZEffectActor::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AProjektZEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AProjektZEffectActor::EndOverlap);
}