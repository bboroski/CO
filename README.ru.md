<p align="center"><img src="assets/duck-ui/duck-mark.svg" alt="CO mark" width="92"></p>
<h1 align="center">CO</h1>
<p align="center"><strong>Deterministic Component Lifecycle Runtime</strong></p>
<p align="center"><img src="https://img.shields.io/badge/STATUS-HOST%20TESTED%20CORE-FFD600?style=for-the-badge&labelColor=111111"><img src="https://img.shields.io/badge/CORE-C11-FFD600?style=for-the-badge&labelColor=111111"><img src="https://img.shields.io/badge/LICENSE-NOT%20DECLARED-FFD600?style=for-the-badge&labelColor=111111"></p>
<p align="center"><a href="README.md">🇺🇦 Українська</a> · <a href="README.en.md">🇬🇧 English</a> · <a href="README.ru.md">🇷🇺 Русский</a></p>

---

**CO — компактный runtime C11 для предсказуемого запуска, пошагового выполнения и завершения компонентов.** Он задаёт явный жизненный цикл без необходимости в полноценной RTOS и оставляет владение памятью и контекстом выполнения вызывающей стороне.

## Реализованные функции

- Явная машина состояний, включая защищённое состояние <code>STEPPING</code>.
- Runtime-объект в памяти, предоставленной вызывающей стороной; heap не используется.
- Callback-интерфейсы <code>init</code>, <code>step</code> и <code>shutdown</code>.
- Передача ошибок callbacks и сохранение последнего результата.
- Насыщающий счётчик циклов выполнения.
- Отклонение рекурсивных вызовов <code>poll</code>/<code>stop</code> во время callback.
- Host-тесты запуска, ошибок, частичной инициализации и защиты от повторного входа.

## Модель состояний

~~~text
STOPPED -> STARTING -> RUNNING -> STEPPING -> RUNNING
              |          |          |
              +--------> FAULTED <---+
FAULTED -> STOPPING -> STOPPED
RUNNING -> STOPPING -> STOPPED
~~~

Callback завершения вызывается после попытки инициализации, в том числе при частичной ошибке, поэтому обязан корректно обрабатывать неполную настройку.

## Сборка и проверка

Требуются компилятор C11 и Make.

~~~sh
make test
make clean
python one.py check
~~~

GitHub Actions запускает host-тесты с GCC и Clang.

## Управление и критерии выпуска

| Контроль | Правило |
|---|---|
| Память | Runtime использует память, предоставленную вызывающей стороной |
| Жизненный цикл | Состояния и ошибки явные |
| Callback safety | Рекурсивные poll/stop отклоняются |
| Host CI | Проверки GCC и Clang должны проходить |
| Интеграция | Вызывающая сторона сериализует доступ из независимых контекстов |

## Границы ответственности

CO не владеет allocator и не создаёт heap; он не реализует preemption, interrupt scheduler или доступ к MMIO. Вызывающая сторона сериализует доступ из независимых контекстов. Политика планирования, приоритеты, deadlines и watchdog относятся к отдельным модулям. Канонический API использует префикс <code>co_</code>; старый заголовок <code>co/runtime.h</code> предоставляет source-level aliases.

Документация: [модель выполнения](docs/execution-model.md).

## Экосистема и лицензия

Связанные проекты: [SAMBU](https://github.com/bboroski/SAMBU), [ToolNG](https://github.com/bboroski/ToolNG), [ReaperCripple](https://github.com/bboroski/ReaperCripple), [Kloz](https://github.com/bboroski/Kloz), [SaintSI](https://github.com/bboroski/SaintSI), [Klipot](https://github.com/bboroski/Klipot), [NUN](https://github.com/bboroski/NUN) и [NUNLauncher](https://github.com/bboroski/NUNLauncher).

**Лицензия не объявлена:** файл <code>LICENSE</code> отсутствует. До распространения необходимо определить условия и добавить полный текст лицензии.

---

**Создано с любовью к предсказуемому коду и людям.**

## Продуктовая система

Единые правила дизайна Duck, трёхъязычной документации, управления возможностями, маркетинговых заявлений и выпусков: [docs/PRODUCT_SYSTEM.md](docs/PRODUCT_SYSTEM.md). Реестр на 10 000 ID — это ёмкость планирования, а не заявление о 10 000 готовых функциях.
