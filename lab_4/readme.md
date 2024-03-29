# Синхронизация процессов при помощи событий, мьютексов и семафоров

## Задача

Написать программу для консольного процесса Administrator и консольных процессов Reader и Writer. Для моделирования передачи сообщений ввести специальные события (с ручным сбросом для Reader), которые обозначают сообщение “A”, сообщение “B”, и автоматическое событие - конец сеанса для процессов Reader и Writer. Одновременно принимать и отправлять сообщения могут только ОДИН АКТИВНЫЙ процесс Writer (использовать мьютекс), и ДВА АКТИВНЫХ процесса Reader (использовать семафор), передача остальных сообщений от других процессов должна временно блокироваться (находиться в режиме ожидания).

### Объекты синхронизации:
- Мьютекс - синхронизация работы Writer и Reader (одновременно может работать только один Writer).
- Семафор - синхронизация работы Reader (одновременно может работать только два Reader).
- События - передача сообщений между Writer и Reader, а также сигнализация о завершении сеанса.

### Процесс Administrator должен выполнить следующие действия:
1. Инициализировать необходимые объекты синхронизации.
2. Запросить у пользователя количество процессов Writer и количество отправленных и принятых сообщений для процессов Writer и Reader.
3. Запустить заданное количество процессов Reader и Writer.
4. Принимать от каждого процесса Reader и Writer сообщение о завершении сеанса и выводить его на консоль в одной строке.
5. Завершить свою работу.

### Процесс Writer должен выполнить следующие действия:
1. Синхронизировать работу процессов Writer с помощью мьютекса.
2. Передачу сообщений реализовать с помощью событий с ручным сбросом.
3. Запрашивать с консоли сообщения, и передавать их (по одному) процессам Reader.
4. Передавать сообщение (с автоматическим сбросом) о завершении сеанса процессу Administrator.
5. Завершить свою работу.

### Процесс Reader должен выполнить следующие действия:
1. Синхронизировать работу процессов Reader с помощью семафора.
2. Передачу сообщений реализовать с помощью событий.
3. Принимать сообщения (с ручным сбросом) от процесса Writer.
4. Выводить на консоль сообщения.
5. Передавать сообщение (с автоматическим сбросом) о завершении сеанса процессу Administrator.
6. Завершить свою работу.
