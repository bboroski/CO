<p align="center"><img src="assets/duck-ui/duck-mark.svg" alt="CO mark" width="92"></p>
<h1 align="center">CO</h1>
<p align="center"><strong>Deterministic Component Lifecycle Runtime</strong></p>
<p align="center"><img src="https://img.shields.io/badge/STATUS-HOST-TESTED%20C11%20CORE-FFD600?style=for-the-badge&labelColor=111111" alt="Host-tested C11 core"></p>
<p align="center"><a href="README.md">🇺🇦 Українська</a> · <a href="README.en.md">🇬🇧 English</a> · <a href="README.ru.md">🇷🇺 Русский</a></p>
<sub>Оновлено: 2026-11-12</sub>


## NEON SYNDICATE — візуальна система

<p align="center"><img src="assets/neon-syndicate/overview.svg" alt="CO — NEON SYNDICATE deterministic runtime concept" width="1200"></p>
<p align="center"><em>Векторна схема lifecycle runtime, а не скриншот виконання чи live telemetry.</em></p>

[Брендбук](design/NEON_SYNDICATE.md) · [Токени](design/neon-syndicate.tokens.json)

## Поточні можливості
- Явна машина станів STOPPED, STARTING, RUNNING, STEPPING, FAULTED і STOPPING.
- Runtime-об'єкт у пам'яті, наданій викликачем; heap не використовується.
- Callback API init, step і shutdown з передаванням помилок.
- Захист від рекурсивних poll/stop під час callback.
- Host-тести старту, fault paths, часткової ініціалізації та recursion guards.

## Швидкий старт і перевірка
```bash
make test
make clean
python one.py check
```

## Архітектура, межі та достовірність
CO не реалізує preemption, interrupt scheduler або MMIO. Викликач серіалізує доступ із незалежних контекстів; scheduling, priorities, deadlines і watchdog залишаються зовнішніми.

## Інтерфейс і архітектурна візуалізація

CO — компактний C11 runtime-компонент без графічного інтерфейсу. Скриншотів GUI немає; нижче наведено карту екосистеми та загальний дизайн-напрям Duck UI, не інтерфейс CO.

<p align="center"><img src="assets/nun-mesh.svg" alt="Карта NUN Mesh: незалежні компоненти та версіоновані контракти" width="960"></p>
<p align="center"><em>Карта екосистеми</em></p>
<p align="center"><img src="assets/neon-syndicate/overview.svg" alt="Спільний дизайн Duck Black Yellow, не GUI CO" width="960"></p>

## Інженерна якість
- Перевіряйте збірку й тести саме для цільової платформи; host CI не замінює hardware qualification.
- Статуси **implemented**, **partial**, **planned** мають підтверджуватися кодом, тестами та документацією.
- Не оголошуйте функцію production-ready лише на підставі макета, специфікації чи відкритого Pull Request.
- Зовнішні інтеграції мають бути явними, версіонованими, ізольованими й перевірюваними.

## Карта документації

- [Модель виконання](docs/execution-model.md)
- [Життєвий цикл сигналів](docs/SIGNAL_PIPELINE_LIFECYCLE.md)
- [Мапування runtime-архетипів](docs/ARCHETYPE_RUNTIME_MAPPING.md)

## Ліцензія
Ліцензію не оголошено; файл LICENSE відсутній.

---

## Статус інтеграцій

- Репозиторій зберігає власні API, збірку, тести та цикл випуску; міжпроєктна взаємодія відбувається через явні версіоновані контракти.
- STaas (SaaS integration control plane) і MoonTreach (CI/test acceleration) розвиваються окремими Pull Requests. Їх не слід вважати можливостями `main` або production-ready до злиття та проходження обов'язкових перевірок.
- Правила федерації та інтеграції: [Hellduck Integration Playbook](https://github.com/bboroski/Hellduck/blob/main/docs/INTEGRATION_PLAYBOOK.md).

## Інженерний стандарт
Індекс аудиту, тестових воріт, безпеки, супроводу та критеріїв інтеграції: [Engineering Improvement Index](docs/ENGINEERING_IMPROVEMENT_INDEX.md).

## Інтеграційні межі
Зберігайте незалежні API, runtime та цикли випуску; інтегруйте через версіоновані контракти. [Hellduck Integration Playbook](https://github.com/bboroski/Hellduck/blob/main/docs/INTEGRATION_PLAYBOOK.md).

---
**「在天愿作比翼鸟，在地愿为连理枝。」**

*«У небі — птахами-нерозлучниками, на землі — гілками одного дерева».*
