# Генетический алгоритм для решения задачи про 30 единиц
## Условие
Есть функция, которой на вход подается n x-ов: $x_1, x_2, ..., x_n$.

$f(x_1, x_2, ..., x_n) = \sum_{i=1}^n x_i$

Каждый x может принимать только значения 0 или 1.

Задача заключается в том, чтобы подобрать такие x-ы, чтобы функция максимизировалась.

## Алгоритм решения
1. Создаем изначальную популяцию из случайных значений.
2. Пока максимальная сумма единиц элементов популяции не стала равна n:
	1. Выполняем селекцию (отбираем m элементов популяции с максимальным значением f).
	2. Скрещиваем элементы, чтобы получить $2m$ элементов.
	3. Мутируем случайное количество случайных элементов (инвертируем случайное кол-во их случайных битов).
	4. Выполняем поиск новой максимальной суммы единиц в популяции.
3. Выводим результат.
