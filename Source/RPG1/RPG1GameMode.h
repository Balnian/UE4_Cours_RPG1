// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "RPG1GameMode.generated.h"

/**
 * 
 */
UCLASS()
class RPG1_API ARPG1GameMode : public AGameMode
{
	GENERATED_BODY()
	
   ARPG1GameMode();
   virtual void StartPlay() override;

	
	
};
