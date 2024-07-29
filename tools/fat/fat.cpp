#include <iostream>
#include <fstream>

using namespace std;

typedef struct
{
    uint8_t BootJumpInstruction[3];
    uint8_t OemIdentifier[8];
    uint16_t BytesPerSector;
    uint8_t SectorsPerCluster;
    uint16_t ReservedSectors;
    uint8_t FatCount;
    uint16_t DirEntryCount;
    uint16_t TotalSectors;
    uint8_t MediaDescriptorType;
    uint16_t SectorsPerFat;
    uint16_t SectorsPerTrack;
    uint16_t Heads;
    uint32_t HiddenSectors;
    uint32_t LargeSectorCount;

    // extended boot record
    uint8_t DriveNumber;
    uint8_t _Reserved;
    uint8_t Signature;
    uint32_t VolumeId;
    uint8_t VolumeLabel[11];
    uint8_t SystemId[8];

} __attribute__((packed)) BootSector;

BootSector g_boot_sector;
uint8_t *g_fat = NULL;

bool read_boot_sector(ifstream &disk)
{
    disk.read(reinterpret_cast<char *>(&g_boot_sector), sizeof(g_boot_sector));
    if (!disk)
    {
        return false;
    }
    return true;
}

bool read_sectors(ifstream &disk, uint32_t lba, uint32_t count, void *buffer_out)
{
    disk.seekg(lba * g_boot_sector.BytesPerSector);
    disk.read(reinterpret_cast<char *>(buffer_out), g_boot_sector.BytesPerSector * count);

    if (!disk)
    {
        return false;
    }
    return true;
}

bool read_fat(ifstream &disk)
{
    g_fat = new uint8_t[g_boot_sector.SectorsPerFat * g_boot_sector.BytesPerSector];
    return read_sectors(disk, g_boot_sector.ReservedSectors, g_boot_sector.SectorsPerFat, g_fat);
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        cout << "Not enough argument" << endl;
        return -1;
    }
    ifstream disk(argv[1]);

    if (!read_boot_sector(disk))
    {
        cout << "Could not read boot sector" << endl;
        return -2;
    }

    if (!read_fat(disk))
    {
        cout << "Could not read fat" << endl;
        delete g_fat;
        return -2;
    }

    delete g_fat;
    disk.close();
    return 0;
}