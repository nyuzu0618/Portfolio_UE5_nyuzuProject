// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjBase.generated.h"

class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class NYUZUPORTFOLIO_API AObjBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjBase();


	//有効・無効の切り替え（無効時は非表示・当たり判定なし）
	UFUNCTION(BlueprintCallable, Category = "Object")
	void SetObjectActive(bool bNewActive);

	UFUNCTION(BlueprintPure, Category = "Object")
	bool IsObjectActive() const { return bIsActive; }

	FName GetObjectID() const { return ObjectID; }
	FText GetObjectDisplayName() const { return DisplayName; }
	FText GetObjectDescription() const { return Description; }

	UStaticMeshComponent* GetMeshComponent() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	//BeginPlay　で呼ばれる初期化。派生クラスで overrideする場合はSuperを呼ぶこと
	UFUNCTION(BlueprintCallable, Category = "Object")
	virtual void InitializeObject();


private:
	//オブジェクトの基本情報
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Object", meta = (AllowPrivateAccess = "true"))
	FName ObjectID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Object", meta = (AllowPrivateAccess = "true"))
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Object", meta = (AllowPrivateAccess = "true"))
	FText Description;


	//オブジェクトの見た目

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> MeshComponent;


	//有効・無効状態
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Object", meta = (AllowPrivateAccess = "true"))
	bool bIsActive = true;

};
