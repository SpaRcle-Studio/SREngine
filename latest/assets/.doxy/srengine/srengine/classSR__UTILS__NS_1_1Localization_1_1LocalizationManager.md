

# Class SR\_UTILS\_NS::Localization::LocalizationManager



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Localization**](namespaceSR__UTILS__NS_1_1Localization.md) **>** [**LocalizationManager**](classSR__UTILS__NS_1_1Localization_1_1LocalizationManager.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**AddLocFileIntoGroup**](#function-addlocfileintogroup) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & fileId, const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & groupId) <br> |
|  void | [**ChangeLocGroupLocale**](#function-changelocgrouplocale) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & id, const Locale & newLocale) <br> |
|  std::vector&lt; [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; | [**GetLocGroupsIds**](#function-getlocgroupsids) () <br> |
|  void | [**LoadInfoAsConfigFile**](#function-loadinfoasconfigfile) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & filePath) <br> |
|  [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**MakeLocFile**](#function-makelocfile) (const std::unordered\_map&lt; Locale, [**Path**](classSR__UTILS__NS_1_1Path.md) &gt; & localePaths, const Locale & languageToLoad, [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) fileId) <br>_using LocalizedTextComponent = SR\_GTYPES\_NS::ITextComponent\*;_  |
|  void | [**MakeLocGroup**](#function-makelocgroup) (std::unordered\_map&lt; [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md), [**LocalizationFile**](classSR__UTILS__NS_1_1Localization_1_1LocalizationFile.md) &gt; & locFiles, const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & groupId) <br> |
|  void | [**RegisterLocGroup**](#function-registerlocgroup) (const std::vector&lt; [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; & locFileIds, const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & groupId) <br> |
|  void | [**RemoveLocFileFromGroup**](#function-removelocfilefromgroup) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & fileId, const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & groupId) <br> |
|  void | [**RemoveLocGroup**](#function-removelocgroup) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & groupId) <br> |
|  void | [**SaveInfoAsConfigFile**](#function-saveinfoasconfigfile) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & filePath) <br> |




























## Public Functions Documentation




### function AddLocFileIntoGroup 

```C++
void SR_UTILS_NS::Localization::LocalizationManager::AddLocFileIntoGroup (
    const StringAtom & fileId,
    const StringAtom & groupId
) 
```




<hr>



### function ChangeLocGroupLocale 

```C++
void SR_UTILS_NS::Localization::LocalizationManager::ChangeLocGroupLocale (
    const StringAtom & id,
    const Locale & newLocale
) 
```




<hr>



### function GetLocGroupsIds 

```C++
std::vector< StringAtom > SR_UTILS_NS::Localization::LocalizationManager::GetLocGroupsIds () 
```




<hr>



### function LoadInfoAsConfigFile 

```C++
void SR_UTILS_NS::Localization::LocalizationManager::LoadInfoAsConfigFile (
    const SR_UTILS_NS::Path & filePath
) 
```




<hr>



### function MakeLocFile 

_using LocalizedTextComponent = SR\_GTYPES\_NS::ITextComponent\*;_ 
```C++
StringAtom SR_UTILS_NS::Localization::LocalizationManager::MakeLocFile (
    const std::unordered_map< Locale, Path > & localePaths,
    const Locale & languageToLoad,
    StringAtom fileId
) 
```



void RegisterTextComponent(std::string& id, SR\_GTYPES\_NS::ITextComponent\* textComponent); 


        

<hr>



### function MakeLocGroup 

```C++
void SR_UTILS_NS::Localization::LocalizationManager::MakeLocGroup (
    std::unordered_map< StringAtom , LocalizationFile > & locFiles,
    const StringAtom & groupId
) 
```




<hr>



### function RegisterLocGroup 

```C++
void SR_UTILS_NS::Localization::LocalizationManager::RegisterLocGroup (
    const std::vector< StringAtom > & locFileIds,
    const StringAtom & groupId
) 
```




<hr>



### function RemoveLocFileFromGroup 

```C++
void SR_UTILS_NS::Localization::LocalizationManager::RemoveLocFileFromGroup (
    const StringAtom & fileId,
    const StringAtom & groupId
) 
```




<hr>



### function RemoveLocGroup 

```C++
void SR_UTILS_NS::Localization::LocalizationManager::RemoveLocGroup (
    const StringAtom & groupId
) 
```




<hr>



### function SaveInfoAsConfigFile 

```C++
void SR_UTILS_NS::Localization::LocalizationManager::SaveInfoAsConfigFile (
    const SR_UTILS_NS::Path & filePath
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Localization/LocalizationManager.h`

