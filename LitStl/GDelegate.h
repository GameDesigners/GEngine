#ifndef GDELEGATE_H
#define GDELEGATE_H
#include "GVector.h"
namespace GEngine {
	namespace GStl {

#define DELEGATE_DEFERERRED_SYNTAX
#ifdef DELEGATE_DEFERERRED_SYNTAX
		template<typename TSingnature> class GDelegate;
		template<typename TSingnature> class GEvents;
#endif // DELEGATE_DEFERERRED_SYNTAX


//无参无返回值的委托函数
//**********************************************************************************************************************************************

#define GDELEGATE_PARAM_COUNT 0
#define IS_HAVE_RETURN        0
#define CLASS_SUFFIX          0_0
#define TEMPLATE_PARAMS       
#define FUNC_PARAMS_TYPE      
#define FUNC_PARAMS           
#define FUNC_USE_PARAMS       
#define TEMPLATE_RETURN_TYPE  void
#include "GDelegateTemplate.h"
#undef  GDELEGATE_PARAM_COUNT
#undef  IS_HAVE_RETURN
#undef  CLASS_SUFFIX
#undef  TEMPLATE_PARAMS
#undef  FUNC_PARAMS_TYPE
#undef  FUNC_PARAMS
#undef  FUNC_USE_PARAMS
#undef  TEMPLATE_RETURN_TYPE



//无返回值 1个参数 的委托函数
//**********************************************************************************************************************************************

#define GDELEGATE_PARAM_COUNT 1
#define IS_HAVE_RETURN        0
#define CLASS_SUFFIX          1_0
#define TEMPLATE_PARAMS       typename A1
#define FUNC_PARAMS_TYPE      A1
#define FUNC_PARAMS           A1 a1
#define FUNC_USE_PARAMS       a1
#define TEMPLATE_RETURN_TYPE  void
#include "GDelegateTemplate.h"
#undef  GDELEGATE_PARAM_COUNT
#undef  IS_HAVE_RETURN
#undef  CLASS_SUFFIX
#undef  TEMPLATE_PARAMS
#undef  FUNC_PARAMS_TYPE
#undef  FUNC_PARAMS
#undef  FUNC_USE_PARAMS
#undef  TEMPLATE_RETURN_TYPE



//无返回值 2个参数 的委托函数
//**********************************************************************************************************************************************

#define GDELEGATE_PARAM_COUNT 2
#define IS_HAVE_RETURN        0
#define CLASS_SUFFIX          2_0
#define TEMPLATE_PARAMS       typename A1,typename A2
#define FUNC_PARAMS_TYPE      A1,A2
#define FUNC_PARAMS           A1 a1,A2 a2
#define FUNC_USE_PARAMS       a1,a2
#define TEMPLATE_RETURN_TYPE  void
#include "GDelegateTemplate.h"
#undef  GDELEGATE_PARAM_COUNT
#undef  IS_HAVE_RETURN
#undef  CLASS_SUFFIX
#undef  TEMPLATE_PARAMS
#undef  FUNC_PARAMS_TYPE
#undef  FUNC_PARAMS
#undef  FUNC_USE_PARAMS
#undef  TEMPLATE_RETURN_TYPE



//无返回值 3个参数 的委托函数
//**********************************************************************************************************************************************

#define GDELEGATE_PARAM_COUNT 3
#define IS_HAVE_RETURN        0
#define CLASS_SUFFIX          3_0
#define TEMPLATE_PARAMS       typename A1,typename A2,typename A3
#define FUNC_PARAMS_TYPE      A1,A2,A3
#define FUNC_PARAMS           A1 a1,A2 a2,A3 a3
#define FUNC_USE_PARAMS       a1,a2,a3
#define TEMPLATE_RETURN_TYPE  void
#include "GDelegateTemplate.h"
#undef  GDELEGATE_PARAM_COUNT
#undef  IS_HAVE_RETURN
#undef  CLASS_SUFFIX
#undef  TEMPLATE_PARAMS
#undef  FUNC_PARAMS_TYPE
#undef  FUNC_PARAMS
#undef  FUNC_USE_PARAMS
#undef  TEMPLATE_RETURN_TYPE

		

//无返回值 4个参数 的委托函数
//**********************************************************************************************************************************************

#define GDELEGATE_PARAM_COUNT 4
#define IS_HAVE_RETURN        0
#define CLASS_SUFFIX          4_0
#define TEMPLATE_PARAMS       typename A1,typename A2,typename A3,typename A4
#define FUNC_PARAMS_TYPE      A1,A2,A3,A4
#define FUNC_PARAMS           A1 a1,A2 a2,A3 a3,A4 a4
#define FUNC_USE_PARAMS       a1,a2,a3,a4
#define TEMPLATE_RETURN_TYPE  void
#include "GDelegateTemplate.h"
#undef  GDELEGATE_PARAM_COUNT
#undef  IS_HAVE_RETURN
#undef  CLASS_SUFFIX
#undef  TEMPLATE_PARAMS
#undef  FUNC_PARAMS_TYPE
#undef  FUNC_PARAMS
#undef  FUNC_USE_PARAMS
#undef  TEMPLATE_RETURN_TYPE



//无返回值 5个参数 的委托函数
//**********************************************************************************************************************************************

#define GDELEGATE_PARAM_COUNT 5
#define IS_HAVE_RETURN        0
#define CLASS_SUFFIX          5_0
#define TEMPLATE_PARAMS       typename A1,typename A2,typename A3,typename A4,typename A5
#define FUNC_PARAMS_TYPE      A1,A2,A3,A4,A5
#define FUNC_PARAMS           A1 a1,A2 a2,A3 a3,A4 a4,A5 a5
#define FUNC_USE_PARAMS       a1,a2,a3,a4,a5
#define TEMPLATE_RETURN_TYPE  void
#include "GDelegateTemplate.h"
#undef  GDELEGATE_PARAM_COUNT
#undef  IS_HAVE_RETURN
#undef  CLASS_SUFFIX
#undef  TEMPLATE_PARAMS
#undef  FUNC_PARAMS_TYPE
#undef  FUNC_PARAMS
#undef  FUNC_USE_PARAMS
#undef  TEMPLATE_RETURN_TYPE



//无返回值 6个参数 的委托函数
//**********************************************************************************************************************************************

#define GDELEGATE_PARAM_COUNT 6
#define IS_HAVE_RETURN        0
#define CLASS_SUFFIX          6_0
#define TEMPLATE_PARAMS       typename A1,typename A2,typename A3,typename A4,typename A5,typename A6
#define FUNC_PARAMS_TYPE      A1,A2,A3,A4,A5,A6
#define FUNC_PARAMS           A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6
#define FUNC_USE_PARAMS       a1,a2,a3,a4,a5,a6
#define TEMPLATE_RETURN_TYPE  void
#include "GDelegateTemplate.h"
#undef  GDELEGATE_PARAM_COUNT
#undef  IS_HAVE_RETURN
#undef  CLASS_SUFFIX
#undef  TEMPLATE_PARAMS
#undef  FUNC_PARAMS_TYPE
#undef  FUNC_PARAMS
#undef  FUNC_USE_PARAMS
#undef  TEMPLATE_RETURN_TYPE



//无返回值 7个参数 的委托函数
//**********************************************************************************************************************************************

#define GDELEGATE_PARAM_COUNT 7
#define IS_HAVE_RETURN        0
#define CLASS_SUFFIX          7_0
#define TEMPLATE_PARAMS       typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7
#define FUNC_PARAMS_TYPE      A1,A2,A3,A4,A5,A6,A7
#define FUNC_PARAMS           A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7
#define FUNC_USE_PARAMS       a1,a2,a3,a4,a5,a6,a7
#define TEMPLATE_RETURN_TYPE  void
#include "GDelegateTemplate.h"
#undef  GDELEGATE_PARAM_COUNT
#undef  IS_HAVE_RETURN
#undef  CLASS_SUFFIX
#undef  TEMPLATE_PARAMS
#undef  FUNC_PARAMS_TYPE
#undef  FUNC_PARAMS
#undef  FUNC_USE_PARAMS
#undef  TEMPLATE_RETURN_TYPE


//无返回值 8个参数 的委托函数
//**********************************************************************************************************************************************

#define GDELEGATE_PARAM_COUNT 8
#define IS_HAVE_RETURN        0
#define CLASS_SUFFIX          8_0
#define TEMPLATE_PARAMS       typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8
#define FUNC_PARAMS_TYPE      A1,A2,A3,A4,A5,A6,A7,A8
#define FUNC_PARAMS           A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8
#define FUNC_USE_PARAMS       a1,a2,a3,a4,a5,a6,a7,a8
#define TEMPLATE_RETURN_TYPE  void
#include "GDelegateTemplate.h"
#undef  GDELEGATE_PARAM_COUNT
#undef  IS_HAVE_RETURN
#undef  CLASS_SUFFIX
#undef  TEMPLATE_PARAMS
#undef  FUNC_PARAMS_TYPE
#undef  FUNC_PARAMS
#undef  FUNC_USE_PARAMS
#undef  TEMPLATE_RETURN_TYPE


//无返回值 9个参数 的委托函数
//**********************************************************************************************************************************************

#define GDELEGATE_PARAM_COUNT 9
#define IS_HAVE_RETURN        0
#define CLASS_SUFFIX          9_0
#define TEMPLATE_PARAMS       typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9
#define FUNC_PARAMS_TYPE      A1,A2,A3,A4,A5,A6,A7,A8,A9
#define FUNC_PARAMS           A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8,A9 a9
#define FUNC_USE_PARAMS       a1,a2,a3,a4,a5,a6,a7,a8,a9
#define TEMPLATE_RETURN_TYPE  void
#include "GDelegateTemplate.h"
#undef  GDELEGATE_PARAM_COUNT
#undef  IS_HAVE_RETURN
#undef  CLASS_SUFFIX
#undef  TEMPLATE_PARAMS
#undef  FUNC_PARAMS_TYPE
#undef  FUNC_PARAMS
#undef  FUNC_USE_PARAMS
#undef  TEMPLATE_RETURN_TYPE

