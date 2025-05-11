

# Namespace SR\_PLATFORM\_NS



[**Namespace List**](namespaces.md) **>** [**SR\_PLATFORM\_NS**](namespaceSR__PLATFORM__NS.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| enum uint8\_t | [**MessageBoxDefaultButtonType**](#enum-messageboxdefaultbuttontype)  <br> |
| enum uint8\_t | [**MessageBoxIconType**](#enum-messageboxicontype)  <br> |
| enum uint8\_t | [**MessageBoxResultType**](#enum-messageboxresulttype)  <br> |
| enum uint8\_t | [**MessageBoxType**](#enum-messageboxtype)  <br> |






## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  std::map&lt; KeySym, uint8\_t &gt; | [**keysymToIndex**](#variable-keysymtoindex)  <br>_Fortunately, there are things like Copilot to generate this kind of stuff..._  |














## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_COMMON\_DLL\_API MessageBoxResultType | [**ShowMessageBox**](#function-showmessagebox) (const std::string\_view & title, const std::string\_view & message, MessageBoxType type, MessageBoxIconType iconType, MessageBoxDefaultButtonType defaultButtonType) <br> |




























## Public Types Documentation




### enum MessageBoxDefaultButtonType 

```C++
enum SR_PLATFORM_NS::MessageBoxDefaultButtonType {
    YesOk,
    No,
    Cancel
};
```




<hr>



### enum MessageBoxIconType 

```C++
enum SR_PLATFORM_NS::MessageBoxIconType {
    Info,
    Warning,
    Error,
    Question
};
```




<hr>



### enum MessageBoxResultType 

```C++
enum SR_PLATFORM_NS::MessageBoxResultType {
    YesOk = 0,
    No = 1,
    Cancel = 2
};
```




<hr>



### enum MessageBoxType 

```C++
enum SR_PLATFORM_NS::MessageBoxType {
    Ok,
    OkCancel,
    YesNo,
    YesNoCancel
};
```




<hr>
## Public Static Attributes Documentation




### variable keysymToIndex 

_Fortunately, there are things like Copilot to generate this kind of stuff..._ 
```C++
std::map<KeySym, uint8_t> SR_PLATFORM_NS::keysymToIndex;
```




<hr>
## Public Functions Documentation




### function ShowMessageBox 

```C++
SR_COMMON_DLL_API MessageBoxResultType SR_PLATFORM_NS::ShowMessageBox (
    const std::string_view & title,
    const std::string_view & message,
    MessageBoxType type,
    MessageBoxIconType iconType,
    MessageBoxDefaultButtonType defaultButtonType
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Platform/MessageBox.h`

