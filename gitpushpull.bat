@echo off
REM This script will add, commit, and push all changes, then SSH to the server and pull+make

REM Set your commit message here or prompt for it
set /p msg="Enter commit message: "

git add -A
git commit -m "%msg%"
git push

REM SSH and run pull+make on remote
ssh -i "c:/Users/Owner/Downloads/LightsailDefaultKey-us-east-2.pem" ubuntu@3.15.195.148 "cd ~/circle-3.1/src && git pull && make"
