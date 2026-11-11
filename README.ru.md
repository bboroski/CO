# CO
**Deterministic Component Lifecycle Runtime**

[Українська](README.md) · [English](README.en.md) · [Русский](README.ru.md)

Компактный runtime на C11 для предсказуемого запуска, пошагового выполнения и завершения компонентов без полноценной RTOS.

## Возможности
- Явные состояния STOPPED, STARTING, RUNNING, STEPPING, FAULTED и STOPPING.
- Runtime storage предоставляет вызывающая сторона; heap не используется.
- Callbacks init, step и shutdown с передачей ошибок.
- Защита от рекурсии и host-тесты fault/partial-initialization сценариев.

## Запуск и проверка
```bash
make test
python one.py check
```

## Границы
CO — runtime на C11 без графического интерфейса; настоящих скриншотов приложения нет.

CO не реализует preemption, interrupt scheduler или MMIO. Вызывающая сторона сериализует доступ из независимых контекстов; планирование и watchdog policy остаются внешними.

## Документация проекта

*Статическая схема экосистемы, не скриншот приложения CO.*

## Связанные проекты
[Документация](docs/) · [API-заголовки](include/)

[Kloz](https://github.com/bboroski/Kloz) · [SaintSI](https://github.com/bboroski/SaintSI)

## Лицензия
Корневой LICENSE не объявлен; перед повторным использованием проверьте условия репозитория.

---
**心心相印。**
*Два сердца понимают друг друга без слов.*
— Китайский идиом
