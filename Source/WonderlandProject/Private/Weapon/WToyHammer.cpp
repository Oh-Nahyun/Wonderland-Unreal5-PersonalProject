// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WToyHammer.h"
#include "Character/WPlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Interface/WHitInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

AWToyHammer::AWToyHammer()
{
 	PrimaryActorTick.bCanEverTick = true;

	WeaponBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Box"));
	WeaponBox->SetupAttachment(GetRootComponent());
	WeaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	WeaponBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace Start"));
	BoxTraceStart->SetupAttachment(GetRootComponent());
	BoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Box Trace End"));
	BoxTraceEnd->SetupAttachment(GetRootComponent());
}

void AWToyHammer::BeginPlay()
{
	Super::BeginPlay();

	WeaponBox->OnComponentBeginOverlap.AddDynamic(this, &AWToyHammer::OnBoxOverlap);
}

void AWToyHammer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWToyHammer::Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner, APawn* NewInstigator)
{
	SetOwner(NewOwner);
	SetInstigator(NewInstigator);
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	ItemMesh->AttachToComponent(InParent, TransformRules, InSocketName);
}

void AWToyHammer::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AWToyHammer::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void AWToyHammer::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const FVector Start = BoxTraceStart->GetComponentLocation();
	const FVector End = BoxTraceEnd->GetComponentLocation();

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	for (AActor* Actor : IgnoreActors)
	{
		ActorsToIgnore.AddUnique(Actor);
	}

	FHitResult BoxHit;
	UKismetSystemLibrary::BoxTraceSingle(this, Start, End, FVector(5.f, 5.f, 5.f), BoxTraceStart->GetComponentRotation(),
										 ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, BoxHit, true);

	if (BoxHit.GetActor())
	{
		IWHitInterface* HitInterface = Cast<IWHitInterface>(BoxHit.GetActor());
		if (HitInterface)
		{
			//////////////
			float WeaponSpeed = GetWeaponSpeed();
			float WeaponDamage = BaseDamage + (WeaponSpeed * 0.05f);
			AWPlayerCharacter* OwnerCharacter = Cast<AWPlayerCharacter>(GetOwner());
			if (BoxHit.GetComponent() && BoxHit.GetComponent()->IsSimulatingPhysics() && OwnerCharacter)
			{
				FVector ForceDirection = OwnerCharacter->GetWeaponForceDirection();
				float ForceScale = FMath::Clamp(WeaponSpeed * 5.f, 300.f, 3000.f);
				BoxHit.GetComponent()->AddImpulse(ForceDirection * ForceScale, NAME_None, true);
			}
			//////////////
			UGameplayStatics::ApplyDamage(BoxHit.GetActor(), WeaponDamage, GetInstigator()->GetController(), this, UDamageType::StaticClass());
			//////////////

			HitInterface->GetHit(BoxHit.ImpactPoint);
		}

		IgnoreActors.AddUnique(BoxHit.GetActor());
	}
}

float AWToyHammer::GetWeaponSpeed() const
{
	AWPlayerCharacter* OwnerCharacter = Cast<AWPlayerCharacter>(GetOwner());
	if (OwnerCharacter)
	{
		return OwnerCharacter->GetWeaponSocketSpeed();
	}
	return 0.0f;
}
