<p align="center"><img src="assets/duck-ui/duck-mark.svg" alt="CO mark" width="92"></p>
<h1 align="center">CO</h1>
<p align="center"><strong>Deterministic Component Lifecycle Runtime</strong></p>
<p align="center"><strong>Host-tested ядро C11</strong></p>
<p align="center"><a href="README.md">🇺🇦 Українська</a> · <a href="README.en.md">🇬🇧 English</a> · <a href="README.ru.md">🇷🇺 Русский</a></p>
<sub>Обновлено: 2026-11-11</sub>


## Навигация

- [Текущие возможности](#текущие-возможности)
- [Быстрый старт и проверка](#быстрый-старт-и-проверка)
- [Архитектура и подтверждённые границы](#архитектура-и-подтверждённые-границы)
- [Интерфейс и архитектурная визуализация](#интерфейс-и-архитектурная-визуализация)
- [Инженерное качество](#инженерное-качество)
- [Карта документации](#карта-документации)
- [NUN Mesh и связанные репозитории](#nun-mesh-и-связанные-репозитории)
- [Дизайн и документация](#дизайн-и-документация)
- [Лицензия](#лицензия)
- [Палитра Duck Black / Yellow](#палитра-duck-black-yellow)

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

## Интерфейс и архитектурная визуализация

CO — компактный runtime-компонент на C11 без графического интерфейса. Скриншотов GUI нет; ниже показаны карта экосистемы и общий стиль Duck UI, а не интерфейс CO.

<p align="center"><img src="assets/nun-mesh.svg" alt="Карта NUN Mesh: независимые компоненты и версионированные контракты" width="960"></p>
<p align="center"><em>Карта экосистемы</em></p>
<p align="center"><img src="assets/duck-ui/duck-ui-preview.svg" alt="Общий стиль Duck Black Yellow, не GUI CO" width="960"></p>

## Инженерное качество
- Запускайте проверки для целевой платформы; host CI не заменяет аппаратную квалификацию.
- Статусы implemented, partial и planned должны подтверждаться кодом, тестами и доказательствами.
- Макет, спецификация или открытый Pull Request не доказывают production-ready реализацию.
- Внешние интеграции должны быть явными, версионированными, изолированными и тестируемыми.

## Карта документации

- [Модель выполнения](docs/execution-model.md)
- [Жизненный цикл сигналов](docs/SIGNAL_PIPELINE_LIFECYCLE.md)
- [Сопоставление runtime-архетипов](docs/ARCHETYPE_RUNTIME_MAPPING.md)

## NUN Mesh и связанные репозитории
[SAMBU](https://github.com/bboroski/SAMBU) · [ToolNG](https://github.com/bboroski/ToolNG) · [ReaperCripple](https://github.com/bboroski/ReaperCripple) · [Kloz](https://github.com/bboroski/Kloz) · [CO](https://github.com/bboroski/CO) · [SaintSI](https://github.com/bboroski/SaintSI) · [Klipot](https://github.com/bboroski/Klipot) · [NUN](https://github.com/bboroski/NUN) · [NUNLauncher](https://github.com/bboroski/NUNLauncher)

Каждый репозиторий сохраняет каноническое имя, собственный код, API, цикл выпуска и границы ответственности. Интеграция означает версионированные контракты, а не автоматическое слияние независимых runtime.

## Дизайн и документация
Общее направление интерфейсов — **Duck Black / Yellow**: тёмные поверхности, жёлтые акценты для действий и состояний, читаемая типографика, доступный контраст, клавиатурная навигация и поддержка reduced motion. Подробности — в [design/DUCK_UI_SYSTEM.md](design/DUCK_UI_SYSTEM.md), если файл присутствует.

## Лицензия
Лицензия не объявлена; файл LICENSE отсутствует.

---
**Создано с любовью к инженерии, системности и людям.**


## Палитра Duck Black / Yellow
Совместимые цвета прежних badges и marks: `#FFD600` (жёлтый) и `#111111` (почти чёрный). Текущий фон интерфейса — `#0D0D0D`. Полная палитра из шести цветов, четырнадцати функциональных оттенков и значения RGB/HSL находятся в `design/duck-ui.tokens.json` (schema 3.0.0). Жёлтый зарезервирован для основных действий, фокуса и выделения; красный и голубой обозначают семантические ошибки и информационные состояния.
