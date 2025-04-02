

# File Serialization.h



[**FileList**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Serialization**](dir_ffec67008ecd4ba04c0216def73faaef.md) **>** [**Serialization.h**](Serialization_8h.md)

[Go to the source code of this file](Serialization_8h_source.md)



* `#include <Utils/Serialization/Serializer.h>`
* `#include <Utils/Serialization/Deserializer.h>`
* `#include <Utils/Serialization/ObjectDataAccessor.h>`
* `#include <Utils/TypeTraits/Factory.h>`
* `#include <Utils/Types/UnicodeString.h>`
* `#include <Utils/Types/SharedPtr.h>`
* `#include <Utils/Math/Size.h>`
* `#include <Utils/Common/StringAtomLiterals.h>`
* `#include <Codegen/Enums.generated.hpp>`
* `#include <Utils/Serialization/DefaultObjectMakers.inl.h>`
* `#include <Utils/Serialization/SaveCheckers.inl.h>`
* `#include <Utils/Serialization/DefaultCheckers.inl.h>`
* `#include <Utils/Serialization/ObjectDataAccessors.inl.h>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) <br> |
| namespace | [**Details**](namespaceSR__UTILS__NS_1_1Details.md) <br> |
| namespace | [**Serialization**](namespaceSR__UTILS__NS_1_1Serialization.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| struct | [**DefaultChecker**](structSR__UTILS__NS_1_1DefaultChecker.md) &lt;typename T, typename Enable&gt;<br> |
| struct | [**DefaultChecker&lt; SR\_UTILS\_NS::StringAtom &gt;**](structSR__UTILS__NS_1_1DefaultChecker_3_01SR__UTILS__NS_1_1StringAtom_01_4.md) &lt;&gt;<br> |
| struct | [**DefaultChecker&lt; T, std::enable\_if\_t&lt; SerializationTraits&lt; T &gt;::HasEmpty &&!IsTypeFromStdArrayTemplateV&lt; T &gt; &gt; &gt;**](structSR__UTILS__NS_1_1DefaultChecker_3_01T_00_01std_1_1enable__if__t_3_01SerializationTraits_3_f1ad6a1b8208027db52c5c5add79c61d.md) &lt;class T&gt;<br>_Specialization for types with "empty" method (std::vector, std::string, std::array, etc...)_  |
| struct | [**DefaultChecker&lt; T, typename std::enable\_if\_t&lt; std::is\_default\_constructible\_v&lt; T &gt; &&CheckOperatorUsableV&lt; CheckerEqualityComparable, T, T &gt; &&!SerializationTraits&lt; T &gt;::HasEmpty &&!std::is\_same\_v&lt; T, SR\_UTILS\_NS::StringAtom &gt; &gt; &gt;**](structSR__UTILS__NS_1_1DefaultChecker_3_01T_00_01typename_01std_1_1enable__if__t_3_01std_1_1is__5bc20061f0ddc01a3d078bd35df479a5.md) &lt;class T&gt;<br>_Default checkers for serialization._  |
| struct | [**DefaultChecker&lt; std::array&lt; T, N &gt; &gt;**](structSR__UTILS__NS_1_1DefaultChecker_3_01std_1_1array_3_01T_00_01N_01_4_01_4.md) &lt;class T, N&gt;<br> |
| struct | [**DefaultChecker&lt; std::optional&lt; T &gt; &gt;**](structSR__UTILS__NS_1_1DefaultChecker_3_01std_1_1optional_3_01T_01_4_01_4.md) &lt;class T&gt;<br> |
| struct | [**DefaultObjectMaker**](structSR__UTILS__NS_1_1DefaultObjectMaker.md) &lt;typename T, typename Enable&gt;<br>_Default object makers for serialization._  |
| struct | [**DefaultObjectMaker&lt; SR\_HTYPES\_NS::SharedPtr&lt; T &gt; &gt;**](structSR__UTILS__NS_1_1DefaultObjectMaker_3_01SR__HTYPES__NS_1_1SharedPtr_3_01T_01_4_01_4.md) &lt;class T&gt;<br> |
| struct | [**DefaultObjectMaker&lt; SR\_UTILS\_NS::StringAtom &gt;**](structSR__UTILS__NS_1_1DefaultObjectMaker_3_01SR__UTILS__NS_1_1StringAtom_01_4.md) &lt;&gt;<br> |
| struct | [**DefaultObjectMaker&lt; std::map&lt; T, U, Compare, Allocator &gt; &gt;**](structSR__UTILS__NS_1_1DefaultObjectMaker_3_01std_1_1map_3_01T_00_01U_00_01Compare_00_01Allocator_01_4_01_4.md) &lt;typename T, typename U, typename Compare, typename Allocator&gt;<br> |
| struct | [**DefaultObjectMaker&lt; std::optional&lt; T &gt; &gt;**](structSR__UTILS__NS_1_1DefaultObjectMaker_3_01std_1_1optional_3_01T_01_4_01_4.md) &lt;class T&gt;<br> |
| struct | [**DefaultObjectMaker&lt; std::set&lt; T, Less, Allocator &gt; &gt;**](structSR__UTILS__NS_1_1DefaultObjectMaker_3_01std_1_1set_3_01T_00_01Less_00_01Allocator_01_4_01_4.md) &lt;typename T, typename Less, typename Allocator&gt;<br> |
| struct | [**DefaultObjectMaker&lt; std::string &gt;**](structSR__UTILS__NS_1_1DefaultObjectMaker_3_01std_1_1string_01_4.md) &lt;&gt;<br> |
| struct | [**DefaultObjectMaker&lt; std::unordered\_map&lt; T, U, Hash, KeyEqual, Allocator &gt; &gt;**](structSR__UTILS__NS_1_1DefaultObjectMaker_3_01std_1_1unordered__map_3_01T_00_01U_00_01Hash_00_0166c036aa51ea51240830509b4715eacb.md) &lt;typename T, typename U, typename Hash, typename KeyEqual, typename Allocator&gt;<br> |
| struct | [**DefaultObjectMaker&lt; std::vector&lt; T, TOther... &gt; &gt;**](structSR__UTILS__NS_1_1DefaultObjectMaker_3_01std_1_1vector_3_01T_00_01TOther_8_8_8_01_4_01_4.md) &lt;class T, TOther&gt;<br> |
| struct | [**ObjectDataAccessor&lt; SR\_HTYPES\_NS::SharedPtr&lt; T &gt;, std::enable\_if\_t&lt; SerializationTraits&lt; T &gt;::IsSerializable &gt; &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01SR__HTYPES__NS_1_1SharedPtr_3_01T_01_4_00_01std_1_bcc0cde7fe2a1b6a6c918edb68e74246.md) &lt;typename T&gt;<br> |
| struct | [**ObjectDataAccessor&lt; SR\_HTYPES\_NS::SharedPtr&lt; T &gt;, std::enable\_if\_t&lt;!SerializationTraits&lt; T &gt;::HasOriginType &gt; &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01SR__HTYPES__NS_1_1SharedPtr_3_01T_01_4_00_01std_1_863ff9278aaa6e199c62f71431dce0e6.md) &lt;typename T&gt;<br> |
| struct | [**ObjectDataAccessor&lt; SR\_HTYPES\_NS::UnicodeString &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01SR__HTYPES__NS_1_1UnicodeString_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; SR\_MATH\_NS::BVector3 &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01SR__MATH__NS_1_1BVector3_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; SR\_MATH\_NS::BVector4 &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01SR__MATH__NS_1_1BVector4_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; SR\_MATH\_NS::FSize &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01SR__MATH__NS_1_1FSize_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; SR\_MATH\_NS::FSize2 &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01SR__MATH__NS_1_1FSize2_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; SR\_MATH\_NS::FVector2 &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01SR__MATH__NS_1_1FVector2_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; SR\_MATH\_NS::FVector3 &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01SR__MATH__NS_1_1FVector3_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; SR\_MATH\_NS::FVector4 &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01SR__MATH__NS_1_1FVector4_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; SR\_MATH\_NS::FVector6 &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01SR__MATH__NS_1_1FVector6_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; SR\_MATH\_NS::IVector2 &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01SR__MATH__NS_1_1IVector2_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; SR\_MATH\_NS::IVector3 &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01SR__MATH__NS_1_1IVector3_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; SR\_MATH\_NS::IVector4 &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01SR__MATH__NS_1_1IVector4_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; SR\_MATH\_NS::IVector6 &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01SR__MATH__NS_1_1IVector6_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; SR\_MATH\_NS::Quaternion &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01SR__MATH__NS_1_1Quaternion_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; SR\_MATH\_NS::UVector2 &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01SR__MATH__NS_1_1UVector2_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; SR\_MATH\_NS::UVector3 &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01SR__MATH__NS_1_1UVector3_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; SR\_MATH\_NS::UVector4 &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01SR__MATH__NS_1_1UVector4_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; SR\_MATH\_NS::UVector6 &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01SR__MATH__NS_1_1UVector6_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; SR\_UTILS\_NS::StringAtom &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01SR__UTILS__NS_1_1StringAtom_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; T, typename std::enable\_if&lt; IsSREnumV&lt; T &gt; &gt;::type &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01T_00_01typename_01std_1_1enable__if_3_01IsSREnumV_3_01T_01_4_01_4_1_1type_01_4.md) &lt;typename T&gt;<br> |
| struct | [**ObjectDataAccessor&lt; bool &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01bool_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; double\_t &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01double__t_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; float\_t &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01float__t_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; std::array&lt; T, N &gt; &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01std_1_1array_3_01T_00_01N_01_4_01_4.md) &lt;typename T, N&gt;<br> |
| struct | [**ObjectDataAccessor&lt; std::int16\_t &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01std_1_1int16__t_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; std::int32\_t &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01std_1_1int32__t_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; std::int64\_t &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01std_1_1int64__t_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; std::int8\_t &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01std_1_1int8__t_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; std::map&lt; T, U, Compare, Allocator &gt; &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01std_1_1map_3_01T_00_01U_00_01Compare_00_01Allocator_01_4_01_4.md) &lt;typename T, typename U, typename Compare, typename Allocator&gt;<br> |
| struct | [**ObjectDataAccessor&lt; std::optional&lt; T &gt; &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01std_1_1optional_3_01T_01_4_01_4.md) &lt;typename T&gt;<br> |
| struct | [**ObjectDataAccessor&lt; std::pair&lt; T, U &gt; &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01std_1_1pair_3_01T_00_01U_01_4_01_4.md) &lt;typename T, typename U&gt;<br> |
| struct | [**ObjectDataAccessor&lt; std::set&lt; T, Less, Allocator &gt; &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01std_1_1set_3_01T_00_01Less_00_01Allocator_01_4_01_4.md) &lt;typename T, typename Less, typename Allocator&gt;<br> |
| struct | [**ObjectDataAccessor&lt; std::string &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01std_1_1string_01_4.md) &lt;&gt;<br>_Data accessors for objects serialization._  |
| struct | [**ObjectDataAccessor&lt; std::uint16\_t &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01std_1_1uint16__t_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; std::uint32\_t &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01std_1_1uint32__t_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; std::uint64\_t &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01std_1_1uint64__t_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; std::uint8\_t &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01std_1_1uint8__t_01_4.md) &lt;&gt;<br> |
| struct | [**ObjectDataAccessor&lt; std::vector&lt; T, TOther... &gt; &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01std_1_1vector_3_01T_00_01TOther_8_8_8_01_4_01_4.md) &lt;typename T, TOther&gt;<br> |
| struct | [**ObjectDataAccessorMathVector**](structSR__UTILS__NS_1_1ObjectDataAccessorMathVector.md) &lt;typename Type, dim&gt;<br> |
| struct | [**ObjectDataAccessorVector**](structSR__UTILS__NS_1_1ObjectDataAccessorVector.md) &lt;class T&gt;<br> |
| struct | [**SaveChecker**](structSR__UTILS__NS_1_1SaveChecker.md) &lt;typename T, typename Enable&gt;<br> |
| struct | [**SaveChecker&lt; SR\_HTYPES\_NS::SharedPtr&lt; T &gt;, std::enable\_if\_t&lt; SerializationTraits&lt; T &gt;::IsSerializable &gt; &gt;**](structSR__UTILS__NS_1_1SaveChecker_3_01SR__HTYPES__NS_1_1SharedPtr_3_01T_01_4_00_01std_1_1enable9d207a6623f032e90f18b6ab57d365d7.md) &lt;typename T&gt;<br> |
| struct | [**SaveChecker&lt; T, typename std::enable\_if&lt; SerializationTraits&lt; T &gt;::IsSerializable &gt;::type &gt;**](structSR__UTILS__NS_1_1SaveChecker_3_01T_00_01typename_01std_1_1enable__if_3_01SerializationTrai86ff178b9c6ba98343a5edcb76ff7b5c.md) &lt;typename T&gt;<br> |
| struct | [**SerializationTraits**](structSR__UTILS__NS_1_1SerializationTraits.md) &lt;typename T&gt;<br> |



















































------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Serialization/Serialization.h`

