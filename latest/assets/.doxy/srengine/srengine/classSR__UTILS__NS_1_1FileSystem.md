

# Class SR\_UTILS\_NS::FileSystem



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**FileSystem**](classSR__UTILS__NS_1_1FileSystem.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**FileSystem**](#function-filesystem) () = delete<br> |
|   | [**~FileSystem**](#function-filesystem) () = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  bool | [**CreatePath**](#function-createpath) (std::string path, uint32\_t offset=0) <br> |
|  const char \* | [**FileMapView**](#function-filemapview) (std::string path) <br> |
|  void | [**ForEachFileInFolder**](#function-foreachfileinfolder) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & path, bool recursive, const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(const [**Path**](classSR__UTILS__NS_1_1Path.md) &)&gt; & func) <br> |
|  uint64\_t | [**GetExecutableAndModulesHash**](#function-getexecutableandmoduleshash) () <br> |
|  uint64\_t | [**GetFileHash**](#function-getfilehash) (const std::string & path) <br> |
|  uint64\_t | [**GetFolderHash**](#function-getfolderhash) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & path, uint64\_t deep=SR\_UINT64\_MAX) <br> |
|  char \* | [**Load**](#function-load) (std::string path) <br> |
|  std::string | [**NormalizePath**](#function-normalizepath) (const std::string & path) <br> |
|  std::vector&lt; std::string &gt; | [**ReadAllLines**](#function-readalllines) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  std::string | [**ReadAllText**](#function-readalltext) (const std::string & path) <br> |
|  std::vector&lt; char &gt; | [**ReadBinary**](#function-readbinary) (std::string\_view path) <br> |
|  std::string | [**ReadBinaryAsString**](#function-readbinaryasstring) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & path, bool checkError=true) <br> |
|  std::shared\_ptr&lt; std::vector&lt; uint8\_t &gt; &gt; | [**ReadFileAsBlob**](#function-readfileasblob) (const std::string & path) <br> |
|  std::vector&lt; uint8\_t &gt; | [**ReadFileAsVector**](#function-readfileasvector) (const std::string & path) <br> |
|  uint64\_t | [**ReadHashFromFile**](#function-readhashfromfile) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  void | [**UnmapFile**](#function-unmapfile) (const char \* str) <br> |
|  bool | [**WriteHashToFile**](#function-writehashtofile) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path, uint64\_t hash) <br> |
|  bool | [**WriteToFile**](#function-writetofile) (const std::string & path, const std::string & text) <br> |


























## Public Functions Documentation




### function FileSystem 

```C++
SR_UTILS_NS::FileSystem::FileSystem () = delete
```




<hr>



### function ~FileSystem 

```C++
SR_UTILS_NS::FileSystem::~FileSystem () = delete
```




<hr>
## Public Static Functions Documentation




### function CreatePath 

```C++
static bool SR_UTILS_NS::FileSystem::CreatePath (
    std::string path,
    uint32_t offset=0
) 
```




<hr>



### function FileMapView 

```C++
static const char * SR_UTILS_NS::FileSystem::FileMapView (
    std::string path
) 
```




<hr>



### function ForEachFileInFolder 

```C++
static void SR_UTILS_NS::FileSystem::ForEachFileInFolder (
    const Path & path,
    bool recursive,
    const SR_HTYPES_NS::Function < void(const Path &)> & func
) 
```




<hr>



### function GetExecutableAndModulesHash 

```C++
static uint64_t SR_UTILS_NS::FileSystem::GetExecutableAndModulesHash () 
```




<hr>



### function GetFileHash 

```C++
static uint64_t SR_UTILS_NS::FileSystem::GetFileHash (
    const std::string & path
) 
```




<hr>



### function GetFolderHash 

```C++
static uint64_t SR_UTILS_NS::FileSystem::GetFolderHash (
    const Path & path,
    uint64_t deep=SR_UINT64_MAX
) 
```




<hr>



### function Load 

```C++
static char * SR_UTILS_NS::FileSystem::Load (
    std::string path
) 
```




<hr>



### function NormalizePath 

```C++
static std::string SR_UTILS_NS::FileSystem::NormalizePath (
    const std::string & path
) 
```




<hr>



### function ReadAllLines 

```C++
static std::vector< std::string > SR_UTILS_NS::FileSystem::ReadAllLines (
    const SR_UTILS_NS::Path & path
) 
```




<hr>



### function ReadAllText 

```C++
static std::string SR_UTILS_NS::FileSystem::ReadAllText (
    const std::string & path
) 
```




<hr>



### function ReadBinary 

```C++
static std::vector< char > SR_UTILS_NS::FileSystem::ReadBinary (
    std::string_view path
) 
```




<hr>



### function ReadBinaryAsString 

```C++
static std::string SR_UTILS_NS::FileSystem::ReadBinaryAsString (
    const Path & path,
    bool checkError=true
) 
```




<hr>



### function ReadFileAsBlob 

```C++
static std::shared_ptr< std::vector< uint8_t > > SR_UTILS_NS::FileSystem::ReadFileAsBlob (
    const std::string & path
) 
```




<hr>



### function ReadFileAsVector 

```C++
static std::vector< uint8_t > SR_UTILS_NS::FileSystem::ReadFileAsVector (
    const std::string & path
) 
```




<hr>



### function ReadHashFromFile 

```C++
static uint64_t SR_UTILS_NS::FileSystem::ReadHashFromFile (
    const SR_UTILS_NS::Path & path
) 
```




<hr>



### function UnmapFile 

```C++
static void SR_UTILS_NS::FileSystem::UnmapFile (
    const char * str
) 
```




<hr>



### function WriteHashToFile 

```C++
static bool SR_UTILS_NS::FileSystem::WriteHashToFile (
    const SR_UTILS_NS::Path & path,
    uint64_t hash
) 
```




<hr>



### function WriteToFile 

```C++
static bool SR_UTILS_NS::FileSystem::WriteToFile (
    const std::string & path,
    const std::string & text
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/FileSystem/FileSystem.h`

