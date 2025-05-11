

# Namespace s\_s



[**Namespace List**](namespaces.md) **>** [**s\_s**](namespaces__s.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef unsigned char | [**uchar**](#typedef-uchar)  <br> |
| typedef unsigned long long | [**ullong**](#typedef-ullong)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  const uchar | [**MAX\_LEN**](#variable-max_len)   = `9`<br> |
|  const ullong | [**N\_HASH**](#variable-n_hash)   = `static\_cast&lt;ullong&gt;(-1)`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  constexpr ullong | [**raise\_128\_to**](#function-raise_128_to) (const uchar power) <br> |
|  constexpr ullong | [**str\_hash**](#function-str_hash) (const char \*const str, const uchar current\_len) <br> |
|  ullong | [**str\_hash\_for\_switch**](#function-str_hash_for_switch) (const char \*const str) <br> |
|  ullong | [**str\_hash\_for\_switch**](#function-str_hash_for_switch) (const std::string & str) <br> |
|  constexpr bool | [**str\_is\_correct**](#function-str_is_correct) (const char \*const str) <br> |
|  constexpr uchar | [**str\_len**](#function-str_len) (const char \*const str) <br> |




























## Public Types Documentation




### typedef uchar 

```C++
typedef unsigned char s_s::uchar;
```




<hr>



### typedef ullong 

```C++
typedef unsigned long long s_s::ullong;
```




<hr>
## Public Attributes Documentation




### variable MAX\_LEN 

```C++
const uchar s_s::MAX_LEN;
```




<hr>



### variable N\_HASH 

```C++
const ullong s_s::N_HASH;
```




<hr>
## Public Functions Documentation




### function raise\_128\_to 

```C++
constexpr ullong s_s::raise_128_to (
    const uchar power
) 
```




<hr>



### function str\_hash 

```C++
constexpr ullong s_s::str_hash (
    const char *const str,
    const uchar current_len
) 
```




<hr>



### function str\_hash\_for\_switch 

```C++
inline ullong s_s::str_hash_for_switch (
    const char *const str
) 
```




<hr>



### function str\_hash\_for\_switch 

```C++
inline ullong s_s::str_hash_for_switch (
    const std::string & str
) 
```




<hr>



### function str\_is\_correct 

```C++
constexpr bool s_s::str_is_correct (
    const char *const str
) 
```




<hr>



### function str\_len 

```C++
constexpr uchar s_s::str_len (
    const char *const str
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Common/str_switch.h`

