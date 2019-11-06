// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Cube.generated.h"

/**
 *
 */
UCLASS()
class CLIENTSERVERPROJECT_API ACube : public AStaticMeshActor
{
	GENERATED_BODY()

		//Public specifier in the constructor
public:
	//Set up ticking
	ACube();

	/*
	Adding the keyword �virtual� to a function header turns it
	into a virtual function.

	Virtual functions are used to make sure the child class
	invokes the correct function.

	What this means is that the compiler will no longer
	consider the function for static linking. Instead, which
	function gets invoke will be determined at
	runtime(dynamic linkage).

	Source code file            - C++ Proprocessor

	Expanded source code file   - Compiler

	Assembler file              - Assembler

	Object code file			- Linker

	Executable file				- .exe

	override - a safety overgaurd to make sure its spelled right
	and not creating somthing new.
	*/

	virtual void Tick(float DeltaTime)override;
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		float Speed = 20;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
		FVector TargetLocation;

private:
	FVector GlobalStartLocation;
	FVector GlobalTargetLocation;
};
