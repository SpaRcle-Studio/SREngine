# Игровые проекты, сцены и скрипты

Примеры: `C:\Work\SREngineProjects\DeathLovers` (новелла, UI), `C:\Work\SREngineProjects\Voidworks` (планета: террейн-сфера, гравитация, игрок на AngelScript).

## Принцип

Движок остаётся движком: под игру в движке ничего не «подпирать». Нужна возможность — делается общий инструмент движка (компонент, свойство, `@method` для скриптов, параметр шейдера), а игровая логика и данные лежат в проекте: скрипты `.as`, шейдеры `.srsl`, сцены, префабы. Пример: `Terrain::m_shape = Sphere` + `GravityField` — движок, `PlanetDensity.srsl` + `PlanetPlayer.as` + `Planet.scene` — игра.

## Проект

```
<Project>/
  .srproject              ProjectSettings (sra): projectName, mainScene, packages, enableCppScripts, buildExcludedPaths, buildProfiles
  Resources/
    as.predefined         генерируется движком (объявления API для скриптов), руками не править
    <Project>/Scenes/...  ресурсы игры - в подпапке с именем проекта
    <Project>/Scripts/...
    <Project>/Shaders/...
```

- Запуск: путь к `.srproject` аргументом командной строки (`CLIManager`: аргумент, оканчивающийся на `.srproject`). `Resources` проекта монтируется в VFS поверх ресурсов движка (приоритет 100 против 0, движок — только чтение), поэтому пути ресурсов единые: `Engine/Shaders/...` из движка, `Voidworks/Scenes/...` из проекта. Своё имя-подпапка — чтобы не перекрыть файлы движка.
- Минимальный `.srproject` — см. `Voidworks/.srproject`. `mainScene` — путь относительно `Resources`. Без C++ скриптов `enableCppScripts: false`.

## Сцены и префабы (sra)

- Текстовый формат `sra format`, табы. Строки: `-o:` объект, `-v:` значение, `-a:` массив, `-k:i` элемент массива, типы значений `-s:` строка, `-i:` int, `-f:` float, `-b:` bool. Объект сцены: `-v:type -s:GameObject`, `-o:ptr` с `entityId`, `-a:components`, `name`, `-a:children`, `-o:transform` (`Transform3D`, только отличные от умолчания поля). Компонент: `-v:type -s:<Класс>`, `-o:ptr` с `entityId` и `@property` полями (имя = serializeName, без `m_`).
- Сохраняются только свойства, отличные от значения по умолчанию. Новое свойство с умолчанием в файле не появится — это нормально.
- Ссылки между объектами — по `entityId` (int64). При ручном добавлении объекта нужен уникальный `entityId`; ссылки на него (`EntityRef`) — тем же числом.
- Сцену пользователь может держать открытой в редакторе и пересохранять: перед ручной правкой файла перечитай его, правь точечно (Edit), не переписывай целиком. Если пользователь сказал, что правил сцену, — свежая версия на диске важнее того, что помнишь.
- Создание объектов движка в редакторе: ПКМ в иерархии (например World → Terrain берёт префаб `Engine/Prefabs/Terrain.prefab` с настройками по умолчанию).
- Объекты, порождаемые в рантайме (пулы чанков и т.п.), не должны сохраняться со сценой: `SceneObject::SetChildrenTransient(true)` на родителе.

## Скрипты AngelScript

- Любой `.as` в `Resources` (кроме кеша) подхватывается и перекомпилируется на лету (`ScriptSystem::HandleFileEvent`). Класс поведения: `class Name : ScriptBehaviour`; на объекте — компонент `Behaviour` с `behaviourName` = имя класса. Доступны поля `gameObject`, `sceneObject`, `transform`.
- Колбэки (точные сигнатуры, иначе не вызовутся — `AngelScriptBehaviourInstance::CacheCallbacks`): `void Awake()`, `void Start()`, `void OnEnable()`, `void OnDisable()`, `void OnAttached()`, `void OnDetached()`, `void OnDestroy()`, `void FixedUpdate()`, `void Update(float dt)`, `bool ExecuteInEditMode() const`, `OnCollision/OnTrigger Enter/Stay/Exit(ScriptCollisionData@)` (или без аргумента).
- Поля класса сериализуются в сцену в `-o:data` компонента `Behaviour` (в том числе приватные). Ссылка на объект сцены — поле `EntityRef<GameObject> name;`, в скрипте `name.get()`; в сцене — `entityId` объекта.
- Компоненты: `cast<CharacterController@>(gameObject.GetComponent("CharacterController"))`. Синглтоны: `Input::Instance()`, `Time::Instance()`, `MathUtils::Instance()`.
- Перед использованием API смотри `Resources/as.predefined` проекта (генерирует движок при запуске). Чего там нет — нет в скриптах. C++ метод становится доступен после тега `/// @method` (см. Codegen.md) и пересборки движка; затем `as.predefined` обновится сам.
- Ограничения: у `FVector3`/`Quaternion` в скриптах нет операторов — арифметика вручную через `MathUtils::MakeFVector3` и хелперы в классе (см. `Voidworks/Scripts/PlanetPlayer.as`). Возврат по значению предпочтительнее ссылок на временные объекты в биндингах.

## Шейдеры проекта

- `.srsl` проекта подключаются свойствами компонентов (например `densityShader` у генератора террейна) путём относительно `Resources`. Общие include движка — `#include <Engine/Shaders/...>`.
- Параметры из игры без правок движка: `TerrainChunkDataMarchingCubesGenerator::m_densityParameters` (имя → vec4 uniform). Ошибки компиляции — в логе (`%LOCALAPPDATA%\SpaRcle-Studio\SREngine\Logs\srengine.log`); после смены сигнатуры функции ищи все вызовы — старый вызов в шейдере ломает всю компиляцию.

## Редактор и игровой режим

- Компоненты, работающие без Play (`ExecuteInEditMode() → true`), должны брать камеру наблюдателя как `Terrain::GetObserver`: в режиме редактора — `RenderScene::GetMainCamera()` (редакторная), иначе `RenderScene::GetGameCamera()`.
- В редакторе физика стоит на паузе, а компоненты включаются/выключаются — `OnDisable`+`OnDestroy` подряд не должны дважды удалять объект из физики (см. Physics.md).
