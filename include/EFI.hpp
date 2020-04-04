#pragma once

// IA-32 UEFI definitions
// Based on UEFI 2.8 Specification, no guarantee on 100% compliance, though
// https://uefi.org/sites/default/files/resources/UEFI_Spec_2_8_final.pdf
// header by nat <3

#define IN
#define OUT
#define OPTIONAL
#define CONST const
#define EFIAPI

namespace EFI
{
    typedef char BOOLEAN;
    const BOOLEAN FALSE = BOOLEAN(0);
    const BOOLEAN TRUE = BOOLEAN(1);
    
    typedef signed int INTN;
    typedef unsigned int UINTN;
    
    typedef signed char INT8;
    typedef signed short INT16;
    typedef signed int INT32;
    typedef signed long INT64;
    
    typedef unsigned char UINT8;
    typedef unsigned short UINT16;
    typedef unsigned int UINT32;
    typedef unsigned long UINT64;
    
    //typedef INT64 INT128[2];
    //typedef UINT64 UINT128[2];
    
    typedef char CHAR8;
    typedef short CHAR16;
    
    typedef void VOID;
    
    typedef VOID* EFI_HANDLE;
    typedef VOID* EFI_EVENT;
    typedef UINT64 EFI_LBA;
    typedef UINTN EFI_TPL;
    
    typedef UINT32 EFI_IPv4_ADDRESS;
    
    struct EFI_GUID
    {
        UINT32 Part0{0};
        UINT32 Part1{0};
        UINT32 Part2{0};
        UINT32 Part3{0};
    };
    
    struct EFI_MAC_ADDRESS
    {
        UINT8 Data[32]{0};
    };
    
    struct EFI_IPv6_ADDRESS
    {
        UINT8 Data[16]{0};
    };
    
    static_assert(sizeof(INTN) == 4, "INTN is not 32-bit");
    static_assert(sizeof(UINTN) == 4, "UINTN is not 32-bit");
    static_assert(sizeof(INT8) == 1, "INT8 is not 8-bit");
    static_assert(sizeof(INT16) == 2, "INT16 is not 16-bit");
    static_assert(sizeof(INT32) == 4, "INT32 is not 32-bit");
    static_assert(sizeof(INT64) == 4, "INT64 is not 64-bit");
    static_assert(sizeof(UINT8) == 1, "UINT8 is not 8-bit");
    static_assert(sizeof(UINT16) == 2, "UINT16 is not 16-bit");
    static_assert(sizeof(UINT32) == 4, "UINT32 is not 32-bit");
    static_assert(sizeof(UINT64) == 4, "UINT64 is not 64-bit");
    static_assert(sizeof(CHAR8) == 1, "CHAR8 is not 8-bit");
    static_assert(sizeof(CHAR16) == 2, "CHAR16 is not 16-bit");
    static_assert(sizeof(EFI_IPv4_ADDRESS) == 4, "EFI_IPv4_ADDRESS is not 32-bit");
    static_assert(sizeof(EFI_GUID) == 16, "EFI_GUID is not 128-bit");
    static_assert(sizeof(EFI_MAC_ADDRESS) == 32, "EFI_MAC_ADDRESS is not 256-bit");
    static_assert(sizeof(EFI_IPv6_ADDRESS) == 16, "EFI_IPv6_ADDRESS is not 128-bit");
    
    static constexpr unsigned _ToEfiErrorCode(UINTN code) { return 0x80000000 | code; }
    static constexpr unsigned _ToEfiWarnCode(UINTN code) { return code; }
    enum EFI_STATUS : UINTN
    {
        EFI_SUCCESS = 0,
        
        EFI_WARN_UNKNOWN_GLYPH = _ToEfiWarnCode(1),
        EFI_WARN_DELETE_FAILURE = _ToEfiWarnCode(2),
        EFI_WARN_WRITE_FAILURE = _ToEfiWarnCode(3),
        EFI_WARN_BUFFER_TOO_SMALL = _ToEfiWarnCode(4),
        EFI_WARN_STALE_DATA = _ToEfiWarnCode(5),
        EFI_WARN_FILE_SYSTEM = _ToEfiWarnCode(6),
        EFI_WARN_RESET_REQUIRED = _ToEfiWarnCode(7),

