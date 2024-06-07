@echo off

:: copy data folder into the build folder
rmdir "BUILD\ParticleEngine\data" /s /q 2> nul
robocopy "ParticleEngine\ParticleEngine\data" "BUILD\ParticleEngine\data" /e
del "BUILD\ParticleEngine\credits.txt" /f
copy "ParticleEngine\ParticleEngine\credits.txt" "BUILD\ParticleEngine\credits.txt" /y
pause