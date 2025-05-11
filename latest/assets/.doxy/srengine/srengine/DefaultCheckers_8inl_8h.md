

# File DefaultCheckers.inl.h



[**FileList**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Serialization**](dir_1c3f3ba47f77e74f680b6bcf664148dc.md) **>** [**DefaultCheckers.inl.h**](DefaultCheckers_8inl_8h.md)

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
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Serialization/DefaultCheckers.inl.h`

