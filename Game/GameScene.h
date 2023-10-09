#pragma once

#define TESTBACKGROUND_NUM 1
#define MESSAGE_WINDOW_PATH  "./Data/image/TestPicture/Test1.png"

class GameScene : public AbstractScene
{
private:
	Parameter param;
	const int iMESSAGE_FONT_SIZE = 32;						// 本文のフォントサイズ
	const int iMESSAGE_FONT_NAME_SIZE = 24;					// 名前のフォントサイズ
	// */
	int iFont_color;

	
	const int MESSAGE_MAX_LENGTH = 27;						// 一行で表示する最大文字数
	const int MESSAGE_MAX_LINE = 3;							//	表示する最大行数
	
	const int BETWEEN_LINES = 50;							//	行間
	// */
	const char* cFont_Name = "MS ゴシック";					//	フォント名
	const char* Message_Window_Path = "../Data/image/TestPicture/Test1.png";	// ゲームウィンドウのファイルパス ここにおいていいのかは要検証

	char* g_message;
	char** g_message_buffer;

	int currentCursor;
	int currentLineCursor;

	int FontColor;
	//int GraphicHandle;

	//int isJapaneseCharactor(unsigned char code);

	//void writeSubString(char* message, int start, int len, int posX, int PosY, int bufferLine);


public:
	GameScene(IOnSceneChangedListener* impl, const Parameter& parameter);
	virtual ~GameScene() = default;

	void update();
	void draw();

};