<!-- Title: CO — deterministic allocation-free C11 component lifecycle runtime -->
<p align="center"><img src="assets/duck-ui/duck-mark.svg" alt="Логотип CO" width="76"></p>

# CO

> **Visual identity:** Duck Black / Yellow — accent `#FFD600`, primary ink `#111111`.

[![Host tests](https://github.com/bboroski/CO/actions/workflows/c11-host-tests.yml/badge.svg?branch=main)](https://github.com/bboroski/CO/actions/workflows/c11-host-tests.yml)

**CO** — компактний allocation-free C11 runtime для контрольованої ініціалізації, покрокового виконання та завершення компонентів без вимоги повноцінної RTOS.

<sub>Оновлено: 2026-11-11 · Мова: C11 · Версію релізу не визначено</sub>

> **TL;DR:** виконайте **make test**; runtime працює з пам'яттю, яку надає викликач, і передає помилки через callback API. Планування потоків залишається відповідальністю застосунку.

[Українська](README.md) · [English](README.en.md) · [Русский](README.ru.md)

## Зміст

- [Призначення](#призначення)
- [Можливості](#можливості)
- [Вимоги та перевірка](#вимоги-та-перевірка)
- [Модель життєвого циклу](#модель-життєвого-циклу)
- [Обмеження та безпека](#обмеження-та-безпека)
- [Документація та інтеграції](#документація-та-інтеграції)
- [FAQ](#faq)
- [Підтримка та ліцензія](#підтримка-та-ліцензія)

## Призначення

CO стандартизує життєвий цикл окремого компонента всередині host application або embedded-програми. Він не запускає потоки й не визначає, коли scheduler має викликати компонент.

## Можливості

- Явні стани STOPPED, STARTING, RUNNING, STEPPING, FAULTED і STOPPING.
- Runtime storage, наданий викликачем; приховані heap allocations відсутні.
- Callback-и init, step і shutdown з передаванням статусу помилки.
- Захист від рекурсивних poll/stop під час callback.
- Тестування успішного запуску, fault paths, часткової ініціалізації та recursion guards.

## Вимоги та перевірка

Потрібні Make та C11-компілятор GCC або Clang. Компіляція вимагає -Wall -Wextra -Werror -pedantic.

~~~bash
make test
make clean
python one.py check
~~~

Тимчасові тестові бінарні файли зберігаються в .build/; make clean видаляє їх.

## Модель життєвого циклу

Застосунок передає callbacks ініціалізації, одного кроку роботи та завершення. CO зберігає стан і повертає помилки викликачеві; після невдалої або часткової ініціалізації застосунок має обробити результат згідно зі своєю політикою.

Докладніше: [execution model](docs/execution-model.md), [signal pipeline lifecycle](docs/SIGNAL_PIPELINE_LIFECYCLE.md) та [runtime archetype mapping](docs/ARCHETYPE_RUNTIME_MAPPING.md). Публічні заголовки: [include/co](include/co); тести: [tests](tests).

## Обмеження та безпека

- CO не є RTOS, scheduler потоків або interrupt scheduler.
- Runtime не виконує preemption, MMIO, драйверні операції чи watchdog policy.
- Застосунок повинен серіалізувати доступ із незалежних execution contexts.
- Не передавайте керування callback-ам, які повторно викликають poll/stop того самого runtime.
- Host-тести не вимірюють target timing або реальні hardware deadlines.

## Документація та інтеграції

- [C11 host tests](.github/workflows/c11-host-tests.yml)
- [module manifest](sambu.module.json)
- [Kloz](https://github.com/bboroski/Kloz) — optional platform services; [SaintSI](https://github.com/bboroski/SaintSI) — optional heartbeat/integrity observation; [ReaperCripple](https://github.com/bboroski/ReaperCripple) — embedded manufacturing and lifecycle integration.

## FAQ

**Чи створює CO окремий thread?** Ні. Викликач керує моментом і контекстом виклику.

**Чи потрібен Kloz?** Ні. Інтеграція через platform context є optional; ядро CO тестується окремо.

## Підтримка та ліцензія

Баги: [Issue tracker](https://github.com/bboroski/CO/issues) · [bug report](https://github.com/bboroski/CO/issues/new). У PR додайте тест для відповідного стану або помилкового сценарію, а також короткий опис API-впливу. Профіль супроводу: [bboroski](https://github.com/bboroski).

**Ліцензія не оголошена:** файл LICENSE у репозиторії відсутній. Узгодьте умови використання з правовласником до зовнішнього розповсюдження.
