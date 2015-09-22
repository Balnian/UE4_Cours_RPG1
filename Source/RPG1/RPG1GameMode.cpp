// Fill out your copyright notice in the Description page of Project Settings.

#include "RPG1.h"
#include "RPG1GameMode.h"



ARPG1GameMode::ARPG1GameMode()
: Super()
{
   // Changer la classe de défaut pour celle définie par le blueprint
   static ConstructorHelpers::FClassFinder<APawn> PlayerPawnObject(
      TEXT("/Game/RPG1/Blueprints/BP_RPGCharacter"));
   if (PlayerPawnObject.Class != NULL)
   {
      DefaultPawnClass = PlayerPawnObject.Class;
   }

}

void ARPG1GameMode::StartPlay()
{
   Super::StartPlay();
   StartMatch();
   if (GEngine)
   {
      GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Début du Jeu"));
   }
}