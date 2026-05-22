# Компілятор
CC = gcc

# Прапорці компіляції
CFLAGS = -Wall -Wextra -std=c11 -g

# Бібліотеки для лінкування (обов'язково -lm для математики)
LIBS = -lm

# Назва кінцевого виконуваного файлу
TARGET = ComplexTask_test

# Стандартна ціль
all: $(TARGET)

# 1. Лінкування виконуваного файлу з об'єктних файлів
$(TARGET): ComplexTask.o ComplexTask_test.o
	$(CC) $(CFLAGS) -o $(TARGET) ComplexTask.o ComplexTask_test.o $(LIBS)

# 2. Компіляція модуля ComplexTask.c у ComplexTask.o (залежить від ComplexTask.h)
ComplexTask.o: ComplexTask.c ComplexTask.h
	$(CC) $(CFLAGS) -c ComplexTask.c -o ComplexTask.o

# 3. Компіляція тестового файлу ComplexTask_test.c у ComplexTask_test.o (залежить від ComplexTask.h)
ComplexTask_test.o: ComplexTask_test.c ComplexTask.h
	$(CC) $(CFLAGS) -c ComplexTask_test.c -o ComplexTask_test.o

# Варіант запуску програми
run: $(TARGET)
	./$(TARGET)

# Очищення проекту від скомпільованих та тимчасових файлів
clean:
	rm -f ComplexTask.o ComplexTask_test.o $(TARGET) ComplexTask_result.txt

# Створення фіктивного тестового файлу
create_test_file:
	@echo "1.0 2.0" > ComplexTask_test.dat
	@echo "-3.0 2.0" >> ComplexTask_test.dat
	@echo "2.0 -1.0" >> ComplexTask_test.dat
	@echo "0.5 0.3" >> ComplexTask_test.dat
	@echo "0.000001" >> ComplexTask_test.dat
	@echo "0.0 0.0" >> ComplexTask_test.dat
	@echo "-6.0 0.0" >> ComplexTask_test.dat
	@echo "-20.0 0.0" >> ComplexTask_test.dat
	@echo "-1.0" >> ComplexTask_test.dat
	@echo "-1.0" >> ComplexTask_test.dat
	@echo "1.0" >> ComplexTask_test.dat
	@echo "-2.0" >> ComplexTask_test.dat
	@echo "1" >> ComplexTask_test.dat
	@echo "1.5 2.5" >> ComplexTask_test.dat
	@echo "3.0 1.0" >> ComplexTask_test.dat
	@echo "Тестовий файл ComplexTask_test.dat згенеровано."