/**
 * jpg.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * JPG-related data types based on JPEG File Interchange Format Version 1.02.
 */

#include <stdint.h>

/**
 * Common Data Types 
 *
 * The data types in this section are essentially aliases for C/C++ 
 * primitive data types.
 *
 * See http://en.wikipedia.org/wiki/Stdint.h for more on stdint.h.
 */
typedef uint8_t  BYTE;
typedef uint32_t DWORD;
typedef int32_t  LONG;
typedef uint16_t WORD;
typedef int8_t  CHAR;

/**
 * Spiff Header
 *
 * The SPIFFHEADER structure contains information about the type, size,
 * and layout of a file that contains a JPEG.
 *
 * Adapted from http://www.fileformat.info/format/spiff/egff.htm
 */
typedef struct _SpiffHeader
{ 
    DWORD   MagicNumber; 
    WORD    HeaderLength; 
    CHAR    Identifier[6]; 
    WORD    Version; 
    BYTE    ProfileId;
    BYTE    NumberComponents;
    DWORD   ImageHeight;
    DWORD   ImageWidth;
    BYTE    ColorSpace
    BYTE    BitsPerSample;
    BYTE    CompressionType;
    BYTE    ResolutionUnits;
    DWORD   VerticalResolution;
    DWORD   HorizontalResolution; 
} SPIFFHEADER; 

/**
 * Spiff Directory Entry
 *
 * The SPIFFDIRECTORYENTRY is an optional structure contains information stored within the SPIFF file.
 *
 * Adapted from http://www.fileformat.info/format/spiff/egff.htm
 */
typedef struct _SpiffDirectoryEntry
{
    WORD  EntryMagic;   /* Directory entry magic number (FFE8h) */
    WORD  EntryLength;  /* Length of entry */
    DWORD EntryTag;     /* Identification value of the entry */
} SPIFFDIRECTORYENTRY;
