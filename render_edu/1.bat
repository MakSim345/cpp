    @echo off
     
     
    rem  Triangle rasterization.bat 
    rem  (c) 2008 Aleksej Borisov aka Imp5
    rem
     
     
    set tex0=.............................................................
    set tex4=0000000000000000000000000000000000000000000000000000000000000
     
    set /a width=61
    set /a height=24
     
    set /a width100=width*100
    set /a height100=height*100
     
     
    set /a trix1=40
    set /a triy1=40
    set /a trix2=40
    set /a triy2=40
    set /a trix3=40
    set /a triy3=40
    set /a tridx1=100
    set /a tridy1=200
    set /a tridx2=300
    set /a tridy2=400
    set /a tridx3=500
    set /a tridy3=300
     
     
    :main_loop
     
    call :clear_buf
    call :render_triangle_subpix %trix1% %triy1% %trix2% %triy2% %trix3% %triy3 tex4
    call :flip_buf
     
    set /a trix1+=tridx1
    set /a triy1+=tridy1
    if %trix1% LEQ -100 set /a tridx1=-tridx1
    if %triy1% LEQ -100 set /a tridy1=-tridy1
    if %trix1% GTR %width100% set /a tridx1=-tridx1
    if %triy1% GTR %height100% set /a tridy1=-tridy1
     
    set /a trix2+=tridx2
    set /a triy2+=tridy2
    if %trix2% LEQ -100 set /a tridx2=-tridx2
    if %triy2% LEQ -100 set /a tridy2=-tridy2
    if %trix2% GTR %width100% set /a tridx2=-tridx2
    if %triy2% GTR %height100% set /a tridy2=-tridy2
     
    set /a trix3+=tridx3
    set /a triy3+=tridy3
    if %trix3% LEQ -100 set /a tridx3=-tridx3
    if %triy3% LEQ -100 set /a tridy3=-tridy3
    if %trix3% GTR %width100% set /a tridx3=-tridx3
    if %triy3% GTR %height100% set /a tridy3=-tridy3
     
    goto main_loop
     
     
     
    :clear_buf
        set scan0=%tex0%
        set scan1=%tex0%
        set scan2=%tex0%
        set scan3=%tex0%
        set scan4=%tex0%
        set scan5=%tex0%
        set scan6=%tex0%
        set scan7=%tex0%
        set scan8=%tex0%
        set scan9=%tex0%
        set scan10=%tex0%
        set scan11=%tex0%
        set scan12=%tex0%
        set scan13=%tex0%
        set scan14=%tex0%
        set scan15=%tex0%
        set scan16=%tex0%
        set scan17=%tex0%
        set scan18=%tex0%
        set scan19=%tex0%
        set scan20=%tex0%
        set scan21=%tex0%
        set scan22=%tex0%
        set scan23=%tex0%
        set scan24=%tex0%
    goto EOF
     
    :flip_buf
        cls
        echo %scan0%
        echo %scan1%
        echo %scan2%
        echo %scan3%
        echo %scan4%
        echo %scan5%
        echo %scan6%
        echo %scan7%
        echo %scan8%
        echo %scan9%
        echo %scan10%
        echo %scan11%
        echo %scan12%
        echo %scan13%
        echo %scan14%
        echo %scan15%
        echo %scan16%
        echo %scan17%
        echo %scan18%
        echo %scan19%
        echo %scan20%
        echo %scan21%
        echo %scan22%
        echo %scan23%
        echo %scan24%
    goto EOF
     
    :render_triangle_subpix
        set /a x1=%1
        set /a y1=%2
        set /a x2=%3
        set /a y2=%4
        set /a x3=%5
        set /a y3=%6
     
        if %y1% GTR %y2% (
            set /a tmp=y1
            set /a y1=y2
            set /a y2=tmp
            set /a tmp=x1
            set /a x1=x2
            set /a x2=tmp
        )
     
        if %y2% GTR %y3% (
            set /a tmp=y2
            set /a y2=y3
            set /a y3=tmp
            set /a tmp=x2
            set /a x2=x3
            set /a x3=tmp
        )
     
        if %y1% GTR %y2% (
            set /a tmp=y1
            set /a y1=y2
            set /a y2=tmp
            set /a tmp=x1
            set /a x1=x2
            set /a x2=tmp
        )
     
        set /a dx1=((x2-x1)*100)/(y2-y1+3)
        set /a dx2=((x3-x1)*100)/(y3-y1+3)
        set /a curx1=x1
        set /a curx2=x1
        set /a cury=y1
       
        :top_tri_loop
            set /a s_curx1=(curx1+50)/100
            set /a s_curx2=(curx2+50)/100
            set /a s_cury=(cury+50)/100
            call :horz_line %s_curx1% %s_curx2% %s_cury% %7
            set /a cury+=100
            set /a curx1+=dx1
            set /a curx2+=dx2
        if %cury% LEQ %y2% goto top_tri_loop
     
     
        set /a cury=y3
        set /a curx1=x3
        set /a curx2=x3
        set /a dx1=((x3-x2)*100)/(y3-y2+3)
        set /a dx2=((x3-x1)*100)/(y3-y1+3)
        :bottom_tri_loop
            set /a s_curx1=(curx1+50)/100
            set /a s_curx2=(curx2+50)/100
            set /a s_cury=(cury+50)/100
            call :horz_line %s_curx1% %s_curx2% %s_cury% %7
            set /a cury-=100
            set /a curx1-=dx1
            set /a curx2-=dx2
        if %cury% GEQ %y2% goto bottom_tri_loop
     
    goto EOF
     
    :horz_line
        if %3 LEQ -1 goto EOF
        if %3 GTR %height% goto EOF
        set /a xx1=%1
        set /a xx2=%2
        if %xx1% GTR %xx2% (
            set /a tmp=xx1
            set /a xx1=xx2
            set /a xx2=tmp
        )
        if %xx1% GTR %width% goto EOF
        if %xx2% LEQ -1 goto EOF
        if %xx1% LEQ -1 set /a xx1=0
        if %xx2% GTR %width% set /a xx2=width
        if %xx2% LSS %xx1% goto EOF
        set /a len=xx2-xx1
        set /a last=width-xx2
        call set fragment=%%%4:~0,%len%%%
        call set scan%3=%%scan%3:~0,%xx1%%%%fragment%%%scan%3:~%xx2%,%last%%%
    goto EOF
     
     
    :EOF 

