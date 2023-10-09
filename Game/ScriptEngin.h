#pragma once

int loadScript(const char* filename, ScriptInformation* ScriptInfo);

int isJapaneseCharactor(unsigned char code);

void writeSubString(char* message, char** g_message_buffer, int start, int len, int bufferLine);

void drawString(int PosX, int PosY, char* g_message_buffer, unsigned int color);

void splitString(char* src, char dest[], const char* delim, int splitNum);

int decodeScript(const char* scriptMessage);
