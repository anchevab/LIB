/*
	tinyFAT.h - Arduino library support FAT16 on SD cards
	Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved

	This library has been made to easily use SD card with the Arduino.

	You can find the latest version of the library at 
	http://www.RinkyDinkElectronics.com/

	This library is free software; you can redistribute it and/or
	modify it under the terms of the CC BY-NC-SA 3.0 license.
	Please see the included documents for further information.

	Commercial use of this library requires you to buy a license that
	will allow commercial use. This includes using the library,
	modified or not, as a tool to sell products.

	The license applies to all part of the library including the 
	examples and tools supplied with the library.
*/
#ifndef tinyFAT_h
#define tinyFAT_h

#if defined(__AVR__)
	#if defined(ARDUINO) && ARDUINO >= 100
		#include "Arduino.h"
	#else
		#include "WProgram.h"
	#endif
	#include "HW_AVR_defines.h"
#else
	#include "WProgram.h"
#endif

#define NO_ERROR					0x00
#define ERROR_NO_MORE_FILES			0x01
#define ERROR_FILE_NOT_FOUND		0x10
#define ERROR_ANOTHER_FILE_OPEN		0x11
#define	ERROR_MBR_READ_ERROR		0xF0
#define	ERROR_MBR_SIGNATURE			0xF1
#define	ERROR_MBR_INVALID_FS		0xF2
#define ERROR_BOOTSEC_READ_ERROR	0xE0
#define	ERROR_BOOTSEC_SIGNATURE		0xE1
#define ERROR_NO_FILE_OPEN			0xFFF0
#define ERROR_WRONG_FILEMODE		0xFFF1
#define FILE_IS_EMPTY				0xFFFD
#define BUFFER_OVERFLOW				0xFFFE
#define EOF							0xFFFF

#define FILEMODE_BINARY				0x01
#define FILEMODE_TEXT_READ			0x02
#define FILEMODE_TEXT_WRITE			0x03

#define SPISPEED_LOW				0x03
#define SPISPEED_MEDIUM				0x02
#define SPISPEED_HIGH				0x01
#define SPISPEED_VERYHIGH			0x00

struct _master_boot_record
{
	byte part1Type;
	unsigned long part1Start;
	unsigned long part1Size;
};

struct _boot_sector
{
	byte sectorsPerCluster;
	uint16_t reservedSectors;
	byte fatCopies;
	uint16_t rootDirectoryEntries;
	uint32_t totalFilesystemSectors;
	uint16_t sectorsPerFAT;
	uint32_t hiddenSectors;
	uint32_t partitionSerialNum;
	uint16_t fat1Start;
	uint16_t fat2Start;
	float partitionSize;
};

struct _directory_entry
{
	char filename[9];
	char fileext[4];
	byte attributes;
	uint16_t time;
	uint16_t date;
	uint16_t startCluster;
	uint32_t fileSize;
};

struct _current_file
{
	char filename[13];
	uint16_t currentCluster;
	uint32_t fileSize;
	uint32_t currentPos;
	uint8_t fileMode;
};


class tinyFAT
{
public:
	_master_boot_record	MBR;
	_boot_sector		BS;
	_directory_entry	DE;
	unsigned long		firstDirSector;
	byte				buffer[512]; // the buffer cannot be any smaller, SD cards are read/written in blocks of 512 bytes
	
	tinyFAT();
		
	byte		initFAT(byte speed=SPISPEED_HIGH);
	byte		findFirstFile(_directory_entry *tempDE);
	byte		findNextFile(_directory_entry *tempDE);
	byte		openFile(char *fn, byte mode=FILEMODE_BINARY);
	uint16_t	readBinary();
	uint16_t	readLn(char *st, int bufSize);
	uint16_t	writeLn(char *st);
	void		closeFile();
	boolean		exists(char *fn);
	boolean		rename(char *fn1, char *fn2);
	boolean		delFile(char *fn);
	boolean		create(char *fn);
	void		setSSpin(byte pin);

private:
	_current_file	currFile;
	int				DEcnt;
	boolean			_inited;

	uint16_t	findNextCluster(uint16_t cc);
	char		uCase(char c);
	boolean		validChar(char c);
	uint16_t	findFreeCluster();

};

extern tinyFAT file;

#endif
