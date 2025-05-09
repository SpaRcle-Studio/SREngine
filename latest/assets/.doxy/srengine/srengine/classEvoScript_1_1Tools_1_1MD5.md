

# Class EvoScript::Tools::MD5



[**ClassList**](annotated.md) **>** [**EvoScript**](namespaceEvoScript.md) **>** [**Tools**](namespaceEvoScript_1_1Tools.md) **>** [**MD5**](classEvoScript_1_1Tools_1_1MD5.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  char | [**digestChars**](#variable-digestchars)  <br> |
|  MD5\_BYTE | [**digestRaw**](#variable-digestraw)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD std::string | [**DigestFile**](#function-digestfile) (char \* filename) <br>_Load a file from disk and digest it._  |
|  SR\_NODISCARD std::string | [**DigestMemory**](#function-digestmemory) (MD5\_BYTE \* memchunk, int len) <br>_Digests a byte-array already in memory._  |
|  SR\_NODISCARD std::string | [**DigestString**](#function-digeststring) (char \* string) <br> |
|  void | [**Final**](#function-final) () <br> |
|  void | [**Init**](#function-init) () <br> |
|   | [**MD5**](#function-md5) () <br> |
|  SR\_NODISCARD std::string | [**TryDigestFile**](#function-trydigestfile) (char \* filename) <br> |
|  void | [**Update**](#function-update) (unsigned char \* input, unsigned int inputLen) <br> |
|  void | [**writeToString**](#function-writetostring) () <br>_Buffer must be 32+1 (nul) = 33 chars long at least._  |




























## Public Attributes Documentation




### variable digestChars 

```C++
char EvoScript::Tools::MD5::digestChars[33];
```




<hr>



### variable digestRaw 

```C++
MD5_BYTE EvoScript::Tools::MD5::digestRaw[16];
```




<hr>
## Public Functions Documentation




### function DigestFile 

_Load a file from disk and digest it._ 
```C++
inline SR_NODISCARD std::string EvoScript::Tools::MD5::DigestFile (
    char * filename
) 
```




<hr>



### function DigestMemory 

_Digests a byte-array already in memory._ 
```C++
inline SR_NODISCARD std::string EvoScript::Tools::MD5::DigestMemory (
    MD5_BYTE * memchunk,
    int len
) 
```




<hr>



### function DigestString 

```C++
inline SR_NODISCARD std::string EvoScript::Tools::MD5::DigestString (
    char * string
) 
```




<hr>



### function Final 

```C++
inline void EvoScript::Tools::MD5::Final () 
```




<hr>



### function Init 

```C++
inline void EvoScript::Tools::MD5::Init () 
```




<hr>



### function MD5 

```C++
inline EvoScript::Tools::MD5::MD5 () 
```




<hr>



### function TryDigestFile 

```C++
inline SR_NODISCARD std::string EvoScript::Tools::MD5::TryDigestFile (
    char * filename
) 
```




<hr>



### function Update 

```C++
inline void EvoScript::Tools::MD5::Update (
    unsigned char * input,
    unsigned int inputLen
) 
```




<hr>



### function writeToString 

_Buffer must be 32+1 (nul) = 33 chars long at least._ 
```C++
inline void EvoScript::Tools::MD5::writeToString () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Scripting/inc/Scripting/Old/Tools/MD5Hash.h`

