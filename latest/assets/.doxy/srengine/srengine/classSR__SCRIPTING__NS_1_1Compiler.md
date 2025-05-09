

# Class SR\_SCRIPTING\_NS::Compiler



[**ClassList**](annotated.md) **>** [**SR\_SCRIPTING\_NS**](namespaceSR__SCRIPTING__NS.md) **>** [**Compiler**](classSR__SCRIPTING__NS_1_1Compiler.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_SCRIPTING\_NS::EvoCompiler](classSR__SCRIPTING__NS_1_1EvoCompiler.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual bool | [**Init**](#function-init) () = 0<br> |
|   | [**~Compiler**](#function-compiler) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |














## Protected Attributes

| Type | Name |
| ---: | :--- |
|  Mutex | [**m\_mutex**](#variable-m_mutex)   = `Mutex()`<br> |
































## Protected Functions

| Type | Name |
| ---: | :--- |
|   | [**Compiler**](#function-compiler) () = default<br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Functions Documentation




### function Init 

```C++
virtual bool SR_SCRIPTING_NS::Compiler::Init () = 0
```




<hr>



### function ~Compiler 

```C++
SR_SCRIPTING_NS::Compiler::~Compiler () override
```




<hr>
## Protected Attributes Documentation




### variable m\_mutex 

```C++
Mutex SR_SCRIPTING_NS::Compiler::m_mutex;
```




<hr>
## Protected Functions Documentation




### function Compiler 

```C++
SR_SCRIPTING_NS::Compiler::Compiler () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Scripting/inc/Scripting/Old/Compiler.h`

