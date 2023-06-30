#include "PEHelper.h"
#include <fstream>
#include <iostream>
#include "SfFile.h"
#include <Windows.h>
#include <filesystem>

bool CreateDirectories(const std::wstring& filePath) {
    std::filesystem::path directoryPath(filePath);
    directoryPath.remove_filename();

    if (directoryPath.empty() || directoryPath.filename() == directoryPath) {
        return true;
    }

    try {
        std::filesystem::create_directories(directoryPath);
    }
    catch (const std::exception& ex) {
        std::cerr << "Failed to create directory: " << directoryPath << std::endl;
        std::cerr << "Error message: " << ex.what() << std::endl;
        return false;
    }

    return true;
}

bool FilePathEndsWithExe(const char* filePath) {
    size_t length = std::strlen(filePath);
    if (length >= 4) {
        const char* extension = filePath + length - 4;
        return (std::strcmp(extension, ".exe") == 0);
    }
    return false;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "No file path provided." << std::endl;
        return 1;
    }


    const char* path = argv[1];

    if (!FilePathEndsWithExe(path)) 
    {
        std::cerr << "File doesn't appear to be an exe..." << std::endl;
        return 1;
    }

    size_t narrowStrLen = strlen(path) + 1; 
    size_t wideStrSize = 0;
    wchar_t* wideStr = nullptr;
    mbstowcs_s(&wideStrSize, nullptr, 0, path, 0);
    wideStr = new wchar_t[wideStrSize];
    mbstowcs_s(nullptr, wideStr, wideStrSize, path, narrowStrLen);

    SetupFactoryFile* sfInst = OpenInstaller(wideStr);
    if ((sfInst != nullptr) && (sfInst->EnumFiles() > 0))
    {
        std::cout << "Setup Factory " << sfInst->GetVersion() << std::endl;
        switch (sfInst->GetCompression())
        {
        case COMP_NONE:
            std::cout << "Compression: None" << std::endl;
            break;
        case COMP_PKWARE:
            std::cout << "Compression: PKWare DCL" << std::endl;
            break;
        case COMP_LZMA:
            std::cout << "Compression: LZMA" << std::endl;
            break;
        case COMP_LZMA2:
            std::cout << "Compression: LZMA2" << std::endl;
            break;
        default:
            std::cout << "Compression: Unknown" << std::endl;
            break;
        }

        std::cout << "File Count: " << sfInst->GetCount() << std::endl;

        for (int i = 0; i < sfInst->GetCount(); i++)
        {
            SFFileEntry fileEntry = sfInst->GetFile(i);
            std::wstring wstr(fileEntry.LocalPath.begin(), fileEntry.LocalPath.end());
            const wchar_t* wcharPath = wstr.c_str();
            if (CreateDirectories(wcharPath)) {
                AStream* outStream = CFileStream::Open(wcharPath, false, true);
                if (!outStream)
                {
                    std::cerr << "Failed to get outstream for file " + fileEntry.LocalPath << std::endl;
                    continue;
                }
                std::cout << "Extracting " << fileEntry.LocalPath << std::endl;
                sfInst->ExtractFile(i, outStream);
            }
            else
            {
                continue;
            }
        }
    }

    if (sfInst != nullptr)
    {
        FreeInstaller(sfInst);
    }

   
    delete[] wideStr;
    return 0;
}