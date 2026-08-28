@echo off
echo Compilando simulacao do ao_watch...

set QPC=C:\qp\qpc
set INC=-I"%QPC%\include" -I"%QPC%\ports\win32-qv" -I.

set SRC1="%QPC%\src\qf\qep_hsm.c" "%QPC%\src\qf\qep_msm.c" "%QPC%\src\qf\qf_act.c" "%QPC%\src\qf\qf_actq.c" "%QPC%\src\qf\qf_defer.c" "%QPC%\src\qf\qf_dyn.c" "%QPC%\src\qf\qf_mem.c"
set SRC2="%QPC%\src\qf\qf_ps.c" "%QPC%\src\qf\qf_qact.c" "%QPC%\src\qf\qf_qeq.c" "%QPC%\src\qf\qf_qmact.c" "%QPC%\src\qf\qf_time.c"
set PORT="%QPC%\ports\win32-qv\qf_port.c"

gcc -O0 -g %INC% main.c simu.c %SRC1% %SRC2% %PORT% -o simu.exe

if %errorlevel% neq 0 (
    echo.
    echo [ERRO] Falha na compilacao! Verifique os erros acima.
) else (
    echo.
    echo [SUCESSO] Compilado com sucesso. Digite simu.exe para rodar!
)