// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "fileIO_library.generated.h"

/**
 * 
 */
UCLASS()
class STEAMAUDIOOLDTEST_API UfileIO_library : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	/*
	UFUNCTION(BlueprintCallable, Category = "fileIO")
	static FString HelloUnreal(int a, int b);

	UFUNCTION(BlueprintCallable, Category = "fileIO")
	static FString HelloUnreal2(int a, int b, int c);
	*/

	UFUNCTION(BlueprintCallable, Category = "fileIO")
	static int appendFile(FString path, FString line);

	UFUNCTION(BlueprintCallable, Category = "fileIO")
	static int writeFile(FString path, FString text);

	UFUNCTION(BlueprintCallable, Category = "fileIO")
	static int addNewLine(FString path);

	UFUNCTION(BlueprintCallable, Category = "fileIO")
	static int createCSV(FString path, FString frist_line);

	UFUNCTION(BlueprintCallable, Category = "fileIO")
	static TArray<FString> getRandomFilePaths(FString path, int count);

	UFUNCTION(BlueprintCallable, Category = "fileIO")
	static TArray<FString> GetAllFilesInDirectory(const FString directory, const bool fullPath, const FString onlyFilesStartingWith, const FString onlyFilesWithExtension);
};

