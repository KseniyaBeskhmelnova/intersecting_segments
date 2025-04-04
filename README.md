# Поиск пары пересекающихся отрезков

Этот проект решает задачу нахождения пересекающихся отрезков на плоскости. Он включает реализацию двух алгоритмов — наивного и эффективного с использованием структур данных (АВЛ-дерево и (2,3)-дерево), а также предоставляет возможность тестировать алгоритмы на случайных данных.  
🖋️Подробно о проекте и результатах экспериментов в отчёте - файл beskhmelnova_report.pdf  

---

## Постановка задачи

Дано множество \( S \), состоящее из \( n \) отрезков на плоскости. Каждый отрезок \( s_i = S[i] \) задан координатами своих концевых точек в декартовой системе координат. Необходимо определить, есть ли среди этих отрезков хотя бы два пересекающихся. Если пересечение найдено, программа должна вывести "истина" (true) и номера пересекающихся отрезков \( s_1 \) и \( s_2 \). В случае, если пересечений нет, следует вывести "ложь" (false).  

---

## Входные и выходные данные

### Входные данные:
✔️ \( n \) — количество отрезков.  
✔️ Для каждого отрезка задаются координаты его концов.

### Выходные данные:
✔️ **В случае пересечения**: "true", а также номера пересекающихся отрезков \( s_1 \) и \( s_2 \).  
✔️ **В случае отсутствия пересечений**: "false".

Также программа выводит время работы наивного и эффективного алгоритмов: 
- \( T_1 \) — время работы наивного алгоритма.
- \( T_2 \) — время работы эффективного алгоритма.  

---

### Алгоритмы решения задачи

1. **Наивный алгоритм (INTERSECTION_NAIVE)**:
   - В этом алгоритме каждый отрезок проверяется на пересечение с каждым другим. Это приводит к сложности \( O(n^2) \), что делает его неэффективным при больших значениях \( n \).
   
2. **Эффективный алгоритм с использованием АВЛ-дерева и (2,3)-дерева (INTERSECTION_EFFECTIVE)**:
   - Для ускорения нахождения пересечений используется АВЛ-дерево и 2-3 дерево, которые позволяют работать с отрезками быстрее. В этом случае сложность алгоритма снижается до \( O(n \log n) \).  

---

## Структуры данных

В реализации использованы следующие структуры данных:

1. **АВЛ-дерево**:
   - Самобалансирующееся бинарное дерево поиска, которое используется для эффективного поиска пересечений отрезков.
   
2. **(2,3)-дерево**:
   - Дерево поиска, которое поддерживает балансировку и обеспечивает более быструю работу с данными.  

---

## Способы задания отрезков

1. **Автоматический способ с псевдослучайными координатами концов отрезков**:
   - Генерация отрезков с случайными координатами их концов внутри квадрата единичной длины.
   
2. **Автоматический способ с заданной длиной \( r \) отрезков**:
   - Генерация отрезков с фиксированной длиной \( r \), случайными центрами внутри квадрата и случайными углами с осью абсцисс.

3. **Ручной ввод координат концов отрезков**:
   - Пользователь может вручную ввести координаты концов отрезков.  

---

## Эксперименты

1. **Эксперимент с первым способом задания отрезков**: 
   - \( n = 1, 2, ..., 10^4+1 \) с шагом 100. Строятся графики \( T_1(n) \) и \( T_2(n) \).
   
2. **Эксперимент с первым способом задания отрезков и \( k \)**:
   - \( n = 10^4+3 \), \( k = 1, 2, ..., 10^4+1 \) с шагом 100. Строятся графики \( T_1(k) \) и \( T_2(k) \).
   
3. **Эксперимент со вторым способом задания отрезков с фиксированной длиной \( r = 0.001 \)**:
   - \( n = 1, 2, ..., 10^4+1 \) с шагом 100. Строятся графики \( T_1(n) \) и \( T_2(n) \).
   
4. **Эксперимент со вторым способом задания отрезков с фиксированной длиной \( r \)**:
   - \( r = 0.0001, 0.0002, ..., 0.01 \) с шагом 0.0001, \( n = 10^4 \). Строятся графики \( T_1(r) \) и \( T_2(r) \).  

### Параметры экспериментов

✔️ **Количество отрезков \( n \)**, варьирующее от 1 до \( 10^4 \) с шагом 100.  
✔️ **Параметр \( k \)** для выбора пересекающихся отрезков, если используется автоматическая генерация.  
✔️ **Длина отрезков \( r \)** для эксперимента с заданной длиной отрезков.  