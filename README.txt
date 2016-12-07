Параметры запуска:
  Обязательные:
  "-l <link>" -- ссылка на репозиторий
  "-d <directory>" -- рабочая директория для репозитория
  
  Необязательные: 
  "--include-patterns" -- если параметр указан, после того как репозиторий будет развёрнут, пользователю будет предложено настроить файл конфигурации.
  "--disable-input" -- если параметр указан, пользователю не будет предлагаться ввод с клавиатуры.
  "-b <name>" -- название используемой ветки (по умолчанию master)
  "-h", "--help" -- отобразить помощь

Настройка файла конфигурации:
  Программа ищет два файла:
    1) Файл конфигурации развёрнутого проекта (по умолчанию config.php).
    2) Файл в формате CSV в котором записано какие подстроки нужно заменить в файле конфигурации (по умолчанию config_templates.csv).
  Если какой-то из файлов не найден, программа попросит ввести пользователя название файла или полный путь к нему в ручную.
  
CSV-файл должен быть составлен по следующим правилам:
  1) Каждая строка -- одно правило замены.
  2) Правило замены записывается в таком виде:
  
  <Шаблон>,<Подставляемое_значение>