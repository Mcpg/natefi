#pragma once

// IA-32 and AMD64 UEFI definitions
// Based on UEFI 2.8 Specification, no guarantee on 100% compliance, though
// https://uefi.org/sites/default/files/resources/UEFI_Spec_2_8_final.pdf
// header by nat <3

// Arch configuration - it can be either ia32 or amd64
#ifndef NATEFI_ARCH
#define NATEFI_ARCH amd64
#endif

// Some Microsoftish macros required by the standard
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
    
    typedef signed char INT8;
    typedef signed short INT16;
    typedef signed int INT32;
    typedef signed long INT64;
    
    typedef unsigned char UINT8;
    typedef unsigned short UINT16;
    typedef unsigned int UINT32;
    typedef unsigned long UINT64;

    #if NATEFI_ARCH == ia32
        typedef INT32 INTN;
        typedef UINT32 UINTN;
    #elif NATEFI_ARCH == amd64
        typedef INT64 INTN;
        typedef UINT64 UINTN;
    #else
        #error Unsupported architecture for NatEFI!
    #endif

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
    
    #if NATEFI_ARCH == ia32
        static_assert(sizeof(INTN) == 4, "INTN is not 32-bit");
        static_assert(sizeof(UINTN) == 4, "UINTN is not 32-bit");
    #elif NATEFI_ARCH == amd64
        static_assert(sizeof(INTN) == 8, "INTN is not 64-bit");
        static_assert(sizeof(UINTN) == 8, "UINTN is not 64-bit");
    #endif

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
    static constexpr UINT32 EFI_SYSTEM_TABLE_REVISION
        = EFI_SPECIFICATION_VERSION;

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

    // Event types
    static constexpr UINT32 EVT_TIMER = 0x80000000;
    static constexpr UINT32 EVT_RUNTIME = 0x40000000;
    static constexpr UINT32 EVT_NOTIFY_WAIT = 0x00000100;
    static constexpr UINT32 EVT_NOTIFY_SIGNAL = 0x00000200;
    static constexpr UINT32 EVT_SIGNAL_EXIT_BOOT_SERVICES = 0x00000201;
    static constexpr UINT32 EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE = 0x00000202;

    #define EFI_FUNC_TYPEDEF(name, ...)    \
        typedef EFI_STATUS (EFIAPI *name)( \
            __VA_ARGS__                    \    
        );
    

    // ALL the service function typedefs supported by NatEFI
    // There's a lot of them
    extern "C"
    {
        EFI_FUNC_TYPEDEF(
            EFI_IMAGE_ENTRY_POINT,
            IN EFI_HANDLE ImageHandle,
            IN EFI_SYSTEM_TABLE* SystemTable);

        // UEFI function prototypes.
        // They're just nice typedefs, see official specs for what every field
        // does.

        // Boot services

        // Event, timer, and task priority services
        EFI_FUNC_TYPEDEF(
            EFI_CREATE_EVENT,
            IN UINT32 Type,
            IN EFI_TP NotifyTpl,
            IN EFI_EVENT_NOTIFY NotifyFunction OPTIONAL,
            IN VOID* NotifyContext OPTIONAL,
            OUT EFI_EVENT* Event
            );

        EFI_FUNC_TYPEDEF(
            EFI_CREATE_EVENT_EX,
            IN UINT32 Type,
            IN EFI_TPL NotifyTpl,
            IN EFI_EVENT_NOTIFY NotifyFunction OPTIONAL,
            IN CONST VOID* NotifyContext OPTIONAL,
            IN CONST EFI_GUID* EventGroup OPTIONAL,
            OUT EFI_EVENT* Event
            );

        EFI_FUNC_TYPEDEF(
            EFI_CLOSE_EVENT,
            IN EFI_EVENT Event);

        EFI_FUNC_TYPEDEF(
            EFI_SIGNAL_EVENT,
            IN EFI_EVENT Event);

        EFI_FUNC_TYPEDEF(
            EFI_WAIT_FOR_EVENT,
            IN UINTN NumberOfEvents,
            IN EFI_EVENT* Event,
            OUT UINTN* Index);

        EFI_FUNC_TYPEDEF(
            EFI_CHECK_EVENT,
            IN EFI_EVENT Event);

        EFI_FUNC_TYPEDEF(
            EFI_SET_TIMER,
            IN EFI_EVENT Event,
            IN EFI_TIMER_DELAY Type,
            IN UINT64 TriggerTime);

        EFI_FUNC_TYPEDEF(
            EFI_RAISE_TPL,
            IN EFI_TPL NewTpl);

        EFI_FUNC_TYPEDEF(
            EFI_RESTORE_TPL,
            IN EFI_TPL OldTpl);

        // Memory allocation services
        EFI_FUNC_TYPEDEF(
            EFI_ALLOCATE_PAGES,
            IN EFI_ALLOCATE_TYPE Type,
            IN EFI_MEMORY_TYPE MemoryType,
            IN UINTN Pages,
            IN OUT EFI_PHYSICAL_ADDRESS* Memory);

        EFI_FUNC_TYPEDEF(
            EFI_FREE_PAGES,
            IN EFI_PHYSICAL_ADDRESS Memory,
            IN UINTN Pages);

        EFI_FUNC_TYPEDEF(
            EFI_GET_MEMORY_MAP,
            IN OUT UINTN* MemoryMapSize,
            IN OUT EFI_MEMORY_DESCRIPTOR* MemoryMap,
            OUT UINTN* MapKey,
            OUT UINTN* DescriptorSize,
            OUT UINT32* DescriptorVersion);

        EFI_FUNC_TYPEDEF(
            EFI_ALLOCATE_POOL,
            IN EFI_MEMORY_TYPE PoolType,
            IN UINTN Size,
            OUT VOID** Buffer);

        EFI_FUNC_TYPEDEF(
            EFI_FREE_POOL,
            IN VOID* Buffer);

        // Protocol handler services
        EFI_FUNC_TYPEDEF(
            EFI_INSTALL_PROTOCOL_INTERFACE,
            IN OUT EFI_HANDLE* Handle,
            IN EFI_GUID* Protocol,
            IN EFI_INTERFACE_TYPE InterfaceType,
            IN VOID* Interface);

        EFI_FUNC_TYPEDEF(
            EFI_UNINSTALL_PROTOCOL_INTERFACE,
            IN EFI_HANDLE Handle,
            IN EFI_GUID* Protocol,
            IN VOID* Interface);

        EFI_FUNC_TYPEDEF(
            EFI_REINSTALL_PROTOCOL_INTERFACE,
            IN EFI_HANDLE Handle,
            IN EFI_GUID* Protocol,
            IN VOID* OldInterface,
            IN VOID* NewInterface);

        EFI_FUNC_TYPEDEF(
            EFI_REGISTER_PROTOCOL_NOTIFY,
            IN EFI_GUID* Protocol,
            IN EFI_EVENT Event,
            OUT VOID** Registration);

        EFI_FUNC_TYPEDEF(
            EFI_LOCATE_HANDLE,
            IN EFI_LOCATE_SEARCH_TYPE SearchType,
            IN EFI_GUID* Protocol OPTIONAL,
            IN VOID* SearchKey OPTIONAL,
            IN OUT UINTN* BufferSize,
            OUT EFI_HANDLE* Buffer);

        EFI_FUNC_TYPEDEF(
            EFI_HANDLE_PROTOCOL,
            IN EFI_HANDLE Handle,
            IN EFI_GUID* Protocol,
            OUT VOID** Interface);

        EFI_FUNC_TYPEDEF(
            EFI_LOCATE_DEVICE_PATH,
            IN EFI_GUID* Protocol,
            IN OUT EFI_DEVICE_PATH_PROTOCOL** DevicePath,
            OUT EFI_HANDLE* Device);

        EFI_FUNC_TYPEDEF(
            EFI_OPEN_PROTOCOL,
            IN EFI_HANDLE Handle,
            IN EFI_GUID* Protocol,
            OUT VOID** Interface OPTIONAL,
            IN EFI_HANDLE AgentHandle,
            IN EFI_HANDLE ControllerHandle,
            IN UINT32 Attributes);

        EFI_FUNC_TYPEDEF(
            EFI_CLOSE_PROTOCOL,
            IN EFI_HANDLE Handle,
            IN EFI_GUID* Protocol,
            IN EFI_HANDLE AgentHandle,
            IN EFI_HANDLE ControllerHandle);

        EFI_FUNC_TYPEDEF(
            EFI_OPEN_PROTOCOL_INFORMATION,
            IN EFI_HANDLE Handle,
            IN EFI_GUID* Protocol,
            OUT EFI_OPEN_PROTOCOL_INFORMATION_ENTRY** EntryBuffer,
            OUT UINTN* EntryCount);

        EFI_FUNC_TYPEDEF(
            EFI_CONNECT_CONTROLLER,
            IN EFI_HANDLE ControllerHandle,
            IN EFI_HANDLE* DriverImageHandle OPTIONAL,
            IN EFI_DEVICE_PATH_PROTOCOL* RemainingDevicePath OPTIONAL,
            IN BOOLEAN Recursive);

        EFI_FUNC_TYPEDEF(
            EFI_DISCONNECT_CONTROLLER,
            IN EFI_HANDLE ControllerHandle,
            IN EFI_HANDLE DriverImageHandle OPTIONAL,
            IN EFI_HANDLE ChildHandle OPTIONAL);

        EFI_FUNC_TYPEDEF(
            EFI_PROTOCOLS_PER_HANDLE,
            IN EFI_HANDLE Handle,
            OUT EFI_GUID*** ProtocolBuffer,
            OUT UINTN* ProtocolBufferCount);

        EFI_FUNC_TYPEDEF(
            EFI_LOCATE_HANDLE_BUFFER,
            IN EFI_LOCATE_SEARCH_TYPE SearchType,
            IN EFI_GUID* Protocol OPTIONAL,
            IN VOID* SearchKey OPTIONAL,
            IN OUT UINTN* NoHandles,
            OUT EFI_HANDLE** Buffer);

        EFI_FUNC_TYPEDEF(
            EFI_LOCATE_PROTOCOL,
            IN EFI_GUID* Protocol,
            IN VOID* Registration OPTIONAL,
            OUT VOID** Interface);

        EFI_FUNC_TYPEDEF(
            EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES,
            IN OUT EFI_HANDLE* Handle,
            ...);

       EFI_FUNC_TYPEDEF(
            EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES,
            IN OUT EFI_HANDLE* Handle,
            ...);

        // Image services
        EFI_FUNC_TYPEDEF(
            EFI_IMAGE_LOAD,
            IN BOOLEAN BootPolicy,
            IN EFI_HANDLE ParentImageHandle,
            IN EFI_DEVICE_PATH_PROTOCOL* DevicePath
            IN VOID* SourceBuffer OPTIONAL,
            IN UINTN SourceSize,
            OUT EFI_HANDLE* ImageHandle);

        EFI_FUNC_TYPEDEF(
            EFI_IMAGE_START,
            IN EFI_HANDLE ImageHandle,
            OUT UINTN* ExitDataSize,
            OUT CHAR16** ExitData OPTIONAL);

        EFI_FUNC_TYPEDEF(
            EFI_IMAGE_UNLOAD,
            IN EFI_HANDLE ImageHandle);

        EFI_FUNC_TYPEDEF(
            EFI_EXIT,
            IN EFI_HANDLE ImageHandle,
            IN EFI_STATUS ExitStatus,
            IN UINTN ExitDataSize,
            IN CHAR16* ExitData OPTIONAL);

        EFI_FUNC_TYPEDEF(
            EFI_EXIT_BOOT_SERVICES,
            IN EFI_HANDLE ImageHandle,
            IN UINTN MapKey);

        // Miscellaneous boot services
        EFI_FUNC_TYPEDEF(
            EFI_SET_WATCHDOG_TIMER,
            IN UINTN Timeout,
            IN UINT64 WatchdogCode,
            IN UINTN DataSize,
            IN CHAR16* WatchdogData OPTIONAL);

        EFI_FUNC_TYPEDEF(
            EFI_STALL,
            IN UINTN Microseconds);

        EFI_FUNC_TYPEDEF(
            EFI_COPY_MEM,
            IN VOID* Destination,
            IN VOID* Source,
            IN UINTN Length);

        EFI_FUNC_TYPEDEF(
            EFI_SET_MEM,
            IN VOID* Buffer,
            IN UINTN Size,
            IN UINT8 Value);

        EFI_FUNC_TYPEDEF(
            EFI_GET_NEXT_MONOTONIC_COUNT,
            OUT UINT64* Count);

        EFI_FUNC_TYPEDEF(
            EFI_INSTALL_CONFIGURATION_TABLE,
            IN EFI_GUID* Guid,
            IN VOID* Table);

        EFI_FUNC_TYPEDEF(
            EFI_CALCULATE_CRC32,
            IN VOID* Data,
            IN UINTN DataSize,
            OUT UINT32* Crc32);
    }

    struct EFI_BOOT_SERVICES
    {
        EFI_TABLE_HEADER Hdr;

        //
        // Task priority services
        //
        EFI_RAISE_TPL RaiseTPL;
        EFI_RESTORE_TPL RestoreTPL;

        //
        // Memory services
        //
        EFI_ALLOCATE_PAGES AllocatePages;
        EFI_FREE_PAGES FreePages;
        EFI_GET_MEMORY_MAP GetMemoryMap;
        EFI_ALLOCATE_POOL AllocatePool;
        EFI_FREE_POOL FreePool;

        //
        // Event and timer services
        //
        EFI_CREATE_EVENT CreateEvent;
        EFI_SET_TIMER SetTimer;
        EFI_WAIT_FOR_EVENT WaitForEvent;
        EFI_SIGNAL_EVENT SignalEvent;
        EFI_CLOSE_EVENT CloseEvent;
        EFI_CHECK_EVENT CheckEvent;

        //
        // Protocol handler services
        //
        EFI_INSTALL_PROTOCOL_INTERFACE InstallProtocolInterface;
        EFI_REINSTALL_PROTOCOL_INTERFACE ReinstallProtocolInterface;
        EFI_UNINSTALL_PROTOCOL_INTERFACE UninstallProtocolInterface;
        EFI_HANDLE_PROTOCOL HandleProtocol;
        VOID* VeryUsefulAlthoughReservedField;
        EFI_REGISTER_PROTOCOL_NOTIFY RegisterProtocolNotify;
        EFI_LOCATE_HANDLE LocateHandle;
        EFI_LOCATE_DEVICE_PATH LocateDevicePath;
        EFI_INSTALL_CONFIGURATION_TABLE InstallConfigurationTable;

        //
        // Image services
        //
        EFI_IMAGE_LOAD LoadImage;
        EFI_IMAGE_START StartImage;
        EFI_EXIT Exit;
        EFI_IMAGE_UNLOAD UnloadImage;
        EFI_EXIT_BOOT_SERVICES ExitBootServices;

        //
        // Miscellaneous services
        //
        EFI_GET_NEXT_MONOTONIC_COUNT GetNextMonotonicCount;
        EFI_STALL Stall;
        EFI_SET_WATCHDOG_TIMER SetWatchdogTimer;

        //
        // DriverSupport services
        //
        EFI_CONNECT_CONTROLLER ConnectController;
        EFI_DISCONNECT_CONTROLLER DisconnectController;

        //
        // Open and close protocol services
        //
        EFI_OPEN_PROTOCOL OpenProtocol;
        EFI_CLOSE_PROTOCOL CloseProtocol;
        EFI_OPEN_PROTOCOL_INFORMATION OpenProtocolInformation;

        //
        // LibraryServices
        //
        EFI_PROTOCOLS_PER_HANDLE ProtocolsPerHandle;
        EFI_LOCATE_HANDLE_BUFFER LocateHandleBuffer;
        EFI_LOCATE_PROTOCOL LocateProtocol;
        EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES InstallMultipleProtocolInterfaces;
        EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES UninstallMultipleProtocolInterfaces;

        //
        // 32-bit CRC services
        //
        EFI_CALCULATE_CRC32 CalculateCrc32;

        //
        // Miscellaneous services
        //
        EFI_COPY_MEM CopyMem;
        EFI_SET_MEM SetMem;
        EFI_CREATE_EVENT_EX CreateEventEx;
    };
}
