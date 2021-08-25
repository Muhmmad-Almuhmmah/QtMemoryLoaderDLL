#include <DllLoader.h>
#include <QFile>
void LoadFromMemory(void)
{
    QD("------------------------------ LoadFromMemory ------------------------------");
    void *data;
    size_t size;
    HMEMORYMODULE handle;
    addNumberProc addNumber;
    HMEMORYRSRC resourceInfo;
    DWORD resourceSize;
    LPVOID resourceData;
    TCHAR buffer[100];

    data = ReadLibrary(&size);
    if (data == NULL)
    {
        return;
    }

    handle = MemoryLoadLibrary(data, size);
    if (handle == NULL)
    {
        QD("Can't load library from memory.");
        goto exit;
    }

    QD("DLL Handle :"<<handle);

    addNumber = (addNumberProc)MemoryGetProcAddress(handle, "addNumbers");
    QD("From memory: "<<addNumber(55, 5435));

    resourceInfo = MemoryFindResource(handle, MAKEINTRESOURCE(VS_VERSION_INFO), RT_VERSION);
    QD(QString().asprintf("MemoryFindResource returned 0x%p", resourceInfo));

    resourceSize = MemorySizeofResource(handle, resourceInfo);
    resourceData = MemoryLoadResource(handle, resourceInfo);
    QD(QString().asprintf("Memory resource data: %ld bytes at 0x%p", resourceSize, resourceData));

    MemoryLoadString(handle, 1, buffer, sizeof(buffer));
     QD("[RC]String1: "<<QString::fromWCharArray(buffer));

    MemoryLoadString(handle, 20, buffer, sizeof(buffer));
    QD("[RC]String2: "<<QString::fromWCharArray(buffer));

    MemoryFreeLibrary(handle);

exit:
    free(data);
}

void LoadFromFile(void)
{
    QD("------------------------------ LoadFromFile ------------------------------");
    addNumberProc addNumber;
    HRSRC resourceInfo;
    DWORD resourceSize;
    LPVOID resourceData;
    TCHAR buffer[100];

    HINSTANCE handle = LoadLibrary(DLL_FILE);
    if (handle == NULL){
        QD("Can't open DLL file "<<QString::fromWCharArray(DLL_FILE));
        return;
    }

    QD("DLL Handle :"<<handle);

    addNumber = (addNumberProc)GetProcAddress(handle, "addNumbers");
    QD("From file: "<<addNumber(77, 66));

    resourceInfo = FindResource(handle, MAKEINTRESOURCE(VS_VERSION_INFO), RT_VERSION);
    QD(QString().asprintf("FindResource returned 0x%p\n",resourceInfo));

    resourceSize = SizeofResource(handle, resourceInfo);
    resourceData = LoadResource(handle, resourceInfo);
    QD(QString().asprintf("Resource data: %ld bytes at 0x%p\n", resourceSize, resourceData));

    LoadString(handle, 1, buffer, sizeof(buffer));
    QD("[RC]String1: "<<QString::fromWCharArray(buffer));

    LoadString(handle, 20, buffer, sizeof(buffer));
    QD("[RC]String2: "<<QString::fromWCharArray(buffer));

    FreeLibrary(handle);
}


void LoadFromMemoryResourceQT(void)
{
    QD("------------------------------ LoadFromMemoryResoureQT ------------------------------");
    QByteArray data;
    size_t size;
    HMEMORYMODULE handle;
    addNumberProc addNumber;
    HMEMORYRSRC resourceInfo;
    DWORD resourceSize;
    LPVOID resourceData;
    TCHAR buffer[100];
    QFile dllRes("://testDLL/SampleDLL.dll");
    if(!dllRes.open(QIODevice::ReadOnly)){
        QD("Can't open DLL file "<<QString::fromWCharArray(DLL_FILE));
        return;
    }
    data=dllRes.readAll();
    dllRes.close();
    size=data.length();
    handle = MemoryLoadLibrary(data.data(), size);
    if (handle == NULL)
    {
        QD("Can't load library from memory.");
        return;
    }
    QD("DLL Handle :"<<handle);
    addNumber = (addNumberProc)MemoryGetProcAddress(handle, "addNumbers");
    QD("From memory[QT Resource]: "<<addNumber(55, 5435));

    resourceInfo = MemoryFindResource(handle, MAKEINTRESOURCE(VS_VERSION_INFO), RT_VERSION);
    QD(QString().asprintf("MemoryFindResource returned 0x%p", resourceInfo));

    resourceSize = MemorySizeofResource(handle, resourceInfo);
    resourceData = MemoryLoadResource(handle, resourceInfo);
    QD(QString().asprintf("Memory resource data: %ld bytes at 0x%p", resourceSize, resourceData));

    MemoryLoadString(handle, 1, buffer, sizeof(buffer));
     QD("[RC]String1: "<<QString::fromWCharArray(buffer));

    MemoryLoadString(handle, 20, buffer, sizeof(buffer));
    QD("[RC]String2: "<<QString::fromWCharArray(buffer));

    MemoryFreeLibrary(handle);
}

int main()
{
    LoadFromFile();
    LoadFromMemory();
    LoadFromMemoryResourceQT();
    return 0;
}
