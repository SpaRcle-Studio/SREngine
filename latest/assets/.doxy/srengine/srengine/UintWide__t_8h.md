

# File UintWide\_t.h



[**FileList**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Types**](dir_e2eff6081ed67c5bc03a553ef17d8efc.md) **>** [**UintWide\_t.h**](UintWide__t_8h.md)

[Go to the source code of this file](UintWide__t_8h_source.md)



* `#include <ciso646>`
* `#include <cinttypes>`
* `#include <cmath>`
* `#include <cstddef>`
* `#include <cstdint>`
* `#include <cstdlib>`
* `#include <cstring>`
* `#include <initializer_list>`
* `#include <iomanip>`
* `#include <istream>`
* `#include <limits>`
* `#include <memory>`
* `#include <ostream>`
* `#include <sstream>`
* `#include <string>`
* `#include <type_traits>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**SR\_TYPES\_NS**](namespaceSR__TYPES__NS.md) <br> |
| namespace | [**detail**](namespaceSR__TYPES__NS_1_1detail.md) <br> |
| namespace | [**array\_detail**](namespaceSR__TYPES__NS_1_1detail_1_1array__detail.md) <br> |
| namespace | [**distance\_detail**](namespaceSR__TYPES__NS_1_1detail_1_1distance__detail.md) <br> |
| namespace | [**iterator\_detail**](namespaceSR__TYPES__NS_1_1detail_1_1iterator__detail.md) <br> |
| namespace | [**my\_own**](namespaceSR__TYPES__NS_1_1detail_1_1my__own.md) <br> |
| namespace | [**std**](namespacestd.md) <br> |
| namespace | [**test\_uintwide\_t\_edge**](namespacetest__uintwide__t__edge.md) <br> |
| namespace | [**util**](namespaceutil.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| struct | [**allocator\_dummy\_unsafe**](structSR__TYPES__NS_1_1detail_1_1allocator__dummy__unsafe.md) <br> |
| class | [**fixed\_dynamic\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__dynamic__array.md) &lt;typename MyType, MySize, typename MyAlloc&gt;<br> |
| class | [**fixed\_static\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__static__array.md) &lt;typename MyType, MySize&gt;<br> |
| class | [**bidirectional\_iterator\_tag**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1bidirectional__iterator__tag.md) <br> |
| class | [**forward\_iterator\_tag**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1forward__iterator__tag.md) <br> |
| class | [**input\_iterator\_tag**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1input__iterator__tag.md) <br> |
| class | [**iterator\_traits**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1iterator__traits.md) &lt;typename iterator\_type&gt;<br> |
| class | [**iterator\_traits&lt; T \* &gt;**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1iterator__traits_3_01T_01_5_01_4.md) &lt;typename T&gt;<br> |
| class | [**iterator\_traits&lt; const T \* &gt;**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1iterator__traits_3_01const_01T_01_5_01_4.md) &lt;typename T&gt;<br> |
| struct | [**my\_iterator**](structSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1my__iterator.md) &lt;typename my\_category, typename my\_value\_type, typename my\_difference\_type, typename my\_pointer\_type, typename my\_reference\_type&gt;<br> |
| class | [**output\_iterator\_tag**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1output__iterator__tag.md) <br> |
| class | [**random\_access\_iterator\_tag**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1random__access__iterator__tag.md) <br> |
| class | [**reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md) &lt;typename iterator\_type&gt;<br> |
| class | [**native\_float\_parts**](classSR__TYPES__NS_1_1detail_1_1native__float__parts.md) &lt;typename FloatingPointType&gt;<br> |
| struct | [**verify\_power\_of\_two\_times\_granularity\_one\_sixty\_fourth**](structSR__TYPES__NS_1_1detail_1_1verify__power__of__two__times__granularity__one__sixty__fourth.md) &lt;Width2&gt;<br> |
| struct | [**is\_integral**](structSR__TYPES__NS_1_1is__integral.md) &lt;class T&gt;<br> |
| struct | [**is\_integral&lt; SR\_TYPES\_NS::uintwide\_t&lt; Width2, LimbType, AllocatorType, IsSigned &gt; &gt;**](structSR__TYPES__NS_1_1is__integral_3_01SR__TYPES__NS_1_1uintwide__t_3_01Width2_00_01LimbType_00fc01edcfaa0e24ac94a4ffb2aaad7198.md) &lt;Width2, typename LimbType, typename AllocatorType, IsSigned&gt;<br> |
| struct | [**param\_type**](structSR__TYPES__NS_1_1uniform__int__distribution_1_1param__type.md) <br> |

















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**UINTWIDE\_T\_2018\_10\_02\_H**](UintWide__t_8h.md#define-uintwide_t_2018_10_02_h)  <br> |
| define  | [**WIDE\_INTEGER\_NAMESPACE\_BEGIN**](UintWide__t_8h.md#define-wide_integer_namespace_begin)  <br> |
| define  | [**WIDE\_INTEGER\_NAMESPACE\_END**](UintWide__t_8h.md#define-wide_integer_namespace_end)  <br> |
| define  | [**WIDE\_INTEGER\_NODISCARD**](UintWide__t_8h.md#define-wide_integer_nodiscard)  <br> |
| define  | [**WIDE\_INTEGER\_NUM\_LIMITS\_CLASS\_TYPE**](UintWide__t_8h.md#define-wide_integer_num_limits_class_type)  `class`<br> |

## Macro Definition Documentation





### define UINTWIDE\_T\_2018\_10\_02\_H 

```C++
#define UINTWIDE_T_2018_10_02_H 
```




<hr>



### define WIDE\_INTEGER\_NAMESPACE\_BEGIN 

```C++
#define WIDE_INTEGER_NAMESPACE_BEGIN 
```




<hr>



### define WIDE\_INTEGER\_NAMESPACE\_END 

```C++
#define WIDE_INTEGER_NAMESPACE_END 
```




<hr>



### define WIDE\_INTEGER\_NODISCARD 

```C++
#define WIDE_INTEGER_NODISCARD 
```




<hr>



### define WIDE\_INTEGER\_NUM\_LIMITS\_CLASS\_TYPE 

```C++
#define WIDE_INTEGER_NUM_LIMITS_CLASS_TYPE `class`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/UintWide_t.h`