        EFI_LOAD_ERROR = _ToEfiErrorCode(1),
        EFI_INVALID_PARAMETER = _ToEfiErrorCode(2),
        EFI_UNSUPPORTED = _ToEfiErrorCode(3),
        EFI_BAD_BUFFER_SIZE = _ToEfiErrorCode(4),
        EFI_BUFFER_TOO_SMALL = _ToEfiErrorCode(5),
        EFI_NOT_READY = _ToEfiErrorCode(6),
        EFI_DEVICE_ERROR = _ToEfiErrorCode(7),
        EFI_WRITE_PROTECTED = _ToEfiErrorCode(8),
        EFI_OUT_OF_RESOURCES = _ToEfiErrorCode(9),
        EFI_VOLUME_CORRUPTED = _ToEfiErrorCode(10),
        EFI_VOLUME_FULL = _ToEfiErrorCode(11),
        EFI_NO_MEDIA = _ToEfiErrorCode(12),
        EFI_MEDIA_CHANGED = _ToEfiErrorCode(13),
        EFI_NOT_FOUND = _ToEfiErrorCode(14),
        EFI_ACCESS_DENIED = _ToEfiErrorCode(15),
        EFI_NO_RESPONSE = _ToEfiErrorCode(16),
        EFI_NO_MAPPING = _ToEfiErrorCode(17),
        EFI_TIMEOUT = _ToEfiErrorCode(18),
        EFI_NOT_STARTED = _ToEfiErrorCode(19),
        EFI_ALREADY_STARTED = _ToEfiErrorCode(20),
        EFI_ABORTED = _ToEfiErrorCode(21),
        EFI_ICMP_ERROR = _ToEfiErrorCode(22),
        EFI_TFTP_ERROR = _ToEfiErrorCode(23),
        EFI_PROTOCOL_ERROR = _ToEfiErrorCode(24),
        EFI_INCOMPATIBLE_ERROR = _ToEfiErrorCode(25),
        EFI_SECURITY_VIOLATION = _ToEfiErrorCode(26),
        EFI_CRC_ERROR = _ToEfiErrorCode(27),
        EFI_END_OF_MEDIA = _ToEfiErrorCode(28),
        EFI_END_OF_FILE = _ToEfiErrorCode(31),
        EFI_INVALID_LANGUAGE = _ToEfiErrorCode(32),
        EFI_COMPROMISED_DATA = _ToEfiErrorCode(33),
        EFI_IP_ADDRESS_CONFLICT = _ToEfiErrorCode(34),
        EFI_HTTP_ERROR = _ToEfiErrorCode(35),
    };

    struct EFI_TABLE_HEADER
    {
        UINT64 Signature;
        UINT32 Revision;
        UINT32 HeaderSize;
        UINT32 CRC32;
        UINT32 Reserved;
    };

    struct EFI_SYSTEM_TABLE;
    struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL;
    struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
    struct EFI_RUNTIME_SERVICES;
    struct EFI_BOOT_SERVICES;
    struct EFI_CONFIGURATION_TABLE;

    static constexpr UINT64 EFI_SYSTEM_TABLE_SIGNATURE = 0x5453595320494249;
    static constexpr UINT32 CreateSystemTableRevision(
        unsigned major, unsigned minor, unsigned patch
    )
    {
        //static_assert(minor < 10, "Minor version is >= 10");
        //static_assert(patch < 10, "Patch version is >= 10");
        return (major << 16) | ((minor * 10) + patch);
    }

    static constexpr UINT32 EFI_SPECIFICATION_VERSION
        = CreateSystemTableRevision(2, 8, 0);
    static constexpr UINT32 EFI_SYSTEM_TABLE_REVISION = EFI_SPECIFICATION_VERSION;

    struct EFI_SYSTEM_TABLE
    {
        EFI_TABLE_HEADER Hdr;
        CHAR16* FirmwareVendor;
        UINT32 FirmwareRevision;
        EFI_HANDLE ConsoleInHandle;
        EFI_SIMPLE_TEXT_INPUT_PROTOCOL* ConIn;
        EFI_HANDLE ConsoleOutHandle;
        EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* ConOut;
        EFI_HANDLE StandardErrorHandle;
        EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* Stder;
        EFI_RUNTIME_SERVICES* RuntimeServices;
        EFI_BOOT_SERVICES* BootServices;
        UINTN NumberOfTableEntries;
        EFI_CONFIGURATION_TABLE* ConfigurationTable;

        bool IsValid() {
            return TableHeader.Signature == EFI_SYSTEM_TABLE_REVISION &&
                TableHeader.Revision == EFI_SYSTEM_TABLE_REVISION;
        }
    };

    extern "C"
    {
        typedef EFI_STATUS (EFIAPI *EFI_IMAGE_ENTRY_POINT)(
            IN EFI_HANDLE ImageHandle,
            IN EFI_SYSTEM_TABLE* SystemTable 
        );
    }
}
