#pragma once

#ifndef COMMON_MACRO_H
#define COMMON_MACRO_H
namespace Common
{
	// ½Ì±ÛÅæ ±âº»Çü Á¤ÀÇ
#define SINGLETON_MAKE(className)                        \
private:                                                 \
friend class SingletonBase<className>;                   \
className() = default;                                   \
~className() = default;                                  \
public:                                                  \
className (const className&) = delete;                   \
const className& operator=(const className&) = delete;

	/**********************************************************************
	@ Delete ¿Í Release
	***********************************************************************/

	// Release
#define SAFE_RELEASE(p) {if(p){(p)->Release();}}
#define SAFE_RELEASE_ARRAY(p) {{for(int i = 0; i < sizeof(p) / sizeof(typeid(p)); ++i){(p[i])->Release();}}}
#define SAFE_RELEASE_MAP(p) {for(auto target : (p)){target.second->Release();}(p).clear();}

	// Delete
#define SAFE_DELETE(p) {if(p) delete (p); (p) = nullptr;}
#define SAFE_DELETE_ARRAY(p) {if(p) delete[](p); (p) = nullptr;}
#define SAFE_DELETE_MAP(p) {for(auto target : (p)){delete target.second; target.second = nullptr;} (p).clear();}


}
#endif // !COMMON_MACRO_H