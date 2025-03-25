Архитектура работы C++ скриптов

python script создает metadata (generated.hpp) для компиляции
скрипт реагирует на @property, @virtualProperty и @function у SR_CLASS

Есть менеджер всей системы, который знает какие библиотеки загружены (dll, so, static)

Есть тег @dontScript, который запрещает видеть класс/поле/метод в скриптах 



Он предоставляет интерфейс:
- AllocateState(string: name) - создает экземпляр обертки над каким-то SR_CLASS


пример для не SR_CLASS

// @class
class Vector3 {
    
};


