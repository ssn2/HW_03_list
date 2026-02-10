#!/bin/env bash

# Лишние выводы я подавил, считаю что тесты у меня 
# безгрешны, идеальны и безошибочны
# Расписывать устал, поэтому ...
# Ну и параметры читать обычный пользователь не может.
# Ибо нечего тут.

# Рюшечки никому не нужные. Но давно на bashe не практиковался
# Терминал трогать не буду, придётся много гуглить
# Основные цвета
BOLD='\033[1m'
BLINK='\033[5m'
BLACK='\033[30m'
RED='\033[31m'
GREEN='\033[32m'
YELLOW='\033[33m'
BLUE='\033[34m'
MAGENTA='\033[35m'
CYAN='\033[36m'
WHITE='\033[37m'

# Сброс цвета
NC='\033[0m'


# Пути к переменным
full_p=/sys/module/supermod_2/parameters/
p_idx=${full_p}idx
p_ch_val=${full_p}ch_val
p_my_str=${full_p}my_str


# Функция проверки формирования строки 'Hello, World!'
function check_build_Hello() {
  echo -e "${BOLD}${BLUE}=== Проверяем правильность формирования строки ===${NC}"
  # Объявляем массив кодов симвлов строки и пусть будет ещё и конец строки 0x10
  declare -a ch_codes=($(od -An -tuC <<< 'Hello, World!'))
  for i in $(seq 0 1 $((${#ch_codes[@]}-2))); do
    echo ${ch_codes[${i}]} > ${p_ch_val}
    echo ${i} > ${p_idx}
  done
  echo -e "${YELLOW}*** Включаем debug скрипта - дублирование команды на консоль ***${NC}"
  set -x
  cat ${p_my_str}
  set +x
  echo -e "${YELLOW}*** Проверили глазами? А сейчас ещё программно проверим (из-за ограничений 0 теперь проваливает тест ***${NC}"
  if [[ $(cat ${p_my_str}) != "Hello, World!" ]]; then
      echo -e "${RED}${BLINK}Тест провален!${NC}"
      exit 1
  fi
  echo -e "${GREEN}=== Тесты на формирование строки пройдены успешно! ===\n${NC}"
}

# Функция проверки работы с idx
# Для простоты не будем генерировать случайного пользователя,
# примем, что в системе уже есть пользователь student
function check_idx() {
  echo -e "${BLUE}${BOLD}=== Проверяем правильность работы с idx  ===${NC}"
  echo -e "${YELLOW}*** Передаём отрицательное значение *** ${NC}"
  echo -1 > ${p_idx} 2>/dev/null && { 
    echo -e "${RED}${BLINK}Тест провален${NC}"
    exit 1
  }
  echo -e "${GREEN}OK!${NC}"
  echo -e "${YELLOW}*** Передаём ноль  ***${NC}"
  echo 0 > ${p_idx} 2> /dev/null || {
    echo -e "${RED}${BLINK}Тест провален${NC}"
    exit 1
  }
  echo -e "${GREEN}OK!${NC}"
  echo -e "${YELLOW}*** Передаём значение больше длины строки ***${NC}"
  echo 56 > ${p_idx} 2> /dev/null && {
    echo -e "${RED}${BLINK}Тест провален${NC}"
    exit 1
  }
  echo -e "${GREEN}OK!${NC}"
  echo -e "${YELLOW}*** Передаём символ ***${NC}"
  echo Ф > ${p_idx} 2> /dev/null && {
    echo -e "${RED}${BLINK}Тест провален${NC}"
    exit 1
  }
  echo -e "${GREEN}OK!${NC}"
  echo -e "${YELLOW}*** Передаём строку ***${NC}"
  echo куцкацуsada > ${p_idx} 2> /dev/null && {
    echo -e "${RED}${BLINK}Тест провален${NC}"
    exit 1
  }
  echo -e "${GREEN}OK!${NC}"
  echo -e "${YELLOW}*** Передаём значение от обычного пользователя ***${NC}"
  su - student -c "echo цкацуsada > ${p_idx}" 2> /dev/null && {
    echo -e "${RED}${BLINK}Тест провален${NC}"
    exit 1
  }
  echo -e "${GREEN}OK!${NC}"
  echo -e "${YELLOW}*** Читаем значение от обычного пользователя ***${NC}"
  su - student -c "cat ${p_idx}" 2> /dev/null && {
    echo -e "${RED}${BLINK}Тест провален${NC}"
    exit 1
  }
  echo -e "${GREEN}OK!${NC}"
  echo -e "${BOLD}${GREEN}=== Тесты на работу с idx пройдены успешно! ===\n${NC}"
}

# Слишком много кода, поэтому дальше в стиле ... и в продакш
# Хотя ... скопируем что было выше!
function check_ch_val() {
  echo -e "${BOLD}${BLUE}=== Проверяем правильность работы с ch_val ===${NC}"
  echo -e "${YELLOW}*** Передаём отрицательное значение *** ${NC}"
  echo -1 > ${p_ch_val} 2>/dev/null && { 
    echo -e "${RED}${BLINK}Тест провален${NC}"
    exit 1
  }
  echo -e "${GREEN}OK!${NC}"
  echo -e "${YELLOW}*** Передаём меньше чем 32  ***${NC}"
  echo 22 > ${p_ch_val} 2> /dev/null && {
    echo -e "${RED}${BLINK}Тест провален${NC}"
    exit 1
  }
  echo -e "${GREEN}OK!${NC}"
  echo -e "${YELLOW}*** Передаём значение больше максимального значения ASCII-кода по ДЗ - 127 ***${NC}"
  echo 130 > ${p_ch_val} 2> /dev/null && {
    echo -e "${RED}${BLINK}Тест провален${NC}"
    exit 1
  }
  echo -e "${GREEN}OK!${NC}"
  echo -e "${YELLOW}*** Передаём символ ***${NC}"
  echo Ф > ${p_ch_val} 2> /dev/null && {
    echo -e "${RED}${BLINK}Тест провален${NC}"
    exit 1
  }
  echo -e "${GREEN}OK!${NC}"
  echo -e "${YELLOW}*** Передаём строку ***${NC}"
  echo куцкацуsada > ${p_ch_val} 2> /dev/null && {
    echo -e "${RED}${BLINK}Тест провален${NC}"
    exit 1
  }
  echo -e "${GREEN}OK!${NC}"
  echo -e "${YELLOW}*** Передаём значение от обычного пользователя ***${NC}"
  su - student -c "echo цкацуsada > ${p_ch_val}" 2> /dev/null && {
    echo -e "${RED}${BLINK}Тест провален${NC}"
    exit 1
  }
  echo -e "${GREEN}OK!${NC}"
  echo -e "${YELLOW}*** Читаем значение от обычного пользователя ***${NC}"
  su - student -c "cat ${p_ch_val}" 2> /dev/null && {
    echo -e "${RED}${BLINK}Тест провален${NC}"
    exit 1
  }
  echo -e "${GREEN}OK!${NC}"
  echo -e "${BOLD}${GREEN}=== Тесты на работу с ch_val пройдены успешно! ===\n${NC}"
}

function check_my_str() {
  echo -e "${BOLD}${BLUE}=== Проверяем правильность работы с my_str ===${NC}"
  echo -e "${YELLOW}*** Передаём строку ***${NC}"
  { echo "куцкацуsada" > ${p_my_str}; } 2> /dev/null && {
    echo -e "${RED}${BLINK}Тест провален${NC}"
    exit 1
  }
  echo -e "${GREEN}OK!${NC}"
  echo -e "${YELLOW}*** Читаем значение от обычного пользователя ***${NC}"
  su - student -c "cat ${p_my_str}" 2> /dev/null && {
    echo -e "${RED}${BLINK}Тест провален${NC}"
    exit 1
  }
  echo -e "${GREEN}OK!${NC}"
  echo -e "${BOLD}${GREEN}=== Тесты на работу с my_str пройдены успешно! ===\n${NC}"
  echo -e "${BOLD}${MAGENTA}=== Все тесты пройдены успешно! ===\n${NC}"
    
}

# Проверяем загружен ли модуль
if lsmod | grep -q supermod_2; then
  clear
  check_build_Hello
  check_idx
  check_ch_val
  check_my_str
else
  echo "Беда, модуль не загружен."
  exit 1
fi
