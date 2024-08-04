#if ARM_EABI_EXC_HANDLING
#if !__thumb
#include <cstddef>
#include "cxxabi.h"
#include <cstring>

namespace {

	//	size of the vtable header in RTTI classes
	static const _CXXABI_PTRDIFF_T RTTI_VTBL_HEADER_SIZE = (sizeof(void *) + sizeof(_CXXABI_PTRDIFF_T));

	//	POD version of __fundamental_type_info class
	struct fundamentalPOD {
		const void	*vtablepointer;
		const char	*__type_name;
	};

	//	POD version of __pointer_type_info class
	struct pointerPOD {
		const void	*vtablepointer;
		const char	*__type_name;
		unsigned int __flags;
		const void	*__pointee;
	};

}

#define ABI_NS_NAME(name)			_ZTVN10__cxxabiv1 ## name ## E
#define SI_CLASS_TYPEINFO_VTNAME	ABI_NS_NAME(20__si_class_type_info)
#define VMI_CLASS_TYPEINFO_VTNAME	ABI_NS_NAME(21__vmi_class_type_info)

extern "C" const unsigned char SI_CLASS_TYPEINFO_VTNAME[];
extern "C" const unsigned char VMI_CLASS_TYPEINFO_VTNAME[];

inline bool ClassRTTIVTablePointerCompare(const unsigned char *,const unsigned char *);


namespace {

	struct DerivedToBaseTreeWalkResult {
		const std::type_info*	base_info;		//	pointer to type_info of the base class that we are looking for.
		const unsigned char*	found_obj;		//	pointer to found class sub-object (NULL: not found).
		bool					is_ambig;		//	true: more than one instance was found.
		bool					is_public;		//	true: found on public access path; false: found on private access path.
	};

	/*
	 * Try to find a base class in a given __vmi_class_type_info class using a recursive class type_info tree walk.
	 *
	 * result:			a reference to the DerivedToBaseTreeWalkResult struct.
	 *					The function's result is stored in this struct.
	 * obj_type_info:	a pointer to obj_ptr's type_info struct (shall not be NULL).
	 * obj_ptr:			a pointer to the class object (shall not be NULL).
	 * on_public_path:	true: obj_ptr is on a public class path.
	 *
	 */
	void DerivedToBaseTreeWalk(
		DerivedToBaseTreeWalkResult &result,
		const abi::__vmi_class_type_info *obj_type_info,
		const unsigned char *obj_ptr,
		bool on_public_path
	)
	{
		const abi::__base_class_type_info*	base_info;
		const std::type_info*				base_type_info;
		const unsigned char*				base_ptr;
		const unsigned char*				vtbl_type_info;
		unsigned int						i, n;
		int									is_public;

		for (i = 0, n = obj_type_info->__base_count; i < n; ++i)
		{
			base_info		= &obj_type_info->__base_info[i];
			base_type_info	= base_info->__base_type;
			is_public		= base_info->__is_public();
			//	compute the address of the base class
			if (base_info->__is_virtual())
			{
				base_ptr = obj_ptr + *(_CXXABI_PTRDIFF_T *)(*(const unsigned char **)obj_ptr + base_info->__get_offset());
			}
			else base_ptr = obj_ptr + base_info->__get_offset();

			for (;;)
			{
				if (*base_type_info == *result.base_info)
				{	//	found a match
					if (result.found_obj == base_ptr)
					{	//	it is an ambiguous match
						result.is_ambig = true;
					}
					result.found_obj = base_ptr;
					if (on_public_path && is_public)
					{	//	found on a public path
						result.is_public = true;
					}
					break;	//	we have to keep searching to make sure that result.is_ambig and result.is_public are correct
				}
				//	use type's vtable pointer to detect the proper class type (poor man's RTTI ;-) )
				//	this could probably be done using dynamic_cast, but this will be much faster
				vtbl_type_info	= *(const unsigned char **)base_type_info - RTTI_VTBL_HEADER_SIZE;
				if (!ClassRTTIVTablePointerCompare(vtbl_type_info, SI_CLASS_TYPEINFO_VTNAME))
				{	//	not a simple single inherited class
					if (ClassRTTIVTablePointerCompare(vtbl_type_info, VMI_CLASS_TYPEINFO_VTNAME))
					{	//	base_ptr is a complex nested class, use recursion to check its base classes
						DerivedToBaseTreeWalk(
							result,
							reinterpret_cast<const abi::__vmi_class_type_info *>(base_type_info),
							base_ptr,
							on_public_path && is_public
						);
					}
					break;
				}
				//	base_ptr is a single non-virtual public base class at offset 0,
				//	so we can continue this loop with abi::__si_class_type_info.__base_type
				base_type_info = reinterpret_cast<const abi::__si_class_type_info *>(base_type_info)->__base_type;
				if (!is_public)
				{
					on_public_path	= false;
					is_public		= true;
				}
			}
		}
	}
}