		 /*
		  *  有返回值 1个参数 的委托函数
		  */
#define GDELEGATE_PARAM_COUNT 1
#define IS_HAVE_RETURN        1
#define CLASS_SUFFIX          1_1
#define TEMPLATE_PARAMS       typename A1
#define FUNC_PARAMS_TYPE      A1
#define FUNC_PARAMS           A1 a1
#define FUNC_USE_PARAMS       a1
#define TEMPLATE_RETURN_TYPE  R
#include "GDelegateTemplate.h"
#undef  GDELEGATE_PARAM_COUNT
#undef  IS_HAVE_RETURN
#undef  CLASS_SUFFIX
#undef  TEMPLATE_PARAMS
#undef  FUNC_PARAMS_TYPE
#undef  FUNC_PARAMS
#undef  FUNC_USE_PARAMS
#undef  TEMPLATE_RETURN_TYPE
		  /*
		   *  有返回值 1个参数 的委托函数
		   */
#define GDELEGATE_PARAM_COUNT 2
#define IS_HAVE_RETURN        1
#define CLASS_SUFFIX          2_1
#define TEMPLATE_PARAMS       typename A1,typename A2
#define FUNC_PARAMS_TYPE      A1,A2
#define FUNC_PARAMS           A1 a1,A2 a2
#define FUNC_USE_PARAMS       a1,a2
#define TEMPLATE_RETURN_TYPE  R
#include "GDelegateTemplate.h"
#undef  GDELEGATE_PARAM_COUNT
#undef  IS_HAVE_RETURN
#undef  CLASS_SUFFIX
#undef  TEMPLATE_PARAMS
#undef  FUNC_PARAMS_TYPE
#undef  FUNC_PARAMS
#undef  FUNC_USE_PARAMS
#undef  TEMPLATE_RETURN_TYPE

