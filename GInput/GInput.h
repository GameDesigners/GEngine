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
		    Tilde        = VK_OEM_3      ,  //~¼ü
		    Alpha0       = 0x30          ,  //¼üÅÌÇøÓòµÄÊý×Ö¼ü0
		    Alpha1       = 0x31          ,  //¼üÅÌÇøÓòµÄÊý×Ö¼ü1
		    Alpha2       = 0x32          ,  //¼üÅÌÇøÓòµÄÊý×Ö¼ü2
		    Alpha3       = 0x33          ,  //¼üÅÌÇøÓòµÄÊý×Ö¼ü3
		    Alpha4       = 0x34          ,  //¼üÅÌÇøÓòµÄÊý×Ö¼ü4
		    Alpha5       = 0x35          ,  //¼üÅÌÇøÓòµÄÊý×Ö¼ü5
		    Alpha6       = 0x36          ,  //¼üÅÌÇøÓòµÄÊý×Ö¼ü6
		    Alpha7       = 0x37          ,  //¼üÅÌÇøÓòµÄÊý×Ö¼ü7
		    Alpha8       = 0x38          ,  //¼üÅÌÇøÓòµÄÊý×Ö¼ü8
		    Alpha9       = 0x39          ,  //¼üÅÌÇøÓòµÄÊý×Ö¼ü9
		    AlphaMinus   = VK_OEM_MINUS  ,  //·ûºÅ¼ü'-/_'
		    AlphaPlus    = VK_OEM_PLUS   ,  //·ûºÅ¼ü'+/='
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
		    Colon_Semi   = VK_OEM_1      ,  //Ã°ºÅºÍ·ÖºÅ¼ü  ;:
		    Comma        = VK_OEM_COMMA  ,  //¶ººÅ¼ü       ,
		    Period       = VK_OEM_PERIOD ,  //¾äºÅ¼ü       .
		    QuestionMask = VK_OEM_2      ,  //ÎÊºÅ¼ü       ?
		    ReferenceMask= VK_OEM_7      ,  //ÒýºÅ¼ü       "
		    LeftBrackets = VK_OEM_4      ,  //×óÀ¨ºÅ¼ü     [{
		    RightBrackets= VK_OEM_6      ,  //×óÀ¨ºÅ¼ü     }]
		    SplitLine    = VK_OEM_5      ,  //·Ö¸îÏß¼ü     \| 
		    Enter        = VK_RETURN     ,  //»Ø³µ¼ü
		    
		    
		     //×ÖÄ¸ 
		    
		    A            = 0x41          ,  //×ÖÄ¸A
		    B            = 0x42          ,  //×ÖÄ¸B
		    C            = 0x43          ,  //×ÖÄ¸C
		    D            = 0x44          ,  //×ÖÄ¸D
		    E            = 0x45          ,  //×ÖÄ¸E
		    F            = 0x46          ,  //×ÖÄ¸F
		    G            = 0x47          ,  //×ÖÄ¸G
		    H            = 0x48          ,  //×ÖÄ¸H
		    I            = 0x49          ,  //×ÖÄ¸I
		    J            = 0x4A          ,  //×ÖÄ¸J
		    K            = 0x4B          ,  //×ÖÄ¸K
		    L            = 0x4C          ,  //×ÖÄ¸L
		    M            = 0x4D          ,  //×ÖÄ¸M
		    N            = 0x4E          ,  //×ÖÄ¸N
		    O            = 0x4F          ,  //×ÖÄ¸O
		    P            = 0x50          ,  //×ÖÄ¸P
		    Q            = 0x51          ,  //×ÖÄ¸Q
		    R            = 0x52          ,  //×ÖÄ¸R
		    S            = 0x53          ,  //×ÖÄ¸S
		    T            = 0x54          ,  //×ÖÄ¸T
		    U            = 0x55          ,  //×ÖÄ¸U
		    V            = 0x56          ,  //×ÖÄ¸V
		    W            = 0x57          ,  //×ÖÄ¸W
		    X            = 0x58          ,  //×ÖÄ¸X
		    Y            = 0x59          ,  //×ÖÄ¸Y
		    Z            = 0x5A          ,  //×ÖÄ¸Z
		    
 		    INSERT       = VK_INSERT     ,  //insert°´¼ü
		    Home         = VK_HOME       ,  //Home°´¼ü
		    PageUp       = VK_PRIOR      ,  //Pageup¼ü
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
		    
		    //Êó±ê
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

