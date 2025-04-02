

# File DefaultCheckers.inl.h



[**FileList**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Serialization**](dir_ffec67008ecd4ba04c0216def73faaef.md) **>** [**DefaultCheckers.inl.h**](DefaultCheckers_8inl_8h.md)

[Go to the source code of this file](DefaultCheckers_8inl_8h_source.md)


















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**DefaultChecker&lt; SR\_UTILS\_NS::StringAtom &gt;**](structDefaultChecker_3_01SR__UTILS__NS_1_1StringAtom_01_4.md) &lt;&gt;<br> |
| struct | [**DefaultChecker&lt; T, std::enable\_if\_t&lt; SerializationTraits&lt; T &gt;::HasEmpty &&!IsTypeFromStdArrayTemplateV&lt; T &gt; &gt; &gt;**](structDefaultChecker_3_01T_00_01std_1_1enable__if__t_3_01SerializationTraits_3_01T_01_4_1_1HasEm7f8e838d2164f5264d4241b1c97027d7.md) &lt;class T&gt;<br>_Specialization for types with "empty" method (std::vector, std::string, std::array, etc...)_  |
| struct | [**DefaultChecker&lt; T, typename std::enable\_if\_t&lt; std::is\_default\_constructible\_v&lt; T &gt; &&CheckOperatorUsableV&lt; CheckerEqualityComparable, T, T &gt; &&!SerializationTraits&lt; T &gt;::HasEmpty &&!std::is\_same\_v&lt; T, SR\_UTILS\_NS::StringAtom &gt; &gt; &gt;**](structDefaultChecker_3_01T_00_01typename_01std_1_1enable__if__t_3_01std_1_1is__default__construccd7dc995762fd2295150430612ff7889.md) &lt;class T&gt;<br> |
| struct | [**DefaultChecker&lt; std::array&lt; T, N &gt; &gt;**](structDefaultChecker_3_01std_1_1array_3_01T_00_01N_01_4_01_4.md) &lt;class T, N&gt;<br> |
| struct | [**DefaultChecker&lt; std::optional&lt; T &gt; &gt;**](structDefaultChecker_3_01std_1_1optional_3_01T_01_4_01_4.md) &lt;class T&gt;<br> |



















































------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Serialization/DefaultCheckers.inl.h`

