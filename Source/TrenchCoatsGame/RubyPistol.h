// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RubyPistol.generated.h"

UCLASS()
class TRENCHCOATSGAME_API ARubyPistol : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARubyPistol();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool pickedUp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool leftHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool rightHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ammoClip;


	
};
