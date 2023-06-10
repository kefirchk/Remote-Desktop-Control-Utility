# Remote-Desktop-Control-Utility

				                          Курсовой проект
				                              на тему
				    
		                  УТИЛИТА УДАЛЕННОГО УПРАВЛЕНИЯ КОМПЬЮТЕРОМ
		
			                                                 Выполнил
			                                                 студент гр. 150501
			                                                 Климович А.Н.
			                              Минск 2023

##### ------------------------------------------------------------------------------------
##### Требуемые библиотеки и пакеты 
##### ------------------------------------------------------------------------------------			  

//=========			
// 1. Qt 
//=========

Так как проект разрабатывался в Qt Creator, то для генерации Makefile с помощью qmake
требуется установить следующие пакеты:
 
 	$ sudo apt install qt5-base-dev

###### P.S. Для написания проекта использовалась Qt Creator 6.0.2 на основе Qt 5.15.3 (GCC 11.2.0, 64 бита).

//=========
// 2. X11.
//=========

Установка на Linux:

	$ sudo apt-get install libxst-dev
	$ sudo apt-get update
	
В проект также добавлены следующие флаги компиляции: -lX11 и -lXst.


##### ------------------------------------------------------------------------------------
##### Сборка
##### ------------------------------------------------------------------------------------			  

//===============================
// Для сборки сервера необходимо:
//===============================

1. В каталоге /build/build-RemoteControlServer-Desktop-Debug в терминале прописать следующее:
	
	qmake ../../src/RemoteControlServer
	
2. В каталоге /build/build-RemoteControlServer-Desktop-Debug в терминале прописать следующее:

	make clean all 
				или
	make
	
3. Далее в каталоге /build/build-RemoteControlServer-Desktop-Debug можно запустить проект:
	
	./RemoteControlServer
	 
//===============================	 
// Для сборки клиента необходимо:
//===============================
	
1. В каталоге /build/build-RemoteControlClient-Desktop-Debug в терминале прописать следующее:
	
	qmake ../../src/RemoteControlServer
	
2. В каталоге ./build/build-RemoteControlClient-Desktop-Debug в терминале прописать следующее:

	make clean all 
				или
	make
	
3. Далее в каталоге /build/build-RemoteControlClient-Desktop-Debug можно запустить проект:
	
	./RemoteControlClient  
	 


##### ------------------------------------------------------------------------------------
##### Описание работы с программами
##### ------------------------------------------------------------------------------------		          

//====================
// RemoteControlServer
//====================

В поле "Пароль" указывается пароль, по которому клиент сможет подключиться к серверу.

"Включить" -- включение сервера.
"Выключить" -- выключение сервера.
"Меню->Выход" -- завершение работы сервера.

После нажатия на кнопку "Включить" сервер в течении 10 секунд будет ожидать входящего
запроса на подлкючение от клиента. Если запроса не приходит, сервер автоматически выключается.

//====================
// RemoteControlClient
//====================

"Меню->Настройки":
	В поле "IP сервера" указывается IP адрес сервера, к которому подключается клиент.
	В поле "Пароль" указывается пароль, по которому клиент подключается к серверу.
"Меню->Выход" -- завершение работы клиента.
"Связь->Присоединиться к серверу" -- подлключиться к серверу.
"Связь->Отсоединиться от сервера" -- отключиться от сервера.

После нажатия на кнопку "Связь->Присоединиться к серверу" клиент будет получать скриншоты экрана
сервера с частатой, заданной в config.h. Также буду обрабатываться нажатия мыши и клавиатуры.

"F12" -- изменение размеров экрана.

##### ------------------------------------------------------------------------------------
##### Примечания 
##### ------------------------------------------------------------------------------------

Некоторые переменные возможно изменить в конфигурационном файле config.h.
Каталоги /Screenshots, созданные в каталогах /build/build-RemoteControlServer-Desktop-Debug и
/build/build-RemoteControlClient-Desktop-Debug ни в коем случае нельзя удалять!!!

