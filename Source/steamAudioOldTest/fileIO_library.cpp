// Fill out your copyright notice in the Description page of Project Settings.


#include "fileIO_library.h"
#include "Misc/LocalTimestampDirectoryVisitor.h"
/*
* 
* FString UfileIO_library::HelloUnreal(int a, int b)
{
	int foo = a + b;
	return FString("hello");
}

FString UfileIO_library::HelloUnreal2(int a, int b, int c)
{
	return FString("hello2");
}

*/


// https://forums.unrealengine.com/t/append-to-text-file-instead-of-overwrite-whats-there/323511
int UfileIO_library::appendFile(FString path, FString line)
{
	
	bool bSuccess = FFileHelper::SaveStringToFile(line, *path, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
	return int(bSuccess);
}

int UfileIO_library::addNewLine(FString path)
{
	bool bSuccess = FFileHelper::SaveStringToFile(FString("\n"), *path, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
	return int(bSuccess);
}

int UfileIO_library::writeFile(FString path, FString text)
{
	
	IPlatformFile& file = FPlatformFileManager::Get().GetPlatformFile();
	IFileHandle* handle = file.OpenWrite(*path);
	if (handle)
	{
		handle->Write((const uint8*)TCHAR_TO_ANSI(*text), text.Len());
		delete handle;
	}
	return text.Len();
}

int UfileIO_library::createCSV(FString path, FString frist_line)
{	
	if (!FPaths::FileExists(path)) {
		return writeFile(path, frist_line.Append(FString("\n")));
	}
	return 0;
}

TArray<FString> UfileIO_library::getRandomFilePaths(FString path, int count)
{
	
	TArray<FString> queue = TArray<FString>();

	
	return queue;
}

/**
Gets all the files in a given directory.'

Credits to staticvoidlol at https://forums.unrealengine.com/t/how-to-get-file-list-in-a-directory/315248/6

@param directory The full path of the directory we want to iterate over.
@param fullpath Whether the returned list should be the full file paths or just the filenames.
@param onlyFilesStartingWith Will only return filenames starting with this string. Also applies onlyFilesEndingWith if specified.
@param onlyFilesEndingWith Will only return filenames ending with this string (it looks at the extension as well!). Also applies onlyFilesStartingWith if specified.
@return A list of files (including the extension).
*/
TArray<FString> UfileIO_library::GetAllFilesInDirectory(const FString directory, const bool fullPath, const FString onlyFilesStartingWith, const FString onlyFilesWithExtension)
{
	// Get all files in directory
	TArray<FString> directoriesToSkip;
	IPlatformFile &PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	FLocalTimestampDirectoryVisitor Visitor(PlatformFile, directoriesToSkip, directoriesToSkip, false);
	PlatformFile.IterateDirectory(*directory, Visitor);
	TArray<FString> files;
	TArray<FString> names;

	for (TMap<FString, FDateTime>::TIterator TimestampIt(Visitor.FileTimes); TimestampIt; ++TimestampIt)
	{
		const FString filePath = TimestampIt.Key();
		const FString fileName = FPaths::GetCleanFilename(filePath);
		bool shouldAddFile = true;

		// Check if filename starts with required characters
		if (!onlyFilesStartingWith.IsEmpty())
		{
			const FString left = fileName.Left(onlyFilesStartingWith.Len());

			if (!(fileName.Left(onlyFilesStartingWith.Len()).Equals(onlyFilesStartingWith)))
				shouldAddFile = false;
		}

		// Check if file extension is required characters
		if (!onlyFilesWithExtension.IsEmpty())
		{
			if (!(FPaths::GetExtension(fileName, false).Equals(onlyFilesWithExtension, ESearchCase::IgnoreCase)))
				shouldAddFile = false;
		}

		// Add full path to results
		if (shouldAddFile)
		{
			files.Add(fullPath ? filePath : fileName);
		}
	}

	return files;
}

