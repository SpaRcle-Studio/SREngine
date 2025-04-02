

# File TypeInfo.h



[**FileList**](files.md) **>** [**Common**](dir_964cfbb3f15edef5ecfb3ae3bc01626c.md) **>** [**TypeInfo.h**](Utils_2inc_2Utils_2Common_2TypeInfo_8h.md)

[Go to the source code of this file](Utils_2inc_2Utils_2Common_2TypeInfo_8h_source.md)



* `#include <Utils/Common/Enumerations.h>`
* `#include <Utils/Common/AnyVisitor.h>`
* `#include <Utils/Math/Size.h>`
* `#include <Utils/Math/Vector2.h>`
* `#include <Utils/Math/Vector3.h>`
* `#include <Utils/Math/Vector4.h>`
* `#include <Utils/Math/Vector6.h>`
* `#include <Utils/Types/UnicodeString.h>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) <br> |
| namespace | [**is\_stl\_container\_impl**](namespaceSR__UTILS__NS_1_1is__stl__container__impl.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| struct | [**IsSTLContainer**](structSR__UTILS__NS_1_1IsSTLContainer.md) &lt;typename T&gt;<br>_type trait to utilize the implementation type traits as well as decay the type_  |
| struct | [**is\_stl\_container**](structSR__UTILS__NS_1_1is__stl__container__impl_1_1is__stl__container.md) &lt;typename T&gt;<br> |
| struct | [**is\_stl\_container&lt; std::array&lt; T, N &gt; &gt;**](structSR__UTILS__NS_1_1is__stl__container__impl_1_1is__stl__container_3_01std_1_1array_3_01T_00_01N_01_4_01_4.md) &lt;typename T, N&gt;<br> |
| struct | [**is\_stl\_container&lt; std::deque&lt; Args... &gt; &gt;**](structSR__UTILS__NS_1_1is__stl__container__impl_1_1is__stl__container_3_01std_1_1deque_3_01Args_8_8_8_01_4_01_4.md) &lt;Args&gt;<br> |
| struct | [**is\_stl\_container&lt; std::list&lt; Args... &gt; &gt;**](structSR__UTILS__NS_1_1is__stl__container__impl_1_1is__stl__container_3_01std_1_1list_3_01Args_8_8_8_01_4_01_4.md) &lt;Args&gt;<br> |
| struct | [**is\_stl\_container&lt; std::map&lt; Args... &gt; &gt;**](structSR__UTILS__NS_1_1is__stl__container__impl_1_1is__stl__container_3_01std_1_1map_3_01Args_8_8_8_01_4_01_4.md) &lt;Args&gt;<br> |
| struct | [**is\_stl\_container&lt; std::multimap&lt; Args... &gt; &gt;**](structSR__UTILS__NS_1_1is__stl__container__impl_1_1is__stl__container_3_01std_1_1multimap_3_01Args_8_8_8_01_4_01_4.md) &lt;Args&gt;<br> |
| struct | [**is\_stl\_container&lt; std::multiset&lt; Args... &gt; &gt;**](structSR__UTILS__NS_1_1is__stl__container__impl_1_1is__stl__container_3_01std_1_1multiset_3_01Args_8_8_8_01_4_01_4.md) &lt;Args&gt;<br> |
| struct | [**is\_stl\_container&lt; std::priority\_queue&lt; Args... &gt; &gt;**](structSR__UTILS__NS_1_1is__stl__container__impl_1_1is__stl__container_3_01std_1_1priority__queue_3_01Args_8_8_8_01_4_01_4.md) &lt;Args&gt;<br> |
| struct | [**is\_stl\_container&lt; std::queue&lt; Args... &gt; &gt;**](structSR__UTILS__NS_1_1is__stl__container__impl_1_1is__stl__container_3_01std_1_1queue_3_01Args_8_8_8_01_4_01_4.md) &lt;Args&gt;<br> |
| struct | [**is\_stl\_container&lt; std::set&lt; Args... &gt; &gt;**](structSR__UTILS__NS_1_1is__stl__container__impl_1_1is__stl__container_3_01std_1_1set_3_01Args_8_8_8_01_4_01_4.md) &lt;Args&gt;<br> |
| struct | [**is\_stl\_container&lt; std::stack&lt; Args... &gt; &gt;**](structSR__UTILS__NS_1_1is__stl__container__impl_1_1is__stl__container_3_01std_1_1stack_3_01Args_8_8_8_01_4_01_4.md) &lt;Args&gt;<br> |
| struct | [**is\_stl\_container&lt; std::unordered\_map&lt; Args... &gt; &gt;**](structSR__UTILS__NS_1_1is__stl__container__impl_1_1is__stl__container_3_01std_1_1unordered__map_3_01Args_8_8_8_01_4_01_4.md) &lt;Args&gt;<br> |
| struct | [**is\_stl\_container&lt; std::unordered\_multimap&lt; Args... &gt; &gt;**](structSR__UTILS__NS_1_1is__stl__container__impl_1_1is__stl__container_3_01std_1_1unordered__multimap_3_01Args_8_8_8_01_4_01_4.md) &lt;Args&gt;<br> |
| struct | [**is\_stl\_container&lt; std::unordered\_multiset&lt; Args... &gt; &gt;**](structSR__UTILS__NS_1_1is__stl__container__impl_1_1is__stl__container_3_01std_1_1unordered__multiset_3_01Args_8_8_8_01_4_01_4.md) &lt;Args&gt;<br> |
| struct | [**is\_stl\_container&lt; std::unordered\_set&lt; Args... &gt; &gt;**](structSR__UTILS__NS_1_1is__stl__container__impl_1_1is__stl__container_3_01std_1_1unordered__set_3_01Args_8_8_8_01_4_01_4.md) &lt;Args&gt;<br> |
| struct | [**is\_stl\_container&lt; std::vector&lt; Args... &gt; &gt;**](structSR__UTILS__NS_1_1is__stl__container__impl_1_1is__stl__container_3_01std_1_1vector_3_01Args_8_8_8_01_4_01_4.md) &lt;Args&gt;<br> |
| struct | [**is\_stl\_vector**](structSR__UTILS__NS_1_1is__stl__container__impl_1_1is__stl__vector.md) &lt;typename T&gt;<br> |
| struct | [**is\_stl\_vector&lt; std::vector&lt; Args... &gt; &gt;**](structSR__UTILS__NS_1_1is__stl__container__impl_1_1is__stl__vector_3_01std_1_1vector_3_01Args_8_8_8_01_4_01_4.md) &lt;Args&gt;<br> |


## Public Types

| Type | Name |
| ---: | :--- |
| union  | [**StandardData**](#union-standarddata)  <br> |
















































## Public Types Documentation




### union StandardData 

```C++

```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Common/TypeInfo.h`