/*
 * Try to convert a derived class pointer to a base class pointer.
 *
 * obj_ptr:			a pointer to a most-derived class object (shall not be NULL).
 * base_ptr_result:	a pointer to a pointer for the found base class result (shall not be NULL).
 * obj_info:		a pointer to obj_ptr's type_info struct (shall not be NULL).
 * base_info:		a pointer to the base class type_info struct (shall not be NULL).
 *
 * The function returns true if obj_ptr has an unambiguous and public "base_info" base class.
 * The address of the found base class is stored in *base_ptr_result.
 *
 */
extern void *matched_base_p;
extern void *current_objectp;
extern "C" int __derived_to_base_conversion(
	void*					obj_ptr,
	void**					base_ptr_result,
	const std::type_info*	obj_info,
	const std::type_info*	base_info
)
{
	const unsigned char *vtbl_type_info;
	obj_ptr = current_objectp;
	for (;;)
	{
		if (*obj_info == *base_info)
		{	//	quick match
			*base_ptr_result = obj_ptr;
			matched_base_p = current_objectp;  /*Santhosh, should have same effect as *base_ptr_result = obj_ptr;*/
			return true;
		}

		//	use type's vtable pointer to detect the proper class type (poor man's RTTI ;-) )
		//	this could probably be done using dynamic_cast, but this will be much faster
		vtbl_type_info	= *(const unsigned char **)obj_info - RTTI_VTBL_HEADER_SIZE;
		if (! ClassRTTIVTablePointerCompare(vtbl_type_info, SI_CLASS_TYPEINFO_VTNAME))
		{	//	not a simple single inherited class
			if (ClassRTTIVTablePointerCompare(vtbl_type_info, VMI_CLASS_TYPEINFO_VTNAME))
			{	//	obj is a complex nested class
				DerivedToBaseTreeWalkResult	result;

				result.base_info	= base_info;
				result.found_obj	= NULL;
				result.is_ambig		= false;
				result.is_public	= false;
				DerivedToBaseTreeWalk(
					result,
					reinterpret_cast<const abi::__vmi_class_type_info *>(obj_info),
					reinterpret_cast<const unsigned char *>(obj_ptr),
					true
				);

				if (result.found_obj != NULL && !result.is_ambig && result.is_public)
				{	//	found an unambiguous and public base class
					*base_ptr_result = (void *)result.found_obj;
					matched_base_p = (void *)result.found_obj; //Santhosh, should have same effect as *base_ptr_result = (void *)result.found_obj;?
					return true;
				}
			}
			break;
		}

		//	obj is a single non-virtual public base class at offset 0,
		//	so we can continue this loop with abi::__si_class_type_info.__base_type
		obj_info = reinterpret_cast<const abi::__si_class_type_info *>(obj_info)->__base_type;
	}

	//	base class was not found
	return false;
}


	/****************************************************************/
	/* Purpose..: Compare two vtable pointers 						*/
	/* Input....: pointer to vtable pointer							*/
	/* Input....: pointer to vtable pointer							*/
	/* Returns..: true: vtables pointers for identical class object	*/
	/****************************************************************/
	inline bool ClassRTTIVTablePointerCompare(const unsigned char *vtbl,const unsigned char *tvtbl)
	{
		if(vtbl==tvtbl) return true;
#if __CXXABI_SAFE_DYNAMICCAST
		//	slow / safe version
		if(vtbl!=NULL)
		{	//	get type_info pointers from vtable header
			vtbl=(const unsigned char *)((RTTIVTableHeader *)vtbl)->md_type_info;
			tvtbl=(const unsigned char *)((RTTIVTableHeader *)tvtbl)->md_type_info;
			if(vtbl!=NULL)
			{
				return __std(strcmp(((fundamentalPOD *)vtbl)->__type_name, ((fundamentalPOD *)tvtbl)->__type_name)) == 0;
			}
		}
#endif
		return false;
	}
#endif //__thumb
#endif //ARM_EABI_EXC_HANDLING