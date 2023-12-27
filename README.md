# SF_Project_5
## Приложение для сетевого чата (использование протокола TCP)
**Установка / Начало работы**

:white_check_mark:___Сервер должен быть запущен первым!!! Иначе связь не установится.___

Открыть два приложения: Server и Client

Работать необходимо в приложении Client.

Server: автоматически подключается база данных MySQL (необходимо указать пароль для БД в функции Handler_MySQL::create_connection_BD)

:white_check_mark: ___Чтобы начать, необходимо пройти регистрацию (нажать 1) ввести:___
1. имя
2. логин
3. пароль (пароль сохраняется в виде хэша с использованием алгоритма SHA-1)

___Каждый из зарегистрированных пользователей, автоматически подключается к чату (авторизуется)___

:white_check_mark: ___Чтобы высылать сообщения другим пользователям или просмотреть личные сообщения,___

___необходимо авторизоваться (нажать 2) ввести:___
1. логин
2. пароль (автоматически преобразовывается с использованием хэш-функции)

:white_check_mark: ___Высылать и принимать сообщения (нажать 3):___ 
  
     's' - отправлять сообщения,

     'r' - получить сообщения; 
 
:white_check_mark: ___Cообщения сохраняются и считываются из БД, связь с которой устанавливается по сети___

## Разработан
:wink: Поповой Оксаной Станиславовной (студент SkillFactory CPLUS-33)

### c использованием:

Паттерна проектирования Наблюдатель (Observer)
   
### Структура проекта

1. Класс ClientCode обеспечивает вызов функций для взаимодействия пользователей с чатом.
2. Класс User (пользователь Observer) позволяет конкретному пользователю взаимодействовать с чатом:
      - создание нового пользователя;
      - авторизация;
      - выход из чата;
      - отправка сообщений  и получение сообщений;
4. Класс Chat (чат Subject) подключается к БД MySQL и взаимодействует с ней и с пользователем по сети:
      - добавление нового пользователя;
      - подключение пользователя к чату;
      - отсоединение пользователя от чата;
      - хранение и рассылка сообщений.
5. Класс Messages связан с классом Chat и User, позволяет отправлять и принимать сообщения по сети.
6. В проекте реализованы:
      - Абстрактные классы: IObserver, ISubject.
      - Шаблонный класс Messages.
      - Использованы принципы ООП: наследование, абстракция, инкапсуляция.
      - Использован механизм Run-Time Type Information (RTTI).
      - Добавлена возможность обработки исключений.
      - Использованы контейнеры cтандартной библиотеки шаблонов STL.
