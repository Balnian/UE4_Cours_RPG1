// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "RPGCharacter.generated.h"

UCLASS()
class RPG1_API ARPGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPGCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

   // Avancer (ou Reculer si -1)
   UFUNCTION()
      void Avancer(float Val);

   // Glisser vers la droite ( ou vers la gauche si -1 )
   UFUNCTION()
      void VersLaDroite(float Val);
   //On active le bool�en bPressedJump 
   UFUNCTION() 
      void OnStartJump(); 
   // On d�sactive le bool�en bPressedJump 
   UFUNCTION() 
      void OnStopJump();

   /** Cam�ra premi�re personne */ 
   UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
      UCameraComponent* ThirdPersonCameraComponent;

   /** Composant Spring Arm */ 
   UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera) 
      USpringArmComponent* SpringArmComponent;

   /** Vitesse de d�placement */ 
   UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mouvement") 
      float Vitesse;

   /** Touche Run Active */ 
   UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera) 
      bool bPressedRun;

   //On active le bool�en bPressedRun 
   UFUNCTION() 
      void OnStartRunning(); 
   // On d�sactive le bool�en bPressedRun 
   UFUNCTION() 
      void OnStopRunning();

   //On active le bool�en bPressedRun 
   UFUNCTION(BlueprintCallable, Category = "Mouvement") 
      bool IsRunning();
};