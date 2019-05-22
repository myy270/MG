/*******************************************************************************
* タイトル:
* プログラム名:
* 作成者:		GP11A341 33 麦英泳
* 作成日:		2018/08/17
*******************************************************************************/
#ifndef _INPUT_H_
#define _INPUT_H_


//*****************************************************************************
// マクロ定義
//*****************************************************************************

// プログラム分けするときに使う
#define	USE_KEYBOARD										// 宣言するとキーボードで操作可能になる
#define	USE_MOUSE											// 宣言するとマウスで操作可能になる
#define	USE_PAD												// 宣言するとパッドで操作可能になる


/* game pad情報 */
#define BUTTON_UP					0x00000001l	//0000 0001
#define BUTTON_DOWN					0x00000002l	//0000 0010
#define BUTTON_LEFT					0x00000004l	//0000 0100
#define BUTTON_RIGHT				0x00000008l	//0000 1000

#define BUTTON_SQUARE				0x00000010l	//0001 0000
#define BUTTON_CROSS				0x00000020l	//0010 0000
#define BUTTON_CIRCLE				0x00000040l	//0100 0000
#define BUTTON_TRIANGLE				0x00000080l	//1000 0000
#define BUTTON_L1					0x00000100l	//0001 0000 0000
#define BUTTON_R1					0x00000200l	//0010 0000 0000
#define BUTTON_L2					0x00000400l	//0100 0000 0000
#define BUTTON_R2					0x00000800l	//1000 0000 0000
#define BUTTON_SHARE				0x00001000l	//0001 0000 0000 0000
#define BUTTON_OPTIONS				0x00002000l	//0010 0000 0000 0000
#define BUTTON_L3					0x00004000l	//
#define BUTTON_R3					0x00008000l	//
#define BUTTON_PS					0x00010000l	//
#define BUTTON_TOUCHPAD				0x00020000l	//

#define BUTTON_LSTICK_UP			0x00040000l	//
#define BUTTON_LSTICK_DOWN			0x00080000l	//
#define BUTTON_LSTICK_LEFT			0x00100000l	//
#define BUTTON_LSTICK_RIGHT			0x00200000l	//

#define BUTTON_RSTICK_UP			0x00400000l	//
#define BUTTON_RSTICK_DOWN			0x00800000l	//
#define BUTTON_RSTICK_LEFT			0x01000000l	//
#define BUTTON_RSTICK_RIGHT			0x02000000l	//

#define LSTICK_OFFSET				(4100)	    //left stick の精度を調整する
#define RSTICK_OFFSET				(4100)	    //right stick の精度を調整する

#define GAMEPADMAX					(4)			// 同時に接続するジョイパッドの最大数をセット

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitInput(HINSTANCE hInst, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

//---------------------------- keyboard
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRepeat(int nKey);
bool GetKeyboardRelease(int nKey);

//---------------------------- mouse
BOOL IsMouseLeftPress(void);      // 左クリックした状態
BOOL IsMouseLeftTrigger(void);    // 左クリックした瞬間
BOOL IsMouseRightPress(void);     // 右クリックした状態
BOOL IsMouseRightTrigger(void);   // 右クリックした瞬間
BOOL IsMouseCenterPress(void);    // 中クリックした状態
BOOL IsMouseCenterTrigger(void);  // 中クリックした瞬間
long GetMouseX(void);               // マウスがX方向に動いた相対値
long GetMouseY(void);               // マウスがY方向に動いた相対値
long GetMouseZ(void);               // マウスホイールが動いた相対値

//---------------------------- game pad
BOOL IsButtonPress(int padNo,DWORD button);
BOOL IsButtonTrigger(int padNo,DWORD button);
BOOL IsButtonRelease(int padNo, DWORD button);
BOOL IsButtonRepeat(int padNo, DWORD button);

#endif