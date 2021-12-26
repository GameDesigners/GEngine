#ifndef GINPUT_H
#define GINPUT_H

#define GINPUT_EXPORTS
#ifdef GINPUT_EXPORTS
#define GINPUT_API __declspec(dllexport) 
#else 
#define GINPUT_API __declspec(dllimport) 
#endif


#include <GSystem.h>
#include <GMap.h>

namespace GEngine {
	namespace GInput {
		enum class GInputDevices
		{
			ID_Keyboard,
			ID_Mouse
		};

		enum class GInputAction
		{
			Down,
			Up,
			DBClick,
		};

		enum class GMouseButton
		{
			None,
			LButton,
			MButton,
			RButton,
			Wheel
		};
		enum class KeyCode : unsigned int
	    {
		    NONE         = 0x00          ,
		    Escape       = VK_ESCAPE     ,
		    F1           = VK_F1         ,
		    F2           = VK_F2         ,
		    F3           = VK_F3         ,
		    F4           = VK_F4         ,
		    F5           = VK_F5         ,
		    F6           = VK_F6         ,
		    F7           = VK_F7         ,
		    F8           = VK_F8         ,
		    F9           = VK_F9         ,
		    F10          = VK_F10        ,
		    F11          = VK_F11        ,
		    F12          = VK_F12        ,
		    PrintScreen  = VK_PRINT      ,
		    ScrollLock   = VK_SCROLL     ,
		    PauseBreak   = VK_PAUSE      ,
		    Tilde        = VK_OEM_3      ,  //~��
		    Alpha0       = 0x30          ,  //������������ּ�0
		    Alpha1       = 0x31          ,  //������������ּ�1
		    Alpha2       = 0x32          ,  //������������ּ�2
		    Alpha3       = 0x33          ,  //������������ּ�3
		    Alpha4       = 0x34          ,  //������������ּ�4
		    Alpha5       = 0x35          ,  //������������ּ�5
		    Alpha6       = 0x36          ,  //������������ּ�6
		    Alpha7       = 0x37          ,  //������������ּ�7
		    Alpha8       = 0x38          ,  //������������ּ�8
		    Alpha9       = 0x39          ,  //������������ּ�9
		    AlphaMinus   = VK_OEM_MINUS  ,  //���ż�'-/_'
		    AlphaPlus    = VK_OEM_PLUS   ,  //���ż�'+/='
		    BackSpace    = VK_BACK       ,
		    Tab          = VK_TAB        ,
		    CapsLock     = VK_CAPITAL    ,
		    LeftShift    = VK_LSHIFT     ,
		    LeftCtrl     = VK_LCONTROL   ,
		    LeftWin      = VK_LWIN       ,
		    LeftAlt      = VK_LMENU      ,
		    RightShift   = VK_RSHIFT     ,
		    RightCtrl    = VK_RCONTROL   ,
		    RightWin     = VK_RWIN       ,
		    RightAlt     = VK_RMENU      ,
		    DShift       = VK_SHIFT      ,
		    DCtrl        = VK_CONTROL    ,
		    DAlt         = VK_MENU       ,
		    Space        = VK_SPACE      ,
		    Colon_Semi   = VK_OEM_1      ,  //ð�źͷֺż�  ;:
		    Comma        = VK_OEM_COMMA  ,  //���ż�       ,
		    Period       = VK_OEM_PERIOD ,  //��ż�       .
		    QuestionMask = VK_OEM_2      ,  //�ʺż�       ?
		    ReferenceMask= VK_OEM_7      ,  //���ż�       "
		    LeftBrackets = VK_OEM_4      ,  //�����ż�     [{
		    RightBrackets= VK_OEM_6      ,  //�����ż�     }]
		    SplitLine    = VK_OEM_5      ,  //�ָ��߼�     \| 
		    Enter        = VK_RETURN     ,  //�س���
		    
		    
		     //��ĸ 
		    
		    A            = 0x41          ,  //��ĸA
		    B            = 0x42          ,  //��ĸB
		    C            = 0x43          ,  //��ĸC
		    D            = 0x44          ,  //��ĸD
		    E            = 0x45          ,  //��ĸE
		    F            = 0x46          ,  //��ĸF
		    G            = 0x47          ,  //��ĸG
		    H            = 0x48          ,  //��ĸH
		    I            = 0x49          ,  //��ĸI
		    J            = 0x4A          ,  //��ĸJ
		    K            = 0x4B          ,  //��ĸK
		    L            = 0x4C          ,  //��ĸL
		    M            = 0x4D          ,  //��ĸM
		    N            = 0x4E          ,  //��ĸN
		    O            = 0x4F          ,  //��ĸO
		    P            = 0x50          ,  //��ĸP
		    Q            = 0x51          ,  //��ĸQ
		    R            = 0x52          ,  //��ĸR
		    S            = 0x53          ,  //��ĸS
		    T            = 0x54          ,  //��ĸT
		    U            = 0x55          ,  //��ĸU
		    V            = 0x56          ,  //��ĸV
		    W            = 0x57          ,  //��ĸW
		    X            = 0x58          ,  //��ĸX
		    Y            = 0x59          ,  //��ĸY
		    Z            = 0x5A          ,  //��ĸZ
		    
 		    INSERT       = VK_INSERT     ,  //insert����
		    Home         = VK_HOME       ,  //Home����
		    PageUp       = VK_PRIOR      ,  //Pageup��
		    Delete       = VK_DELETE     ,  
		    End          = VK_END        ,
		    PageDown     = VK_NEXT       ,
		    Down         = VK_DOWN       ,
		    Up           = VK_UP         ,
		    Left         = VK_LEFT       ,
		    Right        = VK_RIGHT      ,
		    
 		    Num0         = VK_NUMPAD0    ,
		    Num1         = VK_NUMPAD1    ,
		    Num2         = VK_NUMPAD2    ,
		    Num3         = VK_NUMPAD3    ,
		    Num4         = VK_NUMPAD4    ,
		    Num5         = VK_NUMPAD5    ,
		    Num6         = VK_NUMPAD6    ,
		    Num7         = VK_NUMPAD7    ,
		    Num8         = VK_NUMPAD8    ,
		    Num9         = VK_NUMPAD9    ,
		    NumAdd       = VK_ADD        ,
		    NumSubstract = VK_SUBTRACT   ,
		    NumMultiply  = VK_MULTIPLY   ,
		    NumDivide    = VK_DIVIDE     ,
		    NumDecimal   = VK_DECIMAL    ,
	        NumLock      = VK_NUMLOCK    ,
		    
		    //���
		    LMouseBtn    = VK_LBUTTON    ,
		    MMouseBtn    = VK_MBUTTON    ,
		    RMouseBtn    = VK_RBUTTON    ,
	    };

		class GINPUT_API GEngineInput
		{

		};
	}
}
#endif // !GINPUT_H

