#if IS_HAVE_RETURN==0&&GDELEGATE_PARAM_COUNT==0
#define TEMPLATE template<>
#define FUNC_PARAMS_TYPE_SUFFIX
#define PARAMS_SUFFIX
#define FUNC_USE_PARAMS_SUFFIX
#elif IS_HAVE_RETURN>0&&GDELEGATE_PARAM_COUNT==0
#define TEMPLATE template<typename TEMPLATE_RETURN_TYPE>
#define FUNC_PARAMS_TYPE_SUFFIX
#define PARAMS_SUFFIX
#define FUNC_USE_PARAMS_SUFFIX
#elif IS_HAVE_RETURN==0&&GDELEGATE_PARAM_COUNT>0
#define TEMPLATE template<TEMPLATE_PARAMS>
#define FUNC_PARAMS_TYPE_SUFFIX ,FUNC_PARAMS_TYPE
#define PARAMS_SUFFIX ,FUNC_PARAMS
#define FUNC_USE_PARAMS_SUFFIX ,FUNC_USE_PARAMS
#elif IS_HAVE_RETURN>0&&GDELEGATE_PARAM_COUNT>0
#define TEMPLATE template<typename TEMPLATE_RETURN_TYPE,TEMPLATE_PARAMS>
#define FUNC_PARAMS_TYPE_SUFFIX ,FUNC_PARAMS_TYPE
#define PARAMS_SUFFIX ,FUNC_PARAMS
#define FUNC_USE_PARAMS_SUFFIX ,FUNC_USE_PARAMS
#endif // IS_HAVE_RETURN==0&&GDELEGATE_PARAM_COUNT==0

#define STR_CAT(X,Y)        X##Y
#define COMMBINE(X,Y)       STR_CAT(X,Y)
#define GDELEGATE_CLASSNAME GDelegate
#define GEVENT_CLASSNAME    GEvents

TEMPLATE
#ifdef DELEGATE_DEFERERRED_SYNTAX
class  GSTL_API GDELEGATE_CLASSNAME<TEMPLATE_RETURN_TYPE(FUNC_PARAMS_TYPE)>
#else
#define GDELEGATE_CLASSNAME COMMBINE(GDelegate,CLASS_SUFFIX)
class GSTL_API GDELEGATE_CLASSNAME<TEMPLATE_RETURN_TYPE(FUNC_PARAMS_TYPE)>
#endif
{
public:
	typedef TEMPLATE_RETURN_TYPE(*function)(void* FUNC_PARAMS_TYPE_SUFFIX);

public:
	GDELEGATE_CLASSNAME() :__instance(nullptr), __fun(nullptr) {}
	GDELEGATE_CLASSNAME(void* inst, function fun) :__instance(inst), __fun(fun) {}
	~GDELEGATE_CLASSNAME() {}

public:
	template<class C, TEMPLATE_RETURN_TYPE(C::* CF)(FUNC_PARAMS_TYPE)>
	static GDELEGATE_CLASSNAME FromMethod(C* p)
	{
		return __create((void*)p, &__method_stub<C, CF>);
	}

	template<TEMPLATE_RETURN_TYPE(*F)(FUNC_PARAMS_TYPE)>
	static GDELEGATE_CLASSNAME FromFun()
	{
		return __create(nullptr, &__fun_stub<F>);
	}

	TEMPLATE_RETURN_TYPE execute(FUNC_PARAMS)
	{
		return (*__fun)(__instance FUNC_USE_PARAMS_SUFFIX);
	}

	TEMPLATE_RETURN_TYPE operator()(FUNC_PARAMS)
	{
		return (*__fun)(__instance FUNC_USE_PARAMS_SUFFIX);
	}

	operator bool() const
	{
		return __instance != nullptr;
	}

	bool operator!() const
	{
		return !(operator bool());
	}

	bool operator==(const GDELEGATE_CLASSNAME& rhs) const
	{
		return (__instance == rhs.__instance) && (__fun) == rhs.__fun;
	}
private:
	template<class C, TEMPLATE_RETURN_TYPE(C::* CF)(FUNC_PARAMS_TYPE)>
	static TEMPLATE_RETURN_TYPE __method_stub(void* inst PARAMS_SUFFIX)
	{
		C* AP = (C*)inst;
		return (AP->*CF)(FUNC_USE_PARAMS);
	}

	template<TEMPLATE_RETURN_TYPE(*F)(FUNC_PARAMS_TYPE)>
	static TEMPLATE_RETURN_TYPE __fun_stub(void* inst PARAMS_SUFFIX)
	{
		return (F)(FUNC_USE_PARAMS);
	}

	static GDELEGATE_CLASSNAME __create(void* inst, function fun)
	{
		return GDELEGATE_CLASSNAME(inst, fun);
	}

private:
	void* __instance;
	function __fun;
};


TEMPLATE
#ifdef DELEGATE_DEFERERRED_SYNTAX
class GSTL_API GEVENT_CLASSNAME<TEMPLATE_RETURN_TYPE(FUNC_PARAMS_TYPE)>
#else
#define GEVENT_CLASSNAME COMMBINE(GDelegateEvent,CLASS_SUFFIX)
class GSTL_API GEVENT_CLASSNAME
#endif
{
#ifdef DELEGATE_DEFERERRED_SYNTAX
typedef GDELEGATE_CLASSNAME<TEMPLATE_RETURN_TYPE(FUNC_PARAMS_TYPE)> Handler;
#else
typedef GDELEGATE_CLASSNAME<TEMPLATE_RETURN_TYPE,FUNC_PARAMS_TYPE> Handler;
#endif
typedef GVector<Handler> Handlers;

public:
	GEVENT_CLASSNAME() {}

	inline void operator+=(const Handler& handler) 
	{ 
		add(handler);
	}

	inline void operator-=(const Handler& handler)
	{
		remove(handler);
	}

	inline void add(const Handler& handler)
	{
		for(typename GVector<Handler>::iterator_type p = m_delegateList.begin(); p != m_delegateList.end(); p++)
		{
			if (*p == handler)
				return;
		}
		m_delegateList.push_back(handler);
	}

	inline void remove(const Handler& handler)
	{
		for (typename GVector<Handler>::iterator_type p = m_delegateList.begin(); p != m_delegateList.end(); p++)
		{
			if (*p == handler)
			{
				m_delegateList.erase(p);
				break;
			}
		}
	}

	inline bool isVaild()
	{
		return m_delegateList.size() > 0;
	}

	inline void reset()
	{
		m_delegateList.clear();
	}

	inline void operator()(FUNC_PARAMS)
	{
		invoke(FUNC_USE_PARAMS);
	}

	inline void invoke(FUNC_PARAMS)
	{
		for (typename GVector<Handler>::iterator_type p = m_delegateList.begin(); p != m_delegateList.end(); p++)
			p->execute(FUNC_USE_PARAMS);
	}

	inline void invoke_without(FUNC_PARAMS
#if GDELEGATE_PARAM_COUNT>0
		,
#endif
		const Handler& without)
	{
		for (typename GVector<Handler>::iterator_type p = m_delegateList.begin(); p != m_delegateList.end(); p++)
		{
			if (*p != without)
				p->execute(FUNC_USE_PARAMS);
		}
	}

private:
	Handlers m_delegateList;
};