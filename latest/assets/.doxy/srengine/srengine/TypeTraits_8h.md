

# File TypeTraits.h



[**FileList**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**TypeTraits**](dir_16c2d3fce5275752976e0da6f3af1bdb.md) **>** [**TypeTraits.h**](TypeTraits_8h.md)

[Go to the source code of this file](TypeTraits_8h_source.md)



* `#include <Utils/Common/Hashes.h>`
* `#include <Utils/Common/EnumReflector.h>`
* `#include <Utils/Math/Vector2.h>`
* `#include <Utils/Math/Vector3.h>`
* `#include <Utils/Math/Vector4.h>`
* `#include <Utils/Math/Vector6.h>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) <br> |
| namespace | [**Details**](namespaceSR__UTILS__NS_1_1Details.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| struct | [**CheckOperatorUsable**](structSR__UTILS__NS_1_1CheckOperatorUsable.md) &lt;Op, class X, class Y, typename&gt;<br> |
| struct | [**CheckOperatorUsable&lt; CheckerEqualityComparable, std::optional&lt; T &gt;, std::optional&lt; T &gt; &gt;**](structSR__UTILS__NS_1_1CheckOperatorUsable_3_01CheckerEqualityComparable_00_01std_1_1optional_3_835c32e76e2a52d0e0f22fbe39d31aa3.md) &lt;typename T&gt;<br> |
| struct | [**CheckOperatorUsable&lt; Op, X, Y, std::enable\_if\_t&lt; std::is\_same\_v&lt; Y, std::nullptr\_t &gt; &&!SupportsNullptrComparisonV&lt; X &gt; &gt; &gt;**](structSR__UTILS__NS_1_1CheckOperatorUsable_3_01Op_00_01X_00_01Y_00_01std_1_1enable__if__t_3_01stc413c9f9798c835c9db20a200ab862b9.md) &lt;Op, class X, class Y&gt;<br> |
| struct | [**DetectedOr**](structSR__UTILS__NS_1_1DetectedOr.md) &lt;class Default, Op, Args&gt;<br> |
| struct | [**GetFirstOfTypeFromSequence**](structSR__UTILS__NS_1_1GetFirstOfTypeFromSequence.md) &lt;class T, class Pair, Pairs&gt;<br> |
| struct | [**GetFirstOfTypeFromSequence&lt; T, Pair &gt;**](structSR__UTILS__NS_1_1GetFirstOfTypeFromSequence_3_01T_00_01Pair_01_4.md) &lt;class T, class Pair&gt;<br> |
| struct | [**GetFirstOfTypeFromSequenceAssert**](structSR__UTILS__NS_1_1GetFirstOfTypeFromSequenceAssert.md) &lt;class T&gt;<br> |
| struct | [**IsCompleteType**](structSR__UTILS__NS_1_1IsCompleteType.md) &lt;typename T, typename&gt;<br> |
| struct | [**IsCompleteType&lt; T, std::void\_t&lt; decltype(sizeof(T))&gt; &gt;**](structSR__UTILS__NS_1_1IsCompleteType_3_01T_00_01std_1_1void__t_3_01decltype_07sizeof_07T_08_08_4_01_4.md) &lt;typename T&gt;<br> |
| struct | [**IsDetected**](structSR__UTILS__NS_1_1IsDetected.md) &lt;Op, Args&gt;<br> |
| struct | [**IsDetectedConvertible**](structSR__UTILS__NS_1_1IsDetectedConvertible.md) &lt;class To, Op, Args&gt;<br> |
| struct | [**IsDetectedExact**](structSR__UTILS__NS_1_1IsDetectedExact.md) &lt;class Expected, Op, Args&gt;<br> |
| struct | [**IsEnum**](structSR__UTILS__NS_1_1IsEnum.md) &lt;class T&gt;<br> |
| struct | [**IsSREnum**](structSR__UTILS__NS_1_1IsSREnum.md) &lt;class T&gt;<br> |
| struct | [**IsSameClassTemplate**](structSR__UTILS__NS_1_1IsSameClassTemplate.md) &lt;Tmpl1, Tmpl2&gt;<br> |
| struct | [**IsSameClassTemplate&lt; Tmpl, Tmpl &gt;**](structSR__UTILS__NS_1_1IsSameClassTemplate_3_01Tmpl_00_01Tmpl_01_4.md) &lt;Tmpl&gt;<br> |
| struct | [**IsStdArrayTemplate**](structSR__UTILS__NS_1_1IsStdArrayTemplate.md) &lt;Tmpl1&gt;<br> |
| struct | [**IsStdArrayTemplate&lt; std::array &gt;**](structSR__UTILS__NS_1_1IsStdArrayTemplate_3_01std_1_1array_01_4.md) &lt;&gt;<br> |
| struct | [**IsTemplateClass**](structSR__UTILS__NS_1_1IsTemplateClass.md) &lt;typename&gt;<br> |
| struct | [**IsTemplateClass&lt; Tmpl&lt; Args... &gt; &gt;**](structSR__UTILS__NS_1_1IsTemplateClass_3_01Tmpl_3_01Args_8_8_8_01_4_01_4.md) &lt;Tmpl, Args&gt;<br> |
| struct | [**IsTypeFromClassTemplate**](structSR__UTILS__NS_1_1IsTypeFromClassTemplate.md) &lt;typename, typename&gt;<br> |
| struct | [**IsTypeFromClassTemplate&lt; Tmpl&lt; Args... &gt;, Tmpl &gt;**](structSR__UTILS__NS_1_1IsTypeFromClassTemplate_3_01Tmpl_3_01Args_8_8_8_01_4_00_01Tmpl_01_4.md) &lt;Tmpl, Args&gt;<br> |
| struct | [**IsTypeFromStdArrayTemplate**](structSR__UTILS__NS_1_1IsTypeFromStdArrayTemplate.md) &lt;typename T&gt;<br> |
| struct | [**IsTypeFromStdArrayTemplate&lt; std::array&lt; T, N &gt; &gt;**](structSR__UTILS__NS_1_1IsTypeFromStdArrayTemplate_3_01std_1_1array_3_01T_00_01N_01_4_01_4.md) &lt;typename T, N&gt;<br> |
| struct | [**RemoveCVRef**](structSR__UTILS__NS_1_1RemoveCVRef.md) &lt;class T&gt;<br> |
| struct | [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) <br> |
| struct | [**SupportsNullptrComparison**](structSR__UTILS__NS_1_1SupportsNullptrComparison.md) &lt;typename T&gt;<br> |
| struct | [**SupportsNullptrComparison&lt; SR\_MATH\_NS::Vector2&lt; T &gt; &gt;**](structSR__UTILS__NS_1_1SupportsNullptrComparison_3_01SR__MATH__NS_1_1Vector2_3_01T_01_4_01_4.md) &lt;typename T&gt;<br> |
| struct | [**SupportsNullptrComparison&lt; SR\_MATH\_NS::Vector3&lt; T &gt; &gt;**](structSR__UTILS__NS_1_1SupportsNullptrComparison_3_01SR__MATH__NS_1_1Vector3_3_01T_01_4_01_4.md) &lt;typename T&gt;<br> |
| struct | [**SupportsNullptrComparison&lt; SR\_MATH\_NS::Vector4&lt; T &gt; &gt;**](structSR__UTILS__NS_1_1SupportsNullptrComparison_3_01SR__MATH__NS_1_1Vector4_3_01T_01_4_01_4.md) &lt;typename T&gt;<br> |
| struct | [**SupportsNullptrComparison&lt; SR\_MATH\_NS::Vector6&lt; T &gt; &gt;**](structSR__UTILS__NS_1_1SupportsNullptrComparison_3_01SR__MATH__NS_1_1Vector6_3_01T_01_4_01_4.md) &lt;typename T&gt;<br> |
| struct | [**TypeValuePair**](structSR__UTILS__NS_1_1TypeValuePair.md) &lt;class T, val&gt;<br> |



















































------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/TypeTraits/TypeTraits.h`

