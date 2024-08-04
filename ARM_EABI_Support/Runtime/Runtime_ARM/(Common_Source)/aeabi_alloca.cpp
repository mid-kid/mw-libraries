#include <cxxabi.h>

#ifdef  _CPPABI

// struct array_cookie is defined in the header file cxxabi.h
// array_cookie, cookie_size, cookie_of, etc. are presented for exposition only.
// They are not expected to be available to users, but implementers may find them useful.
// The struct array_cookie fields and the arguments element_size and element_count
// are ordered for convenient use of LDRD/STRD on architecture 5TE and above.

const _CXXABI_SIZE_T cookie_size = sizeof(array_cookie);

// cookie_of() takes a pointer to the user array and returns a reference to the cookie.

inline array_cookie& cookie_of(void* user_array)
{
	return reinterpret_cast<array_cookie*>(user_array)[-1];
}

// element_size_of() takes a pointer to the user array and returns a reference to the
// element_size field of the cookie.

inline _CXXABI_SIZE_T& element_size_of(void* user_array)
{
	return cookie_of(user_array).element_size;
}

// element_count_of() takes a pointer to the user array and returns a reference to the
// element_count field of the cookie.

inline _CXXABI_SIZE_T& element_count_of(void* user_array)
{
	return cookie_of(user_array).element_count;
}

// user_array_of() takes a pointer to the cookie and returns a pointer to the user array.

inline void* user_array_of(array_cookie* cookie_address)
{
	return cookie_address + 1;
}


extern "C" void* __aeabi_vec_ctor_nocookie_nodtor(void* user_array,__cxa_cdtor_type constructor,_CXXABI_SIZE_T element_size, _CXXABI_SIZE_T element_count)
{
	__cxa_cdtor_type destructor=NULL;
	return __cxa_vec_ctor(user_array, element_count, element_size, constructor,destructor);
}

// __aeabi_vec_ctor_cookie_nodtor is like __aeabi_vec_ctor_nocookie_nodtor but sets
// cookie fields and returns user_array. The parameters are arranged to make STRD
// usable. Does nothing and returns NULL if cookie is NULL.

extern "C" void* __aeabi_vec_ctor_cookie_nodtor(array_cookie* cookie,__cxa_cdtor_type constructor,_CXXABI_SIZE_T element_size, _CXXABI_SIZE_T element_count)
{
	if (cookie == NULL)
			return NULL;

	cookie->element_size = element_size; cookie->element_count = element_count;
	return __aeabi_vec_ctor_nocookie_nodtor(user_array_of(cookie), constructor, element_count, element_size);
}

extern "C" void* __aeabi_vec_cctor_nocookie_nodtor(void* user_array_dest,void* user_array_src,_CXXABI_SIZE_T element_size, _CXXABI_SIZE_T element_count,void* (*copy_constructor)(void*, void*))
{
	__cxa_cdtor_type destructor=NULL;
	return __cxa_vec_cctor(user_array_dest, user_array_src,element_count, element_size, copy_constructor, destructor);
}

extern "C" void* __aeabi_vec_new_cookie_noctor(_CXXABI_SIZE_T element_size, _CXXABI_SIZE_T element_count)
{
	array_cookie* cookie =reinterpret_cast<array_cookie*>(::operator new[](element_count * element_size + cookie_size));
	cookie->element_size = element_size; cookie->element_count = element_count;

	return user_array_of(cookie);
}

extern "C" void* __aeabi_vec_new_nocookie(_CXXABI_SIZE_T element_size, _CXXABI_SIZE_T element_count,__cxa_cdtor_type constructor)
{
	return __cxa_vec_new(element_count, element_size, 0, constructor, NULL);
}

extern "C" void* __aeabi_vec_new_cookie_nodtor(_CXXABI_SIZE_T element_size, _CXXABI_SIZE_T element_count,__cxa_cdtor_type constructor)
{
	return __cxa_vec_new(element_count, element_size, cookie_size, constructor, NULL);
}

extern "C" void* __aeabi_vec_new_cookie(_CXXABI_SIZE_T element_size, _CXXABI_SIZE_T element_count,__cxa_cdtor_type constructor,__cxa_cdtor_type destructor)
{
	return __cxa_vec_new(element_count, element_size, cookie_size, constructor, destructor);
}

	// __aeabi_vec_dtor is like __cxa_vec_dtor but has its parameters reordered and returns
	// a pointer to the cookie (assuming user_array has one).
	// Unlike __cxa_vec_dtor, destructor must not be NULL.
	// user_array must not be NULL.

extern "C" void* __aeabi_vec_dtor(void* user_array,__cxa_cdtor_type destructor,_CXXABI_SIZE_T element_size, _CXXABI_SIZE_T element_count)
{
	__cxa_vec_dtor(user_array, element_count, element_size, destructor);
	return &cookie_of(user_array);
}

	// __aeabi_vec_dtor_cookie is only used on arrays that have cookies.
	// __aeabi_vec_dtor is like __cxa_vec_dtor but returns a pointer to the cookie.
	// That is, it takes a pointer to the user array, calls the given destructor on
	// each element (from highest index down to zero) and returns a pointer to the cookie.
	// Does nothing and returns NULL if cookie is NULL.
	// Unlike __cxa_vec_dtor, destructor must not be NULL.
	// Exceptions are handled as in __cxa_vec_dtor.
	// __aeabi_vec_dtor_cookie must not change the element count in the cookie.
	// (But it may corrupt the element size if desired.)

extern "C" void* __aeabi_vec_dtor_cookie(void* user_array, __cxa_cdtor_type destructor)
{
	if (user_array == NULL )
		return NULL;

	return __aeabi_vec_dtor(user_array, destructor,element_size_of(user_array), element_count_of(user_array)) ;
}

extern "C" void __aeabi_vec_delete(void* user_array, __cxa_cdtor_type destructor)
{
		return __cxa_vec_delete(user_array, element_size_of(user_array) ,cookie_size, destructor);
}

extern "C" void __aeabi_vec_delete3(void* user_array, __cxa_cdtor_type destructor, void (*dealloc)(void*, _CXXABI_SIZE_T))
{
	return __cxa_vec_delete3(user_array, element_size_of(user_array), cookie_size, destructor, dealloc);
}

extern "C" void __aeabi_vec_delete3_nodtor(void* user_array, void (*dealloc)(void*, _CXXABI_SIZE_T))
{
	__cxa_cdtor_type destructor=NULL;

	return __cxa_vec_delete3(user_array, element_size_of(user_array),cookie_size, destructor , dealloc);
}

#endif