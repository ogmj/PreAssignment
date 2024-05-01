
template < typename T >
class CSingleton
{
public:
	CSingleton()
	{
	}
	static T & GetStaticInstance()
	{
		static T mInstance;
		return mInstance;
	}

	static T * GetInstance()
	{
		if( mpInstance == NULL )
		{
			mpInstance = new T;
			atexit( ReleaseInstance );
		}
		return mpInstance;
	}
	static void ReleaseInstance()
	{
		if (mpInstance)
		{
			delete mpInstance;
		}
	}

private:
	static T * mpInstance;
	static T mInstance;
};

template< typename T >
T *	CSingleton< T >::mpInstance = nullptr; 

