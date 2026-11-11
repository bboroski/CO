<p align="center"><img src="assets/duck-ui/duck-mark.svg" alt="CO mark" width="92"></p>
<h1 align="center">CO</h1>
<p align="center"><strong>Deterministic Component Lifecycle Runtime</strong></p>
<p align="center"><strong>Host-tested ядро C11</strong></p>
<p align="center"><a href="README.md">🇺🇦 Українська</a> · <a href="README.en.md">🇬🇧 English</a> · <a href="README.ru.md">🇷🇺 Русский</a></p>

> **CO** — CO — компактный runtime на C11 для предсказуемого запуска, пошагового выполнения и завершения компонентов без полноценной RTOS.

## Текущие возможности
- Явные состояния STOPPED, STARTING, RUNNING, STEPPING, FAULTED и STOPPING.
- Runtime хранится в памяти вызывающей стороны; heap не используется.
- Callbacks init, step и shutdown с передачей ошибок.
- Защита от рекурсии и host-тесты ошибок и частичной инициализации.

## Быстрый старт и проверка
```bash
make test
make clean
python one.py check
```

## Архитектура и подтверждённые границы
CO не реализует preemption, interrupt scheduler или MMIO. Вызывающая сторона сериализует доступ из независимых контекстов; scheduling, priorities, deadlines и watchdog остаются внешними.

## Инженерное качество
- Запускайте проверки для целевой платформы; host CI не заменяет аппаратную квалификацию.
- Статусы implemented, partial и planned должны подтверждаться кодом, тестами и доказательствами.
- Макет, спецификация или открытый Pull Request не доказывают production-ready реализацию.
- Внешние интеграции должны быть явными, версионированными, изолированными и тестируемыми.

## NUN Mesh и связанные репозитории
[SAMBU](https://github.com/bboroski/SAMBU) · [ToolNG](https://github.com/bboroski/ToolNG) · [ReaperCripple](https://github.com/bboroski/ReaperCripple) · [Kloz](https://github.com/bboroski/Kloz) · [CO](https://github.com/bboroski/CO) · [SaintSI](https://github.com/bboroski/SaintSI) · [Klipot](https://github.com/bboroski/Klipot) · [NUN](https://github.com/bboroski/NUN) · [NUNLauncher](https://github.com/bboroski/NUNLauncher) · [Fragile-Baby](https://github.com/bboroski/Fragile-Baby) · [Luci](https://github.com/bboroski/Luci)

Каждый репозиторий сохраняет каноническое имя, собственный код, API, цикл выпуска и границы ответственности. Интеграция означает версионированные контракты, а не автоматическое слияние независимых runtime.

## Дизайн и документация
Общее направление интерфейсов — **Duck Black / Yellow**: тёмные поверхности, жёлтые акценты для действий и состояний, читаемая типографика, доступный контраст, клавиатурная навигация и поддержка reduced motion. Подробности — в [design/DUCK_UI_SYSTEM.md](design/DUCK_UI_SYSTEM.md), если файл присутствует.

## Лицензия
Лицензия не объявлена; файл LICENSE отсутствует.

---
**Создано с любовью к инженерии, системности и людям.**