		   /*
			*  有返回值 3个参数 的委托函数
			*/
#define GDELEGATE_PARAM_COUNT 3
#define IS_HAVE_RETURN        1
#define CLASS_SUFFIX          3_1
#define TEMPLATE_PARAMS       typename A1,typename A2,typename A3
#define FUNC_PARAMS_TYPE      A1,A2,A3
#define FUNC_PARAMS           A1 a1,A2 a2,A3 a3
#define FUNC_USE_PARAMS       a1,a2,a3
#define TEMPLATE_RETURN_TYPE  R
#include "GDelegateTemplate.h"
#undef  GDELEGATE_PARAM_COUNT
#undef  IS_HAVE_RETURN
#undef  CLASS_SUFFIX
#undef  TEMPLATE_PARAMS
#undef  FUNC_PARAMS_TYPE
#undef  FUNC_PARAMS
#undef  FUNC_USE_PARAMS
#undef  TEMPLATE_RETURN_TYPE


			/*
			 *  有返回值 4个参数 的委托函数
			 */
//**********************************************************************************************************************************************

#define GDELEGATE_PARAM_COUNT 4
#define IS_HAVE_RETURN        1
#define CLASS_SUFFIX          4_1
#define TEMPLATE_PARAMS       typename A1,typename A2,typename A3,typename A4
#define FUNC_PARAMS_TYPE      A1,A2,A3,A4
#define FUNC_PARAMS           A1 a1,A2 a2,A3 a3,A4 a4
#define FUNC_USE_PARAMS       a1,a2,a3,a4
#define TEMPLATE_RETURN_TYPE  R
#include "GDelegateTemplate.h"
#undef  GDELEGATE_PARAM_COUNT
#undef  IS_HAVE_RETURN
#undef  CLASS_SUFFIX
#undef  TEMPLATE_PARAMS
#undef  FUNC_PARAMS_TYPE
#undef  FUNC_PARAMS
#undef  FUNC_USE_PARAMS
#undef  TEMPLATE_RETURN_TYPE



//有返回值 5个参数 的委托函数
//**********************************************************************************************************************************************

#define GDELEGATE_PARAM_COUNT 5
#define IS_HAVE_RETURN        1
#define CLASS_SUFFIX          5_1
#define TEMPLATE_PARAMS       typename A1,typename A2,typename A3,typename A4,typename A5
#define FUNC_PARAMS_TYPE      A1,A2,A3,A4,A5
#define FUNC_PARAMS           A1 a1,A2 a2,A3 a3,A4 a4,A5 a5
#define FUNC_USE_PARAMS       a1,a2,a3,a4,a5
#define TEMPLATE_RETURN_TYPE  R
#include "GDelegateTemplate.h"
#undef  GDELEGATE_PARAM_COUNT
#undef  IS_HAVE_RETURN
#undef  CLASS_SUFFIX
#undef  TEMPLATE_PARAMS
#undef  FUNC_PARAMS_TYPE
#undef  FUNC_PARAMS
#undef  FUNC_USE_PARAMS
#undef  TEMPLATE_RETURN_TYPE



//有返回值 6个参数 的委托函数
//**********************************************************************************************************************************************

#define GDELEGATE_PARAM_COUNT 6
#define IS_HAVE_RETURN        1
#define CLASS_SUFFIX          6_1
#define TEMPLATE_PARAMS       typename A1,typename A2,typename A3,typename A4,typename A5,typename A6
#define FUNC_PARAMS_TYPE      A1,A2,A3,A4,A5,A6
#define FUNC_PARAMS           A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6
#define FUNC_USE_PARAMS       a1,a2,a3,a4,a5,a6
#define TEMPLATE_RETURN_TYPE  R
#include "GDelegateTemplate.h"
#undef  GDELEGATE_PARAM_COUNT
#undef  IS_HAVE_RETURN
#undef  CLASS_SUFFIX
#undef  TEMPLATE_PARAMS
#undef  FUNC_PARAMS_TYPE
#undef  FUNC_PARAMS
#undef  FUNC_USE_PARAMS
#undef  TEMPLATE_RETURN_TYPE



//有返回值 7个参数 的委托函数
//**********************************************************************************************************************************************

#define GDELEGATE_PARAM_COUNT 7
#define IS_HAVE_RETURN        1
#define CLASS_SUFFIX          7_1
#define TEMPLATE_PARAMS       typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7
#define FUNC_PARAMS_TYPE      A1,A2,A3,A4,A5,A6,A7
#define FUNC_PARAMS           A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7
#define FUNC_USE_PARAMS       a1,a2,a3,a4,a5,a6,a7
#define TEMPLATE_RETURN_TYPE  R
#include "GDelegateTemplate.h"
#undef  GDELEGATE_PARAM_COUNT
#undef  IS_HAVE_RETURN
#undef  CLASS_SUFFIX
#undef  TEMPLATE_PARAMS
#undef  FUNC_PARAMS_TYPE
#undef  FUNC_PARAMS
#undef  FUNC_USE_PARAMS
#undef  TEMPLATE_RETURN_TYPE


//有返回值 8个参数 的委托函数
//**********************************************************************************************************************************************

#define GDELEGATE_PARAM_COUNT 8
#define IS_HAVE_RETURN        1
#define CLASS_SUFFIX          8_1
#define TEMPLATE_PARAMS       typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8
#define FUNC_PARAMS_TYPE      A1,A2,A3,A4,A5,A6,A7,A8
#define FUNC_PARAMS           A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8
#define FUNC_USE_PARAMS       a1,a2,a3,a4,a5,a6,a7,a8
#define TEMPLATE_RETURN_TYPE  R
#include "GDelegateTemplate.h"
#undef  GDELEGATE_PARAM_COUNT
#undef  IS_HAVE_RETURN
#undef  CLASS_SUFFIX
#undef  TEMPLATE_PARAMS
#undef  FUNC_PARAMS_TYPE
#undef  FUNC_PARAMS
#undef  FUNC_USE_PARAMS
#undef  TEMPLATE_RETURN_TYPE



//有返回值 9个参数 的委托函数
//**********************************************************************************************************************************************

#define GDELEGATE_PARAM_COUNT 9
#define IS_HAVE_RETURN        1
#define CLASS_SUFFIX          9_1
#define TEMPLATE_PARAMS       typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9
#define FUNC_PARAMS_TYPE      A1,A2,A3,A4,A5,A6,A7,A8,A9
#define FUNC_PARAMS           A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6,A7 a7,A8 a8,A9 a9
#define FUNC_USE_PARAMS       a1,a2,a3,a4,a5,a6,a7,a8,a9
#define TEMPLATE_RETURN_TYPE  R
#include "GDelegateTemplate.h"
#undef  GDELEGATE_PARAM_COUNT
#undef  IS_HAVE_RETURN
#undef  CLASS_SUFFIX
#undef  TEMPLATE_PARAMS
#undef  FUNC_PARAMS_TYPE
#undef  FUNC_PARAMS
#undef  FUNC_USE_PARAMS
#undef  TEMPLATE_RETURN_TYPE

	}
}
#endif // !GDELEGATE_H
