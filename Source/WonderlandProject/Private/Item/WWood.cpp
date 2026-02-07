// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/WWood.h"

AWWood::AWWood()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWWood::BeginPlay()
{
	Super::BeginPlay();
}

void AWWood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWWood::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AWWood::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
