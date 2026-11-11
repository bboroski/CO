<p align="center"><img src="assets/duck-ui/duck-mark.svg" alt="CO mark" width="92"></p>
<h1 align="center">CO</h1>
<p align="center"><strong>Deterministic Component Lifecycle Runtime</strong></p>
<p align="center"><img src="https://img.shields.io/badge/STATUS-HOST%20TESTED%20CORE-FFD600?style=for-the-badge&labelColor=111111"><img src="https://img.shields.io/badge/CORE-C11-FFD600?style=for-the-badge&labelColor=111111"><img src="https://img.shields.io/badge/LICENSE-NOT%20DECLARED-FFD600?style=for-the-badge&labelColor=111111"></p>
<p align="center"><a href="README.md">🇺🇦 Українська</a> · <a href="README.en.md">🇬🇧 English</a> · <a href="README.ru.md">🇷🇺 Русский</a></p>


<p align="center"><sub><a href="design/DUCK_UI_SYSTEM.md">Duck Black / Yellow UI standard</a> · <a href="assets/duck-ui/duck-ui-preview.svg">Vector UI preview</a></sub></p>

**CO — компактний C11 runtime для передбачуваного запуску, виконання кроків і завершення компонентів.** Він надає явний життєвий цикл без вимоги повноцінної RTOS і залишає володіння пам'яттю та контекстом виконання викликачеві.

## Реалізовані функції

- Явна машина станів, включно із захищеним станом <code>STEPPING</code>.
- Runtime-об'єкт у пам'яті, наданій викликачем; heap не використовується.
- Callback-інтерфейси <code>init</code>, <code>step</code> і <code>shutdown</code>.
- Передавання помилок callbacks і збереження останнього результату.
- Насичувальний лічильник циклів виконання.
- Відхилення рекурсивних <code>poll</code>/<code>stop</code> під час callback.
- Host-тести старту, помилок, часткової ініціалізації та захисту від рекурсії.

## Модель станів

~~~text
STOPPED -> STARTING -> RUNNING -> STEPPING -> RUNNING
              |          |          |
              +--------> FAULTED <---+
FAULTED -> STOPPING -> STOPPED
RUNNING -> STOPPING -> STOPPED
~~~

Callback завершення викликається після спроби ініціалізації, зокрема після часткової невдачі, тому має коректно обробляти неповне налаштування.

## Збірка та перевірка

Потрібні C11-компілятор і Make.

~~~sh
make test
make clean
python one.py check
~~~

GitHub Actions запускає host-тести з GCC і Clang.

## Управління та критерії випуску

| Контроль | Правило |
|---|---|
| Пам'ять | Runtime використовує пам'ять, надану викликачем |
| Життєвий цикл | Стани та помилки є явними |
| Callback safety | Рекурсивні poll/stop відхиляються |
| Host CI | Перевірки GCC і Clang мають проходити |
| Інтеграція | Викликач серіалізує доступ між незалежними контекстами |

## Межі відповідальності

CO не володіє allocator і не створює heap; не реалізує preemption, interrupt scheduler або MMIO-доступ. Викликач серіалізує доступ із незалежних контекстів. Політика планування, пріоритети, deadlines і watchdog залишаються окремими модулями. Канонічний API використовує префікс <code>co_</code>; старий заголовок <code>co/runtime.h</code> надає source-level псевдоніми.

Документація: [модель виконання](docs/execution-model.md).

## Екосистема та ліцензія

Пов'язані проєкти: [SAMBU](https://github.com/bboroski/SAMBU), [ToolNG](https://github.com/bboroski/ToolNG), [ReaperCripple](https://github.com/bboroski/ReaperCripple), [Kloz](https://github.com/bboroski/Kloz), [SaintSI](https://github.com/bboroski/SaintSI), [Klipot](https://github.com/bboroski/Klipot), [NUN](https://github.com/bboroski/NUN) і [NUNLauncher](https://github.com/bboroski/NUNLauncher).

**Ліцензію не оголошено:** файл <code>LICENSE</code> відсутній. Визначте умови використання та додайте повний текст ліцензії перед розповсюдженням.

---

**Створено з любов'ю до передбачуваного коду та людей.**

## NUN Mesh

<p align="center"><img src="assets/nun-mesh.svg" alt="NUN Mesh — seven connected engineering repositories with versioned contracts" width="100%"></p>

CO надає NUN Mesh детермінований життєвий цикл компонентів. Він відповідає за порядок init/step/shutdown та прозорі стани помилок, але не замінює RTOS, scheduler або апаратний watchdog.

Адаптивний робочий простір і спільні UI-правила описані в [Adaptive Workspace Integration](docs/ADAPTIVE_WORKSPACE_INTEGRATION.md). Вони не додають цьому native-компоненту неіснуючий графічний runtime.

## Продуктова система та реєстр можливостей

Єдині правила дизайну Duck, тримовної документації, маркетингових заяв, пріоритетів, життєвого циклу функцій і випусків: [docs/PRODUCT_SYSTEM.md](docs/PRODUCT_SYSTEM.md). Каталог допускає до 10 000 ідентифікаторів можливостей; реалізованими вважаються лише функції з кодом, критеріями приймання та перевірними тестами.
