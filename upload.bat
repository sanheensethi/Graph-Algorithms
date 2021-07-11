@echo OFF
echo GITHUB
PAUSE
set /p msg=Enter commit msg:
git status
git add .
git status
git commit -m %msg%
git push
PAUSE