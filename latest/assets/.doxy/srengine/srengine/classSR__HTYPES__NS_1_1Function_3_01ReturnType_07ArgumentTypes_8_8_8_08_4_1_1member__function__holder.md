

# Class SR\_HTYPES\_NS::Function&lt; ReturnType(ArgumentTypes...)&gt;::member\_function\_holder

**template &lt;typename FunctionType, typename ClassType, typename ... RestArgumentTypes&gt;**



[**ClassList**](annotated.md) **>** [**member\_function\_holder**](classSR__HTYPES__NS_1_1Function_3_01ReturnType_07ArgumentTypes_8_8_8_08_4_1_1member__function__holder.md)








Inherits the following classes: SR_HTYPES_NS::Function< ReturnType(ArgumentTypes...)>::function_holder_base














## Public Types

| Type | Name |
| ---: | :--- |
| typedef FunctionType ClassType::\* | [**member\_function\_signature\_t**](#typedef-member_function_signature_t)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
| virtual invoker\_t | [**clone**](#function-clone) () <br> |
| virtual ReturnType | [**invoke**](#function-invoke) (ClassType obj, RestArgumentTypes... restArgs) <br> |
|   | [**member\_function\_holder**](#function-member_function_holder) (member\_function\_signature\_t f) <br>_NOLINT._  |




























## Public Types Documentation




### typedef member\_function\_signature\_t 

```C++
typedef FunctionType ClassType::* SR_HTYPES_NS::Function< ReturnType(ArgumentTypes...)>::member_function_holder< FunctionType, ClassType, RestArgumentTypes >::member_function_signature_t;
```




<hr>
## Public Functions Documentation




### function clone 

```C++
inline virtual invoker_t member_function_holder::clone () 
```




<hr>



### function invoke 

```C++
inline virtual ReturnType member_function_holder::invoke (
    ClassType obj,
    RestArgumentTypes... restArgs
) 
```




<hr>



### function member\_function\_holder 

_NOLINT._ 
```C++
inline member_function_holder::member_function_holder (
    member_function_signature_t f
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/Function.h`

