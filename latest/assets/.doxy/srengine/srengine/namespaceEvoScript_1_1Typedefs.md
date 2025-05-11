

# Namespace EvoScript::Typedefs



[**Namespace List**](namespaces.md) **>** [**EvoScript**](namespaceEvoScript.md) **>** [**Typedefs**](namespaceEvoScript_1_1Typedefs.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef void \*(\* | [**AllocateMemoryFnPtr**](#typedef-allocatememoryfnptr)  <br> |
| typedef void(\* | [**AwakeFnPtr**](#typedef-awakefnptr)  <br> |
| typedef void(\* | [**CloseFnPtr**](#typedef-closefnptr)  <br> |
| typedef void(\* | [**FixedUpdateFnPtr**](#typedef-fixedupdatefnptr)  <br> |
| typedef void(\* | [**FreeMemoryFnPtr**](#typedef-freememoryfnptr)  <br> |
| typedef std::vector&lt; std::string &gt;(\* | [**GetPropertiesFnPtr**](#typedef-getpropertiesfnptr)  <br> |
| typedef std::any(\* | [**GetPropertyFnPtr**](#typedef-getpropertyfnptr)  <br> |
| typedef void \*(\* | [**InitBehaviourFnPtr**](#typedef-initbehaviourfnptr)  <br> |
| typedef void(\* | [**InitFnPtr**](#typedef-initfnptr)  <br>_сборник разных типов методов на все случаи жизни_  |
| typedef void(\* | [**OnDisableFnPtr**](#typedef-ondisablefnptr)  <br> |
| typedef void(\* | [**OnEnableFnPtr**](#typedef-onenablefnptr)  <br> |
| typedef void(\* | [**OnGUIFnPtr**](#typedef-onguifnptr)  <br> |
| typedef void(\* | [**ReleaseBehaviourFnPtr**](#typedef-releasebehaviourfnptr)  <br> |
| typedef void(\* | [**SetAllocateMemoryFnPtr**](#typedef-setallocatememoryfnptr)  <br> |
| typedef void(\* | [**SetFreeMemoryFnPtr**](#typedef-setfreememoryfnptr)  <br> |
| typedef void(\* | [**SetPropertyFnPtr**](#typedef-setpropertyfnptr)  <br> |
| typedef void(\* | [**StartFnPtr**](#typedef-startfnptr)  <br> |
| typedef void(\* | [**SwitchContextFnPtr**](#typedef-switchcontextfnptr)  <br> |
| typedef void(\* | [**UpdateFnPtr**](#typedef-updatefnptr)  <br> |
| typedef void(\* | [**VoidFnPtr**](#typedef-voidfnptr)  <br> |
















































## Public Types Documentation




### typedef AllocateMemoryFnPtr 

```C++
typedef void *(* EvoScript::Typedefs::AllocateMemoryFnPtr) (size_t sz);
```




<hr>



### typedef AwakeFnPtr 

```C++
typedef void(* EvoScript::Typedefs::AwakeFnPtr) ();
```




<hr>



### typedef CloseFnPtr 

```C++
typedef void(* EvoScript::Typedefs::CloseFnPtr) ();
```




<hr>



### typedef FixedUpdateFnPtr 

```C++
typedef void(* EvoScript::Typedefs::FixedUpdateFnPtr) ();
```




<hr>



### typedef FreeMemoryFnPtr 

```C++
typedef void(* EvoScript::Typedefs::FreeMemoryFnPtr) (void *ptr);
```




<hr>



### typedef GetPropertiesFnPtr 

```C++
typedef std::vector< std::string >(* EvoScript::Typedefs::GetPropertiesFnPtr) ();
```




<hr>



### typedef GetPropertyFnPtr 

```C++
typedef std::any(* EvoScript::Typedefs::GetPropertyFnPtr) (const std::string &id);
```




<hr>



### typedef InitBehaviourFnPtr 

```C++
typedef void *(* EvoScript::Typedefs::InitBehaviourFnPtr) ();
```




<hr>



### typedef InitFnPtr 

_сборник разных типов методов на все случаи жизни_ 
```C++
typedef void(* EvoScript::Typedefs::InitFnPtr) (void **);
```




<hr>



### typedef OnDisableFnPtr 

```C++
typedef void(* EvoScript::Typedefs::OnDisableFnPtr) ();
```




<hr>



### typedef OnEnableFnPtr 

```C++
typedef void(* EvoScript::Typedefs::OnEnableFnPtr) ();
```




<hr>



### typedef OnGUIFnPtr 

```C++
typedef void(* EvoScript::Typedefs::OnGUIFnPtr) ();
```




<hr>



### typedef ReleaseBehaviourFnPtr 

```C++
typedef void(* EvoScript::Typedefs::ReleaseBehaviourFnPtr) ();
```




<hr>



### typedef SetAllocateMemoryFnPtr 

```C++
typedef void(* EvoScript::Typedefs::SetAllocateMemoryFnPtr) (AllocateMemoryFnPtr);
```




<hr>



### typedef SetFreeMemoryFnPtr 

```C++
typedef void(* EvoScript::Typedefs::SetFreeMemoryFnPtr) (FreeMemoryFnPtr);
```




<hr>



### typedef SetPropertyFnPtr 

```C++
typedef void(* EvoScript::Typedefs::SetPropertyFnPtr) (const std::string &id, const std::any &val);
```




<hr>



### typedef StartFnPtr 

```C++
typedef void(* EvoScript::Typedefs::StartFnPtr) ();
```




<hr>



### typedef SwitchContextFnPtr 

```C++
typedef void(* EvoScript::Typedefs::SwitchContextFnPtr) (void *pContext);
```




<hr>



### typedef UpdateFnPtr 

```C++
typedef void(* EvoScript::Typedefs::UpdateFnPtr) (float dt);
```




<hr>



### typedef VoidFnPtr 

```C++
typedef void(* EvoScript::Typedefs::VoidFnPtr) ();
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Scripting/inc/Scripting/Old/Compilation/Typedefs.h`

