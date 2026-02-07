// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/WMushroom.h"

AWMushroom::AWMushroom()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWMushroom::BeginPlay()
{
	Super::BeginPlay();
}

void AWMushroom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWMushroom::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AWMushroom::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

