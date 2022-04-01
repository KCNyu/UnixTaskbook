# Shell: порождение процессов и их взаимодействие

## ***Формулировки задач***
---
**Shell1:** Написать программу shellD1, моделирующую конструкцию командного интерпретатора:

    cmdA A1 A2 ... AN ; cmdB B1 B2 ... BM  

Эта конструкция обеспечивает последовательное выполнение команд cmdA и cmdB: вначале запускается команда cmdA с параметрами A1, A2, ..., AN, затем запускается команда cmdB с параметрами B1, B2, ..., BM. Каждая команда использует стандартный вывод на экран.

Формат вызова программы shellD1:

    shellD1 cmdA N A1 A2 ... AN cmdB M B1 B2 ... BM

---

**Shell2:** Написать программу shellD2, моделирующую конструкцию командного интерпретатора:

    cmdA A1 A2 ... AN && cmdB B1 B2 ... BM

Эта конструкция выполняет следующие действия. Вначале запускается команда cmdA с параметрами A1, A2, ..., AN; если эта команда завершилась успешно (код выхода равен 0), то запускается команда cmdB с параметрами B1, B2, ..., BM. Каждая команда использует стандартный вывод на экран.
Формат вызова программы shellD2:

    shellD2 cmdA N A1 A2 ... AN cmdB M B1 B2 ... BM

**Shell3:** Написать программу shellD3, моделирующую конструкцию командного интерпретатора:

    cmdA A1 A2 ... AN || cmdB B1 B2 ... BM

Эта конструкция выполняет следующие действия. Вначале запускается команда cmdA с параметрами A1, A2, ..., AN; если эта команда завершилась с ошибкой (код выхода не равен 0), то запускается команда cmdB с параметрами B1, B2, ..., BM. Каждая команда использует стандартный вывод на экран.
Формат вызова программы shellD3:

    shellD3 cmdA N A1 A2 ... AN cmdB M B1 B2 ... BM

**Shell4:** Написать программу shellD4, моделирующую конструкцию командного интерпретатора:

    cmdA A1 A2 ... AN | cmdB B1 B2 ... BM

Эта конструкция выполняет следующие действия. Вначале запускается команда cmdA с параметрами A1, A2, ..., AN; вывод этой команды перенаправляется на вход команды команда cmdB с параметрами B1, B2, ..., BM (т. е. организуется конвейер). Команда cmdB использует стандартный вывод на экран.
Формат вызова программы shellD4:

    shellD4 cmdA N A1 A2 ... AN cmdB M B1 B2 ... BM

Вначале указывается имя команды cmdA, количество N ее параметров и сами параметры (если параметры отсутствуют, то количество должно быть равно 0), затем имя команды cmdB, количество M ее параметров и сами параметры.
D5. Написать программу shellD5, моделирующую конструкцию командного интерпретатора:
    cmdA A1 A2 ... AN < file
Эта конструкция обеспечивает выполнение команды cmdA с параметрами A1, A2, ..., AN, причем ввод этой команды перенаправляется из файла с именем file (который должен существовать). Команда cmdA использует стандартный вывод на экран.
Формат вызова программы shellD5:
    shellD5 file cmdA N A1 A2 ... AN
Вначале указывается имя существующего файла file, затем команда cmdA, количество N ее параметров и сами параметры (если параметры отсутствуют, то количество должно быть равно 0).
D6. Написать программу shellD6, моделирующую конструкцию командного интерпретатора:
19

cmdA A1 A2 ... AN > file
Эта конструкция обеспечивает выполнение команды cmdA с параметрами A1, A2, ..., AN, причем вывод этой команды перенаправляется в файл с именем file. Если указанный файл отсутствует, то он создается, если он существует, то его прежнее содержимое удаляется.
Формат вызова программы shellD6:
    shellD6 file cmdA N A1 A2 ... AN
Вначале указывается имя файла file, затем команда cmdA, количество N ее параметров и сами параметры (если параметры отсутствуют, то количество должно быть равно 0).
D7. Написать программу shellD7, моделирующую конструкцию командного интерпретатора:
    cmdA A1 A2 ... AN >> file
Эта конструкция обеспечивает выполнение команды cmdA с параметрами A1, A2, ..., AN, причем вывод этой команды перенаправляется в файл с именем file. Если указанный файл отсутствует, то он создается, если он существует, то новое содержимое добавляется в его конец.
Формат вызова программы shellD7:
    shellD7 file cmdA N A1 A2 ... AN
Вначале указывается имя файла file, затем команда cmdA, количество N ее параметров и сами параметры (если параметры отсутствуют, то количество должно быть равно 0).
D8. Написать программу shellD8, моделирующую конструкцию командного интерпретатора:
( cmdA A1 A2 ... AN ; cmdB B1 B2 ... BM ) > file
Эта конструкция обеспечивает последовательное выполнение команд cmdA и cmdB: вначале запускается команда cmdA с параметрами A1, A2, ..., AN, затем запускается команда cmdB с параметрами B1, B2, ..., BM. При этом вывод каждой команды перенаправляется в файл с именем file. Если указанный файл отсутствует, то он создается, если он существует, то его прежнее содержимое удаляется.
Формат вызова программы shellD8:
shellD8 file cmdA N A1 A2 ... AN cmdB M B1 B2 ... BM
Вначале указывается имя файла file, затем команда cmdA, количество N ее параметров и сами параметры (если параметры отсутствуют, то количество должно быть равно 0), затем имя команды cmdB, количество M ее параметров и сами параметры.
D9. Написать программу shellD9, моделирующую конструкцию командного интерпретатора:
( cmdA A1 A2 ... AN || cmdB B1 B2 ... BM ) | cmdC C1 C2 ... CP >> file
Эта конструкция выполняет следующие действия. Вначале запускается команда cmdA с параметрами A1, A2, ..., AN; если эта программа завершилась с ошибкой (код выхода не равен 0), то запускается команда cmdB с параметрами B1, B2, ..., BM. Стандартный вывод успешно проработавшей команды перенаправляется на стандартный ввод команды cmdC с параметрами C1, C2, ..., CP. Стандартный вывод команды cmdC перенаправляется в файл file, причем если файл не существует, то он создается, а если существует, то дополняется новыми данными.
Формат вызова программы shellD9:
shellD9 file cmdA N A1 A2 ... AN cmdB M B1 B2 ... BM cmdC P C1 C2 ... CP
Вначале указывается имя файла file, затем имя команды cmdA, количество N ее параметров и сами параметры (если параметры отсутствуют, то количество должно быть равно 0), затем имя команды cmdB, количество M ее параметров и сами параметры, затем имя команды cmdC, количество P ее параметров и сами параметры.