#pragma once
#ifndef SINGLETON_H
#define SINGLETON_H
#include <iostream>
template <typename T>
class SingletonBase
{
protected:
	static T* mInstance;
	SingletonBase() = default;
	virtual ~SingletonBase() = default;

public:
	static T* Get()
	{
		return mInstance;
	}

	static void Create()
	{
		if (!mInstance)
		{
			mInstance = new T;

			DEBUG_CONFIRM("Singleton subject create ", mInstance, true);
			DEBUG_GET_TYPE("Called Type is", T);
		}
	};

	static void Delete()
	{
		if (mInstance)
		{
			delete mInstance;
			mInstance = nullptr;
			SAFE_DELETE(mInstance);

			DEBUG_CONFIRM("Singleton subject delete ", mInstance, false);
			DEBUG_GET_TYPE("Called Type is", T);
		}
	};
};

template <typename T>
T* SingletonBase<T>::mInstance = nullptr;
#endif // !SINGLETON_H