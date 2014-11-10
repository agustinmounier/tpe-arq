/***************************************************
  Defs.h
	
****************************************************/

#ifndef _defs_
#define _defs_

#define byte unsigned char
#define word short int
#define dword int
#define uchar unsigned char
#define uint unsigned int
#define ushort unsigned short int

/* Flags para derechos de acceso de los segmentos */
#define ACS_PRESENT     0x80            /* segmento presente en memoria */
#define ACS_CSEG        0x18            /* segmento de codigo */
#define ACS_DSEG        0x10            /* segmento de datos */
#define ACS_READ        0x02            /* segmento de lectura */
#define ACS_WRITE       0x02            /* segmento de escritura */
#define ACS_IDT         ACS_DSEG
#define ACS_INT_386 	0x0E		/* Interrupt GATE 32 bits */
#define ACS_INT         ( ACS_PRESENT | ACS_INT_386 )


#define ACS_CODE        (ACS_PRESENT | ACS_CSEG | ACS_READ)
#define ACS_DATA        (ACS_PRESENT | ACS_DSEG | ACS_WRITE)
#define ACS_STACK       (ACS_PRESENT | ACS_DSEG | ACS_WRITE)

#pragma pack (1) 		/* Alinear las siguiente estructuras a 1 byte */

/* Descriptor de segmento */
typedef struct {
  word limit,
       base_l;
  byte base_m,
       access,
       attribs,
       base_h;
} DESCR_SEG;


/* Descriptor de interrupcion */
typedef struct {
  word      offset_l,
            selector;
  byte      cero,
            access;
  word	    offset_h;
} DESCR_INT;

/* IDTR  */
typedef struct {
  word  limit;
  dword base;
} IDTR;

/* Sacado de http://wiki.osdev.org/System_Management_BIOS */

typedef struct {

 	char EntryPointString[4];    //This is _SM_
 	uchar Checksum;              //This value summed with all the values of the table, should be 0 (overflow)
 	uchar Length;                //Length of the Entry Point Table. Since version 2.1 of SMBIOS, this is 0x1F
 	uchar MajorVersion;          //Major Version of SMBIOS
 	uchar MinorVersion;          //Minor Version of SMBIOS
 	ushort MaxStructureSize;     //Maximum size of a SMBIOS Structure (we will se later)
 	uchar EntryPointRevision;    //...
 	char FormattedArea[5];       //...
 	char EntryPointString2[5];   //This is _DMI_
 	uchar Checksum2;             //Checksum for values from EntryPointString2 to the end of table
 	ushort TableLength;          //Length of the Table containing all the structures
 	uint TableAddress;	     //Address of the Table
 	ushort NumberOfStructures;   //Number of structures in the table
 	uchar BCDRevision;           //Unused

} SMBIOSEntryPoint;     

#endif

