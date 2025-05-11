

# Class SR\_UTILS\_NS::Localization::LocalizationFile



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Localization**](namespaceSR__UTILS__NS_1_1Localization.md) **>** [**LocalizationFile**](classSR__UTILS__NS_1_1Localization_1_1LocalizationFile.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  [**SR\_HTYPES\_NS::UnicodeString**](classSR__HTYPES__NS_1_1UnicodeString.md) | [**GetStringById**](#function-getstringbyid) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & id) <br> |
|  void | [**LoadLocalizationStrings**](#function-loadlocalizationstrings) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & filePath) <br> |
|   | [**LocalizationFile**](#function-localizationfile-12) () = default<br> |
|   | [**LocalizationFile**](#function-localizationfile-22) (const std::unordered\_map&lt; Locale, [**Path**](classSR__UTILS__NS_1_1Path.md) &gt; & localePaths, const Locale & languageToLoad) <br> |
|  void | [**SwitchFileByLocale**](#function-switchfilebylocale) (const Locale & newLocale) <br> |
|   | [**~LocalizationFile**](#function-localizationfile) () <br> |




























## Public Functions Documentation




### function GetStringById 

```C++
SR_HTYPES_NS::UnicodeString SR_UTILS_NS::Localization::LocalizationFile::GetStringById (
    const StringAtom & id
) 
```




<hr>



### function LoadLocalizationStrings 

```C++
void SR_UTILS_NS::Localization::LocalizationFile::LoadLocalizationStrings (
    const Path & filePath
) 
```




<hr>



### function LocalizationFile [1/2]

```C++
SR_UTILS_NS::Localization::LocalizationFile::LocalizationFile () = default
```




<hr>



### function LocalizationFile [2/2]

```C++
SR_UTILS_NS::Localization::LocalizationFile::LocalizationFile (
    const std::unordered_map< Locale, Path > & localePaths,
    const Locale & languageToLoad
) 
```




<hr>



### function SwitchFileByLocale 

```C++
void SR_UTILS_NS::Localization::LocalizationFile::SwitchFileByLocale (
    const Locale & newLocale
) 
```




<hr>



### function ~LocalizationFile 

```C++
SR_UTILS_NS::Localization::LocalizationFile::~LocalizationFile () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Localization/LocalizationManager.h`

