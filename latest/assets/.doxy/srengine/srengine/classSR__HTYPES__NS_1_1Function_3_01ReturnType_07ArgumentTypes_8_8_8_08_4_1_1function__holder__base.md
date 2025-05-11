

# Class SR\_HTYPES\_NS::Function&lt; ReturnType(ArgumentTypes...)&gt;::function\_holder\_base



[**ClassList**](annotated.md) **>** [**function\_holder\_base**](classSR__HTYPES__NS_1_1Function_3_01ReturnType_07ArgumentTypes_8_8_8_08_4_1_1function__holder__base.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual invoker\_t | [**clone**](#function-clone) () = 0<br> |
|   | [**function\_holder\_base**](#function-function_holder_base-12) () = default<br> |
| virtual ReturnType | [**invoke**](#function-invoke) (ArgumentTypes... args) = 0<br> |
| virtual  | [**~function\_holder\_base**](#function-function_holder_base) () = default<br> |




























## Public Functions Documentation




### function clone 

```C++
virtual invoker_t function_holder_base::clone () = 0
```




<hr>



### function function\_holder\_base [1/2]

```C++
function_holder_base::function_holder_base () = default
```




<hr>



### function invoke 

```C++
virtual ReturnType function_holder_base::invoke (
    ArgumentTypes... args
) = 0
```




<hr>



### function ~function\_holder\_base 

```C++
virtual function_holder_base::~function_holder_base () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/Function.h`

