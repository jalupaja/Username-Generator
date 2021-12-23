# youName
A username and password generator written in C++

This project has been implemented into [MultiTool](https://github.com/jalupaja/MultiTool) and will be archived!

# Features:
- -h  | --help		Show this output
- -n  | --name		Create new random username
- -nL | --nameLower	Create new lowercase username
- -nU | --nameUpper	Create new uppercase username
- -p  | --pass		Create new password
- -pO | --passOptions Set pasword options ('a'->use lower character, 'A'->use upper characters, '1'->use numbers, '+'->use special characters)
- -r  | --repeat		Set how many names/passwords you want
- -l  | --maxLength	Set maximum length for username/password
- -lm | --minLength	Set minimum length for username

# Shortcut Features:
- name [r]
- nameLower [r]
- nameUpper [r]
- pass [l] [r]

# Usage:
    youName ( -h | -n | -nL | -nU | -p ) [ -pO [aA1+] -r [x] -l [x] -lM [x] ]
