<p align="center"><img src="assets/duck-ui/duck-mark.svg" alt="CO mark" width="92"></p>
<h1 align="center">CO</h1>
<p align="center"><strong>Deterministic Component Lifecycle Runtime</strong></p>
<p align="center"><img src="https://img.shields.io/badge/STATUS-HOST-TESTED%20C11%20CORE-FFD600?style=for-the-badge&labelColor=111111" alt="Host-tested C11 core"></p>
<p align="center"><a href="README.md">🇺🇦 Українська</a> · <a href="README.en.md">🇬🇧 English</a> · <a href="README.ru.md">🇷🇺 Русский</a></p>

> **CO** — CO — компактний C11 runtime для передбачуваного запуску, виконання кроків і завершення компонентів без вимоги повноцінної RTOS.

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

## Інженерна якість
- Перевіряйте збірку й тести саме для цільової платформи; host CI не замінює hardware qualification.
- Статуси **implemented**, **partial**, **planned** мають підтверджуватися кодом, тестами та документацією.
- Не оголошуйте функцію production-ready лише на підставі макета, специфікації чи відкритого Pull Request.
- Зовнішні інтеграції мають бути явними, версіонованими, ізольованими й перевірюваними.

## NUN Mesh та пов'язані репозиторії
[SAMBU](https://github.com/bboroski/SAMBU) · [ToolNG](https://github.com/bboroski/ToolNG) · [ReaperCripple](https://github.com/bboroski/ReaperCripple) · [Kloz](https://github.com/bboroski/Kloz) · [CO](https://github.com/bboroski/CO) · [SaintSI](https://github.com/bboroski/SaintSI) · [Klipot](https://github.com/bboroski/Klipot) · [NUN](https://github.com/bboroski/NUN) · [NUNLauncher](https://github.com/bboroski/NUNLauncher) · [Fragile-Baby](https://github.com/bboroski/Fragile-Baby) · [Luci](https://github.com/bboroski/Luci)

Репозиторії зберігають власні назви, код, API, цикли випуску та межі відповідальності. Інтеграція означає узгоджені контракти, а не автоматичне злиття незалежних runtime.

## Дизайн і документація
Базовий інтерфейсний напрям екосистеми — **Duck Black / Yellow**: чорні поверхні, жовтий акцент для дій і станів, читабельна типографіка, доступний контраст, клавіатурна навігація та підтримка reduced motion. Деталі дивіться в [design/DUCK_UI_SYSTEM.md](design/DUCK_UI_SYSTEM.md), якщо файл присутній у цьому репозиторії.

## Ліцензія
Ліцензію не оголошено; файл LICENSE відсутній.

---
**Створено з любов'ю до інженерії, системності та людей.**
