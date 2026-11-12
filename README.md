# CO
**Детермінований C11 runtime для життєвого циклу компонентів.**

Ініціалізація, виконання кроків і зупинка компонентів через явну машину станів.


## Можливості
- Стани STOPPED, STARTING, RUNNING, STEPPING, FAULTED і STOPPING.
- Runtime-об'єкт у пам'яті, наданій викликачем; heap не використовується.
- Callback API init, step і shutdown із передаванням помилок.
- Захист від рекурсивних poll/stop під час callback.
- Host-тести старту, fault paths, часткової ініціалізації та recursion guards.

## Запуск і перевірка
```bash
make test
make clean
python one.py check
```

## Межі
CO — C11 runtime без графічного інтерфейсу; реальних скриншотів застосунку немає.

CO — runtime-компонент, а не повна операційна система чи універсальний процесний supervisor. Host-тести не замінюють перевірку на цільовому обладнанні.

## Пов'язані проєкти
[Kloz](https://github.com/bboroski/Kloz) · [ReaperCripple](https://github.com/bboroski/ReaperCripple)

## Ліцензія
Ліцензію не оголошено.

---
**「山有木兮木有枝，心悦君兮君不知。」**
*«На горі є дерева й гілля; моє серце любить тебе, та ти не знаєш».*
— «Пісня Юерен» (《越人歌》)