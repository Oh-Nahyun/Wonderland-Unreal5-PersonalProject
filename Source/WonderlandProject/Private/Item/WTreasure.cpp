// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/WTreasure.h"

AWTreasure::AWTreasure()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWTreasure::BeginPlay()
{
	Super::BeginPlay();
}

void AWTreasure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWTreasure::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AWTreasure::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
