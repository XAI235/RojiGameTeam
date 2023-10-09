#pragma once

#define TESTBACKGROUND_NUM 1
#define MESSAGE_WINDOW_PATH  "./Data/image/TestPicture/Test1.png"

class GameScene : public AbstractScene
{
private:
	Parameter param;
	const int iMESSAGE_FONT_SIZE = 32;						// �{���̃t�H���g�T�C�Y
	const int iMESSAGE_FONT_NAME_SIZE = 24;					// ���O�̃t�H���g�T�C�Y
	// */
	int iFont_color;

	
	const int MESSAGE_MAX_LENGTH = 27;						// ��s�ŕ\������ő啶����
	const int MESSAGE_MAX_LINE = 3;							//	�\������ő�s��
	
	const int BETWEEN_LINES = 50;							//	�s��
	// */
	const char* cFont_Name = "MS �S�V�b�N";					//	�t�H���g��
	const char* Message_Window_Path = "../Data/image/TestPicture/Test1.png";	// �Q�[���E�B���h�E�̃t�@�C���p�X �����ɂ����Ă����̂��͗v����

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