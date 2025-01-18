https://github.com/okovtun/PD_311_NP.git
https://www.youtube.com/playlist?list=PLeqyOOqxeiINcYN1bkr6s2AP9k_3079eU

https://fibertop.ru/optic_connectors.htm/
https://www.chipdip.ru/info/import-ic-packages

NetworkProgramming

IMPORTANT:	Отработать занятие 2024.12.11

TODO:
1. При помощи анализатора протокола Wireshark выяснить как работает крманда tracert.
	Для удобства использования лучше всего вводить tracert со следующими ключами:
		tracert -d -w 1 host

TODO:
0. Вывести информацию о сети:
	адрес сети, широковещательный адрес для этой сети, и количество узлов сети;	DONE
1. Обеспечить невозможность некоректного ввода маски;
2. Добавить кнопку "Разложить", при нажатии на которую откроется окно, 
   содержащее информацию о всех подсетях, находящихся в одной классовой сети
   с текущей подсетью;
3. Сеть, введенная в главном окне должна подсвечиваться;
3. В открывшемся окне должна быть кнопка "Сохранить", которая сохраняет информацию о подсетях в файл;

https://github.com/okovtun/PV_319_WIN

TOREAD:
	https://datatracker.ietf.org/doc/html/rfc791
	RFC - Request For Comment;
	IETF - Internet Engineering Task Force;
	IPclasses:	https://datatracker.ietf.org/doc/html/rfc796

TODO:
1. В зависимости от введенных IP-адреса и маски в поле 'Info' будет выводиться:
   адрес сети, широковещательный адрес для этой сети, и количество узлов сети.
   https://learn.microsoft.com/en-us/windows/win32/uxguide/ctrl-spin-controls
   https://learn.microsoft.com/en-us/windows/win32/controls/up-down-control-reference
2. При вводе IP-адреса должна определяться маска и префикс;
3. При изменении маски должен реагировать префикс, и наоборот, 
   при изменении префикса должна реагировать маска;

DONE:
1. Добить сеть класса 'С': 192.168.100.0/24.
   Нужно разделить ее на максимально-возможное количество подсетей;
2. Взять произвольную сеть класса 'B' и разделить ее на 32 подсети;

Network Equipment:
1. Peripheral:	135 239 * 8 = 1,081,912 р.
	https://www.citilink.ru/product/kommutator-zyxel-xgs2220-30-eu0101f-upravlyaemyi-1974989/
2. Central:	   953 039р.
	https://www.citilink.ru/product/kommutator-zyxel-xs3800-28-zz0101f-upravlyaemyi-1167736/properties/
3. Server NIC:  22 119р.
	https://www.citilink.ru/product/setevoi-adapter-10g-etherrnet-zyxel-xgn100c-zz0102f-pci-express-x4-2012285/
4. WiFi APs:	17 600р.
	https://www.citilink.ru/product/tochka-dostupa-zyxel-nebulaflex-nwa50ax-nwa50ax-eu0102f-1595122/properties/
5. PoE Switch: 181 699р.
	https://www.citilink.ru/product/kommutator-zyxel-xgs2220-30hp-eu0101f-upravlyaemyi-1974990/properties/

EIA/TIA 568-A/B	UTP

TODO:
1. Подобрать оборудование для локальной сети в 100 компьютеров, у каждого компьютера должен быть канал 1Gbps.
   Компы буду расположены в аудиториях в количестве по 10-15шт.
   На магистральных участвках сети скорость должна быть не меньше 2.5 Gbps.
   Так же нужно обеспечить доступ беспроводных клиентов, желательно с возможностью безшовного роуминга (802-11r/k/v).
2. https://learn.microsoft.com/ru-ru/windows/win32/fileio/microsoft-smb-protocol-and-cifs-protocol-overview

DONE:
1. Разъемы для оптических кабелей;
	https://avatars.mds.yandex.net/i?id=d8d4814a4439f6dde9786c74be3acc31_l-7755802-images-thumbs&n=13
2. Изучить спецификации технологии Ethernet:
	100Base-TX;
	100Base-FX;
	100Base-T4;

	1000Base-T;
	1000Base-F;

3. Изучить спецификации Ethernet:
	2.5Gpps;
	 5 Gbps;
	10 Gbps;
По каждой спкцификации: тип кабеля, максимальная длина кабеля, по каким парам идет передача, метод кодирования.